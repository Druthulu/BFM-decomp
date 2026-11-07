---
ts: 2026-11-06T05:22:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xv6KqhA8teLxN8GanJtI
---
This is cse recording destinations. The dead-store deletion is likely in `cse_insn`'s `invalidate_memory` / when a store is recorded, the previous store's equivalence is invalidated, and later `delete_dead_from_cse`... Hmm.

Actually, maybe the store removal is in `cse.c`'s `cse_insn` at line 7821: "if (GET_CODE (dest) == MEM)". Let me read around 7800-7900.

Time check: item 3 at ~22:30 (12 min). Let me not go too deep into the source. Let me instead take the empirical route with the struct/scalar mixed aliasing idea.

Actually — an important realization: the stores in question are to a *local stack array* `b`. cse's `in_struct` flag (line 7368) depends on MEM_IN_STRUCT_P! And `delete_dead_from_cse`... hmm.

Let me look at line 7821.
