---
ts: 2026-11-06T21:14:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zJhAqiCZspmrdG2lIvfG
---
The .rtl dump (after expand) shows insn 99 `(set (reg/v:SI 79) ...)` — that's the `rv = (s32)a0` assignment. So it IS generated. And it's deleted before cse. The dump files: w2.i.rtl is the expand output; w2.i.cse is cse1 output (move gone). Which pass between? jump_optimize (jump1) runs before cse1, or the first `flow` (delete_dead_code)? Actually the pass order in toplev.c 2.7.2: after expand, `jump_optimize` (jump1) → `cse` (cse1) → ... and `flow_analysis`/`delete_dead_code`? Let me check. The `-df` flag dumps flow; but flow runs after cse? The dumps are named after the pass that ran. There's no "jump" dump flag? There is -dj (jump). The .jump dump exists. Let me check .jump and .jump2.

Actually the sequence in GCC 2.7.2 toplev.c rest_of_compilation:
```
if (optimize) { ... }
...
jump_optimize (insns, 0, 0, 1);   /* jump1 */
...
cse (insns, ...);
...
```
Hmm, and `delete_dead_code`? In 2.7.2, dead code elimination is part of `flow_analysis` + `delete_dead_code` called in `cse`? Actually the function is `delete_dead_code` called from `jump_optimize`? Let me not guess. Let me check the .jump dump for the move.

The point: the dead set is removed by the early dead-code elimination (flow/jump), not by a later pass. The wall tag `flow-unused-result` says "flow deletes results the target computes but never uses". That fits.

Let me verify by checking w2.i.jump (jump1 output) and w2.i.jump2.
