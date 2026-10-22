---
ts: 2026-10-22T12:45:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ClfrCM8Gm1HAvbaRb6LT
---
This is find_best_addr for memory operands. Not our case (our case is a PLUS in a register, not a memory address).

The fold of `it` (pseudo = symbol_ref) into the plus: that's in cse's `cse_basic_block` → `simplify_gen_binary`? Or in `cse.c`'s handling: cse has a step where a register whose value is a constant gets replaced.

Let me look for where cse replaces a reg with a constant: in cse.c, `cse_basic_block` has:

```c
	  /* If we are looking at a constant, ... */
	  if (CONSTANT_P (x) && ! ...
```
Hmm, let me search for "cse_lookup" and "exp_equiv".

Actually the more likely place: `simplify_gen_binary` in simplify.c calls `fold` and also there's `cse.c`'s `simplify_plus_minus` (line 650 declared!). Let me read simplify_plus_minus — that's for PLUS/MINUS with a constant and a register that has a known value.

Let me read it.
