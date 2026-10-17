---
ts: 2026-10-17T12:25:24.264Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a04bcca3508c8aa5c
model: claude-opus-5-5[1m]
effort: medium
turnId: b53b24c7-146b-4600-ac40-c2f9f65331a4
---
I need to figure out which TU win.c was derived from for func_8012E364 — notes point to ov_SC04_011 and ov_SC03_126, but since the function's address is identical across all overlay copies, any instance could serve as the exemplar, like ov_SC04_011. I should check which copies actually exist to confirm.

For other pairs I'm cataloguing exemplars: 09f0/60d5 map to SC07_006 and MAIN_012; 2cf1's exemplar SC03_028 has func_80189AF4 with its sibling func_8018A404 living in the same TU, so I can apply the body change per-function without issue.

The W4 pairs (a88f exemplar SC03_099, db4e exemplar SC03_113) need extern/caller adjustments, so I'll defer those until later. Before writing the remap script with the EX table, I still need to nail down the exemplar for 69ec by checking win.c's tokens for func_8012E364.
