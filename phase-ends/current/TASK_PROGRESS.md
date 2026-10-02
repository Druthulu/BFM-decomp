# TASK_PROGRESS — T3 (attempt 2)

## Done so far
- Attempt 1 progress archived: logs/T3.progress1.md (commit 35c65708e1). Read it for sweep history, gotchas, cycle launch form, baselines.
- T3.c5 finished blocked, commit a8dbad4a21 (plan_S/apply done agreement; site rows carry base type). Log logs/T3.c5.md.
- c5 wall: 2455 ov RESIDUAL(NO-FIELD) sites, all on Unkstruct_80126B58 / Unkstruct_800B5CB8 inside generated head_types region of include/struct_types.h. IN-LEAF 1955 (70 groups) = residual by cause (3.38 decision, union/split deferred). GAP-PAD 500 (22 groups, all 80126B58) addable.
- Decision (Deviation, expert's): option (a) — additive mode in tools/head_types.py (keep existing fields byte-for-byte, split pads only), regenerate region, re-draw covered bodies, one R22. Rejected: full head_types regen (rewrites 157 lines, breaks 141260 MEMBER spellings); hand edit (generated file); (c) leave 500 residual (would weaken "missing fields added").

## In flight
- Coder T3.c6 (background, log phase-ends/current/logs/T3.c6.md): the additive mode + re-draw + R22. It may still be running (its own detached cycle). Check `git log --oneline -8 | grep T3.c6`, tail of logs/T3.c6.md, and `pgrep -af 'restruct|make check-all|restruct_cycle'` before touching restruct.py, head_types.py, src, headers. Its hand-back went to the dead attempt-2 expert: read its log for VERIFIED lines.

## Current hypothesis
- After c6, remaining: coverage pass (ov bodies with P/X sites but no S row → RESIDUAL rows with cause; check uncovered ov P/X = 0), then verify and summary.

## Next five steps
1. Confirm c6 outcome from logs/T3.c6.md + git log (R22 218/218, NO-FIELD before/after, check-ledger 0).
2. Coder T3.c7: residual rows for uncovered ov bodies (cause: TYPE-NOT-CANONICAL / NO-TYPE-IN-MAP / NON-STRUCT / untyped) + a check reporting 0 uncovered ov P/X sites; ledger only.
3. Per-cause counts (.run/T3/resid.py); check-casts P/X before (P 408,974, X 13,800) vs after.
4. Verify: `PY tools/type_census.py --check-casts --quiet` (rc 1 expected, read ov P/X); `PY tools/type_census.py --check-structs --quiet && make clean && make extract-all JOBS=16 && make check-all JOBS=16` via run.sh --bg + --wait.
5. Write logs/T3.md tail + tasks/T3.md; `PY tools/task_log.py finish T3`; `bash tools/commit_task.sh T3 "..."`.

## Gotchas
- See logs/T3.progress1.md. harness: the expert was forced to hand back while its coder was still running; poll the coder's log/git rather than waiting for a notification.
