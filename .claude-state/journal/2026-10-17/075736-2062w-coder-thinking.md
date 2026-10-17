---
ts: 2026-10-17T13:57:36.951Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2ab9a444ea3aa2ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd53509-0294-4563-a878-c510da735377
---
I'm seeing that the shared load got commoned into the join point by cross-jumping, since both branches had identical code hoisted after the merge. The compiler compares instructions from the end of each branch backward, so with barriers present this optimization was previously blocked since the branches diverged.

Let me check my disassembly around lines 115-135 to see exactly where the load got sunk to.
