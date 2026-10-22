---
ts: 2026-10-22T10:53:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_LDBCP1DubZJG0tmcpOJN
---
The harness keeps saying "Go on with the task". Perhaps there's a check that the task isn't complete. Let me re-read the brief for anything not yet done:

- "Per item append exactly one row to RM2/results.tsv" ✓
- "First read .run/P40/T11/moves.md ... after each item append one line `kind | func | MATCH: move / WALL tag — mechanism (RM2)`" ✓
- "Notes in <dir>/notes.md; do not stop between items." ✓
- "LOG: phase-ends/current/logs/T11.cRM2.md (timeline per item, moves that cracked, walls with evidence)." ✓
- "DONE WHEN: every item of RM2/list.tsv has exactly one results.tsv row; each MATCH/PARTIAL has its win.c scoring 0." ✓

Hmm — "For each item in .run/P40/T11/RM2/list.tsv ... write a lever-free body of `func` in RM2/<dir>/win.c (bare definition) that scores 0." Since no body scores 0, no win.c. But maybe the grader expects a win.c file to exist for each item? Hmm. The DONE WHEN says "each MATCH/PARTIAL has its win.c scoring 0" — so win.c is only for a crack. But to be safe, maybe I should write win.c as the best lever-free body anyway? Hmm, that could be misread as claiming a MATCH. Hmm.

Hmm, the harness's repeated "Go on with the task" might be because the mod expects more work — maybe because the wall rows aren't "done"? Or because the shard's items should be re-dealt (the brief says "Retry: each item was walled before after too few tries; read <dir>/notes.md first, then try new moves.").

Since I have time, the most useful thing is to keep trying to actually crack these items, focusing on the closest ones (80184828 at 1, 8017DA30 at 4). Each additional try batch costs ~1 minute. Let me use the remaining effort on genuinely new move classes that I haven't tried yet:

For 80184828 (1 instruction): I need the pointer in a REG at combine time. New idea I haven't tried: what if the pointer's value comes from a **struct member of a local struct**? No — memory.

Hmm, what about a **static const**? No.

Hmm, what about **a pointer-to-pointer in a local struct**: no.

Hmm, what about making the address expression's first operand a REG by using **pointer arithmetic on a `void *`**? Hmm: `(void *)p` — the mode is the same.

Hmm! NEW IDEA: What about the **the other order in the C source** with a REG first operand: e.g. `off + (u32)p`? Tried (v66, zc) → index first.

Hmm. NEW IDEA 2: What if the *index* were the constant and the pointer the variable? I.e. swap which operand is scaled: the target's add is "addu v0,a1,v0" = ptr + (idx*8). We need ptr as a reg.

NEW IDEA 3: **What if `p` were assigned a value that is not a constant but is still the address — e.g. via an array-of-pointers in a static table?** There's no such table.

NEW IDEA 4: Hmm! What about **`p = D_80195AF6;` where D_80195AF6 is declared as an ARRAY of structs vs a struct?** The tree would be the same.

NEW IDEA 5: What about the **`(u8 *)` cast producing a different mode**? In gcc 2.7, `u8 *` and `D_80195AF6_t *` are both Pmode.

NEW IDEA 6: What if the address were computed with a **32-bit integer multiply** that combine can't rewrite: e.g. `off = unk100 * 8` → the tree (mult unk100 8) → combine converts to a shift. Hmm, what if `off = unk100 * 4 * 2`? → (mult (mult unk100 4) 2) → combine → shift by 3? Probably.

Hmm, but here's a thought: the swap in simplify_rtx applies to the PLUS whose first operand is a constant. What if the address's first operand is the *scaled index* (a REG) and the second is the symbol? Then no swap, but the asm order is index-first ✗.

So the ONLY way is: the pointer in a REG.

Since expand substitutes the constant for the pseudo, the pseudo must not be substituted. What does expand's substitution depend on? Hmm, let me actually find out! The expand.c source isn't in tools/reference/gcc-2.7.2, but maybe in the papermario tree there's an equivalent (gcc-papermario's expr.c has expand_expr!). Let me look at the REG case in the papermario expr.c's expand_expr to see when a pseudo's constant value is substituted into its uses.

That would tell me exactly what to avoid. Let me look.

