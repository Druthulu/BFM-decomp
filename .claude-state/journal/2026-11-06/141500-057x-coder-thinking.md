---
ts: 2026-11-06T21:15:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_P565F1XYvc53qP1mO5ZE
---
So the dead set survives through jump1 and cse1, and is deleted by **combine**! w2.i.combine has 1. Interesting: combine removes the dead copy `rv = (s32)a0` because rv's value is already equal? Actually combine merges insn 99 (rv = a0) — a0 is reg/v:SI 72 (the pointer). Hmm, why would combine delete it? Maybe combine sees `rv = sp20` (insn 93) and `rv = a0` (insn 99) and... no, it shouldn't delete a set unless dead.

Wait, maybe it's cse2 (which runs after combine?) Let me check the pass order: in GCC 2.7.2, the order is: jump1, cse1, ... combine, ... then cse2? The dumps: .cse, .combine, .flow... The `.cse2` dump has 1. So combine or cse2 deleted it.

Actually, hmm: maybe the dead set is removed by `flow` (dead code elimination) which runs between cse1 and combine? The dump names: -df dumps flow, -dc dumps combine. The .flow dump has 1, .combine has 1. Both after deletion. The pass that deleted it is either combine or an earlier flow. Since .cse has 2 and .combine has 1, and .flow also 1 — flow might run between cse and combine.

In GCC 2.7.2 toplev.c rest_of_compilation order:
```
jump_optimize (insns, 0, 0, 1);          /* jump1 */
...
cse (insns, max_reg_num(), 0);            /* cse1 */
...
jump_optimize (insns, 1, 1, 1);           /* jump2? */
...
combine_instructions (insns);
...
```
Hmm, where's flow? Actually dead code elimination in 2.7.2 is `delete_dead_code` called from `flow_analysis`? Let me check: `flow_analysis` computes liveness; `delete_dead_code` removes. They're called by `cse`? Let me grep toplev.c.

Actually, the wall tag `flow-unused-result` says flow. But the dump shows the deletion happened between .cse and .combine (or at .flow which is printed by -df). The .flow dump is printed when the flow pass runs. If flow runs after cse1 and before combine, then flow deleted it. That matches `flow-unused-result`.

Hmm wait, but actually it might be that the `flow` dump is printed at the END (the -df flag prints after each pass? no, it prints when the flow pass runs). Let me just check toplev.c order quickly.

Actually, the important thing for the wall evidence is the mechanism, not the exact pass name. But the tag should be right. Let me grep toplev.c for the pass order.
