# CURRENT PHASE — Phase 19: Scale the toolkit (wave-harvest at scale + cheap front-loaded levers)

**Started:** 2026-06-20 · **Generation:** Gen2 (11th phase) · **Plan approved (gate 1):** Drew, 2026-06-20
**Effort:** Max (planning/synthesis) · xHigh (T1/T2 execution) · **Ultracode for T3 wave batches** (prompt at the transition, R26/R27)
**Plan file:** `~/.claude/plans/plan-mode-enabled-max-golden-truffle.md`

## Scope decisions (Drew, gate 1)
- **Bounded flywheel** — T1 + T2 + **2–3 wave batches of 50**, bank gains, close at a clean checkpoint with a Phase-20 backlog. (Not open-ended; not infra-only.)
- **gcc-research spike (T4) = CONDITIONAL in-phase** — runs ONLY if the waves plateau on a residual class blocking meaningful reach.

## Baseline at phase start (verified this session)
- Fleet **56.64%** byte-identical-from-source (194,839 / 344,010); 136/136 binaries byte-identical; 1450 dedup groups (0 failed); 0 NON_MATCHING.
- `ov_SC01_077`: 1719/2586 = 66.5%, 867 INCLUDE_ASM stubs remaining; clean-rebuild SHA `d19c9580…`.
- Staged: `.run/harvest_wave_p18s1.js` (120 tractable reach-134 targets; P18 ran 31). Ghidra-C cache `.run/ghidra_c/` = 300 fns (fresh).

## Tasks
- [x] **T1 — Per-file -O0 split-file lever** — DONE (re-scoped by Drew: bank infra + 6, defer rest). The 3-object split works (`ov_SC01_077_a` before / `ov_SC01_077_o0` -O0 / `ov_SC01_077` after — a single object's .text can't be split around a middle object). **6/16 -O0 fns matched** byte-perfect (`func_8013B568/B7F4/BD34/C360/C938/C964`). **DEFERRED to Phase 20:** the 10 remaining -O0 fns hit an indexed-global `%lo`-folding codegen quirk (gcc-source research, R17 — our cc1 materializes the address, the original folds %lo); AND the ×134 per-overlay rollout (engine_core.h compiles -O2, can't carry -O0 fns → each overlay needs its own -O0 split). Two findings corrected the Phase-18 backlog's "afternoon, free ×134" premise (R14).
- [ ] **T2 — Recovery tooling.** `tools/cast_call_sites.py` (call-site fn-ptr casts) + implicit-int propagate-first. Build/validate on `.run/drafts-p18s1/` near-misses.
- [ ] **T3 — Scale waves (2–3 batches of 50, Ultracode).** Regen Ghidra-C for fresh targets, `gen_harvest_targets.py` manifest, Step-1 wave prompt → recovery (T2) → gate → `dedup_propagate` ×134 → checkpoint → improve. Each batch = a progress report.
- [ ] **T4 — (CONDITIONAL) gcc-research spike.** Only on a blocking residual class (loop-guard order `func_8012C2D0`; §10 schedule `func_8014F2E0`).
- [ ] **PhaseEnd** — verify all checkboxes (P7), demonstrate milestone, write `PhaseEnd_Phase19.md` (+ `## Plain-English Recap`, R25; Phase-20 backlog), archive worklog (R19).

## Milestone (gate 2, Drew confirms)
-O0 lever banked + recovery tooling proven + toolkit scaled across 2–3 batches of 50, fleet up materially (target +3–5%, ~56.6% → ~60%), 136/136 byte-identical from clean (R22), 0 NON_MATCHING (G4), closed at a clean checkpoint with a Phase-20 backlog.

## Progress log
*(append one line per task as completed)*
- 2026-06-20 — Phase started; plan approved (gate 1); task list built (R28); CURRENT_PHASE.md created. Beginning T1.
- 2026-06-20 — T1: built + proved the 3-object -O0 split infra; matched 6/16 -O0 fns (ov_SC01_077 d19c9580). Two consults with Drew on T1 scope: (1) full -O0 rollout chosen, then (2) on discovering the remaining fns are research-grade (the %lo quirk), Drew chose "bank 6 + infra, defer rest to Phase 20." Fleet unchanged (the 6 are ov_SC01_077-local until rollout). Verified main/resident/ov_SC01_077/+2 byte-identical. Committed checkpoint. → T2.

## Blockers
*(none)*

## Notes / carried to Phase 20
- **The -O0 lever completion (NEW, from T1):** infra is built + proven in ov_SC01_077 (the 3-object split). Remaining: (a) **match the 10 indexed-global -O0 fns** — blocked by the `%lo`-folding quirk (our cc1 materializes `lui;addiu;addu;sw 0(reg)`; original folds `lui;addu;sw %lo(sym)(reg)`); needs gcc-2.7.2 source research (R17/§17), maybe unsteerable from C. Stubs: func_8013B598/B6A0/B7AC/B83C/BC7C/BCDC/BD74/C08C/C0F8/C414. (b) **The ×134 rollout** — each overlay needs its own -O0 split (uniform offsets 0x13410/0x14834, shared bodies header); engine_core.h can't carry -O0 fns. ~+0.6% fleet when complete. (c) the 2 -O0 outliers (func_80144B9C giant + func_801457A4).
- Most giants (28 reach-134 >150-ins); per-overlay unique remainder (×1); comprehension/emulator actor-field naming; Wine/CC1PSX (parked); public flip (Phase 14, Gen3+).
