---
ts: 2026-10-22T21:51:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XtF7dlwGLCnqnHm0GNRd
---
The scheduler is bottom-up (from the end of the block). Priority 5-6 insns go last... The order I care about: insn 65 (priority 3, ref_count 4) is "blocked" repeatedly, and 52 (priority 2, ref_count 4).

The key: which insn is the `lh` and which are the stores. Let me find the insn numbers. Insn 47 has ref_count 19 (that's the `lh v1,524(s0)`? or the table index?).

Rather than decode, let me look at the corresponding .sched dump for the *base* (with barrier) and compare the two blocks' schedules. But the base has an extra insn.

Hmm, time: 16:02, item 4 at 14 min.

Alternative empirical approach: what makes sched1 not fill the load-delay slot? Note "blocking insn 65 for 1 cycles" — insn 65 is blocked (a load-delay). 65 is probably the `lh` or `lhu`.

Actually the crucial observation: in mine the -0x60 group (2 stores) went into the delay slot right after `lh v1,524(s0)`. The insn 65 (priority 3, ref 4) is "blocked for 1 cycle" three times — that's the `lh` waiting for... hmm.

Let me try a completely different, cheap experiment: what if the stores are written with the `D_80126970` one first? Tried variants.

New idea: make the -0x60 stores depend on the *table read* by using the loaded `v1` in the value expression in a way that does NOT fold: e.g. store `v1 - v1 - 0x60` — folds. What about `(v1 & 0) + -0x60`? folds.

What if I use a bitwise trick the tree folder misses: `(s16)(0xFFA0 | (v1 & 0))` — folds.

Hmm.

What about a `volatile`? Not allowed (lever).

What about making the stores' addresses non-constant so they can't be hoisted? no.

What if I introduce a *second* table read before the stores, e.g. `v1 = D_801944F4[...].f6;` twice? Then the second read's index chain depends on the first... but the first is a constant expression.

Hmm, what about the ordering: the target's block has the lh, nop, index chain, lhu, then stores. Mine has lh, stores, index chain, lhu.

Since sched1 is bottom-up, "blocking insn 65 for 1 cycles" three times suggests insn 65 was repeatedly blocked by a load delay — that's the `lhu v1,6(at)` maybe, and the scheduler put the stores around it.

Wait, in mine the -0x80 group went AFTER the lhu (correct), and the -0x60 group went before the sll chain. In the target, both groups are after the lhu.

So the -0x60 group should be scheduled later (higher T). Since sched1 is bottom-up, the -0x60 group should be launched earlier (larger T) than the lhu. Hmm.

Honestly, a cheap trick: make the -0x60 group's stores *appear* after the -0x80 group in the RTL by reordering, but have the assembler emit them in the target order? No.

Hmm, what if I reorder source as: 7A, 74 (the -0x80 group), then 76, 70 (-0x60)? i1 tried that: score 15 (same). Let me check i1's disassembly — maybe the order in the object changed but the score stayed 15 due to a different mismatch. Actually i1 got 15 with 78 vs 79 ins.

Hmm, all variants are 15. The missing insn (78 vs 79) is the nop.

Let me think about the nop: in the target, the load-delay nop after `lh v1,524(s0)`. Since the following insn (sll) depends on v1, sched1 inserts a nop. In mine, sched1 filled it with the li -96.

To make sched1 insert a nop, all insns at that point must be blocked. The li -96 is always ready. UNLESS the li -96 is not yet born — i.e. its birth is scheduled later. The li comes from the store of -0x60; its position follows the store group.

So: I need the store group's position to be after the lhu. What if I put the store group's source AFTER the Blk8 copy? The target's asm has the stores before the Blk8 copy (which is the second lh chain at 3734). So no.

What if the stores came after `func_8014C6C0()`? No, that's a call.

Hmm, what about this: in the target, the two -0x60 stores are at 36fc-370c, right after `lhu v1,6(at)` at 36f8. So they're scheduled right after the table load — the earliest possible after the load. In mine they're earlier (before the index chain).

Since sched1 is bottom-up and the barrier pins the group... 

Let me try: make the -0x60 stores depend on v1 through the *store address*: no.

New idea: what if I split the -0x60 group so that only ONE store is hoisted? no.

Let me look at this from the "what would the original source be" angle: the ROM's source probably had something that made the -0x60 stores depend on the table read. E.g.:

```
v1 = D_801944F4[a0->unk20C].f6;
D_80126976 = -0x60;
...
```
Hmm, no dependency. But the ROM compiler (gcc 2.7.2, the same) with a plain body would hoist them too — unless the original had a different shape.

Wait — maybe the original source did the table read differently: e.g. the index expression uses `a0->unk20C` read TWICE, or the stores are interleaved with the index computation.

Let me try: instead of `v1 = D_801944F4[((Unkstruct*)a0)->unk20C].f6;` write the index into a variable first:

```
s32 idx = ((Unkstruct*)a0)->unk20C;
v1 = D_801944F4[idx].f6;
```
That adds no insns (idx is the same). Then the stores... no dependency still.

OK here's another thought: what if the -0x60 stores were moved after the `lhu` by making them depend on `v1` via a *dead* computation that the RTL keeps? E.g.:

```
s16 m = (s16)(v1 - v1);   /* dead-ish */
D_80126976 = -0x60 + m;   /* folds to -0x60 but depends on v1 at tree level? */
```
Tree folding would fold `-0x60 + (v1 - v1)` → hmm, gcc's fold does simplify `(v1 - v1)` to 0 only if it can prove no overflow; for s32 with -fwrapv absent, `x - x` → 0 is valid. It will fold.

What about `(v1 & 0xFFFF0000) >> 16` ... no.

What if I use a volatile-ish read? no.

Honestly, let me try the simplest possible thing: put the -0x60 group BEFORE the `v1 = ...` line? No, that changes everything.

Alternative: accept a partial? No, only one kind (barrier), so WALL.

Time check: 16:04, ~16 min, 8 tries. Need more tries.

Let me try a batch of ~10 quick variants:
j1: idx variable split.
j2: store group after the Blk8 copy.
j3: -0x60 stores via a temp `s16 m = -0x60;` declared before the table read.
j4: `D_80126976 = -0x60; D_80126970... = D_80126976;` (chain via memory).
j5: write the two -0x60 stores as `*(s16*)&D_80126976 = -0x60;` and `*(s16*)&D_80126970 = -0x60;` (cast both).
j6: reorder the table read after the stores.
j7: use `((Unkstruct*)a0)->unk20C` read into a variable used twice.
j8: make the v1 stores come first.

Let me also consider that the target's block might be split differently.

Let me run j1-j8.
