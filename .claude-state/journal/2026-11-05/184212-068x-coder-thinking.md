---
ts: 2026-11-06T01:42:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TnoUaB1Zf68yG8mTPLf5
---
"Delete insn ... May delete some following insns as a consequence; may even delete a label elsewhere and insns that follow it."

The end-of-pass code deletes the FUNCTION_END note (line 2112). delete_insn(note) deletes the note; if followed by a barrier? The note is followed by label 374, not a barrier. Hmm.

But wait, the order in vA .rtl: jump 368, barrier 369, note 371 BLOCK_END, note 372 FUNCTION_END, label 374. The end-of-pass code deletes note 372. That doesn't delete the jump.

Hmm, unless line 656's redirect did fire: converting jump 368 to RETURN. Then "delete all labels already not referenced": label 374 still referenced by others. Then the FUNCTION_END scan from last_insn: last_insn is label 374; scan back: label 374 (n_labels 1→0), note 372 FUNCTION_END → stop. Delete note 372. So the RETURN insn 368 would remain, printed as `(jump_insn 368 ... (return))`.

But it's not there. So maybe the jump was deleted by the "Delete insns following barriers" pass at the start of the NEXT pass... no.

OR maybe the .jump dump I'm reading is after a *different* pass. Let me verify the dump order by checking gcc's dump file writing: `jump_dump` written right after the first jump_optimize (toplev ~2837). Yes.

Let me look at the actual full section around insn 366 in vA.i.jump with line numbers from the file (not my extraction), to make sure I'm not missing insns due to awk cutting early.
