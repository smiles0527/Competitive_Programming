const JSON_HEADERS = {
  "content-type": "application/json; charset=utf-8",
  "cache-control": "no-store",
};

export default {
  async fetch(request, env) {
    try {
      if (request.method === "OPTIONS") {
        return new Response(null, {
          status: 204,
          headers: corsHeaders(request, env),
        });
      }

      const url = new URL(request.url);
      const path = url.pathname.replace(/\/+$/, "") || "/";
      let response;

      if (path === "/health" && request.method === "GET") {
        response = json({ ok: true, service: "editorial-cms" });
      } else if (path === "/auth/start" && request.method === "GET") {
        response = await startGithubAuth(request, env);
      } else if (path === "/auth/callback" && request.method === "GET") {
        response = await finishGithubAuth(request, env);
      } else if (path === "/auth/dev" && request.method === "GET") {
        response = await devLogin(request, env);
      } else if (path === "/api/catalog" && request.method === "GET") {
        response = await getCatalog(env);
      } else if (path === "/api/problems" && request.method === "GET") {
        response = await getProblems(url, env);
      } else if (path === "/api/editorials" && request.method === "GET") {
        response = await getPublishedEditorials(url, env);
      } else if (path === "/api/me" && request.method === "GET") {
        response = json({ user: await requireUser(request, env) });
      } else if (path === "/api/dashboard" && request.method === "GET") {
        response = await getDashboard(request, env);
      } else if (path === "/api/structure" && request.method === "GET") {
        response = await getStructure(request, env);
      } else if (
        path === "/api/structure/reorder" &&
        request.method === "POST"
      ) {
        response = await reorderStructure(request, env);
      } else if (path === "/api/collections" && request.method === "POST") {
        response = await createCollection(request, env);
      } else if (path === "/api/sections" && request.method === "POST") {
        response = await createSection(request, env);
      } else if (path === "/api/problems" && request.method === "POST") {
        response = await createProblem(request, env);
      } else if (path === "/api/users" && request.method === "GET") {
        response = await listUsers(request, env);
      } else if (path === "/api/export" && request.method === "GET") {
        response = await exportDatabase(request, env);
      } else if (path === "/api/editorials" && request.method === "POST") {
        response = await createEditorial(request, env);
      } else {
        const editorialMatch = path.match(
          /^\/api\/editorials\/(\d+)(?:\/(submit|withdraw|review|publish|archive|restore|duplicate))?$/,
        );
        const userMatch = path.match(/^\/api\/users\/(\d+)\/role$/);
        const collectionMatch = path.match(/^\/api\/collections\/([^/]+)$/);
        const sectionMatch = path.match(/^\/api\/sections\/(\d+)$/);
        const problemMatch = path.match(/^\/api\/problems\/(\d+)$/);

        if (editorialMatch) {
          const id = Number(editorialMatch[1]);
          const action = editorialMatch[2] || "";
          if (!action && request.method === "GET")
            response = await getEditorial(request, env, id);
          else if (!action && request.method === "PUT")
            response = await updateEditorial(request, env, id);
          else if (!action && request.method === "PATCH")
            response = await updateEditorialMetadata(request, env, id);
          else if (!action && request.method === "DELETE")
            response = await deleteEditorial(request, env, id);
          else if (action === "submit" && request.method === "POST")
            response = await submitEditorial(request, env, id);
          else if (action === "withdraw" && request.method === "POST")
            response = await withdrawEditorial(request, env, id);
          else if (action === "review" && request.method === "POST")
            response = await reviewEditorial(request, env, id);
          else if (action === "publish" && request.method === "POST")
            response = await publishEditorial(request, env, id);
          else if (action === "archive" && request.method === "POST")
            response = await archiveEditorial(request, env, id);
          else if (action === "restore" && request.method === "POST")
            response = await restoreEditorial(request, env, id);
          else if (action === "duplicate" && request.method === "POST")
            response = await duplicateEditorial(request, env, id);
        } else if (collectionMatch && request.method === "PATCH") {
          response = await updateCollection(
            request,
            env,
            decodeURIComponent(collectionMatch[1]),
          );
        } else if (sectionMatch && request.method === "PATCH") {
          response = await updateSection(
            request,
            env,
            Number(sectionMatch[1]),
          );
        } else if (problemMatch && request.method === "PATCH") {
          response = await updateProblem(
            request,
            env,
            Number(problemMatch[1]),
          );
        } else if (userMatch && request.method === "PUT") {
          response = await updateUserRole(request, env, Number(userMatch[1]));
        }
      }

      if (!response) response = json({ error: "Not found" }, 404);
      return withCors(response, request, env);
    } catch (error) {
      const status = error.status || 500;
      if (status >= 500) console.error(error);
      return withCors(
        json(
          { error: status >= 500 ? "Internal server error" : error.message },
          status,
        ),
        request,
        env,
      );
    }
  },
};

function json(value, status = 200, extraHeaders = {}) {
  return new Response(JSON.stringify(value), {
    status,
    headers: { ...JSON_HEADERS, ...extraHeaders },
  });
}

function httpError(status, message) {
  const error = new Error(message);
  error.status = status;
  return error;
}

function corsHeaders(request, env) {
  const origin = request.headers.get("origin");
  if (!origin) return {};
  const allowed = new Set(
    [env.SITE_ORIGIN, "http://127.0.0.1:8766", "http://localhost:8766"].filter(
      Boolean,
    ),
  );
  if (!allowed.has(origin)) return {};
  return {
    "access-control-allow-origin": origin,
    "access-control-allow-headers": "authorization, content-type",
    "access-control-allow-methods": "GET, POST, PUT, OPTIONS",
    vary: "Origin",
  };
}

