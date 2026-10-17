---
ts: 2026-10-17T07:37:42.885Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a4ea43d50abd7a6b9
model: claude-opus-5-5[1m]
effort: medium
turnId: 9d9ef813-ca25-4eb0-b083-5b6795e914da
---
Since Restruct rewrites decls to match the def's signature of `a32 arg0`, but a32 isn't defined there, I should use `s32 arg0` instead since the brief allows s32 as a fair alternate spelling.

I'll switch the body head to `s32 arg0` since `a32` only has a typedef in 800_c.c and fails to parse in 800_b_2.c, then rerun.
