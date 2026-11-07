---
ts: 2026-11-06T13:38:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0uXLY1cWSPQf50ogajiV
---
v01_dw_cc scores 0! The do-while around `cc = bb + 8;` splits cse1's EBB so sched1 keeps the load after the cc computation. Excellent.

So item3 MATCH: replace the barrier with `do { cc = bb + 8; } while (0);  // !FAKE: do-while`.

Let me bank win.c and verify, then record.
