---
ts: 2026-11-06T11:53:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Ff22Xt58fB6sysWXg4ji
---
This is the sched dump (before scheduling?) showing the RTL order:
- insn 114: load from -8 (reg 93) = wy
- insn 109: load from -4 (reg 94) = wz
- insn 111: lshiftrt reg 95 = wz>>16

Interesting: the RTL order here is 114 (-8) then 109 (-4). So the expander emitted -8 before -4 (source order: wy after wz? no).

Hmm wait, the source has `wz = part->zz;` (2830) before `wy = part->yy;` (2831). But the RTL has insn 114 (-8, wy) before insn 109 (-4, wz). Hmm, so -8 is wy and -4 is wz, and wy's load (114) precedes wz's (109) in RTL numbering... but insn numbers don't reflect order (the "prev next" chain does: 114's prev is 102, next is 106; 109's prev is 125, next is 133).

The chain order: 99 → 102 → 114 → 106 → 123 → 125 → 109 → 133 → 136...

So the RTL order is: load -8 (114), lshiftrt of 92 (106), add (123), lshiftrt 93 (125), load -4 (109), add (133), stores...

Hmm, this is the .sched dump which is *after* sched1? The dump suffix .sched is after sched1. Let me check whether it's before or after. gcc's `-ds` dumps after sched1. So this IS the scheduled order.

So after sched1: 114 (-8) comes before 109 (-4). That matches mine (yy first).

Now let me dump the ORIG (target) TU's sched and compare. I need the target's sched dump. Let me create a scratch TU with orig.c (which is the current src = target) and dump.

Actually the target build object is compiled from the current src. I can dump the current TU directly: tools/cc1_dumps_tu.sh src/ov_SC03_103/ov_SC03_103_jr_8017C294.c tag. That's the target's dump.

Let me do that (in my item dir).
