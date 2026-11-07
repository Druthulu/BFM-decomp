---
ts: 2026-11-06T01:42:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nGb4TRVG2wG3v2oSU8tv
---
So early jumps to label 374 stayed as `j label_ref`, not RETURN. Why didn't line 656 fire for them? Because `next_active_insn (JUMP_LABEL (insn))` — next_active_insn(374) skips notes and labels but not... hmm, it should be 0 if the label is last.

Oh wait! Maybe next_active_insn returns the label itself? No. Let me look at the condition: it's inside `if (this_is_simplejump...)`? Let me look at the code context around line 650.

Actually line 653: reallabelprev = prev_active_insn (JUMP_LABEL (insn)); then line 656 the redirect check. Hmm. For label 374 at end: next_active_insn(374) = NEXT_INSN chain; if 0 → redirect. Should fire for ALL jumps to 374. Unless... the jumps to 374 were processed BEFORE the label was last? No.

Wait, maybe `JUMP_LABEL (insn)` is 0 for these jumps at that point because mark_jump_label... no, they show label_ref 374.

Hmm, but the early jumps were not converted. So the condition was false: next_active_insn(374) != 0 and its PATTERN != RETURN. What is after label 374 in the *full* insn chain? The .rtl dump shows label 374 last in the function, but the dump for the function ends there because the next function's insns follow! In the TU, after this function's label 374, the next function's code follows (the TU has many functions). So next_active_insn(374) is the first insn of the NEXT function! That's why the redirect doesn't fire.

And for vA, the last function's return jump (insn 368) — wait, the same label 374 is the target of all returns, and next_active_insn(374) is the next function's code, so line 656 wouldn't fire for insn 368 either. Then why did insn 368 disappear?

Hmm, let me re-check: maybe insn 368 is not gone but the dump's function section ended. My awk extraction `NR>n && /^;; Function/{exit}` stops at the next ";; Function" marker. The .jump dump: after our function's last insn (label 374), the next thing is the next function's dump header ";; Function ...". But insn 368 should be before label 374 in the section. It's not there.

Wait, in the vA .rtl dump the tail was:
```
(jump_insn 368 366 369 (set (pc) (label_ref 374)))
(barrier 369 368 371)
(note 371 ... BLOCK_END)
(note 372 ... FUNCTION_END)
(code_label 374 ...)
```
In the vA .jump dump tail:
```
(insn 366 364 371 store)
(note 371 366 374 "" NOTE_INSN_BLOCK_END)
(code_label 374 371 0 181 "")
```
The jump 368 and barrier 369 are gone; the FUNCTION_END note is gone (deleted by the end-of-pass code). So the jump WAS deleted.

Which code? Possibly the "Delete insns following barriers, up to next label" — no. The FUNCTION_END deletion at line 2112 only deletes the note.

Hmm, wait: the label 374's PREV is now the note 371, whose prev is insn 366. The jump 368 was between 366 and the note 371. So the jump was deleted and the note's PREV updated.

Maybe `delete_jump(insn)` at line 1733: "Detect a conditional jump going to the same place as an immediately following unconditional jump" — no (simple jump).

Let me look at lines 1000-1060 (simplejump branch, reallabelprev == temp).

Actually easier: let me search for code that deletes a simple jump whose label is the next label. Perhaps in `thread_jumps` (called at line 2859 BEFORE cse, after the first jump pass? No: 2859 is after the first jump dump at 2840). The dump .jump is written at ~2838, before thread_jumps. So the deletion is within the first jump pass.

Let me look at lines 1400-1430 and 1590-1610 (delete_insn calls).

Alternatively, use a simpler diagnostic: in vA, the .rtl dump (after expansion) has jump 368; in .jump it's gone. Let me grep the .jump dump for "368" (any insn number 368) — earlier grep showed only line 5958 (insn 368 in a DIFFERENT function). So gone.

Let me read jump.c around 1720-1740: "Detect a conditional jump going to the same place as an immediately following unconditional jump" — this_is_condjump. No.

Hmm, what about the `redirect_jump (insn, NULL_RTX)` at 656: it converts the jump to RETURN. Then the label 374's uses decrement to 0 → delete_insn(374) deletes the label. But wait, the label is targeted by many other jumps, so LABEL_NUSES > 1; decrementing gives >0. So label stays.

But the jump insn 368 became `(return)`. Then the RETURN jump_chain is built... Then the code at line 2056? Let me read 2050-2060.

Actually, maybe the RETURN insn 368 got deleted by the RETURN cross-jump with another RETURN in the function — cross_jump=0, so no.

Hmm, maybe it was deleted by the "delete insns following barriers" pass at the START of the *next* jump pass? No, the dump is after this pass.

Wait, maybe the .jump dump is written after jump_optimize but jump_optimize's `delete_insn` for the FUNCTION_END note cascades: delete_insn(insn) deletes the note; if the note is preceded by a barrier... delete_insn has special handling: "If the insn is a barrier, delete it too"? Let me read delete_insn (3383).
