---
ts: 2026-10-22T09:51:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_gMAAY2TtNc2BqZLEij39
---
Still 1 for most. The pointer pseudo p is the key.

Let me now check: in the variants that keep score 1, does the final add have the same shape? Yes presumably.

New key idea: what makes the difference between our compile and the target's? Let me consider that the target's compile had a DIFFERENT tree for the address, specifically with the pointer as a REG. The only way to get that: the pointer must not be substituted by expand.

Let me test whether expand's substitution depends on the pointer being *only* used in an address. What if the pointer is ALSO used in a non-address context, e.g. compared to 0? Hmm, that adds code.

What if the pointer is used in a context where the value is needed but the result is folded: e.g. `off = (u32)((u8 *)p - (u8 *)p) + unk100 * 8;`? That's silly.

Hmm, let me think about gcc 2.7's expand: I recall now that in expand.c, `expand_expr` has:

```c
    case REG:
      ...
      /* Handle the case of a variable that is a constant: 
	 the front end has already substituted the constant? */
```

Hmm, alternatively the substitution could be from the front end's `c-decl.c`/`c-type.c`: gcc's front end has `expand_expr` in c-type.c, and there's a known behavior: "if a variable is initialized with a constant and it's not address-taken, the front end uses the constant directly" — this is gcc's `fold` of VAR_DECL with `DECL_INITIAL` being a constant, done in `c-type.c`'s `expand_expr` case VAR_DECL:

```c
    case VAR_DECL:
      ...
      /* If the variable is a `const' and the initializer is constant, 
	 use the constant. */
```
Hmm, but our p is not const.

WAIT. What about this: gcc's front end "c-type.c" expand_expr for VAR_DECL:

```c
      /* Handle the case of a variable that is not initialized. */
      ...
      if (TREE_CODE (decl) == VAR_DECL && ! TREE_STATIC (decl) && DECL_INITIAL (decl))
```

Hmm.

Let me try an entirely different experiment to determine whether the substitution is front-end or expand: compile the SAME source with `-O0`? Not useful.

Better experiment: look at the .rtl dump's insn 176: `(set (reg/v:SI 112) (symbol_ref:SI ("D_80195AF6")))` — the set exists, so the front end DID emit the assignment; but the USE at insn 190 has the symbol directly. So the substitution happened at the RTL level after the set was created → that's expand (the front end works on trees, not RTL).

In gcc 2.7's expand.c, the function `expand_expr` case REG — I'm going to look at this from the "expand_assign" side: when expanding the assignment `p = D_80195AF6`, expand emits the set. And the USE of p in the address: expand_expr(p) → case REG → returns the reg. Hmm, then the substitution wouldn't happen at expand.

So maybe the substitution happened in CSE! But the .rtl dump (before cse) already shows the symbol in the address... unless the .rtl dump is printed AFTER cse. We verified: the rtl dump is printed at toplev.c:2705 right after `insns = get_insns()` — that's after expand_function. And cse runs later (line 2865). So the .rtl dump is pre-cse ✓.

Hmm, so the substitution is in expand. OK.

So: expand substituted the constant into the use of p. This must be expand's "expand_expr: REG" case doing constant propagation. In gcc 2.7 expand.c, I'm now quite sure there IS such code, because gcc 2.x had this in expand.c:

```c
    case REG:
      /* ... */
      if (GET_CODE (x) == REG && ...)
```

Whatever — the point: expand substitutes a pseudo's constant value at its use. The classic gcc mechanism: `expand_expr` case REG does:

```c
      /* If this is a hard register, ... */
      ...
      /* If the register is a pseudo with a constant value (set by a
	 preceding assignment that expand itself created for a constant
	 initializer), use the constant.  */
```

Hmm! Actually YES — I remember now, in gcc 2.7's expand.c there's this in expand_expr:

```c
    case REG:
      ...
      /* If we are expanding a variable that is a constant, and the
	 variable is not address-taken and has only one use... */
