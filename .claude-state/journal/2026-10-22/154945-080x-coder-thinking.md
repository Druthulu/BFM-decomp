---
ts: 2026-10-22T21:49:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LDWZrTpNoMOUblHhsK2c
---
Target: at 36dc `lh v1,524(s0)` then 36e0 `nop` (load delay), then the sll/addu/sll index chain, then `lhu v1,6(at)` at 36f8, then li -96, stores.

So the lh's delay slot is a nop, then the index arithmetic.

In mine, the li -96 + stores are hoisted into the delay slot at slot 24.

Hmm wait: the delay slot of `lh v1,524(s0)` is the next insn. In the target it's `nop`; then the sll chain. In mine it's `li v0,-96` etc.

But note the target has TWO lh 524(s0) reads (36dc and 3734). Mine too probably.

The lever: the -0x60/-0x80 stores must not be hoisted into the delay slot. In the target they come after the table load (`lhu v1,6(at)`).

Plain C idea: make the constant stores depend on the loaded value? No.

Alternative: make the index computation chain longer/ordered so sched1 can't fill the delay slot... sched1 fills the delay slot with any ready insn; the li is always ready.

What about making the store values depend on v1? E.g. `D_80126976 = -0x60;` where -0x60 is... no.

Hmm. What if the two -0x60 stores come *after* the v1 stores in source (order change)? Then sched1 would fill the delay slot with `lui at; sh v1` instead — also wrong.

What determines which insn fills the delay slot? sched1 schedules the block; the delay slot is filled by sched1's `md_sched` or reorg later? On MIPS, load delay slots are handled by sched1 (it inserts nops) and the branch delay slot by reorg.

In the target, the load-delay slot is a nop → sched1 couldn't find a useful insn, or the following insns depend on the load.

Actually, the load `lh v1,524(s0)` is followed by `nop` then `sll v0,v1,0x2` — the sll DEPENDS on v1, so it can't fill the delay slot. The li -96 is independent and could fill it — but in the target it's placed much later (after the lhu).

So in the ROM, sched1 put li -96 after the `lhu v1,6(at)` load. Why? Because the stores `sh v0,0(at)` use `at`, which is the address register computed by `addu at,at,v0` for the table load! The stores' addresses are symbolic (lui at; sh), and sched1 might avoid moving stores across the `at` usage (at is a hard reg, clobbered). Yes! `at` is used by the table load chain; the constant stores also need `at` for their lui. So they must be scheduled after the at-dependent chain... but sched1 in mine put them right after the lh (before the sll chain).

Hmm.

OK, the barrier in the source pins the table read + index arithmetic to the top of the block. Without it, sched1 hoists the stores.

Plain C options:
1. Make the stores' values depend on v1 in a value-preserving way: e.g. `D_80126976 = v1 - v1 - 0x60;` → folds to -0x60? Probably folds at tree level.
2. Reorder statements: move the D_80126962 = v1 stores before the constant stores? Then the delay slot might get `lui at; sh v1` — also wrong.

Hmm, but maybe the whole store group moving as a block is the issue: in mine the group starts right after the lh. If the group were *forced* after the table load, we'd match. The table load `lhu v1,6(at)` depends on the index chain.

What if the constant stores' values were read from the table entry? No.

Idea: use `v1` in the address? no.

Idea: make the constant stores depend on the table load by making the value: `D_80126976 = (s16)(0x60 * -1)`? folds.

Idea: compute the constants from v1: `D_80126976 = v1 * 0 - 0x60;` folds.

Hmm.

Alternative approach: change the *order* of the source statements so that the delay slot gets something harmless. In the target the delay slot is a nop, i.e. nothing was available. For sched1 to emit a nop, all candidate insns must be blocked.

What if the first statement after the lh were the index chain (dependent on v1)? It is: `v1 = D_801944F4[...].f6` — the index chain sll/addu/sll depends on v1 (the loaded unk20C).

In mine, sched1 chose the independent constant stores for the delay slot.

What if the constants' li were not ready — e.g. if the -0x60 value were loaded from memory? no.

What about making the store address computation depend on v1? e.g. `D_80126976 = -0x60;` → address is a symbol constant. If I write it via a pointer computed from... no.

Practical: try the item-3 trick — put the constant stores in a different form, e.g. via a struct/array so the address uses a register (not `at`)? That changes the asm (target uses lui at; sh).

Let me think about sched1's choice: it schedules the block top-down? sched1 (the first scheduler) schedules with priority. The delay slot after `lh` gets filled by the next scheduled insn if independent.

To block it, the next insn must depend on the lh. In the target the nop means sched1 had no ready independent insn at that point — because the stores' `at` address setup was blocked by the earlier `at` uses? Hmm, actually the sll chain also uses v0... 

Let me look at the sched1 dump for the base (with barrier) and for mine to see the difference. That's the reliable route. But time: item 4 started 15:48, now ~15:52. I have time.

Actually, let me first try cheap variants:
h1: move the two -0x60 stores after the two -0x80 stores (order).
h2: move the D_80126962/6A stores before the constants.
h3: make the constants come from a variable `s16 m = -0x60;` (one li shared? the target has li v0,-96 once and two sh's — so it already shares one li).
h4: init-at-decl trick? no decl here.

The target: `li v0,-96; lui at; sh v0,0(at); lui at; sh v0,0(at)` then `li v0,-128; lui; sh; lui; sh`.

In mine the same sequence just placed earlier.

h5: interleave: `D_80126976 = -0x60; D_8012697A = -0x80; *(s16*)&D_80126970 = -0x60; D_80126974 = -0x80;` — changes grouping.

Let me try a batch of order variants and see if any moves the group after the table load.

Actually, another idea: the barrier is *after* `v1 = D_801944F4[...].f6;` and before the stores. So the barrier prevents sched1 from moving the stores BEFORE the table read. Without it, sched1 moves them up.

Plain C equivalent: make the stores depend on the table read. Since the table read produces v1 and the stores store constants... 

BUT: what if the constant stores are written as storing from a variable that is *assigned* the constant earlier but whose assignment is placed after the table read? E.g.

```
s16 m;
v1 = table[..].f6;
m = -0x60;
D_80126976 = m;
*(s16*)&D_80126970 = m;
```
The `m = -0x60` is still independent of v1 → hoistable.

What if the constant is derived from v1: `m = (s16)(v1 & 0) - 0x60;` → folds.

Hmm, what about `m = -0x60 + (v1 - v1);`? folds.

Unless the compiler doesn't fold `v1 - v1`... it does.

OK, what about making the store's VALUE be v1 for one of them? no.

Different angle: the sched1 decision might hinge on the *block structure*. If the stores were in a different basic block (e.g. after an `if`), sched1 couldn't move them into the delay slot. But the target has them in the same block.

Hmm, what if I add a second read of the table (like the target's second `lh 524(s0)` at 3734)? The target reads unk20C twice (once for the index chain and once for the Blk8 copy). Already in the source.

Let me look at where mine diverges more fully — maybe the whole schedule differs and there's a different fix. Let me dump mine's full disassembly around that region.
