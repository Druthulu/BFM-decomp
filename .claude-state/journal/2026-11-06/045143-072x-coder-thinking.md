---
ts: 2026-11-06T11:51:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oyRmGuvCNlOl6FBHyGNc
---
v3 (barrier gone): the code is 795 insns (2 more). Differences: `addiu s8,sp,236` vs `addiu s7,sp,236` / `addiu s7,sp,240` vs `addiu s8,sp,240` — the two addresses swapped registers (s7/s8), and the target has `addiu s8,sp,236` before `addiu s7,sp,240`, mine has s7 then s8. So a scheduling/ordering of two addius.

So the barrier (empty volatile asm) affects the ordering of two address computations (sp+236 and sp+240) and their register assignment (s7/s8).

Hmm. The barrier is in the `if (lim >= g.otz)` block. The addresses sp+236 and sp+240 are `&sxy[3]`? or `&box[7]`? These are loop-invariant computed before the loop.

The barrier's presence somehow orders them.

Hmm, so both levers are scheduling/ordering levers.

Let me reconsider: v2 (launders gone) = 3, one insn out of order. v3 (barrier gone) = 42 with several diffs. v1 (both) = 45.

Best approach: crack v2's single ordering. That gives PARTIAL:barrier at 0. Then separately crack the barrier.

For v2's single insn: the target has `lw a1,-4(s1)` before `lw v0,-8(s1)` and `srl a2,a1,0x10` right after. Mine has them later.

Since rank_for_schedule uses INSN_LUID (source order) for ties, the RTL order in the target must be zz-then-xx. That means the *expander* emitted zz's load first. Which would happen if the C source had `wz = part->zz;` before `wx = part->xx;`. But v7 did that and still gave xx first!

Unless... the launder changes which variable is loaded first? Hmm.

Wait, maybe my assumption about which load is which is wrong. Let me determine the offsets. Let me find the Part struct definition.
