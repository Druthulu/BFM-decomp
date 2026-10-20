---
ts: 2026-10-17T18:37:14.582Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac81395c556dc97c0
model: claude-opus-5-5[1m]
effort: medium
turnId: 2749fb46-32ea-40ac-942d-d9e5fb5596d6
---
I'm comparing the register allocation details between the two versions, noticing the target uses v1/v0 while mine picked a1 for the same slot, and trying to figure out why the lh v1 pseudo's lifetime might have forced that different choice.

Maybe explicitly hoisting the s50.y load into a local variable before the comparison and subtraction would nudge the compiler toward the same register preference.
