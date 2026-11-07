---
ts: 2026-11-06T11:50:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nJZ6ws4AkevRVV3ZB25Y
---
Item 1 done: PARTIAL:barrier, best 0.

Now write results row, moves.md line, notes.md. Then item 2.

results.tsv row format: dir file func kinds result best tries wall evidence (tabs).
dir = func_80015B6C__800, file = src/800.c, func = func_80015B6C, kinds = barrier,launder, result = PARTIAL:barrier, best = 0, tries = ~60 (I scored: 4 (v0,v1,v2 + orig) + 36 + 8 + 16 + 16 + 2 + 4 + 3 = ~89). Let me count roughly: orig 1, v0 1, v1 1, v2 1, sweep1 36, sweep2 8, gen3 16, gen3w 16, p1/p2 2, p3/p4 2, p5-p8 4, p9-p11 3 = 91. Say 91.

wall = a tag: the barrier that can't be dropped → `sched1-load-order`? Hmm, for a PARTIAL the wall field = "a tag from walls.txt or a new <pass>-<what>". The mechanism for the kept barrier: sched1 hoists the h_ load + y-add chain above the x stores when the EBB isn't split. Tag: `sched1-load-order` (exists). Good.

evidence ≤ 140 chars: "sched1: without the pre-y+=h_ asm barrier the lw h_/addu s2 chain is scheduled above the three x stores; s16 vx,vy forced the copies (launders gone)".

Now append the row. Must be a separate command (one action per command).

Then moves.md append: `barrier,launder | func_80015B6C | PARTIAL:barrier — s16 vx/vy widths force both corner copies (launders gone); sched1 hoists lw h_ above the x stores without the pre-add barrier (G30)`.

And notes.md.

Let me do the results row first.
