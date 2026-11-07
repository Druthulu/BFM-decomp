---
ts: 2026-11-06T12:07:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_chPJCybaYO8hjjraHPop
---
v_s8_store_dw (do-while around the store, but no do-while around `two=2`): 
- The store sink is FIXED (store at 29 now, since the diff no longer shows the store move). 
- But two issues: (a) `li v1,2` hoisted to insn 3 (instead of 5), and (b) `li a0,2432` moved one slot later (31 vs 30).

So the do-while around the store fixed the store but changed the li schedules.

Now, v_s8_dw_two (do-while around two=2) fixed the li v1,2 order but left the store sink. Combining BOTH do-whiles: v_s8_both_dw was tested = 2 (same as v_s8_dw_two). Hmm, so both do-whiles didn't fix the store.

Wait, v_s8_both_dw = 2. Let me check its diff — maybe the store is fixed but something else. Let me dump it.

Actually, v_s8_both_dw was `do{two=2;}while(0)` + `do{store}while(0)`. Score 2. Let me see the diff.

Let me dump v_s8_both_dw.
