---
ts: 2026-11-06T20:49:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FQfiKQOlYMWiYYyOlVUA
---
The combine dump shows the copy insn 92 as a deleted note. So combine (or a pass before it) deleted it and rewrote the uses.

Hmm, wait: between cse2 and combine, the passes are: jump_optimize(2) (after cse2), thread_jumps, flow_analysis, then combine. jump_optimize could do... no. flow_analysis: `life_analysis` in flow.c — does it do dead code elimination? Let me check `flow_analysis` in flow.c: it calls `find_basic_blocks`, `life_analysis`, and maybe `delete_dead_insns`? Earlier grep found no delete_dead_insns. But there's `flow_analysis` → `life_analysis` which has:

Actually, in flow.c there's `life_analysis` and at the end it may call `delete_dead_insns`? Let me grep flow.c for "delete_insn" or "NOTE_INSN_DELETED".
