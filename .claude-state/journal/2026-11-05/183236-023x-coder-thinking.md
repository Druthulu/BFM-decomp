---
ts: 2026-11-06T01:32:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6pt1yYUFONpRs74wa1GG
---
Great data. Line 77: "barrier: swap inner arms if(!overshot){store;ret=1;}else ret=0 (no cross-jump)". Line 149: cse2-pre-fold cross_jump.

For our case: cross-jump merges zero's trailing sw with dec's. Idea: restructure the zero block so the final store isn't the shared tail — e.g., move the `sh zero,244` after the `sw`? Target order li; sh; sw. If we put sw before sh, the tail becomes sh zero,244 (which dec doesn't have), so cross-jump would match nothing (or match earlier insns?). But target order would then be li; sw; sh — differs from target's li; sh; sw. Unless the compiler reorders? It won't.

Alternative: make zero's tail differ by making the store value not v0 but something that emits the same? No.

Alternative: restructure the CFG so zero isn't reachable by fall-through from dec's jump target comparison. Hmm, cross-jump compares any pair of blocks; dec jumps to epilogue (180c). It looks for blocks whose tails match... Actually find_cross_jump in jump.c is called for a jump instruction and compares the block containing the jump with the block it jumps to? Let me recall: `find_cross_jump (insn, e1, e2, ...)` is called from `jump_optimize` for each jump: it compares the block ending at insn (before the jump) with the target block, looking for identical insns at their ends, to redirect the jump to skip. Here dec's block ends with j 180c (epilogue). The target block (180c) is the epilogue: lw ra; lw s0; addiu sp; jr ra; nop. Not matching sw.

Hmm but the merge happened differently: mine's dec jumps to 1800, which is the *store at end of zero*. So cross-jump matched dec's block tail (the sw at 17cc in target) against... zero's block? Wait zero's block precedes 180c; zero's block is not the target of dec's jump (180c is). Unless find_cross_jump scans all blocks? In GCC 2.7's jump_optimize, find_cross_jump is called with (insn, JUMP_LABEL block) — it compares the insns before the jump with those before the target label. So dec's block (lw, addiu, sw) vs epilogue block (lw ra, lw s0, addiu sp, jr, nop) — no match. Hmm.

But maybe the actual merge is different: maybe zero's block got merged into dec? Let me reconsider: mine's 17c0 j 1800 with delay addiu. In target, dec is lw; nop; addiu; j 180c; sw. Mine: lw; j 1800; addiu v0,-1; then falls through to zero's code (move a0...). So dec jumps to 1800 (zero's shared store). So dec's own sw was removed and it jumps to zero's sw. That's cross-jump with the *store as target*.

GCC's find_cross_jump can also match insns of the jump's *own* block tail with insns at the target label's block; but here target is 180c epilogue. Unless after some other optimization, zero's block merged with epilogue... Actually the epilogue is shared and zero falls into it. GCC represents the epilogue block starting at 180c. dec jumps to 180c. find_cross_jump compares dec block backwards (sw, addiu, lw) with epilogue block backwards (nop, jr ra, addiu sp, lw s0, lw ra) — no.

Hmm, so where does the merge come from? Maybe it's not jump2 cross-jump but *reorg* / `thread_jumps`? Or maybe jump2's cross-jump with `optimize` does scan. Let me just look at the source of the compiler: gcc 2.7? There's a cc1 in the toolchain. But maybe easier: experiment.

Actually the residual says mine 136, target 138, difference: mine lost 2 instructions. Mine's dec: lw; j 1800; addiu (3 ins) + zero shared store at 1800. Target dec: lw; nop; addiu; j 180c; sw (5 ins) and zero's own sw. So mine saved 2. Fine.

Approach: try real-C variants and see scores. Candidate moves:

A. Make the zero block's store value not directly constant: `t = 0x1D; ... unk1C = t;` — but t is s32 local, maybe allocated v0 same. The instruction sequence would be li v0,29; sh zero,244; sw v0,28 — identical. Cross-jump still merges. Unless t's pseudo differs and reg allocation picks another reg → then the store is sw v1,28 and target wants v0. Hmm.

B. Prevent the merge by making the *dec* block's tail not a plain jump: e.g., write dec as `unk1C -= 1; return;` — that's what it is. What if we write `((Unk*)a0)->unk1C = ((Unk*)a0)->unk1C - 1;` same.

