---
ts: 2026-11-06T20:12:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_a3qT2ZbqRTpxUXAZRNrv
---
No `delete_dead_insns` in 2.7.2 — dead stores to locals are deleted only by `delete_dead_from_cse` after cse1 (and by combine/reorg later). So a dead insn added inside the loop would survive into loop.c and beyond; cse2 might delete it (cse2's `delete_dead_from_cse` is not called after cse2 in toplev — confirmed line 129 only jump_optimize). So the dead store would persist to combine and possibly be deleted by combine or by sched? It would appear in the final code as a `li` or be removed by `life_analysis`'s `delete_dead_insns`? Not present.

Hmm wait, but vD's dead store was deleted before loop.c (insn_count stayed 28). That's `delete_dead_from_cse`. Right.

So we can't add a dead insn before loop without it being culled.

But what if the dead insn is *not* deletable by delete_dead_from_cse, e.g., it's a call? A dead call would remain (side effects) and change code. No.

What about an insn whose destination is used by a later insn that is itself dead? delete_dead_from_cse iterates: it deletes dead insns and marks regs; it processes in a way that handles chains (`nreg`). Likely cascades.

What about a dead store to a *memory* location? Has side effects, survives, changes code.

Hmm.

Alternative: make `m->savings` or `m->lifetime` smaller. savings for a constant = 1 (computed as number of times the loop executes the insn... for a movable it's `savings = 1`? Actually in scan_loop: `m->savings = ...`? Let me look at how savings is computed: maybe `savings = n_times_used * loop_depth`? Let me check.

Let me look at scan_loop's movable creation.
