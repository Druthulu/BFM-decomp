---
ts: 2026-10-22T09:59:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_O44Hknn2xYspXPdkD0XV
---
This is cse's table element. The reg_equiv substitution is elsewhere. In gcc 2.7's cse.c, the "reg_equiv" mechanism for constants is `record_eq_reg` with the `reg_equiv` array (in cse.c: `reg_equiv[regno]`).

Let me look at record_eq_reg in cse.c — find "record_eq_reg" definition. Earlier grep showed only make_regs_eqv. Let me grep "reg_equiv" more broadly: the earlier grep showed only delete_reg_equiv lines. Hmm! So cse.c in this reference copy doesn't have a reg_equiv array — instead it has the "qty_const" mechanism and `make_regs_eqv`.

So the "forward scan" that folds the constant into the use is probably the `qty_const` mechanism + `simplify_addr`/`fold_rtx` in cse's main loop, or the class-based forwarding: cse's main loop, when it finds an insn whose source is a REG in a class with a constant, replaces the source with the constant (this is cse's "forwarding" of constants to uses).

The key question: is there a use-count condition? In cse's main loop there's the code:

```c
	  /* If we have a set of a reg to a constant, and the reg is used
	     only once, we can forward the constant ... */
```

Let me look at cse.c's main loop for the forwarding of a constant to a use. Search for "forward" in cse.c.
