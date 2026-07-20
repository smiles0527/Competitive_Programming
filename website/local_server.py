from __future__ import annotations

import argparse
import hashlib
import json
import os
import secrets
import tempfile
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
            self.send_json({"mode": "local", "token": self.server.editor_token})
            return
        if parsed.path == "/__editor/file":
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
        super().do_GET()

    def do_POST(self) -> None:
        if urlparse(self.path).path != "/__editor/save":
            self.send_json({"error": "Not found"}, HTTPStatus.NOT_FOUND)
            return
        if self.headers.get("X-Local-Editor-Token") != self.server.editor_token:
            self.send_json({"error": "Invalid local editor token"}, HTTPStatus.FORBIDDEN)
            return
        if self.headers.get_content_type() != "application/json":
            self.send_json({"error": "JSON request required"}, HTTPStatus.UNSUPPORTED_MEDIA_TYPE)
            return
        try:
            length = int(self.headers.get("Content-Length", "0"))
            if length < 1 or length > MAX_BODY:
                raise ValueError("Invalid request size")
            body = json.loads(self.rfile.read(length))
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
    server.editable_roots = editable_roots
    print(f"Local editorial site: http://127.0.0.1:{options.port}/website/index.html", flush=True)
    print(f"Editable roots: {', '.join(sorted(editable_roots))}", flush=True)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        print("\nLocal editorial server stopped.")


if __name__ == "__main__":
    main()
