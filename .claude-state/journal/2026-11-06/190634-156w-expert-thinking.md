---
ts: 2026-11-07T02:06:34.783Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ac8891974f3afdd66
model: claude-opus-5-5
effort: medium
turnId: e0c8644d-6ef7-4f4d-ab7b-71dcf29b7e37
---
I'm seeing a verbatim manifest check fail, with 12 rows no longer matching the original, likely from decompilation. That doesn't look related to T12; my guess is the T11 cracks caused it. The suggested fix is running `--update` on some tool, so I'll grep the Makefile for "verbatim" to find which one.
