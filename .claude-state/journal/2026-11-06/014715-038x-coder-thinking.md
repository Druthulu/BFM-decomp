---
ts: 2026-11-06T08:47:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MxypdugbHXIcivT37l53
---
I can make a spliced TU with the candidate body and dump. The `--try --keep` gives a scratch TU at .run/P36/engine/score/<tu>__<fn>/p3/ov_SC02_000_jr_8018173C.c. I can pass that file to cc1_dumps_tu.sh with DUMP_ROOT under my item dir, then inspect .combine/.cse dumps to see the merge, then delete.

Let me do that for c1 (asm removed) to see which pass merges the copy. That'll tell me what to block.

DUMP_ROOT must be under my shard dir, absolute.
