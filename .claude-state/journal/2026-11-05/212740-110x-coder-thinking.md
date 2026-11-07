---
ts: 2026-11-06T04:27:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FIvNm3LzAToxZVpBya4m
---
The pre-sched RTL order is: 211 (lw obj->1C), 214 (sll), 216 (addu), 217 (sll), 232 (lw p), 235 (addiu), label, 265 (sh).

Wait, insn 232 is `(set (reg/v:SI 76) (mem/s:SI (plus (reg 72) 32)))` — the p load. But the insn's *position* in the list is after 217. Good, that's the source order (multiply, then p). Note the multiply chain is 211,214,216,217 and p is 232 (created later). Good.

Now the .sched dump (post-sched) showed: 204, 211, 232, 214, 216, 217, 235, label, 265. So sched1 moved 232 (lw p) before 214/216/217. So sched1 hoisted it.

Why? insn 232's priority: its dependent is 265 (the sh), which is after the label (a different basic block?). sched1 computes LOG_LINKS within the block. The block ends at the label 262. insn 232 is in the block [start..label]; its only dependent 265 is in the next block, so within this block 232 has no dependents → priority 1. insn 214's priority: 214→216→217→235 = 3 (plus costs). So 214 should be scheduled before 232. But the sched output has 232 before 214!

Hmm, unless the sched dump order is the ORIGINAL order, not the scheduled one. Let me check: maybe -ds prints the RTL BEFORE scheduling (the input). The .sched dump might show the pre-sched RTL (with priorities in comments). The listing shows no priority comments though.

Actually, GCC 2.7.2's schedule_insns prints:
```
if (sched_dump) fprintf(sched_dump, "\n;; Function %s\n\n", ...)
...
```
and during scheduling, `debug_ready_list`? The .sched file likely contains the RTL at the end of scheduling (the scheduled insns). Hmm, but the .sched file has 38706 lines — a lot, probably includes the ready-list debug for each block.

Let me look at the beginning of the .sched dump to understand the format.
