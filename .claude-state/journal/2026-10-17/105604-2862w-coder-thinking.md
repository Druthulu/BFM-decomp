---
ts: 2026-10-17T16:56:04.975Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6aaa11811b8be773
model: claude-opus-5-5[1m]
effort: medium
turnId: c3153718-defe-4620-a7c2-e0184cae88c0
---
I'm tracing register allocation differences between my version and the target: in mine, the tag store happens before the load so the lifetimes of r88 and r91 don't overlap, letting them share register v1, whereas the target's ordering keeps the tag load alive longer, forcing a different allocation.

I'm checking the sched1 output order of the store and load instructions to see if a LUID-based priority tiebreak explains why the stores land in a different sequence than expected. I've spent about four minutes on this, so I want to pull up the .sched dump to look directly at the instruction order.
