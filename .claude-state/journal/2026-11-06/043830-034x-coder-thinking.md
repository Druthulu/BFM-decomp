---
ts: 2026-11-06T11:38:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eo3vQtfqW1LQWcPn9FId
---
Let me look at the priority() function and how blocks are delimited (`schedule_block` called per basic block? and sched_init). Let me look at where sched1 runs: schedule_insns loops over basic blocks; for a block with no jump at end? Let me read around 3200-3280.
