const encoder = new TextEncoder();
const decoder = new TextDecoder();

export default {
  async fetch(request, env) {
    try {
      return await route(request, env);
    } catch (error) {
      return json({ error: error.message || "Unexpected gateway error" }, error.status || 500, request, env);
    }
  }
};

async function route(request, env) {
  const url = new URL(request.url);
  if (request.method === "OPTIONS") return corsResponse(request, env);

  if (url.pathname === "/auth/start" && request.method === "GET") {
    const state = await seal({ kind: "oauth", exp: Date.now() + 10 * 60_000 }, env.SESSION_SECRET);
    const callback = `${url.origin}/auth/callback`;
    const target = new URL("https://github.com/login/oauth/authorize");
    target.searchParams.set("client_id", env.GITHUB_CLIENT_ID);
    target.searchParams.set("redirect_uri", callback);
    target.searchParams.set("state", state);
    target.searchParams.set("allow_signup", "false");
    return Response.redirect(target.toString(), 302);
  }

  if (url.pathname === "/auth/callback" && request.method === "GET") {
    const state = await unseal(url.searchParams.get("state") || "", env.SESSION_SECRET);
    if (state.kind !== "oauth" || state.exp < Date.now()) throw httpError(401, "Expired sign-in request");
    const code = url.searchParams.get("code");
    if (!code) throw httpError(400, "GitHub did not return an authorization code");

    const tokenResponse = await fetch("https://github.com/login/oauth/access_token", {
      method: "POST",
      headers: { "Accept": "application/json", "Content-Type": "application/json", "User-Agent": "cses-editor-gateway" },
      body: JSON.stringify({
        client_id: env.GITHUB_CLIENT_ID,
        client_secret: env.GITHUB_CLIENT_SECRET,
        code,
        redirect_uri: `${url.origin}/auth/callback`
      })
    });
    const tokenBody = await tokenResponse.json();
    if (!tokenResponse.ok || !tokenBody.access_token) throw httpError(401, tokenBody.error_description || "GitHub sign-in failed");

    const user = await github("/user", tokenBody.access_token);
    if (String(user.login).toLowerCase() !== String(env.ALLOWED_LOGIN).toLowerCase()) {
      throw httpError(403, "This GitHub account is not allowed to edit the collection");
    }

    const session = await seal({
      kind: "session",
      login: user.login,
      token: tokenBody.access_token,
      exp: Date.now() + 60 * 60_000
    }, env.SESSION_SECRET);
    const destination = new URL(env.EDITOR_URL);
    destination.hash = new URLSearchParams({ session }).toString();
    return Response.redirect(destination.toString(), 302);
  }

  if (url.pathname === "/api/me" && request.method === "GET") {
    const session = await requireSession(request, env);
    return json({ login: session.login }, 200, request, env);
  }

  if (url.pathname === "/api/file" && request.method === "GET") {
    const session = await requireSession(request, env);
    const path = validatePath(url.searchParams.get("path"), env);
    const file = await github(`/repos/${env.GITHUB_OWNER}/${env.GITHUB_REPO}/contents/${encodePath(path)}?ref=${encodeURIComponent(env.GITHUB_BRANCH || "main")}`, session.token);
    if (file.type !== "file" || !file.content) throw httpError(404, "Repository file not found");
    return json({ path, sha: file.sha, content: decodeBase64Utf8(file.content.replace(/\n/g, "")) }, 200, request, env);
  }

  if (url.pathname === "/api/save" && request.method === "POST") {
    const session = await requireSession(request, env);
    const body = await request.json();
    if (!Array.isArray(body.files) || body.files.length < 1 || body.files.length > 2) throw httpError(400, "One or two files are required");
    const files = body.files.map(file => ({
      path: validatePath(file.path, env),
      content: String(file.content ?? ""),
      sha: String(file.sha || "")
    }));
    if (new Set(files.map(file => file.path)).size !== files.length) throw httpError(400, "Duplicate file path");
    const message = String(body.message || "Update CSES editorial").slice(0, 160);
    const result = await commitFiles(env, session.token, files, message);
    return json(result, 200, request, env);
  }

  if (url.pathname === "/health") return json({ ok: true }, 200, request, env);
  throw httpError(404, "Not found");
}

async function commitFiles(env, token, files, message) {
  const owner = env.GITHUB_OWNER;
  const repo = env.GITHUB_REPO;
  const branch = env.GITHUB_BRANCH || "main";
  const base = `/repos/${owner}/${repo}`;

  for (const file of files) {
    const current = await github(`${base}/contents/${encodePath(file.path)}?ref=${encodeURIComponent(branch)}`, token);
    if (!file.sha || current.sha !== file.sha) throw httpError(409, `${file.path} changed on GitHub. Reload before saving.`);
  }

  const ref = await github(`${base}/git/ref/heads/${encodeURIComponent(branch)}`, token);
  const parent = await github(`${base}/git/commits/${ref.object.sha}`, token);
  const blobs = [];
  for (const file of files) {
    const blob = await github(`${base}/git/blobs`, token, {
      method: "POST",
      body: { content: file.content, encoding: "utf-8" }
    });
    blobs.push({ ...file, newSha: blob.sha });
  }
  const tree = await github(`${base}/git/trees`, token, {
    method: "POST",
    body: {
      base_tree: parent.tree.sha,
      tree: blobs.map(file => ({ path: file.path, mode: "100644", type: "blob", sha: file.newSha }))
    }
  });
  const commit = await github(`${base}/git/commits`, token, {
    method: "POST",
    body: { message, tree: tree.sha, parents: [ref.object.sha] }
  });
  await github(`${base}/git/refs/heads/${encodeURIComponent(branch)}`, token, {
    method: "PATCH",
    body: { sha: commit.sha, force: false }
  });
  return {
    commit: commit.sha,
    files: blobs.map(file => ({ path: file.path, sha: file.newSha })),
    deployment: "queued"
  };
}

