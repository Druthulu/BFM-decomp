---
ts: 2026-11-06T04:57:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jwmMKfoueCjLF1d0ytIE
---
Order: jump_opt, cse1, jump_opt, loop, jump_opt, cse2, jump_opt, thread_jumps, flow_analysis, combine, sched1, local_alloc, global_alloc.

So cse1 runs before flow's dead-store elimination. If I add a dead store that cse1 sees (invalidating memory), flow_analysis later might delete it as dead. Does flow_analysis do dead store elimination? gcc 2.7.2 flow.c has `delete_dead_jumptables`? Dead store elimination in 2.7.2 is in flow.c: `flow_analysis` does not do DSE; there's a separate `delete_dead_from_cse` (after cse) and `flow_analysis` handles dead code. Actually `flow_analysis` computes liveness and `delete_unreachable_blocks`, and there's `delete_dead_insns`? Hmm.

Let's search flow.c for dead store.
