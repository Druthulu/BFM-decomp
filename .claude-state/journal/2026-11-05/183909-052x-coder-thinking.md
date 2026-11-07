---
ts: 2026-11-06T01:39:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zwUwHA3mB3Ngu2qtVtJD
---
Key: the first jump pass (2827) runs right after expansion with `after_regscan=1` and cross_jump=0. It deletes jumps to next. So zero's return jump would be deleted there.

BUT: there's an important subtlety in jump-to-next deletion: it requires the label to be the next nonnote insn AND ... let me read the code in jump_optimize around "delete jumps to next". Maybe it's guarded by whether the jump's target label is the immediately following label. If the store comes after the jump? No.

Hmm, wait: in C, `return;` at the end emits `emit_jump(return_label)` right after the store. The return_label is placed at the end of the function by expand_function_end. Between the jump and the label, there may be NOTE_INSN_BLOCK_END etc. (skipped). So deletion applies.

But actually, gcc's jump-to-next deletion: "delete_insn" of the jump when target is next. Let me read that part of jump.c.
