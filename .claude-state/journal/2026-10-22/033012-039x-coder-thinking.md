---
ts: 2026-10-22T09:30:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Mgy2tUXOPPUfdvD2wLHy
---
In the combine dump, the final address tree is (plus (reg 118) (symbol_ref)) — index first.

And the newval load in the target has (plus symbol reg). Let me check what OUR newval load looks like in the combine dump: it should be (plus (symbol_ref) (reg)) since ours matches the target there ("addu at,at,v0" — wait, ours has "addu at,at,v0" ✓ same as target).

So in ours: newval = (plus symbol reg) — symbol first, NOT swapped. Final = (plus (shift-reg) symbol) — swapped!

Difference: the final's second operand (118) has REG_EQUAL (mult 88 8) — a scaled index. The newval's second operand is a plain reg (no mult note).

So combine's rule fires when it can see the mult/scale. It's the classic gcc 2.7 combine code (I'm now recalling the actual source):

```c
	    case PLUS:
	      ...
	      /* If we have a plus of a symbol and a multiply by a power of 2,
		 we can convert the multiply to a shift and put it first? */
```

Actually here's the real gcc 2.7.2 combine.c code I now remember (from the "combine_insns" PLUS case):

```c
	      /* If this is a PLUS of a constant and a MULT by a power of two,
		 ... */
```

Whatever the exact code, empirically the rule is: (plus SYMBOL (mult x 2^n)) → (plus (mult x 2^n) SYMBOL) — the scaled index moves FIRST.

Hmm interesting, that IS a real gcc thing: "x*2^n + sym" is the canonical scaled-index form? In modern gcc the canonical form is (plus (reg base) (mult index 2^n)) — base first. But gcc 2.7 might canonicalize to index-first for the "array" pattern.

Given the target has pointer-first with a scaled index, the target's tree must have had the pointer as a REG (not a symbol) — so the swap didn't fire.

So: to keep pointer-first, the pointer must be a REG at combine time. And expand folds constant-initialized locals... BUT WAIT: does it? Let me check: in our compile, the final add's tree had symbol_ref — but the newval load ALSO used the symbol (through the direct subscript expression, which is a symbol anyway). So maybe expand didn't fold at all, and the symbol_ref in the final add came from expand's handling of... hmm, the pseudo 112 was SET to the symbol (insn 176) but the use at 190 didn't reference 112 — it used the symbol_ref directly. So expand folded.

Hmm, why would expand fold p's value but the target not?

In gcc 2.7 expand.c, the REG case:

```c
    case REG:
      /* ... */
      if (GET_CODE (x) == REG && ...)
	{
	  rtx reg = x;
	  ...
	  /* Handle the case of a variable that is not a constant.  */
```
I recall this specific code in expand.c (gcc 2.7):

```c
    case REG:
      ...
      /* If this is a hard register, ... */
      ...
      /* ... */
      if (GET_CODE (x) == REG && !HARD_REGNO_P (x)) {
	  /* substitute the constant value if known */
	  ...
      }
```
Hmm, there's `reg_constant`? But reg_constant is a CSE structure. Actually there IS `expand_expr`'s handling via `cse`? no.

Hold on — maybe it's not expand. Maybe it's the *front end* (the C→RTL expansion in c-type.c / expand.c `expand_expr` on the initializer) — the local `p` is a pseudo with an init of the symbol. In gcc 2.7, expand handles "expand_assignment" and then at the end of expand_function there's a pass that removes unused/dead pseudos and substitutes constants: `expand_expr` for a REG whose value is a constant: gcc 2.7's expand.c has:

```c
	  /* If the variable is a constant, substitute it.  */
```
Hmm.

Regardless of the mechanism, the empirical question is: under what C spelling does the pointer stay a REG? Let me test a few directly in the real body:

Test A: make p's initializer non-constant in the front end's view: e.g.
```c
D_80195AF6_t *p = (D_80195AF6_t *)&D_80195AF6[0];
```
still constant.

Test B: assign p from a *conditional*? changes asm.

Test C: assign p inside the else arm via a plain assignment `p = D_80195AF6;` (not an initializer). Same folding probably.

Test D: Have p used in the newval load too, but ALSO keep the target's asm. Since the target's newval load materializes its own symbol copy into `at`, using p there would change the count. But WAIT: would it? If p is used twice, expand keeps the pseudo p as a reg; reload assigns p → a1 (lui+addiu); the newval address = (plus (reg p) (reg idx)) → "addu at,a1,v0" — but the target has "lui at; addu at,at,v0" (an extra lui). The count would be 110 instead of 111 → score changes to 1 (different insn) — worse.

Hmm, but what if p is used twice AND the newval expression is still written directly on the symbol (D_80195AF6[idx].f0)? Then p has ONE use (the final add) → same as now → expand folds.

So the ONLY way is to make p's value non-constant to the front end while the asm still shows lui+addiu of the symbol.

IDEA: What if the pointer is obtained from a **cast of an integer constant that is NOT recognized as an address**? E.g. `p = (D_80195AF6_t *)0x80195AF6;`?? That changes the semantics (absolute address, not the symbol) and the asm would differ (no relocation).

IDEA 2: What if the pointer comes from a *volatile* read of a global pointer variable? Not allowed (new lever) and changes asm.

IDEA 3: What if the pointer is a *pseudo* kept alive by a **non-lever** construct: e.g. the address of p is never taken, but p is used in a way that requires a register — like `p` being compared? no.

IDEA 4: What if we make the *index* the constant and the pointer the scaled part? No.

IDEA 5: What if the final address expression is written so the tree is (plus (reg ptr) (reg idx)) where ptr comes from a *different* variable that is assigned the symbol in a way that survives — e.g. a variable assigned in an outer scope and used after a call? Hmm: if p is assigned before a call and used after, gcc might keep it in a callee-saved reg (s-reg) — that changes the asm (p would be in $s?).

Hmm. What about the possibility that the target's p was in a1 because a1 was a *hard register* — no, a1 is caller-saved.

Hmm, hold on. Let's reconsider: maybe in the target, the pointer pseudo WAS folded by expand to a symbol_ref, and combine's swap rule fired... but the target's swap produced pointer-first?! I.e., maybe combine's canonical form is (plus (mult x 2^n) SYMBOL) → and in the target the tree was already (plus (mult) SYMBOL)?? But the target's asm is "addu v0,a1,v0" = (plus a1 v0) = pointer FIRST with the index (shift) SECOND.

Ugh, wait: "addu v0,a1,v0": dest v0, op1 a1, op2 v0. Which is which? The tree (plus X Y) → "addu dest, X, Y". So X=a1 (pointer), Y=v0 (index). Pointer first ✓ (as I said).

And ours: "addu v0,v0,a1" → X=v0 (index), Y=a1 (pointer).

OK so confirmed.

So the difference must be that the target's tree had the pointer in a reg (a1). And that means expand didn't fold the constant into the address in the target's compile.

Wait... unless the target's tree was (plus (symbol_ref) (reg idx)) and combine did NOT swap because combine's swap requires the *first* operand to be a REG and the second a SYMBOL (i.e., it swaps symbol-first → symbol-second). And in ours the pre-combine tree was (plus symbol (reg)) → swapped to (plus reg symbol). So combine moves symbols to the second position — the general "constant second" canonicalization! And the target's newval tree (plus symbol reg) survived... contradiction again. Unless the newval tree was different: maybe the newval address was (plus (reg at) (reg idx)) where `at` was a pseudo set to the symbol → reload → "lui at; addu at,at,v0"? no wait, that would be "addu at,at,v0" with at = symbol + idx ✓ and the lui at materializing the symbol into at — that IS what we see in BOTH ours and the target!

So the newval address in the target: a pseudo `at` = symbol, then at = at + idx → tree (plus (reg at) (reg idx)) — symbol in a REG. So combine didn't need to canonicalize.

And the final address in the target: (plus (reg ptr) (reg idx)) — ptr in a reg.

So in the target, BOTH the newval symbol AND the final pointer were in REGS at combine time. In ours, the final pointer became a symbol_ref (folded by expand) while the newval one is a reg (at).

Interesting! So expand folded the pointer in the final add but not the newval. Why? Because the newval's symbol comes from a *direct* array subscript (the symbol itself, no variable) — expand emits (plus (symbol_ref) (reg idx))... hmm, but that would be a symbol in the tree, not a reg.

Hmm, but the target's newval address used a REG (at). If the tree were (plus (symbol_ref) (reg idx)), reload would create a register for the symbol (at) and emit "addu at,at,v0" — the same as a reg! Because reload materializes a symbol_ref operand into a register. So both are consistent with the tree (plus symbol idx).

So for the newval, the tree (plus symbol idx) → reload → "addu at,at,v0" ✓ (target) — and combine did NOT swap it to (plus idx symbol) → because the index is a plain reg (no scale).

And in ours the final add's tree (plus symbol 118) where 118 has REG_EQUAL (mult 88 8) → combine recognized the scaled index and swapped → (plus 118 symbol).

In the target, the final add's tree must have been (plus (reg ptr) (reg 118-with-mult-note)) — since combine's swap only fires when the symbol is directly in the tree (the first operand).

=> The target's pointer was a REG in the tree. Confirmed again.

So how did the target's compile keep the pointer as a reg? The pointer must have been a variable whose value was NOT a constant at expand time but became the symbol later (via cse or via reload of the set insn).

AH WAIT! What if the pointer variable was assigned the symbol in a place where the SET insn exists (insn 176: `(set (reg/v:SI 112) (symbol_ref))`) and the USE references (reg 112) — and expand only substitutes constants in *some* cases? In our dump, insn 176 sets 112 = symbol, and 186/188 set 119/120 = symbol (with REG_EQUAL notes). So the pseudo 112 was set but not used in the final add (the final add used the symbol_ref directly).

Hmm! But 112 IS used somewhere — probably for the newval load? No, the newval used `at`... which is a reload of the symbol.

So the set insn 176 exists (p = symbol) but its value was substituted into the use. Classic expand behavior: "expand_expr: a pseudo reg whose value is a constant gets the constant substituted" — this is the `expand_const`/`cse` interplay.

Hmm, in gcc 2.7, expand.c has:

```c
      /* Handle the case of a variable that is a constant: the front end
	 has already substituted it? */
```

The C front end (c-type.c) does constant propagation? Actually, gcc's c front end (c-type.c / c-decl.c) expands the initializer `p = D_80195AF6` into a tree `(set p (addrconst D_80195AF6))`. Then expand handles the assignment: it can either emit `(set (reg p) (symbol_ref))` or, if p is a "constant" pseudo, substitute the constant at all uses. gcc 2.7's expand.c has this in `expand_assign`/`expand_expr`:

```c
    case VAR_DECL / PARM_DECL: ...
```
and there's the function `expand_expr` REG case:

```c
    case REG:
      ...
      /* If this is a pseudo reg that has a constant value, use it.  */
      ...
```
Hmm, actually I remember gcc has `reg_constant` (cse) and `expand` has "expand_const" for `SET` with a constant into a pseudo used once: the code is in expand.c:

```c
/* Expand a call to a function... */
```

Let me instead test empirically what happens with different declarations. Cheap: try these variants in the real body and see if the tree changes:

V1: `D_80195AF6_t *p;` ... `p = D_80195AF6;` (assignment, not initializer)
V2: `D_80195AF6_t *p = &D_80195AF6[0];`
V3: `u8 *p = (u8 *)D_80195AF6;`
V4: `D_80195AF6_t *p = D_80195AF6;` but with an intervening use of p...

Honestly, a quicker experiment: use the LAB (standalone) with a body similar enough to reproduce the swap, then iterate fast. The lab earlier folded the whole address into the load's displacement (lh $2,A+4($2)) because the base was a constant and gcc 2.7 folds constant+index into the displacement when possible. In the real code it didn't fold because the address was HI+LO (the symbol's low part is 0 but the address is > 16-bit signed? D_80195AF6 is fine) — hmm, in the lab, `A+4($2)` folded. In the real code it didn't fold into the displacement because the symbol's low part is 0 and the displacement form requires the full address... whatever.

In the lab the pointer was folded entirely into the addressing mode, so no `addu` at all. To reproduce, I need the address to not fold — e.g. use a struct pointer with an 8-byte stride? Let me craft the lab to mirror: use a `struct { char c; }`? Hmm.

Let me instead do the experiments in the REAL body (1s each). I'll write a batch runner that applies textual variants to a base file and scores them.

Let me write the variant generator for item 80184828 now. Base: v1.c (lever-free). Variants to try (each a full body file):

The relevant part of the body:
```c
        } else {
            D_80195AF6_t *p = D_80195AF6;
            s16 newval = D_80195AF6[((Unkstruct_800B5CB8 *)a0)->unk100].f0;

            if (newval >= CAST_SIGN(s16, (u8 *)a0, 0xE)) {
                s1 = 1;
                ((S0E_80184828 *)((u8 *)a0 + 0xE))->h = newval;
                off = ((Unkstruct_800B5CB8 *)a0)->unk100 * 8;
                D_801270C8 = *(s16 *)((u8 *)p + off + 4);
                D_801E43B4 += 1;
            }
        }
```

Variants:
1. base (v1) → 1
2. p declared as u8*: `u8 *p = (u8 *)D_80195AF6;` and `*(s16 *)((u8 *)p + off + 4)`
3. `off` as u32
4. `off` = `unk100 << 3`
5. address: `*(s16 *)((u8 *)p + off + 4)` → `*(s16 *)((u8 *)p + (off + 4))`
6. `*(s16 *)((u8 *)p + 4 + off)`
7. temp pointer: `u8 *pa = (u8 *)p + off; D_801270C8 = *(s16 *)(pa + 4);`
8. `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` with p = `D_80195AF6_t *p = &D_80195AF6[0];`
9. index in the load: `D_801270C8 = *(s16 *)((u8 *)p + ((Unkstruct_800B5CB8 *)a0)->unk100 * 8 + 4);` (no off var)
10. `s32 off` → `u32 off` (tried by notes) etc.
11. Write the load through a `u16 *`: `D_801270C8 = *(u16 *)((u8 *)p + off + 4);` — hmm, s16 vs u16 changes sign extension of the loaded value → different asm (the target: "lh v0,4(v0)" → lh = signed load ✓ so s16).
12. `p` used as `D_80195AF6_t *` and the address spelled `((u8 *)p + off) + 4`:
    `D_801270C8 = *(s16 *)(((u8 *)p + off) + 4);`
13. Make the pointer a reg by adding a second use that doesn't change the asm: e.g. `if (p == D_80195AF6) ...`? that adds asm.
14. `(u8 *)p` replaced by `(u8 *)(s32)p`.
15. Swap the order of the two operands in C: `off + (u32)(u8 *)p`? Hmm: `*(s16 *)((u8 *)off + (u32)(u8 *)p)` — the tree (plus (reg off) (symbol)) — symbol second → combine keeps → asm "addu v0,v0,a1" (index first) — that's ours; we want pointer first.

Hmm! Idea 16: make the tree (plus (symbol) (reg)) where the reg is the scaled index — i.e. avoid the REG_EQUAL mult note so combine doesn't swap. How? The REG_EQUAL note comes from the multiply insn 184 (the shift). If the multiply is computed into a variable and the note is lost... e.g. `off = unk100 * 8;` — the note (mult (reg 88) 8) is attached to the shift insn because combine created the shift from the mult.

What if the multiply is done via a *different* form that doesn't produce a REG_EQUAL mult note, e.g. `off = unk100 * 8` vs `off = (unk100 << 3)` (no mult note!) — then the tree is (plus symbol (reg shift)) with no mult note → maybe combine won't swap! The notes say v5 tried "the `* 8` spelled as `<< 3`" → 1. Hmm, but maybe with << 3 the shift is a separate insn whose REG_EQUAL note says (mult x 8)? gcc might still attach REG_EQUAL (mult (reg) 8) to the shift. Yeah, likely.

What if the index is multiplied by 8 in a way that isn't a power of 2 multiply? e.g. `off = unk100 * 8` → we need sll by 3 in the asm.

Hmm, what about making the address use a *pointer* arithmetic form where the index is a pointer difference: `(u8 *)p + off` where off is s32...

Let me think about combine's actual code. I'd really like the gcc 2.7.2 source. Let me check if the internet is available? Probably not (sandbox). Let me check if pip/apt cache has gcc-2.7 source... unlikely.

Alternatively, gcc 2.7.2's combine.c might be in the repo's tools/ (maybe a copy for reference). Let me grep the repo for "combine.c".

Let me do thatquickly.
