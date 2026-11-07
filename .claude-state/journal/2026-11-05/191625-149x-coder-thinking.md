---
ts: 2026-11-06T02:16:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QYbk5TMVweJqtdfkRFiy
---
condjump_p returns 1 if SET_SRC is a LABEL_REF! So a simple jump IS "condjump_p" in gcc 2.7.2 (it's "jump_p" semantics). Then the check at line 664 `if (reallabelprev == insn && condjump_p (insn))` applies to simple jumps too, and delete_jump is called. But wait, there's the earlier `this_is_condjump = condjump_p(insn); this_is_simplejump = simplejump_p(insn);` — the code uses condjump_p which includes simple jumps. OK.

So the deletion: reallabelprev == insn, i.e., prev_active_insn(JUMP_LABEL) == insn. For our jump 368, JUMP_LABEL = label 374; prev_active_insn(374) skips the barrier and notes → insn 368. So reallabelprev == insn → delete_jump(368) → deletes the jump (and its dead computation).

So the trailing `return;` jump IS a jump-to-next (the label 374 is the next active insn after skipping the barrier/notes) and is deleted in the first jump pass. Confirmed.

Now: how can the original have kept a jump there? It can't if the label is next. So the original's zero block did NOT end with a jump. Therefore the merge must have been prevented by a different mechanism.

Given condjump_p treats simple jumps as condjumps, the earlier path at line 656: `if (JUMP_LABEL(insn) && (next_active_insn(JUMP_LABEL(insn)) == 0 || ...)) redirect_jump(insn, NULL_RTX);` — for our jump, next_active_insn(374) == 0 (label is last) → redirect to RETURN. But wait, in the mini TU, the label 374 is the last insn → redirect fires, converting the jump to a RETURN. Then condjump_p(RETURN) = 0 (PATTERN is RETURN, not SET). Then the delete wouldn't fire. But the delete DID fire with a PATTERN = (set (pc) (label_ref)). So the redirect did NOT fire, meaning next_active_insn(374) != 0.

What's after label 374 in the mini TU? The .rtl dump showed label 374 as the last insn. But next_active_insn skips notes... NEXT_INSN(374)=0 → 0. So redirect should fire!

Unless... the order: line 653 reallabelprev, line 656 redirect, line 664 delete. If redirect fired, PATTERN becomes RETURN; then condjump_p false; then reallabelprev was computed BEFORE as 368. So no delete. But we saw a delete with a SET pattern → redirect didn't fire.

Hmm, why not? Because `JUMP_LABEL (insn)` — is it set? mark_jump_label sets it at the start of the pass. For our jump, JUMP_LABEL=374 (we read fld[7] = 0x82dc580 which is suspicious; maybe JUMP_LABEL is at a different offset). Hmm.

Actually, maybe the redirect check uses next_active_insn(JUMP_LABEL) where JUMP_LABEL is... whatever.

Let me stop this sub-investigation. The bottom line: a trailing return jump is deleted early. So the original must have avoided the merge differently.

New idea based on the condjump_p discovery: since simple jumps count as condjumps, the code at line 656 `redirect_jump(insn, NULL_RTX)` converts any jump whose target label is at the function end into a RETURN. Our early return jumps (to the same label 374) would ALSO be converted to RETURNs! But the target has `j 180c` for them. In the mini TU, are the early returns converted? The .jump dump showed jumps to label 373/374 as `(set (pc) (label_ref ...))`. So they were NOT converted. Why? Because next_active_insn(374) != 0? Hmm.

Wait, maybe because those jumps have already been processed earlier in the loop, when the label's next active insn was something else? The pass iterates forward; the label 374 is at the end. All jumps to it are processed in the same pass. If next_active_insn(374)==0, all would be converted. They weren't. So next_active_insn(374) != 0. What is it then? Maybe the label 374 is followed by something in the insn chain that isn't printed because print_rtl stops at... Let me check: in the mini TU, after label 374 there might be a `(note NOTE_INSN_FUNCTION_END)` and then the epilogue RTL? Let me look at the miniVA .rtl tail fully.
