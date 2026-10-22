---
ts: 2026-10-22T05:39:59.704Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: afdda1e6f94a02c83
model: claude-opus-5-5[1m]
effort: medium
turnId: 9c3056f4-4231-4295-ac35-2136fa566755
usage: {input: 4, cacheRead: 111984, cacheWrite: 516, output: 176}
---

FYI: T11's expert added a note for every external coder. It says to regenerate a function's scratch copy of its source from the current `src/` before starting on it. Copies go stale once later batches are banked, and G08c found that all the earlier scores in one folder had been measured against an old body. To undo it, run `/usr/bin/python3 tools/pa_ext.py set --drop-note 1`.
