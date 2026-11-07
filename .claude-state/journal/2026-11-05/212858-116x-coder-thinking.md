---
ts: 2026-11-06T04:28:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vVvuY18CG2XsdsNBlf1Y
---
The block numbering is different from the insn numbers. I need the block containing the `<0x11` arm. The combine dump showed insns 204, 211, 214, 216, 217, 232, 235, 262, 265. In the sched dump for our function, let me search for "insn[ 232]" after line 35406 and the block trace.
