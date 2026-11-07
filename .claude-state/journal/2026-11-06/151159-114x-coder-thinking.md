---
ts: 2026-11-06T22:11:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VXuBekjrj21MoNJ8IDc7
---
i2.c = score 3 (ORDER, 197 ins)! That's a big improvement: wrapping the otp block in do{}while(0) gives score 3 — an ORDER difference, not a register swap. So the do-while (C0535) changed the sched1 EBB and fixed the register allocation; now only 3 order mismatches remain!

Let me look at i2's diff. Score 3 = 3 mismatched positions.