function withCors(response, request, env) {
  const headers = new Headers(response.headers);
  for (const [name, value] of Object.entries(corsHeaders(request, env)))
    headers.set(name, value);
  return new Response(response.body, { status: response.status, headers });
}

async function bodyJson(request) {
  try {
    return await request.json();
  } catch {
    throw httpError(400, "Expected a JSON request body");
  }
}

function randomToken(bytes = 32) {
  const data = crypto.getRandomValues(new Uint8Array(bytes));
  return Array.from(data, (byte) => byte.toString(16).padStart(2, "0")).join(
    "",
  );
}

function ownerLogins(env) {
  return new Set(
    String(env.OWNER_LOGINS || "smiles0527")
      .split(",")
      .map((login) => login.trim().toLowerCase())
      .filter(Boolean),
  );
}

function isStaff(user) {
  return user.role === "owner" || user.role === "editor";
}

async function startGithubAuth(request, env) {
  if (!env.GITHUB_CLIENT_ID)
    throw httpError(503, "GitHub OAuth is not configured");
  const state = randomToken(20);
  const callback = new URL("/auth/callback", request.url).toString();
  const target = new URL("https://github.com/login/oauth/authorize");
  target.searchParams.set("client_id", env.GITHUB_CLIENT_ID);
  target.searchParams.set("redirect_uri", callback);
  target.searchParams.set("scope", "read:user");
  target.searchParams.set("state", state);
  return new Response(null, {
    status: 302,
    headers: {
      location: target.toString(),
      "set-cookie": `editorial_oauth_state=${state}; Path=/auth; HttpOnly; Secure; SameSite=Lax; Max-Age=600`,
    },
  });
}

async function finishGithubAuth(request, env) {
  const url = new URL(request.url);
  const state = url.searchParams.get("state") || "";
  const code = url.searchParams.get("code") || "";
  const cookieState =
    parseCookies(request.headers.get("cookie")).editorial_oauth_state || "";
  if (!code || !state || state !== cookieState)
    throw httpError(400, "Invalid or expired OAuth state");

  const tokenResponse = await fetch(
    "https://github.com/login/oauth/access_token",
    {
      method: "POST",
      headers: {
        accept: "application/json",
        "content-type": "application/json",
      },
      body: JSON.stringify({
        client_id: env.GITHUB_CLIENT_ID,
        client_secret: env.GITHUB_CLIENT_SECRET,
        code,
      }),
    },
  );
  const tokenBody = await tokenResponse.json();
  if (!tokenResponse.ok || !tokenBody.access_token)
    throw httpError(401, "GitHub authentication failed");

  const profileResponse = await fetch("https://api.github.com/user", {
    headers: {
      accept: "application/vnd.github+json",
      authorization: `Bearer ${tokenBody.access_token}`,
      "user-agent": "competitive-programming-editorial-cms",
      "x-github-api-version": "2022-11-28",
    },
  });
  const profile = await profileResponse.json();
  if (!profileResponse.ok || !profile.login)
    throw httpError(401, "Could not load the GitHub profile");

  const user = await upsertUser(env, {
    githubId: profile.id,
    login: profile.login,
    displayName: profile.name || profile.login,
    avatarUrl: profile.avatar_url || "",
  });
  const session = await createSession(env, user.id);
  const editorUrl =
    env.EDITOR_URL || `${env.SITE_ORIGIN || ""}/website/edit.html`;
  return new Response(null, {
    status: 302,
    headers: {
      location: `${editorUrl}#session=${encodeURIComponent(session)}`,
      "set-cookie":
        "editorial_oauth_state=; Path=/auth; HttpOnly; Secure; SameSite=Lax; Max-Age=0",
    },
  });
}

async function devLogin(request, env) {
  if (String(env.DEV_MODE).toLowerCase() !== "true")
    throw httpError(404, "Not found");
  const url = new URL(request.url);
  const login = (url.searchParams.get("login") || "smiles0527").trim();
  if (!/^[A-Za-z0-9-]{1,39}$/.test(login))
    throw httpError(400, "Invalid login");
  const user = await upsertUser(env, {
    githubId: null,
    login,
    displayName: login,
    avatarUrl: "",
  });
  const session = await createSession(env, user.id);
  const redirect = url.searchParams.get("redirect");
  if (redirect) {
    const target = new URL(
      redirect,
      env.SITE_ORIGIN || "http://127.0.0.1:8766",
    );
    target.hash = `session=${encodeURIComponent(session)}`;
    return Response.redirect(target.toString(), 302);
  }
  return json({ session, user });
}

function parseCookies(value = "") {
  return Object.fromEntries(
    value
      .split(";")
      .map((part) => part.trim().split("="))
      .filter(([name]) => name)
      .map(([name, ...rest]) => [name, decodeURIComponent(rest.join("="))]),
  );
}

async function upsertUser(env, profile) {
  const desiredRole = ownerLogins(env).has(profile.login.toLowerCase())
    ? "owner"
    : "contributor";
  await env.DB.prepare(
    `INSERT INTO users (github_id, login, display_name, avatar_url, role)
     VALUES (?, ?, ?, ?, ?)
     ON CONFLICT(login) DO UPDATE SET
       github_id = COALESCE(excluded.github_id, users.github_id),
       display_name = excluded.display_name,
       avatar_url = excluded.avatar_url,
       role = CASE WHEN excluded.role = 'owner' THEN 'owner' ELSE users.role END,
       updated_at = CURRENT_TIMESTAMP`,
  )
    .bind(
      profile.githubId,
      profile.login,
      profile.displayName,
      profile.avatarUrl,
      desiredRole,
    )
    .run();
  return env.DB.prepare(
    "SELECT id, login, display_name, avatar_url, role, active FROM users WHERE login = ? COLLATE NOCASE",
  )
    .bind(profile.login)
    .first();
}

