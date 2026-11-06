---
ts: 2026-10-22T21:43:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_g5dVA6ZVZiQCB7e4t1Mj
---
At expand (rtl): insn 40 = `set (reg/v:QI 3 v1)` (byteval, QI) at line ~64, and insn 43 = `set (reg/v:SI 4 a0)` (testval) after. So RTL order: $3 copy (insn 40) before $4 copy (insn 43) — correct source order.

Now let me check the sched dump to see the order after sched1. Find the function in u8.i.sched and look at the insn sequence.
