---
ts: 2026-10-22T16:20:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SOSWgEVjiZZ1oCuFivjf
---
The `.jump` dump (after jump1) shows EQ(72,73) = (it,p) — the target order! Then the `.cse` dump (after cse1) shows EQ(73,72) = (p,it) — cse1 swapped it. So **cse1's fold_rtx swaps the comparison operands**. Why? Because of the REG_EQUAL notes: p has REG_EQUAL (plus symbol K), it has REG_EQUAL symbol. cse's fold_rtx for a comparison probably tries to fold and ends up swapping to put the "more complex" operand first, or it canonicalizes constants.

So the target's compiler did NOT have the swap → the target's C had different REG_EQUALs such that cse didn't swap. The cse swap is likely because it folds `it` (symbol B) and `p` (symbol A + K) into constants for the comparison? Actually in cse's `fold_rtx`, when it encounters `(eq (reg p) (reg it))`, it substitutes the REG_EQUAL of each: (plus symbolA K) vs (symbolB). It then may swap the operands so that... hmm.

Alternatively, the swap may be in `simplify_comparison`/`fold_rtx`'s "if one operand is a constant, put it second" — neither is a constant after substitution (symbol+const is not a constant because the symbol's value is unknown at compile time? Actually symbol_ref + const is a valid constant expression (an address), but cse's `fold_rtx` only folds if the result is a *constant* (`CONST_INT`), not a symbol. So no folding.

Why swap then? In cse.c's fold_rtx, for a comparison with two registers, there's:
```
      /* Put the operand with the smaller register number first? */
```
Hmm. Or `rtx_equal_p` canonicalization: cse's `lookup_as_function`/`fold_rtx` for EQ might swap operands to normalize for the equivalence hash table.

Whatever the cause, empirically the swap happens in cse1 when both operands have REG_EQUALs? Let me test: does the swap happen if one operand has no REG_EQUAL? In the target, the final code has EQ(it,p) — meaning cse1 did NOT swap in the target's build. But the target's C is compiled with the same compiler... so the target's RTL at jump1 must have been EQ(p,it) (swapped), so that cse1's swap makes it EQ(it,p). I.e., the target's C at expand produced NE(p,it) → invert → EQ(p,it)? Wait, the invert in .jump gave EQ(72,73) from the C `it == p` (NE(72,73)). So invert produced EQ(72,73) = same order (no swap). Then cse swapped to (73,72).

So: target's final EQ(it,p) = (72,73) means after cse1's swap, the pre-cse order was (73,72) = (p,it) = EQ(p,it) at jump1. That comes from C `if (p == it)` → NE(p,it) → invert → EQ(p,it) = (73,72)... wait with r1's numbering it=72, p=73: C `p == it` → NE(73,72) → invert → EQ(73,72) → cse swaps → EQ(72,73) = (it,p) = target! 

So q14 (`p == it`) SHOULD give the target. But q14 scored 1 with beq a0,v1 — same as q9. Hmm, but q14 was built on q9's declaration order (`s32 p; s32 it;` → p=72, it=73). Let's redo the logic with q9's numbering: p=72, it=73. C `p == it` → NE(72,73) → invert → EQ(72,73) → cse swaps → EQ(73,72) = (it,p) = target! So q14 should also be target.

Unless the invert DOES swap in some cases. Let me just dump q14 and see. Maybe q14's score-1 diff is a *different* instruction. I did check q14's diff: it's the beq, mine beq a0,v1 vs target beq v1,a0 — the same. Hmm.

Let me dump q14's .jump and .cse to see the orders. That will settle it.
