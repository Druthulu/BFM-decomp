---
ts: 2026-10-22T01:12:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_HQnMp8TdKCgLMK9ybA0p
---
So in the pinned version:
- reg 3 (v1) is used for: the copy of the call result (insn 65: `(set (reg/v:SI 3 v1) ...)`) and the mask (insn 74: `(set (reg:SI 3 v1) (and:SI (reg/v:SI 3 v1) ...))`).
- The RESULT_DECL (73) is in reg 3 as well?? "73 in 3" — but then the return value would be in $3 ✗.

Hmm, "Register dispositions" lists each pseudo's assigned reg: 73 → 3. Hmm. But then how does the return value get to $2?

Ahh, I bet: the RESULT_DECL (r73) is in $3, and at the RETURN, the copy `move $2, $3`... but the target has no such copy. Hmm, unless the copy is elsewhere. Hmm, the target's ins 24 `move v1,v0` — that IS `move $3, $2`!!!

OH!!! I think I've got it backwards. Let me re-read the target:

```
20: li a0,1
21: addiu a1,sp,16
22: jal func_80149290     <- the call
23: move a2,s0            (delay slot)
24: move v1,v0            <- move $3, $2
25: beqz v1,+0x88
26: andi v1,v1,0x8000
```
Hmm, `move v1,v0` = move $3, $2 (dst=$3=v1, src=$2=v0).

And in the pinned version's RTL: insn 65 `(set (reg/v:SI 3 v1) ...)` — the copy's destination is reg 3 ✓. The source would be the call result (in $2) ✓. So the pinned version's `move v1,v0` at ins 24 is the copy of the CALL RESULT into the pseudo r80 (the ret var) ✓ (my original reading).

And the RESULT_DECL r73 → reg 3?? That conflicts with r80 → reg 3. Both in $3? They'd conflict if their live ranges overlap. Hmm, the RESULT_DECL's live range is short (live 4) — maybe it doesn't overlap r80's.

Hmm, but then the return value would be in $3 ✗✗. Unless the RESULT_DECL's copy `move $2, $3`... hmm.

Hmm, hold on: maybe the "73 in 3" is a mis-parse; the disposition line lists "73 in 3" meaning pseudo 73's class preference... Let me look at the RTL near the return to see how the result is returned. Let me look at the last ~30 lines of the .greg dump.
