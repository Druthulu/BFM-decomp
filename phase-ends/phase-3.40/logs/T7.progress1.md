# T7 progress (attempt 1, expert handback forced while coder T7.c1 still running)

## Done so far
- Classified 546 missing-parameter rows → 539 (file,func) bodies: `.run/P40/T7/classify.py` → `.run/P40/T7/classify.json`, `.run/P40/T7/candidates.tsv` (cols class file func regs).
  - READ 179 bodies / 43 distinct names (pin read before written = incoming value; the only real missing-parameter case).
  - SCRATCH 343 (pin written/initialised before read = scratch $aN, no incoming value; refusal cause, not a parameter).
  - NODEF 17 (regex missed the def, mostly `*_jr_*.c` files); c1 resolves them.
- Research: R3.40-009 (T6 rung D recipe: callers hand-edited first, then `restruct.py --apply --rung D --callee F --body FILE --label L`; --all-defs/--tu for copies; T6 never ran --write-residue).
- Coder T7.c1 briefed (READ + NODEF), running; 9 commits `T7.c1: rung D t7c1_<addr>` at handback (head 7bbad4914f).

## In flight
- T7.c1 (pa-coder, background). Log: phase-ends/current/logs/T7.c1.md. Do not touch its files until it reports. Its commits are on main.

## Hypotheses rejected
- "every pin $4-$7 is a missing parameter": the classifier labels by register number only (lever_census.py residue_text, ARG_REGS); 343/539 bodies write the pin first.

## Next five steps
1. Read T7.c1's report (or its log + `git log --grep T7.c1`); brief c2 for any unconverted READ/NODEF names.
2. Survivors: set instrument for SCRATCH rows to `T7 refused: pin written before read (scratch $aN, no incoming value)`, for c1 refusals its cause (writer keeps existing rows verbatim, lever_census.py:1186-1199).
3. `PY tools/lever_census.py --check --strict --residue config/lever_residue.tsv --write-residue config/lever_residue.tsv` → residue-unused 0.
4. Per-site cast residue for touched segments: `PY tools/restruct.py --rung S --residue --only <seg>` then `type_census.py --check-casts --residue`.
5. Full verify line; logs/T7.md, tasks/T7.md (rows before 546 / after, refusals by cause); task_log finish; commit.

## Gotchas
- Plan says 548 rows; the live TSV has 546 at T7 start.
- research_add adopt takes no path: `research_add.py adopt --task T7`.
