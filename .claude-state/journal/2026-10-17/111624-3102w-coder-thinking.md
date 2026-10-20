---
ts: 2026-10-17T17:16:24.530Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
The core issue seems to be about which register ends up holding the return value — v0 is used by the sw instruction, so the addiu that sets v0 for the return can't happen before that use without violating a write-after-read dependency, which points to a register allocation conflict over v0 between my scheduling and the target's.

I'm now wondering whether sched1 hoists the hard-register set for the return value above other uses when there's no dependency pinning it down, versus when a pin (like the register 2 constraint on v) forces it to stay later. That difference in hoisting behavior could explain why the target doesn't reorder the return-value computation the way mine does.

Let me check the scheduler dumps directly to see exactly where the `addiu v0` instruction ends up in sched1 versus sched2, since that'll tell me whether this is a pre-reload or post-reload scheduling issue, and whether it connects to how local/global register allocation chooses between a0 and v0.
