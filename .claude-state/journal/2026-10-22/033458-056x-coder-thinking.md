---
ts: 2026-10-22T09:34:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_8KzxAnXPQSlTprh8AFmI
---
Interesting: cse.c in this reference copy has make_regs_eqv at 826. The moves.md note says "cse make_regs_eqv (cse.c:840): iVar1 outlives t -> canonical". So this reference copy is the actual source used.

Now, where does cse replace a reg by a constant? Let me look at cse.c's main loop for the "set reg to constant" handling. Search for "SET_SRC (x)) == SYMBOL_REF" or "CONSTANT_P (SET_SRC".

Let me grep for "SYMBOL_REF" in cse.c.
