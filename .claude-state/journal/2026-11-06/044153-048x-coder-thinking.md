---
ts: 2026-11-06T11:41:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_m190oNAiRKVBjR2beTKV
---
§3 is very relevant: "an asm ALWAYS has priority 1... Do not try to raise an instruction's priority by feeding a load through an asm."

Also §370: "a ready load always beats an equal-priority ALU leaf". 

Now in our target, the barrier asm splits the block effectively via anti-deps. To get the target order lever-free we'd need the adds to be lower priority... The adds have priority 5 in v0 (they're deep in the dependency chain). Hmm, priority 5 means the add feeds a chain of 5 insns. In target's EBB (barrier split), the adds' priority... 

Let me look at the target's sched dump! I have dumps for v0 (my body). I could also dump orig.c (which scores 0) and compare the sched dumps — the barrier's effect. But what would I learn? The barrier asm splits dependencies; in orig, the block includes the asm insns.

I think this is a genuinely hard wall (it was marked NEEDED DIFFERS after a rung-B search). The shard is "singleton crack shard" — presumably each item was a lever-heavy singleton that might crack. Time budget: 20-30 min per item. We're at ~15-20 min. Let me try 2-3 more quick real-C moves, then record the wall.

Quick ideas:
(1) v4: replace `vx = x; ... vy = y;` with copies made via temporaries assigned at declaration (`s32 vx = x;`)? Declaration init at decl is a listed real C move. Might change LUID (birth order): `s32 vx = x, vy = y;` at the top would move the copies early — target has move a0,s1 at 3850 (after p[7] store). Probably worse.

(2) v5: use `s16` casts: the stores `*(s16 *)(p + 8) = vx;` etc. are already there.

(3) Statement order: swap the two vx/vy store statements? Target order: sh vx(8), sh vy(0xA), later sh x(0x10), sh vy(0x12), sh vx(0x18), sh y(0x1A), sh x(0x20), sh y(0x22). Source order matches exactly.

(4) Use pointer reuse: `u8 *q = p + 8;` and write q[3]=8, q[7]=0x38, etc., with p advanced later? The target's `addiu v0,v0,8` happens at 3834 (before the first-group stores) — same as mine. Then stores via v0.

(5) Change the tag2 load to happen after the c-stores but before... it already does (source).

Actually here's a thought: in v0, the adds were hoisted because of their priority 5 (they feed stores which feed the tag store chain). If we reorder so the adds come from a lower-priority chain... 

What if we write the second group with explicit temps to reduce the dependency depth? E.g.:
```
s16 xs = x + w_;
s16 ys = y + h_;
```
Hmm.

Alternatively, maybe the intended crack is to use `u8`/`s16` width moves: e.g. store `(s16)x` casts.

Let me try a quick experiment: make the adds read the params via locals declared early? Actually, a cleaner idea: since priority comes from the dependency chain length, and the target's barrier resets it, we could shorten the chain by storing x and y as separate temp variables *after* the stores:

v4:
```
p[0x10] = ... etc
```
No.

Honestly, a more promising avenue: what does the target's ordering look like in terms of LUIDs? Target's order = source order. sched1 moves insns only when priority differs. So in the target, all the insns in that region have EQUAL priority (1), except the barrier chains. Since the barrier asm has priority 1 (C0414 §3) and dependencies through it are anti-deps with cost 0 → priority 1. So the whole block's priorities are 1 except the load chains.

For the target's EBB2: lw w_ (1), lw tag (1), addu x (priority = 1 + cost(lw) - 1 = 2?). Hmm, if the load's result_ready_cost is 2, the addu gets 2 and would jump ahead. But in the target, the addu is scheduled after the two loads and after sh 16, sh 18, sh 24... Actually target order: lw t1(w_), lw a2(tag), addu s1, sh s1,16, sh v1,18, sh a0,24, lw t1(h_), and, addu s2, ...

Hmm, the addu IS right after the loads, before the stores of its own result? No: addu at 389c then sh s1,16 at 38a0. And there are 3 stores between addu and lw h_. But those stores include the sh 18 (vy) and sh 24 (vx), which don't depend on addu. So sched1 did reorder: it put the addu before sh 18/sh 24 (which are earlier in source). So yes the load boost is visible: addu priority 2 > stores 1.

But it did NOT put addu before the vx/vy stores (sh 8, sh 10) — those are before in source and have equal priority to the lw. Hmm, so the addu comes after lw w_ (necessary), and the ready list at that point: sh 18, sh 24, addu (2). It should pick addu first — yes it did (addu at 389c, sh 18 at 38a4). 

So in the target, everything is consistent with priority: the stores with priority 1 in source order, and the addu jumping ahead of equal-priority stores once its load is ready.

In v0, why did sh 8(vx) come before sb p[3]=8? Both priority 1? Hmm, v0's dump: the ready list shows priorities 5 for stores (112,118...) and 2 for some. Because in the merged EBB, stores depend on... The byte stores' priority 5 means they depend on a chain of 5 (p from the call? p = func(...) result, then p+=8, then...). Hmm, the priority of a store = priority of the address computation chain.

Wait: in v0's merged block, everything after the call is in one block. Priority of `sb v1,3(v0)` = priority of v0 (the p pseudo) + ... The call result p is defined by a call insn (priority 1?) then addiu p,p,8 (priority 2) then stores depend on it (priority 3?). But the dump shows stores at priority 5.

The adds (152) priority 5 too. So all equal priority 5, and the tie-break is LUID — should be source order! But mine's output has sh s1,8 (vx) before sb v1,3 (p[3]=8), which is NOT source order. Unless register allocation/sched2 (not sched1) did that. Remember there are TWO schedulers: sched1 (pre-alloc) and sched2 (post-alloc). The dt.sh diff compares final code, which is sched2's output. My dump analysis of sched1 is only half the story.

In sched2, the regs are hard, and anti-deps matter. Hmm.

Let me look at the sched2 dump for our function instead — that's the final ordering (then dbr fills). v0.i.sched2.

Actually, the diff shows exactly the final output. Let me look at the sched2 dump to see the priorities and the hazard ("launching X before Y with stalls" lines) for the region.

But how do I use that? The fix must be in C source.

Given the complexity and time, let me consider the likely expected outcome: this item is a WALL. The task says budget 20-30 min per item; walls need ≥20 min and ≥30 scored tries. Hmm — "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". Ugh: 30 scored tries per item! That's a lot of dt.sh calls. Each is ~5-10 s. 30 tries ≈ 3-5 min of compute plus my thinking. OK.

So I need to generate 30+ candidate bodies per item and score them. This suggests scripting a search over real-C moves. There might be a helper: delever_search --run does a guided search but that's for lever removal (it writes the tree). The brief's approach: "delever_search.py --try <TU> <fn> <file> --body (score 0 = MATCH; compares with the function in build/); R3.40-013 helpers."

30 tries — I should write a generator script that emits variants and scores them via sc.sh (one line per candidate). bin/sc.sh <itemdir> <files…> — "one line per candidate". Let me look at sc.sh.