async function createSession(env, userId) {
  const id = randomToken();
  const expires = new Date(Date.now() + 30 * 24 * 60 * 60 * 1000).toISOString();
  await env.DB.prepare(
    "INSERT INTO sessions (id, user_id, expires_at) VALUES (?, ?, ?)",
  )
    .bind(id, userId, expires)
    .run();
  return id;
}

async function optionalUser(request, env) {
  const header = request.headers.get("authorization") || "";
  const token = header.startsWith("Bearer ") ? header.slice(7).trim() : "";
  if (!token) return null;
  const user = await env.DB.prepare(
    `SELECT u.id, u.login, u.display_name, u.avatar_url, u.role, u.active
     FROM sessions s JOIN users u ON u.id = s.user_id
     WHERE s.id = ? AND s.expires_at > CURRENT_TIMESTAMP`,
  )
    .bind(token)
    .first();
  if (!user?.active) return null;
  await env.DB.prepare(
    `UPDATE users
     SET last_seen_at = CURRENT_TIMESTAMP
     WHERE id = ?
       AND (last_seen_at IS NULL OR last_seen_at < datetime('now', '-5 minutes'))`,
  )
    .bind(user.id)
    .run();
  return user;
}

async function requireUser(request, env) {
  const user = await optionalUser(request, env);
  if (!user) throw httpError(401, "Sign in is required");
  return user;
}

async function requireStaff(request, env) {
  const user = await requireUser(request, env);
  if (!isStaff(user)) throw httpError(403, "Editor access is required");
  return user;
}

async function requireOwner(request, env) {
  const user = await requireUser(request, env);
  if (user.role !== "owner") throw httpError(403, "Owner access is required");
  return user;
}

async function getCatalog(env) {
  const { results } = await env.DB.prepare(
    `SELECT c.id collection, c.label collection_label,
            s.slug section, s.label section_label, s.sort_order section_order,
            p.id problem_id, p.slug, p.title, p.source_url, p.sort_order problem_order,
            e.id editorial_id, e.published_at,
            u.login author_login, COALESCE(u.display_name, u.login) author_name
     FROM editorials e
     JOIN revisions r ON r.id = e.published_revision_id
     JOIN problems p ON p.id = e.problem_id
     JOIN sections s ON s.id = p.section_id
     JOIN collections c ON c.id = s.collection_id
     JOIN users u ON u.id = e.created_by
     WHERE e.published_revision_id IS NOT NULL AND e.status <> 'archived'
       AND c.active = 1 AND s.active = 1 AND p.active = 1
     ORDER BY c.sort_order, s.sort_order, p.sort_order, p.id, e.id`,
  ).all();
  return json({ items: results });
}

async function getProblems(url, env) {
  const collection = url.searchParams.get("collection");
  const section = url.searchParams.get("section");
  const where = [];
  const values = [];
  if (collection) {
    where.push("c.id = ?");
    values.push(collection.toLowerCase());
  }
  if (section) {
    where.push("s.slug = ? COLLATE NOCASE");
    values.push(section);
  }
  const { results } = await env.DB.prepare(
    `SELECT p.id, p.slug, p.title, p.source_url, p.sort_order,
            c.id collection, c.label collection_label,
            s.slug section, s.label section_label,
            SUM(CASE WHEN e.published_revision_id IS NOT NULL AND e.status <> 'archived' THEN 1 ELSE 0 END) published_count
     FROM problems p
     JOIN sections s ON s.id = p.section_id
     JOIN collections c ON c.id = s.collection_id
     LEFT JOIN editorials e ON e.problem_id = p.id
     WHERE c.active = 1 AND s.active = 1 AND p.active = 1
       ${where.length ? `AND ${where.join(" AND ")}` : ""}
     GROUP BY p.id
     ORDER BY c.sort_order, s.sort_order, p.sort_order, p.id`,
  )
    .bind(...values)
    .all();
  return json({ items: results });
}

async function getPublishedEditorials(url, env) {
  const collection = (url.searchParams.get("collection") || "").toLowerCase();
  const section = url.searchParams.get("section") || "";
  const slug = url.searchParams.get("slug") || "";
  if (!collection || !section || !slug)
    throw httpError(400, "collection, section, and slug are required");

  const { results } = await env.DB.prepare(
    `SELECT e.id, e.published_at, r.id revision_id, r.markdown, r.solution_cpp, r.summary,
            p.id problem_id, p.slug, p.title, p.source_url,
            c.id collection, s.slug section,
            u.login author_login, COALESCE(u.display_name, u.login) author_name, u.avatar_url
     FROM editorials e
     JOIN revisions r ON r.id = e.published_revision_id
     JOIN problems p ON p.id = e.problem_id
     JOIN sections s ON s.id = p.section_id
     JOIN collections c ON c.id = s.collection_id
     JOIN users u ON u.id = e.created_by
     WHERE e.published_revision_id IS NOT NULL AND e.status <> 'archived'
       AND c.active = 1 AND s.active = 1 AND p.active = 1
       AND c.id = ? AND s.slug = ? COLLATE NOCASE AND p.slug = ? COLLATE NOCASE
     ORDER BY e.published_at, e.id`,
  )
    .bind(collection, section, slug)
    .all();
  if (!results.length) throw httpError(404, "No published editorial was found");
  return json({
    problem: pickProblem(results[0]),
    editorials: results.map(stripProblemFields),
  });
}

function pickProblem(row) {
  return {
    id: row.problem_id,
    slug: row.slug,
    title: row.title,
    source_url: row.source_url,
    collection: row.collection,
    section: row.section,
  };
}

function stripProblemFields(row) {
  return {
    id: row.id,
    revision_id: row.revision_id,
    published_at: row.published_at,
    markdown: row.markdown,
    solution_cpp: row.solution_cpp,
    summary: row.summary,
    author: {
      login: row.author_login,
      name: row.author_name,
      avatar_url: row.avatar_url,
    },
  };
}

