---
ts: 2026-10-22T09:29:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_4E0azLpBigij3hiGFIKw
---
Our asm matches the target except `addu v0,v0,a1` vs `addu v0,a1,v0`.

Both have `lui a1; addiu a1,a1,0` — so the pointer IS in a1 in ours too! Then the add should be (plus a1 v0) → "addu v0,a1,v0". But we got "addu v0,v0,a1" — so the reload put the symbol into a1 but the tree order is (index, pointer).

So the tree order is (plus (reg 118) (reg a1)) after reload, from (plus (reg 118) (symbol_ref)) — combine swapped symbol_ref to second position.

Now: WHY did combine swap in ours but not in the target? In the target, the tree at combine time must have been (plus (symbol_ref) (reg idx)) — symbol first — and it survived.

Wait, but in the target the final add has the pointer in a1 as a REG. If the tree had symbol_ref, the reload would put the symbol into a reg and print "addu v0,a1,v0" (symbol first) — the reload keeps the operand position! So in the target, the tree was (plus (symbol_ref) (reg idx)) and after reload it became (plus (reg a1) (reg idx)) → "addu v0,a1,v0". And in ours the tree was (plus (reg idx) (symbol_ref)) → "addu v0,v0,a1".

So the difference IS the tree order at combine time. And in ours combine swapped it (or expand did). The rtl dump (post-expand) showed ours as (plus (symbol_ref) (reg 118)) = symbol FIRST! And combine changed it to (plus (reg 118) (symbol_ref)).

So combine swapped. And in the target, combine did NOT swap (the symbol stayed first).

What distinguishes? In ours, the second operand 118 is a shift with REG_EQUAL (mult 88 8) — i.e., the plus is (symbol + x*8) — a SCALED INDEX addressing pattern! Combine has a specific rule for that: it recognizes `(plus (symbol_ref) (mult x 8))` and rewrites it as (plus (mult x 8) (symbol_ref))?? Hmm, why?

Actually! I remember now: gcc 2.7's combine.c has this code for PLUS:

```c
	    case PLUS:
	      ...
	      /* If we have (plus (mult x 2^n) y) where y is an address, ... */
```
Hmm.

Alternatively, maybe the relevant code is in combine's handling of `x*8 + sym` → the "scaled index" canonicalization, which in gcc is: for an address (plus (reg) (mult x 2^n)) the canonical form is (plus (mult x 2^n) (reg))?? Hmm, in modern gcc the canonical form for scaled index is (plus (reg base) (mult index 2^n)) — base first.

Let me look at it from the target's perspective: the target's tree kept (plus symbol idx) where idx = unk100*8 → the shift insn is `sll v0,v0,0x3` and then `addu v0,a1,v0`. So the target's tree is (plus symbol (shift)) — symbol first, shift second. So combine did NOT canonicalize to (shift, symbol).

Hmm, so in the target the tree at combine time was already (plus symbol shift) and combine left it. In ours it was (plus symbol shift) too (rtl dump) and combine changed it to (plus shift symbol).

Unless the rtl dump is not pre-combine but post-something. The dump file names: .i.rtl is the dump after "rtl" pass? In gcc 2.7.2, `-dr` = "rtl" dump which happens... Let me check the order of dumps in gcc 2.7: the "rtl" dump (-dr) is printed by `dump_rtl` after expand? Hmm, in gcc 2.7.2, `rtl.c`/`expand.c`... the dump "rtl" is produced in `compile_file` after `expand_function`? Actually the pass sequence in gcc 2.7: expand → ... The "rtl" dump flag is 'r' and is dumped by `dump_rtl (rtl_dump_file, ...)` in `compile_file` right after expand? Let me check the .combine dump to see if the .rtl dump's numbering is consistent (insn numbers match: rtl insn 184/190 vs combine insn 184/194 — similar numbers, so the rtl dump is just before combine).

OK so the tree at combine entry: (plus (symbol_ref) (reg 118)) where 118 = ashift(88,3).

Combine swapped it. Why? Let's look for gcc 2.7.2 combine.c code that swaps commutative operands. I'm now fairly convinced there IS such code, in `combine_insns`:

