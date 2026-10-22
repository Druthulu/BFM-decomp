---
ts: 2026-10-22T12:51:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_bdlf3DOFzerPc3eV8z2C
---
`equiv_constant` uses `qty_const[reg_qty[REGNO(x)]]` — the quantity-based constant of a pseudo. `reg_qty` = the number of SETs of the pseudo. `qty_const[pseudo]` is set when the pseudo has a single set to a constant.

So: a pseudo with ONE set to a constant → qty_const → equiv_constant returns the constant → cse replaces the reg with the constant → the plus folds into an address → lui/addiu with addend.

With TWO sets, qty_const is not set (in cse.c, `qty_const` is set only when the pseudo's quantity is 1 — let me verify).

Let me look at where qty_const is assigned in cse.c.
