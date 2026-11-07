---
ts: 2026-11-07T00:31:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vWzjGHIaS5kSY2lQ6trj
---
So `invalidate_from_clobbers(&writes_memory, x)` is called with writes_memory computed earlier in cse_insn. Let me find where writes_memory is filled in cse_insn (note_mem_written call).
