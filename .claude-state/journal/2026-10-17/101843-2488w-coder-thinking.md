---
ts: 2026-10-17T16:18:43.896Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f42f9bd4d9f47ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 1d9764d9-f745-4839-857f-1b214f31db78
---
I'm comparing the different variants—w4 only touches the struct field through the array access without needing a separate store, while w7 keeps a consistent spelling across all member accesses, making it the cleanest choice. I'm noting that `arr[0].v[0]` is really just the natural field spelling rather than an identity-address trick, so it's more of a de-cast than a laundering mechanism.
