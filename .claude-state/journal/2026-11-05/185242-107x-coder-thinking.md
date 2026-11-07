---
ts: 2026-11-06T01:52:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Vo2dNKGd09Y922YE9Y6V
---
I keep failing to find it. Let me just use gdb on cc1 to break on delete_insn and see the caller when compiling vA. But gdb might not be installed; let's check. Actually, a faster decisive approach: compile vA with `-dj` but also with `-dS`? no.

Alternative: accept the empirical facts and find a C shape that works by brute force. We have a scorer; each try ~1-2 s. Let me generate a larger batch of plausible shapes and score them. The space: we need the cross-jump at jump2 to fail. Facts:
- Source order sh;sw (target) → merge (136 ins).
- Source order sw;sh → no merge but wrong order (138 ins, score 2).

So the ONLY remaining requirement is to get the sh before the sw in the final asm while the store isn't the last RTL insn at jump2. If sched2 can be made to swap the two stores, we win. In v1, sched2 didn't swap. Why? Let me look at v1's .sched2 input/output (correct dump from p5). Earlier I dumped v1 from p3 (stale = orig). Let me redo properly with p5 and check the order at sched2 and dbr.

Actually, the p5 dir is v1 (verified: store then sh). Let me dump p5 and look at .sched (pre-sched2? .sched = after sched1) and .sched2.
