---
ts: 2026-10-17T18:51:37.188Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0b7566fdaca12346
model: claude-opus-5-5[1m]
effort: medium
turnId: 5fa06e7a-0d54-4425-8d05-7af8227a2b37
---
I realize the merged version lost the original branch structure, which is load-bearing—I need to go back to the original if/else-with-goto-join layout and just strip the pin and rename variables, keeping the then-arm's load, copy, and subtract-compare sequence intact.

Comparing register usage between the two versions, I see the same logical structure but with registers shifted because the v0 pseudo-variable spans multiple blocks as a sort of global. The fix is to split that shared v0 into distinct per-segment local variables—one for the top segment, one for the then-arm, one for the else-arm, one for the join point, and one for the final block—so each stays block-local rather than threading through the whole function.
