---
ts: 2026-11-06T02:08:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8Du7OPgNTjik6L7hpsCL
---
delete_jump(insn): only deletes if single_set's dest is PC. Our jump has dest pc. delete_computation deletes the jump plus any preceding insn that computes a dead value (using REG_DEAD notes). So delete_jump on our jump would delete it and possibly the store if the store's value dies there! 

Which call site calls delete_jump with our simple jump? The condjump path at 664 requires condjump_p. Others at 1130/1299 are condjump paths. Hmm, but the hit shows delete_jump ← delete_computation ← delete_insn. The caller of delete_jump — let me get bt 4.

Actually, maybe the jump was turned into a RETURN insn by redirect_jump(NULL), and RETURN's single_set is... a RETURN pattern is not a SET, so delete_jump would not call delete_computation. Hmm.

Let me get the full backtrace for the uid-368 hit.