```c
	  /* If we are adding a constant to a memory address, ... */
```

Alternatively the swap could come from combine's `simplify_rtx` handling of PLUS with a MEM/address...

Hmm hold on. What about the possibility that the swap is NOT in combine but in the *expand* of the second pass... no, the dumps show it changed between .rtl and .combine.

Hmm, but careful: the .combine dump is dumped after combine; the .rtl dump after expand. Between them: nothing else? In gcc 2.7, the order is: expand → (flow analysis) → combine → cse → ... The .rtl dump might be after expand and before flow.

So yes, combine swapped it.

Let me now find gcc 2.7.2's combine.c rule. I recall now with more clarity! In gcc 2.7.2 combine.c there's this in the PLUS case:

```c
	    case PLUS:
	      if (GET_CODE (x) == CONST_INT && GET_CODE (y) != CONST_INT)
		{ x = y; y = const; }   /* put constant second */
```
That's the "constant second" rule for CONST_INT. But our constant is a SYMBOL_REF (an address), not CONST_INT.

But there's ALSO this famous rule in gcc (combine.c, function `simplify_rtx`? or in `combine_insns`):

```c
	  /* Recognize (plus (symbol_ref) (mult x 2^n)) and convert to
	     (plus (mult x 2^n) (symbol_ref))? */
```

I really should test empirically instead of guessing. Experiment plan (in the real body, since the standalone lab folded differently):

Try spellings that change the shape of the scaled-index add:
(a) `off` computed as `unk100 * 8` but the final address `((u8 *)p + off + 4)`.
(b) `((u8 *)p + off + 4)` where off is `u32`.
(c) `((u8 *)p + off + 4)` where p is `u8 *` (cast at decl).
(d) `((u8 *)p + (off + 4))`.
(e) `((u8 *)p + 4 + off)`.
(f) address via a temp pointer: `u8 *pa = (u8 *)p + off; D_801270C8 = *(s16 *)(pa + 4);`
(g) `D_801270C8 = *(s16 *)(p + off + 4);` with p as u8*.
(h) off = `unk100 << 3`.
(i) `*(s16 *)((u8 *)p + off + 4)` where the +4 is folded into off: off = unk100*8+4.
(j) Use a `long`/`int` cast of p: `*(s16 *)((u8 *)(s32)p + off + 4)`.

Let me write a batch runner and try ~20 variants quickly.

Also worth trying: making the pointer a real register by using it in two places — but as discussed, that changes the newval load's materialization. Actually wait: does it? Let's test: `s16 newval = p[unk100].f0;` — p is `D_80195AF6_t *` and `p[idx].f0` = *(s16*)((u8*)p + idx*sizeof(elem)). If the elem is 1 byte, the address = p + idx. The tree (plus (reg p) (reg idx)) → after reload, p's pseudo → a1 → "addu at,a1,v0"? but the target has "lui at; addu at,at,v0" — so in the target the newval address materialized its own symbol into `at` — meaning that expression was NOT through p.

So in the target, p is used ONLY at the end. Yet the tree there had the pointer as a REG (a1).

Hmm, so how does the pointer become a reg at combine time in the target? Because... the pseudo for p was created (p = D_80195AF6) and its value... in the target's compile, expand did NOT fold the constant into the address expression; it kept (reg p) and reload materialized p into a1 with lui+addiu. Then the tree is (plus (reg p) (reg idx)) → after reload (plus (reg a1) (reg idx)) → "addu v0,a1,v0" ✓.

In ours, expand DID fold the constant (symbol_ref) into the plus, and then combine swapped it.

Why the difference? Because in ours, the expression `(u8 *)p + off + 4` involves `off` — hmm.

Ohh! Maybe it's about the ORDER of the source terms: In ours the tree was (plus (symbol_ref) (reg 118)) — symbol first, meaning expand folded p's constant and kept the C order (p + off). Then combine swapped to put the symbol second.

In the target, the tree was (plus (reg p) (reg idx)) — the constant NOT folded by expand. Why not? Because expand folds constants only when the pseudo is a "constant reg" AND ... hmm, in the target p was maybe declared as `u8 *p = (u8 *)D_80195AF6;`? Or maybe p was assigned via a *cast* that prevented folding?

