---
ts: 2026-10-17T18:22:13.247Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a11ed4236c71ce25b
model: claude-opus-5-5[1m]
effort: medium
turnId: 638017c5-5103-4585-b12e-50498d92977e
---
I need s0 to win the register allocation over v0 since s0 belongs to the live whole function while v0 only holds that second value. Since priority favors whichever has more references, I could boost s0's ref count, shorten v0's lifetime, or try using a0 directly as the param pseudo instead of s0.
