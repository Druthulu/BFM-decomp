---
ts: 2026-10-22T06:46:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_OSzeloKb1oZjts2sCwBK
---
The trimmed TU reproduces the target exactly (the #APP #NO_APP is the asm).

Now compare the .sched dumps for the two versions. The .sched dump is the sched1 output RTL. Let me diff the entry block.

Let me look at the function's section in tree.i.sched and cand.i.sched.
