---
ts: 2026-10-17T15:57:37.602Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac3c2f25cd86a3f15
model: claude-opus-5-5[1m]
effort: medium
turnId: 8d79bbc0-6d30-411b-a4e2-472ff86f0d65
---
I'll adopt the report and build out a worklist similar to T10: each coder works scratch-only in their own directory on a handful of functions with a time budget, while a banker coder periodically merges wins back into source, prunes finished rows from the TSV, re-sweeps casts, and commits under strict mode plus R22. Surviving rows get rewritten with the singleton/wall tagging convention.

Running the numbers, roughly 420 functions split across coders at ~8 each means about 52 coder runs; at 4 concurrent that's 13 rounds, each taking a few hours, fitting within the ~14h plan. My main worry is whether banking can run concurrently with cracking -- since the banker does a clean build that wipes build/ and regenerates asm/, this could break crack coders' in-progress `--try` compilations if those depend on build artifacts. T10 avoided this by banking only after all cracking finished, so I should check what `--try` actually reads before deciding whether banking needs to pause crack rounds.
