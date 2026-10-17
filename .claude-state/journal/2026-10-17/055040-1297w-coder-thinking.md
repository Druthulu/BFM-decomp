---
ts: 2026-10-17T11:50:40.797Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a8e969c8cbf9244d6
model: claude-opus-5-5[1m]
effort: medium
turnId: 150f717e-3914-450b-b185-2137b70bb2af
---
I'm realizing class 2 shares the same function body, so fixing one should let me port the fix across. I'm trying to isolate the stsz macro calls that take addresses for the different gte registers to pin down what's going wrong in cases 2 and 3.

Looking at the duplicated comparison logic in cases 6/7, I wonder if restructuring it into a single assignment followed by one conditional check would change the emitted code versus the current pattern, which repeats the same check in both branches. I'm also considering other plain C tricks, like inserting a dead register copy that gets reloaded away, similar to the existing min/max copy pattern already in the code. I'll just test the restructured version along with a few variants against the base case.
