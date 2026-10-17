---
ts: 2026-10-17T06:00:52.502Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
These functions have no direct callers since they're entry points invoked through tables, so the change cascades no further than the parameter itself. I should check whether changing the signature from void to taking s32 a0 affects declarations referenced elsewhere, like in main tables, so I'll grep across the source for each function name to be sure.
