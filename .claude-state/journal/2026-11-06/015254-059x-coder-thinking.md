---
ts: 2026-11-06T08:52:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1IxvbhBnBiwVLQuPHUEB
---
In c1: r72 in 7 (a3), r77 in 6 (a2), r78 in 2 (v0). So t3 still got a2 despite pri 3333 < 3703. Why? Because allocation order: r84 (pri? 6/9 → 2*6/9 = 13333?) → v0; r78 (2/3 → 2*2/3=13333?) hmm. Let me compute: r78 2 refs, live 3 → 1*2/3 = 6666. r75/r76 4000, r77 3333, r72 3703, r74 2000.

Order: r84 (13333) → v0; r78 (6666) → v1? but the disposition says r78 in 2 (v0)! So r78 (t4) got v0 (v0 free because r84 dies at its birth). Then r75 (4000) → a0, r76 (4000) → a1, r72 (3703) → a2 expected... but r72 got a3 and r77 got a2.

Unless the allocation order sorts differently: qsort with qty_compare_1 descending pri, ties by qty number. r72 3703 vs r77 3333: r72 first. So r72 should take a2. But it took a3! So something else took a2 before r72: r77? No, 3333 < 3703.

Hmm, maybe another pseudo with pri between: r90-r98 (HI pseudos, 2/6 → 3333, 2/4 → 5000). r91/r94/r97 are 2/4 = 5000! They're the HI regs of the h computation. Those get allocated: r91 (5000) → after r78... v0 taken by r84, v1 taken by r78? Wait r78 got v0 per dispositions. Hmm, if r78 got v0 and r84 got v0 too (same reg, disjoint), then v1 is free for r91 (5000) → v1? Disposition says r91 in 3 (v1). Yes.

So order: r84 (13333) v0, r78 (6666) v0, r91 (5000) v1, r75 (4000) a0, r76 (4000) a1, r72 (3703) → a2?? but got a3.

Unless r72's pri isn't 3703 in the allocation: qty_size! r72 is a pointer... size 1. Hmm.

Wait, maybe r72 is NOT a qty (local-alloc handles it separately) — maybe the param copy is a "constant" or has REG_EQUIV? No.

Let me reconsider: maybe r72's qty includes r79? No, r79 doesn't exist in c1.

Hmm, dispositions: 72 in 7. Maybe the dump's order lines don't reflect the final assignment order due to qty merging: qtys can combine multiple pseudos (reg_qty). r72's qty might be merged with another pseudo (e.g., a later use creates a copy that gets tied). 

I'm running out of budget for this item. Let me consider: the keepalive kind is "keepalive" — maybe the shard expects PARTIAL when a lever-free body keeps only that kind? No: PARTIAL:<kinds still kept> = win.c scores 0 keeping only those levers. So PARTIAL:keepalive would be a body that still has a keepalive asm (trivial: orig itself). That's allowed as a fallback if we can't crack it, but a WALL is better when we have a lever-free body with a best score.

Given time, let me try a couple more targeted ideas and then settle.

Idea: since allocation order weirdness, maybe t3's live length needs to be much bigger (like the asm's 18). With live 18, pri 1666, r72 (3703) definitely wins. In d3, t3's store after h[1] gave the right allocation (a3/a2) but the store position was wrong (34 vs 21). In c1 (store after t4 load), t3's live 6 and allocation still a2. So local-alloc isn't purely priority here. In d3 the store was at 34 and t3 got a3 — consistent with live 18-ish.

Hmm, why did c1 fail then? Because with live 6, pri 3333 vs r72 3703 — should still work. Unless the *qty* ordering merges... Let me check d3's lreg: t3 live and r72 pri. Actually d3 worked, so let's see if there's a variant with a store position that sched1/sched2 emit at 21 while keeping live long.

What if the t3 store is placed after h[2] (d4)? Live even longer; store position likely later (after h[2]) — worse.

What if we add a *second* store of t3 to sp10[3] later? That would add an instruction.

What if the h[1] computation itself uses t3? E.g., swap: use t3 as the temp for the second lhu? Hmm, h[1] = h[1] + a0->unkA uses r94 (a HI pseudo), not t3.

What if the source stores t3 into sp10[3] and then the *call* passes sp10... no.

Let me try: place the t3 store between h[0] and h[1] (d2: score 4, 46 insns). d2 lost an insn. d3 (after h[1]) = 47 insns score 4 but store at 34.

Target store at 21. What if the store is placed after the fifth load AND after h[0]? Hmm.

Alternatively: maybe the target's t3 liveness comes from a *second use in the same statement*: `sp10[3] = t3;` then later `t3` used in `h[2]`? Not in target.

Let me look at this from the scheduler's perspective: in d3, sched1 ordered the store after h[1]. Could sched1 hoist it back to 21 if the source order were different? The stores to sp10[0..2] happen before; the store to sp10[3] has anti-deps with the lhu loads of sp10[0..2]. sched1's ordering heuristic may place it by priority. The store's priority depends on the source order (LUID).

What if the t3 store is placed *between* the t4 load and its store, i.e. source: ... sp10[2]=t2; t4=load; sp10[3]=t3; sp10[4]=t4; h...? c1 was: sp10[0..2]; t4 load; sp10[3]=t3; sp10[4]=t4 → final store at 35. 

What if: sp10[0..2]; t4 load; sp10[4]=t4; sp10[3]=t3; h... — the store after the t4 store. Probably later.

Hmm, what if the fifth load is moved before the t3 store in source but t3's store stays at 21 by sched1? That's c1, no.

Let me try another lever: make t3's load occur earlier in the source (before t2). Then in sched1's order, t3's load might be at position 3 and its store at 21 → live 6. If sched1 doesn't reorder loads, the final code would have t3's load at position 3 — wrong. But maybe sched1 reorders.

Try: source loads t0,t1,t3,t2 (swap t2/t3 loads) with stores in order 0,1,2,3. Let me test a few permutations.
