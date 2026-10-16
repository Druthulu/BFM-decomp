---
ts: 2026-10-15T22:55:50.069Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a59367940640fa024
model: claude-opus-5-5[1m]
effort: medium
turnId: 803d3be5-75b3-4fdb-8709-5ff2b26b900c
---
I'm adding an optional twin_of parameter to decide_band that lets me detect when a residual text matches a canonical twin name, tagging it with a TYPE-CANON-TWIN residual and layout-twin evidence when found. Now I'm working out how decide_band_cmd would supply this twin_of function, likely by building it from a t3_canon_twins() lookup.

Still writing twin-matching logic...

I'm checking edge cases: canonical defs excludes those with missing layout hash or zero fields, so I need to make sure nfields is read correctly from the definition records. There's also the subtlety that when an existing canonical lhash group is already a tier-3 class with multiple meaningful signatures, adding a new opaque def needs careful handling so it doesn't incorrectly collapse into that group.

On the performance side, walking struct_types.h (~170KB) and running the file walker across ~4800 batch-3 rows should still be manageable since each per-def scan operates on small text snippets.

Confirming that comments under map names resolve to None so name_sig stays unaffected, and that tc.Resolver and tc.layout_hash are available for struct_twins. The ordering matters: residual checks run first, then the twin check acts as a residual class before the define step runs.

For item 2, I'm defining a pure function that locates or creates a "## Dead kept" section in the doc text, parses existing bullet names, and appends bullets for any missing names at the section's end.

I'm drafting the bullet text format for these dead-kept entries, noting that kept names stay dead until drawn later — a future concern, not something to handle now. For item 3, I'm working out how struct_twins should parse config/type_folds.tsv to flag rows appearing after a "# T3" comment line as belonging to the T3 block, tracking a flag that stays set once triggered since T3 rows are appended at the end.

For unbound names matching T3 targets, I'm scanning sites.jsonl to collect a capped set (max 3) of unique binary/function citations per map type, then binding them under a "U" key with the map type noted — matching the existing convention in scan_file where U-keys with a "/" in the second element represent function citations rather than owner names.

I'm now figuring out where to surface this T3 info in the output text — likely folding it into the cause line alongside the existing "used only by" phrasing, adding a fragment noting it's a T3 band def dead until rung S with the relevant map type.

For the implementation, I'm planning to store a mapping of names to map types for T3 cases, then scan the large sites.jsonl file for lines matching each map type by extracting the "type" field cheaply per line rather than full JSON parsing, since there could be thousands of types to check across roughly a million lines. Sites matching those types count as TNC bodies since the type itself marks them non-canonical.

I'm also thinking through testing: building pure helper functions for the T3 targets and site citations so they can be unit tested independently, and constructing a fake UNBOUND class with T3 bindings to verify that the rendered section's cause line matches the expected address pattern.

I'll implement `--decide-band` to detect tier-1 classes by comparing layout hashes and signatures against canonical headers, copying the tier regex locally since type_census.py must remain untouched, then have `--write` append new targets idempotently and add small pure helpers to struct_twins.py (with tests living in restruct's selftest).
