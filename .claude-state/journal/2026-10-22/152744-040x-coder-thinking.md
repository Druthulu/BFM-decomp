---
ts: 2026-10-22T21:27:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MQkGLZEqfMPOYL8kkMql
---
Not decisive. Let me instead look directly at the store in each pass: find the insn that stores to offset 48 with a register in the base dumps.

Simpler: in the base, arm3's store is `(set (mem/s:HI (plus (reg 72) (const_int 48))) (reg/v:HI 121))` at .rtl. Let me check .cse, .combine, .sched for what reg 121's set looks like and whether the store operand became a const.

Let me grep for "const_int 48" near.
