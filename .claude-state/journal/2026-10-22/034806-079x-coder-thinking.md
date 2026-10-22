---
ts: 2026-10-22T09:48:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_fndQGVejU5DybU4QFWbI
---
v02: the final add is STILL "addu v0,v0,a1" (index first) — so using p twice did NOT prevent the substitution (only the frame grew by 8 bytes because p became callee-saved).

So the "lone use" hypothesis is wrong for this case: the substitution happens regardless.

Hmm. So how did the target keep the pointer as a reg?

Wait... maybe the target DIDN'T keep it as a reg. Maybe in the target, the address tree was (plus (symbol_ref) (reg idx)) as well, and combine did NOT swap it because combine didn't process that insn — the difference being in *which insn* combine tried to combine!

In ours, combine swapped the FINAL add's address. Why did combine touch the final add but not the newval load? Because combine tries to combine the final add with the shift insn (e.g. `sll v0,v0,3` + `addu`), and in doing so it calls simplify_rtx on the address → the swap.

In the target, the final add was also next to a shift insn ("sll v0,v0,0x3" then "addu v0,a1,v0") — so combine would have tried the same combination. Hmm, but maybe in the target, combine's try failed and the tree was restored (the dump showed the swapped form in the .combine dump = combine's in-progress state, but the final state after undo = symbol first) — wait, but OUR final asm has the swapped form (index first) — so our combination was ACCEPTED, whereas the target's was REJECTED (and thus reverted to symbol-first = pointer-first).

That's a much better hypothesis! Combine's swap is a side effect of a combine attempt; if the combination is rejected, combine undoes the changes → the tree returns to (plus (symbol) (reg)).

So in the target, combine's attempt to combine the shift+add FAILED (or wasn't tried), leaving the original order (pointer first). In ours, it succeeded.

What does combine try here? The insn `(set (reg 113) (mem/s:HI (plus (symbol_ref) (reg 118))))` where 118 = shift. Combine might try to combine the shift into the address (a "shift by 3 into the address" pattern: `sll v0,v0,3; addu` → could be folded into a scaled address?). Or combine tries (plus (symbol) (mult x 8)) → make_compound_operation converts the ASHIFT to a MULT inside the address (as we saw in make_compound_operation's ASHIFT case: "Convert shifts by constants into multiplications if inside an address")!

Look: make_compound_operation(x, MEM) — when the address contains an ASHIFT, it converts it to MULT. But our address contains (reg 118) — a REG — not an inline ASHIFT. Hmm.

Hmm, but the REG_EQUAL note on 118 says (mult 88 8) — combine can use that note to know that 118 = mult 88 8, and then it can build the address as (plus (symbol) (mult 88 8)) — a compound operation — and try to combine the shift insn into the address (deleting the shift insn!). If that combination succeeds, the shift insn is deleted... but our asm still HAS the shift insn (sll v0,v0,3) and the add. So the combination didn't delete it.

Hmm, but the swap persisted. So combine's simplify_rtx swap happened and was NOT undone (the combination was accepted, or the swap was applied to the tree permanently).

OK, let me look at the actual combine code path that would swap our address. Since simplify_rtx is called from many places in combine, and the swap is at the top of simplify_rtx, ANY call to simplify_rtx on the address (plus (symbol) (reg)) swaps it. And combine calls simplify_rtx on the SET_SRC of insns it tries to combine.

In the target, the same insn exists with the same shape... so why no swap there? Unless in the target, the address was (plus (symbol) (reg)) but the *other* operand order... hmm, in the target the tree must have been (plus (symbol) (reg)) too (symbol first, since the asm has the symbol first).

So in the target combine didn't call simplify_rtx on that address (or the result was undone).

What could differ? The REGISTER ALLOCATION context: combine's decisions depend on the insn's operands and the surrounding insns. Our body might differ from the target's original source in ways that change combine's behavior (e.g. the number of insns before, the pseudo numbers, etc.).

Hmm! Wait. What about the pseudo NUMBERS? Combine's decisions can depend on reg numbers? Unlikely.

What differs between our def and the original source? The original source (as decompiled) is what we have — with the launder. The launder's asm is what makes the target's asm. The project concluded the launder is NEEDED (i.e. without it, the asm differs). So the question is whether some OTHER spelling achieves the same.

Given the analysis, the key difference is: with the launder, p is a hard-register pseudo → the address tree is (plus (reg p) (reg idx)) → combine's simplify_rtx doesn't swap (neither operand is a constant) → "addu v0,a1,v0" ✓.

Without the launder, p's value is a constant → the tree is (plus (symbol) (reg idx)) → combine swaps → "addu v0,v0,a1".

So we need p to be a REG at combine time but NOT a hard-register-pinned pseudo... Hmm, but any reg would do! The problem is only that expand/cse substitutes the constant.

Hmm, but hold on: WHERE does the substitution happen? I claimed expand (since the .rtl dump has the symbol). Let me verify that the .rtl dump really has the symbol in the address — yes: insn 190 in .rtl: `(set (reg/v:HI 113) (mem/s:HI (plus:SI (symbol_ref:SI ("D_80195AF6")) (reg:SI 118))))`.

Hmm! Interesting: the address in the .rtl dump is (plus (symbol) (reg 118)) — symbol FIRST. So at expand time, the pointer was ALREADY the symbol.

Hmm, so what if expand's substitution is exactly the "cse-const-addr" thing? Well, whatever.

NEW IDEA: what if the pointer is not a local variable but the address is computed from the symbol directly, and the *index* is the second operand — the tree would be (plus (symbol) (reg idx)) — same as now. No.

NEW IDEA 2: What if we could make the *first* operand of the plus be a REG by adding 0 to the symbol: e.g. `((u8 *)p + 0 + off + 4)`? The tree: (plus (plus (plus (reg p) 0) off) 4) → the (plus (reg p) 0) folds to (reg p) → the tree becomes (plus (reg p) (reg off))! But then expand would substitute p's constant → (plus (symbol) (reg off)) again. Hmm, same.

The substitution is the problem. UNLESS the substitution only happens when the reg is used in a "simple" way.

Let me now actually find the substitution code. It's in expand.c (not available) — but maybe I can find it in the papermario gcc tree under a different name? No expand.c there either. Hmm, weird: the papermario tree has 119 .c files but no expand.c? Let me list them.

Actually — maybe the substitution is in the FRONT END (c-type.c), which IS available! Let me grep c-type.c for the pattern where a VAR_DECL with a constant initializer is folded.

In gcc 2.7's c-type.c, function `expand_expr`, case VAR_DECL:

```c
    case VAR_DECL:
      ...
      /* Handle the case of a variable that is not initialized... */
      ...
      if (TREE_CODE (decl) == VAR_DECL && ...)
```

Let me grep.
