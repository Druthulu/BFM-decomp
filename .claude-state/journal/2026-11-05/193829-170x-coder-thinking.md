---
ts: 2026-11-06T02:38:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Z0GVQMFuL79xG7EMyVDe
---
30 scored tries on item 2 (b1,b2,b3,b4,b5(compile-error—not scored),b7,b8,b9,b10 = 8 + c1-c6 = 6 + d1-d4 = 4 + e5-e8 = 4 + f1,f2,f3,f5,f6,f7 = 6 → 28 scored + nopin + orig control = 29; plus b6? I created b6 but didn't score it. Let me score b6 to reach 30, and maybe a couple more.

Actually the WALL requirement: ≥20 min and ≥30 scored tries. I have 28 scored candidates + nopin (a scored try) = 29. Let me add b6 and one more.

Actually, let me make one more serious attempt with a different idea before the WALL: the target's nop might come from the addiu being un-stealable because v0 is live at the epilogue. What if the function's switch has a `default` case that uses v0? No default in target.

Hmm, what if the epilogue's live set includes v0 because the *call* at the end of the fall-through (func_8012C658 returns v0) and the function... no.

Let me just do the WALL: best = 8 (74 ins), wall tag `dbr-delay-fill` (existing tag: "reorg steals ... into the branch slot (target nop)").

Let me write the results row, notes, moves line, win.c = nopin.c (the best lever-free body, score 8).

Evidence: "dbr: reorg fills bnez unk98 delay slot with the fall-through `addiu v0,a0,1` (v0 dead at the epilogue); do-while/goto/label/order variants all 74 ins."

Let me finalize item 2.
