---
ts: 2026-10-17T16:23:22.818Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f42f9bd4d9f47ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 1d9764d9-f745-4839-857f-1b214f31db78
---
I'm comparing the scheduling orderings between the two versions — in c1a, the load couldn't hoist above the store because they use different base registers, whereas in the original they shared a base and got hoisted. The pre-allocation state looks otherwise identical aside from this load/store ordering difference.

I think the real variant needed is one where the load uses the same base as the store so it can hoist freely without a barrier — that matches c1 rather than c1a, so I should go look at c1's sched1 dump directly to confirm.
