---
ts: 2026-11-06T01:39:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zxGXrg7z7JitO49oAqWT
---
Pre-jump2: dec's block: insn 317 lw pseudo128; 319 addiu pseudo129; 321 store pseudo129; jump 323 -> label 371. zero's block ends: ... 361 sh; 364 li pseudo133; 366 store pseudo133; then label 371 (epilogue).

At jump2, registers are hard: dec's store is (set mem (reg v0)) where v0=2; zero's store is (set mem (reg v0)) after li v0,29. Both identical.

find_cross_jump(insn=323, JUMP_LABEL=371, minimum=1):
i1 = prev_nonnote_insn(323) = insn 321 (store). 
i2 = PREV of label 371 skipping notes/labels = insn 366 (store). 
Match! minimum 1→0. Continue: i1 = prev(321) = 319 (addiu v0,-1); i2 = prev(366) = 364 (li v0,29). Different (addiu vs set const 29) → break with lose. minimum <= 0 and last1 != 0 → merge. Yes, exactly one matching insn merges.

So to prevent: make the two stores not identical. Since after reload both are `sw v0,28(s0)`.

How can the target have them separate? The target build must have had them *not* identical at jump2. But the target's final bytes show both `sw v0,28(s0)` — identical! So at jump2 they must have differed, and reorg/later passes made them identical? No, reorg doesn't change registers.

