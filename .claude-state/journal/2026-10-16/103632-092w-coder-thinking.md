---
ts: 2026-10-16T16:36:32.859Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: adedfdbb8f5ba3d6e
model: claude-opus-5-5[1m]
effort: medium
turnId: 8f3cea4c-1538-4d9e-8595-5d752c92ba07
---
My plan is to drop the bullets whose names remain in structs_stale, regenerate Twins with struct_twins.py --write, and rerun check-structs in the background. Since this is a docs-only change, no recompile is needed, and I can commit it under the same T5.c1 id rather than opening a new one—though I'm second-guessing whether I should pause and confirm this approach first.

Actually this is needed for DONE WHEN; it's mechanical, regenerating a generated section, docs-only, so I should just proceed and report clearly afterward. The struct_twins.py script reads from the census directory, likely defaulting to the location check-structs just refreshed, so the type census data should be current.

Found that `type_census.json` has the exact `structs_stale` list, so the fix is docs-only: I'll remove the `## Dead kept` bullets for those now-drawn names, then regenerate `## Twins` with `struct_twins.py --write`.
