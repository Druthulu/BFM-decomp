---
ts: 2026-10-17T16:28:47.757Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
This arrangement is worse — both copies get the right allocation in a4 but s7 moves too late. The scheduler won't move s7 across the volatile asm or calls, so it needs to stay early, which means I need to test different combinations of which variable gets set early versus late.
