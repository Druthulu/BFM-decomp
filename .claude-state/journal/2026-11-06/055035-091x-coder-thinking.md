---
ts: 2026-11-06T12:50:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_w6rw8RhjjjdB5GLg1919
---
Same residual. So the two remaining problems are:
(A) the two early returns (`return 0` → move v0,zero; target nop) — 3 diffs.
(B) the idx/unk10A path: `lh a0,112(s1)` (i70a in a0) vs target `lh v0,112(s1)`, and the shift/reload arrangement — 5 diffs.

For (B): the target reloads unk70 into v0 (i70a), and uses a0 later for the D_80183A40 load. Mine keeps i70a in a0 and uses v0 for idx.

Wait: mine at 1c5c: `lh a0,112(s1)` = i70a in a0; target: `lh v0,112(s1)` — i70a in v0! Then the lbu: target `lbu v0,0(at)` overwrites v0 (i70a dead after), so target has i70a in v0 and idx in v0 too.

Mine has i70a in a0, idx in v0.

So the difference is i70a's register: target v0, mine a0. That's the `i70a = unk70;` pseudo. In the target, `lh v0,112(s1)` then `lbu v0,0(at)` (same reg, i70a dies).

Hmm, and later the target reloads unk70 into a0 at 1cb0 (`addu at,at,a0; lbu a0,0(at)` = D_80183A40[i70b]).

So the target's i70a is v0; mine is a0.

Interesting: this is the allocno priority again (the original comment's §137). So the original's priority lever (idx +1 ref → pri 16000) affected which pseudo takes v0.

Given time (05:51, 21 min), and that the remaining 9 points are 2 separate allocation/scheduling issues with the asm being the cause, I'll call it a WALL... but wait, the best is 9, not 44. Let me update: best = 9 (w4/w7).

Hmm, a score of 9 with 261/261 ins is really close. Let me try a couple more moves aimed at (B) since it's the bulk:

(B) is about i70a's register (a0 vs v0) and the reload. Since idx is now s32 (w7), maybe combining w7 with other moves changes priorities. Let me try:
- w8: w7 + `i70a` declared after `i70b`? (decl order)
- w9: w7 + the D_801F32D0 store moved (w6's move) → that gave 42 on w4; try on w7.
- w10: w7 + a do-while around the i70a block.

Also for (A): the early returns. If I could make the early returns return a pseudo in v0 with no insn... 

Hmm, wait! Now that the arms' ret is in v0 (the do-while trick worked!), what if the early returns `return ret;` would work — because ret is v0 now? The problem before was that the early `return ret` made ret live from entry (crossing calls) → s0. But now with the do-while around the arm assignments, ret got v0... Let me test: w8 = w7 with the early returns back to `return ret;`. If ret is v0 (thanks to the arm do-whiles), the early returns become `j; nop` and `beqz a0, epilogue` — exactly the target!

That's a great idea. Let me test.
