---
ts: 2026-10-17T17:01:23.071Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
I'm trying different restructurings to get the label placed before the branch test, considering whether changing what the comparison operates on could produce the right ordering without needing an explicit goto or switch.

Maybe the scheduler's resource-scan logic is the key: it walks backward from the branch, skipping non-conflicting instructions until it hits one that sets or references a needed resource. If I reorder so that an earlier load or the addu instruction references something set later in the block, that would block it from being hoisted past the branch, which might force the desired placement.

Maybe the computed pointer precedes a label from a `for` loop's expanded exit test, and the duplicated loop-exit test at the bottom could explain the ordering gcc produced—the comparison and branch emitted separately from the increment, matching the slt/beqz pattern without folding iVar5's update into the test.
