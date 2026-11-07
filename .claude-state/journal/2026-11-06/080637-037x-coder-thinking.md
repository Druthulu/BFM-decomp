---
ts: 2026-11-06T15:06:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yi9tuLp9gZ1gkmpOIGWw
---
I need a spliced TU: the function body with a candidate, i.e. the whole TU with my body inserted. `--try --keep` gives the scratch TU file! The keep path prints the object; the scratch dir also has the .c. From the earlier keep: `.run/P36/engine/score/ov_SC03_090__func_80188498/p3/cand.o` — the scratch dir has the spliced src file. So I can use that TU file as input to cc1_dumps_tu.sh.

Let me do that for a candidate: orig (matching) and b4 (andi) to compare sched1 priorities. Dump to my item dir (absolute path under shard dir per the constraint).

Actually the constraint says "cc1 dumps (hdump.sh, cc1_dumps_tu.sh) go under your item dir and are deleted (rm -rf that dump dir) as soon as you have read them".

Let me get a scratch TU from a --keep run. Use b4 (score 2, the interesting one) and orig.

DUMP_ROOT env var controls output. It must be absolute under my shard dir.

Let me run --try --keep for b4, find the .c file, then dump.
