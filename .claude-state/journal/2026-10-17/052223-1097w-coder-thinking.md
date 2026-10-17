---
ts: 2026-10-17T11:22:23.964Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
MIPS likely doesn't need HAVE_return handling unless there's no frame, so I can skip that. I want to check what happens after for normal returns—specifically how the function calculates its return value into a pseudo register when there are multiple return points.
