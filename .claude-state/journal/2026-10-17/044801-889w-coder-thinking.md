---
ts: 2026-10-17T10:48:01.903Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a55474736c80a3baf
model: claude-opus-5-5[1m]
effort: medium
turnId: e20d419a-4489-4243-b756-85abe7c2d13c
---
I'm puzzled why x1 is now treated as global with multiple sets and deaths, bumping instruction count to 149 — it seems its computed value is spanning a wider live range than expected, possibly because it's being used as a register/value across blocks.

I should check local-alloc.c around line 472 to see if reg_qty tracking for variables with two sets behaves differently when REG_N_SETS equals one.
