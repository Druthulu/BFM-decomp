---
ts: 2026-11-06T01:41:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_55Q6RYLpLvjL5l2AoEtC
---
Not it. Let me search for the case where a jump to the next insn is removed: maybe in `delete_insn`'s "insn after a barrier" or in `flow`. Hmm.

Actually maybe the jump wasn't deleted by jump.c but by cse's delete_trivially_dead_insns? No.

Wait — maybe I mis-attributed: in vA, the source has `return;` as the last statement of the function. gcc's `expand_null_return` might NOT emit a jump because of the check in stmt.c around line 2622. Let me look at stmt.c:2600-2630: "expand_return ... because expand_null_return takes care of them". Actually there's `expand_start_stmt_expr`... Let me look at how `return;` is expanded in c-parse: `c_expand_return`? Hmm.

But the .rtl dump clearly shows the jump at insn 368 to label 374 (in the vA .rtl dump). So it was emitted. Then deleted in jump pass.

Let me diff .rtl vs .jump insn 368: maybe redirect_jump turned it into RETURN and then the RETURN insn is at a different position — the dump tail showed label 374 after note BLOCK_END, no insn. Let me grep the .jump dump for "RETURN" uppercase? The dump prints `(return)` lowercase. grep "return" found nothing, so gone.

Let me look at jump.c line 200-260 ("Delete insns following barriers"). Line 244 `insn = delete_insn (insn)`. Hmm.

Actually, maybe the jump was deleted by the very first thing: line 656 redirect_jump(insn, NULL_RTX) → becomes RETURN; then later in the same loop the RETURN cross-jump block at 2028: `if (cross_jump && ...)` cross_jump=0, skipped. Then after the loop, "Delete extraneous line number notes"... no.

Could `delete_insn` be called because the RETURN insn is dead? There's a "delete_dead_jumps" at the end? Let me look at jump_optimize's ending around 2050-2130.
