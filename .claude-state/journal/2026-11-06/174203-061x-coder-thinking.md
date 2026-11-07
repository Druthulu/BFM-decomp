---
ts: 2026-11-07T00:42:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qmCACLyUFyLIXHuCs8ha
---
`schedule_select`: among equal-priority ready insns, it picks the one with the largest `potential_hazard`. This is the tie-break that overrides LUID! So the order among equal-priority insns is decided by `potential_hazard`, not LUID.

potential_hazard computes, for the insn's unit, the hazard cost against the "last scheduled" insns. For a `lw` (load) vs `sw` (store) on MIPS1: potential_hazard(unit, insn, 0) considers the unit's hazard list (e.g., a load has a 1-cycle delay before the result is usable, and a store...).

So the load's potential_hazard vs the store's decides. In our case the stores win (scheduled first).

Hmm — so this is a "hazard tie" ordering. The wall tags list "sched1-load-delay-fill", "sched2-unit-hazard", "sched1-ready-order".

So how do we change it with real C? The hazard is a function of the insn type/unit, not the operands... `potential_hazard (unit, insn, 0)` — let me read it; it may consider the registers (a load's hazard depends on its destination register being used soon).

Let me read potential_hazard and actual_hazard.
