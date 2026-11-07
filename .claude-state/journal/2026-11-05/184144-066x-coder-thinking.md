---
ts: 2026-11-06T01:41:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YWn3by65vIWYjQfTx1Rj
---
Found it: "Delete all labels already not referenced" — after redirect_jump(insn, NULL_RTX), the return label 374's LABEL_NUSES drops to 0 (redirect_jump decrements and deletes it: `if (olabel && --LABEL_NUSES (olabel) == 0) delete_insn (olabel);`). Deleting the label also deletes insns after? delete_insn deletes the label and, if followed by a barrier, deletes the barrier too. Hmm, but our label 374 is after the FUNCTION_END note.

Wait, but then how does the epilogue get a label? The epilogue is emitted in final from... hmm. In gcc, the return_label is emitted in expand_function_end; if it's deleted, the epilogue is just appended after the body, and fallthrough works. Since zero falls through, that's fine. And all other returns were converted to RETURN insns? No! The other `return;` blocks compiled to `j 180c` in the target... 

Hmm, wait: if all return jumps get converted to RETURN insns by line 656 (because next_active_insn(label)==0), then the target would have `jr ra` at each return, not `j 180c`. But target has `j 180c` for all the early returns. So the label must NOT be at the end with nothing after it at that point — i.e., the epilogue code (or something) follows the label. Ah, but the epilogue is generated in `final`, after reload. Hmm, but wait: the function returns void; the epilogue label is placed... 

Actually maybe the difference: our vA has the return jump to label 374 which is the return_label at the very end. For the *other* blocks (the early returns), their jumps also target 374. Why weren't they converted to RETURN? Because line 656 checks `next_active_insn (JUMP_LABEL (insn)) == 0` — the label 374's next active insn... At the first jump pass, label 374 is at the end → next_active_insn == 0 → redirect to RETURN. That would apply to ALL jumps to 374, converting them all to RETURN. But the target has `j 180c`. So maybe HAVE_return is not defined, and gen_return... hmm redirect_jump(insn,NULL_RTX) creates a RETURN insn regardless of HAVE_return. Then later `final` would emit jr ra for RETURN. But target has j 180c for all returns!

So this path must NOT be taken. Which means next_active_insn(JUMP_LABEL) != 0 at that pass. So there IS something after the return label at the first jump pass. What? Possibly the epilogue instructions ARE emitted during expand_function_end (before passes). Let me check: in gcc 2.7.2, expand_function_end emits the return label and then... `emit_jump_insn (gen_epilogue())`? No, the epilogue is generated in final.c (`function_epilogue`). Hmm, but there's `use_return_insn`, `return_label` handling.

Wait, but the .rtl dump for vA shows label 374 at the very end with nothing after it (next: 0). And in the .jump dump, label 374 also at the end. So next_active_insn(label) == 0 → the line-656 redirect should have converted ALL jumps to label 374 into RETURN. But the .jump dump still shows `j` (label_ref) for the other returns (jump_insn 323 at line 694 etc.). Let me check: does the .jump dump show the early returns as `(set (pc) (label_ref 374))` or `(return)`?

From the tail of vA jump dump, the jump_insn 323 (dec) was at line 694; let me look at it.
