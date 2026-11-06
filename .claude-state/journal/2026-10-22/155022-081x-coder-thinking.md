---
ts: 2026-10-22T21:50:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IBDkYHL7jSzVNbbzACLN
---
Mine: the first -0x60 group (li -96, lui at, sh, lui at, sh) is in the lh delay slot region; the -0x80 group stays after the lhu (matching target).

Target: lh, nop, sll chain, lhu v1,6(at), li -96, stores, li -128, stores, sh v1 x2, lh...

So only the FIRST group (2 stores of -0x60) is hoisted.

Why is the -0x60 group hoisted but not the -0x80 group? Because the -0x80 group comes later in source and sched1's priority...

In the target, the -0x60 group is AFTER the lhu v1,6(at) — i.e. it's between the lhu and the li -128.

Idea: if I could make the -0x60 stores depend on `at`'s value... 

Since the -0x80 group is not hoisted, what if I reorder the source so the -0x60 stores come after the -0x80 stores? Then the -0x80 group would be hoisted instead (probably). Hmm, but the asm order must be -0x60 first.

Wait — in the target the source order is: D_80126976 = -0x60; *(s16*)&D_80126970 = -0x60; D_8012697A = -0x80; D_80126974 = -0x80; then the v1 stores. That's the current source order.

So the target's sched1 kept source order (with the barrier). Mine hoists the first group only.

The barrier prevents hoisting. What plain C can prevent sched1 from moving the -0x60 stores above the sll chain?

Idea: make the -0x60 stores depend on v1. E.g. store `-0x60` computed as `v1 ^ v1 ^ 0xFFA0`? folds? Maybe not! gcc's fold may not simplify `v1 ^ v1` at tree level... Actually tree-level folding does simplify x^x = 0 for integers (since it's `x ^ x` → 0 is valid). It does.

What about `v1 * 0`? Folds.

Hmm, what about using a pointer derived from the table: e.g. store to `*(s16 *)((u8 *)D_801944F4 + ...)`? changes addresses.

What about making the store's ADDRESS depend on v1? No.

Alternative: make the *load* later. The `lh v1,524(s0)` at 36dc: in the target the delay slot is a nop, then the sll chain. In mine the li -96 fills it.

What if the sll chain insn could fill the delay slot? It depends on v1 → can't.

So the target's nop means sched1 had NOTHING ready at that point, i.e. all other insns were blocked. The barrier made the -0x60 stores blocked (can't move above it), and the sll chain depends on v1.

In plain C, I need the -0x60 stores blocked. The only way: make them depend on the load.

Since the stored values are constants, the dependence must come from the address... 

Wait! What about the fact that in the target, the -0x60 stores come AFTER the table `lhu v1,6(at)` — the barrier is before them. What if the dependency chain is via `at`? `at` is a hard register clobbered by the lui/addiu/addu for the table load. sched1 can't move an insn that sets `at` (lui at) across another that uses/sets `at`... but sched1 works pre-register-allocation; `at` is used only in the final asm. In RTL, the symbolic address stores are `(mem (symbol_ref))` — no at. So `at` doesn't matter at sched1 time.

Hmm. So the difference is purely sched1's priority choice.

What if the -0x60 stores had a dependence on the earlier `jal` (a call)? Stores after a call are blocked from moving above it? No, they're after it anyway.

Let me look at the sched1 dump of the base vs mine to see the block boundaries. Maybe the barrier splits the basic block! An asm volatile with no memory clobber — `__asm__("")` without a clobber list is a `(parallel [])`? In the RTL it appears as `(insn (asm_input ("")))`. That's not a block boundary.

Hmm, but the src comment says the fence "pins the table read + its index arithmetic to the top of the block". So the barrier prevents moving insns above it.

Practical approach: try making the -0x60 stores depend on v1 in a way that doesn't fold:
- `D_80126976 = (s16)(v1 & 0) - 0x60;` → folds.
- Use a conditional: `D_80126976 = v1 == v1 ? -0x60 : 0;` → folds.

Hmm.

Alternative: introduce a data dependence through memory! The -0x60 stores could depend on the table load if the compiler can't prove no-alias: e.g. if the stores' address were computed from a pointer variable whose value is unknown. But the address is a fixed global (D_80126976).

What about writing the stores through a pointer variable initialized to the global:
```
s16 *p = &D_80126976;
...
*p = -0x60;
```
The pointer is a constant (symbol) → folds back.

Hmm.

Different idea: use the item-2/3 trick — make the stores part of a declaration initializer? These are globals, so no.

What if I add a `v1`-dependent statement between the table read and the stores that produces no insn? no.

What if the table read is written as TWO reads (v1 and v1b) so that the sched has more... no.

OK, let me look at the sched1 dump to see the ready-list decisions — maybe there's a structural lever (e.g. the store group being one "insn" or two).

Time: 15:57. Let me spend 5 minutes on the dump.

Actually, let me try a completely different tactic first (cheap): reorder so the -0x80 group comes FIRST in source. If sched1 then hoists the -0x80 group into the delay slot, the asm order would differ (target has -0x60 first). But maybe sched1 doesn't hoist it at all (because it's later in the block) — then I'd need to reorder back... no.

Alternative cheap try: move the `*(Blk8 *)&D_801E4C50 = ...` statement earlier (before the stores)? changes asm.

Let me try a few cheap orderings:
i1: -0x80 group first, then -0x60.
i2: interleave 76, 7A, 70, 74.
i3: interleave 76, 70, 7A, 74 (current is 76,70,7A,74 — yes current).
i4: reverse: 74, 7A, 70, 76.

And one dependency idea:
i5: `D_80126976 = -0x60; *(s16 *)&D_80126970 = D_80126976;` — the second store depends on the first (memory), might chain.

Hmm, i5 changes the li count (target has one li -96 for both).

Let me just try the order variants quickly.
