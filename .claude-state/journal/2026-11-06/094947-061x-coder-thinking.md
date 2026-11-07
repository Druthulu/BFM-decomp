---
ts: 2026-11-06T16:49:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uKRqgsdAeNd3MrkCB0Mz
---
The insn_number counts every insn in the block, not the RTL uid. Let me count the block's insn_number for each insn:
Block 1 insns in order: 20 (label, not counted? labels are not NOTE... code_label has RTX_CLASS 'i'? GET_CODE(code_label) = CODE_LABEL, GET_RTX_CLASS('i')? Let me count only real insns (GET_CODE != NOTE increments insn_number for all insns including labels/jumps? The code: `if (GET_CODE (insn) != NOTE) insn_number++;` — so labels and barriers count too.

Block 1: 
20 code_label → 1
22 note (skip)
28 note
29 note
47 note
57 note
23 insn → 2
30 insn → 3
25 insn → 4
35 insn → 5
37 insn → 6
39 insn → 7
41 insn → 8
33 insn → 9
45 insn → 10
46 insn → 11
49 insn → 12
51 insn → 13
53 insn → 14
55 call → 15
60 insn → 16
61 jump → 17

Births (2*insn_number):
- 78: born at insn 23 (n=2) → birth 4. Dies at 45 (n=10) → death ~19/20.
- 76: born at 30 (n=3) → birth 6. Dies at 35 (n=5) → death 10.
- 77: born at 25 (n=4) → birth 8. Dies at 39 (n=7) → death 14.
- 81: born at 35 (n=5) → birth 10. Dies at 37 (n=6) → death 12.
- 82: born at 37 (n=6) → birth 12. Dies at 39 (n=7) → death 14.
- 83: born at 39 (n=7) → birth 14. Dies at 41 (n=8) → death 16.
- 84: born 41 (n=8) → 16. Dies 45 (n=10) → 20.
- 86: born 45 (n=10) → 20. Dies 46 (n=11) → 22.
- 88: born 46 (n=11) → 22. Dies 51 (n=13) → 26.
- 89: born 60 (n=16) → 32. Dies 61 (n=17) → 34.

Tie groups:
- {76,81,82}: birth = 6 (76), death = 14 (82). nrefs = 4+4+4 = 12. life = 8. pri = 3*12/8 = 4.5.
- {77,83}: birth 8, death 16. nrefs 8. life 8. pri = 3*8/8 = 3.
- {84,86,88}: birth 16, death 26. nrefs 12. life 10. pri = 3*12/10 = 3.6.
- {78}: birth 4, death 20. nrefs 4. life 16. pri = 2*4/16 = 0.5.
- {89}: birth 32, death 34. pri = 2*4/2 = 4.

Allocation order: {76,81,82} pri 4.5 first, {89} 4, {84,86,88} 3.6, {77,83} 3, {78} 0.5.

Hmm, so the h group gets the first free reg. What's the first free reg in block 1? Live at start: 29($sp),30($fp),73(s0),74(s1),75(s2). Free: $2,$3,$4,$5,... The allocator's find_free_reg order... it picked $2 for the h group (mine). Then {89} → $2? No, 89 lives at the end; it can reuse a dead reg. Hmm.

The allocation is per-qty with live-range conflict checks: a qty gets a hard reg not live over its range. So the order matters but the ranges allow reuse.

For the target: {77,83} got $2 and {76,81,82} got $3. That would happen if the t group were allocated first. Its pri is 3 vs h's 4.5. So in the target the priorities must be different.

Hmm, unless the target's RTL has different live ranges: maybe the target's C has the h load *before* the t computation AND the h<<4 chain starts later? Let me look at the target's final .s order: sll a0(78); sll v0(77); lh v1(76); addiu s0; sll v1,v1,4(81); addu v1,v1,s2(82); addu v0,v0,v1(83); lhu a1(84); move a2,s1(74); addu a1,a1,a0(86); sll a1,a1,16(88); li a0; jal; sra a1; slti v0; bnez; sll a0.

The final order is a, t, h, s0++, h<<4, +s2, t+h, lhu, ... So the h load is at position 3.

But local-alloc runs BEFORE sched2/reorg. The order at local-alloc time is the sched1 order (a, h, t, ...) as we saw. In the target's original build, the sched1 order might have been a, t, h — giving different live ranges!

If the sched1 order were a, t, h, s0++, h<<4, ..., then:
- 77 (t) born at n=3, dies at the addu (later).
- 76 (h) born at n=4.
The priorities would be similar (life 8 vs 8), but t's group might have more... hmm.

Actually, the key difference: if the h load comes AFTER the t computation in the sched1 order, the h group's birth is later → shorter life → HIGHER priority. That's the wrong direction.

Hmm. Let me instead look at the actual sched1 dump to see if sched1 moved the h load. The lreg order is a(23), h(30), t(25) — sched1 moved h before t. If I reorder the source so sched1 keeps t before h, the order becomes a, t, h. Let me check the .sched dump to understand.

Actually, let me just try reordering the source (t before h) — that's w6_tlast (a, h, t) and w6_a_after_t (t, h, a) → both 8. Hmm, w6_tlast gave 8 (worse).

Wait, the current source order is a, t, h (the C). But the sched1 RTL order is a, h, t. So sched1 reordered t after h. To get the RTL order a, t, h, maybe I need a dependency change.

Let me look at the sched1 dump for the base to see the order before/after. Actually the .lreg dump reflects post-sched1. Hmm.

Let me try a different approach: maybe I can make the t group's priority higher by adding a *third* tied reg. The t group is {77,83}. If t's value were used in another computation that ties... 

Or: reduce the h group's nrefs. The h group {76,81,82} has nrefs 12 (3 regs × 4). If one of those regs weren't tied, the group would have 8 refs → pri 3*8/8 = 3 = t's 3. Then the qty number tie-break decides: the t group's qty number is lower (77 born before 76)? The qty is created when the first reg is born: 76 (h) is born at insn 30, 77 (t) at insn 25. Wait, in the RTL order, t (insn 25) comes AFTER h (insn 30)? No: the RTL execution order is 23 (a), 30 (h), 25 (t). So h is born (insn 30) before t (insn 25). qty numbering: 76 gets a lower qty than 77. So on a tie, h wins. Hmm.

If the order were a, t, h, then t's qty would be lower.

So maybe the real fix is to get the sched1 order to be a, t, h. Let me examine the sched1 dump to see why it reordered.

Let me look at base.i.sched (the dump after sched1? Actually -dS is sched, -ds is sched2?). The flags: -ds (sched2?), -dS (sched). Let me check which file shows the insn order after sched1. The .lreg dump is after local-alloc, which is after sched1. So the order a,h,t is post-sched1.

Let me look at the .rtl dump (before sched1?) to see the original order.

Actually, the C source order is a, t, h. The RTL order after expand/combine would be a, t, h. Then sched1 moved h before t. Why? sched1 orders by priority/dependencies. The h load is a memory op; the t computation is a shift. Maybe sched1 hoisted the load.

If the target's build had the order a, t, h at local-alloc, sched1 didn't hoist the load. What could prevent it? A dependency: if the t computation used h (or something). Hmm.

Alternatively, maybe the original C had `h` loaded *before* the loop (hoisted by loop.c?) no.

OK, let me look at the sched1 dump for the base to see the pre-sched order and the post-sched order. Let me grep the .rtl and .sched dumps.

Actually, let me try a targeted experiment: introduce a dependency that prevents sched1 from hoisting the h load above the t computation. For example, if the address of the h load depended on t? No.

Or: make the h load's address computation use s0 in a way... it uses s1.

Hmm, alternatively, maybe the answer is the same as item 2: a TWIN! Let me look for the twin of func_8017E9A0 in other overlays. The function name is ov_SC03_112_jr_8017C294 (jr_8017C294). Let me search for the same body with 0x19B (411) in src.
