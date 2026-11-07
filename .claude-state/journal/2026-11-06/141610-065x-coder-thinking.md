---
ts: 2026-11-06T21:16:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_B2RNcQKaAkcTron2LyEQ
---
The flow dump contains MULTIPLE functions' dumps (the TU has many functions). Line 12-42 is func_8017E590 (the first function). Line 1019+ is a later function (func_8017E7DC). So for func_8017E590: reg 79 used 2 times across 4 insns; reg 95 used 3 times across 8 insns. That's the relevant data.

So e (79): n_refs=2, live=4 → pri 0.5. off (95): n_refs=3, live=8 → pri 0.375. e > off. Yet order has e last. Contradiction!

Unless the "regs to allocate" order is NOT sorted by priority but something else. Let me re-read: `allocno_order` is sorted by allocno_compare. Let me check the sort call and direction. Line ~560. Let me read.
