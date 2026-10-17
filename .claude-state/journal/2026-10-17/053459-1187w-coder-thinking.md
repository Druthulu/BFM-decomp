---
ts: 2026-10-17T11:34:59.943Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
I'm checking the minimum match threshold against another jump case—if block 0x384 precedes a label, the required minimum drops to 1, which would be enough to trigger a cross-jump merge into block 1's target. But I need to watch out for nop-padding patterns that could falsely satisfy this match and cause an incorrect merge.

In an else-if ladder, each block is typically preceded by the conditional branch testing the prior condition rather than by a label, since the label belongs to the comparison itself. Tracing through the sequence, the first matching instruction in each branch is the test-and-branch, and since those target different labels, the match count stops at 1—below the required minimum of 2—so no merge should occur there. That makes me wonder whether the actual merge is happening through a different path: cross-jumping into code before a label by matching against the shared fallthrough into the join point instead.
