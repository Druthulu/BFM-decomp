---
ts: 2026-11-06T01:36:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uiDXNrO8IIm3z3s1tSUG
---
I can use cc1_dumps_tu.sh on a TU file. But the item is a whole TU (src/ov_SC03_007/ov_SC03_007_jr_80183894.c) with the function inline. delever_search --try --keep gives the scratch candidate TU (p3/cand.o) — but the scratch dir may have the .i/.c. Let me check the scratch dir contents.

Actually simpler: use `--keep` and look at the scratch dir: /home/musashi/bfm-decomp/.run/P36/engine/score/ov_SC03_007__func_80184E8C/p3/. Let me look.
