---
ts: 2026-10-17T16:41:13.638Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a26a2e7a9927b54ee
model: claude-opus-5-5[1m]
effort: medium
turnId: 253b27e4-07a4-41f7-b188-1141b6e4bbf5
---
I need to keep the v0 pin, since that initial move at the start likely came from it. Since PARTIAL format allows listing kinds still retained, keeping "pin" as a kind should be valid here.

I wonder if I could reduce to just the v0 pin plus keepalive, dropping the s0/v1 pins—that would be PARTIAL:keepalive,pin, still two kinds but fewer actual levers. Let me test that quickly with a minimal c3 variant.
