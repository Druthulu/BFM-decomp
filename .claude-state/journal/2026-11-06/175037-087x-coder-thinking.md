---
ts: 2026-11-07T00:50:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8uinCYzSK0IqUMK5uihz
---
Target: at c6c0-6d4: `lui s0, D_800AF630` (the base loaded into s0), then `jal func_8004914C` with `addiu a0,s0,24` in the delay slot; then `jal func_800491AC` with `addiu a0,s0,24` in the delay slot. So the base s0 is loaded once, and TWO addiu's (one per call, in the delay slots).

Without the launder, cse merges the two `mb+0x18` computations, so only one addiu is needed... but with the calls in between, the value can't survive in a0 across the call (call-clobbered). Hmm, the note says cse unifies the second add through the constant class and combine folds the symbol into the lone survivor.

Let me first just try the lever-free body: remove the three launder asms and score.

Let me extract the function (lines 10967 to the end) and build orig.c. The function is long; let me find its end.
