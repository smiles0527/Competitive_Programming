# Editorial website

This repository uses a small content-management system instead of one Markdown file per editorial.

- Cloudflare D1 stores problems, editorials, C++ solutions, immutable revisions, reviews, users, and roles.
- The Worker in `editor-gateway` exposes the same API locally and in production.
- GitHub OAuth identifies contributors. It does not grant them repository write access.
- Contributors create drafts and submit them for review.
- Editors review, request changes, and publish.
- Owners can also manage roles and export complete backups.
- GitHub Pages remains the public static frontend.

The original 399 Markdown/C++ pairs were imported into the consolidated
`editor-gateway/seeds/editorials.json` snapshot. It is used only to initialize a new database;
new content is created through the editor.

## Local commands

Run these commands from the repository root.

| Command                                            | Purpose                                                                   |
| -------------------------------------------------- | ------------------------------------------------------------------------- |
| `website\setup-local.cmd`                          | Install Wrangler, migrate local D1, and import the initial snapshot once. |
| `website\start-local.cmd`                          | Start the local D1 API and the static site.                               |
| `website\start-and-open.cmd`                       | Start both services and open the site.                                    |
| `website\start-local.cmd -Port 9000 -ApiPort 9001` | Use custom ports.                                                         |
| `website\check.cmd`                                | Validate the Worker, UI scripts, schema snapshot, and tests.              |
| `website\build.cmd`                                | Alias for the complete validation.                                        |
| `website\backup-editorials.cmd`                    | Export the production D1 database to `editor-gateway/backups`.            |
| `website\deploy-gateway.cmd`                       | Check, migrate, and deploy the configured Worker.                         |

The default local site is:

<http://127.0.0.1:8766/website/index.html>

Local development authentication uses the Worker's `/auth/dev` route. The ignored `.dev.vars` file
enables it locally, while the committed production values keep `DEV_MODE = "false"`.

## Editorial workflow

1. Sign in at `website/edit.html`.
2. Choose an existing problem and create an editorial.
3. Save revisions. Every save is immutable in D1.
4. Submit the draft.
5. An editor reviews it in `website/manage.html`.
6. The editor can comment, request changes, approve, or publish the current revision.
7. The public reader immediately uses the published revision. Later draft edits do not replace it
   until an editor publishes again.

Multiple people can publish independent editorials for the same problem. The reader displays an
author selector when more than one published editorial exists.

## Production setup

See `editor-gateway/README.md`. Production requires a D1 database, a GitHub OAuth App, Worker
secrets, and the deployed Worker URL in `site-config.js`. No Git commit is created for an editorial
save.
