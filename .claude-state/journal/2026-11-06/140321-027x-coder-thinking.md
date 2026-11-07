---
ts: 2026-11-06T21:03:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oyDD4gQKsTiFOibUN9jr
---
Only the TU and object, no dumps. I'll run cc1_dumps_tu.sh on that TU with DUMP_ROOT under my item dir. That dumps all functions in the TU (large). Then I grep for func_8017E590 in the .lreg dump.

Disk cap: dumps go under my item dir and I delete them after reading. Let me do it.

Actually, cc1_dumps_tu.sh dumps the whole TU with many functions — could be big but okay. Let me run it with DUMP_ROOT set to my item dir/dumps.
