---
ts: 2026-10-17T11:24:56.289Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
I'm thinking CSE probably won't merge these since the two uses of v live in different blocks, making it a global value rather than something split by pseudo-registers—though the results should come out the same either way. Let me check the g1 diff to confirm whether a v1 copy actually shows up.
