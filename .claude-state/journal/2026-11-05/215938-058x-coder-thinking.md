---
ts: 2026-11-06T04:59:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CztaSfvc4SpjfoJAxdTl
---
r1 (if wrapped) gives the same 38 as q1. r2 (only sites 1,2) also 38. Interesting — so even wrapping only sites 1 and 2 gives 111 ins / 38.

Wait, r2 wraps stores at lines 5 and 12 (sites 1,2) but not 19 (site 3). Still 38/111. And r1 wraps the ifs (not the stores) — also 38/111. Hmm, so the if-wrap also fixed the order? That means the block boundary from the do-while around the if also prevents the hoist.

But both have the same remaining score 38 and 111 ins. The 3 missing insns are the third block's reload, and the s0/s1 swap.

Let me diff r1 to see if it's the same as q1.
