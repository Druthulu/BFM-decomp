---
ts: 2026-11-06T11:40:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_C7JkhTP2TN8njflDHmGN
---
That's cse_around_loop for loops, not a general EBB split.

Let me look at how cse1 processes the CFG — `cse_basic_block` and the main loop in `cse_main`. Actually the key is `cse_basic_block` follows EBBs. Let me check where the table is flushed at a label.
