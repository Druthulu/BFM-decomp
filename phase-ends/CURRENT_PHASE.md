# CURRENT PHASE — Phase 15: Overlay long-tail (ONGOING, not a Gen2 gate)

**Started:** 2026-06-16 · **Project Version (in progress):** 1.13.0 → 1.14.0 · **Generation:** Gen2 (7th phase)
**Effort:** Max (planning + deep tasks); **Ultracode** for the breadth harvests (T5/T6/T7-unique), with the R27 pause-and-wait toggle at each transition.
**Plan file:** `~/.claude/plans/defer-phase14-till-gen3-cheeky-yeti.md` (approved by Drew, gate 1).
**Decisions (Drew, 2026-06-16):** Phase 14 deferred to Gen3+; scope = "build machine + full fleet sweep"; **Ghidra-free by default, escalate to per-overlay → per-SC-area Ghidra import only when the Ghidra-free loop stalls** (T7).

## Strategy (one line)
Overlays are position-locked at vram 0x80128158 and share an enormous engine core byte-identical across all 134 (9366 h_exact groups, ~29.7 MB collapsible), mostly still unmatched → **match the shared core ONCE → propagate fleet-wide** via a new `tools/dedup_propagate.py`, not re-harvest each overlay. The per-overlay `make check` byte-gate is the sole arbiter (G3/P9).

## Verified ground truth (this session, R14)
- 134 overlays on disc; **129 distinct by sha1**; 5 byte-identical dup pairs (free 2-for-1): SC01_005≡006 (done), SC02_000≡003, SC03_014≡015, SC03_118≡119, SC04_018≡019.
- Onboarded (4): ov_SC01_077 (704 REAL, d19c9580), ov_SC01_005 & 006 (3 REAL, 56760dbe), ov_SC03_001 (0 REAL, f8fd92f5). Resident 123/146. Main 54 REAL/959 LINKED.
- Top cross groups: ex0=770 ins @0x80144b9c ×134; ex1=476 @0x80141ca4; ex3=41 ins ×1104 — mostly unmatched even in 077.

## Tasks (harness IDs in brackets; one at a time, P4)
- [ ] **T0 [#1] — IN PROGRESS** — record Phase-14 deferral in `docs/gen2-roadmap.md`.
- [ ] T1 [#2] — onboard diverse wave-1 (~12 overlays); `check-all` green.
- [ ] T2 [#3] — build `tools/dedup_propagate.py` + `src/shared/engine_core.h`; prove on the wave (Tier 1 / Max).
- [ ] T3 [#4] — onboard remaining ~118 overlays (full fleet); 136/136 `check-all` from clean (R22).
- [ ] T4 [#5] — `progress.py --fleet` → `docs/progress.fleet.md`; wire into `make report`. **(P6 rules check after T4.)**
- [ ] T5 [#6] — Ultracode shared-core harvest Tier-1 (small/high-count) + propagate fleet-wide. **(R27 toggle prompt.)**
- [ ] T6 [#7] — Ultracode shared-core harvest Tier-2 (medium) + propagate.
- [ ] T7 [#8] — ongoing tail: giants (match_one) + per-overlay unique remainder; Ghidra escalation when stuck.
- [ ] T8 [#9] — phase close: milestone proof (136/136 clean) + PhaseEnd (Tier 1 / Max).

## Milestone (machine-checkable, P9; tail stays ongoing)
1. All 134 onboarded; `make clean && extract-all && check-all` → 136/136 byte-identical from clean (R22); negative control fails loud.
2. `dedup_propagate.py` proven fleet-wide (≥1 shared fn propagated across the full fleet, all byte-identical, dedup_integrate green, idempotent + negative test fail-closed).
3. `docs/progress.fleet.md` deterministic fleet totals (byte-identical %, collapsible bytes retired/remaining).
4. Shared-core harvest banked + reported honestly; giants + per-overlay unique tails logged as ongoing remainder.

## Blockers / open
- None.

## Log
- 2026-06-16 — Session start: read load order (PROJECT_CONTEXT + all 14 PhaseEnds, no prior CURRENT_PHASE). Drew: skip Phase 14, do Phase 15, Max effort, plan mode. Verified ground truth (overlay count, dup pairs, cross-report, per-overlay counts) directly, correcting several sub-agent overclaims (R14). Plan approved (gate 1). Task list created (R28). Starting T0.
