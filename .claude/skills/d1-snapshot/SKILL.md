---
name: d1-snapshot
description: D1 readability snapshot: census + --check-casts --residue to newest P dir, snapshot, timeline, progress --readme
---

# D1 Snapshot

Captured 2026-11-10 at P3.42 T9 (re-scaffolded with --force).

## When to use
Recording a readability row (phase close, campaign batches)

## Steps
# d1-snapshot
## Steps
1. Series census = newest `.run/P<N>/census` holding a type_census.json (readability_progress.py:63-69; P39 today; never create a newer P dir).
2. `PY tools/type_census.py -j 16 --check-casts --residue --out-dir .run/P<newest>/census` (P3.41-1): writes type_census.json and its sibling residue_census.json in one run, so the row's `uncovered` column is fresh, not blank. Exit 1 = an uncovered raw P/I/X/M site: fix or ledger it (restruct `--rung S --residue --restamp`, rule T2) before recording a row.
3. `PY tools/readability_progress.py --snapshot "<label>"` (refuses a stale census).
4. `PY tools/timeline.py`, then `PY tools/progress.py --readme` (no --help: it runs and rewrites docs/progress.md).
5. Record `readability_progress --check` before the commit that records the row (STALE after it, by design).
6. Inside restruct cycles, a per-batch snapshot "refused (a stale census?)" is non-gating; the cycle continues.
Source: P3.39 tasks/T5.md:25, T11.md:23, T4.md:24, T12.md:22-23; P3.41-1 gap (plain census left `uncovered` blank), fixed P3.42 T9.
