---
ts: 2026-10-22T20:58:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Jby7dE9bPwfQpHgIcFcY
---
The sched1 dump shows the order it chose:
insn 165 (ax = 123), 161 (by = -93), 170 (bx = -87), 175 (lhu D_800B9A02), 190 (ay = 117), 178 (sll)...

So sched1 scheduled 165 (ax) before 161 (by) — matching the "launching 165 before 161" decision. Let me find the sched1 log lines for this block to see the priorities and the "launching X before Y" decision.

The dump's log lines are at the top of the block. Let me find the basic block containing these insns and its log. Search backwards for "basic block number".