function catalogKey(value, field) {
  const key = String(value || "")
    .trim()
    .toLowerCase();
  if (!/^[a-z0-9][a-z0-9_-]{0,79}$/.test(key)) {
    throw httpError(
      400,
      `${field} must use lowercase letters, numbers, underscores, or hyphens`,
    );
  }
  return key;
}

function catalogLabel(value, field) {
  const label = String(value || "").trim();
  if (!label) throw httpError(400, `${field} is required`);
  if (label.length > 160)
    throw httpError(400, `${field} must be 160 characters or fewer`);
  return label;
}

function catalogActive(value) {
  if (value !== true && value !== false && value !== 1 && value !== 0)
    throw httpError(400, "active must be true or false");
  return value === true || value === 1 ? 1 : 0;
}

async function catalogWrite(operation, conflictMessage) {
  try {
    return await operation();
  } catch (error) {
    if (String(error.message || error).includes("UNIQUE constraint failed")) {
      throw httpError(409, conflictMessage);
    }
    if (String(error.message || error).includes("FOREIGN KEY constraint failed")) {
      throw httpError(400, "The selected parent does not exist");
    }
    throw error;
  }
}

async function getStructure(request, env) {
  await requireStaff(request, env);
  const [collections, sections, problems] = await env.DB.batch([
    env.DB.prepare(
      "SELECT id, label, sort_order, active FROM collections ORDER BY sort_order, id",
    ),
    env.DB.prepare(
      `SELECT id, collection_id, slug, label, sort_order, active
       FROM sections ORDER BY collection_id, sort_order, id`,
    ),
    env.DB.prepare(
      `SELECT id, section_id, slug, title, source_url, sort_order, active
       FROM problems ORDER BY section_id, sort_order, id`,
    ),
  ]);
  return json({
    collections: collections.results,
    sections: sections.results,
    problems: problems.results,
  });
}

async function createCollection(request, env) {
  await requireStaff(request, env);
  const payload = await bodyJson(request);
  const id = catalogKey(payload.id, "Collection key");
  const label = catalogLabel(payload.label, "Collection name");
  const row = await env.DB.prepare(
    "SELECT COALESCE(MAX(sort_order), -1) + 1 next_order FROM collections",
  ).first();
  await catalogWrite(
    () =>
      env.DB.prepare(
        "INSERT INTO collections (id, label, sort_order) VALUES (?, ?, ?)",
      )
        .bind(id, label, row.next_order)
        .run(),
    "A collection with that key already exists",
  );
  return json(
    {
      collection: await env.DB.prepare(
        "SELECT id, label, sort_order, active FROM collections WHERE id = ?",
      )
        .bind(id)
        .first(),
    },
    201,
  );
}

async function updateCollection(request, env, id) {
  await requireStaff(request, env);
  const payload = await bodyJson(request);
  const updates = [];
  const values = [];
  if (Object.hasOwn(payload, "label")) {
    updates.push("label = ?");
    values.push(catalogLabel(payload.label, "Collection name"));
  }
  if (Object.hasOwn(payload, "active")) {
    updates.push("active = ?");
    values.push(catalogActive(payload.active));
  }
  if (!updates.length) throw httpError(400, "No editable fields were provided");
  const result = await env.DB.prepare(
    `UPDATE collections SET ${updates.join(", ")} WHERE id = ?`,
  )
    .bind(...values, id)
    .run();
  if (!result.meta.changes) throw httpError(404, "Collection not found");
  return json({ ok: true });
}

async function createSection(request, env) {
  await requireStaff(request, env);
  const payload = await bodyJson(request);
  const collectionId = catalogKey(payload.collection_id, "Collection key");
  const slug = catalogKey(payload.slug, "Section key");
  const label = catalogLabel(payload.label, "Section name");
  const parent = await env.DB.prepare(
    "SELECT id FROM collections WHERE id = ?",
  )
    .bind(collectionId)
    .first();
  if (!parent) throw httpError(404, "Collection not found");
  const row = await env.DB.prepare(
    "SELECT COALESCE(MAX(sort_order), -1) + 1 next_order FROM sections WHERE collection_id = ?",
  )
    .bind(collectionId)
    .first();
  const result = await catalogWrite(
    () =>
      env.DB.prepare(
        "INSERT INTO sections (collection_id, slug, label, sort_order) VALUES (?, ?, ?, ?)",
      )
        .bind(collectionId, slug, label, row.next_order)
        .run(),
    "That section key already exists in this collection",
  );
  return json({ id: result.meta.last_row_id }, 201);
}

async function updateSection(request, env, id) {
  await requireStaff(request, env);
  const payload = await bodyJson(request);
  const updates = [];
  const values = [];
  if (Object.hasOwn(payload, "collection_id")) {
    updates.push("collection_id = ?");
    values.push(catalogKey(payload.collection_id, "Collection key"));
  }
  if (Object.hasOwn(payload, "slug")) {
    updates.push("slug = ?");
    values.push(catalogKey(payload.slug, "Section key"));
  }
  if (Object.hasOwn(payload, "label")) {
    updates.push("label = ?");
    values.push(catalogLabel(payload.label, "Section name"));
  }
  if (Object.hasOwn(payload, "active")) {
    updates.push("active = ?");
    values.push(catalogActive(payload.active));
  }
  if (!updates.length) throw httpError(400, "No editable fields were provided");
  const result = await catalogWrite(
    () =>
      env.DB.prepare(
        `UPDATE sections SET ${updates.join(", ")} WHERE id = ?`,
      )
        .bind(...values, id)
        .run(),
    "That section key already exists in the selected collection",
  );
  if (!result.meta.changes) throw httpError(404, "Section not found");
  return json({ ok: true });
}

