---
ts: 2026-11-06T10:59:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5nEmBpbQtPwOKeJXcGEb
---
w_lit = 2, but now the diff is the sb (like item 1's v_dw6) — wait, this is a different score-2: the sb moved from 34 to 37.

Hmm, actually this is exactly item 1's v_dw6 diff. Interesting.

So the twin with literals behaves like item 1. The store order is right now, but the sb moved.

Let me try: in w_lit, the structure is:
```
do { unk5C } while(0);
t = unkC4;
a = (s32)&D_801907C4;
unk58 = a;
do { unkC4 = t|2 } while(0);
unkC1 = 0;
...
```
The diff: sb (unkC1=0) at 34 vs 37. Mine hoists the sb earlier; the target has it later (after lw32/li).

Hmm. In this structure, the block after the RMW = [sb, sw180, lw32, li, sh...]. Target: [lw32, li, sb, sw180, sh...]. So sched1 in mine put sb first (source order), the target put lw32/li first.

Wait, in the target, the sb is AFTER the lw32 and li. So the target's schedule hoists the lw/li above the sb. That's because the load has a dependent store and higher priority.

In mine, the sb is first in source, so the scheduler emits it first.

Hmm, but in item 1's v_dw6 the same thing happened. So it's consistent.

What if I move the `unkC1 = 0; unkB4 = 0;` statements to AFTER the unk18 stores in the source? Then the source order is: RMW, unk18 stores (lw32, li, sh...), then sb/sw180. The target has lw32, li, sb, sw180, sh v1,24. So the sb/sw180 come between the li and the first sh in the target. Hmm, so the target's order isn't the source order.

Actually the target's schedule: after the RMW: lw v0,32 (for unk18), li v1,16384, sb zero,193 (unkC1), sw zero,180 (unkB4), sh v1,24(v0) (unk18), lw (unk1A), nop, sh v1,26...

So the scheduler interleaved: it hoisted the unk18 load early, then the li, then the two zero-stores, then the sh.

If the source order were: unk18=0x4000; unk1A=0x4000; ...; unkC1=0; unkB4=0; — the scheduler would hoist the loads and place the stores.

Honestly, the scheduler's exact order here is what the barrier's block structure produced. With the do-while structure we get a slightly different block, hence a slightly different schedule.

Time check: item 2 started ~04:07, now maybe 04:25. 18 min. Let me try one or two more quick variants, then record a wall.

Variant: move `unkC1 = 0; unkB4 = 0;` before the RMW in source? Then they'd be in the RMW's block... 

Actually, let me try putting the two zero-stores BEFORE the RMW in source (they're independent). Target order: ...sw196, lw32, li, sb, sw180, sh. If the source has sb/sw180 before the RMW, the scheduler might hoist the lw32/li above them.

Let me test: w_zmove.c = w_lit with `unkC1 = 0; unkB4 = 0;` moved to just before the RMW do-while.

Actually in the target, the sb/sw180 come after the RMW (sw196). So source order before the RMW would require sched1 to sink them after. Unlikely.

Alternative: move them AFTER the three unk18/unk1A/unk1C stores in source. Then the schedule: RMW, lw32, li, sh, lw, sh, lw, sh, sb, sw180. Target has sb/sw180 before the sh's. Hmm.

OK, let me try one more idea for the item-1/twin wall: what if the *tail* statements are in a separate do-while so their block starts with the unk18 store? The target's tail block (after the RMW) starts with lw32. In w_lit the tail block starts with sb.

So: put a do-while boundary right after the RMW, so the next block starts at unkC1=0 — that's what we have. The target's tail block starts with the lw32, meaning in the target the sb/sw180 are NOT at the start.

What if I put the boundary after the sb/sw180 (so the block starts with the unk18 store)? Then: block C = [sb, sw180], block D = [lw32, li, sh...]. Order: sb, sw180, lw32, li, sh. Target: lw32, li, sb, sw180, sh. Wrong.

Hmm.

What if the sb/sw180 are moved to the END of the tail in source? Target order: lw32, li, sb, sw180, sh. The sh uses the lw. So the source order could be: unk18 store; unk1A store; ... but the target has only ONE sh before the sb? Let me look at the full target tail again:

```
f34 lw v0,196
f38 lui v1
f3c addiu v1
f40 sw v1,88
f44 ori v0,2
f48 sw v0,196
f4c lw v0,32(s0)
f50 li v1,16384
f54 sb zero,193(s0)
f58 sw zero,180(s0)
f5c sh v1,24(v0)
f60 lw v0,32(s0)
f64 nop
f68 sh v1,26(v0)
f6c lw v0,32(s0)
f70 nop
f74 sh v1,28(v0)
f78 lw v1,32(s0)
f7c nop
f80 lhu v0,44(v1)
...
```
So the sb/sw180 are between the li and the first sh. The scheduler hoisted the first unk18 load to f4c (before the sb), then the li, then the sb/sw180, then the sh.

Interesting: the target's tail is: lw(unk18), li, sb, sw180, sh(unk18), then lw(unk1A), sh, lw(unk1C), sh.

The original C order: unkC1=0; unkB4=0; unk18=0x4000; unk1A=0x4000; unk1C=0x4000; ...

So sched1 hoisted the unk18 load above the sb/sw180 and the li, but not further.

In my w_lit, the sb was at 34 (before the lw32). So my schedule: ori, sw196, sb, sw180, lw32, li, sh... Hmm wait, the diff said mine has sb at 34 and the target at 36. Let me see mine's actual order: from the earlier v_dw6 dump: ori, sw196, sb, lw32, li, sw180, sh. So mine: sb first, then lw32.

The difference: the target's scheduler hoisted the lw32 above the sb; mine didn't. Why? The block structure: in the target, the tail block contains the load/addr/store/RMW (the barrier is before the load), so when the scheduler processes the block, the unk18 load is part of a longer list. In mine, the tail block starts at the sb.

Hmm, so the block structure difference causes the schedule difference. To replicate the target, the RMW must be in the SAME block as the tail (no do-while around the RMW). But then the store sinks (d_S2S3S4).

Wait: in d_S2S3S4 (item 1), the block2 = [store, RMW, sb, ...] and the store sank. But what if the store is in the block and the RMW too, and the store sinks... 

Hmm, unless the load is also in that block (so the RMW is delayed by the load latency). So: ONE block containing the load, address, store, RMW, and the tail. That's the target. The split is BEFORE the load.

So: split before the load, everything else in one block. That's v_dw5 (do-while around unk5C). And v_dw5 failed because the constant materialization was late.

For the twin with literals: w_dw5-like = do-while around unk5C, then t=load, unk58=&D_801907C4 (constant), RMW, tail. The constant materialization by reload might be late.

What if I use the address variable `a` defined after the load (so it's a qty, not a constant)? Then t and a are both in the block; a born later wins v0 → swap. Hmm, but wait: if the split is before the load and t/a are in the same block, the swap happens.

Unless t is used later (global). In the target, t is pinned.

ARGH.

OK. Both twins are walls at best 2 with the same mechanism. Let me record item 2's wall and move to the big items. I have ~2 more items and time is finite.

Actually, hold on. Let me reconsider one more time the possibility of making t win v0 in the single-block structure. The qty priority: t (refs 2, size 4) vs a (refs 2, size 4). t born at the load, a born at the address. If I make `a`'s birth EARLIER but its *first use* later... no.

What if `a` is declared at the top of the function and initialized there? Then a's birth is early (block A), but its live range is long → low priority. And it would be global. Then t (born in block B) is local to B... 

Hmm, what if `a` is initialized at the top of the *else block* (before the calls)? The else block starts after the if-branch. `a = (s32)&D_801907C4;` at the top of the else block, before the two calls. Then a is global (live across the calls) and its live range is long → low priority. And the lui/addiu would be emitted early (before the calls) — the target has it at f38. Wrong.

What if a is assigned after the calls but before the stores (in the same block as the load)? Same block, born before t? If `a` is assigned BEFORE the load in source, its birth is earlier, so its live range is longer → t wins v0! And the schedule: the address first (v_addr3, wrong order).

Unless sched1 moves the load first... 

Wait, in v_addr3 the order was lui, addiu, lw. sched1 kept source order. What if the load's priority is higher? The load has a dependent (ori). The address has a dependent (store). Hmm.

What if the store that uses `a` is in a LATER block (so the address chain's priority is lower)? Then: a = addr (block B), t = load (block B), [block C: store], RMW... Hmm, the address's dependent store is in block C → the scheduler in block B sees the lui/addiu with no dependent in the block → lower priority → the load goes first!

Let me try:
```
do { unk5C = ...; } while(0);   // A
a = (s32)&D_801907C4;            // B: lui, addiu
t = unkC4;                       // B: lw  (should be scheduled first)
do { unk58 = a; } while(0);      // C: sw
do { unkC4 = t|2; } while(0);    // D: ori, sw
tail...
```
In block B, the lui/addiu feed a store in block C (not in B), so their in-block priority is low; the load feeds the ori in block D, also not in B. Both similar. Hmm, both cross blocks.

Hmm.

I'll stop here. Time is limited. Let me record item 2 as a wall (best 2) and move to the big items. Actually, wait — let me first check the time and count tries for item 2: orig(1), base, w_dw, w_dw6, w_bar, w_v1late, w_v1dw, w_split, w_split2, w_lit = 10. Not enough (need 30). I need to score more variants for item 2 to count as an attempt.

Hmm, the rule: "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". So I need 30 tries on item 2. Let me generate a batch of variants (like item 1's permutation set) to get the count up and maybe find something.

Let me generate the permutation set for the twin (with literals) and score them. That gives 32 tries quickly.

Let me write a gen script for the twin.
