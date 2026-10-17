---
ts: 2026-10-17T17:01:40.293Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a26a2e7a9927b54ee
model: claude-opus-5-5[1m]
effort: medium
turnId: 253b27e4-07a4-41f7-b188-1141b6e4bbf5
---
I'm thinking the dead code must come from something being used in a path that flow analysis couldn't eliminate at compile time, even though the result eventually gets overwritten everywhere—like a use inside a branch that got pruned later by dead-code elimination after a reload or jump.

I conclude mnc is genuinely dead in the final code since it's just a sign-extension that flow deletes regardless of where it's placed. I'll stop chasing this and accept the WALL flow-unused-result issue, recording 99 as the best score so far.
