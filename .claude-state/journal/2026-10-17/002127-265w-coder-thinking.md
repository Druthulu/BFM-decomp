---
ts: 2026-10-17T06:21:27.616Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
I'm checking 8012E688 and 8017E3F0, both just write to scratch space. For 8018094C, the read on $4 looks like a real parameter rather than noise, and tracing callers shows it's actually invoked indirectly through a function pointer passed to func_801788B8, so I'm treating it as a callback taking s0 as its parameter and renaming it to func_8018094C_bank accordingly.

For 8017EC90 (SC03_007), the K&R-style definition has pins duplicating the a0/a1 parameters, so I'm converting it to drop the pins and use the parameters directly. Now I'm compiling the list of remaining READ cases still needing closer inspection: 8017E210, 8017F0AC, 80180FA4, 8018107C (SC07_007, duplicate of a2), 80181B14, 800CCD50, and 80151664, and I want to recheck the background context for these.
