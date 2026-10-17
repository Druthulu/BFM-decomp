---
ts: 2026-10-17T06:17:53.368Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
I'm tracing the 2179 call-site declarations of func_80149CB4 across the fleet, figuring out that since the caller passes through its own incoming a0/a1 parameters, the signature change cascades up one level the same way it did in T6—meaning I need to track who calls this caller next to see how far the cascade propagates.
