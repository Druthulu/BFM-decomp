---
ts: 2026-10-22T11:48:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_i4ioHdUcg2xxnrZRqhIN
---
This is the `expand_expr` switch. The division case at 6744 goes to "binop" which uses `binoptab` → `expand_binop` → for TRUNC_DIV_SI with a constant operand, `expand_binop` calls `expand_mult`? Hmm.

The key: `expand_binop` in expr.c for TRUNC_DIV_SI:
```c
	  /* If we are dividing by a power of two, ... */
	  ...
	  else
	    {
	      /* Use the multiply algorithm.  */
	      ...
	    }
```

Let me look at expand_binop's TRUNC_DIV_SI case.

Hmm, this is a deep rabbit hole and time is short (06:15). Let me STOP the analysis and START experimenting, using the Edit+sc.sh loop.

Let me be decisive about which experiments to run.

=== ITEM 4 EXPERIMENTS ===
The residual: the magic constant's birth position + register allocation.

Variant families:
A. Make the vol chain's division a compound (w4) [control, 14]
B. Make the sx chain's division a compound too.
C. Give vol a second set via a copy.
D. Reorder the chains.
E. Change the `av` if to a ternary.
F. Change the declaration order of vol/sx.

Let me create 8 files and iterate.

=== Actually, hold on. Let me reconsider the whole item-4 situation from the "C0505 catalog" angle mentioned in the brief: "real C moves only (C0505 catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse)".

Let me read the C0505 cookbook entry — it's the lever-removal move catalog! That's exactly what I need. Let me read it.

cookbook/C0505.md.
