---
ts: 2026-10-15T21:19:38.178Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a8db926a6adc5bbd5
model: claude-haiku-5-5[1m]
effort: medium
turnId: 71f49971-3fa1-4ac7-ba61-10ef592c67d9
---
I'm noting that restamp_rows only rewrites entries whose old cause matches TYPE-NOT-CANONICAL, so I'll need to check that condition for any variant. Next I'll look at the restamp logic, struct_map, residue_census, and the struct_twins scanning code to understand the full flow.
