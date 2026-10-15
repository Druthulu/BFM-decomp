---
ts: 2026-10-15T03:38:06.955Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae1bafab81c3094c4
model: claude-haiku-5-5[1m]
effort: medium
turnId: cce2f380-4a93-4035-9f83-e38360d1d36e
---
The CREDITS file points to Druthulu/BFM-decomp, crediting "Druthulu (Drew T)" — likely this is the same user, Drew T, given their git identity matches drewtschu.

Since I lack a Bash or Read tool, I can't check the local git remote to confirm it's the same repo, so I'll flag this for verification instead. I also note the licensing split: the tools/docs are AGPL-3.0 while src has no asserted license, which matters for provenance of the config symbol names.

Next I want to fetch the upstream Druthulu/BFM-decomp README to check its completion state, along with the port's LICENSE, README, and docs directory to verify layout consistency (lever_residue.tsv, src/ov_*, src/md_*, include/common.h), so I'll run several fetches in parallel.
