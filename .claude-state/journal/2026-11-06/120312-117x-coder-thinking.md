---
ts: 2026-11-06T19:03:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jPtwa38IG2IjDjWpospG
---
k1-k3 score 2 (same increment-order residual). Let me check if k1's residual is the same (the a3 increment). If yes, no progress.

Let me look at the sched1 trace for the target (orig, pinned) vs h049 to understand the priority difference. In the target, a7 is a HARD REG ($7), so in sched1 (pre-reload) the a7 increment `(set (reg 7 a3) (plus (reg 7 a3) 104))` — a hard-reg insn. sched1's priority/hazard computations treat it differently.

In h049, a7 is a pseudo (74). sched1's "birthing_insn_p": `(set (reg 74) (plus (reg 74) 104))` — 74 is live at the block start (loop-carried) and reg_n_sets[74] > 1 → birthing_insn_p requires reg_n_sets == 1 → false. Hmm.

The priorities in the h049 trace: 37 (v1 inc) and 40 (a7 inc) both priority 1. Equal → the list order decides.

In the target (orig), let me dump the sched trace and compare the loop block's ready list. If the pin makes the a7 increment's priority higher, that's the mechanism.

Let me dump the orig (pinned) properly: the scratch header for orig.c. Actually, the real src header IS the pinned version — I can compile it directly (it has 40 lines, < 200 → the guard refuses). Let me copy src/shared/ov/func_80146750.h + padding to my item dir and dump.