async function createProblem(request, env) {
  await requireStaff(request, env);
  const payload = await bodyJson(request);
  const sectionId = Number(payload.section_id);
  if (!Number.isInteger(sectionId))
    throw httpError(400, "A valid section_id is required");
  const slug = catalogKey(payload.slug, "Problem key");
  const title = catalogLabel(payload.title, "Problem title");
  const sourceUrl = String(payload.source_url || "").trim().slice(0, 2_000);
  const parent = await env.DB.prepare("SELECT id FROM sections WHERE id = ?")
    .bind(sectionId)
    .first();
  if (!parent) throw httpError(404, "Section not found");
  const row = await env.DB.prepare(
    "SELECT COALESCE(MAX(sort_order), -1) + 1 next_order FROM problems WHERE section_id = ?",
  )
    .bind(sectionId)
    .first();
  const result = await catalogWrite(
    () =>
      env.DB.prepare(
        "INSERT INTO problems (section_id, slug, title, source_url, sort_order) VALUES (?, ?, ?, ?, ?)",
      )
        .bind(sectionId, slug, title, sourceUrl || null, row.next_order)
        .run(),
    "That problem key already exists in this section",
  );
  return json({ id: result.meta.last_row_id }, 201);
}

async function updateProblem(request, env, id) {
  await requireStaff(request, env);
  const payload = await bodyJson(request);
  const updates = [];
  const values = [];
  if (Object.hasOwn(payload, "section_id")) {
    const sectionId = Number(payload.section_id);
    if (!Number.isInteger(sectionId))
      throw httpError(400, "A valid section_id is required");
    updates.push("section_id = ?");
    values.push(sectionId);
  }
  if (Object.hasOwn(payload, "slug")) {
    updates.push("slug = ?");
    values.push(catalogKey(payload.slug, "Problem key"));
  }
  if (Object.hasOwn(payload, "title")) {
    updates.push("title = ?");
    values.push(catalogLabel(payload.title, "Problem title"));
  }
  if (Object.hasOwn(payload, "source_url")) {
    updates.push("source_url = ?");
    values.push(String(payload.source_url || "").trim().slice(0, 2_000) || null);
  }
  if (Object.hasOwn(payload, "active")) {
    updates.push("active = ?");
    values.push(catalogActive(payload.active));
  }
  if (!updates.length) throw httpError(400, "No editable fields were provided");
  const result = await catalogWrite(
    () =>
      env.DB.prepare(
        `UPDATE problems SET ${updates.join(", ")}, updated_at = CURRENT_TIMESTAMP WHERE id = ?`,
      )
        .bind(...values, id)
        .run(),
    "That problem key already exists in the selected section",
  );
  if (!result.meta.changes) throw httpError(404, "Problem not found");
  return json({ ok: true });
}

async function reorderStructure(request, env) {
  await requireStaff(request, env);
  const payload = await bodyJson(request);
  const entity = String(payload.entity || "");
  const ids = Array.isArray(payload.ids) ? payload.ids : [];
  if (!["collections", "sections", "problems"].includes(entity))
    throw httpError(400, "Invalid structure entity");
  if (!ids.length || new Set(ids.map(String)).size !== ids.length)
    throw httpError(400, "ids must contain each item exactly once");

  let rows;
  let statements;
  if (entity === "collections") {
    rows = (
      await env.DB.prepare("SELECT id FROM collections ORDER BY sort_order, id").all()
    ).results;
    statements = ids.map((id, index) =>
      env.DB.prepare("UPDATE collections SET sort_order = ? WHERE id = ?").bind(
        index,
        String(id),
      ),
    );
  } else if (entity === "sections") {
    const collectionId = catalogKey(payload.parent_id, "Collection key");
    rows = (
      await env.DB.prepare(
        "SELECT id FROM sections WHERE collection_id = ? ORDER BY sort_order, id",
      )
        .bind(collectionId)
        .all()
    ).results;
    statements = ids.map((id, index) =>
      env.DB.prepare(
        "UPDATE sections SET sort_order = ? WHERE id = ? AND collection_id = ?",
      ).bind(index, Number(id), collectionId),
    );
  } else {
    const sectionId = Number(payload.parent_id);
    if (!Number.isInteger(sectionId))
      throw httpError(400, "A valid parent section is required");
    rows = (
      await env.DB.prepare(
        "SELECT id FROM problems WHERE section_id = ? ORDER BY sort_order, id",
      )
        .bind(sectionId)
        .all()
    ).results;
    statements = ids.map((id, index) =>
      env.DB.prepare(
        "UPDATE problems SET sort_order = ? WHERE id = ? AND section_id = ?",
      ).bind(index, Number(id), sectionId),
    );
  }

  const expected = new Set(rows.map((row) => String(row.id)));
  if (
    ids.length !== expected.size ||
    ids.some((id) => !expected.has(String(id)))
  ) {
    throw httpError(409, "The catalog changed; refresh before reordering");
  }
  await env.DB.batch(statements);
  return json({ ok: true });
}

async function getDashboard(request, env) {
  const user = await requireUser(request, env);
  const staff = isStaff(user);
  const statement = env.DB.prepare(
    `SELECT e.id, e.created_by, e.status, e.created_at, e.updated_at, e.submitted_at, e.published_at,
            p.id problem_id, p.slug, p.title problem_title,
            COALESCE(NULLIF(e.title, ''), p.title) title,
            c.id collection, c.label collection_label,
            s.slug section, s.label section_label,
            u.login author_login, COALESCE(u.display_name, u.login) author_name,
            e.current_revision_id, e.published_revision_id
     FROM editorials e
     JOIN problems p ON p.id = e.problem_id
     JOIN sections s ON s.id = p.section_id
     JOIN collections c ON c.id = s.collection_id
     JOIN users u ON u.id = e.created_by
     ${staff ? "" : "WHERE e.created_by = ?"}
     ORDER BY CASE e.status WHEN 'submitted' THEN 0 WHEN 'changes_requested' THEN 1 WHEN 'draft' THEN 2 WHEN 'published' THEN 3 ELSE 4 END,
              e.updated_at DESC`,
  );
  const { results } = staff
    ? await statement.all()
    : await statement.bind(user.id).all();
  return json({
    user,
    items: results,
    reviewQueue: staff
      ? results.filter((item) => item.status === "submitted")
      : [],
  });
}

