---
ts: 2026-10-17T10:10:16.043Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aed9b349dc2455822
model: claude-opus-5-5[1m]
effort: medium
turnId: dfd29141-6312-4a35-8baa-9537d6cb55c6
---
Calibration needs a current build matching HEAD, so since the T8.c4 commits changed sources, the build may be stale. The safest path is to run the R22 gate first with a clean extract and check-all, then do the snapshot-baseline and calibrate steps on the four binaries: main, ov_SC01_077, ov_SC02_000, and md_SC07_004.
