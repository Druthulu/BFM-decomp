---
ts: 2026-10-17T17:27:23.855Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
I'm trying another approach: wrapping the copy and test inside a do-while(0) block, hoping that isolating it this way might prevent CSE from treating the copy as redundant and rewriting the test like before.

Since the loop condition is always false, the loop label never gets jumped to and gets deleted, but the loop notes might still remain—and I'm not certain whether CSE's basic-block boundary tracking stops at these notes. It's worth testing to see if that structural separation is enough to keep the original value referenced in the test while the copy stays isolated, making the copy-use pattern span blocks that combine can't merge.
