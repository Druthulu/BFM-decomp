---
ts: 2026-10-17T06:12:56.782Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
I'm wondering if recalibration is needed after every commit since the check compares calibration commit to HEAD, which would be costly per run. Maybe the check is more lenient about which files trigger recalibration, so I should look at how the R56 check is actually implemented.
