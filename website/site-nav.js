(function () {
  const header = document.querySelector("[data-site-nav]");
  if (!header || !window.EditorialApi) return;

  const active = header.dataset.active;
  for (const link of header.querySelectorAll("[data-nav]")) {
    const selected = link.dataset.nav === active;
    link.classList.toggle("active", selected);
    if (selected) link.setAttribute("aria-current", "page");
  }

  const signIn = header.querySelector("[data-sign-in]");
  const signOut = header.querySelector("[data-sign-out]");
  const identity = header.querySelector("[data-identity]");
  const review = header.querySelector("[data-review-link]");

  function signedOut() {
    if (signIn) signIn.hidden = false;
    if (signOut) signOut.hidden = true;
    if (identity) identity.hidden = true;
    if (review) review.hidden = true;
  }

  function signedIn(user) {
    if (signIn) signIn.hidden = true;
    if (signOut) signOut.hidden = false;
    if (identity) {
      identity.hidden = false;
      identity.textContent = `${user.display_name || user.login} · ${user.role}`;
    }
    if (review)
      review.hidden = !["owner", "editor"].includes(user.role);
  }

  signIn?.addEventListener("click", () =>
    EditorialApi.login(location.href),
  );
  signOut?.addEventListener("click", EditorialApi.logout);

  if (!EditorialApi.hasSession()) {
    signedOut();
    return;
  }

  EditorialApi.request("/api/me")
    .then(({ user }) => signedIn(user))
    .catch(signedOut);
})();
