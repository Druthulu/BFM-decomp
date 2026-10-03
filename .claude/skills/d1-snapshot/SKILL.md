---
name: d1-snapshot
description: D1 readability snapshot: census to newest P dir, snapshot, timeline, progress --readme
---

# D1 Snapshot

Captured 2026-10-02 from /home/musashi/bfm-decomp/.run/p339_close/skill_d1-snapshot.md.

## When to use
Recording a readability row (phase close, campaign batches)

## Steps
# d1-snapshot
## Steps
1. `PY tools/type_census.py -j 16 --out-dir .run/P<newest>/census` (mkdir -p first; not the cycle's P37).
2. `PY tools/readability_progress.py --snapshot "<label>"` (refuses a stale census).
3. `PY tools/timeline.py`, then `PY tools/progress.py --readme` (no --help: it runs and rewrites docs/progress.md).
4. Record `readability_progress --check` before the commit that records the row (STALE after it, by design).
5. Inside restruct cycles, a per-batch snapshot "refused (a stale census?)" is non-gating; the cycle continues.
Source: P3.39 tasks/T5.md:25, T11.md:23, T4.md:24, T12.md:22-23.
