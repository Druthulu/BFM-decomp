---
ts: 2026-10-22T09:35:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_WLkKXB73HWmiipRoylTd
---
This is cse's `simplify_addr` — the function that simplifies an address: if the base REG has a constant equivalent (qty_const), it replaces the base with the constant!

So: cse replaces the pointer pseudo with the symbol_ref in the address → giving (plus (symbol_ref) (reg idx)) → then reload's commutative swap puts the symbol second.

The key: `qty_const` is set when a reg is set to a constant and cse decides to record it. Let me find where qty_const is SET (not read). Let me grep "qty_const_insn" and the assignment.

Look at line 816 (init) and search for "qty_const_insn[q] =".
