---
ts: 2026-10-16T16:35:21.611Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: adedfdbb8f5ba3d6e
model: claude-opus-5-5[1m]
effort: medium
turnId: 8f3cea4c-1538-4d9e-8595-5d752c92ba07
---
I'm working through the stale count calculation, realizing some of the kept T3 band definitions are actually now live again since they're drawn by the current rung, so they shouldn't count as dead/stale after pruning.

The dup_classes count of 170 is likely tied to twin classes whose name sets shifted when I removed pruned names — mismatched name sets would cause gating even though the defs still exist, so both the stale twins and dup-class gating trace back to the same root cause: pruning doesn't update the twin hash entries. I'm uncertain whether check_structs ran at the end of T4, which affects whether the pre-T5 state can be trusted, so I want to grep the stale list directly to confirm which names are actually flagged.

T3 was the last successful run with `dup_classes=0 twins_stale=0`, where `twins_stale` tracks mismatched twin classes and stale dead-name entries. I'll now split the 3894.
