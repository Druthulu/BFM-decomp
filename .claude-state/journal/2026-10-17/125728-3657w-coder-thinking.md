---
ts: 2026-10-17T18:57:28.406Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6ee12ed7d3da1789
model: claude-opus-5-5[1m]
effort: medium
turnId: c73a5082-25b2-49a4-a028-dd1d5ff9dd77
---
I'm noticing the computation went into v1 as temps before the final add into a3/pm3, rather than building the whole chain directly in the ot register like the pinned version did — so the register allocation differs even though the result ends up the same.
