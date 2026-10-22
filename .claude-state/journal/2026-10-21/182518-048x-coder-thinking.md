---
ts: 2026-10-22T00:25:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_eMPrJQbnrCvqJ2Znmx9L
---
c8's second block (9cd8-9cf0):
```
subu v0,a0,v1
bgez v0,9ce8
nop
subu v0,v1,a0
9ce8: j 9cf4
9cec: slti v0,v0,16
9cf0: move v0,zero
```
Again the "return 1" path is GONE (no li v0,1, no bnez). GCC 2.7.2 drops the comparison when it can put the slti in a delay slot. This is the same bug as c1.

So the pattern: whenever the two arms are separate and GCC can schedule the slti into a delay slot of a jump, the branch on it is lost. In the target (with asm) the bnez survives.

Interesting: in the target, the slti is in the delay slot of the bltz and the bnez follows immediately. In c8, the slti is in the delay slot of the `j` and the bnez is lost.

So the "correct" structure requires the slti to be in the delay slot of the *conditional* branch (bltz), not of a jump.

In the FIRST block (target), the structure is:
```
bgez v0,9c68
slti v0,v0,16    (delay of bgez)
...
9c68: bnez v0,9cfc
9c6c: li v0,1
```
Here the slti is in the delay of bgez and the bnez survives! (Both arms merged into the shared tail.)

So the first block (no asm) DOES produce a correct structure with slti in the delay slot of the conditional branch. The difference in the second block: the "return 1" tail is duplicated per arm and the return-0 tail too.

Hmm hold on. In the first block, the arms are: {diff<0 → recompute} and {fallthrough}. The shared tail is {bnez, li v0,1}. The if-arm's path: bgez → 9c68 (the shared tail) — jump, not fallthrough! The else path: fallthrough into 9c60 (recompute) then falls into 9c68.

So in the first block, the tail is reached by a jump from one arm and by fallthrough from the other, and the tail is NOT duplicated.

In the second block (target), the two arms each have their own tail. The difference: the second block's if-arm test is *inside* the arm (`if (diff<0x10) {asm; return 1;} return 0;`), while the first block's test is *after* the if.

So the target's second block shape corresponds to source:
```
if (diff >= 0) {
    if (diff < 0x10) { return 1; }   // with asm
    return 0;
} else {
    diff = ...;
    if (diff < 0x10) { return 1; }   // with asm
    return 0;
}
```
and GCC (without asm) merges these into a wrong shape.

What if the source is written so that each arm's test-and-return is a *separate basic block* that GCC won't merge, e.g. by using `goto` to a label placed inside each arm? Like:

```
if (diff >= 0) {
    if (diff < 0x10) { return 1; }
    return 0;
}
```
The merge happened in c1 (if/else version). Hmm.

Wait, actually, maybe the merge is a *jump threading* of the "return 1" blocks: both arms' {bnez → epilogue, li v0,1}. Since the target has them separate, GCC didn't thread. In c1 GCC threaded them into one.

What if the two arms' "return 1" blocks differ in the *register* used for the branch condition? E.g. in the if-arm the value is in v0 and in the else-arm also v0 (target). Hmm, same.

What if the two arms' "return 1" blocks differ in the *value* returned? Both return 1.

OK here's another thought: what if the difference is that in the target, the "return 1" blocks contain the asm, and the asm's *input* operand is a different pseudo in each arm. When GCC compares the two blocks for merging, the asm insn in the if-arm has input = pseudo_diff (mode SI) and in the else-arm input = pseudo_diff (same pseudo). Since the pseudo is the same, the insns look identical... BUT the asm's *output* redefines the pseudo diff. In the merged block, the value of diff before the asm would be ambiguous.

Ugh. Let me try an entirely different tactic: maybe the shape can be forced by making the *value* of the comparison come from different registers in the two arms, e.g. by using two different variables for the two arms' values (c2 tried diff2 in else arm → 13, same as c1; c2's shape might be the "merged" one).

Let me try: make the if-arm's value a *different pseudo* AND the else-arm's too, with an intervening real statement.

Alternatively — accept and try the "unsigned compare" trick to make the RTL differ:
else-arm: `if ((u32)diff < 0x10)` → slti v0,v0,16 (same insn) but RTL compare is unsigned (CCLTU). The branch for unsigned "!= 0" is still bnez. This makes the two blocks' RTL differ → no merge → duplicated tails! And the *instructions* would be identical.

Semantics: (u32)diff < 0x10 vs diff < 0x10 differ for negative diff. In the else-arm diff = sum - x. Is it possible for the original code to have negative diff there? The original game asm has `slti` (signed) so the original semantics is signed. Using unsigned would produce the same asm but wrong semantics. That's a fidelity issue for the decomp — the project cares about matching the original game asm, and the asm is identical, but the C semantics would be wrong for negative values. Since the asm matches, the *game* behavior is identical (the compiled asm is what runs). So a C that compiles to the same asm is "correct" for the decomp goal, even if the C source's abstract semantics differ. But it's ugly and could be flagged.

