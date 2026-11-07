---
ts: 2026-11-06T13:06:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mwUDcmgoxD3zWMRilkrP
---
Item 4: win.c scores 0 on all 141 includers → PARTIAL:launder (keepalive gone, launder kept).

Now record item 4 and item 3.

Item 4 results row:
dir func_80177EA4__func_80177EA4, file src/shared/ov/func_80177EA4.h, func func_80177EA4, kinds keepalive,launder, result PARTIAL:launder, best 0, tries (count: orig baseline, c1, n1-n4 (4), p1, q1, q2, q3? (q3 was written but not scored — no, I didn't score q3), q1, q2 → let me count: orig(0), c1, n1,n2,n3,n4, p1, q1, q2 = 9 tries + 141 includer runs of the final. Say 9), wall -, evidence.

Evidence ≤140: "keepalive asm dropped; do{}while(0) around the uVar1 store replaces it (C0535) so sched keeps sw v0,-4(t0) before the j; the launder stays (iv2c copy v1,a0); 0 on 141/141 includers".

Item 3: WALL, best 18, tries ~62, wall tag, evidence.

Let me count item 3 tries precisely: baseline(1) + c1(1) + h1,h3,h4,h5,h6(5) + i1-i4(4) + j1,j3(2) + k1,k2(2) + m01-m20(20) + p1,p2(2) + r1-r4(4) + s1-s3(3) + t1-t4(4) + u1-u4(4) + v1,v3,v4(3) + w1-w4(4) + x1-x3(3) = 62.

Wall tag for item 3: the lever-free best (18) is caused by the cse hard-reg forward (the $5 set folded into the $4 copy) → the copy-loop source then takes a1 instead of a2. Tag: `cse-hardreg-forward` (new, cse). Hmm, walls.txt has `cse-store-forward	cse1/combine	cse forwards a store into a reload and combine drops the dead store (G18x)` — that's a different mechanism (memory). Let me use a new tag `cse-hardreg-copy-forward`.

Hmm, but also the p2 (launder kept) residual is a sched1 order. The WALL's stated best (18) is lever-free. Evidence should mention: lever-free cse folds the pinned $5 `ba` set into the `dst = ba` copy (the launder's read of ba was what kept it), so the copy loop's src takes a1 not a2 and the 2-insn ba/dst pair is 1 short; keeping the launder volatile gets 159/159 ins, score 2 (one sched1 li/addiu order).

That's >140 chars. Trim.

Let me write both rows now. Careful with tabs.
