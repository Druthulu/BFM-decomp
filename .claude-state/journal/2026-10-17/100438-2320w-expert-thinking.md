---
ts: 2026-10-17T16:04:38.030Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac3c2f25cd86a3f15
model: claude-opus-5-5[1m]
effort: medium
turnId: 8d79bbc0-6d30-411b-a4e2-472ff86f0d65
---
While those run, I want to draft the banker brief outlining the task for whoever handles the first batch: writing a reusable script that swaps function bodies for MATCH/PARTIAL rows using the winning candidate's logic, then verifying the change holds up at the whole-object level.

Once the swap script is written, I'll have the banker rerun the diff check on the original source as a final sanity pass. Then they need a second script that rewrites the residue TSV: dropping rows for full matches, trimming kept/removed kinds for partial matches, and updating wall rows with the right pass/instrument/cause tags while preserving the header lines — doing this in Python since sed is off-limits. After that, they should fix any stale load-bearing comments over swapped code, rerun the restructuring and type census checks (expecting the known pre-existing exceptions), confirm residue census is clean, pass the full R22 regression suite, and commit per-task. If any swap fails regression for a specific function, the banker should revert just that function's change, mark it as WALL with the best known candidate, and proceed.

I want to pin down the exact restruct commands — likely something like running restruct with the S rung and residue flag plus specified forms, scoped to each touched segment, followed by a residue check pass per segment, though I should let the banker verify via the tool's own help text since I'm not fully certain of the flag syntax. I also want to clarify the casts check command and note that the known lying/unbacked pre-existing issues are expected. Now I'm drafting the banker brief template.
