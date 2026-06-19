# CURRENT PHASE — Phase 17: Raise the harness ceiling to "eureka level", then gate the compute run

**Generation:** Gen2 (9th phase) · **Arc:** 8→9→10→11→12→13→15→16→**17** (14 deferred to Gen3+)
**Plan approved (gate 1):** 2026-06-19 (Drew) · **Effort:** Max (this session) · **Status:** PLAN APPROVED — execution NOT yet started (Drew will run T1+ in a fresh normal session)

> Approved plan: `~/.claude/plans/plan-mode-enabled-deep-reserach-reactive-toucan.md` (the durable copy of
> the deep-research findings + the task design). This file is the per-task crash-recovery log (P3/R28).

## Why this phase (one paragraph)
Phase 16 proved the m2c→permuter brute-force tops out at ~3% on the ~964 struct-heavy **shared** engine
functions; a 5-day/32-thread unattended run at that ceiling buys only ~3% fleet — too low to commit. Drew's
decision: **pursue ALL avenues to raise the harness's per-pass yield from single-digit to "eureka level"
BEFORE the run**, measuring with *attended* trials as each lever lands. Deep-research (this session) revised
the premise: type recovery is NOT a blanket match-% lever (global type-prop *breaks* loose matches; struct
def is byte-neutral for fns m2c gets right) — BUT it unlocks a *subset* (m2c structural-misses, fn-ptr
tables) + comprehension. The matching path is **m2c + rich `--context`** (not Ghidra-C). A named,
never-built deterministic lever exists: the DATA-symbol byte-array canonical header (cookbook §14c-c).

## Goal & milestone (P9, observable)
Widen the matchable/permuter-viable draft set across all avenues so the *measured* ceiling (known-answer
re-derivation rate + attended-trial yield) climbs from single-digit to eureka level → then an evidence-based
go/no-go on the unattended run. **Milestone (gate 2):** measured ceiling rise (ladder + trial evidence) +
go/no-go decision with projected run yield; all 136 binaries still byte-identical (R22); findings folded into
`docs/matching-cookbook.md` + `docs/struct-core-pivot.md`. (Open-ended like Phase 15 — monotonic rise, zero
regressions, not a fixed-% gate.)

## Baseline (phase start)
- `make check-all`: 136/136 binaries byte-identical from clean (main `143dbb89…`, resident `8e17e02f…`, 134 overlays).
- `make report`: FLEET REAL 185,779 / LINKED 959 / **54.48% byte-identical-from-source** / 0 NON_MATCHING / 1395 dedup groups.
- ~964 struct-heavy shared stubs remain in `ov_SC01_077` (the harvest source).

## Tasks (one commit per task, P4/R8 cadence per Drew; sequencing of T2–T5 may reorder per T1)
- [x] **T1 — Wall taxonomy** [Max]. **DONE 2026-06-19.** `tools/wall_taxonomy.py` (new) censused all 957
  residual shared stubs → `docs/wall-taxonomy.md` + `.run/wall_taxonomy.json` (reproducible, ~22 s).
  Classifier validated against the real byte-gate (R14): SIG_FIXABLE_KR = exactly the gate-passing set (4/4).
  **Headline findings (drive T2–T5 sequencing):** T4+T5 rich-context (struct/jtbl/fn-ptr-table) = **67%** of
  residuals incl. all 30 jump-table giants; T6 permuter = 146 candidates (101 ≤4-mismatch); T3 sig_unify =
  48 gate-proven free wins; loose-typing WALL = 99 (10%); **T2 DATA-symbol header = 0 functions → recommend SKIP.**
- [ ] **T2 — Avenue 1: DATA-symbol byte-array canonical header** [xHigh]. Split `gen_engine_decls.py`; data →
  universal `extern u8 D_X[];`; overlay `.c` includes it; drafts strip own data decls. Probe (~20-30) → scale.
- [x] **T3 — Avenue 2: K&R loose-signature modeling** [Max]. **DONE 2026-06-19.** Banked **42** gate-proven
  `SIG_FIXABLE_KR` matches (of 48; 6 honestly reverted by the byte-gate) + propagated **13** ×134 fleet-wide →
  **fleet 54.48% → 55.00% (+0.52%)**, REAL +1,778, **136/136 byte-identical** (R22), dedup-check 1408/0.
  Probed the wall: raw drafts 0/99, sig_unify fails — and verifying against the bytes (R14) found a **T1
  classifier bug** (the "LOOSE_TYPING_WALL" was byte-neutral pre-existing warnings, not a wall). Corrected:
  real wall = **ARITY_WALL 74** (§14e dead-end); no K&R lever there. Avenue exhausted; rest is structural →
  T4/T5. (Did a one-time full-fleet `make extract`; fixed `wall_taxonomy.py` + amended `docs/wall-taxonomy.md`.)
