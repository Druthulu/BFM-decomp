# CURRENT_PHASE — Phase 20: Close the propagation cap, crack the gcc residual classes, then scale the waves

**Status:** In progress (plan approved, gate 1 passed) · **Generation:** Gen2 (12th phase) · **Started:** 2026-06-20
**Effort:** Max (planning done); per-task below (R7). Owner decisions: **class-crack first**; **skip the permuter background grind** this phase.
**Project version at phase start:** 1.18.0 (fleet 58.00% byte-identical, 136/136 binaries).

> Open-ended phase (Phase 15/19 precedent): fleet % rises monotonically, 136/136 byte-identical throughout, 0 NON_MATCHING; closed at a clean checkpoint, not a fixed %. Plan file: `~/.claude/plans/max-effort-set-plan-giggly-pony.md`.

## Task checklist

- [x] **T1 — Close the propagation cap (typedef/local-type lift)** · DONE (xHigh)
      Extended `tools/build_engine_types.py` with `find_typedefs()` + collision/overlap guards; lifted **14 typedefs** to `engine_types.h` (byte-neutral, `ov_SC01_077` stays `d19c9580`); `dedup_propagate --auto-from` propagated **9 reach-134 fns ×134**. **check-all 136/136**, fleet **58.00%→58.35%** (+0.35%), dedup **1485→1494**, 0 NON_MATCHING. **FINDING (R14):** cap was 16; only **9 were type-blocked** (all freed) — the other **7 are callee/data-extern plumbing** (`func_80142C84`, `D_800AE620`…), the §19 declaration-plumbing class, NOT the type-lift → recovery-tooling lever (see Notes).
- [x] **T2 — Exemplar-miner / residual router** · DONE (xHigh)
      `tools/exemplar_miner.py` → `docs/exemplar_curriculum.md` + `.run/exemplar_routing.json` (reach computed from sigs like dedup_propagate). **835 residual stubs routed:** WAVE 472 (218 reach-134, T6 fuel) · STRUCT 159 · **PINS 114 (45 reach-134)** · STUB 90 (74 ARITY_WALL + 16 NONFAITHFUL). **Key T3 input:** 17 reach-134 fns at m2c-mismatch=1 = the cleanest regalloc/schedule isolates (likely §17-pins wins + the genuine class residuals). Named exemplars confirmed reach-134. *Caveat: census is the Jun-19 snapshot (pre-Phase-19 waves, ~7% stale); T5/T6 regen gives the authoritative fresh WAVE list.*
- [ ] **T3 — gcc class-crack research block** · **Max each** (R17) — the phase hinge
  - [ ] T3a — `%lo`-folding at `-O0` (most promising; ~10 fns; address-mode/`local-alloc.c`)
  - [ ] T3b — loop-guard operand-order (`func_8012C2D0`; `loop.c get_condition`)
  - [ ] T3c — store-vs-load scheduling tie-break (`func_8014F2E0`; `sched.c`)
      Each: read the gcc-papermario pass → try the C lever → `match_one` → crack (byte-gate + propagate + cookbook idiom) OR cite-irreducible (cookbook verdict).
- [ ] **T4 — Distill the gcc-2.7.2 codegen map** · **Max** (R16)
      Consolidate §17/§18 + T3 into a complete codegen reference (idiom OR cited-irreducible per class) in `docs/matching-cookbook.md` + `docs/hand-matching-process.md`.
- [ ] **T5 — Ghidra-C regen for fresh wave targets** · xHigh + **R23/R29**
      Stop MCP → `DecompileFunctions.java` over fresh tractable reach-134 stubs → restart → **pause + prompt `/mcp`** → `get_binary_info` (G2).
- [ ] **T6 — Enriched waves** · **Ultracode** (R26/R27 — prompt to toggle)
      Wave batches (size 50, bank a lesson each) over fresh reach-134 targets: §17 + T3 classes + canon-first 2-stage gate + `fix_arity_callers` + uncapped propagation. Each match ×134. Verify per batch.

**Optional / conditional (decide live, else → Phase 21):** `-O0` ×134 rollout (only if T3a cracks `%lo`); the 28 giants (deferred to a focused Phase-21 deep session).

## Current task pointer
→ **T3** (gcc class-crack block). Refined opener: attack the **17 reach-134 m2c-mismatch=1 PINS** fns with the existing §17 toolkit (pins/array-decay) — bank ×134 wins + discover what resists; THEN Max gcc-source research on the residuals + the 3 named exemplars (crack-or-cite). T1, T2 complete + committed.

**Carry from T1 → recovery tooling (Phase-20 backlog item 2 / T2 router):** the **7 callee/data-plumbing capped fns** (reach-134, matched-but-local): `0x80142B2C 0x801535F4 0x80155E30 0x80157580 0x801576A8 0x80168F40 0x80170B48`. They fail `compiles_standalone` on undeclared callees/data, not types. A `dedup_propagate` macro-extern-injection (or canonical-callee-sig embed, the `gen_harvest_targets` approach) would free them ×134 (~+0.3%). NOT type-lift; do not reopen T1 for them.

## Blockers
None.

## Progress log
- 2026-06-20: Session start; read full load order (PROJECT_CONTEXT + 19 PhaseEnds). Phase 19 closed at 58.00%. Brainstormed strategy with Drew (ML/Wine/debug-symbols/gcc-papermario threads → honest verdicts; the wall is propagation-cap + ~3 uncracked gcc classes, not comprehension). Max set, plan mode. 3 Explore agents mapped the propagation/wave/quirk subsystems; verified the type-lift crux firsthand. Reframed (R14/P9): class-cracking = ~3 bounded spikes. Drew chose **class-crack first** + **skip permuter grind**. Plan approved (gate 1). CURRENT_PHASE + task list created (R28).

## Notes / decisions
- **R14/P9 reframe (recorded):** of 916 residual stubs — STRUCTURAL_MISS 368 (→waves), PERMUTER_CLASS 146 (→permuter/pins), ARITY_WALL 74 (→stub, fundamental loose-typing), fn-ptr/jtbl 144 (→struct context), NONFAITHFUL 16. Novel uncracked gcc classes = 3 (loop-guard, store-vs-load, `%lo`-folding); 2 carry a single prior "irreducible" verdict (worth ONE Max re-examination each, since the sibling regalloc-order class cracked with pins).
- **Honest % expectation:** T1 ~+0.6%; T3a maybe ~+0.6% (if `%lo` cracks); T3b/c may be 0 (cited-irreducible). Durable value = the codegen map + a higher wave close-rate, then T6 banks the scale %.
- **Commit cadence:** per-task/per-batch local checkpoints (long-phase precedent), each clean-rebuild-verified (R22). Drew pushes (R6).
