---
ts: 2026-11-07T00:41:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uPXGQ1MwfeiAViGY06O3
---
This is the sched1 *result* (after scheduling) — the order shows the val load (insn 53) AFTER the four zero stores (56,59,62,65). So sched1 moved the load down.

Priorities: insn 53 (val load) has priority 1 (from the earlier list: "insn[ 53]: priority = 1, ref_count = 2"). insn 56/59/62/65 (stores) priority 1 each. So all priority 1 → sched1 keeps the *original* RTL order? No — the original order (before sched1) would be the source order: load 53 was born before 56? Let me check the .lreg/.rtl dump order. LUIDs: 53 < 56, so in the pre-sched order, 53 comes before 56. After sched1, 53 is after 65.

With equal priorities, why did sched1 move it? Because of the ready-list ordering: insns are added to the ready list as their predecessors are scheduled; a "birth" adjustment... There's the `adjust_priority` function and the SCHED_GROUP.

Hmm, key: insn 53's LOG_LINKS include REG_DEP_ANTI 50 (the call) — a dependence on the call insn 50 (anti-dependence: the call clobbers registers, so the load can't move above the call). And the stores 56,59,62 also have REG_DEP_ANTI 50.

So all are blocked by the call until the call is scheduled. Then they all become ready at once. The ready list order for equal priorities is LUID order... but sched1's ready list is a sorted list; when several insns become ready at the same time, `priority` equal → they're inserted by LUID (later ones appended). So the order should be 53, 56, 59, 62, 65.

But the output shows 56,59,62,65,53. So sched1 deliberately put 53 later. That's the "birth boost" / `adjust_priority` logic? Let me look at adjust_priority (sched.c:2507) and the ready-list insertion.

Actually, maybe it's the *sched2* pass that produced this final order, not sched1 — the .sched dump is sched1's output; sched2 later (.sched2). The listing here is sched1's output, which already has 53 after 65.

Let me look at the sched1 input order (.lreg dump) to confirm the source order: in the .lreg dump, insns 53,56,59,62,65 in LUID order (53 first). Let me verify.

Actually, an important detail: the .sched dump shows `(insn 56 50 59 ...)` — the chain is 56's prev=50, next=59. And 53: `(insn 53 65 68 ...)` — prev=65. So after sched1, 53 is between 65 and 68.

So sched1 moved the load down. Why? Because its priority is 1 but its *dependents*... hmm, priority of 53 = 1. Priority of 73 (addiu) = 1. Everything is 1. So the ready-list tie-break must favor the stores.

Ah — I bet it's the "birth" concept in `schedule_insns`: `birth` = the LUID; and in `ready_add`, ties are broken by `INSN_LUID`? Let me look at the ready list code (sched.c:2370-2450).

Hmm, but there's something else: the `adjust_priority` function, called when an insn becomes ready: it can RAISE the priority of a "prev" insn... Let me read it.

Actually, let's step back: what matters is the empirical result — the barrier (an empty asm) keeps 53 before the stores. Since asm insns have priority 1 and LINK_COST_FREE, they act as a barrier for *reordering*: sched1 can't move insns across an asm because it creates dependencies? An empty asm with no operands has no dependencies... but sched.c's `sched_analyze_insn` treats an asm specially: for an asm, it adds dependencies? Let me check: in sched_analyze_insn, `if (GET_CODE (body) == ASM_OPERANDS || ...)` — it calls `sched_analyze_1/2`... For an asm with no clobbers, there are no deps. Hmm, but there's a special case: `/* ASM_OPERANDS and ASM_INPUT don't have any special handling */`.

Hmm, but actually, `insn_cost` sets LINK_COST_FREE for asm as the consumer... 

OK, let me look at the *real* mechanism differently: I want a real-C construct that keeps the load before the stores in sched1's output. 

Options:
(a) A data dependency: make a store's *address* or value depend on the load. In the target, the stores are independent (sw zero). But maybe the target's source has a dependence we can't see? No — the target's order has the load first, and sched1 preserved it.

(b) A different *birth order*: the load's LUID earlier than the stores. It already is (53 < 56).

Hmm, so with equal priorities and earlier LUID, why did sched1 place it after? Let me read the ready-list tie-break.

Let me look at sched.c around 2370-2450.
