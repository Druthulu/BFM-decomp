---
ts: 2026-11-06T20:50:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YqZmLutFXn5SSUtSOfCg
---
Line 95: "life_analysis deletes insns whose only effect is to store a value [that is dead]" — so flow's life_analysis DOES delete dead insns. But the copy `87 = 72` is used by many insns — not dead.

Hmm, wait. Maybe the deletion isn't the copy's death but a *propagation* in life_analysis? Line 966: PUT_CODE... Let me look at lines 940-1000 (life_analysis's dead-store elimination).

Actually, line 1487-1493 is in `find_basic_blocks` (deleting unreachable code?).

Hmm. Let me look at lines 940-1000.
