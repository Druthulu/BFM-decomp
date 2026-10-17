---
ts: 2026-10-17T06:27:57.483Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: ec261558-e851-4858-881a-bafc3737e5d1
---
I'm checking the bodies for the remaining batch-2 names, several of which are def-only with empty (void) definitions and no actual calls.

Since any (void) decls in the same translation unit as a changed def would conflict, I should K&R those decls too, consistent with the interim commits, and then move on to creating the hand bodies.
