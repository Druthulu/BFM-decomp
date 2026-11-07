---
ts: 2026-11-07T00:40:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LSQdm5vruynjEhp3Lbof
---
The sched1 dump has the final schedule with priorities. Let me extract the function's insn list (the block after ";; Function func_801831B4") — find the insns and their priorities, especially the val load and the stores.

Let me print the region around the case-0 block. The function region starts at 65099. Let me look at the insns in order with their priorities.

Let me use awk to extract the function text and then sed a range.
