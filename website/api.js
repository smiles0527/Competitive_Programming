(function () {
  const config = window.EDITORIAL_SITE_CONFIG || {};
  const local = ["127.0.0.1", "localhost"].includes(location.hostname);
  const selectedBase = local
    ? config.editor?.localApiBase
    : config.editor?.apiBase;
  const base = String(selectedBase || "").replace(/\/$/, "");
  const sessionKey = "editorial-cms-session";

  function captureSession() {
    const hash = new URLSearchParams(location.hash.slice(1));
    const session = hash.get("session");
    if (!session) return;
    sessionStorage.setItem(sessionKey, session);
    history.replaceState(null, "", `${location.pathname}${location.search}`);
  }

  async function request(path, options = {}) {
    if (!base) throw new Error("The editorial API has not been configured.");
    const headers = new Headers(options.headers || {});
    const session = sessionStorage.getItem(sessionKey);
    if (session) headers.set("authorization", `Bearer ${session}`);
    if (options.body && !headers.has("content-type"))
      headers.set("content-type", "application/json");
    const response = await fetch(`${base}${path}`, {
      ...options,
      headers,
      cache: "no-store",
    });
    const body = await response.json().catch(() => ({}));
    if (!response.ok) {
      const error = new Error(
        body.error || `Request failed (${response.status})`,
      );
      error.status = response.status;
      throw error;
    }
    return body;
  }

  function login(returnTo = location.href) {
    const target = local
      ? `${base}/auth/dev?redirect=${encodeURIComponent(returnTo)}`
      : `${base}/auth/start`;
    location.href = target;
  }

  function logout() {
    sessionStorage.removeItem(sessionKey);
    location.reload();
  }

  captureSession();
  window.EditorialApi = {
    base,
    local,
    request,
    login,
    logout,
    hasSession: () => Boolean(sessionStorage.getItem(sessionKey)),
  };
})();