Actually, hmm — earlier I found that gcc-papermario/expr.c:4887 has expand_expr. Let me look at its VAR_DECL/REG handling. This could reveal the rule (e.g. "if the variable is not address-taken and has a constant initializer, the front end substitutes the constant at each use" — the front end's c-type.c does this in `expand_expr` for VAR_DECL when `TREE_CODE (decl) == VAR_DECL && DECL_INITIAL (decl) && TREE_CONSTANT (DECL_INITIAL (decl))`).

If the rule is "TREE_CONSTANT(DECL_INITIAL)", then an initializer that is NOT TREE_CONSTANT would keep the pseudo alive! What C expression yields a non-TREE_CONSTANT tree for a pointer initializer but still materializes as lui/addiu of the symbol?

Hmm! In gcc 2.7, the front end's `build_binary`/`fold` would fold `&D_80195AF6` into an ADDR_CONST (TREE_CONSTANT). But what if the initializer is `(u8 *)D_80195AF6` — the front end's fold of a CAST of an ADDR_CONST to a pointer type: gcc's fold has a rule: "fold_addr_const" / the cast of an ADDR_CONST to a pointer type is folded to the ADDR_CONST ✓ (so TREE_CONSTANT).

What about `(u8 *)(s32)D_80195AF6`? The front end folds the ADDR_CONST → INTEGER_CST? In gcc 2.7, casting an address to an integer yields an INTEGER_CST (fold does this: "fold_addr_const" → the address as an integer constant) — hmm, that would make the initializer an INTEGER_CST (TREE_CONSTANT) → then the pseudo is substituted → but the *value* would be the integer, and the asm would materialize the integer (lui/addiu with a literal, no relocation) ✗ — but the notes' v12 (that exact cast) was "folded" and the score stayed 1, so gcc kept the symbol (the front end probably keeps ADDR_CONST for pointer casts).

Hmm, so what initializer is NOT TREE_CONSTANT but still yields the symbol address at runtime? E.g.:
- `(u8 *)((u32)D_80195AF6 & 0xFFFFFFFF)` → folds.
- A cast to a *struct* type: `((D_80195AF6_t *)D_80195AF6)` → folds.
- `(u8 *)(s32)&D_80195AF6[0]` → folds.

Hmm, what about a **cast through a union**? no.

What about the initializer being an *arithmetic* expression on the address: `(u8 *)((u32)&D_80195AF6 + 0)` → folds.

Hmm, what about a **function call**? no.

Hmm, so within "real C" there's no escape.

OK — but wait. Let me check the actual rule in the source. Let me look at the papermario gcc's c-type.c... hmm, c-type.c isn't in the papermario tree either (only c-typeck.c). Hmm, but expr.c's expand_expr is there (the RTL-level expansion). Let me check the VAR_DECL case there (line 5027 I read earlier) — it was about DECL_RTL, not constant substitution.

Hmm, the constant substitution of a local's initializer happens in the FRONT END's expand_expr (c-type.c). Let me check if the papermario tree has c-typeck.c with a similar rule... Let me grep c-typeck.c for "TREE_CONSTANT (DECL_INITIAL".

Let me do that quickly. If the rule is TREE_CONSTANT-based, maybe I can find a non-constant initializer.

Hmm, alternatively: what if the variable is declared with an initializer that the front end folds to a constant, but the *use* is in a context where the front end doesn't substitute? E.g. the front end's `expand_expr` for a VAR_DECL checks `DECL_INITIAL` and if it's a constant, returns the constant tree — that happens at EVERY use. So the copy `p = pb` never exists in the tree.

Hmm, so how could the ORIGINAL source have produced a copy? Maybe the original's `p` was NOT initialized with a constant but assigned at runtime from a *table*! E.g. the original might have been:

```c
p = D_80195AF6;   /* hmm */
```

Hmm, but the asm materializes the symbol → a constant.

OK: maybe in the original, `p` was a **global** pointer variable (a static), and the value in it was the address — then the asm would LOAD it from memory (lw) ✗ (the target has lui/addiu).

So the target's "move s0,v0" really is a copy of a constant materialized in v0. Which requires two pseudos: one for the constant, one for p. In the front end, that means: p's initializer is NOT a constant tree, and p's value comes from another variable.

What if the original source was:

```c
    u16 *pb = &D_800B99DC;   /* pb's initializer IS constant → folded at every use */
```
✗.

Hmm, unless the original was:

```c
    u16 *pb;
    pb = &D_800B99DC;    /* an ASSIGNMENT, not an initializer */
```
Hmm! Does the front end treat an assignment differently from an initializer? The assignment `pb = &D_800B99DC;` — the front end's expand_expr for the RHS gives an ADDR_CONST tree; the assignment is expanded as a MODIFY_EXPR → expand assigns the constant to pb's DECL_RTL → the RTL is `(set (reg pb) (symbol_ref))` — and the *use* of pb is `(reg pb)` ✓ NOT substituted by the front end!! (The front end only substitutes for the DECL_INITIAL case.)

So: `u16 *pb; pb = &D_800B99DC; p = pb;` — hmm, but the x3 variant was exactly the block form with an initializer `u16 *pb = &D_800B99DC;`. Let me test the ASSIGNMENT form!

Wait — but then at the RTL level, pb is a pseudo set to the symbol; cse would forward the constant to pb's use (p = pb) → the copy dies ✗ (the cse "lone use" forwarding). Hmm, unless the set isn't a lone use...

Hmm, but hold on: the .rtl dump I took was for x3 (the initializer form) and showed ONE set insn (to reg 81) — i.e. even the set for pb was gone (the front end substituted the constant into p's initializer as well!). With the assignment form, the RTL would have TWO sets: `(set (reg pb) (symbol_ref))` and `(set (reg p) (reg pb))` — and then cse might forward.

That's worth testing! It's a real C move (decl order / init at decl vs assignment) and it's exactly in the catalog ("init at decl").

Let me test for 8018483C:
```c
    u16 *pb;
    ...
    pb = &D_800B99DC;
    p = pb;
```

Hmm, but x3's block was:
```c
    {
        u16 *pb = &D_800B99DC;
        __asm__(...);
        p = pb;
    }
```
So with the asm removed, the front end substituted the constant into `p = pb` (the initializer's value) → one set.

With the assignment form, the front end has no DECL_INITIAL to substitute → the RTL keeps two sets → cse may or may not fold.

Let me test it! This could crack 8018483C.

Similarly for 80184828: `D_80195AF6_t *p; p = D_80195AF6;` → the front end doesn't substitute (no initializer) → the tree would be (plus (reg p) (reg idx))?? Hmm — expand's set insn `(set (reg p) (symbol_ref))` and the use `(reg p)` → then cse/expand might substitute the constant into the address (that's the "expand folds the constant into the use" behaviour I saw). Hmm, for 80184828 the .rtl dump showed the symbol in the plus — but that was for the initializer form.

Hmm! For 80184828, if p is assigned (not initialized), maybe expand does NOT fold it into the address (expand's folding of a constant into an address may apply only to the initializer case, where the front end already substituted).

Hmm, actually, the substitution I observed (symbol in the plus at .rtl time) — was it the front end (for the initializer) or expand? For the initializer form, the front end substitutes the ADDR_CONST into the use → the use's tree is the symbol → the plus tree has the symbol ✓.

With the assignment form, the use's tree is (VAR_DECL pb) → expand creates the pseudo → the plus tree has (reg pb) ✓✓ — a REG! Then combine's simplify_rtx: XEXP(x,0) = (reg pb) → not a constant → NO SWAP → the target's operand order!!! ✓✓✓

That's a promising crack for 80184828!! Let me test it right away.

Similarly for 8018483C: `u16 *pb; pb = &D_800B99DC; p = pb;` → the RTL keeps the copy → maybe the target's "lui v0; addiu v0; move s0,v0" ✓.

And for 8017D81C: `s32 x; x = -0x680;` — hmm, the constant substitution: the front end's expand of `x = -0x680` → the RTL is `(set (reg x) (const_int -1664))` and the uses are (reg x) → then cse forwards the constant to the uses (qty_const) → the li is born at the first use ✗. Hmm, but maybe cse's forwarding doesn't happen for a set that isn't a "class head"... hmm, worth testing too!

And for 8018389C: the launder is on `vol` — `vol = ...; vol = vol / 0xA0;` — hmm, the launder's asm reads vol. Without the asm, the division result is used directly. Hmm, the assignment form doesn't apply there (vol is already assigned).

And for 8017DA30: `q = sub; p = ...; e = ...;` — the launder's asm reads q/p/e. Hmm! The assignment form is already there for q/p/e (they're assignments, not initializers!). Hmm, but the residual persists — because the *values* aren't constants (q = sub, p = ent+0x24, e = a symbol). Hmm, e = (s32)D_801817B0 IS a constant → the front end substitutes it → the call's a2 arg is the symbol. Hmm.

OK! Let me test the "declaration + assignment" (no initializer) form for 80184828 and 8018483C right now. This is a promising, catalog-legal move ("init at decl" → the inverse).

Let me doit.
