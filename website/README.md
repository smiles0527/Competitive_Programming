# Editorial website

## Local repository editing

Run `website/start-local.cmd`, then open:

```text
http://127.0.0.1:8766/website/index.html
```

The **Manage editorials** page audits every editorial in the repository, including files that are not listed on the public site. It reports missing sections, template text, missing or unfinished C++ solutions, short drafts, and unlisted files. Search and filters narrow the catalogue by category, quality, and website visibility.

The home page links the three main workflows: the section reader, the searchable all-editorials catalogue, and the local management workspace. Existing `index.html?collection=...` editorial links are redirected to the reader automatically.

From the manager, open any editorial in the split editor or create a new one. In local repository mode, `Save locally` writes the selected Markdown and C++ files directly into their existing folders. `New editorial` creates a Markdown/C++ pair in the chosen section, adds it to that section's editorial picker, and opens it for editing. It does not run Git commands or publish anything.

The local server accepts requests only on `127.0.0.1` and prints a fresh management password when it starts. The catalogue, editor, creation, and save endpoints require a signed-in browser session. The server also checks the previous file hash before overwriting and restricts writes to registered editorial roots with `.md` or `.cpp` extensions. Set `EDITORIAL_EDITOR_PASSWORD` before startup if you want a persistent password instead of a new generated one.

## Global editing

On the deployed site, the local write endpoint does not exist. After the authenticated gateway is configured, the same editor instead displays `Save and publish`. That action creates a GitHub commit, waits for GitHub Pages to deploy it, and confirms when the change is publicly visible. Pull that commit into the local repository to synchronize a public edit back to the local folders.

## Adding collections

Register each contest or problem set in `website/site-config.js`. Add the same top-level folder to the local server's `--editable-root` arguments and to the deployed gateway's `EDITABLE_ROOTS` setting.
