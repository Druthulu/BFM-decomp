---
ts: 2026-11-06T15:30:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yrnrU0YUfFIKBOHOS619
---
37504 lines — the cse dump covers the whole TU. I need to find the func_8017E178 region. Let me grep for the function name in the .rtl or .cse dump. Actually cse dump labels blocks. Let me grep for "E178" or the insn pattern "andi" with 24576.

Better: the .sched or .lreg dump would show register numbers. Let me look at the cse dump near the start of the function. Grep for "func_8017E178" in the dumps.
