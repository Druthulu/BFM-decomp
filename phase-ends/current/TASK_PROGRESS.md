# TASK_PROGRESS — T4 attempt 1

Task: T4 rung S sweep, md_*, main and shared bodies (forms P and X)
Attempt: 1   Agent: expert-opus55   Ctx at handoff: ~45k   Commit: 95612c3097 (T4.c1 --only main), this progress commit after it

## Done so far
- Scope measured (check-residue before sweep, census at T3 close): md_* uncovered 9,047 sites / 1,309 bodies; src/shared/* 11,452 / 1,708 (shared/ov 11,428 + slot_* ~24); main = top-level src/*.c 1,755 P/X sites + src/resident 78 sites / 22 bodies; ov_* 0 (T3).
- md_* plan (.run/logs/t4_plan_md.log): 50 of 63 drawable files · 278 bodies · 927 deref sites · skipped type-not-canonical 1,965. Most md sites will be residue.
- Retriever (inline, no report): `--only` = matches_only restruct.py:3366-3376 (glob fnmatch on tu path or src/<dir>; `*` crosses `/`, so "src/*.c" over-matches md/ov). Rung S judges every body by per-object oracle (judge_files :311-355, linked fallback; main via delever_oracle.py:310) — no gate_main in restruct; gate_main.py is a slate tool (`gate_main.py <slate.json> [--apply]`). Shared .h are drawn only with `--headers` (plan_S :3408), serial, ~35 s each (every includer). restruct_cycle.sh: HEADERS=1 → --headers; R22 FLEET = count config/check.*.sha.
- T4.c1 coder (coder-opus55, background) committed 95612c3097: exact `--only main` selector + selftest + kit-corpus.

## In flight
- T4.c1 coder still running at handoff (its hand-back to attempt 1 will be lost, T3 gotcha). Detached cycle live: `LABEL_PREFIX=t4_md_ TASK=T4 bash tools/restruct_cycle.sh 1 40 200 S "md_*"` (pid 1360696), apply t4_md_S1 was running.
- c1 brief's remaining steps: md cycle to "nothing drawable" → main cycle (ONLY main, label t4_main_) → shared headers (HEADERS=1, ONLY "src/shared/*", label t4_sh_, batch < ~15 min) + shared .c without HEADERS → `restruct --rung S --residue --only <scope> --label t4_res_<scope>` for md_*, main, src/shared/* → type_census rerun → check-residue 0 for md_*, main, src/shared/*, ov_* → check-structs, check-casts line, clean R22 218/218 → log phase-ends/current/logs/T4.c1.md.

## Hypotheses rejected
- `--only "src/*.c"` for main — over-matches md_/ov_ (10,880 sites); `--only main` before c1 matched 1 body (substring branch).
- gate_main.py as main's gate for rung S — it gates function-draft slates; main's gate is the per-object oracle in apply plus clean R22 (c1 told to record which).

## Current hypothesis
The sweep is mechanical as in T3; done-when is met T3-style (every body with a P/X site has a latest S row, check-residue 0, unbacked 0, R22 218/218). The plan clause "P and X raw = 0 fleet-wide except T5-owned non-struct sites" cannot hold literally: T3's ov residue TYPE-NOT-CANONICAL (234,400 sites) remains raw; record as a deviation exactly as T3 did, verify rc 1 expected (I/M/lying too).

## Next 5 steps
1. Archive this file (git mv → logs/T4.progress1.md), commit.
2. Check `git log --oneline -15` and `pgrep -af "restruct_cycl[e]|restruct.p[y]"`; read phase-ends/current/logs/T4.c1.md if present (grep/tail).
3. If c1's agent is gone and the cycle has finished, continue the remaining c1 steps with a new coder brief naming 95612c3097 and the t4_* labels committed so far (never two cycles at once; recover with `restruct --restore`).
4. When all scopes are covered: run verify `PY tools/type_census.py --check-casts --quiet; make clean && make extract-all JOBS=16 && make check-all JOBS=16` (separate calls via run.sh) and record.
5. Write logs/T4.md and tasks/T4.md (deviation on the fleet-wide clause, before/after per kind), `task_log.py finish T4`, commit.

## Gotchas
- restruct_cycle.sh source reads are denied by a hook; learn from `--help` (prints only usage line: `START END [BATCH] [D|S|L] [ONLY]`; env LABEL_PREFIX, TASK, HEADERS) — harness: its --help omits env vars.
- `.run/P37/restruct/ledger.jsonl` needs `git add -f` before commit_task.sh.
- Forced hand-back while a coder runs loses the coder's report: verify from git and logs.

## State to carry verbatim
- Baselines (sites.jsonl at T3 close, P/X): ov 251,830 · shared/ov 11,428 · md 9,047 · top-level main 1,755 · resident 78 · shared/slot_* 23.
- check-casts at T3 close: raw P=260372 I=51514 X=13790 M=15130; unbacked 0; lying 229.

## Coder runs so far
- c1 coder-opus55 — running at handoff (commit 95612c3097 so far) — logs/T4.c1.md

## Reports commissioned
- none (one retriever-code answer inline)
