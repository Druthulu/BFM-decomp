---
ts: 2026-10-17T16:57:46.955Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6aaa11811b8be773
model: claude-opus-5-5[1m]
effort: medium
turnId: c3153718-defe-4620-a7c2-e0184cae88c0
---
I'm realizing that gcc 2.7's CSE pass doesn't propagate constants across join points after if/else branches, since the join label has two predecessors — so a plain `flag = 1` set before the branch wouldn't get folded at the later check, requiring an actual runtime load and test instead.

But my test case did fold it, so maybe `-fcse-follow-jumps` is letting CSE trace through the branch path and see the constant assignment. I should try variations: making flag a different type (u8, s16, char), or placing `flag = 1` inside both branches instead of before the conditional, to see what reproduces the `move v0,a1` then `beqz v0` pattern.