Hmm, but wait: signed `diff < 0x10` where diff is s32: GCC generates `slti v0,v0,16` + `bnez`? For a signed compare with a constant, GCC 2.7.2 generates slti (which is signed) then bnez. For unsigned `(u32)diff < 0x10` it'd generate `sltiu`? No: for unsigned compare with 16, since 16 fits in the immediate, GCC uses `sltiu` (set if less than unsigned immediate) — a different instruction! Actually for unsigned x < 16, GCC would use `sltiu v0,v0,16`? Hmm, x < 16 unsigned is equivalent to (x & 0xFFFF) < 16 → `andi`+`slti`. GCC might use `sltiu` which is "set if less than unsigned immediate" — for x < 16 with x unsigned 32-bit: sltiu v0,v0,16 gives 1 if (unsigned)v0 < 16. But signed v0 < 16 also requires v0 >= 0. So (u32)diff<16 = sltiu. Different instruction (opcode) → won't match. So that trick fails.

What about making the RTL differ in another way that doesn't change the instructions? E.g. in the else-arm, compare `diff` against a *variable* holding 16? `if (diff < lim)` where lim = 16 → GCC would need a register for lim; it'd load it → extra instructions. No.

Hmm, what about the direction of the comparison: `if (0x10 > diff)`? That's the same RTL (GT_EXPR) but GCC canonicalizes to LT. Probably folded.

What about the two arms having *different* comparison structure: if-arm `if (diff < 0x10)`, else-arm `if (diff < 0x10)` — same.

Let me try another approach: force the blocks apart using a construct that adds NO instructions but changes the block structure. Candidates:
- `goto` to a label placed at the end of each arm (labels don't add instructions):
```
if (diff >= 0) {
    if (diff < 0x10) { return 1; }
    goto out0;
}
diff = sum - *(s16 *)(s1 + 0xA);
if (diff < 0x10) { return 1; }
out0: return 0;
```
Hmm, this shares the return 0.

- Two separate returns via goto labels that are *duplicated*:
```
if (diff >= 0) {
    if (diff < 0x10) { return 1; }
    return 0;
}
diff = sum - *(s16 *)(s1 + 0xA);
if (diff < 0x10) { return 1; }
return 0;
```
= c9 (63 ins, 13).

Hmm, c9 is the "if-arm then straight-line else" version. 63 ins like c1.

Let me now consider that maybe the target's second block is NOT reproducible without the asm, i.e. this is a WALL. But before concluding, let me try a few more shapes:

Shape A: use a helper function? No.

Shape B: make the if-arm's return-1 path *not* a "return" but a set of a variable then a common return:
```
s32 ret = 0;
...
if (diff >= 0) {
    if (diff < 0x10) { ret = 1; }
} else {
    diff = sum - *(s16*)(s1+0xA);
    if (diff < 0x10) { ret = 1; }
}
return ret;
```
This would produce "li v0,1 / move v0,zero" in a shared tail → merged.

Shape C: The target's shape has the if-arm's "return 0" as `j 9d08` with delay `move v0,zero`, and the else-arm's "return 0" as `move v0,zero` (fallthrough). This is what GCC does when the else-arm is the LAST block before the epilogue.

So: the else-arm's code must be the last thing in the function, and the if-arm's code must jump to the epilogue. That's consistent with any source where the if-arm returns and the else-arm falls through to the function end.

Hmm! What if the source is:
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
but with the *inner* if-else nesting deeper so that GCC's jump threading is blocked? E.g. wrap the whole second block in a way that adds a scope but no code.

Honestly, let me look at the problem from the "what did the ORIGINAL game asm look like" angle — maybe the original had this exact shape and the decompiler wrote the C to match with the asm as a hack. To reproduce, I need C that compiles to the original shape.

Let me look at the ORIGINAL game asm for this function! The asm corpus: asm/ov_SC06_029/ only has data. Hmm, but the function is in a "jr" module. The original game asm might be in asm/ov_MAIN_012 or elsewhere. Let me search the asm/ tree for "func_8018656C" — earlier grep found only asm/ov_SC01_084/data/tail.data.s (a string in data). So the original asm of this function isn't in the corpus (the ov modules' text asm may not be extracted).

OK, decision: timebox this item. I've used ~25 min. Let me try 3-4 more quick shapes (cheap), then record a WALL with the mechanism if no luck.

Quick shapes to try:
(1) if-arm with `if (diff < 0x10) { return 1; } return 0;` and else-arm with the recompute BEFORE the if, i.e. exactly c1 but with the else-arm's condition written `if (diff - 0 < 0x10)`? no.

(2) Make the two arms' code *textually different* by spelling the else-arm's value differently but with identical instructions:
else-arm: `diff = sum - *(s16 *)(s1 + 0xA);` → subu v0,v1,a0.
if-arm: `diff = *(s16 *)(s1 + 0xA) - sum;` → subu v0,a0,v1.
Already different.

(3) Introduce a `const` variable to change the RTL:
```
const s32 lim = 0x10;
if (diff >= 0) { if (diff < lim) {return 1;} return 0; }
```
lim would be a literal → same.

(4) Use the C0505 move "&&/|| folds" or "statement order": swap the order of the two return statements? e.g.
```
if (diff >= 0) {
    if (diff >= 0x10) { return 0; }
    return 1;
}
```
That's the same logic with the comparison inverted: `diff >= 0x10` → GCC would generate the inverse branch (bgez) instead of slti+bnez! Different instructions. No good.

(5) What about making the if-arm's condition use the *unsigned* trick differently: `if (diff < 0x10)` in the if-arm and in the else-arm `if (diff - 0x10 < 0)`? Different insns.

