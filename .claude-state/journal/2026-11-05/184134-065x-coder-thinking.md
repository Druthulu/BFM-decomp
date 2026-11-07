---
ts: 2026-11-06T01:41:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cbQfVFE4ObF4duQNGvAJ
---
The vA .jump dump has no insn 368 jump. So the jump was deleted in that pass. Let me look at the lines around where it should be (the tail I saw: insn 366 store, then note BLOCK_END, label 374). So the jump and barrier were removed. Which code removes a simple jump to the following label?

Look at line 2112: `delete_insn (insn);` in the FUNCTION_END scan — that's the note.

Hmm, maybe `delete_jump` at line 189? Let me read the beginning of jump_optimize (lines 160-260).
