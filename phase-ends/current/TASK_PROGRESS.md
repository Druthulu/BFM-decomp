# T7 progress (attempt 2, handback forced while coder T7.c2 still running)

## Done so far
- progress1 archived (logs/T7.progress1.md, b2803d341b).
- T7.c1 finished (logs/T7.c1.md): 161 bodies CONVERTED (160 residue rows), 1 REFUSED (func_8017EC90 ov_SC03_007: params already declared, dropping pin DIFFERS, lui v0 moves 2 slots), 34 reclassified SCRATCH. Final gate 218/218 (t7c1_final).
- Fresh residue: `lever_census.py --check --strict --residue config/lever_residue.tsv --write-residue .run/P40/T7/residue_new.tsv` (fresh path: writing to the same path keeps unused rows verbatim) → 2270 data rows (was 2430), missing-parameter 546 → 386. No comment line in it; instrument.py re-adds line 1 from config/lever_residue.tsv.
- `.run/P40/T7/instrument.py <new> <out> config/lever_residue.tsv` sets instrument on surviving missing-parameter rows: SCRATCH 377+6 hand-read → `T7 refused: pin written before read (scratch $aN, no incoming value)`; REFUSED 1.
- 7 rows the classifier never reached, read by hand: 6 SCRATCH (80038698 $6, 8017D81C a0, 801896EC a0/a1, 80180390 $5, 8017D040 a1, 8012A860 $4 = copy of declared a0); func_80038308 (src/800_c.c:2476) is READ: declared `s16 a0` unused, pin $4 reads it as a32.

## In flight
- T7.c2 (pa-coder, background): func_80038308 def + decls (src/800_b_2.c:975,1792,1838) take the pin as the param; log logs/T7.c2.md. Do not touch src/800_c.c, src/800_b_2.c until it reports (git log --grep T7.c2).

## Next five steps
1. Read T7.c2 outcome; if blocked add its key to instrument.py with its refusal cause.
2. func_80182334 (ov_SC05_008) row: c1 converted its arg pin; the remaining pin is $0, but the kept row still says missing-parameter. Drop that row from the residue input and re-run --write-residue to a fresh path so the writer reclassifies it.
3. Re-run write-residue (fresh path) + instrument.py → copy to config/lever_residue.tsv; check `--check --strict --residue config/lever_residue.tsv` residue-unused 0.
4. Per-site cast residue for touched segments: `restruct.py --rung S --residue --only <seg>` (main, md, ov, shared) then `type_census.py --check-casts --residue`.
5. Full verify line; logs/T7.md, tasks/T7.md (rows 546 before / ~385 after; refusals: SCRATCH 383, REFUSED 1, 80038308 per c2); task_log finish; commit.

## Gotchas
- PreToolUse guard blocks any `cat` of the 290k-char TSV even inside a pipeline: use Python.
