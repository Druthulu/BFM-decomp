---
ts: 2026-11-06T04:27:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gn9PaZdakaE7SUdXu3ix
---
Excellent! The RTL (pre-sched) order in x1:
- insn 204: sh 26 (0x1A store)
- insn 211: lw obj->1C
- insn 232: lw p (reg 76) — note `mem/s:SI` (struct!)
- insn 214: sll
- insn 216: addu
- insn 217: sll
- insn 235: addiu
- label 262
- insn 265: sh 24 (merge store)

So the RTL order is: lw obj->1C (211), lw p (232), sll (214), addu (216), sll (217), addiu (235). The p load (232) is BEFORE the sll chain in the RTL! So the C order in x1 (multiply, add, p) did NOT translate: the p load ended up before the chain. Why? Because the front-end/expand emits `p = *(s32*)(a0+0x20)` — the load — at the point of the assignment. But the C order in x1 is multiply, add, p. Yet the RTL has lw p before the chain.

Wait, insn numbers: 211 (obj->1C), 232 (p), 214 (sll), 216 (addu), 217 (sll). Insn 232 was created later (higher number) but placed between 211 and 214 in the list? The list order is 211 → 232 → 214. That means the insn was inserted after 211. Hmm, that's odd: insn 232 created after 214/216/217 but inserted between 211 and 214. This is likely `loop` or `combine` or `cse` reordering? Or the `do-while` from the `==0` arm? No.

Actually, wait: maybe this RTL is from a different point (the dump may be post-sched?). The .sched dump shows the RTL AFTER scheduling (with the scheduled order). The header of the dump might say. GCC's -ds dump prints the RTL before scheduling with priorities? Let me check: sched_dump prints ";; Function ..." then ";; insn ... priority" maybe. The listing I see is a print_rtl of the insns in their CURRENT order at dump time. If the .sched dump is printed after scheduling, the order is the scheduled order. GCC 2.7.2 schedule_insns prints the dump at the END? Let me check sched.c.

Actually the file is named x1.i.sched and contains 38706 lines — likely the scheduling debug output (block by block, with ready lists). The portion I read shows the final insn list (after scheduling) maybe.

Let me instead look at x1.i.lreg (local-alloc dump) or x1.i.greg (global-alloc) — those are after sched1. To see the pre-sched order, use x1.i.combine (post-combine, before sched1). Let me look at the combine dump around the same insns.
