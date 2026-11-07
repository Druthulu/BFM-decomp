---
ts: 2026-11-06T01:34:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZPOrkQ0XHyQmAbc48XyT
---
Critical: "If we haven't done any renumbering, don't make any assumptions: if (reg_renumber == 0) return rtx_equal_p (x, y);"

jump2 runs before global alloc, so reg_renumber is NULL/0 → only exact same pseudo matches. So the two stores must literally use the SAME pseudo. How?

Wait, which pass is this? jump_optimize runs multiple times: at the end of cse, before loop, after loop, after cse2, and after reload (jump2). Let me check pass order in gcc 2.7.2 toplev.c. If the merge happens after reload (jump2 pass), reg_renumber is non-null and registers are hard regs; then two `sw v0,28(s0)` match exactly (both v0, both s0). That's likely: the merge is done by the *post-reload* jump pass (jump2), where the registers are already hard. The comment says jump2 cross-jump. Yes! jump2 = the jump pass after reload. So rtx_renumbered_equal_p with reg_renumber set: hard regs compared by number → both v0. Hence identical.

So to defeat it, we need the post-reload instructions to differ. Both must be `sw v0,28(s0)` for the target bytes. Hmm, but target keeps them separate! So how does the original source keep them separate if both are identical `sw v0,28(s0)` at jump2 time?

Because find_cross_jump needs the *jump* insn. Let's look at the caller: line 1978 `find_cross_jump (insn, JUMP_LABEL (insn), 1, ...)`. This is called for a JUMP_INSN insn against its label. dec ends with `j .Lepilogue`; e1 = insn (the jump), e2 = JUMP_LABEL (the label at epilogue). It compares i1 = insn before jump (sw) with i2 = insn before label (in zero's block: sw). Same → match. minimum 1 satisfied (one side falls through into label → --minimum? Let's read around 1960-2000).

To defeat: make the insn before the epilogue label NOT be the sw — i.e., zero's block before the epilogue ends with something else, or there's a label/note in between... Or make the insn before dec's jump not the sw.

But target has both sw's identical and separate. So maybe in the target, zero's block does NOT fall through to the epilogue in a way jump2 sees? Hmm, target zero's last insn at 1808 is sw, then 180c is epilogue. dec's last is j 180c with delay sw. So both are identical and adjacent to the same label. Yet not merged in the target build.

Why? Perhaps because in the target, the jump2 pass ran BEFORE the final layout, and at jump2 time the epilogue label's preceding insn was different (e.g., the sw was not yet at the end, or the epilogue was a separate block reachable only by jump). Hmm.

OR: the merge is prevented because the zero block's sw has a REG_DEAD note on a different register? find_cross_jump doesn't compare notes on MIPS (STACK_REGS not defined).

OR: the zero block's sw at 1808 is preceded by `sh zero,244` and the epilogue... 

Hmm wait, maybe in the target the zero block's last insn is NOT at 1808 before the label; maybe there's an alignment or the label is placed differently. Let's re-read target: 1808 sw v0,28(s0); 180c lw ra,52(sp). Yes.

So how did the original compiler avoid merging? Maybe because the two `sw` instructions are in different *basic blocks* not connected: cross_jump compares e1's insns with the target label's block. In target, dec's jump at 17c8 targets 180c. The insn before 180c is the sw at 1808. e1 = 17c8 jump; i1 = prev_nonnote_insn(17c8) = 17c4 addiu (the delay slot is part of the jump insn; prev_nonnote of jump is the addiu? Actually the delay slot insn is the insn after the jump; prev_nonnote_insn(jump) = the insn before the jump, which is addiu at 17c4? No wait: target dec: 17bc lw; 17c0 nop; 17c4 addiu; 17c8 j; 17cc sw(delay). prev_nonnote_insn(jump) walks backward from the jump: 17c4 addiu. And i2 = PREV of the label 180c, skipping notes/labels: 1808 sw. Compare addiu vs sw → differ. Match length 0 → minimum 1 → no merge.

In mine, dec's block: 17bc lw; 17c0 j; 17c4 addiu(delay). prev_nonnote_insn(jump at 17c0) = 17bc lw. Label 1804 (epilogue) prev = 1800 sw. lw vs sw differ → no match?? But mine DID merge. So the merge in mine must be a different mechanism: maybe the merge happened at the pre-reload jump pass (jump_optimize after cse2), where dec's block still had its store before the jump. In that pass, dec block: lw; addiu; j; sw? Pre-reload, the jump insn's delay slot isn't filled yet; the store is an insn before the jump (or after?). Pre-reload, the RTL order is: ... lw; addiu; (set mem) ; jump? Actually store is a separate insn before the jump. So prev_nonnote(jump) = store. Label's prev = zero's store. Both stores: at that pass reg_renumber==0 → rtx_equal_p → need same pseudo.

Hmm, but the two stores' value pseudos differ... unless cse made them the same? Hmm.

Wait, maybe the merge happened in the post-reload jump2 but on the *delay-slot* insn: In mine after reorg? No, reorg runs after jump2.

Let me look at which passes call find_cross_jump with what. Line 1941: minimum 2; 1978: minimum 1 against JUMP_LABEL. Let me read 1900-2050.
