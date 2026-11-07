---
ts: 2026-11-06T06:10:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5Dla2hSSmJzCWQnxU3Jk
---
Right: flow's depth comes from NOTE_INSN_LOOP_BEG. The goto version should remove that. Unless gcc's front-end still emits LOOP_BEG for a goto loop? No, it doesn't. But the score stayed 74 with the same register pairs. Maybe the depth weighting doesn't change the order here because live_length also changes, or maybe the do-while's LOOP_BEG placement is such that refs count... Hmm.

Wait — maybe my goto edit didn't actually remove the loop note because gcc's stmt.c emits LOOP_BEG for `do` only. My edit replaced do-while with label+goto, so no loop notes. Yet the allocation identical? Suspicious. Let me verify the change compiled: maybe the label/indentation broke something? Score same 281 ins. Let me diff my win.c with w1.c to confirm the edit.

Actually the scores being identical in every respect (same register pairs, same score) suggests the allocation decision is driven by something else — maybe live_length also shrinks proportionally.

Let me get the actual dump and alloc table. Use tools/cc1_dumps_tu.sh. Let me check its usage.
