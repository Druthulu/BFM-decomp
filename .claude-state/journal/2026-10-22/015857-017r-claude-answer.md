---
ts: 2026-10-22T07:58:57.620Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: afdda1e6f94a02c83
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fa79e23-5bf1-4e11-b3c1-c4ef323d19bd
usage: {input: 4, cacheRead: 129364, cacheWrite: 285, output: 172}
---

FYI: T11's expert added a third note for every external coder. Before reading a file over 20,000 characters, outline it and read it by line range, because a whole read is blocked and counts as friction. Also, a coder's last word must be done, question or blocked, never "handoff". To undo it, run `/usr/bin/python3 tools/pa_ext.py set --drop-note 3`.
