---
ts: 2026-10-22T06:31:31.897Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: afdda1e6f94a02c83
model: claude-opus-5-5[1m]
effort: medium
turnId: 3af47ccd-3638-4da4-bf6a-912f9e1bc500
usage: {input: 2, cacheRead: 119518, cacheWrite: 383, output: 171}
---

FYI: T11's expert added a note for every external coder. It says to keep scratch files only in the batch's own folder under `.run/P40/T11/`, never in `/tmp`, and to use project-relative `.run/...` paths, after G14b went outside the project. To undo it, run `/usr/bin/python3 tools/pa_ext.py set --drop-note 2`.
