---
ts: 2026-10-15T21:04:37.507Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a392f0f264a320d35
model: claude-opus-5-5[1m]
effort: high
turnId: fbd02241-c212-4c6f-9662-f763aed1dbdc
---
I'm puzzling over why type 800D3888 still shows 19,259 raw census sites across 4908 bodies, since it was folded into 800B5CB8 but the drawn rung only captured about 12k of them — trying to figure out what accounts for that residue.

I notice there are 8 define rows with nonzero remaining sites — like 8016B4F8 at 1273 and 80126948 at 936 — which are canonical defs but still carry raw sites tied to causes like NO-FIELD or NO-EDIT. This raises the question of whether residual types' sites actually get stamped with their residual causes; the by-cause breakdown is missing TYPE-NO-MEMBER entirely, even though seven TYPE-NO-MEMBER types account for roughly 9.6k sites that should've been restamped. My restamp on the ov_* bodies apparently didn't produce any TYPE-NO-MEMBER entries, so I want to check one specific case — ov_SC01_000's func_80169BBC — by grepping the ledger for that function's latest S-row entries and inspecting the causes directly.
