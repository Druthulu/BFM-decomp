---
ts: 2026-10-21T23:41:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG06r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_0kmkaFT9TTEuBIcHdAwj
---
Key: priority = floor_log2(n_refs) * n_refs * size / (death - birth). Shorter live range (death-birth small) → higher priority. So c1 with a SHORT live range gets HIGH priority (allocated first → best reg).

Wait, "We give shorter-lived quantities higher priority." So c1 (short live range) → high priority → gets the best reg ($2). The byte-12 pseudo (long range) → low priority.

So to make c1 get $3 instead of $2, I need c1 to have a LONGER live range (death-birth bigger) than the constants that should get $2, OR to reduce c1's n_refs.

Hmm, but also: the constants 0xA0 etc. are "constant registers" whose priority is DECREASED (the note above: "If this insn introduces a 'constant' register, decrease the priority of that register"). So a constant pseudo (set once from a constant) has lowered priority! That's why in the target the constants (0xA0, -0x78, 0x78) are in $2 (allocated later, after c1 which is a hard reg) and c1 (also a constant...) hmm.

Wait, but c1 = -0xA0 is also a constant register! Both c1 and 0xA0 are constant pseudos. In the target, c1 is hard-reg $3 (pinned), so it doesn't compete.

In my unpinned version, c1 and the constants are all constant pseudos, with lowered priority. c1 got $2 — because among the constant pseudos, c1 has the shortest live range (its set is right before its 2 uses) → highest priority → $2.

Target wants: the constants in $2 and c1 in $3, plus c1's `li` hoisted early (position 60) and the byte-12 pseudo in $6.

Hmm, but if c1 is in $3 and the constants in $2, then c1's live range (set → 2 uses) must conflict with the constants' ranges. And c1's live range is longer than each constant's individual range? Let's compute in the pre-alloc RTL.

Priority formula: pri = floor_log2(n_refs)*n_refs*size / (death-birth).

For c1: n_refs = 3 (set + 2 uses) → floor_log2(3)=1 → 1*3 = 3 → 3/(death-birth).
For 0xA0: n_refs = 3 → 3/(its range length).
For -0x78: n_refs=3.
For 0x78: n_refs=2 → floor_log2(2)=1 → 1*2=2 → 2/range.

If c1's range (death-birth) is larger than 0xA0's range, then 0xA0 has higher priority → 0xA0 gets $2 first, then c1 must get another reg ($3) — but only if they conflict.

So the plan: make c1's live range LONGER than 0xA0's, and make them conflict.

How to make c1's range longer: set c1 earlier (before the 0xA0 stores) — but then the conflict is there too. E.g.:

```
c1 = -0xA0;              // birth
*(s16*)(p+0x1C) = 0xA0;  // 0xA0 birth, use
*(s16*)(p+0x2C) = 0xA0;  // 0xA0 use
*(s16*)(p+0x16) = -0x78; 
*(s16*)(p+0x1E) = -0x78;
*(s16*)(p+0x14) = c1;    // c1 use
*(s16*)(p+0x24) = c1;    // c1 death
```
c1's range: from its birth to its last use → spans ~7 insns. 0xA0's range: 2 insns. So 0xA0 has higher priority → gets $2. Then c1 conflicts with 0xA0 (0xA0's range is inside c1's) → c1 needs a different reg → $3 if free.

But wait: c1 conflicts with 0xA0 → but is that enough? c1's range also covers -0x78's range → -0x78 conflicts with c1 too, and -0x78 also has high priority → -0x78 gets $2 (same as 0xA0, no conflict between them) → c1 gets $3.

And the byte-12 pseudo (long range, low priority) conflicts with $2 (constants), $3 (c1), $4 (a0), $5 (a1) → gets $6 (a2). That matches the target!

But: will the `li -160` be hoisted early (position 60)? In the target, c1 is a hard reg so the pre-RA scheduler can hoist it. In my version, c1 is a pseudo whose range conflicts with the byte-12 pseudo (whose range spans the whole byte group). The scheduler would then not hoist the li past the byte-12 load. Hmm, in the target, `li v1,-160` is at 2714, which is AFTER the byte-12 load at 271c? No: 2714 < 271c. The li is at 2714, before the 12th byte load at 271c. So the li is hoisted above the 12th byte load, and the 12th byte load's store is at 2758.

In the target, c1 ($3) vs byte-12 ($6): no conflict → hoisting allowed. In my pseudo version, c1 conflicts with byte-12 (pseudo) → the li can't be hoisted above the byte-12 load.

Hmm! Unless the conflict is only in local-alloc's view... The pre-RA scheduler (sched1) also uses live ranges. So c1's li would stay after the byte-12 load.

Where exactly is the byte-12 load in the unscheduled RTL? In the source, the 12th byte store is the last of the byte group, and the load is right before it. The scheduler moved the byte-12 load up to position 12 (right after the 11th load) — actually the load is at 271c which is after the 11th load at 2710. The 12th load's store is at 2758.

Hmm, why would the scheduler move the 12th load up but keep the store late? That looks like the scheduler moving the load to an earlier slot (it has no dependencies) — and the store late? That's odd; sched1 usually keeps a load near its use.

Wait, maybe I mis-assume. Maybe the RTL order (pre-sched) is: all 12 loads and stores interleaved... Let me think about the source order of the byte stores: 0x10, 0x18, 0x20, 0x28, 0x11, 0x19, 0x21, 0x29, 0x12, 0x1A, 0x22, 0x2A. So the 12th is 0x2A. The compiler generated: load;store;load;store;...;load(11th at 2710);store(11th at 2718);load(12th at 271c);... then store(12th) at 2758 — way later, after the const stores. So sched1 moved the 12th load earlier and the store later?? That's weird. More likely: the 12th load+store pair was split by the scheduler, with the load scheduled early (before the constant block) and the store late.