(6) What about the "temp" move: give the if-arm's diff a u16 temp? changes insns.

(7) Maybe the trick: in the if-arm, write the comparison as `if (diff < 0x10)` but assign the comparison result to a variable:
```
s32 c;
...
c = diff < 0x10;
if (c) { return 1; }
```
GCC would fold c = (diff<16) into a comparison → same.

(8) What about `volatile`? Not allowed (barrier lever).

(9) Maybe the answer involves the *first* block too: the target's first block has the shared tail {bnez, li v0,1} and continues to the second part. My candidates reproduce the first block exactly (c1's first block matched the target's first block, since the residual differences started at index 49 = the second block). Good.

So the entire problem is the second block's shape.

New idea (10): make the second block's two arms *not* comparable by GCC by making one arm's code have a different *statement order* but the same instructions. Hmm.

New idea (11): the target's if-arm has an extra `j 9d08` before `move v0,zero`. What if this comes from the source having TWO returns in the if-arm and ONE in the else-arm (i.e. the else-arm's "return 0" falls through to the end of the function)? Look at the source:

```
if (diff >= 0) {
    if (diff < 0x10) { return 1; }
    return 0;
} else {
    diff = ...;
    if (diff < 0x10) { return 1; }
    return 0;
}
```
Both arms have explicit returns. In the target, the if-arm has {bnez, li v0,1} + {j, move v0,zero} and the else-arm has {bnez, li v0,1} + {move v0,zero}. Both arms have "return 0" — one as a jump, one as a fallthrough. The asymmetry is just layout: the else-arm's return-0 falls through to the epilogue; the if-arm's return-0 jumps to the epilogue (since the else-arm's code follows it in layout).

So actually the target's shape is EXACTLY what you'd get if the two arms' tails were NOT merged: each arm has {bnez, li v0,1} + {move v0,zero}, laid out sequentially: the if-arm first (with a jump to the epilogue since the else-arm follows), then the else-arm (with a fallthrough).

And c1's merged version: both arms jump to a single shared {move v0,zero}.

So the question: what stops GCC from merging? Let me think about GCC 2.7.2's `jump_threading` (thread.c). It threads a jump to a block whose only successor is the same as the jump's target. E.g. the if-arm's "return 0" block {j epilogue, move v0,zero}: the j targets the epilogue, and the block's successor (fallthrough) is the epilogue → jump threading would remove the j and redirect the predecessor's jump to the fallthrough... Hmm, that would give the if-arm a fallthrough to the else-arm's code — no.

Alternatively the merge of the two {bnez, li v0,1} blocks is `cross_jump`.

Since the target has them separate, cross_jump failed there. Why? Because of the asm: cross_jump compares blocks with `sibling()`, and two ASM insns with the same operands are siblings... but the asm's *output* pseudo: in the if-arm, the asm defines diff; in the else-arm, the asm defines diff. Hmm identical.

BUT: the *inputs*! In the if-arm, the asm's input "0"(diff) refers to the pseudo diff whose current value is (x - sum) computed in the block before. In the else-arm, the input refers to diff = (sum - x). If the blocks are compared, the ASM insn operands are the same pseudo names, so sibling() says equal. However, cross_jump also verifies that the *predecessor* structure allows it. In the if-arm, the return-1 block is entered by fallthrough from the "bltz" block; in the else-arm, it's entered by fallthrough from the "subu" block. cross_jump merges a block with a copy of an identical block when one of them has a single predecessor ending in a jump...

I recall GCC's cross_jump: "Merge two blocks of code that have identical contents... B1 and B2 must have the same number of instructions and each must be reachable by a jump or fallthrough in a cross pattern: the last instruction of B1 is a jump to the successor of B2, and the last instruction of B2 is a jump to the successor of B1". That's the "cross" pattern: B1 ends with a jump to B2's successor and B2 ends with a jump to B1's successor.

In our case: the two "return 0" blocks: if-arm's ends with {j epilogue, move v0,zero} and the else-arm's is {move v0,zero} (falls to epilogue). For a cross pattern, the if-arm's block must end with a jump to the else-arm's successor (epilogue) — yes! `j 9d08` = epilogue = the else-arm's successor. And the else-arm's block must end with a jump to the if-arm's successor — the else-arm's block ends with a fallthrough into the epilogue, not a jump. So no cross. Hmm, but then why did c1 merge them?

In c1 the merged result: both arms' "return 0" became `j 9cfc` (epilogue) with a single `move v0,zero` block. So they DID merge in c1. The merge in c1 combined the if-arm's {j, move} with the else-arm's {move}: the if-arm's `j` was removed (jump threading: the j targets the epilogue and the fallthrough also goes to the epilogue → the j is redundant → removed) and then the two {move v0,zero} blocks became identical and adjacent → merged.

In the target (with asm), the if-arm's `j 9d08` was NOT removed and the two {move} blocks not merged. Why? Because the if-arm's {bnez, li v0,1} block... hmm, the `j` removal (jump threading) happens in thread.c: it removes a jump if the target block's only successor is the fallthrough of the jump. In the target, the if-arm's `j 9d08` targets the epilogue (9d08: lw ra...) and the fallthrough after the j is `move v0,zero` (9cf0) which falls to the epilogue too. So the j could be removed (the epilogue is reached either way) — but the j is in the delay slot position... the j is at 9cec and the move at 9cf0 (delay slot). The delay slot must be filled, so the move must stay in the delay slot. If the j were removed, the move would have to move. So GCC keeps the j to hold the delay slot. OK.

So in the target, the if-arm's {j, move} block exists, and the else-arm's {move} block. They're NOT identical (one has the j) → no merge. But in c1, GCC removed the j and merged.

Why did GCC remove the j in c1? Because in c1, the if-arm's {bnez, li} block was merged with the else-arm's {bnez, li} block first (they're identical) → then the "return 0" path became a single block, and the j became redundant.

Hmm, in the target the two {bnez, li} blocks are also identical... but they weren't merged. So the asm prevented THAT merge. And in c1, the merge of the two {bnez, li} blocks is what caused the (buggy) result.

So: the asm prevents merging of the two "return 1" blocks {bnez, li v0,1}. Why? Because the ASM insn in each block has an output operand (defining pseudo diff) and... hmm, in the if-arm, the asm's *input* is diff, which at that point is a pseudo with a value; the asm's output redefines diff. In the else-arm, same. So the ASM insns are textually identical. Unless the pseudo diff in the else-arm is a *different* pseudo (e.g. cse created a copy) — no.

Wait, maybe the ASM insn's position differs: in the if-arm, the asm might be placed BEFORE the `bnez` (i.e., in the block that computes diff and tests it) since the asm is inside the if body but GCC's expand might hoist the asm to before the branch? No — the asm is in the "diff<0x10" body, which is after the branch.

Hmm, alternatively the asm might be placed in the block *after* the bnez, i.e. the block {asm, li v0,1}. And in the else-arm the same. So blocks: if-arm: {bnez, [asm?], li}. Hmm, the bnez is the last instruction of the block? Then the block is {bnez} and the next block is {asm, li v0,1}. In the else-arm: {bnez} then {asm, li v0,1}. Identical again.

I'm stuck on the theory. EMPIRICAL approach: I need SOME C difference that makes GCC treat the two arms' return-1 blocks as non-mergeable, without changing the instructions.

Options that change the RTL but not the instructions:
(i) Different comparison *modes*: e.g. in the if-arm `if (diff < 0x10)` and in the else-arm `if (diff < 0x10)` — same. What if the else-arm compares a *u32* expression that GCC still compiles to slti+bnez? e.g. `if (diff + 0 < 0x10)`? folds.

Hmm: what if in the else-arm I write `if ((s32)(s16)diff < 0x10)`? That adds a truncation → different insns (lh+...). No.

(ii) Different *pseudo* for the compared value in the else-arm: c2 (diff2) → 13 (same as c1). So no.

Hmm, c2's score 13 = same as c1. So the else-arm with a different variable didn't change anything (probably cse/other passes merged them anyway).

(iii) Different *order* of the comparison and the recompute: e.g. else-arm: `if (diff < 0x10) {...} diff = sum - x;` — changes semantics.

(iv) Use a *different* but equivalent expression in the else-arm that yields the same instruction: `diff = sum - *(s16 *)(s1 + 0xA);` vs `diff = sum - ((s16 *)(s1 + 0xA))[0];` — same RTL.

(v) The C0505 catalog mentions "s16/u8 widths". What if the else-arm's diff is declared as s16 vs s32? That changes the insns (lh).

Hmm, hold on! What about the *first* block? Look at the target's first block: the slti is in the delay slot of bgez and the bnez survives. In c1/c8, the second block's slti landed in the delay slot of a j and the bnez vanished. The difference: in the target, the slti is in the delay slot of a *conditional* branch, and GCC 2.7.2's "delay slot filling" doesn't move a branch's condition computation into a j's delay slot (it only fills delay slots with instructions that don't affect the branch).

The bug in c1/c8: GCC put the slti in the j's delay slot AND dropped the bnez. That's the "slti in delay slot" bug where the branch on the slti result was dropped. This is a known GCC 2.7.2 bug with `slti`/`slt` compare-and-branch.

So, in the target, the slti ends up in the delay slot of the *conditional* branch (bltz) and the bnez survives.

To get the same in plain C, I need the comparison to be computed in the delay slot of the conditional branch. That happens when the comparison is *not* folded into the branch — i.e., when the boolean value is materialized into a register.

Materializing the boolean happens when the value is needed in a register — e.g. when the value is used more than once, or when the comparison result is used as a value.

In the target, the *asm* forces `diff` (the compared value) into a register... but the compared value is diff, not the boolean. Hmm, the slti computes the boolean into v0 and the bnez tests v0.

Why does the target materialize the boolean instead of using a compare-branch (bltz/bgez)? Because with the asm, the *value* diff must be in a register at the asm point; and the compare `diff < 0x10`... hmm.

Let me try to think of the C that makes GCC materialize the boolean: if the boolean is used twice, or if the comparison is on a value that must be materialized.

E.g.:
```
s32 c = diff < 0x10;
if (c) { return 1; }
```
GCC would likely still fold.

What if the *value* diff is used after the comparison? E.g.:
```
if (diff < 0x10) { return 1; }
```
vs
```
if (diff < 0x10) { diff = diff; return 1; }   // forbidden identity
```

What if diff is used in a later expression? Not in this code.

Hmm, what about the *first* block: `if (diff < 0x10) { return 1; }` — GCC materialized the boolean there (slti + bnez) even without the asm! Why? Because the first block's structure is: the recompute is in the if-branch and the test comes after; the boolean is computed in the delay slot of the bgez. So in the first block, GCC materialized the boolean naturally (because the value diff is needed for the recompute? no...).

AH, I think I see: in the first block, the value `diff` after the if is used by the comparison, and the *else* path recomputes diff. So on the path where diff>=0, the value must be kept in a register (v0) for the comparison → the comparison `diff < 0x10` becomes slti on v0 (materialized) rather than a compare-branch. Because the "compare and branch" optimization requires the compare to be the *only* use of the value; here, the value has two uses (the bgez test and the slti test) so GCC materializes.

In the second block (c1), the value diff is used only once (the comparison) → GCC uses compare-and-branch... but the generated code was "bltz v0, 9cec" for `diff < 0` and then the slti for `diff < 0x10` in the delay of the j, with the bnez lost. In the TARGET (with asm), the value diff is used TWICE (once for the `diff < 0x10` compare and once for the asm's input) → so the value must be materialized in a register, and the comparison becomes slti+bnez.

So the key: make `diff` have a second use after the comparison, in real C, without adding instructions!

E.g.:
```
if (diff >= 0) {
    if (diff < 0x10) {
        diff = diff;      // identity — FORBIDDEN
        return 1;
    }
    return 0;
}
```
Forbidden. But what about a *real* second use that's a genuine computation? E.g.:

```
if (diff >= 0) {
    if (diff < 0x10) {
        return 1;
    }
    return 0;
}
```
Hmm.

What about using diff in a way that produces no extra instructions but is a real use — e.g. `if (diff < 0x10) { ... }` and elsewhere `if (diff >= 0x10)`. Hmm, the *else* path already tests diff<0x10 (the recomputed diff though).

What if the if-arm's condition uses diff and the *return value* depends on diff? E.g. `return (diff < 0x10);`? That would compute slti into v0 and return it → `slti v0,v0,16` then the function returns v0 — but the target has `li v0,1` / `move v0,zero`. Different.

What about `return diff < 0x10 ? 1 : 0;`? Same as the if.

Hmm, what about making the *value* have a second use in the ELSE arm: e.g. the else arm recomputes diff, so the original diff has 2 uses: the `diff >= 0` test and... no, the else arm uses the recomputed value.

Hmm, in c1, the `diff >= 0` test is a compare-branch (bltz) and the `diff<0x10` is another compare → the value diff has 2 uses already! (bltz and slti). Yet GCC still produced slti in the delay slot and lost the bnez.

Ugh, but in the target, the SAME structure produced bnez properly — because of the asm.

OK. Let me try the most promising real-C approach for forcing materialization: use the value in a *second comparison* whose result is the same. E.g. in the if-arm:

```
if (diff >= 0) {
    if (diff < 0x10) {
        if (diff >= 0) {      // redundant test, but a second use of diff
            return 1;
        }
        return 0;
    }
    return 0;
}
```
The redundant test `diff >= 0` is a real use; GCC would fold it away (it knows diff>=0 in that branch) → no change. Hmm, but it would fold before codegen.

What about a use that GCC can't fold: `if (diff < 0x10) { if (diff == diff) return 1; ... }`? `diff == diff` is always true → folded, but maybe late enough to matter? Folding happens in cse/flow, before expand. The fold of `x==x` happens early (cse). Hmm, but the *use* of diff in the comparison `diff == diff` might survive as a register use? No, cse removes it.

What about a use in a *store*? Adds instructions.

What about `volatile`? Not allowed (barrier).

What about passing diff to a function? Changes the call.

Hmm, what about making the *if-arm's* diff a u16 temp? "u16 t (HImode copy escapes cse equiv)" from moves.md! E.g.:

```
u16 t = diff;   // or u16 t = (u16)diff;
if (t < 0x10) { return 1; }
```
That generates lhu/andi → extra instructions. No.

Hmm OK, what about this: the asm's real function is to make the compiler treat `diff` as *modified* (unknown) after the asm. What if I use a *real* second set of diff in the if-arm that yields the same value but is a different expression, e.g.:

```
if (diff >= 0) {
    diff = *(s16 *)(s1 + 0xA) - sum;   /* real 2nd set, same value */
    if (diff < 0x10) { return 1; }
    return 0;
}
```
The RTL: a new set of diff with the same value. cse would see the same expression → but cse's make_regs_eqv would make the new set equivalent to the old → the value is the same pseudo → no change in codegen. But it does add a "set" which might affect the *reference count* / priority of diff. Might change the delay-slot choice! Worth a try — cheap.

Actually here's another thought: what if I make the if-arm's diff a *different variable* whose value is computed from the same expression, i.e.:

```
s32 diff = *(s16 *)(s1 + 0xA) - sum;
if (diff >= 0) {
    s32 d2 = diff;     /* copy: a second use, forces materialization */
    if (d2 < 0x10) { return 1; }
    return 0;
}
```
A copy `d2 = diff` — GCC will coalesce it (same value) → no extra instructions, but it DOES add a use of diff (in the copy) → diff must be in a register at the compare. Hmm, but GCC's copy propagation will just make d2 = diff's value; the comparison then uses the same reg. So the value has 2 uses (the bltz and the slti) — the same as before.

Hmm, so why does the target materialize the boolean?

Let me look at the target's second block ONE more time:
```
9cd8: subu v0,a0,v1     ; diff
9cdc: bltz v0,9cf4      ; diff < 0 → else
9ce0: slti v0,v0,16     ; delay slot: diff < 0x10 (materialized!)
9ce4: bnez v0,9d08      ; if (diff<0x10) → return 1
```
and c1's:
```
9cd8: subu v0,a0,v1
9cdc: bltz v0,9cec
9ce0: nop
9ce4: j 9cfc
9ce8: slti v0,v0,16
```
In c1, the slti went into the j's delay slot and the bnez was LOST (bug). In the target, the slti went into the bltz's delay slot and the bnez was kept.

The difference: which delay slot was chosen. GCC's delay-slot filling (mips.c) fills the delay slot of a branch with an instruction that is "safe" (doesn't affect the branch condition) and whose inputs are ready. The slti depends on v0 (diff). For the bltz at 9cdc, the slti (using v0, which the bltz also uses) is safe → it fills the bltz's delay slot in the target. In c1 it filled the j's delay slot instead, and the bnez got lost (a delay-slot bug: the bnez's condition came from the slti in the delay slot, and the branch was dropped?).

Hmm, actually maybe in c1 the bnez was NOT dropped but rather the *entire* "return 1" path was removed because... ugh.

Wait wait wait. Let me re-read c1's disassembly once more:

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
9cfc: lw ra,40(sp)
```
Hmm, at 9ce4: `j 9cfc` — jumps to the epilogue with v0 = ? (v0 holds diff, not 0!). And at 9cf8: move v0,zero then epilogue.

So the paths: (a) diff>=0 → 9ce4: j epilogue (v0 = diff, garbage!) — that's the "return 0" path but v0 isn't zeroed! and (b) diff<0 → 9cec: recompute; 9cf0: j epilogue (v0 = diff) — also garbage.

Hmm, so where's the `move v0,zero`? At 9cf8, which is the delay slot of the j at 9cf0. So the "move v0,zero" is in the delay slot of the second j. And the first path (9ce4 j) has delay slot slti → v0 = the boolean, then jump to epilogue with v0 = boolean!! That's broken (returns the boolean instead of 0/1).

So c1 is genuinely broken code. This is the famous GCC 2.7.2 MIPS delay-slot bug? Or maybe... hmm, this looks like the "jump threading" produced a mess.

Whatever the cause, the point: the target (with asm) is well-formed. So the asm prevents this miscompile.

Hmm! Maybe the real question: is the "correct" C (from the original game) something else entirely, and the current src's C is a decompiler artifact?

Let's think about the ORIGINAL game asm (which the decompiler was matching). The original game asm for this function likely was:
```
subu v0,a0,v1
bltz v0,9cf4
slti v0,v0,16
bnez v0,...
li v0,1
...
```
i.e. exactly the target shape. The original asm was hand-written by the game developers (or by a decompiler of the original). The decompiler (this project) reproduced it with the asm hack.

For the *current* project, matching the build/ object is the goal.

So I need plain C that compiles to that shape.

Let me try a few more shapes quickly:

(A) if-arm with a real 2nd set of diff (same expression) — c10.
(B) if-arm where the comparison uses a copy variable d2 = diff — c11.
(C) The whole second block restructured to the "first block" style but with duplicated tests via goto labels:
```
if (diff >= 0) {
    if (diff < 0x10) { goto r1; }
    goto r0;
}
diff = sum - *(s16 *)(s1 + 0xA);
if (diff < 0x10) { goto r1; }
r0: return 0;
r1: return 1;
```
This gives a shared tail → merged (like c5). No.

(D) What if the else-arm is placed FIRST in the layout (so the if-arm falls through to the end)? i.e. swap arms but keep the "diff>=0" test first:
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
= c3 (61 ins, score 12). Hmm c3 = 61: let me look at c3's shape. 61 ins means the second block is 8 ins (like c8). Not 12.

So c3/c8 give 8-ins second blocks; c1/c9 give 10; c5 gives 8; target 12.

Which candidates gave 10-ins second blocks? c1 (63 ins) and c9 (63). Let me look at c9's second block shape (c9 = if-arm then straight-line else). Let me dis c9.

Actually, I realize I should consider: maybe the merge is prevented if the two arms' "return 1" blocks are *not adjacent* in the layout or if one of them is a jump-target. In the target, the if-arm's {bnez, li} block is a fallthrough from the bltz block, and the else-arm's {bnez, li} block is a fallthrough from the subu block.

What if I could get GCC to lay out the code so the two "return 1" blocks are separated by the "return 0" code? Like the if-arm: {bnez, li v0,1} {j epilogue, move v0,zero} and the else-arm: {bnez, li v0,1} {move v0,zero}. That's exactly the target layout, with the else-arm's return-0 falling through.

What source produces "the else-arm's return-0 falls through to the end of the function"? A source where the else-arm is the last code and the if-arm jumps to the epilogue. E.g.:

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
Both arms return → the layout is arbitrary.

What if the source ends with the else-arm falling through to `return 0;` at the end of the function:
```
if (diff >= 0) {
    if (diff < 0x10) { return 1; }
} else {
    diff = sum - *(s16 *)(s1 + 0xA);
    if (diff < 0x10) { return 1; }
}
return 0;
```
= c5 (62 ins, 8-ins block: subu, bgez, slti, subu, slti, bnez, li, move). Merged.

Hmm, c5's shape: the two arms share the {bnez, li v0,1, move v0,zero} tail. The target: unmerged.

So the merge is the crux. What prevents GCC 2.7.2's cross-jump from merging the two {bnez, li v0,1} blocks?

In the target, these blocks contain the ASM. In c5, they don't.

So: the ASM blocks the merge. To block the merge in plain C, the two blocks must be non-identical in RTL. What if the two arms' return-1 blocks differ in the *value* they return? E.g. the if-arm returns 1 and the else-arm returns 1 — same.

WAIT. What if they differ in a *dead* RTL difference that produces no instructions? For example, in one arm, the returned value is `1` (a constant) and in the other it's `(s32)1`? Same.

What about the if-arm returning 1 via a variable and the else-arm via a constant? e.g.:
```
s32 ret;
...
if (diff >= 0) {
    if (diff < 0x10) { ret = 1; return ret; }
    return 0;
}
```
Hmm, `ret = 1; return ret;` → li v0,1; jr ra — the same instructions, but the RTL has a "set ret 1" and "use ret" instead of a direct constant. That differs from the else-arm's `return 1;` → so the blocks are NOT identical → no merge!! And the instructions: `li v0,1` (the set) and the return uses v0 — should be the same code!

That's promising! But is it "a new lever"? No, it's plain C: a temp variable and a return. It IS a real C move (the C0505 catalog mentions "temps", "decl order/scope", "init at decl"). Legit!

Let me try that: if-arm uses `s32 ret = 1; return ret;` while the else-arm uses `return 1;`.

Hmm, but careful: GCC would propagate ret=1 into the return → same RTL. GCC's copy propagation (cse) would replace `use ret` with the constant 1 → identical again. Hmm, but cse's make_regs_eqv handles constants fine → merged.

Alternative: make the difference in a way that survives: e.g. in the if-arm, return a value that is *computed* but equals 1:
`return 1 + 0;`? folded.

What if the if-arm returns a variable that's set elsewhere (so the value isn't a constant at the return)? e.g.
```
s32 ret = 0;
...
if (diff < 0x10) { ret = 1; }
return ret;
```
That changes the structure (merged tail).

Hmm. What about the *value* of the comparison in the two arms: in the if-arm, `diff` is compared; in the else-arm, `diff` is compared. If in one arm the compared pseudo is a *copy* (e.g. `s32 d2 = diff; if (d2 < 0x10)`) — c2 tried that in the else-arm (diff2) and the result was 13 (same as c1). Hmm, so c2's shape was probably the merged one.

Hmm, why would c2 differ from the target? Because the merge still happened.

OK, radically different idea: what if I make the two arms' return-1 blocks differ by the *presence of a computation that produces the same instructions*? E.g. the if-arm computes `li v0,1` and the else-arm computes `li v0,1` — the instructions are the same but the RTL differs if one is a constant and the other is a copy of a constant...

Honestly, let me just try several variants in one batch:
c10: if-arm: `s32 d2 = diff; if (d2 < 0x10) { return 1; } return 0;` else-arm unchanged.
c11: if-arm: `if (diff < 0x10) { s32 r = 1; return r; } return 0;`
c12: else-arm: `if (diff < 0x10) { s32 r = 1; return r; } return 0;` (if-arm plain)
c13: both arms use `s32 r = 1; return r;` — no, that's symmetric.

Hmm, wait. Actually, maybe a much better idea: what if the difference is in the *condition* being on a value in a different register? In the target, both arms' comparisons are on v0.

Let me also try:
c14: the "0x10" constant replaced by a variable of type s32 initialized to 0x10 (init at decl) — GCC folds constants. No.

Let me also try the "u16 width" trick from moves.md: "u16 t (HImode copy escapes cse equiv)":
c15: in the if-arm: `u16 t = (u16)diff; if (t < 0x10) {...}` — extra instructions (andi/lhu). No.

OK, let me try c10, c11, c12 and see. Actually, hmm, let me reconsider.

Time: it's ~18:45 now; item 1 started 18:21. I'm at 24 min. The budget is 20-30 min per item. I should wrap up item 1 soon with either a match or a wall.

Let me think about what evidence to record for a WALL. The mechanism: "asm forces the boolean materialization (slti+bnez) in the second block; without it GCC 2.7.2 merges the two arms' tails and mis-schedules the slti into a j delay slot, dropping the bnez (63 ins vs 66)". Tag: something like `cse-crossjump-merge` or `expand-delay-slot-bnez`.

But wait — the constraint says the result can be PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers). For a launder-only item, PARTIAL would mean... the kind is launder; PARTIAL:launder would mean the body still has the launder but scores 0 — that's just the orig. Not useful. So for launder items, either MATCH or WALL.

Before declaring a wall, let me try the "different pseudo in one arm" idea (c10/c12) and the "temp variable return" (c11). One batch of 3.

Actually — NEW IDEA, and I think this is the winner: the merge is prevented if the two arms' return-1 blocks are NOT *adjacent* in the RTL, i.e. if the else-arm's block is not a fallthrough-successor of the if-arm's block. In the target layout, the else-arm's code (9cf4) comes right after the if-arm's code (9ce4-9cf0). So they ARE adjacent.

Hmm, that doesn't help.

Let me think about the "sibling" comparison in cross_jump: for two blocks to be merged, they must have the same instructions. The if-arm's block {bnez, li v0,1} vs the else-arm's {bnez, li v0,1}: identical → mergeable → merged (c1/c5).

In the target, they're not merged because the ASM insn is in one of them?? Both should have the asm...

UNLESS: the asm is NOT in both blocks! Consider: GCC might have moved the if-arm's asm into a different position than the else-arm's asm. E.g. the if-arm's asm could have been scheduled into the delay slot region of the bltz block, while the else-arm's asm stayed in its own block. Then the blocks {bnez, li} (if-arm, no asm) and {asm, bnez, li} (else-arm) differ → no merge. And the extra "asm" in the else-arm's block generates no instructions but is in the RTL.

Hmm! But then the "sli" scheduling differs between the arms: in the target, the if-arm has slti in the bltz's delay slot, and the else-arm has its own slti. So the arms' shapes differ → consistent with the asm being in different positions.

Why would the asm be in different positions? Because in the if-arm, the asm is in the block that ALSO contains the "bltz" test? Hmm.

Whatever the cause, the practical question stands: what plain C produces this?

Let me consider the possibility that the answer is: the if-arm and else-arm must be *different code* in the RTL, e.g. by using different *source* expressions that compile to the same instructions. The instruction sequences in the two arms:
if-arm: subu v0,a0,v1 ; slti v0,v0,16 ; bnez ; li v0,1
else-arm: subu v0,v1,a0 ; slti v0,v0,16 ; bnez ; li v0,1

The difference: `subu v0,a0,v1` vs `subu v0,v1,a0` — the operands are swapped! In the RTL, these are different instructions (commutative operands in different order) → the two blocks are NOT identical → no merge!!!

But in c1 (the same source), GCC merged them! Because the merge happened at a different level: the merge is of the *return-1* blocks {bnez, li v0,1}, not the whole arms. The {bnez, li} blocks are identical in both arms.

Hmm, so in the target, the {bnez, li} blocks are also identical. So why no merge?

Unless in the target, the if-arm's return-1 block is {bnez, li} and the else-arm's return-1 block is {bnez, li} but they're not *mergeable* because of the ASM in one of them.

I'll go with: the ASM in each arm is in the return-1 block, and the two ASM insns are NOT identical in RTL because their *input operands* refer to different values: in the if-arm, the asm's input is the pseudo `diff` (whose value at that point is the reg holding v0 = x - sum); in the else-arm, the asm's input is also the pseudo `diff`... but the pseudo's *value* is the same pseudo (the C variable), and in the else-arm it was redefined by `diff = sum - x`. So the pseudo is the same name, but the *reg* it's in might differ (v0 in both). Hmm, so the ASM insns are identical: (set (reg diff) (asm ...)) with the same input reg.

But cross_jump's `sibling` comparison compares the *instructions*; two ASM insns with the same operands and same constraints are siblings. BUT cross_jump in GCC 2.7.2 explicitly SKIPS blocks containing ASMs? Hmm, maybe! There might be a check like "if (GET_CODE (last_insn) == ASM) return 0" or the function `sibling` returns false for ASM insns with operands? Actually, `sibling()` in jump.c compares two insns: for ASM insns, it compares the constraints and the number of outputs/inputs but NOT the operand values (because ASM operands are matched by constraint, not by value). Hmm, if it compares only constraints, they'd be siblings.

BUT: cross_jump might refuse to merge blocks where an ASM's *input* is defined in the block (i.e. a "hard reg" issue) because the merged block would have two different definitions of diff. In the if-arm, the asm's input diff is defined in the *preceding* block (subu v0,a0,v1) — same in the else-arm (preceding block subu v0,v1,a0). So the asm's input is defined in the preceding block in both → when merging the return-1 blocks, the inputs come from different predecessors → the merge would be invalid! GCC might detect this: the asm's input operand is a pseudo (diff) that is *set* in the predecessor block, so the two blocks are NOT equivalent (their inputs differ) → cross_jump's sibling check on the ASM insn compares the input pseudo — the same pseudo name in both → considered equal → but the *values* differ.

This is exactly the kind of subtle thing that could block the merge. And the corresponding plain-C equivalent: make the two return-1 blocks' *input values* differ in a way GCC's sibling check detects. In C, the two arms' compared values come from different expressions, but by the time we're in the return-1 block, the compared value is the pseudo `diff` in both (the same C variable) → GCC's cse makes them the same pseudo → sibling.

If I use a DIFFERENT C variable in the else-arm (c2: diff2), then the else-arm's return-1 block would reference diff2 while the if-arm's references diff → the blocks differ → NO MERGE! But c2 gave 13 (same as c1) — hmm, so it didn't work?! Maybe because cse made diff2 equivalent to diff (diff2 = sum - x, diff = x - sum — NOT equivalent!). Hmm, c2's else-arm: `s32 diff2 = sum - *(s16 *)(s1 + 0xA);` — the value differs from diff. So the two return-1 blocks compare diff vs diff2 → different pseudos → not siblings → no merge. But c2 scored 13, the same as c1. Maybe c2's shape is different in another way but still 63 ins.

I need to look at c2's disassembly. Let me batch-dis c2 and c9 to see their shapes. Then decide.

Let me do that now (one command, 2 disassemblies).