C. Add a `do{}while(0)` around the zero tail — could split the block so cross-jump can't match? C0535: do-while splits cse1 EBB. A do-while around `{ t=0x1D; ... }`? If the block gets split with a label, find_cross_jump won't cross labels. But a do-while(0) usually vanishes at -O2? The example shows it survives as a loop note and affects allocation but doesn't emit code. Would it stop cross-jump? Possibly not; jump2 works after loops are optimized? Order: jump opt runs before loop opt? In gcc 2.7: jump_optimize at the start of each pass; loop.c after. do-while(0) is turned into a plain block by... the parser doesn't; loop optimization removes the loop structure and leaves a barrier (NOTE_INSN_LOOP_BEG/END) or the block. If loop.c runs before jump2 (jump2 is a separate pass after loop), the do-while may be gone.

D. Use `goto` to restructure: e.g., in zero, instead of falling through, `goto end;` where end: is the epilogue... can't touch.

E. Break the tail identity by making the *dec* store happen through a different expression that still emits sw v0,28(s0) but at RTL level has a different source (e.g., via a pointer variable q). Cross-jump compares RTL insn identity: two `(set (mem (plus s0 28)) (reg v0))` are identical regardless of C source. Unless we can make one use `(plus (reg s0) (const 28))` vs `(mem (symbol_ref))` — no, same address.

F. Make the two stores different in *width/kind*: dec uses s32, zero uses u32 → same insn.

G. Make the zero store a *different pseudo* with same allocated reg but different RTL: e.g., `t = 0x1D; unk1C = t;` where t is a fresh pseudo. RTL: (set (reg:SI v0/px) 29) then (set (mem..) (reg px)). dec: (set (mem..) (reg v0)). find_cross_jump compares insns — the store insn has operand reg px in one, reg v0 in the other; they're not identical unless regs are the same pseudo. In target both use v0 (hard reg after reload? no — jump2 runs before reload, on pseudos). So if in zero the store's source pseudo differs from dec's, the RTL insns differ → no merge! And after register allocation both can still be v0.

That's promising: introduce a temp in zero: `t = 0x1D; ((Unk*)a0)->unk1C = t;` — but CSE may substitute t with 29, making it identical to the original (li then store). cse runs before jump2? Pass order: cse, then jump2? In gcc 2.7: -O2 passes: ... cse, loop, cse2, jump2? Let's check: jump_optimize is called multiple times. cse would propagate the constant into the store: (set mem 29), removing li v0,29 unless needed. Then the store would be `li`? Hmm, target has li v0,29 then sw v0 — so cse didn't fold the constant store (stores of constants get a reg in MIPS). Actually MIPS doesn't have store-immediate, so cse keeps li+sw.

If t is a variable, cse may still know t=29 and replace the store operand with 29 constant, then the store insn is (set mem (const 29)) identical in both? dec's store is (set mem (reg v0)) where v0 = unk1C-1. Not identical. Actually if zero's store becomes const-store, then it differs from dec's reg-store → no merge! And codegen of const-store: li v0,29; sw v0,28 — same as target. 

Wait but is that right? Target zero: li v0,29; sh zero,244; sw v0,28. If cse folds to const store, codegen emits li+sw, same. And dec's store is reg → different RTL → cross-jump won't merge. That could crack it!

Actually hold on: does cse even run after the assignment `t = 0x1D`? t is a local variable; if never used elsewhere, it's just a temp; cse would propagate the constant into the use. Yes.

But the existing code is `unk1C = 0x1D;` — a const store already! Yet the merge happened, meaning the RTL at jump2 time had (set mem (reg v0)) for both — because the MIPS backend's movsi splits const store into li+store at expand time? At RTL, `(set (mem:SI ..) (const_int 29))` might be valid and only split in reload/emit. Then dec's is (set mem (reg v0)). Those aren't identical, yet merge happened. Hmm, so maybe jump2's comparison uses the *pre-reload* RTL where both stores have reg? Or maybe the merge happens in a later pass (reorg?) on actual instructions.

