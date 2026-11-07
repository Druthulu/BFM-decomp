---
ts: 2026-11-06T10:56:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_d5l2WQkeqJuEJr7G7L9t
---
v_dw6 mine:
```
f34 lw v0,196
f38 lui v1
f3c addiu v1
f40 sw v1,88
f44 ori v0,2
f48 sw v0,196
f4c sb zero,193      <- moved after sw196 (target has it before lw32)
f50 lw v0,32
f54 li v1,16384
f58 sw zero,180
f5c sh v1,24(v0)
```
Target:
```
f34 lw v0,196
f38 lui v1
f3c addiu v1
f40 sw v1,88
f44 ori v0,2
f48 sw v0,196
f4c lw v0,32
f50 li v1,16384
f54 sb zero,193
f58 sw zero,180
f5c sh v1,24(v0)
```
So mine moved `sb zero,193` up (before the lw32) while the target has it after the lw/li. Actually mine[34] sb is EARLIER than target[36]. Wait: mine has sb at f4c (position 34) and target at f54 (position 36). So mine hoisted the sb earlier; the target has it later (after the lw and li).

This is the same class: sched1 ordering of a store.

Hmm, so v_dw6 is off by one store position too. The blocks: after the RMW block, the next block starts with unkC1=0, unkB4=0, then the unk20 loads... In the target, the sb is after the lw32/li. In mine, before.

If the block boundary is right, sched1 in the last block orders: sb, lw32, li, sw180, sh. Target: lw32, li, sb, sw180, sh.

The sb and sw180 are zero-stores; the target has them after the lw and li (filling...). sched1 hoisted sb in mine.

Hmm.

OK: this item is genuinely tricky. Given the time (started 03:35, now ~04:05 = 30 min), I must stop per the brief.

Let me record the WALL for item 1 and move to item 2. Actually — since item 2 is a twin, maybe I should spend the next 20-30 min on item 2 with the knowledge gained; the same wall likely. But let me at least check whether item 2's orig differs (e.g., it has `s32 v1;` and different globals but the same shape).

Given the wall, let me be efficient: record item 1 WALL, then item 2: try the best candidates (v_dw, v_dw6, v_addr) and record the same wall if they behave the same.

Then the two big items (144 ins) — those are the HUD functions with 6 levers; barrier+pin. Those might be harder.

Hmm, wait. Before recording a wall, let me reconsider one thing: maybe I should look at how the *other* twin (func_80189F7C) differs: it has `s32 v1;` and `v1 = 0x4000;` — the author already used a variable for 0x4000. Interesting: in func_8018966C the 0x4000 constants are immediates; in 80189F7C they use v1. This suggests the author used different spellings for the same code. Maybe the lever-free version of one is easier.

Let me look at 80189F7C's target and orig differences. Its orig has `s32 v1; v1 = 0x4000;` before the t load, and the barrier after `unk5C = 0x8000`. Wait, in 80189F7C the barrier is before `v1 = 0x4000;`? Let me re-read:

```
((Unkstruct*)s0)->unk5C = 0x8000;
__asm__("" ::: "memory");
v1 = 0x4000;
t = ((Unkstruct*)s0)->unkC4;
((Unkstruct*)s0)->unk58 = (s32)&D_801907C4;
...
```
So the barrier is before `v1 = 0x4000` and the t load.

Let me score the twins' lever-free variants to see if one is easier. Let me apply the same v_dw6/v_dw transformations to 80189F7C.

Actually, let me first write the item-1 wall row, then work on item 2.

Hmm, hold on. Let me reconsider the whole approach once more. What if the intended lever-free body uses a *different source order* for the whole tail, e.g., putting the unkC1=0/unkB4=0 stores BEFORE the unkC4 RMW? The target's order is fixed by the bytes, but the C order can differ and sched1 reorders.

Actually here's a thought: the target's final order is essentially the source order of the orig. The barrier preserves it. Without the barrier, sched1 reorders. The do-while split changes things. What if we *disable* sched1's reordering by making each statement its own block? Then the order is exactly source order. But blocks also affect allocation and add overhead? No overhead (do-while emits nothing) but each block boundary prevents reordering.

If I wrap EVERY statement in its own do-while, the order would be exactly the source order = the target order (since the target is source order). But allocation: t and the address would be in different blocks, affecting registers (as seen). Hmm, but maybe that's fine: t in its own block, the address in another.

But v_dw6 showed a store moved even with blocks — because the target's order is not exactly the source order: the target has `lw v0,32` and `li v1,16384` between sw196 and sb, i.e., within the last block sched1 reorders.

Let me check: the source after the RMW: unkC1=0; unkB4=0; unk18=0x4000; unk1A=0x4000; ... The target: lw v0,32 (the unk20 load for unk18), li v1,16384, sb zero,193 (unkC1), sw zero,180 (unkB4), sh v1,24(v0) (unk18). So the target hoisted the lw/li above the sb/sw. That's sched1 reordering in that block — matching the original (barrier-free) block.

