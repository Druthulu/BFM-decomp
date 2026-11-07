---
ts: 2026-11-06T21:43:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Rinz6jF6ZjwQOCVCbUM6
---
I can dump the current v0.c by passing the file directly. But it needs to be a full TU (a .c file) — v0.c is only a body. The tool says the first arg may be a .c FILE (a spliced TU, a --try scratch copy). v0.c is a body only, so cpp would produce nothing. I need a spliced TU. The scorer's scratch dir has `ov_SC06_029_jr_8017C954.c` in p4 (the full TU with the body spliced!). At .run/P36/engine/score/.../p4/ov_SC06_029_jr_8017C954.c. That's from the --keep run. I can dump that. But DUMP_ROOT must be under my shard dir.

Let me run cc1_dumps_tu.sh with that TU and tag, DUMP_ROOT under my item dir. Then alloc_table.py.

Wait: "hdump.sh needs an absolute <outdir> under your shard dir" and "cc1 dumps go under your item dir and are deleted". cc1_dumps_tu.sh uses DUMP_ROOT env. Let me set DUMP_ROOT to my item dir/dumps.

Let me do it.