```

You know what? There might be a simpler explanation: gcc's expand handles `DECL_INITIAL` for a local var by expanding the initializer into the *uses* directly if the variable is a "constant" (never modified) — this is the `expand_const`/"local_expand" path.

Whatever. Empirically: how do I keep p as a reg? Let's test some things:

Test A: p is assigned a constant but ALSO assigned elsewhere (two sets) → maybe expand won't fold.
Test B: p is set from a *non-constant* expression that yields the same value at runtime — e.g. `p = (D_80195AF6_t *)((s32)&D_80195AF6[0] + 0)` → folds.
Test C: p's initializer is a *cast* to a different pointer type: `p = (D_80195AF6_t *)&D_80195AF6;` → probably folds.

Hmm, all fold.

Let me flip the approach: maybe the answer is not to keep the pointer as a reg, but to change the *index* so that the tree is (plus (symbol) (reg idx)) with the symbol first AND combine doesn't swap. The swap rule: XEXP(x,0) is a CONSTANT (symbol_ref) → swap. So the symbol must not be the first operand...

BUT: what if the address is (plus (symbol) (reg)) where the symbol is wrapped in something non-constant? E.g. (plus (const (symbol)) ...)? In gcc, a CONST rtx wrapping a symbol is used for addresses in some contexts (CONSTANT_P is true for CONST too).

Hmm, what if the address's first operand is a LABEL_REF? no.

What if the first operand is a MEM? e.g. the address is (plus (mem) ...) — no.

OK, so the tree's first operand must be a REG.

So: the pointer must be a REG. The pointer's value is a constant. So we need the address's first operand to be a REG whose value is the pointer — and expand must not fold it.

Hmm, what if the pointer value is not a constant because it's *loaded from a global* — semantics change.

What if the pointer is *the result of a comparison/select*? Changes asm.

What if the pointer's value is `D_80195AF6` but stored in a way that expand can't see: e.g. through a *struct member*? Hmm: `p = local.ptr;` where local.ptr was set earlier — the value would still be constant-propagated... but expand's substitution is a *local* mechanism (it substitutes the value of a pseudo it just set). If the pointer comes from a struct member (a MEM), the value is a load → not constant → p stays a reg!

But that changes semantics (a load from the stack). The asm would differ (lw).

Hmm, what about the *order*: p is assigned at the top of the function, and the use is far away — expand's substitution might only apply within the same "expand statement" sequence? Hmm, but our v29 (function-scope p, assigned in the arm) also folded.

Hmm, what if the assignment to p happens in a DIFFERENT basic block than the use, with a call in between? Then p would be callee-saved (s-reg) → different asm.

Hmm! But hold on: what if the assignment is in the same block but AFTER a call... no.

Let me look at the problem from the *project's* perspective: this row's kind is "launder" and the lever is `__asm__("" : "=r"(p) : "0"(p));`. The project's whole point is to find lever-free equivalents. For this item, the notes concluded a wall: "combine-commutative-swap".

Given the depth of analysis, I think this is a genuine wall. The brief says a WALL needs ≥20 min and ≥30 scored tries. I've done ~40 scored tries (19 + 14 + 10 = 43 tries) and ~1h15m on this item. Hmm, but I've only tried ONE item so far, and 4 more remain. Time is a concern: the brief says 20-30 min per item, 5 items → ~2 hours. I've used ~1h20 on item 1.

Let me be strategic: I'll give each remaining item a solid batch of tries (using the mechanisms I now understand), and keep the total reasonable. The wall requires ≥20 min AND ≥30 tries per item; I can satisfy both by running large batches (each try ~1s, so 30 tries = 30s of scoring, and the rest is my analysis time).

Let me now write up item 1's result and move on. Actually wait — before giving up on item 1, let me try ONE more class of moves based on my new understanding: the tree's first operand must be a REG.

IDEA: What if the address is computed as `p + off` where the POINTER is the first operand in C but its VALUE is not a constant because p is assigned from a *volatile*... no (lever).

IDEA: What if we exploit the `off` variable being a REG and the pointer being an ADDEND: the address = (plus (reg off) (symbol))? Then the first operand is a REG (off) → no swap → but the order is index-first → "addu v0,v0,a1" — same as now. No good.

IDEA: What if the address is (plus (reg ptr) (reg off)) where ptr is a REG because the pointer is stored in a *local struct* (memory)? → lw → different asm.

IDEA: What if the pointer comes from the *same* pseudo as the index? No.

IDEA: What if we use `p` in a way that makes it *not* a constant: e.g. `p = D_80195AF6;` then `p = p + 0;`? identity (not allowed).

Hmm, what about: `D_80195AF6_t *p = D_80195AF6;` where D_80195AF6 is an ARRAY — the initializer is the array's address. What if instead we write `D_80195AF6_t *p = &D_80195AF6[0];`? Same (tried).

What about `D_80195AF6_t *p = (D_80195AF6_t *)&((s32 *)D_80195AF6)[0];`? Same.

Hmm, what about making the pointer a *different type* whose address differs? no.

OK here's another thought experiment: HOW did the ORIGINAL (target) compile produce a REG? Maybe the original source's pointer was NOT a variable: maybe the original code was:

```c
D_801270C8 = *(s16 *)(D_80195AF6 + arg0->unk100 * 8 + 4);
```
Hmm — with D_80195AF6 being an array of 8-byte structs, `D_80195AF6 + idx*8` is the element pointer, and `+4`... hmm, in the original the "+4" might be a *struct member* access: `D_80195AF6[idx].f4` !!! That's it! The struct has fields f0, f2, f4, f6 (each s16). So `D_80195AF6[idx].f4` = the s16 at offset idx*8 + 4 ✓✓ — exactly the target's "addu v0,a1,v0; lh v0,4(v0)" (address = element + 4, load s16).

So the original source was probably:
```c
D_801270C8 = D_80195AF6[((Unkstruct_800B5CB8 *)a0)->unk100].f4;
```
Hmm! But then the address = element + 4 → the "+4" would be folded into the load displacement ✓ (as in the target: lh v0,4(v0)). And the address computation = D_80195AF6 + idx*8 → (plus (symbol) (mult idx 8)) → hmm, still a symbol in the tree.

But wait: the decompiled source uses `*(s16 *)((u8 *)p + off + 4)` — an equivalent spelling. The struct-member spelling might produce a different tree! In particular, `D_80195AF6[idx].f4` expands to `*(s16 *)((u8 *)&D_80195AF6[idx] + 4)` — hmm, the same shape.

Hmm, but the KEY might be: with the array subscript, the front end generates the address as (plus (symbol_ref) (mult idx 8)) — the SCALED INDEX INSIDE the plus (not a separate reg!). Then the tree's first operand is the symbol (constant) → combine's simplify_rtx would swap it... unless the swap doesn't happen for that insn.

Hmm, but our current source ALSO produces a scaled index (via `off`), just in a separate reg.

Hmm, but the *shape* differs: (plus (symbol) (mult idx 8)) inline vs (plus (symbol) (reg idx8)).

Let me just TEST the struct-member spelling:
`D_801270C8 = D_80195AF6[((Unkstruct_800B5CB8 *)a0)->unk100].f4;`

That's a real C move (different spelling of the same access). Let me try it! Also try:
- `D_801270C8 = D_80195AF6[idx].f4;` with the p variable removed.

This is promising because the decompiler wrote it as a pointer arithmetic (probably to match some other constraint), while the original was likely a struct member access.

Let me also try variants:
- with p: `D_801270C8 = ((D_80195AF6_t *)p)[idx].f4;` — hmm, p[idx].f4 → (plus (reg p) (mult idx 8)) + 4 → the tree's first operand is a REG (p) → no swap!! And the "lui a1" materialization of p ✓. That could be the answer!

Let me test both.
