---
ts: 2026-10-17T10:27:40.930Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: afda95bec87dc8de3
model: claude-opus-5-5[1m]
effort: medium
turnId: 1e35bd3f-abc8-4289-9a6e-6d49268d15f8
---
The P36 T7 agent packs likely need rebuilding since the tree has changed — I should regenerate them with the build script for current exemplars. These residual failures suggest previous agents already tried and struggled with them, confirming they're genuinely hard; time to write the approach note and dispatch to a developer-level agent.

For splitting work, Wave 1 could cover the four largest coders by row count, Wave 2 the next tier, and the remaining 32 small classes handled sequentially since many are just variants of the bigger ones. I'm wary of concurrent pack builds racing on the shared ORDER.tsv file, so I'll build all the packs myself in a single batch call first, checking the list option to confirm how `--only` selects exemplars for each function.
