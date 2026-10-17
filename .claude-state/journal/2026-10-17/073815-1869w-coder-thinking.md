---
ts: 2026-10-17T13:38:15.833Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe7336983cc0fdaf
model: claude-opus-5-5[1m]
effort: medium
turnId: ad81449e-f0c8-40b2-83c6-f273f94996ed
---
I'm noting that bare `register` without inline asm stays ordinary C, which makes me wonder whether gcc 2.7 at -O2 actually treats user-declared register variables specially — like via REG_USERVAR_P affecting allocation priority in global.c or qty comparisons in local-alloc.

Let me just check the actual TU directory for the candidate file to see what's there rather than guessing further.
