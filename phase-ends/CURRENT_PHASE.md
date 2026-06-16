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
- [x] **T1** [xHigh] — `dup_report.py --cross` → `docs/duplicates.cross.md` (multi-sig ingest, binary tag, cross/intra
      split, `(count−1)×nins×4` rank, per-member rows); wired `make report` (gated BINARY=main). Per-binary reports
      byte-stable. **DONE** (commit `commit:0060`). EXE↔resident cross groups = 0 (confirms the byte-finding).
- [x] **T2** [Max] — `config/dedup.us.yaml` schema + `tools/dedup_integrate.py` (byte-honesty VALIDATOR, fail-closed on
      hash drift) + `make report` dedup-check gate. **DONE.** Verified: --check passes on empty registry; clean rebuild
      main → `143dbb89` (no-op proven, R22). *Refinement below.*
- [x] **T3** [xHigh] — intra-binary collapse PROOF. **DONE.** `src/shared/clearTbl40.h` macro `CLEAR_TBL40`
      instantiated at both `func_80037004`/`func_80037334` in `src/800.c`; matched first try. Clean rebuild
      `143dbb89` WITH shared-C AND WITHOUT (stub) — dual invariant. I0 in `dedup.us.yaml`; dedup-check PASS;
      negative tests (wrong hash/vram) fail-closed. progress REAL 52→54 (2 dedup-shared), 50.33%.
- [x] **T4** [Max] — `tools/sig_image.py`: Ghidra-free `h_exact` signer + boundary detection. **DONE.** Validated
      vs resident oracle: **100% h_exact on the contiguous/non-GTE subset (140/140), zero UNEXPLAINED** (98.6%
      overall). 2 misses = non-contiguous bodies (D5, inherent to a linear sweep). Boundary rule: first `jr $ra`
      at/after all forward targets. h_norm/h_seq = conservative placeholders (= h_exact) until T5.
- [x] **T5** [Max] — `sig_image.py`: `h_norm` (self-consistent normalization: mask j/jal targets + lui highs +
      hi/lo-paired address-los; keep registers/constants/branch-offsets) + `h_seq` (mnemonic seq). **DONE via the
      scope-guard (deviation D2).** Validated on the resident: h_exact groups 6/6 == Ghidra; h_norm reproduces 7/9
      Ghidra structural groups, the 2 disagreements benign (differ only in masked address/jump fields — Ghidra's own
      ref-analysis is inconsistent there); byte-gate is the final acceptance for any h_norm candidate.
- [ ] **T6** [xHigh] — sign 134 overlays @ `0x80128158` (deterministic loop, no fan-out); add to dup_report BINARIES;
      regenerate `docs/duplicates.cross.md` with real cross-binary groups.
- [ ] **T7** [xHigh; PhaseEnd=Max] — 4.7 sha-record + docs note; cookbook §11; SETUP/psyq-worklist/README refresh;
      regenerate reports; PhaseEnd.

## Milestone (gate 2)
Cross-binary report spans ≥2 binaries; one shared C body fills ≥2 addresses byte-gated, EXE `143dbb89`/resident
`8e17e02f` byte-identical with-and-without dedup (clean rebuild R22); plumbing accepts an overlay member w/o Makefile
change; 0 NON_MATCHING in default build.

## Deviations / refinements (for the PhaseEnd)
- **D1 — Game-code dedup is SOURCE-LEVEL, not a `psyq_integrate` object-swap.** The approved plan said
  "fork `psyq_integrate.py` (.ld interpose) for the cross case." The byte-reality: `psyq_integrate`'s swap only
  works for separate library *subsegment* stub objects; game-code functions are interior to one object per binary
  (`build/src/800.o`, `build/resident/resident.o`), and the linker can't excise interior bytes. So a shared body is
  authored once (a macro in `src/shared/<fn>.h`) and instantiated at each member site in each binary's `.c` (same
  bytes at each vram). The **byte-gate is the existing per-binary `make check`**; `dedup_integrate.py` is the
  byte-honesty **validator** (fail-closed on hash drift), not an interpose engine. The `.ld` interpose stays the
  library mechanism (Phase 8, untouched). Milestone + owner decisions unchanged; tool is simpler + byte-correct.
  Consequence: no `SRC_SHARED_DIR` OBJS exclusion needed (shared bodies are `.h`, skipped by the `*.c` glob); no
  build-recipe change (dedup-check lives in `make report`).
- **D2 — sig_image `h_norm` is SELF-CONSISTENT, not a Ghidra-byte-exact `normToken` replica.** The plan's gate was
  "h_norm ≥98% byte-match vs Ghidra." Byte-reality made that low-value: EXE↔resident share nothing, overlays share
  with EACH OTHER (h_exact, since they load at the same vram) and call (not embed) the resident — so cross-tool
  structural (overlay↔Ghidra-binary `h_norm`) is the only thing a byte-exact replica would add, and it's low-value.
  sig_image uses a self-consistent normalization (uniform within the overlay fleet) + `h_exact` as the
  format-independent cross-tool tier; every `h_norm` candidate is byte-gated (its sole acceptance, per the roadmap).
  Full Ghidra-byte-exact `normToken` is a documented future refinement (would need dumping Ghidra's raw normToken
  strings + iterating; chases Ghidra's own ref-analysis inconsistencies). Scope-guard was pre-approved in the plan.

## Blockers
(none)

## Progress log
- 2026-06-16: Phase planned at Max via 3 Explore + 2 Plan agents; owner approved. Key finding (EXE↔resident share
  nothing) reshaped the milestone to "report + machinery; defer collapse."
- 2026-06-16: **T1 done** (`commit:0060`) — `dup_report --cross` → `duplicates.cross.md`; per-binary reports byte-stable;
  EXE↔resident cross groups = 0.
- 2026-06-16: **T2 done** — `dedup.us.yaml` registry + `dedup_integrate.py` validator + `make report` gate; clean
  rebuild main `143dbb89` (no-op, R22). Recorded deviation D1 (source-level share). Next: T3 proof.
- 2026-06-16: **T3 done** — machinery half of the milestone PROVEN. Shared body `CLEAR_TBL40`
  (`src/shared/clearTbl40.h`) → `func_80037004`+`func_80037334`; matched first try; clean rebuild `143dbb89`
  WITH shared-C and WITHOUT (stub); I0 validated, fail-closed negatives pass; REAL 52→54. `progress.py` taught to
  count dedup members (registry source-of-truth). Next: T4 (sig_image h_exact) — the report half's tooling.
- 2026-06-16: **T4 done** — `tools/sig_image.py` (rabbitizer, Ghidra-free). h_exact byte pipeline + boundary
  detection validated on the resident: 100% h_exact on the 140 contiguous/non-GTE funcs, zero UNEXPLAINED; 2
  non-contiguous bodies (D5) are inherent residuals. Next: T5 (h_norm normToken calibration).
- 2026-06-16: **T5 done** — sig_image h_norm (self-consistent normalizer + HiLoTracker) + h_seq. Validated on the
  resident: h_exact 6/6 groups == Ghidra; h_norm 7/9 Ghidra structural groups, disagreements benign (masked-field
  only). Took the pre-approved scope-guard → self-consistent (deviation D2), not Ghidra-byte-exact. Next: T6 (sign
  the 134 overlays + populate the cross-report — the milestone's report half).
