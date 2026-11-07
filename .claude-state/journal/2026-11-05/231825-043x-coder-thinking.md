---
ts: 2026-11-06T06:18:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FzNE5RC5owgcrSjTFtZC
---
§195-I is interesting: "ANY second SET of a pseudo in the address's equivalence chain (in-place p += K, p = r; copy, or an asm re-tie) kills the fold; the pass is cse and the gate is invalidate's reg_tick++".

But for our otz: the fold is by combine, after cse. Hmm.

Let me search for a cookbook entry about keeping a copy that combine folds — "cse-copy-merge" is the wall tag. The G14 line 187 says "the launder tied-output on sc -> empty do { } while (0)". Let me look at that item's win.c to see exactly where the do-while went. Item func_8018CDEC (G14). Let me find the dir.

Actually the key: for func_8018302C (line 219) "the copy wrapped in do-while(0) (loop-shaped live range) — or v1,v0 survives". Let me look at that win.c to see the pattern. Find the dir in .run/P40/T11/*/func_8018302C*.
