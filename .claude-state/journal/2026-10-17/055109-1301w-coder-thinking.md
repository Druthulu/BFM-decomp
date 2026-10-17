---
ts: 2026-10-17T11:51:09.953Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a9b75b3e3c01d6fa8
model: claude-opus-5-5[1m]
effort: medium
turnId: 9b80ef94-0ae1-44c6-acfd-ddecb9279a50
---
I notice the 0x2A store gets delayed until after the sh v0 38 instruction, so the compiler appears to be scheduling that particular store later in the sequence rather than following strict source order.

Since all stores target the same base pointer s0 with constant offsets, GCC 2.7.2's scheduler can treat them as non-conflicting and freely reorder them, while loads from a different base must respect read-after-write dependence against prior stores. My version has an extra instruction compared to the target (91 vs 90), likely a nop, and I'm checking whether that comes from the hard register assignment for the -0xA0 constant.

If -fschedule-insns runs before register allocation on MIPS at O2, then sched1 could have moved the -160 pseudo earlier and the unk1C pseudo later, with local-alloc later assigning v1 vs v0 based on overlapping lifetimes -- that would explain why the target's -160 constant ends up in a different register and scheduled earlier than the analogous 160/-120/120 cases.

I should try varying the source order of the stores -- maybe the original wasn't in post-sched order at all, since scheduling can reorder things from source order. Let me try permuting the positions of the c1 stores within the s16 block and the position of the 0x2A byte store to see if any arrangement reproduces the target layout.

I noticed the target delays the last colour byte store past the coordinate stores, giving -160 its own register—likely a source-order effect in sched1. I'll try reordering the store block to match this.
