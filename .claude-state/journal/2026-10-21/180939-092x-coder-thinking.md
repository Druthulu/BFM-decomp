---
ts: 2026-10-22T00:09:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_FNycuVoqbfl3yoFIsGwN
---
That's for comparisons. The add's swap is elsewhere. Let me look at combine's `convert_add` → `simplify_operand`... Hmm.

Actually, in gcc 2.7.2's combine.c, the relevant function is `simplify_operand` / `match_operand`, and there's a step in `convert_add`:

```c
static rtx
convert_add (rtx x, rtx y, int convert_attribs)
{
  ...
      /* If we have an addition of a constant and a register, ... */
```

Hmm.

Alternatively, the swap might come from `combine_regs` (local-alloc's combine_regs.c) — which isn't in the reference tree (I saw the list: basic-block.h, c-convert.c, c-typeck.c, caller-save.c, calls.c, combine.c, config, convert.c, cse.c, emit-rtl.c, expmed.c, expr.c, flow.c, fold-const.c, function.c, global.c, hard-reg-set.h, integrate.c, jump.c, local-alloc.c, loop.c, loop.h, optabs.c, recog.c, regclass.c, regs.h, reload.c, reload1.c, reorg.c, rtl.h — no combine_regs.c!). Hmm.

OK. Let me take the empirical route with a different lever: the C0505 catalog's "pointer reuse" / "temps" / "statement order".

Hmm, let me think about the ONE thing that might matter: the ORDER of the two operands in the tree. gcc's tree for `(u8 *)p + off`:
- The pointer p is a variable of type D_80195AF6_t*; the cast to u8* is a no-op.
- The addition: ptr + int → in gcc's C front end, `build_binary_op` for POINTER_PLUS_EXPR → the tree is (PLUS ptr (converted int)).

So the tree is (plus p off) → p first. But the output is (plus index p).

Hmm, so gcc swapped the tree's operands. In gcc's combine, `convert_add` has:

```c
  /* Reassociate and simplify expressions.  */
  ...
  if (GET_CODE (x) == PLUS && ...)
```

Hmm.

WAIT. What about `simplify_operand`'s "reassociation" in fold_rtx's simplify_plus:
```c
rtx
simplify_plus (rtx x, rtx y)
{
  ...
  /* Fold CONST op CONST to CONST.  */
  ...
  if (GET_CODE (x) == PLUS && GET_CODE (y) == PLUS) ...
  ...
  /* Handle the case of (plus (plus a b) c) → (plus a (plus b c)) */
```
Hmm, the reassociation could reorder.

Hmm, what if the tree is (plus p (mult idx 8)) and simplify_plus flattens to (plus p (mult idx 8)) and then canonicalize_commutative_operation sorts by cost: the cost of (mult idx 8) vs the cost of p. If the mult's cost > p's cost, they get swapped → (plus (mult idx 8) p) ✓ MINE. And in the launder version, p is a hard reg (a1) with a lower cost? Hmm.

So the cost of the operand: for a REG, the cost is 1 (cheap); for a MULT, higher. So the more expensive operand goes FIRST (per canonicalize_commutative_operation: "Make sure that X is the more expensive of the two" → hmm, the code was: `if (xcost > ycost) swap` — so the more expensive goes first? Let me re-read my memory of the code:

```c
  /* Make sure that X is the more expensive of the two...  */
  if (xcost > ycost)
    return gen_rtx (GET_CODE (op), GET_MODE (op), y, x);
```
Hmm, that swaps so that the MORE expensive is first? If xcost > ycost, the result is (op y x) — so the cheaper (y) is first. Hmm, so the cheaper goes first.

Hmm, whatever the direction, the swap depends on the operands' costs.

So to flip, I need to change the relative cost of the two operands. The index (a MULT result) vs p (a REG). Hmm.

If p were a hard reg (a1) at the time of the combine, its cost might be lower → different order. Hmm, but in the final code both are hard regs.

Hmm, hmm. But the combine pass runs BEFORE the register allocation, so p is a PSEUDO in both my version and the launder version. Hmm! So the cost of p is the same...

Hmm, so what does the launder change at combine time? The asm's output is a HARD reg (a1) — so the tree (plus hardreg_a1 (mult idx 8)) vs mine (plus pseudo_p (mult idx 8)). The cost of a hard reg vs a pseudo: in gcc, `rtx_cost` for a REG is 1 regardless of hard/pseudo? Hmm, but `COMMUTATIVE_COST` might distinguish.

Hmm! Hmm, hmm. But actually — hold on: with the launder, the address is (plus a1 v0) where a1 is a HARD reg. combine's canonicalization: the cost of a hard REG (a1) = 1; the cost of the mult = ~2-3. So the cheaper (a1) goes first ✓ = the target's order!

In mine: the cost of the pseudo p = 1 (a REG is a REG) and the mult = 2-3 → the same order → (plus p mult) hmm, that would be the TARGET's order ✗ (mine is the opposite).

Hmm, so my reasoning is inverted somewhere. Hmm.

OK, empirically: what if I make the index expression NOT a multiply but something with a different cost? E.g. `off = ((Unkstruct_800B5CB8 *)a0)->unk100 * 8;` → the mult is folded to a shift by combine... hmm, but the shift is also an insn.

What if the index were a plain value (no scaling)? The target has the sll, so no.

Hmm, what if the ADD is written with the index as the FIRST operand in the C? Not possible in C (ptr + int only).

Hmm, but what about `*(s16 *)((u8 *)p + off + 4)` vs `*(s16 *)((u8 *)(p + (off/8)) + 4)`. Hmm.

What about using a `long`/`u32` arithmetic: `D_801270C8 = *(s16 *)((u8 *)((u32)p + (u32)off) + 4);` — the tree = (plus (convert p) (convert off)) — hmm, the converts might make the costs differ!

Let me try that (v7). The semantics: (u32)p + (u32)off — the same address on a 32-bit target ✓. Hmm, but the convert of p to u32: gcc folds (convert (reg p)) → hmm, a no-op on 32-bit → the tree stays (plus p off).

Hmm.

What about `(u8 *)p + off` where off is `u32`? Hmm, tried-ish.

OK, let me consider the time. I've spent a lot. Score 1 on this item is really close. Let me try two more cheap things:
(v7) `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` with `off` declared as `u32` (the width dial) — hmm, the decl is at the function scope: `u32 off;`. Hmm, but `off` is also... only used here ✓.

Hmm, wait: `off` is declared at the function scope but assigned inside the block. Changing s32 → u32: the address = p + (u32)off → the index is zero-extended → the tree = (plus p (zero_extend off)) hmm, the zero_extend of a 32-bit value is a no-op → the tree = (plus p off).

Hmm.

(v8) What if the p variable is not used at all for the address, and instead the address is spelled `D_80195AF6` directly? I.e.:
```
D_801270C8 = *(s16 *)((u8 *)D_80195AF6 + off + 4);
```
Then the tree = (plus (symbol_ref D_80195AF6) off) — the symbol_ref has a HIGHER cost → the canonicalization would put the cheaper (off) first?? Hmm, that would give (plus off symbol_ref) = mine's order ✗. Hmm, or the target's.

Hmm! Actually, that's a promising test: the cost of a SYMBOL_REF is higher than a REG. If canonicalize puts the cheaper first, then with a symbol_ref: (plus off symbol) hmm.

Ugh, 50/50. Let me just try (v8) — it's a 1-line change and doesn't need the `p` variable... but then `p` becomes unused (the launder's p). Hmm, and the target has the `lui a1; addiu a1,a1,0` (the materialization of &D_80195AF6 into a1) — which would still be needed for the address ✓ (the symbol_ref → the lui/addiu into a1) ✓.

Hmm, but the p variable also... hmm, in the launder version, p = D_80195AF6 is materialized into a1 and used in the add. In v8 (no p), the symbol_ref is used in the add → the materialization into a1 happens at the add ✓ (the same insns).

Hmm, but the ORDER of the materialization (insns 69-70, early) vs the add (85) — in the target, a1 is materialized early (69-70) and used at 85. With a symbol_ref in the tree, gcc would materialize it right before the add (at 84-85) ✗ (the target has it at 69-70).

Hmm! So the p VARIABLE is needed to hoist the materialization early. Hmm.

OK. Let me try v7 with the u32 width and v8 with a direct symbol_ref, and see.

Actually, hold on, let me reconsider: what if I keep p but use a DIFFERENT expression for the address that has the tree (plus p off) with p as a hard-ish reg...

Hmm, what if `p` is used TWICE — once in the address and once elsewhere — so it's a longer-lived pseudo? Hmm.

Let me try the two variants and then wrap up this item either way.

Actually, let me try something much more promising: **the `off` variable's assignment placement**. What if `off` is assigned EARLIER (e.g. before the `if` block)? Then the index's live range is longer, and the add's operand tie changes!

Hmm, `off = ((Unkstruct_800B5CB8 *)a0)->unk100 * 8;` — the index is unk100 (a load from a0+0x100). Hmm, the target's `lh v0,256(s0)` at 79 — the index load! And the sll at 84.

So the index is loaded at 79 and scaled at 84. In mine, the same ✓ (the diff showed no differences up to 85).

Hmm, so the index's load is at 79 (in the target) — that's AFTER the branch (insn 77-78) and before the sll. OK.

So: if I move the `off` assignment EARLIER in the source (before the `if (newval >= ...)` test), the index's load would move earlier → changing the code ✗ (the target has the load at 79, after the branch).

Hmm, so the `off` assignment must stay where it is.

OK, let me just try v7 (u32 off) and v8 (symbol_ref) — 2 calls, then decide.

Hmm, actually, let me reconsider the whole thing: maybe the operand-order difference is a red herring caused by the REGISTER assignment, and the R-family "REG-caller" class has a known dial: "the caller-saved swap is decided in local-alloc's block_alloc/combine_regs by which dying pseudo the operand ties to — the temp inlined/introduced first".

"the temp inlined/introduced first" — the R-rules R-something generate: (a) inline a temp, (b) introduce a temp. I've tried inlining the index (v3) and introducing a pointer temp (v6). Hmm.

What if I introduce a temp for the INDEX: e.g.
```
                off = ((Unkstruct_800B5CB8 *)a0)->unk100 * 8;
                D_801270C8 = *(s16 *)((u8 *)p + off + 4);
```
Hmm, `off` IS a temp but gcc inlines it.

To prevent the inlining, off must have 2 uses. Hmm! What if I use `off` in a harmless way... hmm.

WAIT. What about using `off` for BOTH addresses? Hmm, the newval load uses the unscaled index.

Hmm, hmm: `newval = D_80195AF6[idx].f0` — the target's address = D_80195AF6 + idx (unscaled). And the other = D_80195AF6 + idx*8.

Hmm, so if I wrote the newval load using `off`... no, the scale differs.

OK. Decision: let me try 2 more variants (v7: u32 off; v8: the address via a `D_80195AF6_t *` typed pointer arithmetic `p + idx` — hmm, sizeof(D_80195AF6_t) might be 8? hmm, no: the newval load's address is unscaled, so sizeof == 1).

Hmm, v8: `D_801270C8 = *(s16 *)((u8 *)(p + off) + 4);` — hmm, p is D_80195AF6_t* so p + off would be off ELEMENTS (off*1 since sizeof==1) → the address = p + off (not off*8) ✗ (the target scales by 8).

Hmm. So the *8 is manual. OK.

Let me try v7 (u32 off) and, if that fails, v9: `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` with the `off` assignment moved to just before the use but the SCALING done differently: `off = ((Unkstruct_800B5CB8 *)a0)->unk100; ... p + off*8`? hmm, same.

Let me just do v7 and then wrap up.
