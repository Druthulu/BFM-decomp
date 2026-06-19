# CURRENT PHASE — Phase 16: Crack the struct-heavy shared core

**Generation:** Gen2 (8th phase) · **Started:** 2026-06-18 · **Status:** APPROVED (gate 1 passed), executing
**Plan source:** `~/.claude/plans/plan-mode-enabled-max-cryptic-nebula.md` (approved 2026-06-18)
**Type:** open-ended (NOT a Gen2 gate — Phase 14/public-flip parked to Gen3+). Milestone = honest pipeline-proof, not a fleet-% target.

> Crash-recovery log (P3). Updated after every task. The PhaseEnd is the synthesis; this is the live state.

## The wall (byte-verified, R14)
964 shared stubs remain in `src/ov_SC01_077/ov_SC01_077.c` (68,486 ins, ~35.6 MB collapsible). All struct-heavy: m2c emits `arg0->unkXXX` that won't compile without the struct types. **It is a TYPE-GRAPH, not one struct** (`func_80132784` chains 4 types deep + a polymorphic ×12/×8 access). Buckets: 75 tiny / 447 small / 265 medium / 71 large-medium / **106 giants (>150 ins)**. 399 m2c-targets (≤145 ins); 159 of them also arity-blocked (`never⊆targets`) → clean struct-medium prize ≈ 240. Fleet **54.48%** (187,426/344,010 by fn count); ceiling if all cracked ≈ 90%. Box: **15 GiB RAM** (binds permuter parallelism), 32 threads, 946 GB disk; systemd-user offline, cron present.

## Owner decisions (gate 1)
- **Unattended run = in-phase payoff** (away window). ⚠️ **BLOCKER:** confirm away-window dates before S6 (GATE-D must pass with owner present).
- **ML = dropped/parked** (research-note only).
- **Giants = conservative** — target ~240 struct-medium band; hand-prove 2–3 giants (robustness); **defer the 106-giant grind**. Driver worklist = the ~858 non-giant stubs.

## The per-function pipeline (S2 wires, S7 loops; byte-gate is the sole arbiter G3/P9)
`m2c --context .run/m2c_actor_ctx.c --valid-syntax -f <fn>` → `sig_unify.py` → `match_one.py` (rank) → decomp-permuter (only if compiles-but-differs; `--stop-on-zero -j8`, wall-clocked) → `harvest_verify.py` (whole-binary byte-gate) → on match: `dedup_propagate.py --auto-from ov_SC01_077` → git checkpoint → `make report` (assert fleet-% strictly rose).

## Task checklist (gated; GATE = no-go STOP/re-plan, P5)
- [x] **S0** Research/SOTA scan + ML research-note (Max) — **DONE** → cookbook §15. Key finding below.
- [ ] **S1** Type-graph inference `tools/struct_infer.py` (Max) → **GATE-A:** ≥8/10 mediums COMPILE via the graph — *in progress*
- [ ] **S2** Pipeline build: `tools/m2c_ctx.py` flat ctx + wire chain + patch `dedup_propagate.compiles_standalone()` (xHigh) → end-to-end on 1 fn
- [ ] **S3** 10-medium validation (Max) → **GATE-B:** ≥6/10 byte-identical; record permuter yield (<4/10 → STOP run)
- [ ] **S4** Giants robustness: hand-match 2–3 incl. `func_80132784` (Max)
- [ ] **S5** Driver `tools/auto_driver.py` + supervisor `tools/auto_supervisor.sh` (xHigh); neutralize SessionStart MCP hook for window
- [ ] **S6** Hands-on trial (xHigh) → **GATE-D:** multi-hr pass + forced kill→auto-resume→`check-all` 136/136 + negative control
- [ ] **S7** Unattended multi-day run, ~858 non-giant band (script) — monotonic fleet %, every checkpoint check-all-green/reverted
- [ ] **S8** Harvest/propagate sweep + fleet roll-up (xHigh + 1 surgical survey)
- [ ] **S9** Close / PhaseEnd (Max) — honest milestone, plain-English recap (R25)

**Current task pointer → S0.**

