---
ts: 2026-10-17T11:57:01.856Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a8e969c8cbf9244d6
model: claude-opus-5-5[1m]
effort: medium
turnId: 150f717e-3914-450b-b185-2137b70bb2af
---
I'm tracing through the scheduling order at T-35, where the ready queue contains 20, 15, and 18, and working out which item gets picked and how that determines the final printed order of 18, 15, 20, 22.

Looking at the priority markers, 20 and 15 carry the boosted value 0x7f000001 while 18 just has priority 1, so I'm trying to recall what adjust_priority does in gcc 2.7's sched.c — whether it's boosting instructions that don't create new live registers ("birthing" insns). I need to go read that function to confirm.
