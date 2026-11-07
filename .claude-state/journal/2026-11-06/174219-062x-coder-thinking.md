---
ts: 2026-11-07T00:42:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wIkdpDaIA9vjMUKLpZYD
---
potential_hazard depends on `unit_n_insns[unit]` — the number of insns already scheduled in that unit. And `blockage_range`. So the tie-break depends on the unit usage counts. For a load vs a store, the units differ (load unit vs store unit?) and the counts.

This is deep. The practical approach: find a real-C move that changes which insn wins. Since the target has the load before the stores and mine has it after, and both have the same instruction multiset, the difference must be in `unit_n_insns` counts or the ready order at that point.

Hmm, wait. Actually — maybe the difference is elsewhere: in the target's RTL (pinned), insn 53's priority might be higher (2 instead of 1), which would put it first. With the pin, `val` is $2 (a hard reg), and the load's dependent chain may differ.

Actually, remember w3 (barrier kept, pin dropped): the order was RIGHT (load at 32). So the barrier alone fixes the order without the pin. So the order issue is solvable without the pin — the barrier does it. But the barrier is a lever we must drop.

And with the barrier dropped, the pin doesn't fix the order (w2 = 6, ORDER).

So I need a real-C replacement for the barrier's scheduling effect.

The barrier (empty asm) — what does it do in sched1? An asm insn: `sched_analyze_insn` for ASM_OPERANDS adds dependencies for the clobbered/used regs. With no operands, no deps. But the insn's `insn_unit` — for an asm, `insn_unit` returns... the default unit. Hmm, and `actual_hazard`/`queue_insn`.

Hmm, but more importantly: does the asm change the ready-list ordering? Since the asm is scheduled at some point, and after scheduling it, `last_scheduled_insn` = the asm, and the class tie-break for the next insn depends on the relationship to the asm.

Alternatively, the asm may *block* the stores: `actual_hazard` for an asm insn is nonzero? An asm might block the pipeline for several cycles → the stores get queued (blocked) → the load gets scheduled first. That's plausible: `actual_hazard_this_instance` uses `function_units[unit].blockage` for the *last* insn's unit.

OK. Rather than reverse-engineer further, let me think about the real-C constructs that change this:

The tie-break is `potential_hazard` among equal-priority insns, which depends on `unit_n_insns[unit]` (how many insns already scheduled for that unit). So if I change the *number of prior loads/stores* in the block, the counts change. But the block's contents are fixed by the target.

Alternative: change the *priority* of the load so it's > 1. Priority = max over dependents (priority(dep) + cost - 1). The load's dependent is addiu (73) → priority 1 + cost(load) - 1. If insn_cost(load) = 2, the load's priority would be 2. The dump shows priority 1 for insn 53, so insn_cost returned 1 (MIPS1 default latency 1 for a load in this compiler config?).

Hmm, but in the TARGET's RTL (pinned), what's the load's priority? If the target's load also has priority 1, then the tie-break (potential_hazard) put it first there. Since the target's block is otherwise identical, the tie-break should be the same...

Unless the barrier changes the unit counts. With the barrier asm scheduled between the load and the stores, the "last_scheduled_insn" and unit counts change.

Hmm, let me look at the actual difference in the *ready list*: maybe without the barrier, the load is scheduled early but then *reorg* (dbr) or sched2 moves it down. Wait — the .sched dump already shows it down, and that's sched1.

Let me examine the sched1 dump more: the dump prints ";; blocking insn ..." messages and the final order. Let me look at the dump text before the insn listing for the case-0 block to see the scheduling decisions (the dump file may include ";; insn X has a greater potential hazard").

Let me grep the region for "potential hazard" / "blocking".
