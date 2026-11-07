---
ts: 2026-11-06T21:02:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rgMtUhaFmq3ieNvwKaQ8
---
So block 1: lhu $2 (load), addu $3 (sub), sll $2. The sub got $3, and the sll got $2. In the alloc table block 1 has r78 v0, r79 v0... hmm, that doesn't match. Maybe the alloc_table's "hard" is from the .greg dump for local pseudos? Confusing.

Let me look at the .lreg dump for this block to get the real allocation info.