Alternatively the target's p might have been a **parameter**! But the signature is `void func_80184828(void *a0)` — one param. Hmm.

Alternatively: maybe in the target's original source, the final address expression did NOT use a pointer variable p at all, but rather a *different* constant expression, e.g.:

```c
D_801270C8 = *(s16 *)((u8 *)D_80195AF6 + unk100 * 8 + 4);
```
Hmm, that's the same constant.

Hmm, but the difference in fold behavior could come from the *cast*: `(u8 *)D_80195AF6` — expand's folding of a cast of a symbol into an address is standard.

Wait, maybe I should look at this from the *other* direction: in ours, who created the symbol_ref in the plus? The rtl dump at insn 190: `(set (reg/v:HI 113) (mem/s:HI (plus:SI (symbol_ref:SI ("D_80195AF6")) (reg:SI 118))))`. And insn 176: `(set (reg/v:SI 112) (symbol_ref:SI ("D_80195AF6")))` — a pseudo 112 set to the symbol, and 186: `(set (reg:SI 119) (symbol_ref ...))` with REG_EQUAL, and 188: `(set (reg:SI 120) (symbol_ref ...))` with REG_EQUAL.

So there are multiple pseudos set to the symbol: 112, 119, 120 (119 and 120 with REG_EQUAL notes = cse'd copies). And the plus at 190 uses symbol_ref directly rather than (reg 112)! Interesting — expand emitted the symbol_ref directly in the plus because the pseudo's value is a constant and expand does that substitution ("expand_expr REG case: if the reg has a constant value, use the constant").

Hmm, so in ours the substitution happened. In the target it didn't — maybe because in the target, the pseudo p had *two* uses (so expand kept it as a reg)? But we showed p is used once...

Unless in the target, p was used twice but one use was optimized away into the symbol (e.g. the newval load used p, and expand folded it). Hmm, if p had 2 uses, expand would keep the pseudo as a reg for BOTH uses → the newval load's address would be (plus (reg p) (reg idx)) → "addu at,a1,v0" (not "lui at; addu at,at,v0"). Target has the latter. Contradiction.

So in the target, p is used once and expand still kept it as a reg?! Then the pointer reg p was materialized by reload into a1 (lui+addiu). That's consistent with the target's "lui a1; addiu a1,a1,0" at the arm start.

So why does expand keep the reg in the target but substitute the constant in ours?

AH WAIT. Maybe the difference is the *cast* `(u8 *)p`! In ours: `(u8 *)p + off + 4` where p is `D_80195AF6_t *`. The cast to u8* is a no-op cast. Expand: for `(u8*)p + off`, expand_expr on the PLUS with a pointer operand: it does "convert to address" and may fold constants.

In the target maybe the source was `(u8 *)p + off + 4` too. Hmm.

OK, let me stop theorizing and start testing empirically with the real body — the try loop is fast. I'll try ~15 variants and observe. If the swap is combine's canonicalization of (plus (symbol) (scaled index)), maybe an unscaled index spelling avoids it: e.g. if off were not a multiple of 8, the address would be (plus symbol (reg)) — no shift — and combine might not swap. But we need the *8.

Alternatively maybe the swap is triggered by the *shift* (ashift) specifically: combine's rule might be "convert (plus (symbol) (mult x 8)) into (plus (mult x 8) (symbol))" for the "scaled index" canonical form, and our tree at combine time was (plus symbol (ashift)) → converted to (plus (ashift) symbol). The target's tree must have been (plus (reg p) (ashift)) — no symbol — so no conversion.

So the crux: make the pointer a REG at combine time. Since expand substitutes the constant when the pseudo's value is constant...

Hmm, what if p is NOT a constant but the code still yields the same asm? E.g., what if we write:

```c
D_80195AF6_t *p;
...
p = D_80195AF6;
```
Same.

What if p is assigned in a branch? e.g.
```c
if (x) p = D_80195AF6; else p = D_80195AF6;
```
→ phi → reg, but adds branches (asm changes).

Hmm, what if we make the pointer's value depend on a *runtime* value that is provably equal? Not without levers.

What about the *order* of the terms in C: `(u8 *)off + (u32)p`? Then the tree is (plus (reg off) (symbol_ref)) — symbol second already! Then combine's canonicalization (constant second) wouldn't change it, and the asm would be "addu v0,v0,a1" (index first) — same as ours. No.

Hmm! What about making the index appear as the base and the pointer as an offset: the asm "addu v0,a1,v0" means base=a1(pointer), offset=v0(index). Since both are regs, the order in the asm = the tree order.

So we need the tree (plus (reg ptr) (reg idx)). The ptr must be a reg at combine time.

Since expand substitutes constants into the address, maybe there's a spelling where expand does NOT substitute: e.g. when the pointer expression is not a simple constant but a *cast of a constant to a pointer* — hmm, same.

What about when the pointer variable's value is a constant but the variable is ALSO used elsewhere (so expand keeps the pseudo reg)? We showed p is used once...

BUT: what if we use p in the newval load in a way that produces the SAME asm as the target? The target's newval load: "lui at; addu at,at,v0; lh v0,0(at)" — the address = symbol + idx. If our source used `p[idx].f0` with p a reg, the address would be (plus (reg p) (reg idx)) → reload p into a reg → "addu at,a1,v0" — one instruction instead of two (lui+addiu+addu = 3 vs addu = 1+reload). Actually the reload of p into a1 would need lui+addiu somewhere → same count! Hmm: "lui a1; addiu a1,a1; addu at,a1,v0; lh v0,0(at)" = 4 insns vs target's "lui a1; addiu a1,a1; lui at; addu at,at,v0; lh v0,0(at)" = 5. The target has an extra lui at. So the target's newval address materialized its own copy → symbol_ref.

So in the target: the final add uses a reg (a1) and the newval uses a symbol (at).

If p were used twice (newval + final), the newval would use the same reg → one fewer lui → count mismatch (111 vs 112). So no.

Therefore: in the target, p (a reg) is used ONCE, and expand did NOT substitute the constant into the address expression. In ours, expand DID.

What's the difference? Let me look at gcc 2.7's expand_expr REG case:

```c
    case REG:
      ...
      /* If this is a hard register, ... */
      if (GET_CODE (x) == REG && REGNO (x) < FIRST_PSEUDO_REGISTER) ...
```
and expand has the "expand_const" / "reg_constant" mechanism: expand tracks constants for pseudos? There's `expand_expr`'s handling of `PLUS` with `CONSTANT_P` operands.

Hmm, in gcc 2.7.2, expand.c has:

```c
      /* Handle the case of a variable that is a constant.  */
      if (GET_CODE (x) == SYMBOL_REF || GET_CODE (x) == CONST_INT) ...
```

There's the "reg_constant" table used by expand? Hmm, actually gcc 2.7 has `cse` do constant propagation, not expand. But the RTL dump (post-expand) already had the symbol_ref in the plus. So it was expand.

Hmm, in gcc 2.7.2 expand.c, function `expand_expr`, case REG:

```c
    case REG:
      /* ... */
      if (GET_CODE (x) == REG && ...)
	{
	  ...
	}
```
I recall this piece in expand.c:

```c
      /* Handle the case of a variable that is a constant: this is
	 done in expand_const? */
```

OK. There IS a known expand behavior: "expand_expr: REG" → if the reg is a pseudo whose value is a constant known via `reg_constant`... hmm, but reg_constant is a cse thing.

ALTERNATIVELY: maybe the substitution in ours came NOT from expand but from the *tree level* — i.e. the source expression itself: `(u8 *)p + off + 4` where p is a variable assigned D_80195AF6 — expand emits (reg p) normally. But the dump shows symbol_ref...

Wait, maybe the dump I looked at is the .i.rtl which is dumped AFTER cse?? Let me check the insn numbering: .rtl insn 184 = ashift; .combine insn 184 = ashift (same number) — the combine dump is after combine which doesn't renumber much. The .cse dump has insn 184 = ashift too.

The key question is whether .rtl is before combine. The .combine dump shows insn 194 as the plus (with the swap) while .rtl shows insn 190 as the plus. Different numbers (190 vs 194) — so combine renumbered (it deleted some insns). So .rtl is before combine. OK.

Hmm, so expand substituted the symbol. In gcc 2.7.2's expand.c, there IS this code in `expand_expr` for REG:

```c
    case REG:
      ...
      /* If this is a pseudo-register that holds a constant, use the
	 constant.  */
```
Hmm, I actually now recall the function `expand_expr` case REG:

```c
    case REG:
      /* ...
	 This is the case of a variable that is not a constant.  */
      ...
```
and there's a separate `expand_const`? Hmm.

Honestly the mechanism detail doesn't matter as much as finding a working spelling. Let me be empirical and try a batch of variants, then dump the RTL of any variant that changes the tree.

An important clue: the target's tree kept the pointer as a REG. What if the pointer in the target was NOT a local variable but the *result of an expression* like `&D_80195AF6[0]` — same.

What if the target's p was assigned from a *volatile* global? no.

Hmm, what if in the target the pointer pseudo was *also used* by the `at` materialization — i.e. the compiler used the same pseudo for both the final address and the newval address, but the newval one needed a *modified* copy (symbol + idx) so it got its own reload (at)? Hmm! That's plausible: reload creates at = symbol (a fresh copy for the newval address computation) and keeps a1 for p (used at the end). But if p's pseudo value is the symbol, expand would have substituted it...

Unless the pseudo was NOT a constant at expand time but became one later (cse). Hmm: cse's reg_equiv could turn (reg p) into (symbol_ref) — but that's later than expand.

Wait, actually maybe in the target the pointer pseudo p was assigned the symbol via a *separate insn* (`set (reg p) (symbol_ref)`) and the use at the add was (reg p) because expand didn't fold. Then reload assigns p → a1 → "lui a1; addiu a1,a1,0". And the newval load's address (plus (symbol_ref) idx) → reload creates at → "lui at; addu at,at,v0" ✓.

So in the target: expand did NOT fold the symbol into the plus at the final add, but DID at the newval load. What differs between the two expressions?

Final add address: (plus p off) where off = idx*8, then +4.
Newval address: (plus symbol idx) — hmm, this one is `D_80195AF6[idx].f0` — direct array subscript on the SYMBOL (not through p).

So maybe the difference isn't expand folding but the SOURCE: in the target, the newval expression was written directly on the symbol `D_80195AF6[idx].f0` (as in our current source!) and the final one used the pointer VARIABLE p. And the difference in the trees is: the direct-symbol subscript folds to (plus (symbol_ref) (reg idx)) → survives combine as symbol-first (as in the target's `addu at,at,v0`); while the variable-based one is (plus (reg p) (reg off)) → hmm, but in ours the variable-based one folded to symbol_ref at expand.