Wait, maybe the actual merge is `jump2`'s "cross-jump" comparing *instruction sequences* (rtx_insn) with `rtx_equal_p`, and the const store's RTL after cse: for MIPS, movsi for const to memory is expanded at expand time into li+sw (since MIPS has no store-immediate), so at RTL both are `li v0,29; sw v0` where li is (set (reg v0) (const 29)) and store (set mem (reg v0)). So the store insns are identical (reg v0) — pseudos? v0 is a hard reg only if... li's dest would be a pseudo allocated later. At jump2 time it's a pseudo, e.g. reg 79. dec's store source is another pseudo (from lw). Different pseudos → stores differ.

Unless... the lw in dec loads into the *same pseudo* as zero's li dest due to local-alloc? No, jump2 is before reload/alloc? In gcc 2.7, jump_optimize (jump2) runs after cse2 and before sched? Register allocation (global-alloc, local-alloc) runs after. So pseudos differ.

Hmm, but maybe the merge isn't jump2 cross-jump; maybe it's `reorg`/`dbr` merging on actual hard regs after alloc: the last insn of zero block and dec block are both `sw v0,28(s0)`; reorg could... Actually there's a pass `thread_jumps`/`cross_jump` only in jump2.

Alternatively, the merge could be done by `flow` or by the "no-op move" elimination... Let me just test empirically: score variants.

Let me first try simple variants and see score. Candidates:
1. `t = 0x1D; unk1C = t;` (t already declared s32 at top).
2. Reorder? no.
3. `((Unk*)a0)->unk1C = (s32)0x1D;`
4. Use `v = 0x1D`? v is s16.

Actually, wait. Let's reconsider the comment: "find_cross_jump merges this block's trailing `sw $v0,0x1C($s0)` with the identical one ending the `dec:` block". That says jump2 cross-jump explicitly. So at jump2 time the RTL insns are considered identical — meaning the pseudos are the same. How? Because the `sw` operand is v0 pseudo? Hmm, in zero, the li's pseudo and store's pseudo are the same. In dec, lw's pseudo and store's pseudo are the same. If these two pseudos were *coalesced*... jump2 runs before allocation, but the RTL after cse/flow might have these as the same pseudo if cse reused? No, they're in different basic blocks; cse could assign them the same register-equivalent? Actually cse's constant propagation can substitute.

Hmm, maybe the trick is different: cross-jump's comparison is on insns ignoring register *numbers* (it uses `rtx_equal_p`? no, cross_jump has special handling: it compares insns with `insns_match_p` which allows registers to differ if they're not live? Let me recall jump.c's `insns_match_p`: "Compare the insns in the two blocks, ignoring differences in register numbers that can be fixed up by renaming." Yes! There's `rtx_renumbered_equal_p` used by cross-jump, which considers two insns equal if registers are renamed consistently. That's why the line-240 note says "jump2 cross-jump renames regs so const-vs-var stores do not differ". So different pseudos still match under renaming.

So the store `(set (mem (plus s0 28)) (reg X))` matches `(set (mem (plus s0 28)) (reg Y))` under renaming. And the preceding insns differ so only 1 insn matches — that's enough.

To defeat it: make the store's *address* differ structurally, e.g., one uses base+offset via a different base expression that renumbers differently? Both use s0+28. If in zero the address were computed via a pointer variable p (= a0), then the RTL would be (mem (reg p)) with p = a0, and after renaming p↔s0 it's the same. Hmm.

What if the store in zero uses a different offset form: e.g., `*(s32 *)((u8*)a0 + 0x1C)` vs struct field — same.

What if we change the store in zero to be a `sh`? No, unk1C is s32 and target is sw.

What if we make zero's store come *before* the `sh zero,244`? Then the block tail is sh (different from dec's sw) → no match. But target order... Let me check target order again: 1800 li v0,29; 1804 sh zero,244; 1808 sw v0,28. Yes sw last. So can't reorder.

Alternative: make zero's block not end at the epilogue: e.g. add an explicit `goto` to the epilogue? no.

Alternative: alter dec's block so its tail isn't a lone sw: e.g., in dec, use `unk1C--; return;` — target has the store in the delay slot of j 180c. What if we write `--unk1C;`? Same.

Hmm, what about making dec's store use a different *value register* that survives differently... target requires v0.

Another angle: the match is on a single insn `sw`. cross_jump requires at least 2 matching insns? Actually there's a check: "Don't make a change if the match is only one insn" maybe. Let me look at gcc 2.7's jump.c find_cross_jump. Let me find the compiler source in the repo? Maybe tools/ or a vendor dir. Let's grep.
