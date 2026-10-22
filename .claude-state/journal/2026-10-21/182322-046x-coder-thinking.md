---
ts: 2026-10-22T00:23:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_xhYcLTCRj0ufjhXCLZlu
---
c5's second block:
```
9cd8: subu v0,a0,v1
9cdc: bgez v0,9cec     ; diff>=0 → shared tail
9ce0: slti v0,v0,16    (delay)
9ce4: subu v0,v1,a0
9ce8: slti v0,v0,16
9cec: bnez v0,9cf8     ; shared tail: return 1
9cf0: li v0,1
9cf4: move v0,zero     ; return 0
9cf8: epilogue
```
That's exactly the FIRST block's shape (merged). The target's second block is unmerged with duplicated tails.

Target second block (7 ins + ...):
```
9cd8: subu v0,a0,v1
9cdc: bltz v0,9cf4
9ce0: slti v0,v0,16
9ce4: bnez v0,9d08
9ce8: li v0,1
9cec: j 9d08
9cf0: move v0,zero
9cf4: subu v0,v1,a0
9cf8: slti v0,v0,16
9cfc: bnez v0,9d08
9d00: li v0,1
9d04: move v0,zero
9d08: epilogue
```
So the target has: the if-arm tests diff<0x10 with bnez to epilogue, and if not, jumps to the epilogue with v0=0; the else-arm recomputes and tests with bnez to epilogue, else falls through to move v0,zero → epilogue.

