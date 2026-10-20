---
ts: 2026-10-17T18:39:21.456Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0b7566fdaca12346
model: claude-opus-5-5[1m]
effort: medium
turnId: 5fa06e7a-0d54-4425-8d05-7af8227a2b37
---
I'm comparing scheduler outputs between sched1 and sched2, tracking how instructions like sh, sb, sw, and lhu get reordered relative to each other, and analyzing register lifetimes to match my allocation against the target's use of r111 and r110.

Trying to work out local-alloc's priority formula based on reference count and life length to understand why r110 would get v0 over r111 — unless the target's scheduling actually shortens r111's life differently than I assumed, perhaps through a different instruction order that I haven't considered yet.

I'm trying to recall the local-alloc priority formula based on reference count, size, and life length to figure out why r111 outranked r112. Maybe the original ordering tested different store placements, since one variant scoring 10/12 had the computation happen before the other stores. I should dig into the lreg dump to check how r111 and r112 tie and compare their allocation priorities directly.
