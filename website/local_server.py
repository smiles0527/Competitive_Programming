from __future__ import annotations

import argparse
import hashlib
import json
import os
import re
import secrets
import tempfile
import html
from http import HTTPStatus
from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
from urllib.parse import parse_qs, unquote, urlparse


REPOSITORY = Path(__file__).resolve().parent.parent
MAX_BODY = 10 * 1024 * 1024


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


class EditorialHandler(SimpleHTTPRequestHandler):
    server_version = "EditorialLocalServer/1.0"

    def end_headers(self) -> None:
        self.send_header("X-Content-Type-Options", "nosniff")
        self.send_header("Referrer-Policy", "no-referrer")
        super().end_headers()

    def do_GET(self) -> None:
        parsed = urlparse(self.path)
        if parsed.path == "/__editor/status":
            authorized = self.headers.get("X-Local-Editor-Token") == self.server.editor_token
            self.send_json({"mode": "local", "authorized": authorized})
            return
        if parsed.path == "/__editor/file":
            if not self.authorized(): return
            try:
                query = parse_qs(parsed.query)
                relative, target = self.validated_path(query.get("path", [""])[0])
                data = target.read_bytes()
                self.send_json({"path": relative, "sha": digest(data), "content": data.decode("utf-8")})
            except FileNotFoundError:
                self.send_json({"error": "File not found"}, HTTPStatus.NOT_FOUND)
            except (ValueError, UnicodeDecodeError) as error:
                self.send_json({"error": str(error)}, HTTPStatus.BAD_REQUEST)
            return
        if parsed.path == "/__editor/catalog":
            if not self.authorized(): return
            try:
                self.send_json({"items": self.editorial_catalog()})
            except (OSError, UnicodeDecodeError) as error:
                self.send_json({"error": str(error)}, HTTPStatus.INTERNAL_SERVER_ERROR)
            return
        super().do_GET()

    def editorial_catalog(self) -> list[dict]:
        required = ["Problem", "Idea", "Algorithm", "Correctness", "Implementation", "Complexity", "Worked Example"]
        placeholders = ["state the task precisely", "describe the first implementation step", "state the central invariant", "add the official constraints", "trace the central state"]
        items = []
        for collection in sorted(self.server.editable_roots):
            root = (REPOSITORY / collection).resolve()
            if not root.is_dir():
                continue
            for editorial_dir in sorted(root.rglob("editorials")):
                if not editorial_dir.is_dir():
                    continue
                section_dir = editorial_dir.parent
                preview = section_dir / "preview.html"
                listed = {}
                if preview.is_file():
                    preview_text = preview.read_text(encoding="utf-8")
                    for file_name, label in re.findall(r'<option\s+value="editorials/([^"/]+\.md)"[^>]*>(.*?)</option>', preview_text, re.IGNORECASE | re.DOTALL):
                        listed[file_name] = re.sub(r"<[^>]+>", "", label).strip()
                for md in sorted(editorial_dir.glob("*.md")):
                    markdown = md.read_text(encoding="utf-8")
                    cpp = section_dir / f"{md.stem}.cpp"
                    code = cpp.read_text(encoding="utf-8") if cpp.is_file() else ""
                    heading = re.search(r"^#\s+(.+?)\s*$", markdown, re.MULTILINE)
                    title = heading.group(1).strip() if heading else listed.get(md.name, md.stem)
                    present = set(re.findall(r"^##\s+(.+?)\s*$", markdown, re.MULTILINE))
                    missing = [name for name in required if name not in present]
                    lower = markdown.lower()
                    found_placeholders = [phrase for phrase in placeholders if phrase in lower]
                    issues = []
                    if not cpp.is_file(): issues.append("Missing C++ file")
                    elif len(code.strip()) < 80: issues.append("C++ solution looks unfinished")
                    if missing: issues.append("Missing " + ", ".join(missing))
                    if found_placeholders: issues.append("Template text remains")
                    if len(markdown.split()) < 180: issues.append("Editorial is very short")
                    if md.name not in listed: issues.append("Not listed in the section preview")
                    if found_placeholders or len(markdown.split()) < 80:
                        quality = "draft"
                    elif missing or not cpp.is_file() or len(code.strip()) < 80:
                        quality = "incomplete"
                    else:
                        quality = "ready"
                    relative_md = md.relative_to(REPOSITORY).as_posix()
                    relative_cpp = cpp.relative_to(REPOSITORY).as_posix()
                    items.append({
                        "collection": collection,
                        "section": section_dir.relative_to(root).as_posix(),
                        "slug": md.stem,
                        "title": title,
                        "label": listed.get(md.name, title),
                        "markdownPath": relative_md,
                        "codePath": relative_cpp,
                        "listed": md.name in listed,
                        "quality": quality,
                        "issues": issues,
                        "words": len(markdown.split()),
                        "codeLines": len(code.splitlines()),
                        "modified": max(md.stat().st_mtime, cpp.stat().st_mtime if cpp.is_file() else 0)
                    })
        return items

    def do_POST(self) -> None:
        endpoint = urlparse(self.path).path
        if endpoint not in {"/__editor/login", "/__editor/save", "/__editor/create"}:
            self.send_json({"error": "Not found"}, HTTPStatus.NOT_FOUND)
            return
        if self.headers.get_content_type() != "application/json":
            self.send_json({"error": "JSON request required"}, HTTPStatus.UNSUPPORTED_MEDIA_TYPE)
            return
        try:
            length = int(self.headers.get("Content-Length", "0"))
            if length < 1 or length > MAX_BODY:
                raise ValueError("Invalid request size")
            body = json.loads(self.rfile.read(length))
            if endpoint == "/__editor/login":
                supplied = str(body.get("password", ""))
                if not secrets.compare_digest(supplied, self.server.editor_password):
                    self.send_json({"error": "Incorrect management password"}, HTTPStatus.UNAUTHORIZED)
                    return
                self.send_json({"authorized": True, "token": self.server.editor_token})
                return
            if not self.authorized(): return
            if endpoint == "/__editor/create":
                self.create_editorial(body)
                return
            files = body.get("files")
            if not isinstance(files, list) or not 1 <= len(files) <= 2:
                raise ValueError("One or two files are required")

            checked = []
            seen = set()
            for item in files:
                relative, target = self.validated_path(item.get("path", ""))
                if relative in seen:
                    raise ValueError("Duplicate file path")
                seen.add(relative)
                current = target.read_bytes()
                if not item.get("sha") or digest(current) != item["sha"]:
                    self.send_json({"error": f"{relative} changed on disk. Reload before saving."}, HTTPStatus.CONFLICT)
                    return
                content = str(item.get("content", "")).encode("utf-8")
                checked.append((relative, target, content))

            staged = []
            try:
                for relative, target, content in checked:
                    handle, temporary = tempfile.mkstemp(prefix=".editor-", suffix=".tmp", dir=target.parent)
                    with os.fdopen(handle, "wb") as stream:
                        stream.write(content)
                        stream.flush()
                        os.fsync(stream.fileno())
                    staged.append((relative, target, Path(temporary), content))
                for _, target, temporary, _ in staged:
                    os.replace(temporary, target)
            finally:
                for _, _, temporary, _ in staged:
                    temporary.unlink(missing_ok=True)

            self.send_json({
                "saved": True,
                "files": [{"path": relative, "sha": digest(content)} for relative, _, _, content in staged]
            })
        except FileNotFoundError:
            self.send_json({"error": "File not found"}, HTTPStatus.NOT_FOUND)
        except (ValueError, TypeError, json.JSONDecodeError) as error:
            self.send_json({"error": str(error)}, HTTPStatus.BAD_REQUEST)

    def authorized(self) -> bool:
        if self.headers.get("X-Local-Editor-Token") == self.server.editor_token:
            return True
        self.send_json({"error": "Management authorization required"}, HTTPStatus.UNAUTHORIZED)
        return False

    def create_editorial(self, body: dict) -> None:
        collection = str(body.get("collection", ""))
        section = str(body.get("section", ""))
        slug = str(body.get("slug", "")).lower()
        title = str(body.get("title", "")).strip()
        if collection not in self.server.editable_roots:
            raise ValueError("Collection is not editable")
        if not section or any(char not in "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 _-" for char in section):
            raise ValueError("Invalid category")
        if not slug or any(char not in "abcdefghijklmnopqrstuvwxyz0123456789_-" for char in slug):
            raise ValueError("Use lowercase letters, numbers, hyphens, or underscores for the file name")
        if not title:
            raise ValueError("Problem name is required")

        base = (REPOSITORY / collection / section).resolve()
        approved = (REPOSITORY / collection).resolve()
        if approved not in base.parents or not base.is_dir():
            raise ValueError("Category does not exist")
        editorial_dir = base / "editorials"
        preview = base / "preview.html"
        md = editorial_dir / f"{slug}.md"
        cpp = base / f"{slug}.cpp"
        if not editorial_dir.is_dir() or not preview.is_file():
            raise ValueError("Category is not configured for editorials")
        if md.exists() or cpp.exists():
            raise ValueError("An editorial or solution with this file name already exists")

        preview_text = preview.read_text(encoding="utf-8")
        marker = "    </select>"
        if marker not in preview_text:
            raise ValueError("Editorial picker was not found in the category preview")
        option = f'      <option value="editorials/{html.escape(slug)}.md">{html.escape(title.lower())}</option>\n'
        updated_preview = preview_text.replace(marker, option + marker, 1)
        markdown = str(body.get("markdown", ""))
        code = str(body.get("code", ""))

        created = []
        try:
            md.write_text(markdown, encoding="utf-8", newline="\n")
            created.append(md)
            cpp.write_text(code, encoding="utf-8", newline="\n")
            created.append(cpp)
            self.atomic_write(preview, updated_preview.encode("utf-8"))
        except Exception:
            for target in created:
                target.unlink(missing_ok=True)
            raise
        self.send_json({"created": True, "files": [f"{collection}/{section}/editorials/{slug}.md", f"{collection}/{section}/{slug}.cpp"]}, HTTPStatus.CREATED)

    @staticmethod
    def atomic_write(target: Path, content: bytes) -> None:
        handle, temporary = tempfile.mkstemp(prefix=".editor-", suffix=".tmp", dir=target.parent)
        try:
            with os.fdopen(handle, "wb") as stream:
                stream.write(content)
                stream.flush()
                os.fsync(stream.fileno())
            os.replace(temporary, target)
        finally:
            Path(temporary).unlink(missing_ok=True)

    def validated_path(self, value: str) -> tuple[str, Path]:
        relative = unquote(str(value)).replace("\\", "/").strip("/")
        parts = Path(relative).parts
        if len(parts) < 2 or parts[0] not in self.server.editable_roots:
            raise ValueError("Path is outside the approved editorial collections")
        if any(part in {"", ".", ".."} for part in parts) or Path(relative).suffix.lower() not in {".md", ".cpp"}:
            raise ValueError("Invalid editable path")
        target = (REPOSITORY / Path(*parts)).resolve()
        approved = (REPOSITORY / parts[0]).resolve()
        if target == approved or approved not in target.parents:
            raise ValueError("Path escaped its editorial collection")
        return relative, target

    def send_json(self, body: dict, status: int = HTTPStatus.OK) -> None:
        payload = json.dumps(body).encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Content-Length", str(len(payload)))
        self.send_header("Cache-Control", "no-store")
        self.end_headers()
        self.wfile.write(payload)


def main() -> None:
    parser = argparse.ArgumentParser(description="Serve the editorial site with safe local file editing")
    parser.add_argument("--port", type=int, default=8766)
    parser.add_argument("--editable-root", action="append", dest="roots", default=[])
    options = parser.parse_args()
    editable_roots = set(options.roots or ["CSES"])

    def handler(*args, **kwargs):
        return EditorialHandler(*args, directory=str(REPOSITORY), **kwargs)

    server = ThreadingHTTPServer(("127.0.0.1", options.port), handler)
    server.editor_token = secrets.token_urlsafe(32)
    server.editor_password = os.environ.get("EDITORIAL_EDITOR_PASSWORD") or secrets.token_urlsafe(10)
    server.editable_roots = editable_roots
    print(f"Local editorial site: http://127.0.0.1:{options.port}/website/index.html", flush=True)
    print(f"Editable roots: {', '.join(sorted(editable_roots))}", flush=True)
    print(f"Management password: {server.editor_password}", flush=True)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        print("\nLocal editorial server stopped.")


if __name__ == "__main__":
    main()
