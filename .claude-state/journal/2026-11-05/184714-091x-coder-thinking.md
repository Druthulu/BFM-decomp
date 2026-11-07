---
ts: 2026-11-06T01:47:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Eqc9ctaRKYp7nk7YDhOz
---
next_active_insn(label 374): NEXT_INSN(374) == 0 → returns 0. So the redirect SHOULD fire for all jumps to 374 in the first pass. But the dump shows they didn't. 

Unless the first jump pass runs BEFORE the epilogue label is placed at the end... no, .rtl shows it.

Hmm wait, maybe `jump_optimize` is called with `after_regscan=1` and there's an early `if (!optimize) {...return;}`? No, optimize>0.

OK, maybe redirect_jump(insn, NULL_RTX) fails because `redirect_exp`'s validate_change fails for the jump pattern. For a simple jump: pattern = (set (pc) (label_ref 374)). redirect_exp: code==SET && nlabel==0 && SET_DEST==pc && SET_SRC is LABEL_REF with XEXP==olabel → validate_change(insn, loc, gen_rtx(RETURN, VOIDmode), 0). Hmm, `loc` here is &PATTERN(jump) (the SET). It replaces the SET with a RETURN. validate_change should succeed.

Then jump_optimize continues; JUMP_LABEL(insn) still 374? redirect_jump sets JUMP_LABEL(insn)=nlabel=0. Then `if (olabel && --LABEL_NUSES(olabel)==0) delete_insn(olabel)`.

Hmm, but the dump shows the jumps unchanged. So the redirect didn't fire. Why? Because maybe `JUMP_LABEL (insn)` is 0 for these jumps at this point! In the first pass, mark_jump_label sets JUMP_LABEL for jumps. It should be set.

Wait — unless the code at line 656 is inside a conditional block `if (!optimize) return;`... no.

Hmm, hold on. Let me reconsider: maybe the first pass at 2827 is `jump_optimize (insns, 0, 0, 1)` where the args are (f, cross_jump, noop_moves, after_regscan). Yes. And the dump .jump after it.

Let me test directly: does the first pass convert jumps-to-end into RETURN? Look at the orig .jump dump for the LAST function in the TU — its returns should become RETURN. But grep for "return" in vA.i.jump found none. Hmm, that grep was on vA.i.jump whole file? I did `grep -n "return\|(jump_insn" $D/jump_vA.rtl` on the extracted section. Let me grep the whole file for "(return)".