async function getEditorial(request, env, id) {
  const user = await requireUser(request, env);
  const editorial = await editorialRow(env, id);
  if (!editorial) throw httpError(404, "Editorial not found");
  if (
    !isStaff(user) &&
    editorial.created_by !== user.id &&
    editorial.status !== "published"
  ) {
    throw httpError(403, "You cannot access this editorial");
  }

  const [{ results: revisions }, { results: reviews }, { results: authors }] =
    await Promise.all([
      env.DB.prepare(
        `SELECT r.id, r.summary, r.created_at, r.author_id,
              u.login author_login, COALESCE(u.display_name, u.login) author_name,
              CASE WHEN r.id = ? THEN r.markdown ELSE NULL END markdown,
              CASE WHEN r.id = ? THEN r.solution_cpp ELSE NULL END solution_cpp
       FROM revisions r JOIN users u ON u.id = r.author_id
       WHERE r.editorial_id = ? ORDER BY r.id DESC`,
      )
        .bind(editorial.current_revision_id, editorial.current_revision_id, id)
        .all(),
      env.DB.prepare(
        `SELECT rv.id, rv.revision_id, rv.decision, rv.comment, rv.created_at,
              u.login reviewer_login, COALESCE(u.display_name, u.login) reviewer_name
       FROM reviews rv JOIN users u ON u.id = rv.reviewer_id
       WHERE rv.editorial_id = ? ORDER BY rv.id DESC`,
      )
        .bind(id)
        .all(),
      env.DB.prepare(
        `SELECT u.id, u.login, COALESCE(u.display_name, u.login) name, u.avatar_url
       FROM editorial_authors ea JOIN users u ON u.id = ea.user_id
       WHERE ea.editorial_id = ? ORDER BY ea.position, u.id`,
      )
        .bind(id)
        .all(),
    ]);
  return json({ editorial, revisions, reviews, authors });
}

async function editorialRow(env, id) {
  return env.DB.prepare(
    `SELECT e.*, p.slug, p.title problem_title,
            COALESCE(NULLIF(e.title, ''), p.title) title,
            p.source_url, p.id problem_id,
            s.slug section, s.label section_label,
            c.id collection, c.label collection_label,
            u.login author_login, COALESCE(u.display_name, u.login) author_name
     FROM editorials e
     JOIN problems p ON p.id = e.problem_id
     JOIN sections s ON s.id = p.section_id
     JOIN collections c ON c.id = s.collection_id
     JOIN users u ON u.id = e.created_by
     WHERE e.id = ?`,
  )
    .bind(id)
    .first();
}

function validateContent(payload) {
  const markdown = String(payload.markdown ?? "");
  const solution = String(payload.solution_cpp ?? "");
  const summary = String(payload.summary ?? "").slice(0, 500);
  if (!markdown.trim()) throw httpError(400, "Editorial Markdown is required");
  if (markdown.length > 500_000 || solution.length > 500_000)
    throw httpError(413, "Editorial content is too large");
  return { markdown, solution, summary };
}

async function createEditorial(request, env) {
  const user = await requireUser(request, env);
  const payload = await bodyJson(request);
  const directPublish = user.role === "owner" && payload.publish === true;
  const problemId = Number(payload.problem_id);
  if (!Number.isInteger(problemId))
    throw httpError(400, "A valid problem_id is required");
  const problem = await env.DB.prepare("SELECT id FROM problems WHERE id = ?")
    .bind(problemId)
    .first();
  if (!problem) throw httpError(404, "Problem not found");
  const content = validateContent(payload);

  const result = await env.DB.prepare(
    "INSERT INTO editorials (problem_id, created_by) VALUES (?, ?)",
  )
    .bind(problemId, user.id)
    .run();
  const editorialId = result.meta.last_row_id;
  const revisionResult = await env.DB.prepare(
    "INSERT INTO revisions (editorial_id, author_id, markdown, solution_cpp, summary) VALUES (?, ?, ?, ?, ?)",
  )
    .bind(
      editorialId,
      user.id,
      content.markdown,
      content.solution,
      content.summary,
    )
    .run();
  const revisionId = revisionResult.meta.last_row_id;
  await env.DB.batch([
    directPublish
      ? env.DB.prepare(
          `UPDATE editorials
           SET current_revision_id = ?, published_revision_id = ?,
               status = 'published', published_at = CURRENT_TIMESTAMP,
               updated_at = CURRENT_TIMESTAMP
           WHERE id = ?`,
        ).bind(revisionId, revisionId, editorialId)
      : env.DB.prepare(
          "UPDATE editorials SET current_revision_id = ? WHERE id = ?",
        ).bind(revisionId, editorialId),
    env.DB.prepare(
      "INSERT INTO editorial_authors (editorial_id, user_id) VALUES (?, ?)",
    ).bind(editorialId, user.id),
  ]);
  return json({ editorial: await editorialRow(env, editorialId) }, 201);
}

async function assertCanEdit(request, env, id) {
  const user = await requireUser(request, env);
  const editorial = await editorialRow(env, id);
  if (!editorial) throw httpError(404, "Editorial not found");
  if (!isStaff(user) && editorial.created_by !== user.id)
    throw httpError(403, "You cannot edit this editorial");
  if (editorial.status === "archived" && user.role !== "owner")
    throw httpError(409, "Archived editorials cannot be edited");
  return { user, editorial };
}

