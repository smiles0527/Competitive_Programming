import { readFile } from "node:fs/promises";
import path from "node:path";
import { fileURLToPath } from "node:url";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const snapshot = JSON.parse(
  await readFile(path.join(root, "seeds", "editorials.json"), "utf8"),
);
const seen = new Set();
let count = 0;
let missingSolutions = 0;

for (const section of snapshot.sections) {
  for (const problem of section.problems) {
    const key =
      `${snapshot.collection.id}/${section.slug}/${problem.slug}`.toLowerCase();
    if (seen.has(key)) throw new Error(`Duplicate problem key: ${key}`);
    seen.add(key);
    if (!problem.markdown.trim()) throw new Error(`Missing editorial: ${key}`);
    if (!problem.solution_cpp.trim()) missingSolutions += 1;
    count += 1;
  }
}

if (!count) throw new Error("The editorial snapshot is empty");
console.log(
  `Snapshot OK: ${count} editorials, ${missingSolutions} without a C++ solution.`,
);
