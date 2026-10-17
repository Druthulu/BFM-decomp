---
ts: 2026-10-17T17:12:08.639Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
I'm reasoning that in sched1's ordering, the struct-typed store can't alias with the scalar symbol load under gcc 2.7's MEM_IN_STRUCT_P logic, so the scheduler is free to reorder them ahead of the dependent loads.

Since a and b have equal lifetimes, the tie-break falls to lower qty, placing a before b, while sched2 flips the order by putting a's load first. Now I'm moving on to examine the siblings.

The struct store creates no apparent dependency on the scalar loads, so sched1 hoists it above them—making `a` and `b` equal in lifetime, with the tie-break favoring the lower qty, assigning v1 to `a` and a0 to `b`. Next I'll look at the siblings.
