---
ts: 2026-11-06T10:07:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MJVkL0mJ9OjUXTWrxZby
---
There's a spliced TU copy at p3/ov_SC03_121_jr_8017E1D0.c. I can dump it. Disk has 31G free, not 4GB — the brief said ~4GB free but df says 31G. OK, still be careful.

Let me dump the -dg (global alloc) pass for this TU with w1.c's TU. Actually p3 contains the last --try candidate (wk.c for item 1, or w1.c for item 4?). The last --try on item 4 was wk? No, for item 4 I ran --keep on w1.c then later sc.sh on variants (sc.sh doesn't --keep). The p3 dir is per-function, and the last --try with --keep for func_80180E64 was w1.c. Then sc.sh ran --try without --keep, which probably overwrote... let me just re-run --try --keep with the v0 variant to get a fresh TU.

Actually, better: let me create the spliced TU myself? The --keep route is easiest.

But wait, the item dir's `tu` is the source file. The candidate TU is the source with the body replaced. Let me re-run --keep on v0.c (item 4).

Then run cc1_dumps_tu.sh on that file with DUMP_ROOT under my shard dir.

Let me do it.
