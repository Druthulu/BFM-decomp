---
ts: 2026-10-17T11:15:53.692Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
I'm realizing why the cross-jump didn't happen in the target: the first return wasn't cross-jumped, and the second return's `v0=0` got hoisted before the branch rather than appearing as a standalone tail before `end`, so there's no matching later "v0=0; goto end" sequence to merge with.

Maybe the branch inversion rule applies differently depending on fill order: the conditional branch tries filling its delay slot from the insns before the unconditional jump, picking up "v0=0" there before the invert-and-merge logic runs, which would explain why mine ends up with the move in the delay slot while the target still computes v0 separately.

Rather than keep theorizing, I should just dump the RTL with -dj and look directly at what jump.c actually does to this pattern, since I'm spending too much time guessing.
