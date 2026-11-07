---
ts: 2026-11-06T06:13:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fFOtdfraRt0Ui4CaE17s
---
No s0 in the whole function's .lreg section. So the conflict with hard reg 16 doesn't come from the .lreg RTL text.

Hmm... unless global.c records a conflict with hard reg 16 from `basic_block_live_at_start` — i.e., the *entry* block's live set includes hard reg 16 because... `function.c`'s `expand_function_start` may emit a note that $16 is live? Actually, in gcc 2.7.2, for functions with a non-local goto or setjmp, callee-saved regs are live at entry. Not here.

Wait, another thought: `record_conflicts` with hard regs — `IOR_HARD_REG_SET (hard_reg_conflicts[allocno], hard_regs_live)`. hard_regs_live is seeded from basic_block_live_at_start which includes *pseudos* renumbered by local-alloc: `else if ((a = reg_renumber[i]) >= 0) mark_reg_live_nc (a, ...)`. So if a local pseudo was assigned $16 by local-alloc, it's live in the block start. But we found no s0 in .lreg... because .lreg prints local pseudos as their hard reg? It should print `(reg:SI 16 s0)`. Hmm, we found none.

Hold on, maybe the .lreg dump is BEFORE local-alloc? gcc dump flags: -dl = local-alloc? The dump file names: .lreg, .greg, .sched, .sched2, .lreg is local-alloc output. Yes .lreg = after local-alloc, .greg = after global-alloc.

Hmm, so no $16 in local-alloc output. Confusing.

Let me look at the .greg section again more carefully — maybe the conflict line I read isn't for this function or the "16" is something else. Let me print the exact lines 1940-1970.
