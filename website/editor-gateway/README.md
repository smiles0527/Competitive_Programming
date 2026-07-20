# Editorial editor gateway setup

The public site remains on GitHub Pages. This Worker performs GitHub sign-in and accepts authenticated editorial updates from the hidden editor.

## 1. Register a GitHub App

Create a GitHub App owned by `smiles0527` with these settings:

- Homepage URL: `https://smiles0527.github.io/Competitive_Programming/`
- Callback URL: `https://YOUR-WORKER.workers.dev/auth/callback`
- Repository permission, Contents: Read and write
- Installation scope: Only this account

Install the App only on `smiles0527/Competitive_Programming`. Record its client ID and generate a client secret.

## 2. Deploy the Worker

Copy `wrangler.toml.example` to `wrangler.toml`, replace the Worker hostname in the GitHub App callback, and deploy with Wrangler.

Set these encrypted Worker secrets:

```text
GITHUB_CLIENT_ID
GITHUB_CLIENT_SECRET
SESSION_SECRET
```

`SESSION_SECRET` should be a randomly generated value of at least 32 bytes. Do not commit any of these values.

## 3. Connect the editor

Replace the placeholder gateway address in `website/site-config.js` with the deployed Worker URL. Commit and push the change.

Keep the repository's Pages source set to the `main` branch and repository root. Every save from the editor creates one commit on `main`; GitHub Pages then publishes that commit automatically.

The private editor is available at:

```text
https://smiles0527.github.io/Competitive_Programming/website/edit.html
```

It can also be opened from the public collection with `Ctrl+Shift+E`.

To add another contest collection, register its path and sections in `website/site-config.js`, then add its top-level repository directory to `EDITABLE_ROOTS`. The gateway will reject changes outside those explicitly approved roots.