Unless the target's jump2 pass didn't merge because at that point zero's store wasn't the insn immediately before the label 371 — e.g., zero's block ended with a jump insn at jump2 (later deleted by reorg's jump-to-next? reorg doesn't delete jumps; jump2 itself does jump-to-next deletion... Actually jump2 does "delete jumps to next instruction" at the start, before cross-jump? Order within jump_optimize: the loop deletes jumps to next instruction and performs cross-jumping in the same pass; the jump-to-next deletion happens when it encounters the jump (earlier in the insn stream). So if zero's block had a jump to label 371, it would be deleted by jump2 itself (it's a jump to the next insn) BEFORE the cross-jump loop reaches dec's jump? The pass processes insns in order: zero's jump comes after dec's jump in the stream (dec block precedes zero block). Wait no: dec block is before zero block in layout (dec at 314, zero at 325). The jump-to-next deletion for zero's jump would be processed after dec's jump. So when cross-jumping dec's jump, zero's jump still exists → i2 = zero's jump, not zero's store → first call fails; jump_chain retry (minimum 2): target = zero's jump (a jump to label 371); compare i1 = dec's store vs i2 = zero's store → match (min 2→1); then i1=addiu vs i2=li → differ → min 1 >0 → no merge. 

So if zero's block ends with a jump at jump2 time, the merge is prevented. Then later, jump2's own jump-to-next deletion removes zero's jump (since label 371 follows immediately), leaving fall-through. And dec's jump remains (target is not next? dec block is followed by zero block, not the label, so dec's jump survives), and reorg fills its delay slot with the store — but wait, dec's store was at 321 before the jump. In the target final, dec is: lw; nop; addiu; j; sw. The sw is in the delay slot after the jump. So reorg moved the store (321) into the delay slot of the jump (323). Yes! reorg's fill_simple steals the store from before the jump into the delay slot. That matches target exactly.

So: we need zero's block to end with an explicit jump at jump2, which is then deleted as jump-to-next. How to get that in C? A `return;` at the end of zero emits `j 371`. But earlier jump_optimize passes (cross_jump=0 but jump-to-next deletion still active!) would delete it if the label immediately follows at that time. Wait — does the earlier jump pass delete jumps to next? Yes, jump_optimize does "delete jumps to the next instruction" regardless of cross_jump. So the return jump would be deleted in the first jump pass (after cse) and gone by jump2. Hmm.

But hold on: maybe at the earlier pass, the label 371 is not immediately after zero's block, because the epilogue/return label is placed after other stuff? Let's check the .jump dump (after the first jump pass) — in j1_nopin.rtl, zero's block has no jump, and label 371 follows. If we add `return;`, would the first jump pass delete it? Let's test empirically: dump vA (with return) and look at .jump / .jump2.

Actually vA scored 9 same as nopin. Let me dump vA to see whether the jump existed. Maybe gcc elided the return at expand time because it's the last statement (there is such an optimization in gcc: in `expand_return`, if the return is the last statement...). Let's check vA's .jump RTL quickly.

Alternatively, force a jump that isn't recognized as terminal: e.g., `if (0) return;`? no. `goto end; end: return;`? Hmm.

Think: gcc's parser/c expander knows the last statement of the function; a return there still emits a jump (expand_null_return_1). But then the *jump-to-next deletion* in the first jump pass removes it.

Wait, but does the first jump pass run before or after the return label is placed? The label placement happens in final/function epilogue, which is at the end of compilation (after all RTL passes). Actually the return_label is created during expansion and placed... where? In gcc, `return_label` is placed at the end of the function body by `expand_function_end` (called after body expansion). So at the time of the first jump pass, the label exists at the very end, right after zero's block. So jump-to-next deletes zero's return jump. Hence vA = nopin.

So how to keep a jump at zero's block end through to jump2? We need the label NOT to immediately follow at the early passes but to immediately follow at jump2? Impossible; the layout doesn't change between.

Alternative: prevent the early deletion by putting something between zero's jump and the label that later disappears... e.g., a note? prev/next_nonnote skip notes, so jump-to-next considers the label after skipping notes. Hmm.

Alternative approach: make the store in zero NOT identical to dec's store at jump2 by making it a *different hard register*. Target requires v0 in both. But maybe we can make zero's store use a different register that gets coalesced? no.

Alternative: make the jump_chain retry not apply: If zero's block doesn't fall through into the label... 

Wait — actually, maybe I have it backwards: perhaps the real C doesn't have zero's block last! Maybe the real C has a different block order where zero is NOT adjacent to the epilogue, so the store isn't the label's predecessor. But the target's physical layout has zero adjacent to the epilogue. Layout order is determined by block order (fall-through order), which follows source. Hmm, unless the zero block is emitted at the end via a `goto` to a label placed at the end of the function in source. It IS at the end.

Hmm, let's reconsider. Maybe the merge is prevented not by a jump but by the store's *operand* differing at jump2. Consider: zero's store is `sw v0,28(s0)` where v0 is loaded by `li v0,29`. dec's store is `sw v0,28(s0)` where v0 = addiu. Identical insn. Unless the register allocator assigned different registers at jump2... but final bytes require both v0. Hmm, both must be v0 in final. But maybe at jump2 the allocation differs and reload changes... no, jump2 is after reload.

Wait wait. Maybe the real source has the zero block's store *before* the `sh zero,244`, i.e., different order, and the target's final order comes from sched1 reordering. Let's check: target order is li v0,29 (1800), sh zero,244 (1804), sw v0,28 (1808). If source had store then sh, sched1 might reorder them (independent stores)? Schedulers typically don't reorder stores much but sched1 does move stores. Hmm, that's plausible but then the store would still be the last insn.

OK here's another thought: what if zero's block ends with a *conditional* construct that jump2 keeps, and reorg turns it into fallthrough? E.g., `if (1) return;` — constant folding might keep a conditional jump? `if (x) return;` with x known 0? no.

Let me look at the target's actual structure again: target zero block at 17f8-1808 has NO jump; the epilogue at 180c. So final has no jump. But the question is only about jump2's view.

Maybe the answer: the early jump passes do NOT delete a jump to the immediately-following label when the label has LABEL_NUSES or when there's a barrier/note. Actually, the jump-to-next deletion in jump.c requires the label to be the next *real* insn AND ... let me read that part. Also, maybe gcc's expander emits the jump AFTER the store, and the first jump pass is *before* expand_function_end places the return label? No: expand_function_end runs during expansion, before any RTL pass.

Hmm, but actually — the first jump_optimize call at toplev 2827 is `jump_optimize(insns, 0, 0, 1)` — after_regscan=1? Let's look at the context: 2827 is in "rest_of_compilation"? Let me read the pass sequence around 2800-2930 to know which pass is which.
