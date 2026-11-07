---
ts: 2026-11-06T11:58:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_l72J8eI8cSL3jonmhixr
---
Still 8. The `two` variable and do-while didn't change. Let me look at the v_two diff to see if the allocation changed. Let me check.

Actually, the score is the same. Let me think about the two issues:
1. Register swap (v1->v0 x4, v0->v1 x2).
2. Store position (one slot).

For issue 2 (store sink): the barrier `__asm__ __volatile__("")` at the end of the middle block. It's a compiler barrier that prevents the scheduler from moving the 0x10 store past it. Without it, sched sinks the store one slot. To fix in real C, I need a dependence or a scheduling barrier. 

Hmm, the store `CAST_WIDTH(s32, (u8*)a0, 0x10) = v;` then the next statement is `a0->unk14 = 0x200000;`. The scheduler moved the store after the `li a0,2432` (the func_8002D4C8 arg). 

Real C: reorder the statements so the store naturally stays? Or add a dependence between the store and the next statement. The next statement is `unk14 = 0x200000` (a store to a0+0x14). If the compiler can't prove 0x10 and 0x14 don't alias... they're both constant offsets, non-overlapping. Hmm.

What if I combine the store with something? 

For issue 1 (register swap): the target has p in v0, two in v1. Mine has two in v0, p in v1. 

Let me look at the v_two disassembly to see the current allocation. Let me dump it.

Actually, let me reconsider. The target:
- lw v0,32(s0)   (p in v0)
- li v1,2        (two in v1)
Mine:
- lw v1,32(s0)   (p in v1)
- li v0,2        (two in v0)

So mine allocates two to v0 and p to v1. To flip, I need p to get v0. Since p is born first and has more uses, why does it get v1? 

Maybe because `two` is a CONSTANT (2) and gcc's local-alloc has a preference to put constants in v0? Or because of the `register s32 two __asm__("$3")` pin, the original forced two to v1, and without it gcc picks v0 for two.

Let me look at the order of allocation. In local-alloc, pseudos are allocated in order of qty priority. The `two` pseudo might have higher priority (being a constant with REG_EQUAL?) or lower.

Hmm. Let me try changing the order: compute `two` BEFORE `p`. Or make p's birth earlier. 

Actually, the target's p is in v0 and two in v1. If I could make `two` get v1... 

Let me try: reorder so `two = 2` comes before `p = ...`. Then two is born first → gets v0? That's the opposite. Hmm.

Or make p used more (it already is). Or use a `u16` for p? No.

Let me look at the v_two diff to see if the allocation changed from nopin. Let me dump.

Actually, let me think about the register pair counts: v1->v0 x4, v0->v1 x2. So mine uses v1 where target uses v0 (4 times: the lw, the 3 sh zero), and v0 where target uses v1 (2 times: li v1,2 and sh v1,2(s0)? that's 2). So it's a clean swap of p and two between v0 and v1.

To flip, I need gcc to allocate p to v0 and two to v1. 

In local-alloc, the order is by `qty_compare`. The pseudo with higher priority gets the first free register. Let me look at what determines it. Typically, more refs × live length → higher priority. p has 4 refs (lw + 3 sh), two has 2 refs (li + sh). So p should have higher priority → gets v0. But mine gives p v1. Weird.

Wait, maybe the issue is the ORDER of allocation: local-alloc processes pseudos in order of first appearance (by regno/UID). p is born at insn 4 (lw), two at insn 5 (li). So p first → v0. But mine gives two v0. 

Hmm, maybe because `two` is a constant (2) and gcc's `reg_equiv_constant` or local-alloc gives constants a preference. Or the `two = 2` creates a pseudo with REG_EQUAL 2, and local-alloc's copy/constant handling.

Let me try making `two` NOT a constant but computed: e.g., `two = 1 + 1;`? Folds to 2. Or `two = 2; two` read. Hmm.

Let me try: `two = p != 0 ? 2 : 2;`? adds compare.

What if `two` is read from a global? No.

Let me look at the target's original source: `register s32 two __asm__("$3"); two = 2;`. The pin forced $3. Without it, gcc chose v0.

Maybe I can force v1 by making `two` a variable that gcc allocates after p. If I declare `two` and use it only later... 

Let me try: `s32 two; ... p = ...; ...; two = 2; store two;` with two assigned AFTER p. Already in v_two (p first, then two=2). And it gave two v0.

Hmm. What if I make `two` a `u8` or `s16`? v_two_u16 = 8 (same). 

What if I use `((...)a0)->unk2 = 2;` but force the constant to v1 by making it the result of a function? No.

Let me look at the actual v_two disassembly to confirm the swap and understand.

Actually, this is the local-alloc register choice (lreg-qty-priority wall). Let me check walls.txt: `lreg-qty-priority local-alloc qty priority (refs/live length) gives the hard reg to the other pseudo (G22)`. That fits!

So the register swap might be a lreg-qty-priority wall. And the store sink is a sched-store-sink wall.

Hmm, two issues. Let me see if I can crack either.

For the store sink: let me try reordering the tail statements. The target order after the middle block:
- sw v0,16(s0)   (0x10 = v)   [insn 29]
- li a0,2432     [30]
- lui v0,0x20    [31]
- sw v0,20(s0)   (unk14)      [32]
- lui v0,0x2     [33]
- move a1,zero   [34]
- sw zero,24(s0) (0x18)       [35]
- sw v0,72(s0)   (unk48)      [36]
- jal func_8002D4C8 (delay sw zero,28(s0)) [37,38]

Mine has the sw 0x10 at 30 (after li a0,2432 at 29?). Let me see the full mine order. The diff only showed the one-insn move. So mine: ... sw 0x10 at 30, target at 29. The barrier prevented sched from sinking the store past the `li a0,2432`. 

Real C: if the store 0x10 depends on something that's computed after... no. Or if I reorder the source so the store is emitted later/earlier.

Hmm. Let me look at the mine disassembly to see the exact order.

Let me dump v_two.
