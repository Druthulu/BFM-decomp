# T8 progress (attempt 1, expert-opus55) — handback forced by harness while T8.c3 runs

## Done
- Baseline strict (.run/logs/t8_strict0.log): pins 1868, asm 1409, gte-levers 434, direct GTE 0, per-TU asm defs 164 {launder 154, instruction 9, barrier 1}, residue 0 — FAIL. delever --plan: 595 files / 870 removable sites.
- Retriever (no report file): no tool records a lever cause; P36 composition is prose (docs/gen3-handoff.md:36-37); delever ledger .run/P36/delever/ledger.jsonl sites carry {kind, verdict, why, oracle} only; tools/delever_cycle.sh is P36-hardwired (git add -A src, phase-36 message) — do not run it.
- T8.c1 done, commit 71636b5fbd (log logs/T8.c1.md): lever_census strict_failures emits one asm-macro entry per per-TU def (fn = macro name); `--write-residue PATH` writes (file, func, kind) rows with pass/instrument/cause from the delever ledger; cause vocab head-class / singleton / missing-parameter / gte-clobber-steer / asm-macro-def / asm-body-routine / carve/signature-parked, suffix ` [3.40-agent]`; fixed fn None vs "" key mismatch; selftest viii/ix. Probe (on a dirty tree) 2587 rows, round-trip residue-unused 0 rc 0. make tools-health was red only from c2's uncommitted src (share_census S1 174) — recheck.
- T8.c2 done, commits 3695293d75 bb84bb1ab5 ac3a3b5f8a 586729bb45 836575d461 075d9a2c74 608683bb2a ef90e38e83 (log logs/T8.c2.md): recalibrated 146/146, selftest --real 114/114; batches t8_tus1-4, t8_hdr1 all final N/N, R22 218/218 each; removed gte-lever 343 + barrier 2; recipes t8_r2 146 bodies LEVER-FREE, header phase killed at ~60 min (6 of ~101 headers), restored, R22 green; 55 gte_rt_m comments fixed. After: pins 1868, asm 1405, gte-levers 91, direct GTE 343 (inline, regression), lever_census --check OK.

## In flight
- T8.c3 (coder, background, log logs/T8.c3.md): re-consolidate the 343 inline GTE statements via gte_consolidate (--inventory/--header/--apply, labels t8_gte<k>), strip trailing spaces; revert 139 no-op brace-wrap banks of t8_r2 (keep the 7 real ones); R22; make tools-health. Check `git log --oneline -15` and `pgrep -af "gte_consolidate|delever|make"` before touching src/tools.

## Next five steps
1. Read T8.c3's VERIFIED (or logs/T8.c3.md if it ended unreported): direct GTE 0, R22 218/218, tools-health OK.
2. Coder T8.c4: `lever_census --check --strict --residue config/lever_residue.tsv --write-residue config/lever_residue.tsv -j 16` on the clean tree; gate rc 0; `lever_progress --snapshot` + docs/levers.md; D1: `type_census.py -j 16 --out-dir .run/P39/census`, `readability_progress.py --snapshot`, `timeline.py`, `progress.py --readme`; make kit-corpus/tools-health; docs/ops note + docs/ops/INDEX.md (H7: new lever_census flag).
3. Run verify: `PY tools/lever_census.py --check && PY tools/lever_census.py --check --strict --residue config/lever_residue.tsv`.
4. Write logs/T8.md, tasks/T8.md (progress: line; Deviations: plan never drains — md_MAIN_003_jr_800D1E18.c 4 REFUSED asm-data sites redrawn forever; --propagate impossible, recipe rows carry no after_text; header recipes bounded; pins 0 removed — all previously NEEDED).
5. task_log.py finish T8; commit_task.sh T8 with D1 outputs.

## Gotchas
- generalizable: delever removing a gte-lever's extra clobbers leaves raw inline GTE asm, undoing the one-spelling gate; re-run gte_consolidate after any delever pass.
- generalizable: rung R recipes bank no-op brace wraps on RESIDUE bodies with no live sites; filter "0 pin(s) gone" banks.
- harness: expert hook denies reading tools/*.sh source even for --help-less scripts (delever_cycle.sh has only a usage line).
