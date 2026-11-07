---
ts: 2026-11-06T05:02:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pVFsvdi2srVMnmuKqxrP
---
Now the ONLY remaining difference is the s0/s1 register swap: `base` ↔ `a1`. All instructions match otherwise. Score 24 (MIXED).

So I need to swap the register allocation of `base` (D_80078E78) and `a1`. Target: a1→s1, base→s0. Mine: a1→s0, base→s1.

This is a global-alloc priority issue. The moves catalog mentions "greg-pri-refs" and similar. The do-while added loop-weighted refs to a1 (inside the loops), pushing a1 above base.

In the target (with the asm barrier), a1→s1 and base→s0. Which pseudo has higher priority? Global-alloc assigns registers in order of priority; for MIPS, the order of s-regs in `REG_ALLOC_ORDER`... Let me think: if a1→s1 and base→s0, and s0 is allocated before s1, then base had the higher priority.

In mine, a1→s0 → a1 has the higher priority. So the do-while's loop-weighting of a1's refs pushed a1 above base.

How to fix: reduce a1's priority or raise base's. Real-C moves:
- Add a ref to `base` somewhere (e.g., use base in the first half instead of the absolute symbols)? That changes the code.
- Avoid the loop-weighting: put the do-while around something that doesn't contain a1 uses. In r1 (do-while around the ifs), the a1 uses aren't inside the loop... but r1 also gave 38 with the same swap. Hmm! In r1, the do-while wraps the `if ((s16)D_80078EA6 >= 0xA1) {...}` which contains `D_80078EA4 = 0xA00000` (no a1). So why did a1's priority rise?

Maybe the swap isn't due to loop-weighting but due to the block structure change (live ranges). Hmm.

Let me test: does the swap happen with the do-while only at site 3? r4 gave 78/107 (the order issue remained). Let me test the register assignment with a variant that fixes only the order without any do-while...

Actually, let me think about global-alloc's priority: `REG_N_REFS * (loop_depth?)`. In flow.c, `REG_N_REFS` counts references, and `REG_LIVE_LENGTH`. The priority for allocation is `floor_log2(refs) * refs / live_length` or something (allocno_compare in global.c). Let me look at the actual formula in global.c.

Actually, the moves catalog line 8: "keepalive: k/j pri 1917/1891 beat m24 1428". So priority = something like refs^2/live? Let me check global.c's allocno_compare:

```
static int
allocno_compare (v1, v2)
{
  ...
  /* Process insns in the order of increasing priority... */
  i = (int) ((floor_log2 ((int) allocno1->n_refs) * allocno1->n_refs)
	     / (allocno1->live_length / 10 + 1));
```

Something like that. So priority ≈ log2(refs)*refs / (live_length/10+1).

The do-while changes live_length (the insns inside a loop are weighted?) and n_refs.

To raise base's priority: increase base's refs or decrease its live length. base = D_80078E78 is used 6 times in the second half. In the target, base is used 6 times (lw/sw/lh × 3 blocks × 2 insns?). Hmm.

Wait — in the target, base (s0) is used for the second half: `lw v0,96(s0)`, `sw v0,96(s0)`, `lh v0,98(s0)` etc. — 9 uses maybe. And a1 (s1) is used in `addu v0,v0,s1` (6 uses).

In mine, a1 got s0. So a1's priority > base's. To flip, I could add a use of base or reduce a1's.

Options:
- Use `base` in the first half: e.g., access D_80078EA4 through base+0x2C? Reloc mismatch.
- Add a dummy use of base that doesn't emit code? E.g., a dead `if (base) ...`? That emits code.
- A `do-while` around a block containing base uses to loop-weight them (like the a1 effect). E.g., wrap the second-half stores in do-while — but they're already correct and wrapping changes things.

Hmm, the cleanest: apply the same loop-weighting trick to a block containing base uses, so base's priority rises. The second-half code uses base. If I wrap those in do-while, the refs become loop-weighted. But that might break the second half's scheduling.

