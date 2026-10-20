---
ts: 2026-10-17T17:50:28.673Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: af8c379eaae6cf6ee
model: claude-opus-5-5[1m]
effort: medium
turnId: 4f5d1d7b-243b-4976-9079-51d9b9c05b4b
---
There's one leftover unused row from func_800391D4 that doesn't fit the singleton-drop rule for MATCH functions since it's the only missing-parameter case. I should drop it, but rather than a one-off scoped fix, I'm considering making bank_rows.py handle this generically for MATCH functions going forward.
