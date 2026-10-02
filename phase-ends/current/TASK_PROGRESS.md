# T5 progress (attempt 1, forced hand-back)

## Done so far
- Context loaded; summaries T1-T4, T10 read.
- Retriever (inline, no report file): R1/R2/R3 recipes (restruct.py RECIPES :1535) are body/TU-text only, act on global/gaddr bases, ran only on KEPT P sites; no tool converts abs 0x80 literals to symbols or writes config/symbols.*.txt.
- T5.c1 (ef4507badb, logs/T5.c1.md): uncovered I=35,625 M=14,762 (gate matches). ABS literal sites = 0 (the absolute-address clause is vacuous). I: &D_x gaddr 21,388 sites/7,738 bodies; local/param TNC 10,793; D_x global deref 2,600; &ident NO-TYPE-IN-MAP 843; FILE-SCOPE 1. M: param TNC 13,691 (7 Unkstruct types hold 13,214), global 1,066, other 5. 15 `--try --recipes` probes: 10 IDENTICAL, 3 DIFFERS, 2 NO-SITE-CONVERTIBLE. Scratch in .run/P39/t5/.
- T5.c2 (f476751f9f tool, 9d2c7e9dc6 log): `restruct --rung S --recipes --forms I,M` runs R1/R2/R3 on every I/M gaddr/global site; refused site → per-site RESIDUAL(R<n>-<why>) (e.g. R2-DIFFERS, R2-WIDTH, R<n>-REKEYS, R1-NOT-GLOBAL, R1-STILL-RAW); plan selects only bodies with uncovered I/M global sites (2,325 files); residue_cause_im gaddr → GADDR; restruct_cycle.sh RECIPES=1 FORMS=I,M pass-through; selftest 107/107; tools-health OK; ops doc docs/ops/p39-t5-2026-10-02-restruct-im-recipes.md.

## In flight
- T5.c3 coder (background, may be orphaned by this hand-back): calibrated, pilot cycle running at hand-back: pid 2021488 `RECIPES=1 FORMS=I,M LABEL_PREFIX=t5_im TASK=T5 tools/restruct_cycle.sh 1 1 50 S ov_SC07_006` (log .run/P37/restruct/cycle_t5_im.log; batch json batch_t5_imS1.json). Its brief: after a green pilot, sweep all segments (ov_*, md_*, main, src/shared/*) in detached cycles < 10 min/batch, then gate; log phase-ends/current/logs/T5.c3.md.

## Hypotheses rejected
- Abs-address → symbol tooling needed: rejected, 0 ABS literal sites (T5.c1).
- Ledger everything RESIDUAL directly: rejected by plan (RESIDUAL only after the recipe ladder refused).

## Current hypothesis
- Global/gaddr I/M (~25k sites) go through the recipe ladder sweep (drawn or RESIDUAL(R<n>-why)); remaining TNC/NO-TYPE-IN-MAP/FILE-SCOPE I/M (~25k, non-global bases, no recipe applies) close with `restruct --rung S --residue --forms I,M --only <seg>` per segment (T3 binding: TNC residual).

## Next five steps
1. `pgrep -af restruct_cycle`; if c3's cycle is running wait (never launch a second); read logs/T5.c3.md / git log for t5_im batches.
2. If c3 died mid-sweep: new coder resumes the sweep from the next uncommitted batch (`restruct --plan --rung S --forms I,M` shows what is left).
3. Coder: `restruct --rung S --residue --forms I,M --only <seg> --label t5_res_<seg>` for ov_*, md_*, main, src/shared/*; commit ledger.
4. Verify: `PY tools/type_census.py --check-casts --residue --quiet` (I/M uncovered 0; rc 1 only on lying 229 until T6); `make clean && make extract-all JOBS=16 && make check-all JOBS=16` via run.sh.
5. Write logs/T5.md, tasks/T5.md; `task_log.py finish T5`; commit.

## Gotchas
- harness: forced expert hand-back while a coder's detached cycle runs (again, as T3/T4); respawn must pgrep before briefing.
- ledger `.run/P37/restruct/ledger.jsonl` needs `git add -f`, not passed to commit_task.sh.

## State to carry verbatim
- Gate baseline: `raw P=257464 I=51505 X=13790 M=15130 (uncovered P=0 I=35625 X=0 M=14762); unbacked 0; lying=229 (ledgered 0)`.
- Commits: ef4507badb (c1), f476751f9f + 9d2c7e9dc6 (c2).
