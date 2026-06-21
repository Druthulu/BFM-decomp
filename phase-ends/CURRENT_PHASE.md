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
  - [~] T3b — loop-guard (`func_8012C2D0`, worked in ov_SC03_014). **R14: exemplar MISLABELED** — it's gcc **strength-reduction/addressing** (end = base `D_80120194` + 0x658C as an induction-var final-value), NOT operand-order. 2 drafts: base-relative-end + `lhu`/`u16` now correct; residual = gcc materializes the base separately before +0x658C (resists the constant-fold my C produces). Likely crackable via indexed-struct-array, but a deep per-fn induction-var grind. Prior "irreducible" was an incomplete framing. PAUSED for the ROI checkpoint below.
  - [ ] T3c — store-vs-load scheduling tie-break (`func_8014F2E0`; `sched.c`)
      Each: read the gcc-papermario pass → try the C lever → `match_one` → crack (byte-gate + propagate + cookbook idiom) OR cite-irreducible (cookbook verdict).
- [x] **T4 — Distill the gcc-2.7.2 codegen map** · DONE (Max, R16)
      Wrote **cookbook §20** (the wave-at-scale gate cap = loose-typing call-graph wall; store-vs-load + §10 hoist-vs-remat + IV-combine + hoisted-invariant-order CONFIRMED-irreducible with byte-evidence; the **-O1 class**; the stale-`.o` + args-as-array + `--chunk 1` gotchas; the T1/T2 wins) + an **R14 correction** to the §17a loop-guard entry (strength-reduction, not operand-order). `%lo` (T3a) left as a placeholder to append when cracked.
- [ ] **T5 — Ghidra-C regen for fresh wave targets** · xHigh + **R23/R29**
      Stop MCP → `DecompileFunctions.java` over fresh tractable reach-134 stubs → restart → **pause + prompt `/mcp`** → `get_binary_info` (G2).
- [~] **T6 — Enriched waves (batch 1 done)** · Ultracode
      Wave on 48 cached reach-134 ≤90-ins targets → **41/48 match_one MATCH (85%)**. Whole-binary gate: **8/41 banked** (7 ×134 + 1 local), fleet **58.35%→58.63%** (+0.28%), dedup 1494→1501, check-all 136/136. **KEY FINDING (byte-verified, R14/P9): the 33 lost are the LOOSE-TYPING WALL IN THE CALL GRAPH.** A callee (e.g. `func_80153C74`) is declared with CONFLICTING types at different overlay sites, so the draft's extern hits `conflicting types` in-TU (a COMPILE error, not a byte miss). match_one over-predicts because it compiles STANDALONE (draft's own externs) and masks jal/%hi/%lo. **ALL recovery levers fail:** `sig_unify`/`canon_draft_decls` impose a single "canonical" that's wrong for some sites; `fix_arity_callers` (0, not arity); no-proto externs (0, incompatible with the overlay's narrow decls); strip-externs (0, implicit-int ≠ target). **The ONLY fix is per-site function-pointer casts** (`((ret(*)(args))func_X)(…)`, §17a) = **Drew's backlog item 2 (auto call-site-cast recovery), the precisely-diagnosed Phase-21 cap.** Diagnostic lesson: a failed in-TU build leaves a STALE `.o` (objdump misleads — trust the whole-binary SHA, not the disasm). **The 7 DIFFs gave gold gcc diagnoses (do T3c/T4 for free):** T3c store-vs-load `func_8014F2E0`/`func_80150528` CONFIRMED unsteerable (sched.c); §10 hoist-vs-remat `func_80149374`/`func_801493D0`; IV-combine `func_80177AD4`; hoisted-invariant order `func_80177F84`; `func_80161A90` = **-O1** (build-infra, needs an -O1 split like -O0).

**Optional / conditional (decide live, else → Phase 21):** `-O0` ×134 rollout (only if T3a cracks `%lo`); the 28 giants (deferred to a focused Phase-21 deep session).

## Current task pointer — MULTI-SESSION CONTINUE (Drew, 2026-06-21: not closing; resume in a fresh session)
**Done + committed:** T1 (cap, +0.35%), T2 (router), T3b (cited — R14 reframe), **T3c (cited — written up in §20)**, **T4 (codegen map §20 + §17a correction)**, T6 batch-1 (8 banked, +0.28%). Fleet **58.00%→58.63%**, 136/136 byte-identical, 0 NON_MATCHING.

