---
ts: 2026-11-06T04:31:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9uQp2vTZqHzU9vVKPCmp
---
30 tries reached (26+4=30). All at 14. The p reload hoist is the wall: sched1 fills the obj->1C load-delay slot with the p reload in mine; the target has a nop.

Let me make one final attempt with a promising idea before recording: make the p reload NOT ready at the obj->1C load's delay slot by giving it a dependency on the multiply chain via a REAL expression. The only real dependency I can create without changing values: none.

Alternatively, reorder the RTL so the obj->1C load is not immediately followed by the p load — e.g., make the first thing after the obj->1C load a dependent insn (sll), which it is. The p load fills the delay slot because the sll isn't ready (needs the load). To make the slot a nop, no independent insn should be ready — i.e., the p load must not be ready. Its address a0 is ready. Unless the p load's address depends on the obj->1C load's result... fake.

What if we make the p load use a pointer that is computed from `v` in a way that doesn't change the address but isn't folded? E.g., `p = (Unk*)((s32)((Unk*)a0)->unk20 + (v & 0));` — folds. `p = (Unk*)((s32)((Unk*)a0)->unk20 | (v & 0));` folds.

What about `p = ((Unk*)((s32)a0 + 0x20))[...]`? no.

I'll record the WALL. Best lever-free score = 14 (w4 family). The wall tag: a new `sched1-load-delay-fill`? The walls list has `sched1-load-delay-fill` (G18 func_80180610: sched1 fills a load-delay slot with an independent store group the target leaves as nop). This is the same mechanism: sched1 fills the obj->1C load-delay slot with the independent p reload, target leaves a nop. So use the existing tag `sched1-load-delay-fill`.

Wait, but the target DOES have a nop at 4934 (the delay slot). Mine fills it with the p load. Yes, exactly `sched1-load-delay-fill`.

Let me double check: target 4930 lw v1,28(s2); 4934 nop; 4938 sll. Mine 4930 lw v1,28(s2); 4934 lw a0,32(s1); 4938 sll. Yes, sched1 fills the load-delay slot that the target leaves as nop.

So result = WALL, best = 14, wall = sched1-load-delay-fill, evidence: "sched1 fills the obj->1C lw delay slot with the p reload (target nop); the reload then overlaps v1 so p gets a0 not v1; best w4 (do-while on the ==0 p load) 14, 107 ins".

Result row: dir, file, func, kinds=barrier, result=WALL, best=14, tries=30, wall=sched1-load-delay-fill, evidence.

Let me count tries precisely: nopin(1), w1,w2,w3,w4(5), w5,w6,w7(8), w8,w9(10), d1,d2,d3,d4(14), r1,r2,r3(17), u1(18), x1(19), y1..y7(26), y8..y11(30). Yes 30.

Best = 14. The best candidate is w4.c (or w5..y11 all 14). I'll copy w4.c to win.c? The row says WALL best = lowest score of a lever-free body. The win.c should be the best lever-free body. For a WALL, "each MATCH/PARTIAL has its win.c scoring 0" — WALL doesn't require win.c, but I'll keep win.c = w4.c (best, 14) for reference.

Also clean up the dumps dir (delete) per the disk rule.

Let me record: results append, notes, moves line.

Time check: item 4 start ~21:22, now ~22:40? That's ~78 min — way over. I should wrap up. Let me check the date and finish.

Wait — I should also consider: is 14 really the best? All the w4-family are 14. Yes.

Let me append the result row (one action), then notes, moves, and delete dumps.
