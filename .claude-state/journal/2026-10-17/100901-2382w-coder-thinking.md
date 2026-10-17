---
ts: 2026-10-17T16:09:01.384Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f42f9bd4d9f47ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 1d9764d9-f745-4839-857f-1b214f31db78
---
I'm trying to figure out which pseudo-register corresponds to the product versus the field, since the product spans multiple blocks across the branch and thus needs global allocation, while the field load happens locally after the branch—so local allocation likely assigns it before the global pass runs.
