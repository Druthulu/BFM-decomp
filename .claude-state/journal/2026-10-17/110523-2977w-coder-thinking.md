---
ts: 2026-10-17T17:05:23.798Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6aaa11811b8be773
model: claude-opus-5-5[1m]
effort: medium
turnId: c3153718-defe-4620-a7c2-e0184cae88c0
---
Without the barrier, the scheduler hoists the address computation since it sits on a higher-priority critical path through the shift and add instructions, while the target's ordering with v1b first only works because the barrier forces that dependency. So without the barrier, I need the address computation to have lower scheduling priority, or restructure so v1b's computation naturally comes first.

I'm trying the C-level change where v0b depends on v1b (making v0b = v1b * 2 instead of independent), which lengthens v1b's dependency chain so it outweighs the address chain in priority. That got 18 matching instructions out of 100 -- worth examining this diff more closely.
