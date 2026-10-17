---
ts: 2026-10-17T16:38:38.974Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a26a2e7a9927b54ee
model: claude-opus-5-5[1m]
effort: medium
turnId: 253b27e4-07a4-41f7-b188-1141b6e4bbf5
---
I'm comparing the original and c2 versions, which stay identical through the combine pass, so the divergence must come from scheduling — it looks like insn 78 got reordered ahead of insn 63, which changes how register 72's liveness interacts with the later uses.

Actually, I suspect reload_cse is substituting a0 for s0 since they hold equivalent values, and that this depends on where the barrier insn sits relative to block boundaries during sched1 — the barrier is in block 1 rather than block 3, which could explain why c2's scheduler didn't make the same reordering. I want to check the sched1 dump for block 3 in both versions to confirm this.