Alternatively, reduce a1's loop-weighting: instead of `do { D_80078EA4 += a1; } while (0)`, use a different block-splitting construct that doesn't involve a1. r1 wrapped the *if* (which doesn't use a1) and still had the swap... so maybe the swap isn't from a1's loop-weighting.

Hmm, wait: in r1, the do-while wraps the if. But the *store* is immediately before. Maybe the block split causes the store to be in the previous block, and something about the flow changes.

Let me test the swap in a simpler setting: take v1 (no do-while, score 55) — did it have the s0/s1 swap? Looking at the earlier v1 diff: mine[8] beqz s2 (same), and the code used s1 for a1: `addu v0,v0,s1` at mine[14]. So v1 had a1→s1, base→s0 (correct!). So the swap was introduced by the do-while.

So the do-while (regardless of placement) flips the allocation. Because it changes the live ranges/refs.

Which do-while placement is minimal? r4 (only site 3's store) gave 78/107, and the order issue remained in blocks 1/2. Let me check r4's register assignment — if r4 keeps a1→s1, then the swap comes from wrapping sites 1/2 or the ifs.

Let me test a variant: apply the do-while to sites 1,2 only (r2, 38) — check its regs. It showed the swap in the earlier diff (r1). Let me check r2.

Actually, let me test: do-while at site 1 only; do-while at site 2 only; do-while at site 3 only (r4); and the inner-if fix combined with each. The goal: fix the order in blocks 1,2,3 while keeping a1→s1.

Let me think about why the swap happens: the do-while makes the block a "loop", and flow.c adds loop_depth weighting to refs inside. The `D_80078EA4 += a1` uses a1 inside the loop → a1's refs get weighted up. In r1 (if wrapped, no a1 inside), why the swap? Hmm, maybe the if body contains `D_80078EA4` uses, not a1. So a1's refs shouldn't change.

Unless the do-while around the if changes the *live length* of a1 (a1 is live across the loop) and the priority formula uses live_length. a1's live length might decrease (since the loop block is counted differently), raising a1's priority.

Hmm. Let me get the allocation table to see the priorities. tools/alloc_table.py is available (used by hdump.sh). That would show the refs/live/prio for each pseudo. Let me run hdump.sh with t2 (the 24-score body) and look at the alloc table, comparing with the target... but the target's allocation is from the original (with asm). Hmm, alloc_table gives my allocation only.

Alternatively, use the moves catalog: to raise base's priority, add refs. E.g., a "keepalive"-like move is a lever (not allowed). But a real 2nd use of base that doesn't change the code? Impossible.

Hmm, what about changing the *declaration order* of the locals? `base` is declared first, then `a1` is a parameter. Parameters are pseudo-allocated before locals? The allocno order can affect ties. The brief allows "decl order/scope" moves.

What if I declare a local `s32 a1v = a1;` and use a1v? That changes refs.

Let me try the simplest: change the order of the declarations or introduce the base pointer differently. E.g., `u8 *base; base = D_80078E78;` (assign at use, not at decl) — this changes the live range of base (shorter) → higher priority! The target has `lui s0; addiu s0` early in the prologue, so base is set at the top. But a shorter live range for base in the source might still produce the same prologue.

Wait, base is used only in the second half. If we assign `base = D_80078E78;` just before the second half (after the first half), the live range shrinks → priority rises → base might get s1 (higher) — that's the wrong direction! We want base to get s0 and a1 s1. Currently base→s1 (higher priority than a1). We want base→s0 (lower priority than a1). So we need to *lower* base's priority or raise a1's.

Hmm, wait: which of s0/s1 is assigned first? In the target, a1→s1, base→s0. If allocation goes s0 first (higher priority → s0), then base had the higher priority in the target. In mine, a1→s0 → a1 higher. So in the target, base > a1; in mine, a1 > base. So the do-while raised a1 above base (or lowered base).

To restore, raise base's priority or lower a1's. Since the do-while is around the a1-using store, wrapping it loop-weights a1. So maybe use a do-while that does NOT contain the a1 use. In r1, the do-while wraps the if (no a1) — yet the swap persisted. Let me verify r1 actually has the swap... The r1 diff showed `register pairs (mine -> target): s1->s0 x16, s0->s1 x7` — yes, swapped.

Hmm, so even wrapping the if causes it. Maybe the do-while changes the live_length of a1 because a1 is live across the loop, and loop weighting applies to live ranges too.

What if the do-while is placed *after* the last a1 use? E.g., wrap only the third block's inner if (site 20) — s3 gave 55/107 (no order fix in blocks 1/2, and did the regs swap?). Let me check s3's diff for the swap. If s3 has no swap, then the swap comes from the earlier do-whiles.

Let me check s3 quickly.

Actually, let me be systematic and use alloc_table.py to see the priorities. Run hdump.sh for t2 and v1 and compare the alloc tables for base and a1. That will tell me the refs/live/prio.

hdump.sh <includer TU> <header basename> <body.c> <outdir> <tag>. The includer TU is src/ov_MAIN_012/ov_MAIN_012_jr_801458E0.c and the header basename is func_8014B944.h.

Let me run it for v1 and t2.
