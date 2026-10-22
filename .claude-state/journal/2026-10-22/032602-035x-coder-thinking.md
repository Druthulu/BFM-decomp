---
ts: 2026-10-22T09:26:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ViTUY7SEq7oWyOTaXwp5
---
Confirmed: a1 = D_80195AF6 (the pointer), and the target's add is `addu v0,a1,v0` (pointer first). The `at` materialization is for the newval load, where the tree is (plus (symbol_ref) v0) → `addu at,at,v0` — pointer first there too, and NOT swapped!

Interesting!! In the target, the newval load's address add is (plus symbol_ref v0) → pointer first (symbol first!). But combine's canonicalization would move the constant to the second... yet here the symbol is FIRST and the reg SECOND, and it survived!

Hmm, so combine's canonicalization doesn't universally apply. Then why did OUR tree (plus (symbol_ref) (reg 118)) become (plus (reg 118) (symbol_ref))?

Wait, maybe the swap in ours isn't canonicalization but the "convert mult to shift" transformation: combine sees (plus (symbol_ref) (mult x 8)) and rewrites the mult into a shift: gcc 2.7 combine has a rule that turns (plus (mult x 2^n) y) into (plus (lsh x n) y) — hmm, but our tree at combine time (rtl dump) was (plus (symbol_ref) (reg 118)) with 118 already the ashift (REG_EQUAL mult 8). Then combine produced (plus (reg 118) (symbol_ref)).

But the target's newval add (plus (symbol_ref) (reg v0)) stayed pointer-first! In that case the second operand is a plain reg (not a shift). Hmm, but both are (plus symbol reg) shapes.

So the swap isn't a general "constant last" rule. It must be specific to the *shift* case! I bet combine has a rule for (plus (symbol_ref) (ashift x 3)) — the "address + scaled index" pattern — and it rewrites to (plus (ashift) (symbol))? That seems arbitrary.

Alternative: the swap happens in the pass that handles (plus (mem/s) ...) forms or in "reload" — the reload pass rewrites the insn operands when one is a constant address needing a register: for a commutative op, reload may swap operands so that the reload operand comes first? Hmm: in reload.c, `reload` handles the case where an operand must be in a register: for commutative ops, gcc has `commutative_op_p` and reload may swap to put the reload in the first operand. Actually YES — in reload.c there's this known code:

```c
	  /* If this is a commutative operation, and the first operand is
	     reloadable, and the second is not, swap them.  */
```
Hmm, but in our case the symbol_ref operand needs a reload (into a1) and it's currently SECOND. After the swap it became FIRST. So reload swapped them? But then the asm would print (plus reload-first) = "addu v0,v0,a1"? The reload operand is the symbol → reloaded into a1 → tree becomes (plus (reg 118) (reg a1)) → "addu v0,v0,a1" = ours.

And in the target, the newval load's tree (plus (symbol_ref) (reg v0)): the symbol also needs a reload into `at`... and it printed "addu at,at,v0" (symbol first). Hmm! So reload did NOT swap there.

Difference between the two cases: in the newval case the tree is (plus symbol reg) — symbol first, reg second. In our case (plus symbol reg) too! Both symbol first! Yet one swapped and one didn't.

Wait, our rtl dump showed insn 190: `(set (reg/v:HI 113) (mem/s:HI (plus:SI (symbol_ref:SI ("D_80195AF6")) (reg:SI 118))))` — symbol first, reg 118 second. And combine changed it to (plus (reg 118) (symbol_ref)).

So the swap happened in COMBINE, not reload. And the target's newval case: (plus symbol reg) survived combine... but the target's *final* add (plus a1 v0) — in the target, was the pointer a reg at combine time? The target's final add has a1 (a reg). So in the target, combine saw (plus (reg ptr) (reg idx)) — the pointer was a reg pseudo, NOT a symbol.

And the target's newval add (plus symbol v0) survived combine with symbol first — so combine does NOT canonicalize symbol-first in general.

So what's special about our insn 190 that made combine swap it? The second operand is 118 = (ashift 88 3) with REG_EQUAL (mult 88 8). Hmm! Maybe combine's rule: for (plus (symbol_ref) (mult x 8)) — the "address + scaled index" — combine has a specific transformation in gcc 2.7 for `x*8 + sym`? Hmm, but our tree at combine time already had the shift (ashift) not (mult).

Hmm, hold on: maybe the order in the rtl dump isn't what combine sees; combine runs multiple times (the .combine dump is after combine). Between the rtl dump and combine, there's... the rtl dump is after expand; combine is the first pass. So combine itself did it.

Combine has this in gcc 2.7.2 (I recall from the source, function combine_insns, the PLUS case):

```c
	    case PLUS:
	      ...
	      /* If we have a plus of a symbol and a shifted index... */
```

Alternatively, this could be the "plus (symbol) (mult)" → "plus (mult) (symbol)" rule tied to the `x + sym*2^n` pattern used for array indexing.

Let me just test empirically with a standalone file. That's the fastest path. Let me create a small test C file and compile it with the toolchain to see the operand order.

Test file:
```c
extern int A[100];
extern int B;
extern int idx;
int f(void) {
    int *p = A;
    int off = idx * 8;
    return *(short *)((char *)p + off + 4);
}
```
Compile with tools/bin/gcc-2.7.2-psx (driver?) — let me check the toolchain dir.

Then variants to find pointer-first.

Let me check what's in tools/bin/gcc-2.7.2-psx/.
