# CURRENT PHASE — Phase 22: Hand-grind the giants (×134) + idiom-distill-then-fan-out flywheel

**Generation:** Gen2 (14th phase of the arc; Phase 14 deferred to Gen3+) · **Started:** 2026-06-26 · **Effort:** Max (giants/synthesis) ↔ Ultracode (idiom waves, prompt per R27) · **Plan approved:** gate 1 ✅ (Drew)

> Per-task crash-recovery log (P3). The full approved plan is at `~/.claude/plans/plan-mode-enabled-max-shimmering-thimble.md`. This file is the committable state a fresh session resumes from.

## Goal

Drive the **byte-weighted** progress number (~30% decomp.dev-comparable; the function-count metric is at 63.18%) by **hand-grinding the giants** (reach-134, >150 ins — each banks ×134), distilling each crack into a reusable idiom, then fanning that idiom out across its class via the existing wave harness. Open-ended; monotonic; zero regressions; close at a clean checkpoint when giant ROI drops.

## Decisions (Drew, gate 1)
- **Calibrate on a mid-giant first:** `func_8015126C` (254 ins / 135K, already a **close=2** backlog near-miss) → `func_8014EE14` (248 / 131K, close=6) → escalate toward `func_80144B9C` (770 / 410K).
- **Background grinder ON:** token-free permuter daemon on the regalloc/coalescing residual, alongside the hand-loop.

## The operating loop
A. Hand-decomp next giant (Max) → §27 recipe → match_one → harvest_verify byte-gate → dedup_propagate ×134 → commit. ROI-gate: irreducible class → bank closest draft to backlog (P9), move on.
B. Distill the last-mile idiom → cookbook (R16/R30).
C. If general → fan out a few waves (Ultracode, prompt R26/R27) applying it → gate_stage → distill.js → backlog.
D. Rinse and repeat (next giant, highest byte-weight first).

## Tasks
- [ ] **T0 — Unified byte-weighted ranked worklist** *(in progress)* — refresh fuel_manifest + backlog; `tools/worklist.py` → `docs/worklist.md` + `.run/worklist.json` (ranked by byte-weighted gain, grouped by idiom class, byte-weighted % + cumulative cols).
- [ ] **T1 — Fuel prefetch + calibrate on func_8015126C** — verify 27 giants cached (prefetch via DecompileFunctions.java if needed, R23/R29); run the full hand-loop on func_8015126C → bank ×134 → commit → distill.
- [ ] **T2 — Hand-decomp giants by byte-weight (loop)** — func_8014EE14 → … → func_80144B9C; one at a time, byte-gated, propagated ×134, committed. Report each (P3).
- [ ] **T3 — Distill idioms → cookbook** — per crack (R30).
- [ ] **T4 — Idiom fan-out waves (Ultracode)** — a few waves per learned idiom over its class (prompt R27).
- [ ] **T5 — Background token-free grinder** — start after T1; grinder.py via auto_supervisor.sh; auto_stop.sh kill switch.
- [ ] **T6 — Progress honesty + PhaseEnd** — keep worklist/backlog/progress.fleet.md fresh; track both %s; PhaseEnd_Phase22.md at close (Tier-1 Max).

**Current task pointer:** T0.

## Verification invariant (every bank)
`make check-all` → 136/136 byte-identical from a CLEAN tree (R22); `dedup-check` validated, 0 failed; 0 NON_MATCHING (G4); byte-gate (harvest_verify) is the sole arbiter (G3/P9); each bank = checkpoint commit; the `db.*.gbf` churn is R23 restart-noise (do NOT stage).

## Reuse (no rewrites)
orchestrator / wave_targets / worker_wave.js / distill.js / gate_stage / idiom_loop / grinder + supervisor / harvest_verify / match_one / dedup_propagate / build_fuel_manifest / backlog; cookbook §17–§27 + hand-matching-process.md + automation-runbook.md.

## Guardrails
- Don't grind confirmed-irreducible classes (store-vs-load sched, hoist-vs-remat, IV-combine, hoisted-invariant order, narrow-param loose-typing, cross-jump merge) — ROI-gate, bank closest, move on.
- Actor struct is byte-NEUTRAL for matching (comprehension only).
- R27 effort transitions: prompt Drew to toggle Max↔Ultracode at every A/B↔C boundary; never launch a Workflow on a verbal yes.

## Blockers
(none)

## Progress log
- 2026-06-26: Phase plan approved (gate 1). Task list built (R28). CURRENT_PHASE.md written. Starting T0.
