# Editorial website

## Local repository editing

Run `website/start-local.cmd`, then open:

```text
http://127.0.0.1:8766/website/index.html
```

The hidden editor opens with `Ctrl+Shift+E`. In local repository mode, `Save locally` writes the selected Markdown and C++ files directly into their existing folders. It does not run Git commands or publish anything.

The local server accepts requests only on `127.0.0.1`, issues a per-process write token, checks the previous file hash before overwriting, and restricts writes to registered editorial roots with `.md` or `.cpp` extensions.

## Global editing

On the deployed site, the local write endpoint does not exist. After the authenticated gateway is configured, the same editor instead displays `Save and publish`. That action creates a GitHub commit, waits for GitHub Pages to deploy it, and confirms when the change is publicly visible.

## Adding collections

Register each contest or problem set in `website/site-config.js`. Add the same top-level folder to the local server's `--editable-root` arguments and to the deployed gateway's `EDITABLE_ROOTS` setting.