So why would expand fold (reg p) → (symbol_ref) in ours but not in the target?

Possibility: because of the *cast* `(u8 *)p`! Ours: `((u8 *)p + off + 4)`. If the target's original was `((u8 *)p + off + 4)` too... hmm, but ours folds.

Hmm, ours folds p (a `D_80195AF6_t *` variable) into a symbol_ref. But wait — does it? The dump shows (plus (symbol_ref) (reg 118)). Since p is `D_80195AF6_t *p = D_80195AF6;` — this is a *local initialized with the constant*. Expand folds a local's constant initializer into its uses (that's standard "expand: substitute constants for pseudos" — indeed gcc's expand has this: a pseudo with a constant init gets the constant substituted at expand time — "expand_expr REG case: if the variable's value is a constant, use it" — this is real: gcc 2.7's expand.c has:

```c
    case REG:
      ...
      /* If this is a variable that was initialized with a constant, ... */
```

Yes! I'm now confident: gcc 2.7's expand has "expand_const" and the local var with a constant initializer is substituted.

So in the TARGET's original source, `p` was probably NOT initialized with a constant! It might have been assigned in a way that isn't a constant init... but the value IS the symbol (lui a1; addiu a1,a1,0 with the D_80195AF6 reloc).

Hmm! What if p was assigned from a *function call* or from a global variable pointer? E.g.:

```c
extern D_80195AF6_t *D_80195AF6_ptr;  /* no */
```

OR: what if p was assigned the symbol but through a *cast of an integer*: `p = (D_80195AF6_t *)(s32)D_80195AF6;`? expand would fold the cast of a symbol → symbol. Hmm.

OR: what if p was assigned *inside* the else branch (not at declaration)? e.g.
```c
} else {
    D_80195AF6_t *p = D_80195AF6;
```
Same thing (a local with constant init).

Hmm, what if the ORIGINAL source didn't have a pointer variable at all, and the "p" in our decomp is an artifact? Then the original would be:
```c
D_801270C8 = *(s16 *)((u8 *)D_80195AF6 + unk100 * 8 + 4);
```
Then the tree = (plus (symbol_ref) (shift)) → combine would swap → "addu v0,v0,a1". But the target has pointer-first. Hmm, so no.

Hmm, so the target's tree has a REG pointer. Which means expand didn't fold. When does expand NOT fold a constant local? When the local is *address-taken* or when the variable is modified...

Ooh! What about the ORDER of statements: maybe in the original, `p = D_80195AF6;` came AFTER something, and there were intervening uses...

Alternatively, maybe the original source's p was a **global variable** (file-scope pointer)! A global pointer variable would be loaded from memory (lw) — the target has no such load.

