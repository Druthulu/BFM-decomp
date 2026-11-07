---
ts: 2026-11-06T18:16:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6o1O41CLW4XLsPC3wR4A
---
The candidate TU is `.run/P36/engine/score/ov_SC04_018__func_80184B70/p3/ov_SC04_018_jr_80183E6C.c`. It's a shared scratch area (created by the helper), but I must not write there. I can read it. For dumps I'll use DUMP_ROOT under my item dir.

Run: DUMP_ROOT=.run/P40/T11/W48x/dumps_item3 tools/cc1_dumps_tu.sh <that .c file> t3. Wait the script does `d=${DUMP_ROOT:-...}/dumps_$tag; rm -rf "$d"; mkdir -p "$d"`. So DUMP_ROOT must be a directory that exists (or mkdir -p creates it). Use my item dir.

The TU copy path is outside my shard but reading is fine. However, the helper may delete the scratch after the call? --keep keeps it. It stays until "removed after use" — I should remove it after. It's a shared area, but the brief says --keep scratch is removed after use. I'll remove it at the end (that's a shared helper's scratch, presumably safe). Actually, careful: "write only under .run/P40/T11/W48x/". Removing a helper's scratch is arguably part of my use. I'll leave removal until after dumps, then rm -rf that p3 dir? Other coders might use the engine dir; p3 is specific to this call. Hmm, but maybe better not to touch shared. The instruction says "--keep scratch is removed after use" — so yes remove it.

Let me dump.
