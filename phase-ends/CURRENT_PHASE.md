# CURRENT_PHASE — Phase 24: Fix + evolve the permuter (§31-class-aware) · integration-recovery tool · scale the §31 wave

**Started:** 2026-07-02 · **Effort:** Max · **Gen2 phase 16 of the arc (8→…→23→24)** · Open-ended matching phase (checkpoint-close, like 15/20/21/22).
**Plan:** approved (Drew, sequencing = permuter-first, staged). Full plan: `/home/musashi/.claude/plans/plan-mode-enabled-max-tender-bengio.md`.
**Baseline at phase start:** fleet 64.86% byte-identical-from-source (~30% byte-weighted); 136/136 binaries byte-identical; 0 NON_MATCHING; dedup groups per Phase-23 close. main `143dbb89…`, resident `8e17e02f…`, ov_SC01_077 `d19c9580…`.

## Invariant (every task)
Whole-binary byte-gate (`tools/harvest_verify.py`) is the SOLE arbiter (G3/P9). Tools only reshape declarations/plumbing or PROPOSE candidates; nothing banks except a byte-identical SHA1 rebuild, verified CLEAN (R22): `make clean && (extract all 136) && make check-all` → 136/136; `tools/dedup_integrate.py --check` 0-failed; `tools/progress.py --fleet` monotonic up. No Ghidra DB change (R23 restart-noise — do NOT stage `db.*.gbf`).

## Task checklist
- [ ] **T1 — Re-log map-wave results + backlog hygiene** *(xHigh)* ← CURRENT
- [ ] T2 — Permuter Stage-0: floor-free masked scorer (-drz) *(Max)*
- [ ] T3 — Permuter setup fixes: pins · typedefs · -O0 *(xHigh)*
- [ ] T4 — Probe the flagship func_80132784 (4/400) *(Max)*
- [ ] T5 — Permuter evolve: §31-directed mutation + grinder fixes *(Max)*
- [ ] T5b — Fable5 §31 map-extension spike: crack an intrinsic class (S11/RC-6) *(Max; agent model:fable)* — added 2026-07-02 (Drew)
- [ ] T6 — Build the integration-recovery tool *(Max)*
- [ ] T7 — Unblock the 8 compile-blocked region-a giants *(xHigh)*
- [ ] T8 — Scale the §31 wave *(breadth → prompt for /effort toggle, R27)*
- [ ] T9 — Distill + PhaseEnd *(Max, Tier-1)*

**Current task:** T1. **Rules check due after T4** (P6).

**Fable5 policy (Drew, 2026-07-02):** Fable5 (`Agent(model:fable)`) is the reserved *discovery / wall-breaker* tier (reads the gcc-2.7.2 source; ~375k tok/giant), NOT the workhorse. Cheap-tier-first: permuter + Opus applying §31 → Fable5 only when they stall. Two uses this phase: (1) **on-demand escalation** on any giant the fixed permuter can't close (T4/T8 — no task); (2) **T5b** proactive spike to test whether S11/RC-6 are truly intrinsic. A Fable5-cracked lever goes into §31 (R16) so Opus applies it thereafter.

## R14 corrections carried in (do NOT re-adopt the stale Phase-23 backlog framings)
- "split-file-blind glob" is refuted — the real defect is `compile.sh`/`match_one.py` are **-O2 only** (can't match `_o0`). → -O0 compile.sh variant (T3).
- "churn-without-blacklist" is refuted — the real churn is **floor-victim idle re-tries** (`grinder.py:120 tried.clear()`). → scorer (T2) + input-changed gating (T5).
- `func_80144090` ×1 is a **type-lift** case (`OtBlk` not in `engine_types.h`), NOT a straggler. → `build_engine_types.py` (T6).
- `backlog.jsonl` closeness is **stale/regressed** for the wave seeds (true values in `.run/wave/*.c` headers; `func_8014E048` logged `failed` → `wave_targets` skips it). → re-log first (T1).
- The "~95/80/31" class counts are aspirational; real canon `SCHEDULE=30/REGALLOC=84/REMAT=3`, steerable near-misses scattered in `OTHER`/`None`. → wave text-scans `where_stuck` (T8).
- `gcc-papermario` is gcc **2.8.1**, not 2.7.2; vanilla 2.7.2 at `tools/reference/gcc-2.7.2/` (cite it). `loop.md` on vanilla; sched/regalloc/cse map files still cite 2.8.1 lines.
- **No decomp-permuter submodule edit** for the overhaul (scorer rebind + `#pragma _permuter b64literal` pin carrier + `weight_overrides`, all in `tools/`). The pin-scope randomizer pass (only submodule edit) is deferred.

## Progress log
*(append one line per task on completion — the crash-recovery trail)*
- **T1 ✓ (2026-07-02):** re-logged 7 map-wave seeds with BYTE-VERIFIED closeness (dropped 19 stale/unreproducible records from `.run/backlog.jsonl`, `.bak` kept; best_draft → `.run/backlog_drafts/`). Ground truth (match_one `-dr`): func_8014E048=**35** (was mis-logged `failed`), func_80176D94=**52**, func_80148094=**72** (best draft = `vG2.c`, NOT the named file), func_801412A8=**110**; T6 leaf-MATCHes func_8014F4C0/func_80155800=**0**. func_80144090 excluded (banked ×1, not a stub → T6 `OtBlk` type-lift). Fixed gate_stage sig_unify/`--src-file` doc-drift. `wave_targets --class REGALLOC` + grinder now surface all 4 count-exact permuter seeds with true closeness; func_80132784 correctly kept out of blind selection. No build-input changed → 136/136 invariant untouched. Commit: (checkpoint).

## Blockers / open findings
- **R14 FINDING (P9, surfaced to Drew):** the Phase-23-close premise *"the flagship func_80132784 is 4 instructions from a ×134 bank"* is **NOT reproducible from any on-disk draft** — the best is **204-off with the wrong instruction count (384≠400: match_one `-dr` collapses ~16 nops on this GTE/nop-heavy seed)**; the true closeness is **unknown pending T2's `-drz` scorer**. → **Reframe T4**: func_80132784 is a genuine hard GIANT (wrong instr count ⇒ structural C work, not a register swap; residual = S7/S11 prologue-weave + hoist-vs-remat). The realistic near-permuter targets are the **count-exact** seeds (func_8014E048 35, func_80176D94 52, func_80148094 72, func_801412A8 110). S11 blocks func_801412A8 + func_80132784 → **T5b Fable5 spike** is well-motivated. Permuter-first still sound (these are exactly regalloc/schedule residuals), but the "easy flagship win" framing is retired.
