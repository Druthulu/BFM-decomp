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
- [x] **T0 [#1] — DONE** (commit commit:0101) — Phase-14 deferral recorded in `docs/gen2-roadmap.md`.
- [x] **T1 [#2] — DONE** — onboarded diverse wave-1 (12 overlays, all 7 SC areas + 2 dup pairs); `check-all` **18/18 byte-identical**, 0 anomalies.
- [ ] **T2 [#3] — IN PROGRESS** — build `tools/dedup_propagate.py` + `src/shared/engine_core.h`; prove on the wave (Tier 1 / Max).
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
- 2026-06-16 — **T0 done** (commit:0101): Phase-14 deferral propagated through gen2-roadmap (additive, H5).
- 2026-06-16 — **T1 done**: onboarded wave-1 = ov_{SC01_000, SC01_001, SC02_000, SC02_003, SC03_002, SC03_006, SC04_000, SC04_018, SC04_019, SC05_000, SC06_000, SC07_000} (all byte-identical at 100% INCLUDE_ASM in ~50s; dup pairs SC02_000≡003=5ece4bca, SC04_018≡019=fe9b413f). Fleet `make check-all` = **18/18 passed**. Position-lock risk retired across all 7 areas — no anomalies. Next: T2 (dedup_propagate.py).
