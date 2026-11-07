---
ts: 2026-11-06T12:29:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_E9KQD6X5T1EoFSSgOUnt
---
Line 320 and 322: "empty do-while after the loop call (reorg fills beqz slot from target)" — the technique: an empty `do { } while (0)` AFTER the loop call (i.e., at the end of the if arm) makes reorg fill the beqz slot from the target! That's a lever-free crack of exactly our situation (G28x/G28y, barrier,pin items).

So: add `do { } while (0);` at the end of the if arm (after the call), which stops the reorg scan of the fall-through thread. Let me check the actual worked example from G28x... The shard dirs may still exist: .run/P40/T11/G28x/func_80187EA0/? Let me check for a win.c there.
