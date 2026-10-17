---
ts: 2026-10-17T11:50:02.407Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a4daaa68013ad062c
model: claude-opus-5-5[1m]
effort: medium
turnId: 271cef5f-aa35-4bfd-88b6-c572019ec154
---
I'm comparing the scheduling of the struct return copy against the target: the target loads into v0, stores it, then moves v0,s0 afterward, creating an anti-dependence on v0 that keeps the ordering intact in sched2 after register allocation.

In mine, the temp got v1 instead of v0 — so maybe sched1 moved the hard-reg set earlier, or local-alloc saw a conflict I'm not accounting for. I should dump the .sched output for r1 to see exactly where that move landed before the load.
