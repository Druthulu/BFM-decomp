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
- [x] **T2 [#3] — DONE** — `tools/dedup_propagate.py` + `src/shared/engine_core.h` built & proven: 4 funcs propagated across all 16 onboarded overlays, clean `check-all` **18/18**, dedup_integrate green, idempotent, negative-test fails-closed. Also added Makefile `-MMD` header-dep tracking (closed a stale-build gap the negative test exposed).
- [x] **T3 [#4] — DONE** — onboarded all remaining 118 overlays (0 failed) → full fleet **136 binaries**; **clean rebuild `check-all` 136/136 byte-identical** (R22, 0 extract fails, ~8 min).
- [ ] T3 [#4] — onboard remaining ~118 overlays (full fleet); 136/136 `check-all` from clean (R22).
- [x] **T4 [#5] — DONE** — `progress.py --fleet` → `docs/progress.fleet.md` (fleet **947 REAL / 959 LINKED / 13132 byte-identical / 344010 matchable = 3.82%**); refactor `report(binary)`+index (6m38s→7s, single-binary output unchanged); wired into `make report`; **fixed dup_report --cross double-count** (overlay counted as named binary AND glob → collapsible bytes were 2× inflated; back to accurate 28.6M). dedup-check 8/0. **(P6 rules check done before T4.)**
- [~] **T5 [#6] — (a) DONE / (b) PENDING TOGGLE** — (a) **bulk-propagated 553 already-matched shared funcs fleet-wide** (`dedup_propagate --auto-from ov_SC01_077`; 9 skipped = 077-local types, byte-gate caught + compile-pre-filter added): all 134 overlays byte-identical, 561 dedup groups (0 failed). **Fleet REAL 947→74,527; byte-identical 3.82%→22.14%.** (b) Ultracode-harvest the still-UNMATCHED shared core — **STOP: prompt Drew for `/effort ultracode` + WAIT before the harvest Workflow (R27).**
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
- 2026-06-16 — **KEY FINDING (reshapes T5):** of `ov_SC01_077`'s 785 matched signed functions, **577 are h_exact-identical across ALL 134 overlays** (2.19 MB collapsible) — already matched, just need propagating (free credit, no harvest). 204 are 077-unique. So T5 has two parts: (a) bulk-propagate these 577 already-matched shared funcs fleet-wide (mechanical, after T3); (b) Ultracode-harvest the still-UNMATCHED shared core (the big ex0–ex50 giants/mediums, mostly unmatched even in 077).
- 2026-06-16 — **T5(a) done** (the big free-credit run): `dedup_propagate --auto-from ov_SC01_077` bulk-propagated **553** already-matched shared functions across all 134 overlays, each byte-gated. Hardened the tool for fleet scale: registry **shorthand** (vram+binaries; dedup.us.yaml 4050 lines vs ~77k verbose), **per-overlay apply** (one read/write/file), **gate-only-changed**, **skip already-registered** (additive/resumable), and a **compile pre-filter** (body must build with common.h alone — 9 functions use 077-local struct types and were skipped honestly; the byte-gate first caught one mid-run → fail-closed revert → added the filter). `group_members()` reader (both forms) in dedup_integrate + progress; progress `_DEDUP_CACHE` (fleet 136× parse → 1). **Fleet: REAL 947→74,527, byte-identical 13,132→76,174 = 22.14%**; dedup-check 561 validated / 0 failed. R22 clean rebuild verifying before commit. Next: T5(b) Ultracode harvest of the unmatched core (R27 toggle).
- 2026-06-16 — **T4 done**: refactored `progress.py` → `report(binary)` + `--fleet` (aggregates `docs/progress.fleet.md`, deterministic source-derived) + a per-binary `.s` index (fleet run 6m38s→7s; single-binary `docs/progress.md` byte-unchanged). Wired `--fleet` into `make report`. **Honesty fix (R14):** `dup_report --cross` was double-counting each onboarded overlay (named BINARIES entry AND `.run/sig.ov_*` glob) → collapsible bytes 2× inflated (58.7M); deduped by alias → accurate **9366 h_exact groups / 28.6M collapsible**. `make report` green, dedup-check 8/0. Fleet now: 947 REAL / 959 LINKED / 3.82% byte-identical. Rules check (P6) done. Next: T5.
- 2026-06-16 — **T3 done**: onboarded all remaining 118 overlays (sequential new_overlay.sh, 0 failed) → fleet = 134 overlays + main + resident = **136 binaries**. R22 CLEAN rebuild (make clean → extract all 136 → check-all) = **136 passed / 0 failed**, 0 extract fails. Every overlay byte-identical at 100% INCLUDE_ASM. Report-tool dicts + overlays.mk auto-registered by new_overlay.sh. Next: T4 (fleet roll-up + regenerate fleet-wide cross-report).
- 2026-06-16 — **T2 done**: built `tools/dedup_propagate.py` (extract body → DEFINE_func macro in src/shared/engine_core.h → in-place stub/def replace at every h_exact member → snapshot+byte-gate fail-closed → register dedup.us.yaml). Proven on 4 medium funcs (0x80128EA8/8012A568/80132EC4/80138C30) across all 16 onboarded: clean `check-all` 18/18, dedup_integrate 8 validated/0 failed, idempotent re-run no-op, negative test (corrupt body) → `make check` FAILS then restores. Fixed 2 bugs found by self-verification: (i) edit-accumulation read from snapshot not disk (only last fn landed); (ii) **Makefile had no header-dep tracking** → header-only edits were stale/false-pass → added `cpp -MMD -MP` + `-include $(C_DEPS)` (output-neutral; R22-clean 18/18). Cookbook §14, SETUP inventory updated. Next: T3.
