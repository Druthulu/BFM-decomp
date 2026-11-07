---
ts: 2026-11-06T02:15:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PSv4b6mSqMONjAOEBy8e
---
PATTERN code = 41 = SET; SET_SRC = pc (code 51). So PATTERN is `(set (pc) ...)`? Wait: SET_SRC (fld[1]) = pc_rtx. That means the SET is `(set (pc) X)` where X is SET_DEST? No: in RTL, `(set DEST SRC)`: fld[0]=DEST, fld[1]=SRC. I read fld[1] = 0x82d998c = pc. So SET_SRC = pc — that means the pattern is `(set (something) (pc))`? That's inverted.

Hmm, for a jump, PATTERN is `(set (pc) (label_ref ...))`: DEST=pc, SRC=label_ref. I read fld[0] at offset 8 = 0x89601ec (SET_DEST) and fld[1] at offset 4 = 0x82d998c (pc). So DEST=0x89601ec, SRC=pc. That's `(set X pc)` — that's a jump if X is... no.

Wait, I think I mixed the offsets: in the SET rtx, fld[0] is at offset 4 (not 8), fld[1] at offset 8. I read `*(void**)(PATTERN+4)` = SET_DEST? No: XEXP(RTX,N) = fld[N]; fld[0] is at offset 4 (since the header is 4 bytes). So SET_DEST = *(void**)(PATTERN+4) = 0x82d998c, SET_SRC = *(void**)(PATTERN+8) = 0x89601ec.

So SET_DEST = 0x82d998c (pc, code 51) ✓, SET_SRC = 0x89601ec (the label_ref). Great: PATTERN = (set (pc) (label_ref ...)). So it IS a simple jump. condjump_p should return 0!

But the breakpoint at 0x80f31cb is hit, and the code path calls condjump_p; if it returned 0, we'd jump to 0x80f3207 and NOT call delete_jump. Yet the delete happened. Unless the breakpoint at 0x80f31cb is hit for this insn and condjump_p returns 0, and then the deletion we saw came from a DIFFERENT call site... but the backtrace showed 0x80f31f5 which is right after delete_jump at this site.

Hmm, wait: gdb sets the breakpoint at 0x80f31cb which is the *call* instruction. If condjump_p returns 0, execution goes to 0x80f3207. Our breakpoint hit proves the call happened. But the delete_jump call at 0x80f31f0 is only reached if the test passes. So condjump_p returned nonzero for this insn!

But PATTERN is (set (pc) (label_ref)). Let me look at condjump_p's source in this gcc version.
