# TASK_PROGRESS — T4 attempt 2

Task: T4 rung S sweep, md_*, main and shared bodies (forms P and X)
Attempt: 2   Agent: expert-opus55   Commit before this: fd8c632c9b (archived progress1)

## Done so far
- Archived attempt-1 progress → logs/T4.progress1.md (fd8c632c9b).
- Read plan Context/Interfaces/Cookbook/Research, T4 entry, T1-T3 summaries.
- Briefed coder T4.c2 (coder-opus55, background) with all remaining c1 steps: wait for live md cycle (pid 1360696, label t4_md_, log .run/P37/restruct/cycle_t4_md.log) → main cycle (label t4_main_, `--only main`) → shared plan + HEADERS=1 cycle(s) t4_sh_ (+ t4_shc_ for shared .c) → `--residue` per scope (labels t4_res_<name>) → `--check-residue` 0 for md_*, main, src/shared/*, ov_* → type_census refresh, --check-structs, --check-casts line → final clean R22 (.run/logs/t4_final_r22.log) → log phase-ends/current/logs/T4.c2.md.

## In flight
- T4.c2 coder running at forced hand-back (its report will be lost). It waits on md cycle via tail --pid, then launches further detached cycles itself.

## Hypotheses rejected
- (from attempt 1) `--only "src/*.c"` over-matches; gate_main.py is a slate tool, not rung S's gate (c2 told to record whether it applies).

## Current hypothesis
Mechanical sweep as T3; done-when met T3-style; fleet-wide "P/X raw = 0 except T5-owned" cannot hold literally (TYPE-NOT-CANONICAL residue) → deviation, verify rc 1 expected for check-casts.

## Next 5 steps
1. Archive this file → logs/T4.progress2.md, commit.
2. `git log --oneline -20 | grep T4`; `pgrep -af '^bash tools/restruct_cycl[e].sh'`; check for phase-ends/current/logs/T4.c2.md (grep/tail). If a cycle is live, wait on it with `tail --pid=<pid> -f /dev/null` in background; never launch a second.
3. When cycles are done and c2's log/commits show the remaining steps unfinished, brief T4.c3 naming c2's commits/log for the remainder only.
4. Verify: `PY tools/type_census.py --check-casts --quiet` then `bash tools/run.sh t4_verify -- bash -c 'make clean && make extract-all JOBS=16 && make check-all JOBS=16'`.
5. Write logs/T4.md, tasks/T4.md (deviations: fleet-wide clause; main gate), `task_log.py finish T4`, commit.

## Gotchas
- harness: forced hand-back while coder runs, twice now; coder reports lost — verify from git and logs.
- harness: reading .claude/skills via cat is hook-denied; use Read.
- `.run/P37/restruct/ledger.jsonl` needs `git add -f`.

## State to carry verbatim
- Baselines (P/X sites at T3 close): ov 251,830 · shared/ov 11,428 · md 9,047 · top-level main 1,755 · resident 78 · shared/slot_* 23.
- check-casts at T3 close: raw P=260372 I=51514 X=13790 M=15130; unbacked 0; lying 229.

## Coder runs so far
- c1 (95612c3097) gone; c2 running at handoff — logs/T4.c2.md
