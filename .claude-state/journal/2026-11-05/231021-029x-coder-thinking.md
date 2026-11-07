---
ts: 2026-11-06T06:10:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_panBzBsthOYFPN0iZz4h
---
The scratch TU is `.run/P36/engine/score/ov_SC03_029__func_801804A0/p3/ov_SC03_029_jr_8017FF7C.c`. I can dump it. Note: it's outside my shard dir but it's the tool's own scratch (allowed to use, and I must remove it after use — "`--keep` scratch is removed after use").

Let me copy that TU into my item dir and dump there (dumps must go under my item dir).

Actually cc1_dumps_tu.sh takes the .c file and writes to DUMP_ROOT. I'll set DUMP_ROOT to my item dir.
