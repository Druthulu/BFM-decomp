---
ts: 2026-11-06T18:59:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ACCN0iZmpIrNAg0DtqM7
---
No score 0 or 1. The best is 2 (20 variants). So the a3 increment position is the last issue.

Let me look at which variants score 2 and what their remaining diff is. If all 20 have the same diff (the a3 increment), maybe a different approach fixes it.

The target's loop tail: a3+104, v1+104, a2+1, slti, bnez, a1+104.
The score-2 variants: v1+104, a3+104, a6+1, slt, bne, a5+104.

So the a3 and v1 increments are swapped in position. sched1's order. To flip: make the a3 increment come before v1's in the final schedule.

Since sched1 schedules the loop body backward, the increments' order depends on the RTL order and dependencies. The target's RTL (with the pin) had the increments in the source order (a7 first) and sched1 kept them.

In the lever-free build, sched1 reorders them. Why? Let me look at the sched1 trace for the score-2 variant... The loop body is a basic block; the increments are independent.

Hmm, maybe the difference is due to the *register* difference: in the target, a7=$7 (a3) and v1=$3; the increments are `addiu a3,a3,104` and `addiu v1,v1,104`. In mine (score 2), the same registers, but the order swapped. So it's purely sched1's choice.

What determines it? In sched.c's backward pass, insns are added to the ready list; the order among equal-priority insns is by the "potential hazard" (register conflicts with the current insn) and the list order. The trace showed "insn 89 has a greater potential hazard" etc.

Let me look at the sched trace for the score-2 variant's loop block and see what decides. But maybe easier: try variants that change the *loop structure* (e.g., the a6 increment's position, the loop test form) to shift sched1's order.

The target's tail order: a3, v1, a6, slt, bnez, a5(delay). Mine: v1, a3, a6, slt, bne, a5(delay). Only a3/v1 swapped.

What if the source order of the a7 increment is after v1's but the *RTL* has a7 first? The source order in g007 is v1 first. sched1 produced v1 first. If the source were a7 first (g001), the allocation flips (wrong). 

Hmm, what if the a7 increment is written differently to change its scheduling: e.g., `a7 = (unsigned short *)((char *)a7 + 0x68);` vs `a7 += 0x68/2`? The insn is the same.

What if the increments are combined: `a7 = (unsigned short *)((char *)a7 + 0x68); v1 = (unsigned short *)((char *)v1 + 0x68);` — the target.

What about the a6 increment position: in the target it's after v1; in mine it's after a3. Hmm.

Let me check the score-2 variants' exact diffs to see if any has a different residual (e.g., a different insn out of place that might be easier to fix). Let me list the score-2 files and run dt on a few.

Actually, let me look at the full list: 20 score-2 variants. Their permutations: which ones? Let me find them.
