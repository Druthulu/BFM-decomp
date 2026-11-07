---
ts: 2026-11-06T12:46:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_y0ii95JolkB9M4GCFhar
---
Interesting: in v21, the early returns emit `j; move v0,zero` (the move in the delay slot) whereas the target has `j; nop`.

Also: the second early return in the target is `beqz a0, 1e3c` (branch directly to the epilogue!) whereas mine is `bnez a0, 1ab4; ...; j 1e2c; move v0,zero` — inverted branch. In the target, `if (ptr == 0) return ret;` compiled to a direct beqz to the return label. Mine: `bnez a0, continue` + `j return`. This is the jump optimization: `if (x == 0) return; ...` — target does beqz to the epilogue.

Hmm, in the target: `beqz a0, 1e3c` where 1e3c is the epilogue. So the target's early return is a *conditional branch to the return block* with no insn. Mine does `bnez a0, 1ab4` (skip) + `j 1e2c` + move v0,zero.

If the C were `if (ptr != 0) { ...rest... }`? no.

The difference: with `return 0`, jump_optimize chose the inverted form (because the return block is far? or because the "then" has a value move). With `return ret` (a pure jump), it uses beqz directly.

So the target's early return value must be a pseudo that's already in v0 (no insn) → beqz to the return label.

OK. Given the difficulty, and that ret's allocation is the blocker, let me try ONE more idea that could solve BOTH: what if `ret` is not a variable at all but the function returns via a chain that gcc keeps in v0?

Alternative: what if we declare `ret` as a *parameter-like* variable initialized from... no.

Hmm, what about making `ret` a `u16`?! The store is s16 (unk2). If ret were u16, the store would need no truncation. And the return would need a zero-extend... `move v0,ret`? no.

Let me try: `u16 ret;` with `ret = 7;` etc. The STORE does `unk2 = ret` (s16 store from u16 → no conversion) and `return ret` → zero-extend to s32? Hmm, the function returns s32; returning a u16 → `andi v0,ret,0xffff`? That's an extra insn.

What about `s16 ret;`? `unk2 = ret` (s16) fine; `return ret` → sign-extend? The function returns s32; ret s16 → gcc knows the value... it would need sll/sra. Extra.

OK. Let me try one more thing on the v21 base: add a *real use* of ret that forces its live range to end earlier? no...

Actually, here's a thought I haven't tried: make the STORE use the value in a way that doesn't require ret to be live across the arm's store. What if the arms don't assign `ret` but instead the store block receives the value via the struct field... no.

Honestly: WALL. It's 05:47, 17 min in; I have 36 scored tries; I'll record the wall at ~06:00 after a couple more quick shots.

Let me do 2-3 more targeted tries on v21 (the best base), since only 1 register pair remains:
w1: v21 + `ret = (s16)N` in arms.
w2: v21 + do-while around the arm's ret assignment (c5 move).
w3: v21 + swap the two early returns' order? no.
w4: v21 + `s32 ret = 0;`.

Actually, a better idea to try: since the target's early return has NO insn, and mine has `move v0,zero`, what if the early returns are `return ret;` AND we accept ret in a callee-saved reg? No, then all arms' li go to that reg (a0 currently).

Hmm hold on, what if the early returns return the *same expression* as the arms' `ret`? Like `return ret;` where ret was assigned... no, uninitialized.

Wait, actually! What if we assign `ret` in the early-return paths first? E.g.:

```
if (D_801ED4E4[...] == 0) {
    func_8012CAE4((void *)param_1);
    return ret;      /* ret uninitialized */
}
```
What if instead we write:
```
if (D_801ED4E4[...] == 0) {
    ret = 0;        /* extra insn: move v0,zero */
    func_8012CAE4((void *)param_1);
    return ret;
}
```
Then ret is defined (in v0!) before the call → live across the call → saved reg. No.

OK: let me test w2 (v21 + do-while around arm ret) and w1, then wrap up as WALL.

Actually, wait. Let me reconsider ONE more structural idea, since v21 is so close: what if the STORE block is `unk2 = ret;` and the arms set ret... 

What if we make the store *read* the value from a place that forces the ordering — e.g., write the arm as:

```
if (unk70 == 0x28) {
    ...
    unkD8 = call(...);
    goto STORE28;   /* with ret = 7 set in the store block */
}
```
i.e., per-arm store blocks:
```
STORE28: ret = 7; goto STORE;
```
The label STORE28 is a branch target → the li is in a separate basic block from the call's store → sched1 can't move it up! And jump_optimize might merge `ret = 7; goto STORE` into... the STORE block? It would try to merge the blocks: `STORE28: ret = 7; goto STORE` — a block with a single jump to STORE, no. It would merge only if the jump goes to the immediately following block. If we lay them out as separate blocks, jump2 might cross-jump them (all arms' `ret = N; goto STORE` blocks are similar but with different constants).

Would that be "fake"? It's real C (goto to a label). Adding 6 labels. The target's asm has no extra jumps, but jump_optimize might merge the label blocks back... Since each STORE-N block is entered only by its arm's goto and it's an unconditional jump to STORE, jump_optimize's "jump to next insn" and block merging would likely delete it (a block consisting of only a jump gets threaded: goto STORE28 → STORE28: ret=7; goto STORE — the first goto is redirected to STORE only if the block is empty; here it has the li, so the block stays, and the arm's `goto STORE28` becomes a jump to that block. Then reorg... this adds 6 jumps. Bad.

Unless the label block is placed immediately after the arm, so `goto STORE28` is a jump to the next insn → deleted, merging back.

OK. Given the evidence (moves.md 302-311: five WALLs of the same family), I'll record this as a WALL with best 46 and the tag. What tag? The mechanism: "sched1 puts the ret constant before the call-result store because ret is a pseudo (no WAR on v0), so ret conflicts with $v0 and global-alloc gives it $a0; the pin is the only thing that creates the dependency". Tag: `sched1-ret-v0-war` — a new `<pass>-<what>` tag: `sched1-ret-war` or `global-ret-v0-conflict`. Let me check walls.txt for an existing tag.