- [ ] **T4 — Avenue 3: m2ctx-style rich context generator** [xHigh]. Build the missing context generator
  (structs + byte-array data + types + fn-ptr-table types) → wire into `decompile.py`/harvest.
- [ ] **T5 — Avenue 4: struct inference + emulator field-typing** [Max + Drew emu]. Infer actor struct from
  m2c field-access union; Drew-driven PCSX-Redux field-typing (R10); feed via T4 context. Scoped to the
  structural-miss + fn-ptr buckets + comprehension.
- [ ] **T6 — Avenue 5: permuter tuning + attended trials + known-answer ladder** [mixed; R26 prompt if breadth].
  After each of T2–T5, bounded attended pipeline pass on a fixed sample (`p16_known_answer`/`p16_improve`);
  tune permuter (`-j` on 32 threads); track ceiling; set the "eureka" threshold with Drew from trial data.
- [ ] **T7 — Go/no-go on the unattended run + phase close** [Max]. Present measured ceiling + projected run
  yield → decide; if GO deploy `auto_driver`+supervisor supervised-first; fold findings; PhaseEnd (R18/R25/R19).

## Verification discipline (every task)
`make clean && (extract all) && make check-all` → 136/136 (R22); `make report` fleet-% is the OUTCOME metric
(verify it, not just the gate — §14d); probe each lever on a ~20-30 known-answer sample before scaling (§14d);
0 NON_MATCHING in any default build (G4).

## Decisions / notes
- **bgIsolation disabled for this repo (2026-06-19, Drew-approved):** added `"worktree": {"bgIsolation":
  "none"}` to `.claude/settings.json` so sessions edit in place. The background-job worktree directive is
  incompatible with this project (R2/H2 single ext4 clone; clone-bound gitignored toolchain
  `.venv`/`tools/bin`/`disks/`; live Ghidra MCP bound to the main clone for T5; R6/R8/R20
  commit-on-`main`/Drew-pushes-via-GitHub-Desktop). HEAD==origin/main; origin unreachable from WSL (R6).
- **Execution deferred to a fresh normal session (Drew, 2026-06-19):** this session did the deep-research +
  Phase-Start planning (gate 1) only. The fresh session starts at T1 and, per R28, creates the live task list
  (one TaskCreate per T1–T7) before starting work.

## Blockers
- (none — unblocked once bgIsolation:none was set)

## Resequence after T1 — APPROVED by Drew 2026-06-19 (P5d gate passed)
**T3 (48 gate-proven free wins) → T4+T5 built together (rich context: struct + jump-table + fn-ptr-table
types — 67% reach incl. the giants) → T6 (validate the 146 permuter candidates, then close).** **T2 DROPPED**
(DATA-symbol byte-array header — addresses 0 functions). Task list updated: T2 deleted, T3 in_progress.

## Progress log
- 2026-06-19: Deep-research complete (3 agents, web+codebase, X2); findings revised Phase-16 premise (durable
  copy in the approved plan file). Phase 17 plan approved (gate 1, Drew). Resolved the bg-isolation/worktree
  conflict (bgIsolation:none, Drew-approved). CURRENT_PHASE.md written. Paused before T1 per Drew — execution
  resumes in a fresh normal session.
- 2026-06-19: **T1 DONE** (Max). Built `tools/wall_taxonomy.py`; censused all 957 residual shared stubs →
  `docs/wall-taxonomy.md` + `.run/wall_taxonomy.json`. Classifier byte-gate-validated (R14: SIG_FIXABLE_KR =
  4/4 gate-passing). Findings: T4+T5 context lever = 67%, T6 = 146 permuter candidates, T3 = 48 free wins,
  wall = 99, **T2 = 0 (skip)**. Baseline still 136/136 byte-identical (T1 was read-only; restored the .c
  after the gate validation). Recommended resequence recorded above; paused for Drew's nod before T2/T4.
- 2026-06-19: **Resequence APPROVED** (Drew): T3 → T4+T5 → T6, drop T2. Task list updated (T2 deleted).
- 2026-06-19: **T3 DONE** (Max). Banked 42 + propagated 13 ×134 → fleet **55.00% (+0.52%)**, 136/136 R22 green.
  One-time full-fleet `make extract` (needed for per-overlay propagation gate + check-all). Verifying the wall
  against the bytes (R14) exposed + fixed a T1 classifier bug (LOOSE_TYPING_WALL was byte-neutral warnings →
  real wall is ARITY_WALL 74); `wall_taxonomy.py` fixed, `docs/wall-taxonomy.md` amended. Avenue exhausted.
  **NEXT: T4 (m2ctx rich-context generator) [xHigh] — prompt Drew for the /effort toggle (R27).**
