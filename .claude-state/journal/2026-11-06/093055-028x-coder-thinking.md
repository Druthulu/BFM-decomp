---
ts: 2026-11-06T16:30:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_r8EZ2u85Z6IYy995V458
---
Key: "We give up if we find a label in stream 1." So a CODE_LABEL in the first stream stops cross-jump merging. So placing a label inside the first block (that is actually referenced, so it survives) would prevent merging. But an unreferenced label is deleted (LABEL_NUSES==0 deleted). If we use a `goto` to it, the goto emits a jump instruction (bytes change).

Hmm, but what about a label at the *start* of the first block that is jumped to by the `if`? The `if (f()!=0) goto L; ... L: calls...` — the compiler already places a label there (the if target). Cross-jump uses find_cross_jump(insn, x, ...) where e1 is the jump. It gives up when it finds a label in stream 1 before minimum insns. The minimum is 2.

The target structure: the branch target labels are at the start of each call block. Both blocks are targets. Cross-jump compares preceding instructions: the jump at end of block 1 is `j ret` (simple jump). e1 = that jump; e2 = the jump at end of block 2? Actually cross-jump is invoked on conditional jumps too (line 1923: `if (cross_jump && condjump_p(insn))`). The two conditional jumps `beqz v0,180` and `beqz v0,1c0`? Hmm.

Actually the merging we observe: mine merges the two 4-call blocks into one (one copy, branch to it from both). Wait no: mine[51] is `bnez v0,170` and the block at 0x170... let me get mine's actual layout to understand what got merged. Let me use --keep and objdump? Or simpler: dt.sh shows the diff; mine has 307 vs target 318 (11 fewer = one block of 11 insns merged away).

Cross-jump merging happens in jump2 (after reload). The barrier is an asm — wait, an empty asm `__asm__ __volatile__("")` compiles to... In gcc 2.7.2, does an empty asm emit an instruction? It emits an asm insn with an empty template — it stays as an RTL insn (asm_operands) that outputs zero bytes! So it IS in the RTL stream (an insn whose template is empty). That's why it blocks cross-jump: it's a real insn in the stream that differs (asm operands), and also `insn_cost`... So removing it lets cross-jump merge.

To replace it with real C that emits zero bytes but stays in the RTL stream... Options:
- A zero-byte real construct: e.g., a `static` volatile? No.
- A cast that generates an RTL insn with no output? Most casts fold away.

Hmm, C0505 says: "A goto chain → structured C ... a label between a store and its tail blocks jump1's if-conversion". But here we need to block jump2 (cross-jump after reload). The doc C0208 says "CROSS-JUMPING RUNS AFTER SCHEDULING, SO NO C-LEVEL BARRIER CAN STEER IT". So a real C construct can only steer cross-jump via actual RTL differences.

What real C could make the two call blocks non-identical at RTL but identical bytes?
1. Different argument spelling that produces the same RTL: e.g. `func_800D2AA0(0)` vs `func_800D2AA0((u8*)0)`. Both const 0 → same RTL. Hmm, but a cast to pointer might generate a different mode? `move a0,zero` either way.
2. One block uses `func_800468FC()` and the other... same function, can't differ.
3. Register allocation difference: if one block uses a different register for the same value. But all args are constant 0.

Hmm, cross-jump merges *suffixes*; maybe merging happens because both blocks end with `j ret`. If the source had one block fall through to `ret` (no jump) and the other jump, cross-jump could still merge. 

