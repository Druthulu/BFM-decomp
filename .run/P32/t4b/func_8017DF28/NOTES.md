# func_8017DF28 (ov_SC06_022, 119 ins) — S83 hand analysis (residual 2: `addiu $s2,$sp,0x10` in the jal's delay slot vs the target's bnez slot)
Target read: the block-move stores are `sw $vN,0x1C..0x2C($sp)` (sp-relative, BEFORE the jal); `addiu $s2,$sp,0x10` sits in the
`bnez $s1` delay slot = the FIRST insn of the taken branch (.L8017DFAC) hoisted by reorg. So in the original the block-move's
copy_addr_to_reg pseudo DIED at the copy (stores folded to sp-relative by cse/find_best_addr) and `&mtx` was materialised
afresh inside the taken branch; in every draft cse REUSES the block-move pseudo for the later `&mtx` args (invalidate_for_call
never invalidates pseudos), so its def stays at the top and reorg parks it in the jal slot. Measured (S79): mptr before/after
the call/after the if, inline `&mtx`, §194-K re-tie (un-folds the stores), word-wise copy (loses the 3-load groups), §H diamond
(cross-jumped away). Untested: a source form in which cse does NOT substitute the pseudo at the arg site — e.g. the copy
through a `register Blk20`-typed variable, a `volatile`-qualified destination, or the copy destination expressed as a
different-but-equal address (`(Blk20 *)((u8 *)&pos - 0x20)` — check whether cse folds it back). Fable: read mips.c
expand_block_move + cse.c cse_insn's REG substitution for `(plus fp 16)`.
