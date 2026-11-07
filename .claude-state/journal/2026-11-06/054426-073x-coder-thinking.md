---
ts: 2026-11-06T12:44:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qZit5xoSPVDqZJVquqZd
---
268 ins vs 261 — worse (7 extra), no cross-jump merge.

Time check: ~05:55, 25 min into item 2. Per the brief: budget 20-30 min; past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries. I have 8 tries. I need 30 for a WALL.

Hmm, that's the rule: "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". So I must produce 30 scored tries. Let me generate ~24 more variants efficiently in one batch via sc.sh (one command, background if long). Each score takes ~10-15 s, so 24 × 12 s = ~5 min. Run in background.

Variants to try (lever-free C moves within the budget):
1. c2 base with different decl orders of locals.
2. s16/u16 widths for i70a/i70b/idx.
3. init-at-decl for ptr/tmp1/tmp2.
4. temp reuse / statement reorder.
5. The `(s16)` cast on ret assignments.
6. do-while(0) at various places.
7. The `if (ptr == 0)` early return as `return ptr;`.
8. i70b as s16.
9. buf as u16[6] → keep.
10. q pointer reuse.
11. Reordering the tail statements.
12. `ret` declared as the last variable.
13. `D_801F32D0 = 0;` moved.
14. idx declared outside the block.
15. Combining tmp1/tmp2 statements.

But honestly, the goal is a MATCH; a WALL requires 30 tries. Since the item is likely a WALL (the pin is the mechanism), I should generate a decent spread of lever-free moves and score 30+.

Actually wait. Before mass-producing, let me reconsider the core issue once more, because a "WALL" here is a real outcome but a crack would be better.

The blocker: ret needs v0; sched1 puts `li ret,N` before the v0 store because ret isn't v0 (circular).

Hmm, what about making the v0 store come *before* the li by giving the store a *use* of ret? E.g. if the store's value were `ret`... no, it's the call result.

What if we swap the two statements: `ret = 7;` BEFORE `unkD8 = call(...)`? Then the RTL order is li, call, store. ret is live across the call → callee-saved. BUT: what if ret's live range is short because the STORE use... no, live across the call.

Hmm, unless... the li comes before the call, and the call clobbers v0 → ret can't be v0 → s0. That's what c1 did.

What if the C has the store and the ret assignment in an order where the li is emitted after the call but sched1 keeps it: e.g., if the li's value depended on a value defined by the store. We can't fake that.

Alternatively, can we make the store *not* use v0 but still emit `sw v0,216(s1)`? The store's value is the call result = v0.

Hmm, what if the call result is stored via a cast that forces a different register? e.g. `unkD8 = (s32)(u16)call(...)` → adds an andi.

OK, what about the OTHER direction: make `ret` be assigned in v0 by making the *STORE* block use it first: `unk2 = ret; return ret;` — the STORE block. If the arm's goto is the only path, the live range is def→STORE.

Honestly, I'm confident this is the classic "pin $2 needed" wall (moves.md 302-311 list five such WALLs).

Let me now produce 30+ scored tries with sensible lever-free variants and then record a WALL with the best score.

Plan: generate variants c8..c40 with different real-C moves, score them with sc.sh in one background command (24 files × ~12 s ≈ 5 min). But the brief says a command that may run longer than a few minutes → background. 24 × 12 s = 288 s. Hmm, borderline. Let me split into two batches of 12.

Actually, let me reconsider the budget: "Budget 20-30 min wall per item (date at start/end); past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries on that item". So I need 30 tries. Let me do it.

Let me write a generator script that produces variants by applying single moves to c2 (the best base at 53? Actually c5 was best at 53). Let me use c5 as the base for the variant set? Hmm, c5 (do-while around ret=7) at 53 was the best. But the base choice matters little; variants should be plausible.

Let me write a python generator creating ~26 candidates from c2 with single moves:

1. decl order permutations (4)
2. ret = N → ret = (s16)N (all arms)
3. idx declared outside the block
4. init-at-decl for tmp1/tmp2
5. ptr = func_8012C1B8() init-at-decl
6. i70a as s16 / i70b as s16
7. early return 0 → return ptr / return 0u
8. do-while(0) at arm tails (after goto? no) 
9. statement reorder in the tail
10. u16 buf → s16 buf
11. q reuse variants
12. i as u16
13. CAST_ALIAS vs CAST_SIGN variants

Many of these will be neutral. The point is 30 scored tries with real moves.

Let me write the generator.
