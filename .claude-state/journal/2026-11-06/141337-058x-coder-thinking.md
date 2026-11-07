---
ts: 2026-11-06T21:13:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2F7ddiDQwQJcLubfN441
---
dump_flow_info is called in flow.c line 388 — likely when `flow_dump` is set by -df? The .flow dump file (cand.i.flow) should contain it! Let me grep the flow dump for "Register 79 used".