This looks like: two separate "return" paths, where in the if-arm GCC generated a `j` for the return-0 (because it's not the fallthrough) and in the else-arm the return-0 falls through.

For GCC to generate this, the two arms must be *separate* basic blocks that are NOT merged. The duplication of the tail (li v0,1 etc.) is a consequence.

How to prevent cross-jump merging in real C? The two tails differ in the target? Let's see: if-arm tail = {bnez → epilogue, li v0,1} then {j epilogue, move v0,zero}. else-arm tail = {bnez → epilogue, li v0,1} then {move v0,zero}. These are the SAME code except one has an extra jump. Cross-jump merging would require the if-arm's "return 0" path to jump to 9d04 instead of 9d08 — that's a "jump to jump" threading: `j 9d08` could become `j 9d04`? No, cross-jump doesn't do that (it merges identical blocks by redirecting predecessors' jumps).

Hmm, so why didn't GCC merge in the target? Because merging requires the *predecessor blocks* to be identical too? Cross-jump in GCC 2.7.2: `jump_threading`/`cross_jump` merges two basic blocks with identical instructions when one is a successor of the other in a "cross" pattern. The condition includes that the two blocks have the same number of instructions and the same instructions.

In the target, the if-arm's return-0 block is {j 9d08, move v0,zero} and the else-arm's return-0 block is {move v0,zero} (followed by epilogue). These are NOT identical (one has the jump) → no merge. And the return-1 blocks: if-arm {bnez 9d08, li v0,1} and else-arm {bnez 9d08, li v0,1} — identical! But the bnez is the *last* instruction of a block? The blocks are: [bnez, li v0,1] and [bnez, li v0,1] — but bnez's target is the epilogue in both, so they are separate blocks ending with a jump. Two identical blocks ending in a jump to the same target... cross-jump could merge them (redirect one predecessor). But GCC didn't.

Why? Because of the ASM: the if-arm's return-1 block contains the asm (which, even though empty, creates an ASM_OPERANDS in the RTL) and the else-arm's too. Both have asms but with different operands? In the if-arm, diff is the value from `*(s16*)(s1+0xA) - sum`; in the else-arm, diff is `sum - *(s16*)(s1+0xA)`. The asm in each block references "0"(diff) — the same pseudo name but different values in the two blocks; after the asm, the pseudo is redefined. Hmm, in the merged world, the two asm statements would have to be identical, which they are structurally (same pseudo, same constraints) — so the blocks should be identical and mergeable...

Unless the asm in the if-arm and else-arm have different *modes*? No.

OK here's another thought: maybe the reason is that the two blocks end with `bnez 9d08` (a conditional jump to the epilogue) and the *preceding* code differs. Cross-jump in GCC 2.7.2 requires the two blocks to be "crossjump candidates": same instruction sequence, and each block's *last* instruction is a jump. Here both are {bnez, li} — but the bnez is NOT last (li is). Hmm, the block ends with `li v0,1` and then falls to the next block, which is `j 9d08` in the if-arm and `move v0,zero` in the else-arm. So the block structure:

if-arm: B1: [bnez 9d08, li v0,1] → B2: [j 9d08, move v0,zero] → epilogue
else-arm: B3: [bnez 9d08, li v0,1] → B4: [move v0,zero] → epilogue

Cross-jump would merge B1 with B3 (identical) — but B1 and B3 have different predecessors (the bltz vs the fallthrough) and merging them changes control flow. GCC's cross_jump merges a block with a *copy* of an identical block if the predecessors' jumps are redirected. The condition in GCC 2.7.2 cross_jump: both blocks must have the same number of instructions, and the last instruction of one must be a jump... plus "cross jump" requires the merged block to be entered by a jump.

Whatever. Empirically: the target has B1 and B3 separate, while c1/c5 merged them into one. The difference: the asm. Since B1 and B3 both contain the asm, why aren't they merged? Because the asm's *input* is a pseudo that differs? In the if-arm, the asm's input pseudo is `diff` whose value at that point is the result of `subu v0,a0,v1`; in the else-arm it's the result of `subu v0,v1,a0`. When comparing blocks, GCC compares RTL instruction sequences; the asm operands are the same pseudo (diff), so they'd compare equal...

Unless the asm is not in B1/B3 at all! GCC might place the asm elsewhere (e.g., scheduled into a different position). Since the asm is empty, it produces no code, but it stays in the RTL of some block. Its position in the instruction stream affects block boundaries. The asm is *before* `return 1` in the C, but GCC's expand may move it.

Hmm, so the presence of the asm creates an extra "note" instruction in the block, which might prevent cross-jump from merging because of the block's instruction *count* differing? No, both have it.

Honestly, maybe the reason is subtler: the asm defines diff, so after the asm, `diff` is a *new* pseudo value; the "return 1" then does `li v0,1; jr ra`. The blocks B1 and B3 in the target have identical code.

Wait — maybe GCC *did* try to merge and couldn't because the predecessors' control flow differs: B1 is reached by fallthrough from the `bltz` block; B3 is reached by the taken branch of bltz. Cross-jump merging requires the predecessor of B1 to be a jump to B1 (not a fallthrough) so it can be redirected. In the if-arm, the block before B1 is the bltz block (fallthrough into B1). In the else-arm, the block before B3 is the `subu v0,v1,a0` block ending with a fallthrough into B3. Hmm, both are fallthroughs.

OK. Let me try to think about what the *original game asm* looked like — maybe the original had this unmerged shape naturally, e.g. because the original source (from the decompiler's perspective) had a structure like:

```
if (diff >= 0) {
    if (diff < 0x10) { return 1; }
    return 0;
} else {
    diff = sum - *(s16 *)(s1 + 0xA);
    if (diff < 0x10) { return 1; }
    return 0;
}
```
which is c1 → merged. So the original game's asm is the unmerged one, and the decompiler needed the asm to reproduce it. That's the "NEEDED DIFFERS" comment: the current def doesn't match the original game asm either? Hmm, "NEEDED DIFFERS" might mean the lever was needed to match the *original* asm, not the current build.

WAIT. This is important! Maybe the score target is NOT the current build but the ORIGINAL game asm. Let me re-read the brief: "`delever_search.py --try <TU> <fn> <file> --body` (score 0 = MATCH; compares with the function in build/)". Hmm, "compares with the function in build/". And the target I disassembled (build/src/ov_SC06_029/ov_SC06_029_jr_8017C954.o) DOES contain the asm's effect (the unmerged shape). So build/ = the current def's output. Confirmed by the fact that orig.c scored 0 (66 ins) and the build object has 66 ins.

So the target is the current build. The current build has the unmerged shape (as produced with the asm). To match without the asm, I need the unmerged shape from plain C.

So: what plain C produces the unmerged shape? The target shape has B1 and B3 separate, i.e. GCC did NOT merge the two "return 1" blocks, and the "return 0" blocks are separate too (one with a j).

Idea: if the two arms' code differs in a way that prevents merging — e.g. if in one arm the comparison uses a *different* pseudo. But the code shape must stay the same.

What if the else-arm's recomputation is expressed so that the *register* differs, e.g. `diff = sum - *(s16 *)(s1 + 0xA);` (subu v0,v1,a0) — already.

Hmm, what if the difference is that in the if-arm, the comparison is `diff < 0x10` and in the else-arm `diff < 0x10` but the *value* is in a different pseudo → c2 tried (diff2) and got the same 13 as c1. Hmm, c2 gave the same as c1 — meaning GCC merged anyway.

What made the target unmerged? The asm. In GCC, an asm statement creates an "ASM" insn in the RTL; cross_jump compares blocks with `sibling` function which requires the two blocks to have the same number of insns and matching insns. Two ASMs with the same operands compare equal...

Hmm, unless the asm in the if-arm is in a different position: maybe GCC placed the if-arm's asm in the block *before* B1 (e.g. in the bltz block, since the asm is only executed on the taken path...). Actually, since the asm is inside `if (diff<0x10) { asm; return 1; }`, the asm belongs to the return-1 path.

Hmm, hold on! Maybe the asm is in the block containing the *comparison* (before the branch), because GCC's expand might place the asm before the branch on the "diff<0x10" test... no.

Let me look at this from a different angle: get the GCC RTL dump for the function with the asm, using tools/cc1_dumps_tu.sh. That would show the block structure and how the asm sits, and where the merge was blocked. But dumps are disk-heavy (Disk capped ~4GB free). The brief mentions hdump.sh and cc1_dumps_tu.sh for header items and alloc tables.

Alternatively — empirical brute force: try a bunch of C spellings and see which gives 66 ins with the right shape. Let me think about which spellings could yield an unmerged tail:

(1) Make the two arms' "return 1" blocks differ in a *value-producing* way that yields the same instructions. E.g. in the else-arm: `return 1;` and in the if-arm: `return 1;`...

(2) Use a `goto`:
```
if (diff >= 0) {
    if (diff < 0x10) goto ret1;
    goto ret0;
}
diff = sum - *(s16*)(s1+0xA);
if (diff < 0x10) goto ret1;
ret0: return 0;
ret1: return 1;
```
This gives a shared tail → merged shape.

(3) Duplicate the code so the two arms are textually distinct but instruction-identical:
```
if (diff >= 0) {
    if (diff < 0x10) { return 1; }
    return 0;
}
{
    s32 d = sum - *(s16 *)(s1 + 0xA);
    if (d < 0x10) { return 1; }
    return 0;
}
```
Same as c1.

Hmm. What if the difference is that in one arm the *value compared* is a different pseudo, AND the return value differs in a way that yields the same instruction: e.g. if-arm `return 1;` else-arm `return 1;`.

What if the if-arm returns `1` and the else-arm returns `1` but one is `return 1;` and the other `return (s32)1;`? Folds.

Hmm, think about what makes blocks non-mergeable in cross_jump: the function `cross_jump` in GCC 2.7.2 (jump.c) checks:
- both blocks have the same number of insns
- for each pair, `sibling` (same insn type and operands)
- the last insn of b1 must be a jump (for the "cross" case) or ...

Actually cross_jump only merges when the *last* instruction of one block is a conditional jump and the other is an unconditional jump to the same target — "cross jump" = swapping. There's also `jump_threading` (thread.c) which redirects a jump to a block whose only successor is the same as the jump's target — that's the "jump to jump" threading.

The merge I observe (c1/c5 merging two tails into one) is probably jump_threading/cross_jump at the RTL level.

Given the difficulty, maybe the answer lies in a completely different rewrite: make the *second block* structurally like the *first* block in the target but with the extra instructions. Wait...

Actually, let's look at the target's second block once more and compare with the FIRST block of the target:

First block (no asm):
```
9c54: subu v0,a0,v1
9c58: bgez v0,9c68
9c5c: slti v0,v0,16   (delay)
9c60: subu v0,v1,a0
9c64: slti v0,v0,16
9c68: bnez v0,9cfc   ; shared
9c6c: li v0,1
9c70: jal ...        ; continue (fallthrough after the shared tail)
```
So the first block's tail {bnez, li v0,1} is SHARED between the two arms. Then the fallthrough continues.

Second block (with asm):
```
9cd8: subu v0,a0,v1
9cdc: bltz v0,9cf4
9ce0: slti v0,v0,16
9ce4: bnez v0,9d08
9ce8: li v0,1
9cec: j 9d08
9cf0: move v0,zero
9cf4: subu v0,v1,a0
9cf8: slti v0,v0,16
9cfc: bnez v0,9d08
9d00: li v0,1
9d04: move v0,zero
9d08: epilogue
```
Here the tails are NOT shared: the if-arm has {bnez, li v0,1, j, move v0,zero} and the else-arm has {bnez, li v0,1, move v0,zero}.

Note the difference between the two blocks: the first block's "if (diff<0) diff = ..." structure has the *recompute* in the negative arm, and the "return 1" test is shared afterwards. The second block's structure has the recompute in the else arm and the test duplicated.

Interesting: the first block's source is:
```
diff = D_80126B62 - sum;
if (diff < 0) { diff = sum - D_80126B62; }
if (diff < 0x10) { return 1; }
```
i.e. the test is AFTER the if — a single test. That's why it's shared.

The second block's source:
```
diff = *(s16*)(s1+0xA) - sum;
if (diff >= 0) { if (diff < 0x10) { asm; return 1; } return 0; }
else { diff = sum - *(s16*)(s1+0xA); if (diff < 0x10) { asm; return 1; } return 0; }
```
The C source duplicates the test — the decompiler wrote it that way (probably from the original asm). If instead I write it in the FIRST block's style:
```
diff = *(s16*)(s1+0xA) - sum;
if (diff < 0) { diff = sum - *(s16*)(s1+0xA); }
if (diff < 0x10) { return 1; }
return 0;
```
That's semantically equivalent? Let's check: original: if diff>=0: test diff<0x10 → 1 or 0; else: recompute diff = sum - x, test → 1 or 0. The new version: if diff<0 → diff = sum - x; then test diff<0x10 → 1 else 0. Since in the else branch diff<0 → recompute; and the original's else branch is diff<0. Yes! Equivalent: original's "diff>=0" branch tests the original diff; new version tests the original diff when diff>=0 (no recompute). Same.

But: the resulting code shape would be the FIRST block's shape (shared tail) — that's c5-like, not the target's unmerged shape. So no.

So the target's second block genuinely has duplicated tails, which plain C in this style doesn't produce...

UNLESS the target's build was NOT produced from this source! Wait — the build/ object was built from the current src. Let me double check that the build object corresponds to the current src (with the asm). The orig.c (with asm) scored 0 vs the build object → yes, identical.

So with the asm, GCC produces the unmerged shape. Fine.

So the question remains: what plain C produces the unmerged shape?

Insight: maybe the asm's presence is not what unmerges; maybe the *first* block's shape (shared) and the second's (unmerged) differ because of the *return value* semantics. In the first block, the "return 1" path is followed by MORE code (the second part of the function), so the tail {bnez, li v0,1} is a "return" that exits the function — the fallthrough continues the function. In the second block, the "return 1" and "return 0" are the last thing in the function.

In c1, the second block's tails merged into a single {bnez, li v0,1, move v0,zero}? Actually c1 produced:
```
9cd8: subu v0,a0,v1
9cdc: bltz v0,9cec
9ce0: nop
9ce4: j 9cfc
9ce8: slti v0,v0,16
9cec: subu v0,v1,a0
9cf0: j 9cfc
9cf4: slti v0,v0,16
9cf8: move v0,zero
9cfc: epilogue
```
Here BOTH arms jump to the epilogue (9cfc) and the "return 1" (li v0,1) is GONE. So GCC 2.7.2 generated *broken* code (returning 0 always). That's a delay-slot bug: it moved `slti` into the delay slot of `j 9cfc` and lost the bnez. Wow.

Hmm, actually maybe not broken: `slti v0,v0,16` in the delay slot of `j 9cfc`... and then v0 is overwritten by `move v0,zero` at 9cf8. So yes, the return-1 path is gone. Broken code — but the score doesn't care about semantics, only instructions.

OK so in c1, GCC's RTL-level structure differs a lot. The target (with asm) has the correct structure.

So: the asm forces GCC to keep the comparison in a register and branch on it. The key difference might be: with the asm, `diff` is a *pseudo* that must live in a register across the branch; without it, GCC turns the comparison into a branch on the *expression* directly (compare-and-branch), and then the "return 1" case...

WAIT. That's it! Without the asm, GCC does "compare and branch" optimization: `if (diff < 0x10) return 1;` becomes a single branch (bltz/bgez style) without materializing the boolean. With the asm, diff must be in a register at the asm point, so GCC must compute the comparison into a register (slti) and branch on it.

Look at the target: `slti v0,v0,16` then `bnez v0` — a materialized boolean. In c5: also `slti v0,v0,16` then `bnez v0` (shared tail). So c5 also materializes. Hmm.

But in c1, the slti is in the delay slot of the j and the bnez vanished — that's the compare-and-branch folding gone wrong.

So the real difference: c1 (13) has 63 ins, c5 (8) has 62, target 66.

Let me now think about the target's extra instructions vs c5:
target: 66 ins. c5: 62. Difference of 4: the target duplicates {bnez, li v0,1} (2) and {move v0,zero} + {j} (2)?

c5's second block: 9cd8 subu, 9cdc bgez, 9ce0 slti, 9ce4 subu, 9ce8 slti, 9cec bnez, 9cf0 li v0,1, 9cf4 move v0,zero = 8 ins.
target's second block: 9cd8 subu, 9cdc bltz, 9ce0 slti, 9ce4 bnez, 9ce8 li, 9cec j, 9cf0 move, 9cf4 subu, 9cf8 slti, 9cfc bnez, 9d00 li, 9d04 move = 12 ins.
Difference = 4. Yes.

So I need the unmerged version. To get GCC to not merge the two "return 1" blocks, the blocks must differ. In the target they differ by... the ASM (which is in the return-1 path of each arm).

Hmm, unless the asm is in a DIFFERENT position in each arm, making the blocks differ!

In the if-arm, the asm's input is diff = (x - sum) computed in v0; in the else-arm, diff = (sum - x) also in v0. Same.

But the *output* of the asm: "=r"(diff) — after the asm, diff is a new value in a register. Then `return 1` sets v0=1. In the if-arm, the asm's output register must be allocated... In the target, the li v0,1 is in the delay slot; the asm output could be in v0 too (same reg, since GCC coalesces). So both arms: asm output in v0.

So the two asm statements have identical RTL? If the RTL is identical, cross_jump would merge them. It didn't. So maybe the RTL differs in some subtle way (e.g. the asm in one arm is scheduled differently, or one arm's asm is in a block with a different label).

I wonder: maybe the merge in the target was prevented because the *predecessor* of the else-arm's return-1 block ends with a *fallthrough* and cross_jump requires jump predecessors.

Let me try: in the else-arm, the recompute `diff = sum - *(s16 *)(s1 + 0xA);` — what if I write it so the else-arm's test is preceded by a jump? E.g., use goto:

```
if (diff >= 0) {
    if (diff < 0x10) { return 1; }
    return 0;
} else {
    diff = sum - *(s16 *)(s1 + 0xA);
    if (diff < 0x10) { return 1; }
    return 0;
}
```
vs
```
if (diff < 0) {
    diff = sum - *(s16 *)(s1 + 0xA);
    if (diff < 0x10) { return 1; }
    return 0;
} else {
    if (diff < 0x10) { return 1; }
    return 0;
}
```
(c3, 61 ins, score 12) — the arm order matters! c3 = 61 ins, so it produced something different from c1's 63. The target is 66.

Given the target has "bltz" (diff<0 → jump to the else part at 9cf4) and the fallthrough is the >=0 arm, the target's structure matches c1's arm order (if-arm = diff>=0 first).

In c1: 63 ins. Target: 66. c1's shape:
```
subu v0,a0,v1
bltz v0,9cec
nop
j 9cfc        (return 0 path)
slti v0,v0,16
9cec: subu v0,v1,a0
9cf0: j 9cfc
9cf4: slti v0,v0,16
9cf8: move v0,zero
```
Interesting: c1's if-arm (diff>=0, fallthrough at 9ce4): `j 9cfc` (return 0) with delay slti — the slti is dead, and the "return 1" is missing. So GCC decided "if (diff<0x10) return 1" is FALSE always?? That is a real GCC 2.7.2 bug (the compare-and-branch expansion). Or... hmm, maybe not: maybe GCC decided the `bnez` was unnecessary because... no, it's necessary.

Hmm hold on, maybe I should reconsider: maybe in c1, GCC decided that the value `diff` at that point is *known* to be >= 0x10 or < 0 ... no.

Wait, actually: maybe GCC 2.7.2's "expand" of the comparison `diff < 0x10` where diff = x - sum: it might have used the *branch* on the slti result computed in the delay slot of the bltz (9ce0: nop in c1, slti in target). In c1 the delay slot of bltz is nop and the slti went to the j's delay slot.

I'm burning time. Let me consider the bigger picture: 11 items, each with a launder lever. This one is hard (it's a "WALL" candidate). I should timebox: the brief says 20-30 min per item, past 30 min stop and record a wall. I've used ~15 min on item 1. Let me try a couple more promising candidates, then move on and record a WALL if needed.

Promising ideas remaining:
(a) Give the two arms different *pseudo* names AND different code but same instructions: c2 did diff2 in else-arm → 13 (same as c1).
(b) Make the else-arm's comparison use a different but equivalent expression, e.g. `if (diff < 0x10)` vs `if (0x10 > diff)`: probably identical.
(c) Use unsigned/signed mix: `if ((u32)diff < 0x10)` → different asm (sltiu? no, same slti with different reg). Actually (u32)diff < 16 → slti v0,v0,16 — same instruction! And the RTL differs (unsigned compare) → blocks differ → no merge! But the branch would be `bnez` (nonzero) either way. Hmm, but the *comparison* for signed `diff<0x10` and unsigned `(u32)diff<0x10` produce the same slti. The RTL differs (different comparison mode) → cross_jump won't merge the blocks! That could give the unmerged shape.

But careful: signed vs unsigned changes the branch condition: for signed, `diff < 0x10` is true iff diff <= 15; for unsigned, (u32)diff < 16 is true iff diff in [0,15] as unsigned — different semantics for negative diff! In the else-arm, diff = sum - x could be negative → semantics differ. Since we only need to match the *asm* (and the asm would be the same slti), semantics don't matter for scoring, but the project cares about correctness (decomp). Hmm, the "diff" in the else arm: sum - x where sum and x are s16-ish. Could be negative. The original code: `diff < 0x10` signed. Using unsigned would be wrong. But wait — in the else-arm, the original C is `diff = sum - *(s16*)(s1+0xA); if (diff < 0x10)`. If diff is negative, signed comparison gives true (return 1) whereas unsigned gives false. That's a semantic difference — not acceptable for a decomp (though the score wouldn't notice). Hmm. But the *original game asm* used slti (signed). So signed it is.

Alternatively use `(s16)diff < 0x10`? That changes the asm (lh instead of slti). No.

(d) Force different block structure with a `goto`:
```
if (diff >= 0) {
    if (diff < 0x10) { return 1; }
    goto ret0;
}
diff = sum - *(s16 *)(s1 + 0xA);
if (diff < 0x10) { return 1; }
ret0: return 0;
```
This shares the ret0 → merged shape probably.

(e) Duplicate the whole computation in both arms so they're textually different but instruction-identical. E.g. in the if-arm, write `diff = *(s16 *)(s1 + 0xA) - sum;` again (a real 2nd set!) inside the if:

```
s32 diff = *(s16 *)(s1 + 0xA) - sum;
if (diff >= 0) {
    diff = *(s16 *)(s1 + 0xA) - sum;   /* real 2nd set */
    if (diff < 0x10) { return 1; }
    return 0;
} else {
    diff = sum - *(s16 *)(s1 + 0xA);
    if (diff < 0x10) { return 1; }
    return 0;
}
```
The extra "real 2nd set" in the if-arm might change the RTL (a new set of diff) and prevent the merge, while generating the same instructions (the recomputation is CSE'd away — hmm, cse would fold it, giving the same RTL again).

Hmm. But note moves.md has successful launder cracks of exactly this form: "launder->real 2nd set pv = *p; pv &= 0xFF000000". So a real 2nd set that survives cse is the way. A recomputation identical to the first would be folded by cse (cse:840 make_regs_eqv).

(f) What if the real 2nd set uses a *different but equivalent* expression, e.g. in the if-arm: `diff = (s16)*(s1+0xA) - sum;` — same.

Hmm, what about making the 2nd set in the if-arm be `diff = sum - sum + diff;`? weird.

(g) What about the possibility that the *whole* second block should be written in the "first block" style but with an extra twist to duplicate the tail? Like:

```
s32 diff = *(s16 *)(s1 + 0xA) - sum;
if (diff < 0) {
    diff = sum - *(s16 *)(s1 + 0xA);
    if (diff < 0x10) { return 1; }
    return 0;
}
if (diff < 0x10) { return 1; }
return 0;
```
This is the "first block" style with the test duplicated manually! Semantically equivalent. And the code shape: the two "return 1" blocks are separate in the source (not merged by the source structure), but GCC's cross-jump may still merge them since they're identical... but maybe the merge requires identical predecessors, and here the predecessors differ (one ends with a fallthrough from the recompute, the other from the bltz). In the target, the if-arm's return-1 block's predecessor is the bltz block (fallthrough) and the else-arm's is the recompute block (fallthrough). Same situation.

Hmm, but the target's shape is:
```
bltz v0,9cf4
slti (delay)
bnez → epilogue
li v0,1
j epilogue
move v0,zero
9cf4: subu v0,v1,a0
slti v0,v0,16
bnez → epilogue
li v0,1
move v0,zero
epilogue
```
This is EXACTLY the shape of my (g) formulation! The if-arm: {bnez, li v0,1} then {j, move v0,zero}; the else-arm: {bnez, li v0,1} then {move v0,zero}.

And in c1 (same structure but with if/else), GCC merged them into one tail. The difference between (g) and c1: in c1 the else-arm is an `else {}` block; in (g) it's straight-line code after the if. That might change the RTL block structure and prevent the merge!

Let me try (g). Also try (h): (g) but with the if-arm first:
```
if (diff >= 0) {
    if (diff < 0x10) { return 1; }
    return 0;
}
diff = sum - *(s16 *)(s1 + 0xA);
if (diff < 0x10) { return 1; }
return 0;
```
Hmm, this is c1 minus the else-block. The `return 0` inside the if-arm vs the fallthrough `return 0` after — different.

Let me write (g) and (h) and test both. Also (i): (g) with the negative-arm first.

Time check: 18:35ish. Let me move fast.
