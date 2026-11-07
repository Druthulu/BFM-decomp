---
ts: 2026-11-06T11:56:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PKs3uzZGKzvwR4xaTQPj
---
My sed messed up (it duplicated the store and removed the wrong one — `sh v0,16(s0)` appears twice and the register allocation changed). The sed logic was flawed: the first substitution inserted a store before the reload, and the second substitution removed the original 0x10 store... but it also matched wrong.

Let me write y01 properly with a Python script or by hand. Let me just write the file directly.

Target order of the sh stores: 16, 12, 22, 18, 14, 20.
I'll move the first `sh 16` to between the sb+6 and the lbu+6, and remove it from its original place.

Let me write y01.c by hand.
