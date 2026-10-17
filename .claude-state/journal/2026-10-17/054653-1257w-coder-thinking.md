---
ts: 2026-10-17T11:46:53.197Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a9b75b3e3c01d6fa8
model: claude-opus-5-5[1m]
effort: medium
turnId: 9b80ef94-0ae1-44c6-acfd-ddecb9279a50
---
Since the body_tree data may be stale against current source, I'll just use delever_search directly against the real TU as the main scorer, treating score 0 as a match. I still want to use match_one with the target for verifying wins, but I'll calibrate with delever_search first and check its help options before building a per-function script.
