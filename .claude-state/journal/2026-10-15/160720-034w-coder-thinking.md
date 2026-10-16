---
ts: 2026-10-15T22:07:20.531Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a355e5f4e671b32e5
model: claude-opus-5-5[1m]
effort: medium
turnId: e98fac13-aa90-492f-ab26-6b8eacc10264
---
I'm realizing --write would create dead defs and duplicate classes, which is the problem T3.c2 flagged — the expert's note about dead names needing to be listed under "## Dead kept" in docs/struct-twins.md suggests --write should also append those dead-kept entries when it runs.

Deduping within the batch feels like scope creep beyond the brief's step 3, so I'll keep it simple: --write appends define target names under that section, and I need to check the existing format of that section before implementing it.
