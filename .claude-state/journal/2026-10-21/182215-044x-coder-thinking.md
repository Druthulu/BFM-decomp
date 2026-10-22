---
ts: 2026-10-22T00:22:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_AGPugI5q7nrES6r1ev5w
---
c2 same as c1 (13), c3 = 12 (61 ins).

Let me look at c3's asm to see the shape. And think differently.

Key realization attempt: In the target, the second block's if-arm has `bnez v0,9d08` where 9d08 is the epilogue, and the delay slot `li v0,1`. But in the *first* block (no asm), the merged shape is `bnez v0,9cfc` (epilogue) with delay `li v0,1`. Interesting: in the first block, the bnez jumps to the epilogue with v0=1.

Hmm! Note in the first block, the "return 1" path jumps to the epilogue, and the fall-through continues to the second part of the function. So the first block's structure is: if (diff<0x10) return 1 (jump to epilogue); else continue.

In the second block, "return 1" also jumps to the epilogue (9d08) and "return 0" jumps to 9d08 too (move v0,zero + j 9d08).

So both blocks' "return 1" = `bnez v0, epilogue` with `li v0,1` in the delay slot.

In the target's second block, the if-arm is:
```
bltz v0,9cf4
slti v0,v0,16     (delay slot)
bnez v0,9d08
li v0,1
j 9d08
move v0,zero
```
and the else-arm:
```
9cf4: subu v0,v1,a0
9cf8: slti v0,v0,16
9cfc: bnez v0,9d08
9d00: li v0,1
9d04: move v0,zero
```

Note the else-arm's "return 0" falls through to the epilogue (9d04 → 9d08 lw ra), while the if-arm's "return 0" jumps (9cec: j 9d08 with delay move v0,zero).

So the two arms' tails are NOT merged in the target. And in c1 they were merged (and the bnez lost — a GCC bug in the merged form).

Hypothesis: GCC 2.7.2's cross-jump merged the two arms' tails in c1 and, in doing so, mis-scheduled the slti into the j's delay slot and lost the bnez. The asm (in the return-1 path of each arm) blocked the merge.

To block the merge without asm: make the two arms' "return 1" blocks differ in the RTL but generate the same instructions. E.g., in one arm `return 1;` and in the other `return 1;`... identical. What about the *value* of the comparison: if-arm `diff < 0x10` vs else-arm `diff < 0x10` — identical.

Alternative: block the merge by making one arm's return-1 path *not* a simple return. E.g. in the if-arm:
```
if (diff < 0x10) {
    diff = diff;   // no
    return 1;
}
```

What about using a `volatile`? That's a barrier lever (not allowed).

Hmm what about: in the if-arm, use `return 1;` and in the else-arm use `return 1;` but where the else-arm's diff is a *different pseudo* (c2 tried: no change).

What if the difference is in the *order of the arms* (c3: 61 ins, 12)? Let me look at c3's asm to understand what shape it produced. Let me dis c3.

Actually, let me think about a different, more robust strategy: maybe the "asm" isn't needed for codegen at all — maybe the current src's asm is a red herring and the *target* (build/) was built with the asm... The target IS the built object. So the target contains the effect of the asm. Score 0 requires matching it.

Hmm wait, actually — is the target the built object, or the ORIGINAL game asm? The brief says "compares with the function in build/". The build/ object is from src. So target = current src's compiled output = has the lever's effect. So I need a lever-free body producing the same instructions.

Given GCC 2.7.2's fragility, matching exactly may be hard. But other items in moves.md did crack.

Let me look at c3's disassembly to see what shape it produced, and then think about how to force the target shape.

Actually, maybe a much better approach for this function: rewrite the whole second block so that the code is *literally* the target shape, using a formulation that GCC compiles that way. E.g. write it with explicit returns and no shared tail:

