---
ts: 2026-10-17T18:22:02.409Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe44831ff24b6c2f
model: claude-opus-5-5[1m]
effort: medium
turnId: 38414235-3946-4014-b22c-6e9e31b9cd68
---
I'm noticing the target writes to unk00, unk04, unk0C, unk0D, unk0E but orders unk04 before unk0C -- the source order differs from the assembly order since sched1 reordered things within the barrier-free area. Let me check the head of a0.s to confirm.
