---
ts: 2026-10-15T22:53:13.261Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a59367940640fa024
model: claude-opus-5-5[1m]
effort: medium
turnId: 803d3be5-75b3-4fdb-8709-5ff2b26b900c
---
I'm working out the tiering logic: a new opaque definition joining a class with exactly one meaningful signature lands in tier 1, two or more pushes it to tier 3 with opaque entries forming tier 2 rows, and an all-opaque class stays tier 2. For the first rule, I'm defining when a new define counts as a TYPE-CANON-TWIN—specifically when its layout hash matches an existing canonical definition's hash and that class would otherwise be tier 1.

I need to decide whether to count meaningful signatures across all defs or just canonical ones, and I'm leaning toward computing this over the full census of defs since that's what check-structs would actually gate on, even if the canonical name ends up being a non-canonical meaningful def from somewhere like a .c file.

The real question is how to get the lhash for the new rendered def itself—whether the census exposes per-def lhash somewhere (maybe defs.jsonl or similar) since dup rows alone only cover existing multi-type classes, not unique canonical layouts. I should check how restruct already parses rendered defs and calls into the census/resolver machinery, and look at decide_band to see the existing pattern for computing this.
