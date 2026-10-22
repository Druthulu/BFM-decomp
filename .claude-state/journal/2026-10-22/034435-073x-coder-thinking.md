---
ts: 2026-10-22T09:44:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_apPMmKm6ZbSZSelfMSiD
---
FOUND IT! At the top of `simplify_rtx`:

```c
  /* If this is a commutative operation, put a constant last and a complex
     expression first.  We don't need to do this for comparisons here.  */
  if (GET_RTX_CLASS (code) == 'c'
      && ((CONSTANT_P (XEXP (x, 0)) && GET_CODE (XEXP (x, 1)) != CONST_INT)
	  || (GET_RTX_CLASS (GET_CODE (XEXP (x, 0))) == 'o'
	      && GET_RTX_CLASS (GET_CODE (XEXP (x, 1))) != 'o')
	  || ...))
    { swap }
```

For our tree (plus (symbol_ref) (reg 118)): XEXP(x,0) = symbol_ref → CONSTANT_P(symbol_ref) is TRUE (SYMBOL_REF is a constant in gcc's CONSTANT_P? CONSTANT_P covers CONST_INT, CONST, SYMBOL_REF, LABEL_REF, CONST_DOUBLE). And GET_CODE(XEXP(x,1)) != CONST_INT (it's a REG) → so the condition holds → SWAP → (plus (reg 118) (symbol_ref)) ✓✓✓ That's exactly the swap we observed!

And the newval address (plus (symbol_ref) (reg idx)) — the same rule would apply! Hmm, why didn't the newval address get swapped? Because simplify_rtx is applied to... hmm. Maybe because for the newval address the tree was (plus (symbol_ref) (reg)) too and it should have been swapped as well. But the target shows "addu at,at,v0" = symbol first!

Hmm! Unless the newval address's tree was NOT (plus symbol reg) but (plus (reg at) (reg idx)) — i.e. the symbol was already in a reg at combine time. Hmm, but then the "lui at" materialization...

Wait: maybe for the newval, the address was formed differently: `D_80195AF6[idx].f0` → the front end generates the address as (plus (symbol_ref) (mult idx 8)) → then expand converts the mult to a shift... and the shift is *inside* the plus: (plus (symbol) (ashift idx 3))? Then simplify_rtx's swap condition: XEXP(x,0) = symbol_ref → CONSTANT_P → swap → (plus (ashift) (symbol))?? But the target shows the newval add as (plus symbol idx) — symbol first.

Hmm, confusing. Unless in the target the newval address's index was NOT scaled: we saw "addu at,at,v0" where v0 = unk100*8 (computed in the delay slot) — so the index IS scaled but it's in a REG (v0), so the tree was (plus (symbol) (reg v0)) → simplify_rtx swaps it → (plus (reg v0) (symbol)) → "addu at,v0,at"?? But the target shows "addu at,at,v0"!

Hmm, so the target's newval add was NOT swapped. Why? Because simplify_rtx's swap happens on the tree — but maybe the address's plus was inside a MEM and simplify_rtx wasn't applied to it, or the insn was already in a form that combine didn't touch (combine's try_combine only touches insns it tries to combine).

AH, that's the key: combine only *simplifies* insns it attempts to combine. The final add insn (the one with the address) got combined/simplified; the newval load insn maybe wasn't touched by combine.

Hmm, but both are loads with the same shape.

Wait, actually, maybe the difference: the final add's tree at combine time was (plus (symbol_ref) (reg 118)) where 118 = the shift result — and the *load* insn is `(set (reg 113) (mem/s:HI (plus (symbol) (reg 118))))` — a 16-bit load. The newval load is `(set (reg 122) (sign_extend (mem/s:HI (plus (symbol) (reg idx)))))`.

Hmm, both are MEMs.

Honestly, the difference might be that the final add's insn was the one combine tried to combine (e.g. with the shift insn) and in doing so it called simplify_rtx on the address → swapping. The newval load wasn't combined.

So: the swap happens in combine's simplify_rtx when it processes the final address. To avoid it, the address's tree must not have a CONSTANT first operand at that point. I.e. the pointer must be a REG (not a symbol) at combine time.

So the question remains: how to keep the pointer as a REG in the address, lever-free?

Since the symbol_ref was in the tree already at the .rtl dump (post-expand), the substitution happened in expand (or the front end). If we could make expand NOT substitute, the tree would be (plus (reg p) (reg idx)) → no swap → "addu v0,a1,v0" ✓.

How does expand substitute? In gcc 2.7's expand.c, the REG case of expand_expr:

```c
    case REG:
      ...
      /* If this is a hard register, ... */
      ...
      /* Handle the case of a variable that is a constant: 
	 ... */
```
I recall in gcc 2.7 expand.c:

```c
    case REG:
      /* ...
	 If we are expanding a variable that has a constant value,
	 use the constant.  */
      if (GET_CODE (x) == REG && ...)
```
Hmm, actually I strongly suspect the substitution is done by the C front end: in c-type.c, `expand_expr` for a VAR_DECL with a constant initializer... no, the front end doesn't do that.

BUT: gcc 2.7's expand.c DOES have this in `expand_expr` (case REG):

```c
    case REG:
      /* ... */
#ifdef HAVE_cc0
      ...
#endif
      /* Handle the case of a variable that is a constant:  */
      ...
      if (GET_CODE (x) == REG && !HARD_REGNO_P(...))
```

I can't recall. Let me EXPERIMENT: does the substitution depend on the number of uses of p? Let me test the variant where p is used twice (newval through p) and check the .rtl dump / the asm.

Actually, let me just run the experiment: variant with `s16 newval = p[idx].f0;`.

Let me write the batch tester now. I'll create a runner script that scores a list of files, and a generator for variants.

Let me be efficient: create the variant files with a Python script (textual replacements), then score them with a loop.

Note the time budget: I've used ~50 min so far on item 1 (of 5). The brief wants 20-30 min per item, and I have 5 items. I've spent a lot on item 1. Let me speed up: run batches of variants (each ~1s) and analyze in bulk.

Let me write the generator + scorer.
