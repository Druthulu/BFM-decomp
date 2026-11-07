---
ts: 2026-11-06T11:58:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_60kBUvu163JyngSBr9LR
---
Interesting! p2 (launders kept, barriers removed) = 8, 93 insns (one fewer). p1 (barriers kept, launders gone) = 69.

So here the LAUNDERS are the load-bearing levers, not the barriers. Removing the barriers nearly works (score 8).

Wait, that contradicts my v0/v1 (both removed) = 75. So removing the launders is catastrophic; removing the barriers is nearly fine.

So the crack path: remove barriers (allowed), keep launders? No — for a MATCH both kinds must go. For PARTIAL, we need win.c scoring 0 keeping only some kinds: PARTIAL:launder would be p2 with launders kept and barriers gone, if it scores 0. It's 8 now; maybe real-C moves can get it to 0.

Let me look at p2's diff.
