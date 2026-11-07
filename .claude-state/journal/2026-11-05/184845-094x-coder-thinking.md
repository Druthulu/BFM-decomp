---
ts: 2026-11-06T01:48:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UYNmje4pfBFaLkExUcIn
---
Pass order: global_alloc, then sched2 (if flag_schedule_insns_after_reload), then jump_optimize(cross_jump=1) at line 3142, then... reorg? Where is dbr (reorg) relative to jump2? Let me look further after 3142. The brief's helpers dump -dd = dbr (reorg). Let me check toplev for "dbr" / reorg pass.

Actually, in gcc 2.7.2 the delayed-branch scheduling (reorg.c) is invoked from final? No: `dbr_schedule` is called in toplev after jump2? Let me grep.
