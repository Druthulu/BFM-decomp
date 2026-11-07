---
ts: 2026-11-06T01:40:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CyABOlOQq1oLy2zcAHY2
---
Not our case. Let's find where a simple jump to the immediately following label is deleted. Maybe `delete_jump` handles it, or the "thread_jumps" pass. But vA's .jump shows the jump gone and no barrier, so something deleted it. Let me check the .jump dump more carefully: maybe the first jump pass turned it into... In vA .jump, after insn 366 comes NOTE BLOCK_END then label 374. The jump insn 368 and barrier 369 are gone. Which code deleted them? Possibly `delete_dead_jumps` or the loop at line 176 "Delete insns following barriers, up to next label" — no.

Maybe thread_jumps (flag_thread_jumps) deleted it? thread_jumps runs before cse (line 2859) and again at 2937. Hmm, but thread_jumps redirects jumps.

Actually, maybe it's `redirect_jump (insn, NULL_RTX)` at line 656: "If a jump references the end of the function, try to turn it into a RETURN insn, possibly a conditional one." redirect_jump(insn, NULL_RTX) converts the jump to a RETURN. But our function's epilogue is shared; the label 374 is followed by FUNCTION_END note, not a RETURN insn (the epilogue instructions are emitted later, after all passes? Actually the epilogue is generated in final, after reload). So at jump pass time, the return label is at the very end with nothing after it → next_active_insn(label) == 0 → redirect_jump(insn, NULL_RTX) converts it to a RETURN insn! But then target's returns are `j 180c`... Hmm, but these RETURN insns later get redirected? Wait, in vA .jump the jump just vanished entirely (no RETURN either?). Let me look more carefully at the .jump dump around that area. The tail showed insn 366 then NOTE BLOCK_END then code_label 374. A RETURN insn would appear as `(jump_insn ... (return))`. Not there. So the jump was deleted.

Wait, maybe redirect_jump(insn, NULL_RTX) converts to RETURN and then... hmm.

Let me look at the .jump dump for the nopin (which has no return jump) — same tail. And for the orig with barrier: the barrier insn after the store prevents? Let's compare. Actually let's find what pass deletes it by looking at the .rtl (before jump), .jump (after first jump pass). In vA .rtl the jump exists. In .jump it's gone. So the first jump pass deletes it.

Where? Line 656: `if (JUMP_LABEL (insn) && (next_active_insn (JUMP_LABEL (insn)) == 0 || GET_CODE (PATTERN (next_active_insn (JUMP_LABEL (insn)))) == RETURN)) changed |= redirect_jump (insn, NULL_RTX);`

next_active_insn(label 374): the label is at the very end, next is FUNCTION_END note, then 0. So next_active_insn == 0 → redirect_jump(insn, NULL_RTX) → makes the jump a RETURN insn. Then subsequent code (RETURN handling) cross-jumps returns... and then maybe the RETURN insn gets... Hmm, but the dump shows no RETURN insn.

Oh wait — maybe redirect_jump to NULL_RTX turns `(set (pc) (label_ref))` into `(return)`; then at line 2030 the RETURN cross-jump code runs; then... the insn would still be there. Unless `delete_jump` was called. Let me look at the actual .jump dump around 360-374 in vA with line numbers.

Actually maybe the RETURN insn is deleted because "returns all jump to the same place" and there's another RETURN earlier... cross-jump between returns would merge them (minimum 2). Hmm.

Wait, maybe I'm looking at the wrong function instance: the TU might define func_80184E8C twice? No.

Let me look at vA .jump tail with more context including the barrier/return.
