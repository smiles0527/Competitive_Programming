# Editorial API

All responses are JSON. Authenticated requests use:

```text
Authorization: Bearer SESSION_TOKEN
```

## Public

| Method | Route | Purpose |
| --- | --- | --- |
| `GET` | `/health` | Service health. |
| `GET` | `/api/catalog` | Flat catalog of published editorials. |
| `GET` | `/api/problems?collection=&section=` | Ordered problem catalog. |
| `GET` | `/api/editorials?collection=&section=&slug=` | Published revisions and authors for one problem. |

## Authentication

| Method | Route | Purpose |
| --- | --- | --- |
| `GET` | `/auth/start` | Begin GitHub OAuth. |
| `GET` | `/auth/callback` | Complete GitHub OAuth and return to the editor. |
| `GET` | `/auth/dev?login=&redirect=` | Local-only identity flow when `DEV_MODE=true`. |
| `GET` | `/api/me` | Current user and role. |

## Contributor

| Method | Route | Purpose |
| --- | --- | --- |
| `GET` | `/api/dashboard` | Own drafts, or all editorials for staff. |
| `POST` | `/api/editorials` | Create a draft and its first revision. |
| `GET` | `/api/editorials/:id` | Load an accessible editorial, revisions, authors, and reviews. |
| `PUT` | `/api/editorials/:id` | Save an immutable revision. |
| `PATCH` | `/api/editorials/:id` | Rename an editorial or move it to another problem. |
| `DELETE` | `/api/editorials/:id` | Permanently delete an editorial when the caller has permission. |
| `POST` | `/api/editorials/:id/submit` | Submit a draft for review. |
| `POST` | `/api/editorials/:id/withdraw` | Withdraw an editorial from review. |
| `POST` | `/api/editorials/:id/duplicate` | Create an independent draft copy. |

## Editor and owner

| Method | Route | Purpose |
| --- | --- | --- |
| `POST` | `/api/editorials/:id/review` | Comment, approve, or request changes. |
| `POST` | `/api/editorials/:id/publish` | Publish the current revision. |
| `POST` | `/api/editorials/:id/archive` | Remove an editorial from the public catalog. |
| `POST` | `/api/editorials/:id/restore` | Restore an archived editorial. |

## Owner

| Method | Route | Purpose |
| --- | --- | --- |
| `GET` | `/api/users` | List users and roles. |
| `PUT` | `/api/users/:id/role` | Change a user role. |
| `GET` | `/api/export` | Export all durable editorial data as JSON. |

Public reads always use `published_revision_id`. Saving a new draft revision does not change the
public content until an editor publishes that revision.

Owner writes are direct: `PUT /api/editorials/:id` immediately updates `published_revision_id`, and
an owner may pass `"publish": true` when creating an editorial to publish its first revision in the
same operation.
