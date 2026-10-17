# T7 progress (attempt 3, handback forced while coder T7.c3 still running)

## Done so far
- progress2 archived (logs/T7.progress2.md, 9a53eca2b7).
- T7.c2 done green (535a85c937, logs/T7.c2.md, gate 218/218 t7c2_gate): func_80038308 pin became s32 arg0.
- Residue rewritten from the current tree: input .run/P40/T7/residue_in.tsv = config TSV minus the func_80182334 pin row (so the writer reclassifies it: now singleton(pin), real pin is $0) → `--write-residue .run/P40/T7/residue_new3.tsv` → instrument.py → residue_final3.tsv → copied to config/lever_residue.tsv. Committed 8ca59342a5.
- `lever_census.py --check --strict --residue config/lever_residue.tsv` OK, residue-unused 0 (.run/logs/t7_strict.log).
- Rows: missing-parameter 546 → 384 (survivors: SCRATCH 383 `T7 refused: pin written before read (scratch $aN, no incoming value)`, REFUSED 1 func_8017EC90 ov_SC03_007 `params already declared; dropping the re-read pin DIFFERS`). Total data rows 2430 → 2269(+header).
- Per-seg cast residue `restruct.py --rung S --residue --only {main,md,ov,shared}` (.run/logs/t7_casts.log): ov 3 rows/22 sites merged (TYPE-NO-MEMBER), others 0. `--check-residue --only ov` → uncovered 0.
- Cast gate `type_census.py --check-casts --residue` rc 1: uncovered P=3 (ov), unbacked 7, lying 0 (.run/logs/t7_casts2.log). T5 close had both 0, so the cause is T7 body rewrites: the ledger site keys (`bclass:base`, e.g. local:aN → param:aN; type_census.py:1998-2027) no longer match.

## In flight
- T7.c3 (pa-coder, background): list the 3 + 7 sites, back them with restruct's own rung-S writers (apply/residue, scoped), no hand-written ledger rows; log logs/T7.c3.md; commits as T7.c3 if src changes. Check `git log --grep T7.c3` and logs/T7.c3.md.

## Next five steps
1. Read the T7.c3 outcome (log). If blocked, record the sites as refusals/causes in the summary; that is a done-when gap → question/blocked.
2. Re-run `type_census.py --check-casts --residue` → rc 0.
3. Full verify line (strict lever + casts + R22 218/218) via tools/run.sh, foreground, timeout high.
4. Write logs/T7.md (timeline from progress1/2/3 + c1/c2/c3) and tasks/T7.md (rows 546 → 384; refusals SCRATCH 383, REFUSED 1; c2 converted 80038308; 80182334 reclassified singleton(pin)).
5. `task_log.py finish T7`; commit_task.sh T7.

## Gotchas
- PreToolUse guard blocks `cat` of the 290k-char TSV: use Python.
- casts.sh piped into tail hid rc; check rc directly.
