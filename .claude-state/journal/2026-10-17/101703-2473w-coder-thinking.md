---
ts: 2026-10-17T16:17:03.436Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac8178896d2313b85
model: claude-opus-5-5[1m]
effort: medium
turnId: 589d16b4-5a62-4ce6-8a45-63d170f3cb6e
---
That approach is worse, so I'm going back to b4. I'm thinking scheduling only reorders within a basic block, so maybe splitting the store and the return into separate basic blocks—like having the store be the last statement of one block, with the return reached through a join point—would prevent hoisting.

I'm considering restructuring the control flow so the error-check branches return early and the fallthrough path stores into node before returning 1, possibly sharing a common return-1 block via a jump target, but that risks changing code layout since the target has the v0=1 assignment sitting right in the delay slot of the jump to the epilogue. There's also the question of why the pseudo got v1 instead of v0—it's because v0 is live from an earlier hard-register assignment, forcing that dependency to persist. I'm also considering whether scheduler tie-breaking by instruction order could be exploited here.

Now I'm digging into gcc 2.7's backward list scheduler: priorities are computed as the longest path to the end of the block, and both the store and the v0=1 assignment have no real successors besides the final jump, so their priorities tie. The tie-break seems tied to a register "birth" boost—instructions that set a register not previously live get a priority bump—which is exactly the mechanism causing v0=1 to be scheduled where it is, so I'm looking at ways to either change that store's priority or avoid the birthing boost altogether.

I'm also considering whether reordering the load of `node` relative to the function call could match the target's instruction order, or whether swapping around which store comes last in the branch could produce the right layout, though the target's fixed store sequence constrains those options.

Let me try the goto-based variant next, since the do-while(0) trick isn't really available here without a fake marker.
