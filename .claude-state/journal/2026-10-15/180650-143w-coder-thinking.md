---
ts: 2026-10-16T00:06:50.948Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a59367940640fa024
model: claude-opus-5-5[1m]
effort: medium
turnId: 803d3be5-75b3-4fdb-8709-5ff2b26b900c
---
I'm realizing that since type_census.json only keeps the top 300 names by count, any listed rows beyond that cutoff get dropped by struct_twins' load_rows, causing their sections to disappear and re-trigger gating each run. Since I can't modify type_census, the fix needs to live in load_rows itself—preserving rows currently listed under `## Twins` even if they fall outside the top-300 json and aren't in dup_gating.tsv.

I need to confirm these surviving rows are genuinely valid tier-2 matches rather than stale: a row absent from dup_gating was presumably cleared by twins_ok, but if its listed lhash is now stale, keeping it would just preserve outdated data. So I want to check whether type_census or check-structs records stale lhashes anywhere in its output, since dup_gating.tsv alone doesn't distinguish "valid non-gating" from "stale non-gating" rows.

Found the root cause: `type_census.json` only retains the top 300 `dup_layout_classes`, so when struct_twins' `load_rows` uses it to restore rows already removed from dup_gating.tsv, anything beyond the cap gets dropped and re-gated on regeneration. I'll now check what the census exposes about stale rows to fix this struct_twins rule bug.