async function requireSession(request, env) {
  const authorization = request.headers.get("Authorization") || "";
  if (!authorization.startsWith("Bearer ")) throw httpError(401, "Sign in required");
  const session = await unseal(authorization.slice(7), env.SESSION_SECRET);
  if (session.kind !== "session" || session.exp < Date.now()) throw httpError(401, "Session expired");
  if (String(session.login).toLowerCase() !== String(env.ALLOWED_LOGIN).toLowerCase()) throw httpError(403, "Account not allowed");
  return session;
}

function validatePath(value, env) {
  const path = String(value || "").replace(/\\/g, "/");
  const segments = path.split("/");
  const roots = String(env.EDITABLE_ROOTS || "CSES").split(",").map(root => root.trim()).filter(Boolean);
  if (segments.length < 2 || !roots.includes(segments[0]) || segments.some(segment => !segment || segment === "." || segment === "..")) {
    throw httpError(400, "Path is outside the approved editorial collections");
  }
  if (!/^[\w .+\-\/]+\.(?:md|cpp)$/.test(path)) throw httpError(400, "Invalid editable path");
  return path;
}

async function github(path, token, options = {}) {
  const response = await fetch(`https://api.github.com${path}`, {
    method: options.method || "GET",
    headers: {
      "Accept": "application/vnd.github+json",
      "Authorization": `Bearer ${token}`,
      "Content-Type": "application/json",
      "User-Agent": "cses-editor-gateway",
      "X-GitHub-Api-Version": "2022-11-28"
    },
    body: options.body ? JSON.stringify(options.body) : undefined
  });
  const body = await response.json().catch(() => ({}));
  if (!response.ok) throw httpError(response.status, body.message || "GitHub request failed");
  return body;
}

async function seal(value, secret) {
  const iv = crypto.getRandomValues(new Uint8Array(12));
  const key = await encryptionKey(secret);
  const ciphertext = new Uint8Array(await crypto.subtle.encrypt({ name: "AES-GCM", iv }, key, encoder.encode(JSON.stringify(value))));
  const joined = new Uint8Array(iv.length + ciphertext.length);
  joined.set(iv); joined.set(ciphertext, iv.length);
  return base64Url(joined);
}

async function unseal(value, secret) {
  try {
    const joined = fromBase64Url(value);
    const iv = joined.slice(0, 12);
    const ciphertext = joined.slice(12);
    const key = await encryptionKey(secret);
    const plaintext = await crypto.subtle.decrypt({ name: "AES-GCM", iv }, key, ciphertext);
    return JSON.parse(decoder.decode(plaintext));
  } catch {
    throw httpError(401, "Invalid or expired session");
  }
}

async function encryptionKey(secret) {
  const digest = await crypto.subtle.digest("SHA-256", encoder.encode(secret));
  return crypto.subtle.importKey("raw", digest, "AES-GCM", false, ["encrypt", "decrypt"]);
}

function base64Url(bytes) {
  let binary = "";
  for (const byte of bytes) binary += String.fromCharCode(byte);
  return btoa(binary).replace(/\+/g, "-").replace(/\//g, "_").replace(/=+$/, "");
}

function fromBase64Url(value) {
  const base64 = value.replace(/-/g, "+").replace(/_/g, "/") + "===".slice((value.length + 3) % 4);
  return Uint8Array.from(atob(base64), character => character.charCodeAt(0));
}

function decodeBase64Utf8(value) {
  const binary = atob(value);
  return decoder.decode(Uint8Array.from(binary, character => character.charCodeAt(0)));
}

function encodePath(path) { return path.split("/").map(encodeURIComponent).join("/"); }
function httpError(status, message) { const error = new Error(message); error.status = status; return error; }

function allowedOrigin(request, env) {
  const origin = request.headers.get("Origin");
  return origin === env.SITE_ORIGIN ? origin : env.SITE_ORIGIN;
}

function corsHeaders(request, env) {
  return {
    "Access-Control-Allow-Origin": allowedOrigin(request, env),
    "Access-Control-Allow-Headers": "Authorization, Content-Type",
    "Access-Control-Allow-Methods": "GET, POST, OPTIONS",
    "Access-Control-Max-Age": "86400",
    "Vary": "Origin",
    "Cache-Control": "no-store"
  };
}

function corsResponse(request, env) { return new Response(null, { status: 204, headers: corsHeaders(request, env) }); }
function json(body, status, request, env) {
  return new Response(JSON.stringify(body), { status, headers: { "Content-Type": "application/json; charset=utf-8", ...corsHeaders(request, env) } });
}
