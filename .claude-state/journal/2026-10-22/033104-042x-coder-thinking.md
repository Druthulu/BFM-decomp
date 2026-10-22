---
ts: 2026-10-22T09:31:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_0HWx3iegef0L4y8TP69S
---
No COMMUTATIVE macro in gcc 2.7.2 (it used `swappable_operand_p` / direct code). Let me search for the specific transformation: a PLUS where one operand is a MULT/SHIFT and the other is an address.

Search combine.c for "MULT" near "PLUS" or for the function `plus_op`? Let me grep for "GET_CODE (x) == MULT" or "ASHIFT".

Let me grep for "ashift" or "ASHIFT" in combine.c.
