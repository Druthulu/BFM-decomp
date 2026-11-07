---
ts: 2026-11-06T01:44:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7ziVUeMXO7tMwyHujVVM
---
Now it's clear. In orig, the barrier is a real `(asm_input ("") )` insn 368 at jump2 time, after the store. So find_cross_jump for dec's jump: i1 = prev_nonnote(dec's jump) = store; i2 = prev of label 373 = the asm insn → differ → no match. Then jump_chain: zero has no jump. So no merge.

And the asm insn survives to final but emits zero bytes.

So the barrier's role: an insn between zero's store and the label.

Now, the target's real C must have something else there, or the target's real C prevented the merge differently. Our job: find real-C that makes find_cross_jump fail at jump2 without any asm.

Options at jump2 (post-reload, hard regs):
1. Make zero's store instruction differ from dec's store in some way (different reg or different address form or different insn).
2. Put a non-note insn between zero's store and the label (like the asm) — e.g., another real instruction that emits no bytes? Impossible.
3. Put a CODE_LABEL between the store and the label! find_cross_jump skips CODE_LABELs when walking i2 backward (`while (i2 && (GET_CODE (i2) == NOTE || GET_CODE (i2) == CODE_LABEL)) i2 = PREV_INSN (i2);`) — it skips labels, so that doesn't help.
4. Make zero's block not end at the store: i.e., the store is not the last insn before the label. E.g., if the zero block's final insn were a jump (then i2 = jump ≠ store). But the jump would be deleted as jump-to-next... Wait, is it? In vA the jump was deleted. Why? Because redirect_jump(insn, NULL_RTX) at line 656 converted it to RETURN? But the other returns weren't converted. Hmm, but wait: for vA the jump WAS deleted. Let me check: in vA .jump, the jump 368 is gone entirely. If it had been converted to RETURN, we'd see `(jump_insn ... (return))`. Gone. 

Hmm, maybe delete happened because the label 374 got deleted (LABEL_NUSES dropped to 0? no, others use it). 

Ohh, maybe the jump was converted to RETURN and then the "return cross-jump" — no, cross_jump=0.

Wait, maybe jump.c line 1742 "Detect a conditional jump jumping over an unconditional jump" ... no.

Let me look at line 189/244: "Delete insns following barriers, up to next label." In vA .rtl: jump 368, barrier 369, notes, label 374. At the START of the first jump pass, this loop: sees barrier 369 → then deletes insns after it up to the next label: notes with line numbers != FUNCTION_END are skipped, else deleted. Note 371 BLOCK_END: `NOTE_LINE_NUMBER(insn) != NOTE_INSN_FUNCTION_END` — BLOCK_END is negative (not FUNCTION_END) → insn = NEXT (skipped, not deleted). Note 372 FUNCTION_END: NOTE_LINE_NUMBER == FUNCTION_END → `insn = delete_insn(insn)` → deletes note 372! And then next = label 374 → stop. So the FUNCTION_END note is deleted early, but the jump and barrier remain.

Hmm so the jump should remain. But it's gone. Unless the jump got deleted at line 656 (redirect to RETURN) and the RETURN then... the dump would show it.

Let me just directly grep the vA .jump for "jump_insn 368" — earlier grep for "insn 368" showed only line 5958 (a different function's insn 368). So the insn was deleted or renumbered.

Wait, maybe insn 368 got converted to RETURN and then *merged with the label*: the code at line 2112 deletes the FUNCTION_END note. Then in the NEXT jump pass (there are several), a RETURN insn at the end of a block... would be deleted? There are more jump passes after (at 2870, 2923, 2929) but the dump .jump is after the first. Hmm, unless the .jump dump is written after a later pass. Let me check toplev: the jump dump is written right after the first jump_optimize (line ~2838). Yes.

OK let me stop theorizing and look at vA's .jump dump around the end again: it showed insn 366 store, note 371 BLOCK_END, label 374. The jump 368 and barrier 369 both gone. What deletes a simplejump plus its barrier? delete_insn(jump) deletes the following barrier too. So delete_jump(jump) was called. Which call site? line 667 (condjump), 1130, 1299, 1733 (condjump). None for simplejump. Unless the jump was first turned into a RETURN and then `delete_insn` somewhere.

Hmm, wait: maybe the jump was redirected to RETURN by line 656, and then the RETURN insn was deleted by the code at line ~2056? Let me read 2050-2060.
