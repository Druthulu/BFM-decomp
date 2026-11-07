---
ts: 2026-11-07T00:31:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fQViVjjN4dJmPFtjZsnq
---
That's cse_set_around_loop. The main store handling is in cse_insn (around line 7246/7265 area is the call handling). Let me look at cse_insn's writes_memory computation.
