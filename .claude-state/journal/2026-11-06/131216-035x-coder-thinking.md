---
ts: 2026-11-06T20:12:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pzFHKBXGl7k2gw1YgK4s
---
After loop.c: cse2 (no delete_dead_from_cse after cse2 apparently — line 129: `if (tem) jump_optimize`), then flow_analysis (life), combine, sched, local_alloc...

`flow_analysis` computes life info but does it delete dead insns? In gcc 2.7.2, `flow_analysis` → `life_analysis`? The `-dS`? Dead code deletion: `delete_dead_insns`? Let me grep flow.c for "delete".

Actually in gcc 2.7.2, dead code elimination happens in `jump_optimize`? No. `delete_dead_from_cse` is the main one. Hmm, so a dead insn added would survive cse2 (cse2 may delete it via cse's own `delete_dead_from_cse`? no, that's only after cse1).

Wait, but flow_analysis with `-dS`? Let me grep for `delete_dead_insns` across the tree.
