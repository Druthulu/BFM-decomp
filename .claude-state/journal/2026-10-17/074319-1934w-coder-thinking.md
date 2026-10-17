---
ts: 2026-10-17T13:43:19.315Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a715c83225823a44a
model: claude-opus-5-5[1m]
effort: medium
turnId: cb00494e-7b3a-4f28-b3fa-24b3d50bb0ef
---
The pv load now happens earlier, before the lhu, so the scheduling order shifted even though the score itself stayed the same. I notice pv is register r77, which is a global spanning two blocks, so it gets allocated by the global allocator after locals are assigned — I need to check the allocation and diff more closely.
