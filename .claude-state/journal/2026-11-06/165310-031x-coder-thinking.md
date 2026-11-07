---
ts: 2026-11-06T23:53:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Qz5aZiB5wwCPL1wgQ7j9
---
33KB, over 20,000 chars. I can copy it with cp and splice with a script.

Let me create a splice script: read src/resident/resident.c, replace lines 936-1020 (the function) with my win.c body, write to my item dir as t_nopin.c. Then run cc1_dumps_tu.sh on it with DUMP_ROOT set to my item dir.

But note: cc1_dumps_tu.sh writes to ${DUMP_ROOT:-.run/P32/t4e}/dumps_$tag — I need DUMP_ROOT under my shard dir. The brief says hdump.sh needs absolute outdir; for cc1_dumps_tu.sh it's DUMP_ROOT env. Let me set DUMP_ROOT=/home/musashi/bfm-decomp/.run/P40/T11/G23x/func_800CFE60__resident.

Let me write the splice script.

Actually wait — is the effort worth it? The budget is 20-30 min per item and there are 4 items. I've used ~12 min. Let me time-box item 1 to 30 min, and if it walls, move on.

Actually, this is a "singleton crack shard" — the goal is to crack each. Let me spend a bit more.

Let me do the dump — it will tell me the allocno priorities exactly.

Plan:
1. splice win.c (the lever-free baseline, score 18) into resident.c → t_win.c
2. cc1_dumps_tu.sh with DUMP_ROOT my item dir
3. alloc_table.py on the .greg dump

Actually the baseline win.c is what I want (score 18, the s3/s4 swap + missing copy). Let me use G_nopin.c instead (launder kept, score 14) — that isolates the reg swap cleanly. Actually both have the same swap. Let me use G_nopin.c to see the allocno table with only the pin removed.

Hmm, but I want the lever-free one eventually. Let me dump G_nopin first.

Actually, simpler: dump the ORIGINAL (pinned) and G_nopin, compare. But let me start with G_nopin.

Let me write the splice script.
