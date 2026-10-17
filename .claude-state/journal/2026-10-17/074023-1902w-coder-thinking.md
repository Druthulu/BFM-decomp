---
ts: 2026-10-17T13:40:23.584Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a91f36121b5043b6a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2eee350e-3a84-4d56-9c95-e752be0f81a2
---
I want to compare the schedule dumps between a1 and the original to understand the discrepancy. Looking at instruction 23 in the original, which assigns s0 = P72 after the call—since s0 is callee-saved and shouldn't be clobbered by the call, I'm trying to figure out why sched1 placed it there instead of before the call.

Actually, calls still treat call-used registers as clobbered, but s0 should be exempt from that, so the move is puzzling. I'm wondering if the key is making the argument copy's source get defined late—after the first call—as a pseudo copy, but CSE would likely fold that copy away unless it's hidden behind a mode change or bit-altering cast. I also consider whether an extended basic block boundary, like a branch or goto, could prevent CSE from merging it, but jump1 runs before CSE and would just delete a trivial jump.

Given the time spent, I'll shelve S01 for now and revisit later, moving on to S05.