What if the two blocks' order/arrangement differs: target block1 is followed by block2 (fallthrough after block1's j ret)? In target, block1 ends with `j 554` at 0x178, then block2 starts at 0x180 (the second if's target... wait 0x180 is where `beqz` goes when v0==0). Let me re-read target:

- 0x150: `beqz v0,180` — if func_800D2454()==0 goto 0x180.
- 0x158-0x178: call block A (4 calls) + j 554.
- 0x180: next: lui a0,D_800EC9A4 ... func_800D2704 call setup.
- 0x190: `beqz v0,1c0` — if ==0 goto 0x1c0.
- 0x198-0x1b8: call block B (identical) + j 554.
- 0x1c0: continuation.

So blocks A and B are identical and both end `j 554`. Cross-jump should merge them unless something stops it. In target they're NOT merged. So the original source must have had something. Since the original binary was compiled from the real source, the real source presumably had this structure and gcc didn't merge. Why? Cross-jump merging requires the *preceding* sequences to be comparable. It compares backwards from the jumps. find_cross_jump(e1=jump A, e2=jump B): i1 = prev_nonnote(A's j) = move a0,zero; i2 = prev of B's j skipping notes/labels = move a0,zero. Continue: jal, nop, jal, nop, jal, move a0,zero, jal... Then i1 = prev_nonnote(jal func_800D2D44) = `beqz v0,180`? Wait A's block starts at 0x158 right after the beqz at 0x150 (with a delay nop at 0x154). So i1 walks back to the beqz. i2 walks back: B's block starts at 0x198, preceded by beqz at 0x190. Both `beqz v0,label` — but the labels differ! `rtx_renumbered_equal_p` compares label refs? It might consider different labels unequal. That would stop at the beqz — but by then it has already found 11 identical insns, enough to merge.

Hmm, so why not merged? Unless minimum is larger. Let me look at the call site: `find_cross_jump (insn, x, 2, ...)` — minimum 2. So it should merge.

Wait, maybe target's blocks are NOT identical: check `func_800D2D44(0)` in A: 0x158 jal func_800D2D44; 0x15c `move a0,zero` (delay slot). B: 0x198 jal func_800D2D44; 0x19c `move a0,zero`. Same. func_800468FC: A 0x160 jal, 0x164 nop; B 0x1a0 jal, 0x1a4 nop. Same. func_8002D8D4: A 0x168 jal, 0x16c nop; B 0x1a8 jal, 0x1ac nop. Same. func_800D2AA0: A 0x170 jal, 0x174 move a0,zero; B 0x1b0 jal, 0x1b4 move a0,zero. Same. j 554: A 0x178, B 0x1b8. Same target.

They ARE identical. So why does the original object keep both? Because... maybe the original compilation used -O2 but cross-jump has a limit on "cross_jump_death_matters" or the insns' registers differ. Or maybe this function was compiled with different flags? The whole TU has a recipe.

OR: the real source had the two blocks differ in a way that produces identical *final* bytes after relaxation. E.g., one block's `func_800D2AA0(0)` came from `func_800D2AA0(NULL)`? same.

OR the difference is in a REG note / REG_EQUIV that prevents equality.

Hmm, alternatively: cross-jump's `rtx_renumbered_equal_p` compares hard registers after reload. If one block uses a0 and the other uses... both zero.

Hold on: maybe the merge is blocked because the blocks are *not* preceded by comparable insns within the minimum: find_cross_jump requires at least `minimum` insns; we have 11. Fine.

Let me actually test with the real gcc: does removing just the barrier merge them? Yes, w3 shows 10 fewer insns. So the asm blocks it. The original binary has them unmerged, so the real source must have had something that blocks it — possibly an empty asm too! But the task says the def must be lever-free. If the original source had an asm, then this is a genuine wall (no-c-spelling / hand-asm).

But wait: could the real source have had a *volatile* or some construct that creates an RTL insn with zero bytes? Let's think about what real C produces an insn with no output:
- `(void)0;` — nothing.
- A label with a goto: jump insn (bytes).
- `__asm__` — lever.
- A `static const`? no.
- A zero-length struct copy? expand_block_move with size 0 → nothing.
- `volatile` access to a zero-size? no.

Hmm, what about a `switch` with one case? Generates a jump.

What about `if (p[1] != 0) ... else ...` structures? 

Actually, maybe the target's two blocks aren't the result of two source copies but of a `goto` to a shared label that jump2 then *unmerged*? No, jump2 merges, never unmerges.

Wait — cross-jumping is enabled only in jump2 for -O2? `jump_optimize(f, cross_jump, ...)` called from toplev with cross_jump=2 at -O2. Hmm.

Another possibility: cross-jump does NOT merge when the two blocks have different LABEL_NUSES or when the jump targets... Actually find_cross_jump is called on *conditional* jumps: line 1923 `if (cross_jump && condjump_p (insn))` then `x = prev_real_insn (JUMP_LABEL (insn))` and find_cross_jump(insn, x, 2, ...). Here insn = a conditional jump, x = the insn before its target label. So it compares the code *before* the conditional jump with the code *before the target label*. For our case, the conditional jumps are the beqz at 0x150 and 0x190. find_cross_jump(beqz A, x=prev before label 0x180). Before beqz A: `move a2,s0`? Actually the call setup. Before label 0x180: `j 554` (block A's jump). These differ → no merge there.

Then also the unconditional jumps: line ~1941 uses find_cross_jump(insn, x...) for simplejump? Let me read lines 1900-1960.
