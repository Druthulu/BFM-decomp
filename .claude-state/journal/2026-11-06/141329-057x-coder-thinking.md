---
ts: 2026-11-06T21:13:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_g7PiCx87Adg09Ms7glpb
---
No life dump. -dL maybe not producing a file. 

Let me look at the .greg dump's disposition section: maybe it shows reg_renumber for each pseudo, which tells me the order isn't the issue but the register choice. Actually line 4 gives the order.

Let me focus on the order: 78 108 117 74 127 150 76 95 141 73 128 79. e=79 last. Let me understand why. Let me compute live lengths from the flow dump. The flow dump (cand.i.flow) shows live info? Let me check if it prints reg_live_length. Actually flow.c line 2889 `i, reg_n_refs[i], reg_live_length[i]` — that's under some debug flag. Let me see line 2880-2895.
