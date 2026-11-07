---
ts: 2026-11-06T16:40:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZOJTAmBjs5obxJ2N5gs3
---
The residual without the launder: the `lw v1,0(s1)` (the load `*(u32*)p`) moved 7 insns late, and `lui a0,0xff00` took its slot — exactly cluster (b) described in the comment. The launder kills sched1's birthing boost so the load stays at its source position.

So we need a second SET of pv that survives to sched1 and emits zero bytes. 

Idea: make pv's second set part of a *dead but not deleted* construct. flow deletes dead stores to pseudos. But does flow delete a set to a pseudo that's also... hmm.

Alternative: `pv = 0;` placed where flow can't prove it dead? E.g., inside a conditional: `if (D_800A651C) pv = 0;` — adds a test (bytes).

What about `pv = 0;` in a loop? no.

Hmm, what about using pv in a way that's optimized away *after* sched1? No pass after sched1 removes dead code except sched2/reorg.

Wait: the launder is an *asm*, which is volatile and survives everything. The second set is in the asm's output operand. The asm emits zero bytes.

Real-C alternatives that survive flow with zero bytes:
- A volatile read? emits a load.
- A `static` variable? no.
- What about assigning pv to itself via a function call? no.

Hmm, what about making the second set *not dead*: use pv in the address of a memory reference that is the SAME as another (so no extra insn)? For example, if pv is used as the base of a load/store that already exists. pv is `*(u32*)p` = the tag word. After the ot store, could we use pv in a way that produces no instruction? 

Actually, look at the source: after `pv = *(u32 *)p;`, pv is used in the OR expression. Then at the end there's `func_80016638(...)`. If we add a use of pv as an argument to func_80016638, it would add a move (a0/a1/a2). The call takes 3 args: (&D_800A6518[...], 0x10, 1). Adding a 4th arg costs 0 bytes? The brief's C0505 says "a call passed at its REAL arity (the extra arg costs 0 bytes — jump2 deletes the no-op copy)". But func_80016638's prototype has 3 args; passing 4 to a prototyped function is an error. If declared K&R, extra args allowed → move a3,pv would emit a real instruction (move a3,?). Not zero.

Hmm. What about using pv in a *dead* comparison that fold removes but flow... fold runs before sched1 too. The order: cse, loop, cse2, jump1, flow1, combine, sched1. fold is part of jump1? Actually fold_rtx is cse; jump1 does jump_optimize. Dead code elimination is in jump1 (delete unreachable) and flow1 (dead stores). So anything provably dead before sched1 is gone.

What survives: a use whose deadness isn't provable. E.g., a store to a global of pv? That emits a store (bytes).

So: to create a 2nd SET of pv that survives to sched1 and costs 0 bytes, we need... an asm (lever) or a construct that expand emits as a zero-byte insn. 

Wait — what about a *conditional move* / a branch? no.

What about assigning pv from itself with a *volatile* intermediate? no.

Hmm, what about `pv = *(u32*)p;` twice? The second load emits bytes.

What about making pv's single set not single by using two different *expressions* that both set pv and are identical, with cse folding one? Then only one set remains.

The birthing boost applies to "single-set" registers. What counts? Let me read sched.c around 2469-2545 (the birthing boost).
