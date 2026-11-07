---
ts: 2026-11-06T12:33:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QMj6QQJ9mUsHN8J4sjgv
---
So STORE (1e38) = `sh v0,2(s1)` (unk2 = ret) and the return epilogue at 1e3c. The arms jump to 1e38 with v0 = ret.

Note the arms jump to 1e38 (the store) while the early returns jump to 1e3c (the epilogue) — different labels, both in the target. In C, `return ret;` early would emit `j return_label`, and the STORE label is separate. Good.

Now let's see the arms' code in the target to understand the C. Let me look at 1b00-1b60.