## New tools/files
`tools/struct_infer.py`, `tools/m2c_ctx.py`, `src/shared/engine_struct.h` (#ifdef M2C skeleton / #else real layout), `tools/auto_driver.py`, `tools/auto_supervisor.sh`, opt `src/shared/engine_decls.h`. Reused: sig_unify, match_one, harvest_verify, dedup_propagate (patch compiles_standalone += struct header), decompile.py --context, permuter/compile.sh, progress.py --fleet, build_engine_types.py (additive). m2c context MUST be flat directive-free C (rejects #include/#ifndef).

## Kill-criteria (P5)
K1 type-graph won't compile (GATE-A <8/10) → STOP, fall back to hand-typing top-leverage 10–20. K2 permuter yield <4/10 (GATE-B) → STOP unattended plan. K3 driver corrupts state (GATE-D not 136/136) → no unattended run; runtime: any checkpoint check-all≠136/136 & auto-revert fails → halt+notify. K4 silent under-propagation → assert fleet-% rose per batch; flat-but-green → halt.

## Safety invariants
Byte-gate (`make build` SHA1) is the only truth (G3/P9). R22 clean-rebuild for byte-checks. **NEVER `git checkout src/<overlay>.c` during a harvest** (§14c — silently reverts banked matches). Commits on `phase-16-autodrive` branch, explicit pathspec `git add` (never `-A`), local only — owner pushes (R6). State/logs under `.run/auto/` (R12). 0 NON_MATCHING in default builds (G4).

## Timeline (Drew, 2026-06-18 Thu 10:26pm MDT — departs Sun 2026-06-21 afternoon)
Must be verified + ready to launch unattended by Sun afternoon. Cadence (I own the launch/test/analyze/iterate loop):
- **Thu night / Fri:** build pipeline (S2) + struct inference (S1); **first small known-answer test**.
- **Sat night:** larger overnight test (the de-risk trial, GATE-D incl. forced-kill→resume).
- **Sun afternoon:** verified → **go-mode** (launch S7 unattended). Several small runs + adjustments allowed in between.

**Known-answer oracle test (Drew's method):** take an ALREADY-matched struct-heavy function (engine_core.h DEFINE or an inline def in ov_SC01_077.c), revert it to an INCLUDE_ASM stub, run the FULL pipeline (m2c+ctx → sig_unify → permuter → harvest_verify byte-gate), confirm it independently re-derives the byte-match we already know is correct. Zero-ambiguity end-to-end validation; also a yield baseline. Use known-answer fns for early tests; unmatched mediums for the real GATE-B.

**Execution-order adaptation (S0 finding):** build the m2c+macros+permuter+byte-gate **pipeline (S2) FIRST** (testable tonight), then add `struct_infer` (S1) as the regalloc/structural enhancer + measure its lift. Same tasks + gates; order adapted to get a known-answer test running fastest. (Within-phase autonomy, P3.)

## Blockers
- (resolved) Away window = Sun afternoon; S1–S6 must complete by then.

## Progress log
- 2026-06-18 — Phase planned at Max (Tier-1): 3 Explore + 3 Plan agents + bounded web research; scope byte-verified (R14); plan approved (gate 1). Task list built (R28). CURRENT_PHASE.md written. Beginning S0.
- 2026-06-18 — **S0 DONE** (cookbook §15). Ran m2c on real ov_SC01_077 stubs (R14). **Finding that refines the plan (favorable):** m2c `--valid-syntax` output COMPILES via `m2c_macros.h` (`M2C_FIELD` = byte-faithful cast) — the struct is NOT a hard *compile* prerequisite; 30/30 sampled m2c-targets use only byte-faithful macros. **Compiling ≠ matching:** the residual is regalloc/scheduling → **decomp-permuter is the byte-closer (essential)**; struct types (S1) are an *enhancer* (regalloc-aid + structural fixes + readability), not the sole gate — S3/GATE-B measures macro-only vs struct-typed yield. S2 must: add `s64/u64/f64` + the byte-faithful m2c macros to `common.h` (match_one/harvest_verify strip scalar typedefs); type function-pointer-table globals; keep `M2C_FIELD` as the byte-faithful fallback where m2c loses types through index arithmetic. ML dropped (owner). No plan re-scope needed (S3 settles the macro-vs-struct question). → S1.
