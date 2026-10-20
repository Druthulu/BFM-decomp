---
ts: 2026-10-17T18:36:04.186Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0b7566fdaca12346
model: claude-opus-5-5[1m]
effort: medium
turnId: 5fa06e7a-0d54-4425-8d05-7af8227a2b37
---
I'm reconsidering the pattern—this looks like the classic "t in v0" load case with a constant value in v1, so I'm testing different candidate splits, including whether t is computed in a single statement with a u16 type, or whether the field subtraction happens directly after the store instruction.
