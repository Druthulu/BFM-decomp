# Pre-PA3 state

bfm-decomp: matching decomp of Brave Fencer Musashi (PS1, SLUS-00726 USA). Matching is finished: 218/218 binaries
rebuild byte-for-byte (main EXE, resident blob, 138 overlays, 78 modules; `docs/verification.md`). Generation 3 (the
project's Gen3, opened at legacy P35) makes that C legible: typed, cast-free, named, grouped by system, with the bytes
unchanged. Roadmap and Done-criteria: `GENERATION_PLAN.md`.

## Where it stands
- Closed in Gen3: P35 dedup, P36 levers off to a measured floor (`phase-ends/PhaseEnd_Phase36.md`), P37 census + struct
  map + declaration layer (`PhaseEnd_Phase37.md`), P37.5 the PA3 migration, 3.38 struct unification (2026-09-30),
  3.39 casts to declared data (2026-10-02). PhaseEnds are in `phase-ends/`, legacy index `phase-ends/LEGACY_INDEX.md`.
- Open phase: **3.40 Residue lane**, plan `phase-ends/current/PHASE_PLAN.md` (approved 2026-10-17, v3; v1/v2 kept
  beside it). Done: T1-T10 and T21 (summaries `phase-ends/current/tasks/`).
- Done so far in 3.40: a 95 % canonical-type band frozen in `config/tnc_band.tsv` (6,676 types) with folds in
  `config/type_folds.tsv`; rung-S re-sweeps of ov_*, md_*, main and src/shared; the legacy-T7 declaration items;
  missing-parameter pins turned into real parameters; oracle re-judge of unjudged levers; head-class cracks; the
  singleton pilot (T10), which projected past the cap and was ruled on.

## In flight: T11, the singleton crack wave (status `next`, paused)
- Paused 2026-10-22 by the developer for the PA3 restart. Log `phase-ends/current/logs/T11.md`; the newest resume
  note is archived as `logs/T11.progress13.md` (2026-11-05).
- Banked so far: B1 54 fns, B2 24, B3 24, B4 9 (`T11.c101`-`c104`), each gated 218/218.
- **7 matches sit unbanked on disk** in gitignored scratch `.run/P40/T11/` (G16x: 4, G18: 3; re-scored 0 by the expert).
  Next bank K=105, B=5, by an in-house coder from `.run/P40/T11/bank_brief.txt`, behind a barrier (the bank gate
  wipes `build/`). Held items: `.run/P40/T11/held.tsv`.
- Then the next shards from `.run/P40/T11/mm_queue_a9.txt` (one space-separated line), starting G18x, up to 4
  DeepSeek lanes via `PY tools/pa_ext.py run openrouter-deepseek/deepseek .run/P40/ext/T11.c<S>.md`; retry
  func_801372B0 with cookbook C0535; bank every 6-8 shards; end with TSV wall causes, residue-unused 0, R22, summary.
- Two G07 matches are held as MATCH-NEEDS-DECL (they need a shared-header prototype change outside the brief), for the
  developer's call (`logs/T11.md:52`).

## What is next
- In 3.40, in dependency order: T18 (3 K&R-empty lying decls, 1 unbacked CAST), T19 (wall vocabulary
  `config/lever_walls.tsv` + the lever_census check), T20 (walls for the 864 rows no wave re-judges), T12 (timeline
  "uncovered" series; not done yet), T17 (drift TNC types), T13 milestone gate, T15 ledger backup, T14 phase-close docs.
  T16 is superseded by T15.
- Then 3.41 types validated + Ghidra mirror, 3.42 rename harness + SHARED_FN form, 3.43 evidence and best-guess
  names, 3.44 file layout + clang-format, 3.45 generation validation from a fresh clone (`GENERATION_PLAN.md`).
- Inbox, routed to 3.45: license (no commercial reuse; CC BY-NC-SA 4.0 recommended for src/ and docs/,
  `phase-ends/current/INBOX.md`).

## Decided; do not undo
- Bytes are the only truth (R22): `make clean && make extract-all JOBS=16 && make check-all JOBS=16` -> `218 passed,
  0 failed of 218` after any shared body, header or EXE edit; main gated only via `tools/gate_main.py` (rung S on main uses the per-object oracle instead).
- No ROM-derived content in git (`tools/audit_public.py`); never `git clean -x` (ignored but present: `ghidra/`,
  `dumps/*.bin`, `tools/psyq/`); `make clean` is the only clean. `PROJECT_CONTEXT.md` is never edited.
- The developer pushes; no tags or releases at closes; no AI trailers (`HOW_WE_WORK.md`).
- 3.40 milestone (REPLAN 2026-10-15/17): TNC 0 only inside the frozen 95 % band; the tail goes to TYPE-BELOW-BAND by
  a rule the tool applies; drift types never get TYPE-BELOW-BAND (T17).
- T10 ruling (a), 2026-10-17: full singleton wave at the 4-coder cap, 20-30 min a function; the parked families
  (instruction rows, func_80188C04's 11 fns) are not attempted; every survivor names its compiler wall. The
  Done-criteria were amended to `lever_census --check --strict --residue config/lever_residue.tsv` with every residue
  row walled (`GENERATION_PLAN.md:4`).
- Crack coders run on openrouter-deepseek/deepseek at default high effort (free MiniMax retired 2026-10-22); all other
  coder work is in-house; no escalation to Opus or Haiku; a failed run or wall is held for the developer
  (`PHASE_PLAN.md` Changes, `HOW_WE_WORK.md` External coders).
- Lever doctrine (`docs/levers.md` §5): ban the silence, not the lever. Marked ordinary-C fakes (do-while, dead
  initialiser) are allowed and counted apart; an invented condition or dead store is never banked. The 5,262 K&R
  calls are the original's convention, not debt.
- Names (developer 2026-10-17, `docs/gen3-standards.md` rule 1): a `guess_<Name>` with a basis row beats a bare
  placeholder; confirmed names need citations. `GENERATION_PLAN.md`'s Standing constraints still says "unnamed beats
  wrong"; the 3.42/3.43 scopes carry the amendment.
- Order types -> casts -> names -> layout; renames only through symbol files + `tools/ghidra_apply_symbols.sh`; S1
  one-source-per-function stays at 0.
- Defects in harness files (`tools/` harness, `.claude/`, hooks, agents) are `harness:` gotchas, never tasks here.