async function updateEditorial(request, env, id) {
  const { user, editorial } = await assertCanEdit(request, env, id);
  const content = validateContent(await bodyJson(request));
  const revisionResult = await env.DB.prepare(
    "INSERT INTO revisions (editorial_id, author_id, markdown, solution_cpp, summary) VALUES (?, ?, ?, ?, ?)",
  )
    .bind(id, user.id, content.markdown, content.solution, content.summary)
    .run();
  const revisionId = revisionResult.meta.last_row_id;
  if (user.role === "owner") {
    await env.DB.prepare(
      `UPDATE editorials
       SET current_revision_id = ?, published_revision_id = ?,
           status = 'published',
           published_at = COALESCE(published_at, CURRENT_TIMESTAMP),
           updated_at = CURRENT_TIMESTAMP
       WHERE id = ?`,
    )
      .bind(revisionId, revisionId, id)
      .run();
    return json({
      editorial: await editorialRow(env, id),
      revision_id: revisionId,
    });
  }
  const status =
    ["published", "submitted", "changes_requested"].includes(editorial.status)
      ? "draft"
      : editorial.status;
  await env.DB.prepare(
    "UPDATE editorials SET current_revision_id = ?, status = ?, updated_at = CURRENT_TIMESTAMP WHERE id = ?",
  )
    .bind(revisionId, status, id)
    .run();
  return json({
    editorial: await editorialRow(env, id),
    revision_id: revisionId,
  });
}

function cleanEditorialTitle(value) {
  const title = String(value ?? "").trim();
  if (!title) throw httpError(400, "Editorial name is required");
  if (title.length > 160)
    throw httpError(400, "Editorial name must be 160 characters or fewer");
  return title;
}

async function updateEditorialMetadata(request, env, id) {
  const { user, editorial } = await assertCanEdit(request, env, id);
  const payload = await bodyJson(request);
  const updates = [];
  const values = [];

  if (Object.hasOwn(payload, "title")) {
    updates.push("title = ?");
    values.push(cleanEditorialTitle(payload.title));
  }

  if (Object.hasOwn(payload, "problem_id")) {
    const problemId = Number(payload.problem_id);
    if (!Number.isInteger(problemId))
      throw httpError(400, "A valid problem_id is required");
    if (
      !isStaff(user) &&
      !["draft", "changes_requested"].includes(editorial.status)
    ) {
      throw httpError(
        409,
        "Withdraw this editorial before moving it to another problem",
      );
    }
    const problem = await env.DB.prepare("SELECT id FROM problems WHERE id = ?")
      .bind(problemId)
      .first();
    if (!problem) throw httpError(404, "Problem not found");
    updates.push("problem_id = ?");
    values.push(problemId);
  }

  if (!updates.length) throw httpError(400, "No editable fields were provided");
  updates.push("updated_at = CURRENT_TIMESTAMP");
  await env.DB.prepare(
    `UPDATE editorials SET ${updates.join(", ")} WHERE id = ?`,
  )
    .bind(...values, id)
    .run();
  return json({ editorial: await editorialRow(env, id) });
}

async function duplicateEditorial(request, env, id) {
  const user = await requireUser(request, env);
  const source = await editorialRow(env, id);
  if (!source) throw httpError(404, "Editorial not found");
  if (
    !isStaff(user) &&
    source.created_by !== user.id &&
    source.status !== "published"
  ) {
    throw httpError(403, "You cannot duplicate this editorial");
  }
  const revision = await env.DB.prepare(
    "SELECT markdown, solution_cpp FROM revisions WHERE id = ?",
  )
    .bind(source.current_revision_id || source.published_revision_id)
    .first();
  if (!revision) throw httpError(409, "Editorial has no revision to duplicate");

  const title = `${source.title} (copy)`.slice(0, 160);
  const editorialResult = await env.DB.prepare(
    "INSERT INTO editorials (problem_id, created_by, title) VALUES (?, ?, ?)",
  )
    .bind(source.problem_id, user.id, title)
    .run();
  const editorialId = editorialResult.meta.last_row_id;
  const revisionResult = await env.DB.prepare(
    "INSERT INTO revisions (editorial_id, author_id, markdown, solution_cpp, summary) VALUES (?, ?, ?, ?, ?)",
  )
    .bind(
      editorialId,
      user.id,
      revision.markdown,
      revision.solution_cpp,
      `Duplicated from editorial ${id}`,
    )
    .run();
  await env.DB.batch([
    env.DB.prepare(
      "UPDATE editorials SET current_revision_id = ? WHERE id = ?",
    ).bind(revisionResult.meta.last_row_id, editorialId),
    env.DB.prepare(
      "INSERT INTO editorial_authors (editorial_id, user_id) VALUES (?, ?)",
    ).bind(editorialId, user.id),
  ]);
  return json({ editorial: await editorialRow(env, editorialId) }, 201);
}

async function submitEditorial(request, env, id) {
  const { editorial } = await assertCanEdit(request, env, id);
  if (!editorial.current_revision_id)
    throw httpError(409, "Save a revision before submitting");
  if (!["draft", "changes_requested"].includes(editorial.status)) {
    throw httpError(409, "Only drafts or requested changes can be submitted");
  }
  await env.DB.prepare(
    "UPDATE editorials SET status = 'submitted', submitted_at = CURRENT_TIMESTAMP, updated_at = CURRENT_TIMESTAMP WHERE id = ?",
  )
    .bind(id)
    .run();
  return json({ editorial: await editorialRow(env, id) });
}

