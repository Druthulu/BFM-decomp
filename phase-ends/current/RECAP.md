MILESTONE: green

## Recap
Phase 3.39 was the cast campaign: the decompiled C still read memory through raw pointer arithmetic such as `*(s16 *)(p + 0x10)`, and the goal was that every such "raw cast" either becomes a named struct member or global, or is kept on purpose with a written reason. Early on the sweep hit a wall: about 292,000 sites point into structs that have no single agreed definition yet, so the plan was changed (the "replan", reading A, 2026-10-02) to accept those sites as recorded residue, each one listed in the restruct ledger with its cause, and to leave giving those structs their canonical definitions to Phase 3.40. Under that reading the phase delivered: zero uncovered raw casts, every intentional cast spelled by one of five registered macros backed by a ledger row, lying function declarations cut from 229 to 11 (all ledgered), GTE (the PlayStation geometry coprocessor) instructions spelled one way through one header, and every remaining compiler-steering "lever" (pins and inline asm) listed in a lever residue file. All 218 game binaries still rebuild byte-identical. Raw cast counts fell from 503,016 to 336,219 overall.

Milestone verification, all at commit 78a8415257 from a clean source tree (only an unrelated discussion index line and an untracked agent file were dirty; gate outputs were restored after the run, not committed):
- `PY tools/type_census.py --check-casts --residue` exit 0: uncovered P=0 I=0 X=0 M=0, unbacked macros 0, lying 11 (ledgered 11) (.run/logs/p339_c1_casts.log).
- `PY tools/restruct.py --rung S --check-residue --only <seg>` exit 0 for `ov_*`, `md_*`, `main`, `src/shared/*`: uncovered 0 sites / 0 bodies each (.run/logs/p339_c2_resid.log).
- `PY tools/lever_census.py --check --strict --residue config/lever_residue.tsv` exit 0: residue 3528, residue-unused 0, direct GTE in bodies 0 (.run/logs/p339_c2_resid.log).
- `make clean && make extract-all JOBS=16 && make check-all JOBS=16` exit 0: `check-all: 218 passed, 0 failed of 218` (.run/logs/p339_c4_r22.log).
- `PY tools/phaseend_index.py verify` printed RED (0/1) (.run/logs/p339_close_verify.log): it parsed the whole multi-command `verified by` text as one clause and expected the check-all line in the first command's output. Its first command exited 0. Each clause was then run alone, and every one was green (above).

## Records
- T5's flagged commits: 3f547f1152 committed about 794k lines of `.run/P39/census` scratch to git, and 5201d28b19 untracked it again. History is unchanged (no rewrite). `restruct_cycle.sh:96` still stages `.run/P37/census` (tracked files only).
- Replan (reading A, REPLAN 2026-10-02): T4 hit the TYPE-NOT-CANONICAL wall and was left blocked. T10 added the per-site residue gate `--check-casts --residue`, and the milestone reads residue covered by a cause-named ledger row as closed. The literal lever `--strict` 0 also moves to 3.40 (reading A for levers, 2026-10-01).
- Critic's T7.1 ruling (2026-10-02): T7 was reopened as T7.1. Its done-when clauses are read the way lever_census's own docstring defines them ("direct" means not through a gte_inline.h macro; per-TU defs means those of kind gte), so T7's "direct GTE" total was not reachable as first written. T8's done-when gained the per-TU asm macro definitions (164, all ledgered).
- Two census dirs disagree by about 5 P sites (the gate's `.run/P37` has 257,470 and the series' `.run/P39` has 257,475). This was not investigated (T9, T11).
- H7 deviations: T2 changed `tools/type_census.py`, `tools/lever_census.py` and two `config/` ledgers without listing HOW_WE_WORK.md or docs/ops in its Files. T10 later added the "type_census casts" Tools row and T8 the lever-residue ops note. T11 changed `tools/progress.py` with no HOW_WE_WORK.md or docs/ops line.
- harness: `phaseend_index.py verify` does not split a Milestone `verified by` list joined by commas and "and". Its `--help` does not say how clauses are delimited.

## Decisions that still bind
- Kept casts and lying declarations stay only with a ledger row: rule R123 (rules_add).
- Raw cast residue is covered per site by a cause-named RESIDUAL row: rule R124.
- GTE asm in bodies is spelled only through include/gte_inline.h: rule R125.
- The lever gate is `--strict --residue config/lever_residue.tsv` until the literal 0 in 3.40, and asm-macro rows follow the T8 shape: rule R126.
- main's rung-S gate is the per-object oracle plus a clean R22, not gate_main.py (environment fact, already in docs/ops/gate-main-only-with-gate-main.md and the T4 ops note).
- `timeline.py --check` masks the newest row's Commits cell (environment fact, docs/ops/p39-t1-2026-10-01-restruct-stale-supersede-timeline-check.md).
- Next task needs: the 3.40 planner sizes the canonical-types campaign from residue_census (TYPE-NOT-CANONICAL 291,819 sites over about 13k map types, where the top 81 types cover half) and from config/lever_residue.tsv (2,433 rows, 3,528 sites, 70 tagged [3.40-agent]), which is the input for the literal `lever_census --check --strict` 0.
- Next task needs: the standing request (developer, 2026-10-02) for every phase close is to update the README graphs, story section 10 and retrospective section 7, and the wiki pages. The 3.40 planner gives it a task, as T12 did here.
- Promoted at this close: cookbook C0518-C0528, skills `tools-edit-kit-corpus` and `d1-snapshot`, rules R123-R126.