```
if (diff >= 0) {
    if (diff < 0x10) {
        return 1;
    }
} else {
    diff = sum - *(s16 *)(s1 + 0xA);
    if (diff < 0x10) {
        return 1;
    }
}
return 0;
```
This is the "single return 0 at the end" form: the "return 0" is shared, the "return 1"s are separate. That might produce:
```
bltz v0,9cf4
slti v0,v0,16
bnez v0,9d08
li v0,1
j 9d08?
```
Hmm, the target's if-arm has `j 9d08; move v0,zero` (return 0 via jump) whereas the else-arm has `move v0,zero` falling through. With a single shared "return 0", both arms would jump to it → the shape would be: if-arm: bnez/li/j(return0); else-arm: bnez/li/j(return0) — both jumping. But the target's else-arm falls through to move v0,zero. Hmm, unless the shared return-0 block is placed right after the else-arm (at 9d04) and the if-arm jumps to it (9cec: j 9d08 → but 9d08 is the epilogue, not 9d04!).

Wait: target if-arm: 9cec: `j 9d08` with delay 9cf0: `move v0,zero`. So the if-arm's return-0 is its own block (j to epilogue with v0=0), and the else-arm's return-0 is at 9d04 (move v0,zero) falling into the epilogue. Two separate return-0 blocks. So no sharing at all in the second block.

That's the signature of "cross-jump merging was blocked". The asm blocked it.

How else can one block cross-jump merging? If the two blocks are not "identical" in the eyes of the cross-jump pass, e.g. different jump targets, different preceding instructions, or one is a "jump to jump" case.

The cross-jump in GCC 2.7.2 merges blocks when the code is identical AND the predecessor's jump can be redirected. The if-arm's return-0 ends with `j 9d08` (epilogue) and the else-arm's return-0 is the block `move v0,zero` (falls to epilogue). If GCC had merged, the if-arm's `j 9d08` would become `j 9d04`... it didn't, presumably because the merge would require changing an instruction (the jump target), which cross-jump CAN do (it's "jump threading"). Hmm.

Since with the asm GCC didn't merge, the asm must create an RTL difference in the tails. The asm is in the return-1 path, not the return-0 path. But GCC's cross-jump compares whole basic blocks. The "return 1" blocks: if-arm: [asm, li v0,1] vs else-arm: [asm, li v0,1] — the asm's *output* pseudo is diff in both; if the asms reference the same pseudo, they'd be equal. Hmm, but the asms are in different blocks with different diff values (v0 in if-arm...). The asm operands: "=r"(diff) : "0"(diff) — in the if-arm diff is in v0 (same as the else-arm? no, the else arm recomputes into v0 too). Hmm.

Honestly, let me try a totally different approach for this function: maybe I can find a C formulation that produces the exact target shape by making the two arms structurally different in C but identical in asm. E.g.:

```
if (diff >= 0) {
    if (diff < 0x10) {
        return 1;
    }
    return 0;
} else {
    diff = sum - *(s16 *)(s1 + 0xA);
    if (diff < 0x10) {
        return 1;
    }
    return 0;
}
```
(c1, merged) → target wants unmerged.

What if I add a real statement in one arm that generates no instructions but changes the RTL? Like `sum = sum;`? Identity — forbidden.

What about `diff = diff + (sum - sum);`? Ugly and might generate code.

Alternatively: maybe the *sum* variable being reused. In the target's second block, `sum` (v1) is used in both arms. If I split `sum` into two variables, the code might change.

Hmm, let me look at this from the "how did the original decompiler crack it" angle: the comment says "!FAKE: launder — NEEDED DIFFERS (P36 rung B t8_tus2)". So the decompiler marked it as fake and needed. My job: find a real C that matches.

Let me try more shapes quickly. Candidates to try:
c5: single return 0 at the end (as sketched).
c6: else-arm first with `diff < 0` (c3 tried; 12).
c7: if-arm `if (diff < 0x10) { return 1; } return 0;` in both arms but with the else-arm using `<= 0xF`.
c8: use `u32`/different type for diff? changes asm.

Let me try c5 and c7 now, and also look at c3's disasm.

Let me write c5 and c7.
