---
ts: 2026-11-06T08:51:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_q5wAiyjHL223EYTQqd4T
---
Suggestions are computed but `find_free_reg` in the main loop is called with just_try_suggested=0 both times (lines 1473, 1527 show `0, 0`), so suggestions don't influence the choice in this version. So allocation is purely priority + ascending free reg.

Therefore, to give the a0 copy a2 and t3 a3, t3 must be allocated AFTER the a0 copy, i.e. t3's priority < 3703 (live ≥ 6) — or t3 allocated before but a2 taken... 

Hmm wait, there's another possibility: the a0 copy is allocated BEFORE t3 if t3's priority is lower. t3 live must be ≥6.

But also the a0 copy must not be blocked from a2 by some reg living at a2 (r79 in w2, a pointer, 2/7). In w2, r79 got a0.

So we need t3's live ≥ 6. The only real-C way: t3's death insn is later in the pre-local-alloc RTL while the final code still stores at position 21. Since sched1 runs before local-alloc and its order determines liveness, and the final code (after sched2/reorg) has the store at 21, maybe sched2 CAN move the store earlier if the source arrangement is right. In d3, sched1 put the store after h[1] (position 34) and sched2 kept it. Hmm.

What if the source puts the t3 store after the fifth load (c1): sched1 put it after the fifth load (position 35) and it stayed. What if the store is placed between the fifth load and its store? c1: `t4 = load; sp10[3] = t3; sp10[4] = t4;` — sched1 put sw t3 at 35.

Alternatively, place the store after h[2] but before the call (d4)? The live range would be even longer; sched1 might keep it late.

I wonder if sched2 ever moves it. Let me test whether a *store* can be hoisted by sched2: In the target, the stores are all after the loads, which sched1 does. 

Hmm, let me look at the problem from the target's liveness again: maybe the target's t3 has a *different* live length because its load is scheduled differently in sched1's order (before the other loads) and sched2 reorders the loads. Does sched2 reorder loads? sched2 runs after reload; it can reorder within blocks. If sched1's order were [load t3 first, ...] and sched2 reordered to t0,t1,t2,t3, the final code would show target order while liveness (computed at sched1 output) has t3 live from earlier.

Does the pipeline have sched2? Yes (toplev.c). So maybe the source places t3's load FIRST, and sched2 reorders.

But wait: if t3's load were first, sched1 might keep it first and sched2 might not reorder. Uncertain.

Let me try: reorder the source loads: t3 first, then t0,t1,t2, and the store early. Score it.

Also try: t3 loaded after t4 (source order t0,t1,t2,t4,t3) — then t3's load at the end, live from 56 to 59? That shortens, wrong direction.

Let me try t3-first.

Actually, better: let me test the hypothesis by looking at what the *target's* live length must be: For the a0-copy (3703) to beat t3, t3's pri must be ≤ 3703, so live ≥ 6 (pri 3333). If t3's load is one position earlier in sched1's order than in the final code, live = 6. So if the source has t3's load at position 3 (before t2) and sched2 moves it to position 4 (target), we'd get live 6.

But sched1 typically orders loads by dependency/priority; sched2 might too. Risky.

Alternatively: t3's store one position LATER in sched1's order, then sched2 moves it up one. d3/c1 moved it much later (after h[1]/after t4 load).

What if the source order is: t0,t1,t2 loads; t3 load; t0,t1,t2 stores; t4 load; t3 store; t4 store — i.e., the t3 store just after the t4 load (c1)? That's c1: sched1 emitted the store after the t4 load (live 6!). Let me check c1's lreg to see t3's live length. If live 6, then pri 3333 and the a0 copy should get a2... but c1's final code had t3=a2! So live wasn't 6 or the allocation didn't change. Let me dump c1 and check.

Actually c1's diff: mine[24:25] lw v0 (t4), then sw a2,28(sp) at 35. In c1's final code, t3 = a2 (still). So local-alloc gave t3 a2 → t3 was still allocated before the a0 copy → live still 5? But the store is after the load in the final code... The live length at local-alloc time depends on sched1's order, which may differ from the final (sched2) order. Let me dump c1 and read the lreg register summary. It's cheap.
