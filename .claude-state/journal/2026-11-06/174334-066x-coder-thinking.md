---
ts: 2026-11-07T00:43:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mxLnGZyXeMK03Efiiqo4
---
All ≥6. The ORDER issue persists in most. w14 (init at decl) is 8 with 68 ins (different).

Let me look at w10's diff: it's still ORDER. And w18 (p[0]=0) also ORDER.

Hmm, so the load placement is stubborn. Let me examine w10's diff to see if the order is the same as w1's.

Actually, maybe I should attack the ORDER differently: make the load's dependent chain longer so its priority is higher. Priority(load) = priority(dep) + cost - 1. If the load's result feeds something that feeds a longer chain, priority rises. In the target, val feeds addiu → sw (2 levels). If val also fed something else...

What if `val` is used in the *store address*? no.

Alternatively, change *which* register the load's result uses... no.

Hmm, what about the actual mechanism: "blocking insn 53 for 1 cycles" — the load was blocked by an actual hazard. `actual_hazard` uses the unit of the last scheduled insns. On MIPS1, the mips.md defines the cpu unit with a blockage of 1 for loads? Let me check what makes a load block: `function_units[unit].blockage` — for the "load" unit, blockage 1 means after issuing a load, you can't issue another insn for 1 cycle? That would be the load delay.

So after the call (which is a "memory" unit insn?), the load is blocked for 1 cycle, then the stores go, and after them the load is fine.

In the target (with the pin), the load has a hard reg $2 — hmm, but sched1 runs before register allocation! So the pin's effect at sched1 time: `register s32 val __asm__("$2")` makes the RTL use (reg:SI 2) directly, so the load's destination is a hard register. Does that change the hazard? `actual_hazard_this_instance` depends on the *unit* and possibly on `insn` (the insn being scheduled) — let me check whether it examines the destination register.

Actually, for the ORDER issue: w3 (barrier kept, pin dropped) had the right order. So the barrier is what fixes the order, not the pin. Let me confirm by checking the target's sched1 trace (with barrier): the asm blocks, changing the phase.

So: I need a real-C replacement for the barrier's scheduling effect. Since the asm's effect is to insert an insn between the load and the stores that blocks the pipeline for a cycle, changing the phase...

Hmm, what if the *real* original C had something between them that creates an insn... but the target has exactly 71 insns, same as mine. So no extra insn.

Wait — maybe the real original C's source ORDER is different: the load after the stores! And the target's schedule (load first) comes from sched1 hoisting it. In my w10 (source order: load after the stores), sched1 still gives ORDER 6 — meaning it did NOT hoist the load.

Hmm, so the target's order must come from the RTL order at sched1 being load-first with a phase that avoids the block. The barrier does that.

Let me look at the target's sched1 trace to understand exactly what the asm does. I can dump the *src* body (orig.c with barrier) — but that's the src file. I could dump the TU from src directly: tools/cc1_dumps_tu.sh src/ov_SC02_031/ov_SC02_031_jr_8017AE2C.c — it's a real TU, so it works. Dump to my item dir, then compare the sched traces.

That's the decisive experiment. Let me do it (25 MB, fine).
