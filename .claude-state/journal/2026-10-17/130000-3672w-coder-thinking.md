---
ts: 2026-10-17T19:00:00.103Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6ee12ed7d3da1789
model: claude-opus-5-5[1m]
effort: medium
turnId: c73a5082-25b2-49a4-a028-dd1d5ff9dd77
---
I'm noticing sv gets recomputed with addiu each time it's used in the func_8012F14C call, rather than being reused via CSE, which raises the question of why rot's register behavior differs from sv's in this same pattern.

I'm checking my own code's register allocation more broadly — s0 points to sp+24 for one call's argument and sp+32 for the matrix, but it's unclear whether the sv/rot distinction comes from different pointer casts in their prototypes or from how their addresses get used in stores. I should trace through my full code to pin down exactly which uses trigger the difference.
