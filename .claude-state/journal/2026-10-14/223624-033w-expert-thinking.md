---
ts: 2026-10-15T04:36:24.636Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7996093418d381a4
model: claude-opus-5-5[1m]
effort: medium
turnId: 709b2f04-d315-4060-ba93-85c3894dd69d
---
I'm wondering if residue_census.json was ever force-added given the gitignore rule, and I want to check its mtime and contents against what was on disk at P37, since the gate values in T9/T11 didn't quite match the census numbers at the time.

Actually, the discrepancy is consistent: the gate count is always 5-6 lower than the raw census count within the same directory. That suggests residue_split deduplicates sites by key (file/func/line/col), so duplicate entries — maybe from a header included across multiple translation units or a macro expanding twice on the same line — get collapsed, and I want to verify this by comparing the current on-disk census json against residue_split directly.

Found that `residue_census.json` was never tracked—the `.run/` ignore rule swallowed it—so no history exists. The key clue is T11 showing the P37 gate at P=257,464 vs the census JSON's 257,469, suggesting `residue_split` is collapsing sites; I'll dig into that function next.
