---
ts: 2026-11-06T01:45:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7SNFRoSwVvw8ebo47osx
---
Found it! Lines 540-560: "Delete insns setting a pseudo that is dead" — the dead-store elimination at the start of the jump pass (before regscan? it's `!reload_completed && after_regscan`). For vA, the trailing jump... no, that deletes INSNs (sets), not jumps.

Hmm, that deletes dead pseudo sets. Could it delete the `li`/store? No.

OK, let me actually test a different way: use gdb? Too heavy. Let me instead use cc1 with -dJ and compare, plus look at the .jump for a *return* in a simpler test. 

Actually, wait! Maybe the jump in vA was deleted because of the code at line 2056-2115 (the FUNCTION_END scan) *deleting the FUNCTION_END note*, which is followed by the label; and then `delete_insn(note)` — the note's NEXT is the label 374. Hmm.

Hold on, let me reconsider: in vA .rtl the order was jump 368, barrier 369, note BLOCK_END 371, note FUNCTION_END 372, label 374. The FUNCTION_END scan starts at last_insn. What is last_insn? It's computed in the loop at ~247: "Delete all labels already not referenced. Also find the last insn." It iterates all insns, setting last_insn = insn for non-deleted ones. Label 374 is referenced (LABEL_NUSES from the other jumps) so it stays; last_insn = label 374.

Backward scan from label 374: CODE_LABEL n_labels=1→0; PREV = note 372 FUNCTION_END → while condition fails (NOTE with kind == FUNCTION_END) → exit. insn = note 372 → delete it. So only the note.

So the jump 368 should survive... unless the label 374 was deleted and re-created? No.

Let me just look at the vA .jump dump for insn numbers near 366-374 with grep on the raw file lines 8735-8760 — I did: it showed store 366 then note 371 then label 374. The note 371's NEXT is now 374 (was 372 deleted then 371 relinked). So between store 366 and note 371, the jump 368 and barrier 369 were deleted.

Ahh — maybe I've got it: the pass at line 540-560 (`delete_insn` for dead pseudos) — it iterates `for (insn = f; insn; insn = next)`, and `next = NEXT_INSN(insn)` is captured BEFORE deletion. When it deletes an insn, it also deletes a following BARRIER. But not our jump.

Hmm, what about the very first loop "Delete insns following barriers, up to next label" (line 176): for the barrier 369 (after the jump 368), it deletes insns following it up to the next label: notes (skip) and FUNCTION_END (delete). Not the jump.

I'm going in circles. Let me use gdb-free binary search: compile vA with only -dj (no other) — same. Alternatively use `-dJ`? The jump2 dump shows the state after all jump passes; vA's jump2 also had the merge, so the jump was gone by then.

New approach: maybe the jump was deleted by `thread_jumps` BEFORE the first jump_optimize? No, thread_jumps runs after.

Hmm, wait: maybe the .rtl dump is written AFTER the first jump pass! Let me check toplev line 2702.
