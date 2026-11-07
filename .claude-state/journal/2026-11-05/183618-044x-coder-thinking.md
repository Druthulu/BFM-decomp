---
ts: 2026-11-06T01:36:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ba7jSLbYMvAr3PEtAjBi
---
So expand_null_return emits a jump. Then why did vA score the same 9? Maybe because the jump was emitted but deleted by a later pass before jump2 (e.g., jump_optimize earlier passes with cross_jump=0 still do "delete jumps to next instruction" — jump-to-next optimization). The earlier jump_optimize calls (2827, 2870, 2923, 2929) delete a jump to the immediately following label. At that time, zero's return jump targets return_label which is at the very end (epilogue). Between zero's jump and the label there might be nothing, so it's deleted as jump-to-next. Then at jump2, zero falls through again.

Hmm. So the explicit return gets removed pre-jump2. In the target, how did it survive to jump2? Maybe the return label is not immediately after zero's block at that time — e.g., the epilogue code (return_label) placement: in gcc, the return label is emitted at the end of the function after the body; zero's block is the last block, so the jump-to-next deletion applies. In target, though, the physical order is zero block then epilogue, so the jump was deleted at some point.

Unless the target's zero block ends with a *conditional* or the jump deletion didn't happen because a NOTE (LOOP_END etc.) or a barrier sits between.

Wait. Maybe the merge isn't at jump2 but at an earlier cross_jump pass? All earlier passes pass cross_jump=0. Let me double check jump_optimize args: (f, cross_jump, noop_moves, after_regscan). Line 2827: (insns, 0, 0, 1). Line 3142: (insns, 1, 1, 0). So yes only the last.

Hmm, then how does the target avoid the merge at jump2? Let me reconsider: maybe in the target at jump2 time, the two stores aren't both `sw v0,28(s0)` because register allocation gave different registers *at jump2*? No.

Wait, maybe the target's dec block doesn't end with a simple jump to the epilogue at jump2; maybe it ends with `return` (RETURN insn) because the function returns void and... no, all target returns are `j 180c`.

Let me look at the target: dec is `j 180c; sw`. The j is a simple jump to the epilogue label. zero falls through.

Hmm, let me reconsider whether the merge is really jump2. Maybe it's `reorg`'s `fill_simple` / `dbr`? No, cross-jump merging with deletion of the store and redirecting the jump is jump.c's do_cross_jump.

Actually wait — maybe the merge happens in jump2 but the comparison in the target differs because at jump2 time the *labels* differ: The epilogue label (return_label) may not be the target of dec's jump; instead each return jumps to a label placed right before the epilogue. That label is the target. zero falls through into... the label, and its sw is right before the label. Still same.

Let me instead just dump the RTL at jump2 for orig (with barrier) and nopin and see exactly. Tools: cc1 -da dumps. There's tools/cc1_dumps_tu.sh. Let me check its usage.
