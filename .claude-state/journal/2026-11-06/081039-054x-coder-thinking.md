---
ts: 2026-11-06T15:10:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0DrjDLmPvAT01eaLHTmA
---
These are block-boundary NOTES (priority = max - small). The interesting region is around lines 1600-2300 (sched1 for the function's later blocks). Let me grep in lines 1600-2400 for priorities of the mults and the "launching" order.

Let me find the block that contains insn 472/484. The log lines ";; insn[ 472]: priority = 1". Let me look at lines 1660-1750.