async function withdrawEditorial(request, env, id) {
  const { editorial } = await assertCanEdit(request, env, id);
  if (editorial.status !== "submitted")
    throw httpError(409, "Only submitted editorials can be withdrawn");
  await env.DB.prepare(
    "UPDATE editorials SET status = 'draft', submitted_at = NULL, updated_at = CURRENT_TIMESTAMP WHERE id = ?",
  )
    .bind(id)
    .run();
  return json({ editorial: await editorialRow(env, id) });
}

async function reviewEditorial(request, env, id) {
  const reviewer = await requireStaff(request, env);
  const editorial = await editorialRow(env, id);
  if (!editorial) throw httpError(404, "Editorial not found");
  if (!editorial.current_revision_id)
    throw httpError(409, "Editorial has no revision");
  const payload = await bodyJson(request);
  const decision = String(payload.decision || "");
  const comment = String(payload.comment || "").slice(0, 10_000);
  if (!["comment", "approve", "request_changes"].includes(decision)) {
    throw httpError(400, "Invalid review decision");
  }
  await env.DB.prepare(
    "INSERT INTO reviews (editorial_id, revision_id, reviewer_id, decision, comment) VALUES (?, ?, ?, ?, ?)",
  )
    .bind(id, editorial.current_revision_id, reviewer.id, decision, comment)
    .run();
  if (decision === "request_changes") {
    await env.DB.prepare(
      "UPDATE editorials SET status = 'changes_requested', updated_at = CURRENT_TIMESTAMP WHERE id = ?",
    )
      .bind(id)
      .run();
  }
  return json({ editorial: await editorialRow(env, id) });
}

async function publishEditorial(request, env, id) {
  await requireStaff(request, env);
  const editorial = await editorialRow(env, id);
  if (!editorial) throw httpError(404, "Editorial not found");
  if (!editorial.current_revision_id)
    throw httpError(409, "Editorial has no revision");
  await env.DB.prepare(
    `UPDATE editorials
     SET status = 'published', published_revision_id = current_revision_id,
         published_at = CURRENT_TIMESTAMP, updated_at = CURRENT_TIMESTAMP
     WHERE id = ?`,
  )
    .bind(id)
    .run();
  return json({ editorial: await editorialRow(env, id) });
}

async function archiveEditorial(request, env, id) {
  await requireStaff(request, env);
  const editorial = await editorialRow(env, id);
  if (!editorial) throw httpError(404, "Editorial not found");
  await env.DB.prepare(
    "UPDATE editorials SET status = 'archived', updated_at = CURRENT_TIMESTAMP WHERE id = ?",
  )
    .bind(id)
    .run();
  return json({ editorial: await editorialRow(env, id) });
}

async function restoreEditorial(request, env, id) {
  await requireStaff(request, env);
  const editorial = await editorialRow(env, id);
  if (!editorial) throw httpError(404, "Editorial not found");
  if (editorial.status !== "archived")
    throw httpError(409, "Only archived editorials can be restored");
  const status =
    editorial.published_revision_id &&
    editorial.current_revision_id === editorial.published_revision_id
      ? "published"
      : "draft";
  await env.DB.prepare(
    "UPDATE editorials SET status = ?, updated_at = CURRENT_TIMESTAMP WHERE id = ?",
  )
    .bind(status, id)
    .run();
  return json({ editorial: await editorialRow(env, id) });
}

async function deleteEditorial(request, env, id) {
  const user = await requireUser(request, env);
  const editorial = await editorialRow(env, id);
  if (!editorial) throw httpError(404, "Editorial not found");
  const ownsEditorial = editorial.created_by === user.id;
  if (!isStaff(user) && !ownsEditorial)
    throw httpError(403, "You cannot delete this editorial");
  if (editorial.published_revision_id && user.role !== "owner") {
    throw httpError(
      409,
      "Only the owner can permanently delete an editorial that has been published",
    );
  }
  if (
    !editorial.published_revision_id &&
    !ownsEditorial &&
    !isStaff(user)
  ) {
    throw httpError(403, "You cannot delete this editorial");
  }
  await env.DB.prepare("DELETE FROM editorials WHERE id = ?").bind(id).run();
  return json({ ok: true, id });
}

async function listUsers(request, env) {
  await requireOwner(request, env);
  const { results } = await env.DB.prepare(
    "SELECT id, login, display_name, avatar_url, role, active, created_at, updated_at, last_seen_at FROM users ORDER BY login COLLATE NOCASE",
  ).all();
  return json({ users: results });
}

async function updateUserRole(request, env, id) {
  const owner = await requireOwner(request, env);
  const payload = await bodyJson(request);
  const role = String(payload.role || "");
  if (!["owner", "editor", "contributor"].includes(role))
    throw httpError(400, "Invalid role");
  if (id === owner.id && role !== "owner")
    throw httpError(409, "You cannot remove your own owner role");
  const result = await env.DB.prepare(
    "UPDATE users SET role = ?, updated_at = CURRENT_TIMESTAMP WHERE id = ?",
  )
    .bind(role, id)
    .run();
  if (!result.meta.changes) throw httpError(404, "User not found");
  return json({ ok: true });
}

async function exportDatabase(request, env) {
  await requireOwner(request, env);
  const [
    collections,
    sections,
    problems,
    users,
    editorials,
    revisions,
    authors,
    reviews,
  ] = await Promise.all(
    [
      "collections",
      "sections",
      "problems",
      "users",
      "editorials",
      "revisions",
      "editorial_authors",
      "reviews",
    ].map(
      async (table) =>
        (await env.DB.prepare(`SELECT * FROM ${table}`).all()).results,
    ),
  );
  return json({
    exported_at: new Date().toISOString(),
    collections,
    sections,
    problems,
    users,
    editorials,
    revisions,
    editorial_authors: authors,
    reviews,
  });
}
