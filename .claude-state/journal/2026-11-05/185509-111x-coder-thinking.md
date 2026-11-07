---
ts: 2026-11-06T01:55:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_C8uljvHG31eEJEj3ItHk
---
gdb exists. But cc1 may not have symbols. A breakpoint on delete_insn needs the symbol; the binary might be stripped. Let me check `nm`.

Actually, let me think once more. Maybe the jump-to-next deletion for a simplejump is done by `delete_jump` in `jump.c` line 664 but with `condjump_p` — wait, for a simple jump to the next insn, after `redirect_jump(insn, NULL_RTX)` at 656 (which requires next_active_insn(label)==0)... in vA2, the return label 374's next_active_insn: NEXT_INSN(374) = 0 → returns 0 → redirect fires! It converts the jump to RETURN. Then `reallabelprev == insn` and `condjump_p(insn)` — after conversion, PATTERN is RETURN; condjump_p(RETURN) = 0. So no delete.

Then JUMP_LABEL(insn)=0 and LABEL_NUSES(374) decremented by 1. Other jumps still reference 374.

Then the RETURN insn exists. Where does it go? The dump doesn't show it. Hmm, unless the RETURN insn was later deleted by the "Delete all labels already not referenced" loop? No.

WAIT. Maybe the dump doesn't print it because... print_rtl prints jump_insn with (return). grep "(return)" found 0 in the whole file. So no RETURN.

Hmm, is it possible that redirect_jump(insn, NULL_RTX) FAILED (validate_change failed) and returned 0? Then the jump remains. But it's gone.

Unless the jump was deleted by `delete_jump` at line 1733 etc. after being converted... no.

Let me try gdb. First check nm for delete_insn symbol.
