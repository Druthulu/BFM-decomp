---
ts: 2026-10-17T12:00:04.649Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a4daaa68013ad062c
model: claude-opus-5-5[1m]
effort: medium
turnId: 271cef5f-aa35-4bfd-88b6-c572019ec154
---
I should check memrefs_conflict_p in sched.c to see what's actually blocking the hoist, and figure out whether this happens during CSE or scheduling by comparing the instruction order before and after combine versus after sched.
