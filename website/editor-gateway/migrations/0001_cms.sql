PRAGMA foreign_keys = ON;

CREATE TABLE users (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  github_id INTEGER UNIQUE,
  login TEXT NOT NULL UNIQUE COLLATE NOCASE,
  display_name TEXT,
  avatar_url TEXT,
  role TEXT NOT NULL DEFAULT 'contributor'
    CHECK (role IN ('owner', 'editor', 'contributor')),
  active INTEGER NOT NULL DEFAULT 1,
  created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE collections (
  id TEXT PRIMARY KEY,
  label TEXT NOT NULL,
  sort_order INTEGER NOT NULL DEFAULT 0
);

CREATE TABLE sections (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  collection_id TEXT NOT NULL REFERENCES collections(id) ON DELETE CASCADE,
  slug TEXT NOT NULL,
  label TEXT NOT NULL,
  sort_order INTEGER NOT NULL DEFAULT 0,
  UNIQUE (collection_id, slug)
);

CREATE TABLE problems (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  section_id INTEGER NOT NULL REFERENCES sections(id) ON DELETE CASCADE,
  slug TEXT NOT NULL,
  title TEXT NOT NULL,
  source_url TEXT,
  sort_order INTEGER NOT NULL DEFAULT 0,
  created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  UNIQUE (section_id, slug)
);

CREATE TABLE editorials (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  problem_id INTEGER NOT NULL REFERENCES problems(id) ON DELETE CASCADE,
  created_by INTEGER NOT NULL REFERENCES users(id),
  status TEXT NOT NULL DEFAULT 'draft'
    CHECK (status IN ('draft', 'submitted', 'changes_requested', 'published', 'archived')),
  current_revision_id INTEGER,
  published_revision_id INTEGER,
  created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  submitted_at TEXT,
  published_at TEXT
);

CREATE TABLE revisions (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  editorial_id INTEGER NOT NULL REFERENCES editorials(id) ON DELETE CASCADE,
  author_id INTEGER NOT NULL REFERENCES users(id),
  markdown TEXT NOT NULL,
  solution_cpp TEXT NOT NULL DEFAULT '',
  summary TEXT NOT NULL DEFAULT '',
  created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE editorial_authors (
  editorial_id INTEGER NOT NULL REFERENCES editorials(id) ON DELETE CASCADE,
  user_id INTEGER NOT NULL REFERENCES users(id),
  position INTEGER NOT NULL DEFAULT 0,
  PRIMARY KEY (editorial_id, user_id)
);

CREATE TABLE reviews (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  editorial_id INTEGER NOT NULL REFERENCES editorials(id) ON DELETE CASCADE,
  revision_id INTEGER NOT NULL REFERENCES revisions(id) ON DELETE CASCADE,
  reviewer_id INTEGER NOT NULL REFERENCES users(id),
  decision TEXT NOT NULL CHECK (decision IN ('comment', 'approve', 'request_changes')),
  comment TEXT NOT NULL DEFAULT '',
  created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE sessions (
  id TEXT PRIMARY KEY,
  user_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
  expires_at TEXT NOT NULL,
  created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX problems_section_order_idx ON problems(section_id, sort_order, id);
CREATE INDEX editorials_problem_status_idx ON editorials(problem_id, status);
CREATE INDEX editorials_creator_idx ON editorials(created_by, updated_at);
CREATE INDEX revisions_editorial_idx ON revisions(editorial_id, id DESC);
CREATE INDEX reviews_editorial_idx ON reviews(editorial_id, id DESC);
CREATE INDEX sessions_expiry_idx ON sessions(expires_at);
