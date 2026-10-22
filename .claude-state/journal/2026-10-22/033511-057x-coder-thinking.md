---
ts: 2026-10-22T09:35:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_i3ULgBabAGR4NnywusCO
---
Not it either. Let me search cse.c for where a REG is replaced by a constant — the `qty_const` mechanism ("qty_const[reg_qty[REGNO(addr)]]")! That's cse's "quantity" tracking of constants.

Look at line 5043: `if (GET_CODE (addr) == REG && ... qty_const[reg_qty[REGNO(addr)]] != 0) addr = qty_const[...]` — so cse tracks a reg's constant value in `qty_const` and substitutes it.

Where is qty_const set? In cse's main loop, for a SET of a reg to a constant, cse records the quantity. Let me find where qty_const is assigned.

Also relevant: the moves.md note "cse: single-set const addr r73 folded into lone use" — so cse folds a constant into a lone use.

Let me grep for qty_const assignments.
