---
ts: 2026-10-17T19:05:13.754Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aed641f299013cd69
model: claude-opus-5-5[1m]
effort: medium
turnId: a05808f2-3ac4-478a-96ff-4005570aa66e
---
I'm realizing the volatile asm memory barrier treats the register load as dependent on everything, since sched considers volatile asm a barrier for all pending state, which keeps li a1 pinned above it. So to get real C code replicating this tied ordering, the load needs an explicit dependency forcing it to stay fixed relative to the barrier.

I'm considering naming this pattern `sched2-load-delay-fill`: sched2 fills the load delay slot of the lw instruction with li a1 since there's no true dependency, while the target instead has a nop there because the volatile asm is the only real constraint. This seems like a solid candidate worth an 8 rating.