Hmm, actually maybe: the source order of the 12th store (p+0x2A) comes before the 0xF/0x13 byte stores and the s16 block. The scheduler moved the const block (0xF, 0x13, and the s16 stores) BEFORE the 12th byte store. And the 12th byte LOAD stayed at its position (right after the 11th store). So the load/store pair got separated by the scheduler.

Why? Because in the RTL the order was: ..., lw v0 (12th), sb v0,42(s0), li v0,8, sb v0,15, li 58, sb 19, li 160, sh 28, sh 44, ... and the scheduler moved things around: the sb 42 was moved after the const block? The scheduler (sched1) tries to reduce register pressure and fill slots. Anyway, both the target and my candidate do this, so the behavior is the same modulo the c1 difference.

Key question: in the target, is the `li v1,-160` position a consequence of the pin (hard reg) or of the source order? In the source, c1 = -0xA0 is set right before its two stores. But the target's li is at 2714, very early — before the const block. So the scheduler hoisted the constant load from its source position (just before the sh 20/sh 36 stores) to an early slot. Why would it hoist a constant load upward? sched1 does "hoist" independent insns? Hmm, in the target the li v1,-160 at 2714 is in the middle of the byte group, right after the 11th load at 2710 and before the 11th store at 2718. That's a classic "the constant got scheduled into a hole" — sched1's ready list picks the highest priority insn; the constant's pseudo (hard reg $3) had no dependency conflict, so it got scheduled early. Whereas in my version, c1's pseudo conflicts with the byte-12 pseudo (live range overlap) so the scheduler kept c1's li after the byte-12 load.

Hmm, but wait: does the conflict really exist? The byte-12 pseudo's live range: birth at its load (271c), death at its store (2758) — spanning the const block. c1's range: birth at its set, death at its last use. If c1's set is early (in the byte group area) and its uses are in the const block, they overlap → conflict.

In the target, c1 is $3 and byte-12 is $6 → no conflict (different hard regs) → the scheduler can hoist the li.

So the puzzle: I need c1 in $3 AND the scheduler to hoist the li early. In the pseudo world, the scheduler's conflict analysis happens before allocation, so c1 and byte-12 conflict regardless of the final allocation. Therefore the li's position would differ from the target...

Unless the conflict is broken by making c1's live range NOT overlap byte-12's. byte-12's range: from its load to its store (2758) — nearly the whole const block. c1's set must be after byte-12's load (271c) and c1's uses before its store (2758)? c1's uses are the sh 20/36 stores, which in the target are at 274c/2750 — inside byte-12's range. So c1's range always overlaps byte-12's range in the target.

Hmm, but hold on: in the pre-alloc RTL, where are the stores? The order in the RTL before scheduling is the source order. Let me think about the pre-sched RTL:
- byte group: load1,store1,...,load11,store11,load12,store12
- then 0xF: li 8, sb 15; 0x13: li 58, sb 19
- then s16: li 160, sh 28, sh 44, li -120, sh 22, sh 30, li -160 (c1 set), sh 20, sh 36, li 120, sh 38, sh 46.

Hmm wait, the source has 0x2E = 46 store last: `*(s16 *)(p + 0x2E) = 0x78;` yes.

byte-12's range in the pre-sched RTL: from load12 to store12, which is adjacent! (load12 immediately followed by store12). So in the pre-sched RTL, byte-12's live range is SHORT (2 insns) and does NOT overlap c1's range (which is later in the const block)!

But the pre-RA scheduler then moved the load12 up and store12 down, creating the long range. The scheduler's conflict analysis (which uses live ranges computed by flow analysis) — the scheduler computes its own live ranges via `compute_live_ranges` in sched1? In gcc 2.7, sched1 uses `flow_analysis` / `sched_luid`? Hmm.

Wait, but actually — if the scheduler moved load12 up to 271c (i.e., before the const block) and store12 down to 2758, then it created an overlap with c1's range. But the scheduler works on a dependency DAG, not live ranges; it decides based on dependencies and register pressure estimates.

OK, this is getting really deep. Let me just try things empirically. The key lever I identified: move c1's assignment EARLIER (before the 0xA0 stores) so its live range is long, making 0xA0/-0x78 (short ranges) win $2 and c1 get $3.

Wait, but the previous attempt (k01, m01, r01, u01...) moved c1's assignment EARLIER (to right after the byte group, i.e. `c1 = -0xA0;` at line 12 = after the 12 byte stores) and got 11. Hmm. Let me check the exact position of c1 in those: e.g. m01: `c1 = -0xA0;` inserted at line 12 (after the byte stores) and removed from its original spot. So c1's range spans from after the byte group to the const block — long. Result 11.

So that didn't crack it. Hmm, but 11 = the same score as the plain unpinned. The score is 11 with "mine 91 ins, target 90" — one extra insn and register differences. Let me look at what the diff was for m01 to see whether c1 got $3.

Let me run the diff for m01 and u01.

Actually, let me be smarter: write a script that, for a candidate, dumps the candidate's disassembly and compares register usage of the `li -160`. Even better: use the "--keep" output and grep the li.

Plan: create a helper script `tryc.py <itemdir> <candidate>` that compiles with --keep, disassembles, prints the score and the lines with "-160" plus the register of the last byte store, then cleans up the scratch.

But --keep leaves scratch in .run/P36/engine/score/... (shared area, not my shard). The constraint says --keep scratch is removed after use. I can rm -rf that dir afterwards. But "write only under .run/P40/T11/G06/" — the --keep scratch is in .run/P36/engine/score/... which the tool creates itself; I must remove it after use. OK.

Let me write the helper.
