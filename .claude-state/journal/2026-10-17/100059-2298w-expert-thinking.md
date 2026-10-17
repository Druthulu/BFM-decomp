---
ts: 2026-10-17T16:00:59.041Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac3c2f25cd86a3f15
model: claude-opus-5-5[1m]
effort: medium
turnId: 8d79bbc0-6d30-411b-a4e2-472ff86f0d65
---
I'm planning the generalized bank tools for T11, deciding to write setup.py and the generic dt.sh/sc.sh scripts myself while leaving swap.py and rows.py for the first banker coder to implement, to stay within my budget.

I'll scale T10's approach: splitting the 394 remaining singleton functions (plus 2 unattempted func_80136824 copies) into 50 shards of ~8, each handled by scratch-only crack coders (max 4 concurrent) that score matches and write results rows, while a serial banker swaps in wins, updates survivor rows, and commits at barrier points every 8 shards to avoid scoring against a half-rebuilt tree from R22's `make clean`. Parked rows that were never attempted get their wall cause assigned by the final banker.
