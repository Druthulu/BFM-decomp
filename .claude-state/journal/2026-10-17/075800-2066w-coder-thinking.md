---
ts: 2026-10-17T13:58:00.660Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2ab9a444ea3aa2ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd53509-0294-4563-a878-c510da735377
---
I'm wondering if this is a jump optimization case—cross-jump merging tail code across branches—or possibly related to how barriers prevent sinking the b4b load past shared code paths in older GCC versions.

Actually, I think I see it: scheduling likely moved the load of b4b to the end of each branch since it's only used at the join point, making both branches end identically, which then lets cross-jumping (running after scheduling) merge them into a single join block. That would explain why the barrier mattered—it blocks that late movement before cross-jumping can act.

To match the target, I should instead make the branch tails diverge by moving the store into each branch itself, so each branch ends with its own identical store that cross-jumping merges, but the preceding pointer-advance instructions (differing by plus/minus) stay separate. I'll try moving `b4b[1] = var` into both branches to see if that produces the right shape.
