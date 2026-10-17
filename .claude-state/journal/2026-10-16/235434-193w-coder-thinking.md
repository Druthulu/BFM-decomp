---
ts: 2026-10-17T05:54:34.687Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
I need a clean source for this. Following the T6 recipe means hand-editing callers then checking rung D, but that requires committing the caller edit first, which needs a green full check -- though the edit itself should be green per-binary since it's bytes-preserving across the 136 affected translation units. I'm considering whether to pass the caller edits via the --with mechanism instead, treating the header as a file that judge_files would evaluate through its includers, but committing directly seems simpler.

So the plan is to batch caller edits across a group of names, run check-all, commit, then handle rung D for each definition before another check-all and commit. Before touching anything though, I want to survey all 43 names first -- gathering each one's definition files, pin lines, and callers across the build objects, noting that SC03_107 binary builds live under build/src/ov_SC03_107 while names used in main are called fleet-wide. I'll write this survey to a file and review it name by name.
