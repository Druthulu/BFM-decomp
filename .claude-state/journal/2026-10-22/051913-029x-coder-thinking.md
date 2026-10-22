---
ts: 2026-10-22T11:19:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Ry2vQOk30txBOQc8Is37
---
There's `.run/gccmap/gcc-2.7.2-vanilla-src` — the gcc source! Let me look at sched1.c there.

Note: constraint says "never ls/find outside the project" — this is inside the project. Good.

Let me look at sched1.c's launch_priority / birthing logic.

But careful about disk: the source dir is inside the project, fine.

Let me grep.
