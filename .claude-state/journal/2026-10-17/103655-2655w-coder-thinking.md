---
ts: 2026-10-17T16:36:55.642Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a26a2e7a9927b54ee
model: claude-opus-5-5[1m]
effort: medium
turnId: 253b27e4-07a4-41f7-b188-1141b6e4bbf5
---
I'm looking at the `move a0,s0` instruction at the start of the inner block, where arg is a pseudo holding a copy of param_1 that got assigned register a0 since it's passed to the function call. Without a barrier, CSE would just substitute arg with param_1/s0 directly, so I need to keep arg as a distinct pseudo—noting this move happens right after the branch, at what looks like a join point.

But the target also shows the 138-offset load using a0, meaning CSE didn't propagate s0 into it there either, which is odd unless the asm clobber of $4 is what forces the separate copy. I'll try a few variants, like defining arg as a cast of param_1 right after the `if (val<0)` check, to see if that reproduces the right instruction ordering.
