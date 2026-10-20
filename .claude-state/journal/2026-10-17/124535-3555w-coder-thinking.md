---
ts: 2026-10-17T18:45:35.581Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0b7566fdaca12346
model: claude-opus-5-5[1m]
effort: medium
turnId: 5fa06e7a-0d54-4425-8d05-7af8227a2b37
---
With the GTE part fixed, I'm now tracing s2: it holds s1+0xFC and appears live across the call to func_80013294, meaning the target computes s2 before that call rather than keeping it purely local like v0.

I also need to check the s0/s1 register swap — the target has s0 holding the unk20 pointer and s1 holding the param, so I should test an arrangement where s2 is assigned right before the conditional call.
