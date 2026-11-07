---
ts: 2026-11-06T22:40:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_K7ufXJvey5qjbWtHG1hE
---
The difference: in w0, the pointer load is insn 16 and r72 dies there (REG_DEAD r72), and r81 is the pointer. In w6, the pointer load is insn 16 too but it has a REG_EQUIV note and r72 is NOT dead at insn 16 (the REG_DEAD r72 is at a later insn 184). So the tie between r72 and the pointer failed in w6 because r72 is still live after the lw.

Wait, why is r72 still live after the lw in w6? Because in w6, the loads `lh 14` and `lh 6` are scheduled AFTER the lw (w6 asm: lw first, then lh 14, lh 6). So r72 is used after the lw → not dead → no tie → the pointer gets $v0 and r72 stays $a0.

In w0, the target order has lh 14, lh 6, then lw (r72 dies at the lw) → tie.

So the scheduling order differs. The schedule depends on the pseudo/register... no, sched1 runs BEFORE register allocation. The RTL order at sched1 time is the same for w0 and w6 except the mask-in-place changed the s1ang def. Hmm, but sched1's ordering is influenced by the insn priorities/dependencies.

Wait, in w6 the lw is first (insn 16) — but in w0 also insn 16? Both have insn 16 = the lw. The difference is the ORDER in the final asm. Hmm, the lreg dump is after local-alloc; the insn numbers are the same. Let me look at the actual RTL order in the lreg dump around insns 4-20 for both.

Actually the asm output order is determined by sched2 (after reload) — the post-reload scheduler. w0's final order matches the target. w6's order has the lw first. sched2 reorders after register allocation, so the register assignment affects sched2's decisions. Hmm, but the *tie* (local-alloc) depends on the pre-local-alloc order (sched1).

Wait, in w6 the REG_DEAD r72 is at insn 184 (a later insn), meaning at the RTL level (after local-alloc), r72 is used after the lw. So sched1's order in w6 has the lh uses after the lw. In w0, sched1's order has the lw after the lh uses (r72 dies at insn 16).

So sched1 ordered differently between w0 and w6. Why? The only source difference is the mask-in-place (u6 eliminated, s1ang reassigned). That changes the dependency graph: in w6, `lh $17,18($2)` (s1ang) depends on the lw ($2), and the s1ang load... hmm.

Actually, in w0, the s1ang load `lh $16,18($2)` also depends on the lw. Both have that.

Hmm, the difference: in w6, s1ang is used later (7 refs, in the arms), so its live range extends, which may affect sched1? No, sched1 doesn't know live ranges of pseudos beyond the block.

Let me look at the RTL order directly. In w6's lreg dump, the insns around 16:
- insn 16: lw pointer
- insn 20: lh s1ang (depends on pointer)
- insn 59: lh 14
- insn 39: lh 6?

In w0:
- insn 16: lw pointer
- insn 20: lh s1ang
- insn 25: lh 14
- insn 39: lh 6?

Hmm, both have the lw at insn 16 before the lh's. The insn numbers are in program order after sched1? Actually the insn numbers are assigned before scheduling and don't change. The RTL order is the linked list order. Let me print the RTL order (the insn sequence) for both.

Actually, the REG_DEAD note position tells the truth: in w0, r72 is dead at insn 16 (the lw); in w6, r72 is dead at insn 184. Hmm, that's odd — the same source, but the liveness differs? 

Oh wait, in w6 the `lw` has a REG_EQUIV note: `(expr_list:REG_EQUIV (mem:SI (plus:SI (reg/v:SI 72) ...))`. This is because combine/cse created a REG_EQUIV. In w0 there's no REG_EQUIV. Hmm, why?

Hmm, w6 line 156-158: `(set (reg:SI 80) (mem:SI (plus:SI (reg/v:SI 72) ...)))` with REG_EQUIV. This suggests cse/combine handled it differently.

Let me look at the actual source of the difference. The mask-in-place `s1ang = s1ang & 0xFFF;` vs `u6 = s1ang & 0xFFF;`. In w6, s1ang is reassigned, so the load `s1ang = *(...)` and the mask are both defs of the same pseudo. This might create a REG_EQUIV for the pointer.

This is getting deep. Let me try a variant: keep `u6` as a separate variable but ALSO make s1ang global by *reassigning* it in a harmless way that doesn't change the code. For example:

```
u6 = s1ang & 0xFFF;
if (u6 == u5) return 0;
...
```
and use s1ang in a later block via a reassignment that is cse-merged:
```
s1ang = s1ang & 0xFFF;
```
right after u6? Then both are the same value; cse merges → s1ang = u6 (copy, coalesced). s1ang is then used in the arms (replacing u6). That's basically w6 but with u6 kept for the compare. Hmm.

Alternatively, reassign s1ang *without* the mask: `s1ang = s1ang;` — optimized away.

Hmm, what about: `if (u6 == u5) return 0;` then `iVar4 = u5 - u6;` then use `s1ang` (raw) in the arms with the mask:
```
if (iVar4 > 0x800) { t = (s1ang & 0xFFF) + 0x1000; ... }
```
The second mask is in a different block (multiple preds) → cse won't merge → s1ang raw is used in block 0 and block 3 → global. And the second andi is an extra instruction... unless it's in a block where the target has an andi? No.

Hmm.

Let me reconsider: maybe I should fix w6's scheduling issue instead. The problem in w6: the pointer load got a REG_EQUIV and r72 wasn't dead at it. Why? Let me look at the combine/cse dumps for w6 vs w0. Actually, let me look at the RTL order in w6 vs w0 around insn 16.

Let me print the insn sequence (the linked list order) in the lreg dump for both, around the first 20 insns. I'll grep the "(insn N" lines in order.
