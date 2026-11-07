---
ts: 2026-11-06T05:21:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2eSAyF20oAfc3gjIK4P1
---
Not the dead-store code. The dead-store elimination for memory in cse 2.7.2 is likely in `cse_insn`'s "record the store and invalidate" or in the `invalidate_memory` logic. Actually, the dead-store elimination I'm thinking of might be in `flow.c`'s `dead_code` or in `combine`/`dce`.

Wait — GCC 2.7.2 doesn't have a separate DCE pass for stores. But it does have `flow_analysis` with `mark_used_regs` where stores to a *stack slot that is dead* are removed? Hmm, there's `delete_dead_insns` in flow.c? Let me grep flow.c for "delete_insn".
