---
ts: 2026-11-06T11:50:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_joXxWJEcBW8oucGdMj6u
---
The scratch TU has the candidate spliced. But that's from the last --keep run (v2? no, the last --keep was v2). Actually I ran --keep for v2. But then I ran sc.sh on s1,s2,s4 which overwrote... no, --keep only keeps for that invocation; sc.sh without --keep removes its scratch. The p3 dir still has the v2 TU (from the --keep run). Good.

Let me dump sched1 for this TU and look at the region. The dump is big; I'll grep the .sched file around the insns. Let me run cc1_dumps_tu.sh with the TU file.

The tool writes to ${DUMP_ROOT:-.run/P32/t4e}/dumps_<tag>. I need DUMP_ROOT under my item dir. Let me set DUMP_ROOT=<itemdir>/dumps and tag=sched.

Note: this compiles the TU; it takes a while (~seconds).

Then look at .sched1 (or .sched) for the loop body. Let me do it.

Also, I should compare with the target's sched1 (orig.c body, which matches). Two dumps: one for v2, one for orig. That's more work but decisive.

Let me first dump v2.
