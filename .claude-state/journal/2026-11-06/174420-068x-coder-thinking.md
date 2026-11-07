---
ts: 2026-11-07T00:44:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_027Rzi0WYxDGFlNQ3N7B
---
In the target's sched1 output: `(insn 53 50 55 ...)` — wait, line 299 is insn 53 (the val load) with dep on 50; then `(insn 55 53 58 (asm_input ("")) ...)` — the asm at 55 comes after 53, then 58 (first store).

So the target's order after sched1: 53 (load), 55 (asm), 58,61,64,67 (stores), 70... 

And the asm insn 55 has deps: `(insn_list 45 (insn_list:REG_DEP_ANTI 48 (insn_list 53 (insn_list 50 (nil)))))` — it depends on 45 (p=...), 48, 53 (the load!), 50 (the call).

Key: the asm depends on insn 53 (the load) — because the asm has no operands but `sched_analyze` adds deps for all live registers? For an asm with no operands, sched_analyze_insn treats it as using/clobbering... hmm, an asm with no clobbers shouldn't have deps. But the dump shows the asm depends on 53, 48, 45, 50 — i.e., all the preceding insns that define live registers. That's because an asm is treated as clobbering ALL registers? No... For a `volatile` asm with no clobbers, `sched_analyze_insn` calls `sched_analyze_2` on ASM_OPERANDS... Actually there's special code: "if (GET_CODE (body) == ASM_OPERANDS) ... it's a scheduling barrier" — let me check.

Anyway: empirically, the asm creates an anti-dependence chain from all live insns, forcing the load (53) to be scheduled before the asm, and the asm before the stores. That's how it fixes the order.

Real-C replacement: create a dependence that forces the load before the stores... but the stores must not depend on the load's *value* (the code is `sw zero`).

Hmm — what if the stores' *addresses* depend on a value derived from the load? No, they're absolute symbols.

Alternative: make the load's priority 2. The priority = max over dependents. If the load feeds an insn whose priority is 2, the load becomes 2 (with cost 1: 2+1-1 = 2). The load feeds insn 73/75 (addiu) which has priority 2 in mine? In mine: "insn[73]: priority = 2" and "insn[75]: priority = 2". So priority(load 53) = priority(73) + cost - 1 = 2 + 1 - 1 = 2! But the dump says insn 53 priority = 1.

Hmm, in my w1 dump: "insn[ 53]: priority = 1, ref_count = 2" and "insn[ 73]: priority = 2". So why is 53's priority 1?

Because the LOG_LINKS of 53 (its deps) are used to compute 53's priority: priority(53) = max over deps x of (priority(x) + cost - 1). Deps of 53 = insn 50 (the call, anti-dep). So priority(53) = priority(50) + cost - 1 = 1 + 1 - 1 = 1. The priority is computed from the *insn's dependencies*, not its dependents! I had it backwards.

So: priority(insn) = max over its predecessors (LOG_LINKS) of (priority(prev) + insn_cost(prev, link, insn) - 1). This is a "critical path length from the start".

So the load's priority is 1 because its predecessor is the call (priority 1). The stores' priority is 1 too.

Then the tie-break (potential_hazard / actual_hazard blocking) decides.

In the target, the asm forces the order via dependences.

Now, what real-C construct could make the load's priority higher than the stores'? Its priority comes from its predecessor chain: if the load depended on an insn with priority 2, it'd be 2. Its predecessor is the call (priority 1).

Hmm, the call's priority: insn 50 priority 1.

What if the load's address computation (lui v0,0x0) is a separate insn that depends on something with priority 2? The lui is a separate insn (the address). The load depends on the lui; the lui depends on the call (anti). Both priority 1.

OK, different approach: change the ORDER of the stores relative to the load in the RTL *before* sched1 so that sched1's blocking phase works out. In w10 (source: load after the stores), sched1 still ends with the load after the stores.

Hmm, what if the load comes before the *call* (init at decl)? w14 gave 68 ins (different) — the load was hoisted before the calls (wrong).

Let me think about the actual hazard mechanism more concretely: "blocking insn 53 for 1 cycles" — the load is blocked. Why? `actual_hazard_this_instance(unit, instance, insn, clock, cost)`: it looks at `function_units[unit].blockage` and the `last_scheduled_insns`? Let me read it.
