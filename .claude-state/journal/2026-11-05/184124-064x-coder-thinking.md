---
ts: 2026-11-06T01:41:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3Jo35eGR6EIRaIEDyEO9
---
There it is! `#ifdef HAVE_return ... if (insn && GET_CODE (insn) != BARRIER) { emit_jump_insn (gen_return ()); emit_barrier (); }`. Wait, that ADDS a return. Hmm, but this is guarded by HAVE_return; if MIPS defines HAVE_return, the compiler emits explicit RETURN insns when control falls through to the epilogue! And the target has `j 180c`, not jr ra, so HAVE_return is probably not defined... Actually wait, the target's epilogue is shared with jr ra at the end, and all returns are `j 180c`. If HAVE_return were defined, the last block would get a `jr ra` return insn. Not the case. So HAVE_return is not defined for this port. Good.

So where did the jump go? The "detect jump to following insn" for condjump only... For simple jumps, maybe `delete_jump` isn't called but the jump remains as RETURN and then... the FUNCTION_END scan: "One label can follow the end-note: the return label. Ordinary insns can follow it if returning a structure." Our sequence: jump(return) 368, barrier 369, note BLOCK_END 371, note FUNCTION_END 372, label 374. The scan from last_insn backward: label 374 (n_labels 1→0), then note 372 is FUNCTION_END → loop stops? The condition allows NOTE with kind != FUNCTION_END; FUNCTION_END stops. Then check: insn is NOTE FUNCTION_END → can_reach_end=1; delete the note. So the FUNCTION_END note is deleted, leaving label 374 at the end. Fine.

So after the first jump pass, the RETURN insn 368 should still be there... but the dump shows it gone. Unless the dump .jump is written BEFORE... no.

Hold on, maybe the jump was converted to RETURN and then `delete_insn` in the redirect_jump when olabel's LABEL_NUSES hits 0: `if (olabel && --LABEL_NUSES (olabel) == 0) delete_insn (olabel);` — that deletes the *label*, not the jump.

Hmm, but wait: after redirect, the label 374 might have 0 uses and get deleted... but then the return label placement breaks. In the dump, label 374 exists.

Let me just look at the full .jump section of vA around the end with all lines (maybe the return is represented as `(jump_insn 368 ... (return))` but my awk extraction cut at a ";; Function" line inside? No.

Let me directly grep the vA .jump file for "368".
