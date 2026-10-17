---
ts: 2026-10-17T13:41:29.138Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a715c83225823a44a
model: claude-opus-5-5[1m]
effort: medium
turnId: cb00494e-7b3a-4f28-b3fa-24b3d50bb0ef
---
I'm checking that all 33 cases match, focusing on why variable p got assigned different registers between mine and the target—since p is a global, it gets allocated after locals, and its register choice depends on which local registers are still live and conflicting with it in each block.

This leads me to think about the original source structure—likely the standard PSX `addPrim` macro that packs/unpacks tag addresses using bitmasks, where the mask constants m24 and mFF were probably hoisted as separate variables by the decompiler or an older compiler's constant-loading behavior in a branch.

Now I want to check the remaining diff for i0 to see which mismatches are left.
