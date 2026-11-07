---
ts: 2026-11-06T04:58:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VGXeOMEMkPiNXCCm3We1
---
Big progress! q1 fixed the load order but now:
1. s0/s1 register roles swapped (base is in s1 instead of s0, a1 in s0 instead of s1). This is a global-alloc difference.
2. In the third block, the load of EA6 is still hoisted (mine[43:45] v1 vs target v0) — that's the `if (D_80078EA6 < 0x80)` load, which is BEFORE the store (correct: the load precedes the store in the source). Wait, target[43] lui v0; lh v0 — hmm, mine[43] lui v1; lh v1. So the register is v1 vs v0 — that's the load for the third block's outer condition `if ((s16)D_80078EA6 < 0x80)`. In the target it's v0; mine v1. Why? Because the do-while(0) changed the register allocation (the load's pseudo lives across the block boundary → gets v1?).

Hmm. And the third block's inner `slti v0,v1,129` vs target's `lui v0; lh v0; nop; slti v0,v0,129` — the target RELOADS EA6 after the store (because the store to EA4 might alias? no — because of the memory clobber). In mine, the value is reused (v1), so the second load is gone (3 insns short).

So the do-while around the store fixed the ordering but changed the register allocation and the reload behavior.

Let me think about the register swap s0/s1: `base` vs `a1` (s1). In the target, base is s0 and a1 is s1. In q1, base is s1 and a1 is s0. That's a global-alloc priority difference caused by the do-while changing ref counts/live ranges.

Hmm, q3 gave 114 ins and score 38 — same insn count. Let me look at q3's diff.

Actually, let me reconsider. Maybe apply do-while(0) only where needed, in a way that doesn't change ref counts. q1 wrapped all 6 stores. Maybe only the first half's 3 stores need it (the second half already matched). Let me try wrapping only the first-half occurrences.

Also, the third block's inner `if (D_80078EA6 >= 0x81)` reload: with the do-while wrapping the store, the load after the store can't be hoisted but gcc might reuse the earlier load (cse). In the target there are TWO loads of EA6 (one before the store for `< 0x80`, one after for `>= 0x81`). cse didn't merge them because the store + barrier. Without the barrier, cse merges them (if it can prove no alias). Hmm.

So for the third block, we need cse to NOT reuse the earlier load. A dead-reset (C0414) or an aliasing store could break it.

This is getting deep. Let me approach systematically: apply the do-while only to the first-half stores (3 sites), and see.

Let me write variants:
r1: do-while on the first 3 `D_80078EA4 += a1;` only.
r2: do-while on all 6 (q1) but with the third block's inner if using a temp.
r3: q1 + dead-reset for the third block's reload.

First, let me count the occurrences and identify which belong to the first half. In the source, the first half has 3 `D_80078EA4 += a1;` and the second half has 3 `*(s32 *)(base + 0x60) += a1;`. So q1 only wrapped the D_80078EA4 ones (3 sites) — the replace targeted "D_80078EA4 += a1;" which appears only in the first half. Right.

So the first half now has the correct load order, but the register allocation flipped and the third block's reload vanished.

Hmm wait, in q1's diff, the second half (base+0x60) also shows s0/s1 swaps — that's just the global register assignment change (base/a1 swapped), which affects all uses.

So the remaining issues in q1:
1. s0/s1 swap (base vs a1).
2. Third block: the outer `if (D_80078EA6 < 0x80)` load uses v1 instead of v0, and the inner reload is missing (cse reused the value).

For issue 1: the register assignment is a global-alloc decision driven by ref counts. The do-while changes the ref counts (loop-weighted refs!). do-while(0) makes the insns inside "loop-weighted" (REG_N_REFS += loop_depth). That's what C0535 exploited ("flow REG_N_REFS += loop_depth"). Hmm, that could change priorities.

Maybe wrapping only *some* stores keeps the counts right. Or wrapping the store+if together (q2) — that was worse.

Let me look at what determines s0 vs s1: both `base` (D_80078E78) and `a1` are candidates. The target: base→s0, a1→s1. In q1: base→s1, a1→s0. Global-alloc assigns in order of priority (refs*loop_depth). The do-while increases the weight of `a1`'s uses (s0 = a1 means a1 got the first s-reg? Hmm, s0 is allocated first? Actually callee-saved allocation order depends on priorities).

Wait, in the target: s1 = a1, s0 = base. In q1: s0 = a1, s1 = base. So the priority order flipped. Adding loop-weight to the a1 uses inside do-while increased a1's priority... but a1 already had high priority? Hmm, it got s0 in q1 which is *lower* or *higher*? The order of assignment: global-alloc assigns the highest-priority pseudo to the first available register. Which of s0/s1 is assigned first? In global-alloc, the register allocation order is from the END of the register list? For MIPS, the order is s0, s1, ..., or s1, s0? Hmm.

In the target, a1=s1 and base=s0. If the highest priority gets s1... then a1 had higher priority than base in the target. In q1, base got s1, so base's priority rose above a1's.

The do-while made the `D_80078EA4 += a1` uses loop-weighted, increasing a1's refs. But that would raise a1's priority, not base's. Hmm, unless the loop notes also affect base.

Hmm, wait: in q1, s1=base. So base's priority rose. The do-while contains `D_80078EA4 += a1` only (a1 uses). Why would base's priority rise? Maybe because `base` is live across the loop note and gets extra refs? No.

Alternatively, the allocation order might be s0 first for the highest priority. Then in the target base (s0) had higher priority than a1 (s1); in q1 a1 (s0) has higher. That's consistent with a1's loop-weighted refs rising. So the target has base > a1, and our do-while pushed a1 above base.

So we need to *not* increase a1's refs. Wrap something else? The load hoist involves the store and the load of EA6. The store `D_80078EA4 += a1` uses a1. Hmm.

Alternative: put the do-while around the *load* side instead: `if (do { ... } while (0))`? Can't.

What if we wrap the whole `if (cond)` block in a do-while? Then the refs inside the loop include the EA6 load (no a1 use) — wait, the store `D_80078EA4 += a1` is inside the if? No: in block 1, the store is before the if:
```
D_80078EA4 += a1;
if ((s16)D_80078EA6 >= 0xA1) { D_80078EA4 = 0xA00000; }
```
So wrapping the if in a do-while wouldn't include the store. But sched1 could still hoist the load above the store? The load is inside the do-while body; the store is outside. If the do-while body is a separate block, the load can't move above the block start... Actually sched1 schedules per basic block; the block boundary is at the loop note? The do-while(0) creates LOOP_BEG/LOOP_END notes; if the block split happens at the note, then the load is in a separate block from the store → no hoist. And a1's refs wouldn't be loop-weighted.

Let me try: `do { if ((s16)D_80078EA6 >= 0xA1) { ... } } while (0);`.

Hmm, but the store is immediately before; the block boundary between them... The store is in the outer block, the load in the do-while block. sched1 can't move the load above the block start. 

But careful: loop.c might hoist the invariant load out of the "loop"! loop.c hoists loop-invariant computations to the loop preheader. `if (D_80078EA6 >= 0xA1)` inside a do-while(0) — the load of EA6 is loop-invariant → loop.c could hoist it to before the loop = before the store! That would defeat it. But maybe loop.c doesn't run or doesn't hoist for such a trivial loop.

Let me just test a batch:
r1: do { if (cond) {...} } while (0) for each block.
r2: do { D_80078EA4 += a1; } while (0) but ONLY in the first two blocks (not the third).
r3: q1 + dead-reset for the third block.
r4: wrap the load in a temp inside the do-while after the store (q3 style) — q3 gave 114 ins but 38 score. Let me look at q3's diff first.

Let me check q3's diff quickly.
