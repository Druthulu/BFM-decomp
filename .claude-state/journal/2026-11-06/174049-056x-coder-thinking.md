---
ts: 2026-11-07T00:40:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SBBePilPXkMDXHaJxLmD
---
Interesting: the sched1 dump shows the *scheduled* order. Note insn 45 is `(set (reg/v:SI 75) ...)` — probably p = &D_801B7930. Let me see insns 56-84 in detail (the stores and the val load).

Let me print lines from the "(insn 56" to the end of the block.
