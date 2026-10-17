---
ts: 2026-10-17T16:48:14.639Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6aaa11811b8be773
model: claude-opus-5-5[1m]
effort: medium
turnId: c3153718-defe-4620-a7c2-e0184cae88c0
---
I'm noticing the base pseudo function uses a3 where the target uses v0, and the branch target offset differs too — the back-edge jumps to a different location, suggesting the loop instruction order differs. I should compare lines 28-40 of both versions to pin down the discrepancy.
