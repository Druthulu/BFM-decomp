---
ts: 2026-11-06T20:47:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_f7OiRraLm4jtjs57pK8t
---
The initial RTL: insn 92 `(set (reg/v:SI 87) (reg/v:SI 72))` — ent = a0's pseudo (72). Then the uses of 87.

Now let me see what the .cse dump shows (whether the copy was propagated).
