---
ts: 2026-11-06T12:08:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jdvrhMQMJXVKW9JgK9lD
---
All 38. Total tries: 25 + 7 = 32. Good, ≥30.

Best lever-free = 38 (w3). Item 4 = WALL.

Hmm, but wait: is there a PARTIAL? PARTIAL requires score 0 keeping only some kinds. w2 (barrier removed, launder kept) = 8; w1 (launder replaced, barrier kept) = 30. Neither is 0. So no PARTIAL. WALL with best 38.

Wall tag: the launder is `cse-const-addr` (cse folds/substitutes a constant/absolute address the target keeps base-relative) — that fits: without the launder, cse rematerializes the constant address per use (+3 insns). Yes! walls.txt has `cse-const-addr`: "cse folds or substitutes a constant/absolute address the target keeps base-relative (T10 S09, S11, S16)". Perfect.

But the barrier part: the load hoist across the store. That's a sched issue. Hmm, one wall tag only. I'll use `cse-const-addr` and mention the barrier in the evidence.

Hmm, actually the barrier removal alone gives 8 — the load/sched hoist. The launder removal alone gives 30 — the const-addr rematerialization. Both are blockers. The tag should reflect the primary. Let me use `cse-const-addr` and mention both.

Evidence ≤140: "launder: cse rematerialises &D_8011F7F0 per use (lui+lhu x4, +3 ins); barrier: sched1 hoists the D_8018DB2C[idx] load above the D_8011F83A store (no alias seen)"

That's ~150. Trim: "launder: cse rematerialises &D_8011F7F0 per use (+3 ins); barrier: sched1 hoists the D_8018DB2C[idx] load above the D_8011F83A store (no alias seen)" ~140.

Let me set win.c = w3 (best lever-free, 38) and write the row.

Wait, let me double check w3 = both levers removed, score 38, and has no asm except the pins. Let me verify.
