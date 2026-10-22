---
ts: 2026-10-22T00:11:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_YoL3lvlAE3cFFMTBn8WH
---
Still 1. Hmm.

Interesting: even the integer-add spelling gives the same. So gcc's canonicalization is robust.

Hmm! So the operand order in the output is (index, p) in ALL my variants, and the target has (p, index). And the launder version gives (p, index).

Since the launder makes p a HARD reg, and gcc's canonicalization depends on the operand being a hard reg... hmm, but at combine time (before allocation) p is a pseudo in both.

Hmm! UNLESS: the launder's asm is IN the block (inside the if), and the asm is a scheduling/barrier element that changes the LUIDs and hence the order in which the operands get their registers, and the "swap" is a combine_regs artifact.

Hmm! Let me reconsider: maybe the "swap" isn't a tree swap at all but the ALLOCATION: in mine, the add's result went to v0 (the index's reg) and the operands are (v0, a1) — hmm.

Hmm, hmm, what if in the target the tree is (plus p index) and gcc allocated the result to v0 (the index's reg, the dying pseudo) — the result reg = the SECOND source. In mine, the tree is (plus index p) and the result = v0 = the FIRST source.

Hmm! So maybe the difference is really the tree order, and the tree order comes from the LUIDs/expansion order.

Hmm, in gcc, `expand` builds the address: the base (p) and the offset (off). For a MEM, expand creates (mem (plus base offset)). The base comes first ✓. So the tree is (plus p off) in both.

Then combine's `convert_add` → hmm, `simplify_operand` may reorder: combine has a step where, for a commutative operation, it tries the operands in both orders to find a simplification! E.g., in `convert_add`:
```c
  /* Try to simplify the operands in both orders */
  ...
      new_x = simplify_operand (x, ...);
      new_y = simplify_operand (y, ...);
      ...
      /* If we have a plus of a reg and a constant, ... */
```
Hmm, combine's `match_operand`/`simplify_operand` can produce a different tree.

Hmm! And in the launder version, p is a hard reg → `simplify_operand` on a hard reg behaves differently (it's already a "simple" value, not simplifiable) → the tree stays (plus p off) ✓. In mine, p is a pseudo with a symbol_ref reg_equiv → combine might simplify it into the symbol_ref + something → REORDERING the tree ✗.

So: the flip is caused by combine simplifying the pseudo p (whose reg_equiv is the symbol_ref) — hmm, but if p were simplified to the symbol_ref, the add would be (plus symbol_ref off) and the materialization would be at the add (not early) ✗. Hmm, but the materialization IS early (69-70) in mine ✓ — hmm, so p wasn't simplified away.

OK. Whatever. Let me now consider: is there a C way to make the address's base a HARD reg at combine time? A call argument! p is passed to no call...

Hmm, what if I PASS p to a function?! There's no suitable call.

Hmm, what if p is used in a context that requires a hard reg — e.g. the `off` value? no.

Hmm.

OK, let me now consider the remaining possibility: the swap is decided by the ORDER in which the operands are USED (the LUIDs) — the index is loaded at 79 and p is materialized at 69-70, so p is EARLIER. Hmm.

In the target's tree (plus p index), p (earlier) is first ✓. In mine (plus index p), the index (later) is first ✗. Hmm, so it's the opposite of the LUID order.

Hmm! So maybe: gcc's canonicalization puts the LATER-defined operand first? Then to flip, I'd need p to be defined LATER than the index. I.e., move p's assignment AFTER the index's load!

But the target has p's materialization (69-70) before the newval load (71-73) hmm. But the INDEX's load is at 79 (after) — hmm! So in the target, p's materialization (69-70) is BEFORE the index's load (79) → p is defined EARLIER. And the target's tree has p first.

And in mine: p's materialization is also at 69-70 (matching) and the index load at 79 (matching) — the same order! But the tree differs. ✗ So the LUID order isn't the discriminator either.

ARGH.

OK. Given the extensive effort, let me record this item as a WALL with best=1 and the evidence. That's honest and useful. Hmm, but score 1 is SO close. Let me try 2 more cheap things with a different flavor:

(a) What if the `p` variable's TYPE changes (e.g. `u8 *p` instead of `D_80195AF6_t *p`)? The C0505 "widths" dial! `u8 *p = (u8 *)D_80195AF6;` hmm, then `(u8 *)p` is a no-op and the address = p + off.

Hmm, the tree: (plus p_reg off_reg) hmm, same.

(b) What if `off` is a `u16`? Then the index would be zero-extended → the tree (plus p (zero_extend off)) → hmm, a different shape! And the target's `addu` hmm.

Hmm, but the index = unk100 * 8 can exceed 16 bits.

(c) What if the whole address is computed as `(u8 *)p + off` where off is the result of a `<<` — tried.

(d) What if I use the "&&/||" fold... no.

(e) **What if the second operand of the add is a CONSTANT-EXPRESSION-based pseudo?** Hmm.

(f) What if the load's address is written as `(u8 *)p + off + 4` vs `4 + (u8 *)p + off`? Hmm.

Let me try (b): `off` as `u32` — tried (v7, same). Hmm.

Let me try (a): p as `u8 *`:
```
            u8 *p = (u8 *)D_80195AF6;
            ...
                D_801270C8 = *(s16 *)(p + off + 4);
```
Hmm, the cast (u8*)D_80195AF6 — the tree = (plus (convert symbol) off). Hmm, the convert of a symbol_ref to u8* is a no-op → the same.

Hmm.

OK. Let me try one thing that might actually matter: the ORDER of the two statements `off = ...` and the load. What if `off` is assigned AFTER the load? no.

Hmm, let me try: the `+ 4` moved into the load's offset differently: `*(s16 *)((u8 *)p + off + 4)` vs `*((s16 *)((u8 *)p + off) + 2)`. Hmm: (s16*)(addr) + 2 = addr + 4 ✓ (the s16 is 2 bytes). The tree: (plus (plus p off) 4) hmm, the +2*2 = 4 → the same.

OK, I'm going to accept a WALL for this item (score 1) and move on to the last item (func_8017D81C), then do the bookkeeping. Actually, hold on. Let me try ONE more: the R-family "REG-caller" dial is the "commutative swap" and the delever_search R-rules can do it. The R-catalog's R2/R4 might be "the commutative swap" rules. Let me look at what R2 and R4 do in delever.py — maybe one of them is exactly "swap the operands of a commutative add" and I can replicate it manually.

Let me grep for R2/R4 docs in delever.py.
