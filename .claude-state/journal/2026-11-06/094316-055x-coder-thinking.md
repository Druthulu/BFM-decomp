---
ts: 2026-11-06T16:43:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wLzyZLcm6M8hNKqOt65b
---
The emitted code is the target's layout! But the jump2 RTL showed a merge. So the dump I read must be stale or from a different TU copy. Wait, the dump was made from $D/dumptu/ov_SC01_084/t.c which I copied from p4 AFTER the --keep. Hmm, but maybe the p4 scratch TU wasn't updated by --keep? The --keep output path is p4/cand.o; the TU copy in p4/... Let me check: the previous --keep (v3) was p3, and I copied from p3 path. For w4 I copied `.run/P36/engine/score/ov_SC01_084__func_80181F80/p4/ov_SC01_084_jr_8017F690.c`. Maybe the scratch TU file name differs or it's the same as the src? Let me check the dump's jump2 for the asm/body.

Actually more likely: the jump2 dump is of the *correct* w4 body but jump2's merge there is a DIFFERENT merge (the same optimization applied but at a point where the result still assembles identically?). Hmm, but the emitted code is clearly unmerged (has the j at 2ba8). So the dump can't be w4.

Let me verify by checking the dump's .jump1 or the .s for the region, and diff the dump's t.c against win.c.
