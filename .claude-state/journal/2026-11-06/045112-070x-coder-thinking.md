---
ts: 2026-11-06T11:51:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SwZbPKVwclSROkPTz3XO
---
Priority is dependency-chain based (longest path). Both loads are independent (priority 1). So sched1's order of two independent insns... The scheduler in gcc 2.7.2: it processes the ready list, picks by priority then by "insn number"? For equal priority, it picks the one with the lowest insn number? Or the most recently added?

Actually the "birth order" issue: in sched.c, ready list ordering. Two independent loads with equal priority: it schedules the one that's "most urgent"? There's a `sched_analyze` and `schedule_block`. Let me look at how it picks among equal priorities.

Alternatively — maybe it's NOT sched1. The RTL before sched1 might already have xx first, and the target's RTL has zz first due to the launder's presence in the *expander* (the launder forces wz's materialization, changing the expansion order?).

Hmm, the loads are expanded in source order: xx, zz. So RTL has xx then zz. In the target, after sched1, zz comes first. So sched1 reordered. In v2, xx stays first. So the launder changed sched1's choice.

Why? The launder makes `wz` live longer. Hmm, sched1's `rank_for_schedule`: compares priority, then `INSN_REF_COUNT`, then... let me look.

Let me grep for rank_for_schedule.
