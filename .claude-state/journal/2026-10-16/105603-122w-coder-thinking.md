---
ts: 2026-10-16T16:56:03.467Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6262df0e8a0d472a
model: claude-opus-5-5[1m]
effort: medium
turnId: 7850ba3c-c3b4-45a3-a86f-0ae36df32364
---
I'll leave config/type_folds.tsv untouched since it's not part of this task, and since restruct would still compile correctly even if a define target becomes an alias later.

I'm also thinking about canon choice for shared components — names need to live in canon headers like include/struct_types.h, otherwise they'd be refused as "not defined in a canon header." I should dry-run this check before finalizing.

For the TSV build, I'm structuring rows with tier, lhash id, size, n, and names — the lhash split on ':' doesn't matter since only the base portion gets reported.

I'll run `lift_types.py --fold` feeding it one row per shared-object component instead of whole classes, to keep separate names like G62 apart. Doing a dry run first.
