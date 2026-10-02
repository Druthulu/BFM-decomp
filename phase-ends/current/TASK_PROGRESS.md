# TASK_PROGRESS — T3 (attempt 1)

## Done so far
- T3.c1 (3ff15ee462, 3507628e40, fe2e814776): restruct rung S per-site classes, KEPT(<class>)/RESIDUAL(<cause>), CAST_* respell of kept P sites, `--only` glob; exemplar ov_SC05_010_jr_80180F84.c.
- T3.c2 (d476f3c92e): `--bbt` / RESTRUCT_BBT pin (.run/P39/census/body_base_type.json, untracked, never rewritten) + s_finished.
- T3.c3 (568de6c713, 357451cbb9, e88040d15a): apply uses the pin; s_judged.
- T3.c4 (0938e511ed..ffc0d3ecc1): unbacked 96 → 0 (alias-def params, S_PRIOR carry, nested base drift).
- Sweep: t3_S1..S54 committed by restruct_cycle.sh, every batch R22 218/218 (logs .run/P39/restruct/cycle_t3_{a,b,c,d,e}.log). Ends at HEAD b0951592bd (S55..S60 committed no src change).
- Full timeline: phase-ends/current/logs/T3.md.

## In flight
- T3.c5 (coder-opus55, background, log phase-ends/current/logs/T3.c5.md): fix the 6-file plan/apply loop (S55..S61), site_row type on every site, batched NO-FIELD field additions in canonical headers (one R22), re-draw affected bodies. It may still be running: check `git log --oneline -8` for T3.c5 commits and `pgrep -af 'restruct|make check-all'` before touching tools/restruct.py, src or headers.

## Hypotheses rejected
- Drift via unpinned bbt in apply: wrong; c3 found s_body_edits checked the live struct_map first (NO-TYPE-IN-MAP).

## Current hypothesis
- After c5, remaining done-when gaps: (a) coverage — ov bodies with P/X sites but no S row (files never drawable: all bases TYPE-NOT-CANONICAL) need RESIDUAL rows + a check that counts uncovered ov P/X sites = 0; (b) summary numbers.

## Next five steps
1. Read T3.c5 return (VERIFIED lines); confirm check-casts unbacked 0.
2. Coder T3.c6: residual rows for uncovered ov bodies (cause per site: TYPE-NOT-CANONICAL / NO-TYPE-IN-MAP / NON-STRUCT / untyped) + `restruct --check-residue --only "ov_*"` → 0 uncovered; R22 not needed (ledger only).
3. Re-run .run/T3/resid.py for per-cause counts; check-casts for P/X before (P 408,974, X 13,800) vs after.
4. Run verify: `PY tools/type_census.py --check-casts --quiet` (rc 1 expected, read ov P/X), `PY tools/type_census.py --check-structs --quiet && make clean && make extract-all JOBS=16 && make check-all JOBS=16` (bg + wait).
5. Write logs/T3.md tail + tasks/T3.md; `PY tools/task_log.py finish T3`; `bash tools/commit_task.sh T3 "..."`.

## Gotchas
- restruct_cycle.sh ignores SIGINT during R22; stop it with TERM on the script pid and its `bash -c` parent, then kill the make/xargs children; `restruct --restore` afterwards.
- `pgrep -f 'restruct.py --apply'` in a kill loop matches your own shell (exit 144).
- Per-batch overhead (calibrate + R22 + census) is ~20 min; batch 200 files once apply time is small.
- plan_S weights come from the drifted live map (order alphabetical); harmless.
- harness: the hook denies `--help | head` style pipes on tool help and `cat` of SKILL files; use Read.

## State to carry verbatim
- Cycle launch: `setsid nohup bash -c 'RESTRUCT_BBT=.run/P39/census/body_base_type.json LABEL_PREFIX=t3_ TASK=T3 bash tools/restruct_cycle.sh <S> <E> 200 S "ov_*"; echo "cycle exit=$?"' > .run/P39/restruct/cycle_t3_<x>.log 2>&1 &`
- Baseline denominators: P 408,974 · I 60,666 · X 13,800 · M 19,542; ov raw 478,494.
- check-casts after c4: macros CAST_ALIAS 555 SIGN 5238 WIDTH 3966 MISALIGNED 258 NONSTRUCT 208, unbacked 0.
