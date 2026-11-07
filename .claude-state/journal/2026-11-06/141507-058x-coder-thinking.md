---
ts: 2026-11-06T21:15:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HpF4M2YU3rqUqrmmUdNz
---
Line 2983: flow_analysis (with delete_dead_code presumably) runs before combine_instructions (3004). So flow deletes the dead set. Confirmed: wall tag `flow-unused-result` — "flow deletes results the target computes but never uses". 

Item 2: WALL, best 1, wall flow-unused-result, tries 34 (w1-w4 + t01-t30), evidence: "flow deletes the dead `move v0,s0` (rv=(s32)a0) in a void fn; only $2 pin+asm keep it (row kinds); lever-free 42/43".

Wait — but the result format: WALL requires best = lowest score of a lever-free body. w2 (both levers off) = 1. Good.

But hold on: could there be a PARTIAL with score 0? PARTIAL:keepalive means pin removed, keepalive kept → score 1 (w4). PARTIAL:pin means keepalive removed, pin kept → score 1 (w1). Neither scores 0. So no PARTIAL. WALL it is.

Time check: item2 started ~14:08, now maybe 14:25. Let me check date. Need ≥20 min for WALL. I started item2 around 14:08-14:10. Let me check now.

Let me record item 2. Also need notes.md for the item.

Actually, the brief: "Notes in <dir>/notes.md". Let me write notes for each item.

Let me get date and finalize item 2.
