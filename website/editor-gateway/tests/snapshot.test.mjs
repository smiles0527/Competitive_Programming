import assert from "node:assert/strict";
import { readFile } from "node:fs/promises";
import path from "node:path";
import test from "node:test";
import { fileURLToPath } from "node:url";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const snapshot = JSON.parse(
  await readFile(path.join(root, "seeds", "editorials.json"), "utf8"),
);

test("snapshot contains the complete Sorting and Searching section in CSES order", () => {
  const sorting = snapshot.sections.find(
    (section) => section.slug === "Sorting",
  );
  assert.ok(sorting);
  assert.deepEqual(
    sorting.problems.map((problem) => problem.slug),
    [
      "distinctnumbers",
      "apartment",
      "ferriswheel",
      "concerttickets",
      "restaurantcustomers",
      "moviefestival",
      "sum2values",
      "maxsubarraysum",
      "sticklength",
      "missingcoinsum",
      "collectingnumbers1",
      "collectingnumbers2",
      "playlist",
      "towers",
      "trafficlights",
      "distinctvaluesubarrays",
      "distinctvaluesubsequences",
      "josephus1",
      "josephus2",
      "nestedrangescheck",
      "nestedrangescount",
      "roomallocation",
      "factorymachines",
      "tasksdeadlines",
      "readingbooks",
      "sumofthreevalues",
      "sumoffourvalues",
      "nearersmallervalues",
      "subarraysums1",
      "subarraysums2",
      "subarrarydivisibility",
      "distinctvaluesubarraysII",
      "arraydivision",
      "moviefestival2",
      "maximumsubarraysum2",
    ],
  );
});

test("snapshot problem keys are unique and content is present", () => {
  const keys = new Set();
  for (const section of snapshot.sections) {
    for (const problem of section.problems) {
      const key = `${section.slug}/${problem.slug}`.toLowerCase();
      assert.ok(!keys.has(key), key);
      keys.add(key);
      assert.ok(problem.markdown.trim(), key);
    }
  }
  assert.equal(keys.size, 399);
});