**Remaining, prioritized for the fresh session (the plan is approved — resume autonomously, P3/§Session-Start step 4):**
1. **[THE CAP — highest ROI] Build the §17a auto-call-site-cast recovery tool** (cookbook §20). The diagnosed gate cap: the wave's 33 match_one-MATCH drafts fail in-TU on loose-typed callee conflicts; the fix is per-site fn-ptr casts `((ret(*)(args))func_X)(…)` (drop the draft's conflicting extern, cast the call to the draft's intended sig, gate). Recovers T6 batch-1's 33 reach-134 (~+1%) AND lifts every future wave from ~20%→~80%+ gate-pass. Drafts preserved: `.run/drafts-t6-cn/` (agent originals, post canon_resident_calls); failures `.run/t6_fails.txt`; gate good-sha `d19c9580…`.
2. **T3a — %lo-folding -O0** (`func_8013C360` cluster; cookbook §18 open residual; entangled with the -O0 split infra). Append the verdict/crack to cookbook §20's placeholder.
3. **T5 — Ghidra-C regen** (R23/R29: stop MCP → DecompileFunctions.java → `/mcp`) for fresh reach-134 targets → more T6 wave batches (now with the cast-recovery → full yield). Cache is 300; ov_SC01_077 has 668 stubs.
4. **[build-infra] -O1/-O0 split files** to bank the -O1 (`func_80161A90`) + the 6 matched -O0 fns ×134 (per-overlay -O0 splits, uniform offsets, scriptable).

**Reusable wave recipe (proven this session):** `gen_harvest_targets --min-reach 134 --max-nins 90` → filter to cached Ghidra-C → Workflow (one agent/target, §17 toolkit, **pass args as a JSON array NOT a string** — the gotcha that bit us) → `canon_resident_calls` → **the new cast-recovery** → `harvest_verify --chunk 1` (chunk>1 mis-attributes compile-erroring drafts) → `dedup_propagate --auto-from`.

**Carry from T1 → recovery tooling (Phase-20 backlog item 2 / T2 router):** the **7 callee/data-plumbing capped fns** (reach-134, matched-but-local): `0x80142B2C 0x801535F4 0x80155E30 0x80157580 0x801576A8 0x80168F40 0x80170B48`. They fail `compiles_standalone` on undeclared callees/data, not types. A `dedup_propagate` macro-extern-injection (or canonical-callee-sig embed, the `gen_harvest_targets` approach) would free them ×134 (~+0.3%). NOT type-lift; do not reopen T1 for them.

## Blockers
None.

## Progress log
- 2026-06-20: Session start; read full load order (PROJECT_CONTEXT + 19 PhaseEnds). Phase 19 closed at 58.00%. Brainstormed strategy with Drew (ML/Wine/debug-symbols/gcc-papermario threads → honest verdicts; the wall is propagation-cap + ~3 uncracked gcc classes, not comprehension). Max set, plan mode. 3 Explore agents mapped the propagation/wave/quirk subsystems; verified the type-lift crux firsthand. Reframed (R14/P9): class-cracking = ~3 bounded spikes. Drew chose **class-crack first** + **skip permuter grind**. Plan approved (gate 1). CURRENT_PHASE + task list created (R28).

## Notes / decisions
- **R14/P9 reframe (recorded):** of 916 residual stubs — STRUCTURAL_MISS 368 (→waves), PERMUTER_CLASS 146 (→permuter/pins), ARITY_WALL 74 (→stub, fundamental loose-typing), fn-ptr/jtbl 144 (→struct context), NONFAITHFUL 16. Novel uncracked gcc classes = 3 (loop-guard, store-vs-load, `%lo`-folding); 2 carry a single prior "irreducible" verdict (worth ONE Max re-examination each, since the sibling regalloc-order class cracked with pins).
- **Honest % expectation:** T1 ~+0.6%; T3a maybe ~+0.6% (if `%lo` cracks); T3b/c may be 0 (cited-irreducible). Durable value = the codegen map + a higher wave close-rate, then T6 banks the scale %.
- **Commit cadence:** per-task/per-batch local checkpoints (long-phase precedent), each clean-rebuild-verified (R22). Drew pushes (R6).
