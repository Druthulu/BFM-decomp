---
ts: 2026-10-17T18:22:29.713Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe44831ff24b6c2f
model: claude-opus-5-5[1m]
effort: medium
turnId: 38414235-3946-4014-b22c-6e9e31b9cd68
---
I'm noticing the store to that memory slot ended up sinking after the load instead of being hoisted, which seems different from what the comment claims about the ordering.

I suspect the scheduler groups these differently because the aliasing between the stores and that other load forces a dependency, and the second basic block isn't part of the same extended block so pseudo-sharing wouldn't apply. I want to try reordering the stores to match the target's sequence and testing a few other variations like removing that intermediate variable or using a pointer alias to see which one reproduces the expected output.
