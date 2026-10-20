---
ts: 2026-10-20T01:10:39.882Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a8d7becfcec4f8e6c
model: claude-haiku-5-5[1m]
effort: medium
turnId: 931fba74-47f8-4707-8660-f2bd85a047e7
---
Found it — both psyq_integrate.py and psyq_link_region.py call mkdtemp but never call rmtree to clean up, which explains the leftover tmp* directories matching the random 8-character naming pattern.

The 303k loose wave_*.json files still have an unclear source though. I still want to check whether api_agent writes per-wave shard message files directly at the top level rather than inside subdirectories — let me do one more targeted grep for that pattern before concluding.
