---
ts: 2026-11-06T21:01:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_i5wnJBzIWFhy8VXlEZTj
---
The TU is a spliced multi-function file; "common.h" is found via -Iinclude. Good — then a scratch copy anywhere works with `-Iinclude`. So I can copy the TU to my item dir, replace the function body, and run cc1_dumps_tu.sh on the .c file with DUMP_ROOT set under my shard dir. cc1_dumps_tu.sh uses DUMP_ROOT env: `${DUMP_ROOT:-.run/P32/t4e}/dumps_$tag`. Set DUMP_ROOT=.run/P40/T11/W49x/func_800CC4E8__md_MAIN_034/dumps.

But splicing: I need to replace lines 901..(end of function) with my body. Let me see the current function in src to find its extent.
