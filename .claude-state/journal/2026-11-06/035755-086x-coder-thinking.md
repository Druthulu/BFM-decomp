---
ts: 2026-11-06T10:57:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_a6XpYdZcVLbNq8mHiJYS
---
Same as item 1: the sw 88 store sinks. The v1 register issue is fixed by moving the assignment late.

So the twin has the same wall: score 2, store sink.

Hmm, both twins hit the same wall. Let me think about whether there's a way to prevent the store from sinking, now that I know the structure.

Current best (w_v1late): 
```
do { t = unkC4; } while(0);
unk58 = &D_801907C4;
unkC4 = t|2;
v1 = 0x4000;
... stores
```
Mine: lw, lui, addiu, ori, sw196, lw32, sw88, ... Target: lw, lui, addiu, sw88, ori, sw196, ...

The store sinks because in block2 the ori is ready and has higher priority.

Idea: put the RMW in its own block (do-while) so block2 = [unk58 store] alone. Then the store is in a block by itself → no sink. And the next block starts with the RMW. But in v_dw6 that moved the sb.

Wait, but in this twin the source after the RMW is `v1 = 0x4000; ...`. Let me try w_dw6 with v1late:
```
do { t = unkC4; } while(0);       // block1: lw
do { unk58 = ...; } while(0);     // block2: lui, addiu, sw
unkC4 = t|2;                       // block3: ori, sw
v1 = 0x4000;
...
```
In v_dw6 (item 1) the issue was the sb hoisting. Here the next statements are v1=0x4000 and the unk20 loads. The target: after sw196 comes lw v0,32, li v1,16384, sb zero,193, sw zero,180, sh...

So the block after the RMW in the target contains the lw32/li/sb/sw/sh. In w_dw6-style, block3 = [RMW, v1=..., unkC1=0, unkB4=0, lw32...]. sched1 might order differently.

Let me just try it: w_dw6b = do {t} + do {store} + RMW + v1 late.

Actually, let me think about the target's tail block ordering again: ori, sw196, lw32, li v1, sb zero, sw zero, sh v1,24(v0)...

In my v_dw6 (item 1), the tail block was [RMW, unkC1=0, unkB4=0, unk18..., ...] and sched1 gave: ori, sw196, sb, lw32, li, sw180, sh. So the sb was before the lw32.

The target has lw32, li, sb, sw180, sh. Hmm.

What if the block boundary is placed so that the RMW is in the *same* block as the tail but the store is in a previous block? That's the w_dw6 structure (block3 = RMW + tail). The sched1 result differs from the target.

Hmm, why would sched1 put the sb before the lw32 in mine but after in the target? Because in the target, the block also contains the load (at the start), which shifts the schedule. The target's block = [lw, addr, sw88, ori, sw196, lw32, li, sb, sw180, sh...]. The initial load's latency makes the scheduler fill with the address and the store, then the RMW, then the lw32/li, then sb/sw180/sh.

In w_dw6, block3 = [ori, sw196, lw32, li, sb, sw180, sh] — sched1 ordered sb before lw32. Hmm, why? The sb is a store; the lw32 is a load with dependents. The scheduler should prefer the lw32 (higher priority). Unless the sb has a memory dependence forcing order.

Ugh. Maybe the sb (unkC1=0) and the sw180 (unkB4=0) are zero-stores that cse/flow might merge or reorder.

Let me try a different split: put the RMW + v1 + unkC1 + unkB4 all in the block with the store? I.e., only the load is in its own block, and everything else in the second block (d_S2S3S4 = score 2, store sink).

So the tension is: the store must come before the RMW in the output, but sched1 wants it after.

What if I make the RMW *not ready* when the store is ready? The RMW depends on the load (from block1, complete). If the load were in the SAME block, the RMW would be delayed by the load latency → the store goes first (the target's mechanism).

So: the load, address, store, and RMW must all be in ONE block (the target). Then sched1 works. The barrier creates that block. The do-while around the load splits BEFORE the load (if wrapped around the preceding statement) — v_dw5 — but that failed due to the constant placement.

Let me revisit v_dw5 for this twin with the v1-late move:
```
do { unk5C = 0x8000; } while(0);   // block A
t = unkC4;                          // block B
unk58 = ...;
unkC4 = t|2;
v1 = 0x4000;
...
```
v_dw5 (item 1) gave: lw, nop, ori, sw, lw32, lui, addiu, sw88. The constant was materialized late by reload.

What if the address is a VARIABLE (so it's not a reload constant)? Then in block B: lw, a=addr, store, RMW. With `a` in the same block, t and a are both local; a born later wins v0 → swap. Hmm, unless v1late-like tricks.

What if `a` is defined in block A (with the unk5C store) so it's global? Then in block B, t is local and gets v0, and a (global) got v1 earlier. The schedule: block A: sh unk5C, lui, addiu; block B: lw, sw a, ori, sw. Order: sh, lui, addiu, lw, sw, ori, sw. Target: ... sh unk5C, lw, lui, addiu, sw, ori, sw. The address would be before the load. Wrong.

Hmm.

What if `a` is defined in block B AFTER the load but t is global (used in block C)? Then...

I keep going around. Let me try one concrete thing: the do-while around unk5C + the address as a variable assigned right after the load (v_dw5a):
```
do { unk5C = 0x8000; } while(0);
t = unkC4;
a = (s32)&D_801907C4;
unk58 = a;
unkC4 = t|2;
```
Schedule in block B: lw, lui, addiu, sw, ori, sw (the load first, then the address). Registers: t and a both local; a born later → a wins v0 → swap. Damn.

Unless t is global: make the RMW use t in a later block? 

What if I add a do-while around the RMW only:
```
do { unk5C = 0x8000; } while(0);   // A
t = unkC4;                          // B: lw
a = (s32)&D_801907C4;               // B: lui, addiu
unk58 = a;                          // B: sw
do { unkC4 = t|2; } while(0);       // C: ori, sw
```
Now t is global (B→C), a is local to B → global-alloc gives t a reg first; a gets a free one. And the schedule in B: lw, lui, addiu, sw ✓. In C: ori, sw ✓. The tail after C...

Registers: t global → v0 hopefully; a local → v1. 

This is v_addr5-like but with the split before the load (via the unk5C do-while) instead of around the load. In v_addr5 the t got v1. Hmm, but there the structure was: do{t}; do{a+store}; RMW. Here: do{unk5C}; t; a; store; do{RMW}. The difference: t and a are in the same block B.

Let me try it. Also try with v1late.

Actually, let me simplify: build this variant on the twin (which needs v1late) and on item 1.

w_split:
```
do { unk5C = 0x8000; } while(0);
t = unkC4;
a = (s32)&D_801907C4;
unk58 = a;
do { unkC4 = t | 2; } while(0);
v1 = 0x4000;
...
```
Let me generate and score.
