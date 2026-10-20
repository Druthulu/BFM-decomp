---
ts: 2026-10-17T18:25:33.669Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe44831ff24b6c2f
model: claude-opus-5-5[1m]
effort: medium
turnId: 38414235-3946-4014-b22c-6e9e31b9cd68
---
I'm thinking through how gcc 2.7's backward scheduler computes priority as the longest path to the end of the block, with leaves starting at base cost and priority propagating from dependents back through INSN_DEPEND, and trying to figure out how the scheduler selects among ready leaf instructions based on that priority.

The store with no in-block dependents sinks to the bottom of the block, matching the "floats to the bottom" comment, so I'm trying to figure out what dependency would keep unk00's store from being treated as a true leaf — since sched1 operates on pseudos before register allocation, there are no hard-register anti-dependencies, but a pseudo that gets reassigned later in the block could still create an anti-dependence forcing the store to precede that reassignment.

This suggests the real source had a reused local variable, say `v`, set once to the constant value stored into unk00, then reassigned later to the lw-chain computation — the second assignment to `v` would need to happen after the store due to the anti-dependence, giving the store a dependent and keeping it from floating to the bottom. Since gcc 2.7 doesn't do SSA, each local maps to a single pseudo, so reusing `v` (rather than something like `ent`, which lives in an unrelated block) seems like the right candidate to try.
