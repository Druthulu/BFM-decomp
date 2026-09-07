# CURRENT_PHASE — Phase 13: Representative location overlays (end-to-end + fleet runbook)

> Gen2 phase 6. Plan approved 2026-06-16. Crash-recovery task log (P3/P5). **Milestone MET** (gate 2 pending Drew's confirm).

## Status: 6 binaries build BYTE-IDENTICAL (main, resident, + 4 overlays)
| binary | sha1 | state |
|---|---|---|
| main | 143dbb89 | unregressed |
| resident | 8e17e02f | unregressed |
| ov_SC01_077 | d19c9580 | **REAL 690/2586** (Ultracode harvest, 5 passes) + Ghidra-imported |
| ov_SC01_005 | 56760dbe | dup pair; REAL 3 (shared) |
| ov_SC01_006 | 56760dbe | dup pair; REAL 3 (shared from one source) |
| ov_SC03_001 | f8fd92f5 | free-roam (scale test) |

## Tasks
- [x] **T0** — overlay splat template + `overlays.mk` indirection (no-op proven)
- [x] **T1** — SC01/077 end-to-end: byte-match `d19c9580` + 690-fn Ultracode harvest + Ghidra import. Reusable non-4-aligned-overlay handling (bin carve + incbin asset rule + objcopy end-align trim).
- [x] **T2** — dup-pair collapse SC01/005 ≡ 006: `src/shared/ov_setters.h` (SETTER/RETCONST macros) instantiated in both .c; `dedup.us.yaml` D1/D2/D3; both `56760dbe` from one source; dedup_integrate 4 validated/0 failed.
- [x] **T3** — free-roam ov_SC03_001 byte-identical `f8fd92f5`.
- [x] **T4** — `tools/new_overlay.sh` one-command onboarding (idempotent; proven on 005/006/001).
- [x] **T5** — `make build-all`/`check-all`: 6/6 [OK] exit 0; negative control fails loud.
- [ ] **T7** — effort experiment (Max vs Ultracode Workflow yield, controlled 80-fn set `.run/ov077_exp.txt`). Drew's add-on; needs the effort-toggle dance.
- [ ] **T6** — docs (cookbook §13 runbook + overlay-handling additions, SETUP, gen2-roadmap status, per-ov digests) + PhaseEnd (Tier-1 Max). Includes the clean fleet proof (`make clean` → extract-all → `check-all`, R22).

## Commits (this phase)
50c5c9ea3 T0 · 144839f24 T1a/b · 3b59354c7 T1c · 0278a902d/fdc9e22a8/b6a82b8c4/5ccdd2b22/ce07b7279 harvest p1-5 · 3262cbca3 T1c-Ghidra · 67592993e T3+T4 · eee4cb319 T2 · e2200e17d T5

## Blockers / next
→ **Gate 2** (Drew confirms milestone) + **T7** (needs `/effort ultracode` for arm A, then `/effort max` for arm B) → **T6** PhaseEnd at Max.
