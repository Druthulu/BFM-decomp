---
ts: 2026-10-22T06:46:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_OhyqGHiIm4C4WUc9vfcp
---
Good, small. Now dump the candidate and compare the .sched dump (that's the sched1 dump!) — `tree.i.sched` is the sched1 RTL dump. Let me look at the entry block of func_8018FB5C in tree.i.sched.

Let me first verify the trimmed TU gives the same code: check tree.s for the function.

Then dump cand01.
