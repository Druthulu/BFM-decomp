---
ts: 2026-11-06T18:34:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZeGuscyYWB0Gt9FEJO8n
---
LAUNCH_PRIORITY = 0x7f000001. So insn 55 has launch priority. Let me look at where LAUNCH_PRIORITY is set: in `schedule_insn`/`adjust_priority`, when an insn has a dependency that requires launching early: `adjust_priority (prev)` — if an insn is the only use of a value that dies... Let me read the code around adjust_priority.
