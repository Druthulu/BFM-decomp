---
ts: 2026-11-06T09:11:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TxjHYe5mPSAYhlNbjBRm
---
All are void defs with extern void decls. So probably all are "value must reach v0" cases. But maybe the value is used differently (e.g., a call result must go to a callee-saved reg).

Let me read the defs. Item 2: md_SC05_026 func_801F0C4C at 367.
