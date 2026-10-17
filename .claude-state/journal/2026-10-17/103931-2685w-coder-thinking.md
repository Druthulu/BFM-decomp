---
ts: 2026-10-17T16:39:31.258Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f42f9bd4d9f47ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 1d9764d9-f745-4839-857f-1b214f31db78
---
I'm looking at the mn/mx move-then-shift pattern versus the target scheduling order, trying to figure out why keeping the original source order makes mny's live range longer than my's. I need to find a way to shorten mny's live length elsewhere to compensate instead of reordering the instructions.

I'm checking whether tweaking refs for my via a redundant shift expression would help, but CSE would likely just substitute back to the same pseudo register, undoing the change.
