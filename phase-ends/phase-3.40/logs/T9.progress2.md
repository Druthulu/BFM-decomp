# TASK_PROGRESS — T9 attempt 2

Task: T9 head-class lever cracks with propagation
Attempt: 2   Agent: pa-expert   Commit: e8eb183581 (last green on HEAD: c8dc06c87d T9.c16, R22 218/218)

Why a handoff: harness forced the report while coder T9.c18 was still running (its own background build).

## Done so far
- Attempt 1 progress archived: logs/T9.progress1.md (full state, rejected hypotheses, gotchas, cookbook candidates: read it).
- T9.c16 verified landed: c8dc06c87d, 146 copies, -148 rows, R22 218/218, residue 1469 data rows.
- 38 classes confirmed (.run/P40/T9/classes.tsv, 70 name lines, 38 unique hashes).

## In flight
- T9.c18 (pa-coder, label t9_p4, log logs/T9.c18.md, scratch .run/P40/T9/c18/): bank W4 pair a88fd15989e7 + db4e4996d215 (12 rows, 6 copies) by finding a caller spelling that keeps callers' bytes (def already MATCH 43); optional one try on src/shared/ov/func_8012E364__6d96fc6c.h (3 objects). Cap ~75 min; reverts what is not IDENTICAL everywhere. Check `git log --oneline | grep T9.c18` and `git status --porcelain src config`; if no commit and no coder alive with dirty src, its edits are orphaned: revert them (git checkout of listed files) — never commit unverified src.

## Current hypothesis / decisions
- 4a789ceca27f func_80177B5C (133 rows): NOT counted as lever-free (identity combine = C-spelled launder; counting it would redefine the term). Surface in report as a developer decision; rows kept.

## Next 5 steps
1. Verify T9.c18 outcome (commit or clean tree).
2. Write phase-ends/current/tasks/T9.md from templates/task.template.md: rows cleared per class (c8 -400, c13 -25, c16 -148, c18 ?), uncracked classes with best scores (progress1 list), agent-hours (~20 h coders + c18).
3. Run verify line (gate via tools/run.sh, foreground, each call < 285 s or background shell).
4. `PY tools/task_log.py finish T9`; `bash tools/commit_task.sh T9 "<line>"`.
5. Return done, noting the 80177B5C decision.

## Gotchas
- See logs/T9.progress1.md Gotchas (lever_census --write-residue drops line-1 comment; propagate keys on first LEVER-FREE row; permuter lane 1 dead).
