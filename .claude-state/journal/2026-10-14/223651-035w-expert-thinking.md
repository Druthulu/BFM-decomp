---
ts: 2026-10-15T04:36:51.240Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7996093418d381a4
model: claude-opus-5-5[1m]
effort: medium
turnId: 709b2f04-d315-4060-ba93-85c3894dd69d
---
This explains it: the 5 P and 1 M #define-line sites in include/common.h are counted in the raw census but excluded by the residue gate, exactly matching T11's "6 sites: P 5, M 1" count. So it's not a directory issue but a legitimate exclusion — explained rather than needing a fix, though it might warrant a docs note. The settled reading is that the gate runs type_census with cast-checking and residue filtering, writing output to the specified directory.

I need to pin down how P37 (gate/restruct census), P39 (newest series census), and the residue census interact — if someone ever creates a P40/census directory, it would become the new "newest" and shift the series source, so I should avoid creating that during this phase. I'll settle on using P37 as the fixed gate and restruct directory while letting the series continue reading whatever is newest (currently P39), confirming restruct_cycle refreshes the newest dir regardless. Now I'm waiting for the nocache step before running the check-casts and residue flags into P37 to establish baselines and the lever census.

Found the discrepancy: `include/common.h` has 6 `#define`-line sites (5 P, 1 M) that `residue_split` excludes but the raw census counts, exactly matching T11's numbers — so it's a predicate difference, not a directory issue. Now waiting for the no-cache run to confirm.
