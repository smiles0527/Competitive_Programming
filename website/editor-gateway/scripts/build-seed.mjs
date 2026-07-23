import { mkdir, readFile, writeFile } from "node:fs/promises";
import path from "node:path";
import { fileURLToPath } from "node:url";

const gatewayRoot = path.resolve(
  path.dirname(fileURLToPath(import.meta.url)),
  "..",
);
const snapshotPath = path.join(gatewayRoot, "seeds", "editorials.json");
const sqlPath = path.join(gatewayRoot, ".wrangler", "editorials.sql");
const snapshot = JSON.parse(await readFile(snapshotPath, "utf8"));

const sqlString = (value) =>
  value == null ? "NULL" : `'${String(value).replaceAll("'", "''")}'`;

const lines = [
  "PRAGMA foreign_keys = ON;",
  "DELETE FROM reviews;",
  "DELETE FROM editorial_authors;",
  "DELETE FROM revisions;",
  "DELETE FROM editorials;",
  "DELETE FROM problems;",
  "DELETE FROM sections;",
  "DELETE FROM collections;",
  "DELETE FROM sessions;",
  "DELETE FROM users;",
  `INSERT INTO users (id, login, display_name, role) VALUES (1, ${sqlString(snapshot.owner.login)}, ${sqlString(snapshot.owner.display_name)}, 'owner');`,
  `INSERT INTO collections (id, label, sort_order) VALUES (${sqlString(snapshot.collection.id)}, ${sqlString(snapshot.collection.label)}, ${snapshot.collection.sort_order});`,
];

let sectionId = 0;
let problemId = 0;
let editorialId = 0;
let revisionId = 0;

for (const section of snapshot.sections) {
  sectionId += 1;
  lines.push(
    `INSERT INTO sections (id, collection_id, slug, label, sort_order) VALUES (${sectionId}, ${sqlString(snapshot.collection.id)}, ${sqlString(section.slug)}, ${sqlString(section.label)}, ${section.sort_order});`,
  );

  for (const problem of section.problems) {
    problemId += 1;
    editorialId += 1;
    revisionId += 1;
    lines.push(
      `INSERT INTO problems (id, section_id, slug, title, source_url, sort_order) VALUES (${problemId}, ${sectionId}, ${sqlString(problem.slug)}, ${sqlString(problem.title)}, ${sqlString(problem.source_url)}, ${problem.sort_order});`,
      `INSERT INTO editorials (id, problem_id, created_by, status, current_revision_id, published_revision_id, published_at) VALUES (${editorialId}, ${problemId}, 1, 'published', ${revisionId}, ${revisionId}, CURRENT_TIMESTAMP);`,
      `INSERT INTO revisions (id, editorial_id, author_id, markdown, solution_cpp, summary) VALUES (${revisionId}, ${editorialId}, 1, ${sqlString(problem.markdown)}, ${sqlString(problem.solution_cpp)}, 'Imported from the original editorial collection');`,
      `INSERT INTO editorial_authors (editorial_id, user_id, position) VALUES (${editorialId}, 1, 0);`,
    );
  }
}

await mkdir(path.dirname(sqlPath), { recursive: true });
await writeFile(sqlPath, `${lines.join("\n")}\n`, "utf8");
console.log(
  `Generated ${snapshot.sections.reduce((count, section) => count + section.problems.length, 0)}-editorial D1 seed at ${path.relative(gatewayRoot, sqlPath)}.`,
);
