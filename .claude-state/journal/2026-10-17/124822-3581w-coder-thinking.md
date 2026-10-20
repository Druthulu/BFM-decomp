---
ts: 2026-10-17T18:48:22.059Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac81395c556dc97c0
model: claude-opus-5-5[1m]
effort: medium
turnId: 2749fb46-32ea-40ac-942d-d9e5fb5596d6
---
I'm wondering if swapping declaration order matters, since pseudo numbers get assigned at declaration time in expand, and the allocno tie-breaking rule favors lower pseudo numbers when priorities are equal. I should try moving the `s32 i;` declaration to after the `mOr` declaration to see if that changes the register allocation outcome.
