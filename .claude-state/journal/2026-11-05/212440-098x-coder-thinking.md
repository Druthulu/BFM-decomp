---
ts: 2026-11-06T04:24:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dhq4p9Q9pqTFFeKhCBt3
---
Same. So moving the p load after the add in source didn't change the schedule — sched still hoists it.

The reload is caused by cse: the raw 0x1A store kills the model load. Then p's load is a fresh load. Its position in the RTL (after the add) doesn't matter for sched1; sched hoists it.

What determines sched1's hoist? The load's priority. To lower it, maybe make the load's use further away or dependent on the chain. 

Idea: make the store's address computation depend on the chain by using the SAME register for the multiply's final result and the store's base? Not possible.

Idea: use a **do-while(0) around the multiply chain** so the p load is in a different EBB and can't be hoisted above the loop boundary. w6 did exactly that (do-while around the multiply at line 59) and got 14 — but did the p load stay after? Let me check w6's schedule. w6 wrapped the multiply only; the p load is after the do-while, so it's in a different block? The do-while's end note/branch is between them. sched1 shouldn't move the p load above the loop-end branch. Let me check w6's disassembly.
