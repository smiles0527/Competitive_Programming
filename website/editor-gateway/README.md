# Editorial gateway configuration

Configuration of the editorial gateway for the public site and authenticated updates of editorial
content.

## Architecture

The GitHub Pages site is a static client. A Cloudflare Worker provides GitHub authentication,
authorization, and the editorial API. Cloudflare D1 stores the content and revision history.
Editorial updates do not create Git commits and contributors never receive repository permissions.

Roles are enforced by the Worker:

- `contributor`: create, edit, and submit their own drafts;
- `editor`: review any submission, request changes, publish, and archive;
- `owner`: all editor permissions plus role management and full exports.

Logins listed in `OWNER_LOGINS` become owners. Every other new login starts as a contributor.

## 1. Create the D1 database

From this directory:

```text
npx wrangler login
npx wrangler d1 create competitive-programming-editorials
```

Copy the returned database ID into `wrangler.toml`. Then initialize production:

```text
npm install
npm run seed:build
npm run db:migrate:remote
npm run db:seed:remote
```

Run the remote seed only for a new, empty database. It replaces database content with the
consolidated 399-editorial snapshot.

## 2. Register GitHub OAuth

Create a GitHub OAuth App owned by `smiles0527`:

- Homepage URL: `https://smiles0527.github.io/Competitive_Programming/`
- Callback URL: `https://YOUR-WORKER.workers.dev/auth/callback`

Only `read:user` identity is requested. Repository permissions are not required.

## 3. Configure and deploy the Worker

Copy `wrangler.toml.example` to `wrangler.toml`, set the D1 database ID, and keep:

```text
SITE_ORIGIN = "https://smiles0527.github.io"
EDITOR_URL = "https://smiles0527.github.io/Competitive_Programming/website/edit.html"
DEV_MODE = "false"
```

Store secrets through Wrangler:

```text
npx wrangler secret put GITHUB_CLIENT_ID
npx wrangler secret put GITHUB_CLIENT_SECRET
```

Then deploy:

```text
npm run check
npm run deploy
```

Finally, replace the `apiBase` placeholder in `website/site-config.js` with the deployed Worker URL
and publish the static site.

## Local development

`website\setup-local.cmd` applies migrations and imports the seed once.
`website\start-local.cmd` starts Wrangler on `127.0.0.1:8787` and the static site on
`127.0.0.1:8766`.

Local sign-in uses `/auth/dev` and the `OWNER_LOGINS` list. Local overrides are stored in the
ignored `.dev.vars` file; `.dev.vars.example` documents them. This route returns 404 in production
because the production configuration keeps `DEV_MODE` set to `false`.

## Backups and recovery

The owner interface can download a JSON export. For a D1 SQL backup run:

```text
npm run db:export
```

Backups, local D1 state, secrets, and `node_modules` are ignored by Git.

## Adding collections and problems

The initial schema is collection-agnostic. Collections, sections, and problems are rows in D1, so
the public catalog does not require new HTML files or manifests. At present, the seed importer
creates the CSES catalog. A future collection importer can emit the same consolidated snapshot
shape without changing the API or frontend.
