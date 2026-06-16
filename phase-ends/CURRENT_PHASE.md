# CURRENT PHASE — Phase 11: Cross-binary dedup pipeline

**Generation:** Gen2 (4th phase) · **Target version:** 1.11.0 · **Effort:** Max (default) · **Plan approved:** 2026-06-16
**Authoritative scope:** `docs/gen2-roadmap.md` lines 105–117. **Full plan:** `~/.claude/plans/plan-mode-enabled-max-purring-kite.md`

## Owner decisions (2026-06-16)
1. **Report + machinery; defer collapse.** Prove the cross-binary *report* via `sig_image` over overlays; prove the
   *share machinery* via an intra-binary `h_exact` collapse (byte-gated, stub fallback); wire cross-binary plumbing
   ready. First true two-binary collapse → Phase 13.
2. **PsyQ 4.7 = sha-record only** (already committed: `tools/psyq/conv47/` + `psyq-4.7-converted.zip`). Linking → Phase 12.

## Byte-verified facts (anchors)
- EXE `SLUS_007.26` byte-identical = SHA1 `143dbb89f34491258bbc27810d0a12ec8b43a8dd`.
- Resident `8e17e02ff8954d07c979449198f7e1645046b353`.
- **EXE↔resident share NO collapsible code** (h_exact=0; h_norm=2 trivial 4-ins leaves) — 4.0 vs 4.7 + different roles.
- Proof group (intra-EXE, h_exact): `func_80037004` ≡ `func_80037334` (9 ins, identical externals incl. `D_80076251`).
  Fallback: `def_cbready` ≡ `def_cbread` (10 ins, 1 call) or `SYS_OBJ_538` (3-way).

## Task checklist
- [ ] **T1** [xHigh] — `dup_report.py --cross` → `docs/duplicates.cross.md` (multi-sig ingest, binary tag, cross/intra
      split, `(count−1)×nins×4` rank, per-member rows); wire `make report` (gated BINARY=main). Verify per-binary
      reports byte-stable. ← **CURRENT TASK**
- [ ] **T2** [Max] — `config/dedup.us.yaml` schema + `tools/dedup_integrate.py` (fork psyq_integrate; byte-gate; stub
      fallback; `--check`/`--apply`); Makefile `SRC_SHARED_DIR` exclusion + member-driven gated call. Verify build
      `143dbb89` with dedup absent (no-op) + present-but-empty.
- [ ] **T3** [xHigh→Max] — intra-binary collapse PROOF (`func_80037004`→`src/shared/clearTbl40.c`, fill both addrs).
      Verify clean rebuild `143dbb89` WITH dedup AND WITHOUT (stub fallback); negative gate tests.
- [ ] **T4** [Max] — `tools/sig_image.py`: `h_exact` + boundary detection. Verify ≥99% h_exact vs `.run/sig.resident.jsonl`,
      zero UNEXPLAINED.
- [ ] **T5** [Max] — `sig_image.py`: `h_norm` normToken replica + resident acceptance gate (≥98% non-GTE; GTE/noncontig
      documented). Scope guard: ship h_exact + self-consistent h_norm if calibration over-runs.
- [ ] **T6** [xHigh] — sign 134 overlays @ `0x80128158` (deterministic loop, no fan-out); add to dup_report BINARIES;
      regenerate `docs/duplicates.cross.md` with real cross-binary groups.
- [ ] **T7** [xHigh; PhaseEnd=Max] — 4.7 sha-record + docs note; cookbook §11; SETUP/psyq-worklist/README refresh;
      regenerate reports; PhaseEnd.

## Milestone (gate 2)
Cross-binary report spans ≥2 binaries; one shared C body fills ≥2 addresses byte-gated, EXE `143dbb89`/resident
`8e17e02f` byte-identical with-and-without dedup (clean rebuild R22); plumbing accepts an overlay member w/o Makefile
change; 0 NON_MATCHING in default build.

## Blockers
(none)

## Progress log
- 2026-06-16: Phase planned at Max via 3 Explore + 2 Plan agents; owner approved. Key finding (EXE↔resident share
  nothing) reshaped the milestone to "report + machinery; defer collapse." Starting T1.
