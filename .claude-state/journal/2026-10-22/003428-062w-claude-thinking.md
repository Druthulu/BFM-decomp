---
ts: 2026-10-22T06:34:28.359Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: afdda1e6f94a02c83
model: claude-opus-5-5[1m]
effort: medium
turnId: 6a716585-2a4d-4246-9abb-946f75549633
---
I'm trying to figure out why learning mode keeps MiniMax to one run at a time until something comes back clean — G14b had friction so it didn't count, and the refused launches (G15b, RM1, RM1x) plus a test launch are red, not throttling. I'm puzzled that G08c was noted as clean yet still seems to trigger one-at-a-time behavior, so maybe the learn count resets on some other condition I haven't pinned down yet.