OK here's another thought: maybe in the original, the pointer was obtained via a *cast of the array symbol to a different pointer type* in a context where expand keeps it: e.g.

```c
D_801270C8 = *(s16 *)((u8 *)&D_80195AF6[0] + off + 4);
```
Then the tree = (plus (plus (symbol_ref) 0) off)... hmm, &D_80195AF6[0] = symbol_ref + 0 → folds to symbol_ref.

What if the offset expression isn't a multiple of 8? The target's asm clearly has sll by 3.

Hmm, what if the address is computed as `p + off` where off is an *unsigned* and the sum type is 64-bit? No.

Let me look at the problem from the "what does the project's decomp say" angle: the current def has the launder `__asm__("" : "=r"(p) : "0"(p));` with the comment "NEEDED DIFFERS (P36 rung B t8_tus2)" — meaning the project's own tooling determined that the launder was needed to reproduce the target. The lever is exactly the "keep p in a register" trick.

The brief's task: find a lever-free way. This looks like a genuine wall (the notes' tag: combine-commutative-swap).

But wait — maybe there's another spelling: what if we DON'T use a pointer variable but instead use the *symbol* with a scaled index in a form that yields (plus reg symbol)? We need pointer FIRST.

Hmm, what if the pointer is the FIRST operand and it's a symbol_ref, and the index is the second: (plus (symbol_ref) (reg idx)) — that's what we have pre-combine! And combine swaps it. What if we make the second operand something combine won't swap with? Combine swapped (plus symbol (shift)) → (plus (shift) symbol). Maybe the swap is triggered by the *shift* (scaled index canonicalization). What if the index is not a shift but a plain reg? Then (plus symbol reg) — would combine keep it? The target's newval case: (plus symbol reg) survived!! (addu at,at,v0 where at=symbol, v0=idx plain reg).

YES! Look: the target's newval add has the symbol FIRST and a plain reg second, and combine did NOT swap. So combine's swap is specific to the *scaled index* (shift) case: (plus symbol (ashift)) → (plus (ashift) symbol).

That's a very plausible combine rule: gcc's combine has a "plus with mult/shift" canonicalization where the scaled index goes first (for the scaled-index addressing pattern).

So: if I can make the final address's index NOT a shift — e.g. if the multiply by 8 stays a MULT insn instead of being converted to a shift — then the tree might stay (plus symbol (reg)) → "addu v0,a1,v0" ✓.

But the target's asm has `sll v0,v0,0x3` — a shift! So in the target, the index was a shift too, yet the tree kept symbol first. Hmm!! Contradiction?

Unless in the target the tree was (plus (reg ptr) (reg shift)) — pointer a reg, index shift — and the "swap" rule applies only when the first operand is a symbol_ref.

So combine's rule might be: canonicalize (plus SYMBOL (mult/shift x)) → (plus (mult/shift x) SYMBOL). If the first operand is a REG, no swap. And the target's newval case (plus symbol (reg idx)) — the second operand is a plain reg (not scaled), so no swap ✓ consistent!

