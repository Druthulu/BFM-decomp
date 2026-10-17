---
ts: 2026-10-17T13:12:08.364Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a68ccc2589980bbb7
model: claude-opus-5-5[1m]
effort: medium
turnId: d2c7b2f5-b16a-49db-83ae-0a0f8f0ba379
---
I need a binaries list to calibrate on—maybe use a subset of the six TUs like ov_SC03_099, 094, 103, 113, 117 and ov_SC05_007. Since my tree is dirty, calibration results could be skewed, so I should stash my edits first to be safe.

Actually, simpler: I'll save my diff to a patch file, check out a clean tree, run calibration, then reapply the patch afterward.
