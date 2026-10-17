---
ts: 2026-10-17T16:36:50.288Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f42f9bd4d9f47ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 1d9764d9-f745-4839-857f-1b214f31db78
---
I need to swap allocation priority between my and mny globally — mny needs more references since it has higher priority. I'm checking around lines 125-145 where box references get assigned repeatedly, looking for a good spot to increase mny's usage over my's.
