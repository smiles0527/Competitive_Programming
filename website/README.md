# Editorial website

## Editing of local repository

Execute `website/start-local.cmd`, then go to:

```text
http://127.0.0.1:8766/website/index.html
```

The **Manage editorials** page executes the audit of all editorials found in the repository, including those that are not included on the public website. It finds all editorials with missing sections, template text, missing or corrupted C++ solutions, abbreviations, and unregistered files. Searching capabilities and filters allow narrowing down the list of editorials by category, quality, and website visibility.

The home page offers three main workflows: the section reader, all editorials catalog, and local management environment. Links to existing editorials in the format `index.html?collection=...` are automatically redirected to the section reader.

From the manager interface, you can open selected items in the split editor or create a new editorial. In local repository editing mode, **Save locally** saves the selected Markdown and C++ files directly to the appropriate folders. **New editorial** creates a pair of Markdown/C++ files in the selected section, registers it in that section's editorials list, and starts editing. No Git commands are executed and no changes are published.

After local login, the section reader, all editorials catalog, management console, and live editor include all sections and pairs of Markdown/C++ files found in the repository, including those that are not yet published. The deployed website uses only those sections that were explicitly published in `site-config.js`.

The local server connects only to `127.0.0.1` and prints a new management password on startup. Accessing the catalog, editor, creation, and save endpoints requires browser-session authentication. The server verifies the previous file hash before overwriting and allows write operations only in directories registered as editorial roots containing `.md` and `.cpp` files. To keep a persistent password instead of generating one on every startup, set `EDITORIAL_EDITOR_PASSWORD` before starting the server.

## Global editing

On the deployed website, the local save endpoint is unavailable. After configuring the authenticated gateway, the same editor offers the **Save and publish** button. This operation generates a GitHub commit, waits until the GitHub Pages deployment finishes, and confirms the public visibility of the change. To make public changes available locally, pull the corresponding commit into the local repository.

## Adding collections

Each contest or problem set should be added to `website/site-config.js`. Create the same top-level folder in the local server's `--editable-root` and in the deployed gateway's `EDITABLE_ROOTS` settings.
