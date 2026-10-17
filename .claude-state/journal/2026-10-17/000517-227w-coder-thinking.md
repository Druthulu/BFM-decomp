---
ts: 2026-10-17T06:05:17.539Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
I'm noticing --kr also strips existing prototypes that already had proper params, like turning `extern s32 func_8018107C(s32 arg0);` into an empty-param form elsewhere — a temporary regression, but that's fine since a later rung will normalize all these declarations to their final form anyway.

I should also check SC05_001, where the caller func_80180520(s32 a0) needs to pass a0 through correctly.
