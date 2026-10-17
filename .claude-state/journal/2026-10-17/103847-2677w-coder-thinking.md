---
ts: 2026-10-17T16:38:47.563Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a26a2e7a9927b54ee
model: claude-opus-5-5[1m]
effort: medium
turnId: 253b27e4-07a4-41f7-b188-1141b6e4bbf5
---
I'm trying to figure out why scheduler moved register a0=72 to the top in the original version, suspecting it relates to how a0 gets clobbered earlier in block 1 and how that interacts with scheduling priority around the live range of register 89.
