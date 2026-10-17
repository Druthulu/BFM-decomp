---
ts: 2026-10-17T06:18:09.752Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
I'm realizing func_80149CB4 actually takes real arguments (a void pointer and an int), just wrapping a call to func_80157D20 — not a no-arg stub as I assumed. I should check the actual call sites in MAIN_012 near jr_801555F4 to confirm how callers pass these values.
