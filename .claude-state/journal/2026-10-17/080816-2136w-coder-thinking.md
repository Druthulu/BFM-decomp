---
ts: 2026-10-17T14:08:16.600Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe7336983cc0fdaf
model: claude-opus-5-5[1m]
effort: medium
turnId: ad81449e-f0c8-40b2-83c6-f273f94996ed
---
I notice v1b gets the scheduling nearly right. The issue is register allocation order: p shares s0 with the dead param a0, but in the target idx=s1, tbl=s2, p=s0 reusing the param slot — so p needs to be allocated first since it has the most references, before idx and tbl get assigned.

Looking deeper, maybe p is actually the same variable as param a0, reused after it dies, matching the catalog pattern where a late local reusing an earlier-dead one lands in its register. If so, p's pseudo would just be the param pseudo: s0 for p, s1 for idx, s2 for tbl. That would also mean the assignment isn't a REG_EQUIV fold since the variable gets set twice (once as param, once as &D), which matches the absolute +0x10/+0x20 stores not folding. I want to try treating a0 as a reused void* variable cast to p and see if the offsets fold correctly from there.
