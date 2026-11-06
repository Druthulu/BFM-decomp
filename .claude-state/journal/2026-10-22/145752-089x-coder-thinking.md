---
ts: 2026-10-22T20:57:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QMIoW3tKnkFGWwHvgXsn
---
Target: at 14fc lhu s2,26(sp) (bx = out.vy), 1500 lhu s1,24(sp) (ay = out.vx). Same as mine (mine: 1500 lhu s1, 14fc lhu s2 presumably). Then the adds.

So the difference is purely sched1's ordering of by vs ax, and ay vs the chain.

Let me dump sched1 for gen_o3 and look at the priorities. Let me run the dump and find the .sched section for this function. The .sched dump is huge (200+ insns). I'll extract the block around the adds and the sched1 ";; Sched" lines.

Let me do it.
