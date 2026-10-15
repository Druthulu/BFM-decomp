---
ts: 2026-10-15T21:04:10.313Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a392f0f264a320d35
model: claude-opus-5-5[1m]
effort: high
turnId: fbd02241-c212-4c6f-9662-f763aed1dbdc
---
The ledger doesn't track type per site, so figuring out the cause for the 126 a2c8734a bodies would require joining census sites against ledger entries -- a bigger investigation than seems necessary. I'm checking whether this level of detail is actually required by the done-when criteria, which just calls for residue rows rewritten with check-residue returning 0.

Actually, I'm now noticing TYPE-NO-MEMBER is missing from the by-cause breakdown, meaning the 7 rows c4 added after c3's restamp didn't propagate through my latest run. The restamp logic should route a2c8734a through type_folds into residual TYPE-NO-MEMBER since it's non-canonical, unless the per-site type name in body_base_type.json differs from what struct_map reports in top_types. I want to write a small scratch script to load body_base_type.json and cross-check site counts for the top residual type names against the residue data, so first I should inspect the structure of body_base_type.json itself.