So the rule is about scaled indices: (plus sym (shift)) → (plus (shift) sym).

Then the target's final add (plus (reg ptr) (reg shift)) — pointer is a REG → no swap ✓.

So we need the pointer to be a reg at combine time. Since expand folds constant-initialized locals...

Hmm, what if p is initialized with a NON-constant but the same value at runtime? Not possible without a lever.

What if we avoid the pointer variable and use the symbol directly, but then the index must not be scaled-by-8 — but it must be (target has sll 3).

Unless... we can express the *8 scaling* differently so that the multiply isn't a shift-by-3 in the tree: e.g. `unk100 * 8` → the tree (mult idx 8) → combine converts to shift. What if we use `unk100 * 4 * 2`? Still folds. What if `unk100 << 3` → shift directly ✓ (that's what we have).

Hmm, so the index is always scaled.

Therefore the pointer MUST be a reg at combine time. Options to achieve that lever-free:

Option 1: Make the pointer's value NOT a compile-time constant: e.g. derive it from a runtime value that equals the symbol... impossible.

Option 2: Make expand NOT fold: expand folds a local initialized with a constant. What if the local is initialized with the constant *in a way that expand doesn't see*, e.g. via a compound literal? Or if the pointer is a *parameter*? Not allowed.

Hmm, what about a **static** local? `static D_80195AF6_t *p = D_80195AF6;` — a static local lives in memory → the use would be a load → different asm. No.

What about a local *array* or struct member? no.

Option 3: Accept (plus symbol (reg idx)) where idx is NOT scaled — i.e. change the *address computation* so that the scaled part is added to the symbol differently: e.g. compute `off` such that the address = symbol + off where off is a plain reg holding idx*8 — but the shift is a separate insn so the tree operand is the shift reg... wait!

Hmm, hold on: in OUR tree, the plus's second operand was (reg 118) where 118 = (ashift 88 3) — a REG (the shift result in a pseudo), not a shift expression inline! The tree was (plus (symbol_ref) (reg 118)) — the second operand is a plain REG. So by my rule analysis, no swap should occur... but combine DID swap. Hmm, so the rule isn't about the tree shape but about the *insn* it's replacing: combine sees the insn `(set (reg/v:HI 113) (mem/s:HI (plus:SI (symbol_ref) (reg 118))))` — where 118 has REG_EQUAL (mult 88 8)! Combine looks at the REG_EQUAL note to know that 118 = mult 88 8, and applies the "scaled index" canonicalization: (plus sym (mult x 8)) → (plus (mult x 8) sym). THAT's the rule! gcc's combine has a specific transformation for `symbol + x*2^n` → `x*2^n + symbol`??

Hmm, that seems odd but let me check gcc 2.7.2 combine.c... I recall:

```c
	  /* Handle (plus (symbol_ref) (mult x 2^n)) as (plus (mult x 2^n) (symbol_ref))? */
```

Hmm. Actually! I remember a real gcc 2.x combine rule: "convert (plus (mult x 2^n) (symbol)) to ..." hmm.

Wait, maybe it's the opposite: gcc's canonical form for an address with a scaled index is (plus (reg base) (mult index 2^n)) — the scaled index LAST. So combine would want (plus sym (mult x 8)) — symbol first, mult last — which is what we had! And it swapped to the opposite. So no.

Let me stop and get the actual gcc 2.7.2 combine.c source. Maybe it's obtainable... The toolchain is a binary. But maybe the repo has gcc sources somewhere? Let me search the repo for "combine.c" or a gcc source tarball. There's tools/bin/gcc-2.7.2-psx.tar.gz (binaries).

Alternatively, use the dump evidence: combine's own dump might have a comment about the substitution. The .combine dump has ";; Combiner totals" and per-insn notes. Let me look at the combine dump around insn 194 for notes.

Let me look at the combine dump section for our function, specifically the insn that became (plus (reg 118) (symbol_ref)) and see the notes.

Actually, better idea: the combine dump in gcc 2.7 prints the insn AFTER combine with its notes. Let me look at both insn 184 and 194 in the .combine dump with full text.

Let me print the raw combine dump region.