So the target's block structure is exactly ONE block from the load to the end, with the barrier before the load. And within that block sched1 produced the source order (because the load latency drives it).

So the ONLY thing we need is the barrier replacement: a split before the load, with everything after in one block, and the load first in that block.

v_dw5 (do-while around unk5C) did that but the schedule was off. Why? Because in v_dw5 the block after the do-while starts with the load, but the constant materialization (lui/addiu for &D_801907C4) was placed by reload LATE (after the lw32). In the target (with the asm), the constant is placed at 29-30 (right after the load).

Hmm, reload places the constant materialization at the point of use (the store). sched2 then schedules. In v_dw5, the block is one; sched2 could reorder but didn't.

Wait, in v_dw5 the final order was: lw, nop, ori, sw, lw32, lui, addiu, sw88. The constant materialization ended up after the lw32. In the target: lw, lui, addiu, sw88, ori, sw196, lw32.

The difference: the constant's placement and the ori ordering. With the asm present, reload's output differs? The asm forces memory ordering; the lui/addiu isn't memory.

Hmm, sched2 (post-reload) is a different scheduler. Let me check the target's .sched2 dump vs a candidate's. That requires a spliced TU.

Honestly, given the time, let me take the pragmatic path: try v_dw5-style splits with the address as a *variable* (to control the constant placement) — v_addr variants already did that.

Let me try ONE final combination: do-while around unk5C (split before the load) + the address as a variable `a` defined right after the load (inside the same block):
```
do { unk5C = 0x8000; } while(0);   // block A
t = unkC4;                          // block B
a = (s32)&D_801907C4;
unk58 = a;
unkC4 = t|2;
```
This is v_addr4 with the split moved before the load instead of around it. In v_addr4 the do-while was around the load (t in block1). Here the load is in block2 with a. So t and a are both local to block2 → a (born later) wins v0 → swapped. Hmm.

Alternatively: `do { unk5C } while(0); a = ...; t = ...;` no.

I'll stop. Record the wall.

Actually, WAIT. One thing I haven't tried: what if the load's result t is used *in the same statement* as the store, i.e., the RMW is written with the load inline: `unkC4 = (unkC4 | 0x2);` — that's `|=`. With `|=`, there's no separate t; the qty is the loaded value used immediately by the ori. The load's pseudo is born and dies in the RMW (short range). And the address is a constant pseudo (not a qty). Then the only qty competition is with other pseudos.

p_or (S1, S3, |=) scored 11 because the load hoisted. With a do-while around the unk5C or around the `|=`:
`do { unkC4 |= 0x2; } while(0)` — the load+ori+store in a block; the unk58 store in another block → order: store, lw, ori, sw. Wrong.

Hmm what about: `unk58 = ...; do { unkC4 |= 0x2; } while(0);` → the block after the store contains the RMW. Order: lui, addiu, sw88, lw, ori, sw196. Target: lw, lui, addiu, sw88, ori, sw196. Close but the load is after the address.

If the RMW's block starts with the load, sched1 issues the load first, then the store's address... but the store is in the PREVIOUS block. Hmm.

What if the store and the RMW are in the same block with the load: `do { unk58 = ...; unkC4 |= 0x2; } while(0)` → order lui, addiu, sw88, lw, ori, sw. Target has the load first.

OK so with |=, the load is always after the address. The target has the load first because the barrier is before the load and the address comes later.

So: `do { unk5C = 0x8000; } while(0); t = unkC4; unk58 = ...; unkC4 = t|2;` — the load first in the block. That's v_dw5, which failed due to the constant placement.

What if instead of a do-while around unk5C, I put the *unk2/unkC0/unkBC/unk5C stores* in the do-while and the load after? Same as v_dw5 but with more statements in the loop; the split is at the same place. Probably the same.

What if the split is achieved by a do-while around the *calls*? No.

Let me test v_dw5 with the address as a variable:
```
do { unk5C = 0x8000; } while(0);
t = unkC4;
a = (s32)&D_801907C4;
unk58 = a;
unkC4 = t|2;
```
t and a both local to the same block → a wins v0. Swapped. Unless I put `a` in the do-while block (block A): then a is local to A, t local to B → both local, different blocks: local-alloc in B gives t v0 (only qty), and in A gives a v0 too? Then after register allocation they'd both be v0 → conflict across the block boundary (t is live across A? no, t is defined in B, a dies in B). a is defined in A and used in B → a is live across the boundary → global! Then global-alloc assigns a a hard reg first... hmm, a global with refs 2.

If a is global and t is local to B, global-alloc assigns a a reg (maybe v0), then local-alloc gives t v1. Swapped.

