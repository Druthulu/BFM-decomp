---
ts: 2026-10-17T11:55:43.361Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a8e969c8cbf9244d6
model: claude-opus-5-5[1m]
effort: medium
turnId: 150f717e-3914-450b-b185-2137b70bb2af
---
I'm trying to figure out why the scheduler placed `lw t1` before `move s0,a2` — thinking through how the bottom-up list scheduler picks among ready instructions, and whether the hard-register parameter copy for a2 is constrained by the asm volatile barrier in the tree.

Then I'm comparing register allocation between target and mine: target assigns b=v1, pac=a2, pb0=t1, pb8=t0, while mine gives b=t0, pb0=v1, pb8=a3, pac=a2. I'm reasoning about why pb0 can't take v1 in the target version — likely because its live range conflicts with v1 or extends through the region where a3 is tied up with the fourth call argument.

Since manual reasoning about local-alloc priority ordering is getting complicated, I decide to just try a few quick code variations — swapping the declared types of a and b, reordering the pb0[0] = a assignment relative to other loads, and adjusting how pac's load merges with nearby instructions — to see if any produces the matching register allocation.
