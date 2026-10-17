---
ts: 2026-10-17T11:12:20.297Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5faba3cdb29155cb
model: claude-opus-5-5[1m]
effort: medium
turnId: e4e5bc1c-68a3-4a95-bce5-27c78dfaef1c
---
I'm noticing fn.rtl doesn't seem to force a memory address register, which might explain why cse1 doesn't fold the expression while cse2 does. I want to check the cse pass's head section to understand why.