Unless global-alloc gives a v1 (because t... no, t is local, not considered).

Argh.

OK, final answer for item 1: WALL best 2, tag sched-store-sink (or a new tag). The mechanism: with the barrier gone, sched1 hoists the unkC4 load to the EBB top or sinks the unk58 store; the do-while split that fixes the order leaves the constant materialization misplaced; the pin's v0 reservation is also needed for the t/address allocation.

Let me write the results row now. But first let me double-check the "tries" count and pick the evidence string.

Actually, hmm, wait. Let me reconsider the pin part: in d_S2S3S4 (score 2), the registers were correct WITHOUT the pin. So only the store position is wrong. So the wall is purely sched-store-sink. Good.

Let me record: result WALL, best 2, tries ~53, wall sched-store-sink, evidence "sched1/sched2: load-then-store order needs the asm barrier; do-while split keeps order but reload places the &D_801907C4 constant late".

Hmm, evidence should be "gcc pass + mechanism ≤140 chars". Let me write: "sched1: without the barrier the unkC4 load hoists to the EBB top; a do-while split fixes order but sched1 sinks sw 88 (best 2)".

Let me now append to results.tsv. Format: `dir file func kinds result best tries wall evidence` tab-separated. The header uses tabs.

Let me write the row with printf. Careful with tabs.

Also the moves.md line: `kind | func | MATCH: move / WALL tag — mechanism (G28x)`.

Let me do item 1's results row now. Then item 2.

Actually, wait. I want to reconsider whether to spend the remaining budget differently: maybe try the big items first (they might be easier or harder) — no, let me finish the small pair.

Let me also reconsider: is there any chance the task intends "lever-free" to allow keeping *non-row* levers? The kinds for these items are barrier,pin. The rule: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin, launder, barrier, keepalive macro or asm". So both must go.

OK. Let me write the wall row.

Hmm, actually hold on. Let me try one more thing that just occurred to me: what if the barrier's replacement is the `do{}while(0)` around the *load* but with the store order fixed by making the unk58 store part of the SAME do-while as the RMW, i.e.:
```
do { t = unkC4; } while(0);      // block1: lw
unk58 = ...;                     // block2: lui, addiu, sw
do { unkC4 = t|2; } while(0);    // block3: ori, sw
```
= v_dw6, which was off by the sb.

What if I DON'T wrap the RMW, i.e.:
```
do { t = unkC4; } while(0);      // block1
unk58 = ...;                     // block2
unkC4 = t|2;                     // block2
```
= d_S2S3S4, store sinks.

So v_dw6 (3 blocks) fixed the store but moved the sb. The sb is in the block after the RMW: [sb, sw zero, lw32, li, sh...]. In v_dw6, sched1 put the sb first (source order) — but the target has lw32/li before sb. So the target's block is the whole tail (one block), where sched1 hoisted the lw32/li above the sb.

So v_dw6 splits too much. If I merge the RMW with the following statements (i.e., only wrap the load and the store), then the block after the store contains the RMW + sb + ... = the target's structure (one block), but the RMW and the store would be in the same block? No: 
```
do { t = unkC4; } while(0);   // block1: lw
unk58 = ...;                  // block2 start
unkC4 = t|2;                  // block2
unkC1 = 0; ...                // block2
```
That's d_S2S3S4 (block2 = store, RMW, sb, ...) where the store sank.

If instead:
```
do { t = unkC4; } while(0);   // block1
do { unk58 = ...; } while(0); // block2: lui, addiu, sw
unkC4 = t|2;                  // block3 + rest
```
Then block3 = [ori, sw196, sb, ...]. In block3 sched1 would order ori, sw196, then sb/sw/lw32/li... The target has ori, sw196, lw32, li, sb. So block3 = the target's tail minus the store. That could work! The sb position issue in v_dw6 was because block3 started at the RMW; same here. Hmm, v_dw6's block3 = [RMW, sb, sw180, lw32, li, sh...]. The target's tail from the ori: [ori, sw196, lw32, li, sb, sw180, sh]. In v_dw6 sched1 put sb before lw32; the target has lw32 first.

So even in the target, that tail is one block and sched1 ordered lw32, li, sb, sw180, sh. In v_dw6 it ordered sb, lw32, li, sw180, sh. Why the difference? Because in the target the block also contains the load/address/store before it, which affects the schedule? Possibly the load's latency shifts things.

I'll stop. Record the wall.

Let me now write the results row and moves.md line for item 1, then move to item 2.

Actually — one consideration: maybe I should NOT spend 25 min per twin. Let me do item 2 quickly: apply the same best candidates, confirm, record the wall, then spend the remaining effort on the two big items.

But the brief says each WALL needs ≥20 min and ≥30 tries on that item. So for item 2 I need 20 min and 30 tries too. Hmm, "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". So I must do the work per item. OK.

Let me write item 1's row.
