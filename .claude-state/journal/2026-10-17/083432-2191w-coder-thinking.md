---
ts: 2026-10-17T14:34:32.722Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad6d34fe5a434569c
model: claude-opus-5-5[1m]
effort: medium
turnId: 59758253-d852-4335-8721-e201fdcf73ff
---
Since this isn't tracked, I need a baseline — stashing seems risky since the dirty tree includes other files' changes, so maybe a worktree of HEAD is cleaner, though census might need build artifacts. I'm also considering that the brief suggests using `--only <seg>` targeting touched segments like "ov_SC05_005" rather than letting restruct's default residue check sweep every body.

I wonder if my functions' uncovered sites aren't being matched by `--only` since bodies are keyed per translation unit, not by function name directly. The census JSON only has aggregates, not individual sites, so I should try running restruct with `--check-residue --only` on each segment to pinpoint which bodies actually hold the uncovered sites.
