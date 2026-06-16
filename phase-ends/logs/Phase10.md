# CURRENT_PHASE — Phase 10: Resident engine blob (splat config + all-asm byte-match)

**Generation:** Gen2 (phase 3 of the 8→9→**10**→11→{12,13}→14 arc) · **Started:** 2026-06-15
**Plan approved:** yes (gate 1 passed) · **Effort:** planning Max (done); execution xHigh (T2→Max if the split fights)
**Plan file:** `/home/musashi/.claude/plans/plan-mode-enabled-max-giggly-hollerith.md`

## Milestone (gate 2)
`make build BINARY=resident && make check BINARY=resident` → SHA1 **`8e17e02ff8954d07c979449198f7e1645046b353`**
at 100% INCLUDE_ASM, with `main` still **`143dbb89f34491258bbc27810d0a12ec8b43a8dd`** (no regression).

## Target facts (verified this session)
- File: `extracted/retail/MAIN.CD.dir/FILE_010.dir/1.1` — **365,404 B**, SHA1 `8e17e02f…`, PAC **type-1 (uncompressed)**, gitignored, manifest-verified.
- Load **vram 0x800CEDF8** (Phase-3 T6b proven); `VRAM_BASE`=0x800CEDF8 (fileoff 0→vram). Computed **end vram 0x80128154** (4 B under overlay slot 0x80128158 — boundary corroboration).
- First word = data `0x00000036`; code at +0x04. **Flat image, NO header segment.**
- Alias `resident`, basename `resident`. Paths: `build/resident/`, `config/splat.resident.yaml`, `config/check.resident.sha`, `config/symbols.resident.txt`, `.run/sig.resident.jsonl`, `asm/resident/`, `src/resident/`.

## Decisions locked (owner-confirmed 2026-06-15)
- Ghidra = **second program** in the `bfm` project (not a region in main).
- **Defer** EXE→resident pointer table (Q#2) to Phase 11/12.
- **Keep stacked** `symbol_addrs_path: [config/symbols.us.txt, config/symbols.resident.txt]` — 0 func syms in the resident window, 27 shared engine globals in symbols.us.txt the blob references; byte-identity is symbol-name-independent (no relocations).
- c-mode INCLUDE_ASM (match-ready); asm-mode is the de-risk fallback for the milestone.

## Tasks
- [x] **T1 — Scaffold `resident` instance + prove no-op on `main`** (xHigh) ✅ DONE
  - Makefile: `BINARIES += resident`; `resident_*` block; per-binary OBJS prune-list (`<bin>_ASM_DIR`/`SRC_DIR` + `$(BINARIES)`-derived prune); per-binary `UNDEF_SYMS`/`UNDEF_FUNCS` aliases (resident→`build/resident/undefined_*`).
  - `config/splat.resident.yaml` (flat, no header, no gp_value, single code seg c-mode, stacked symbols, per-binary asm/src/build/undefined paths, find_file_boundaries False).
  - `config/check.resident.sha` (seed `8e17e02f…  resident`); `config/symbols.resident.txt` (provenance banner, count=0).
  - Exit: (a) main `make clean&&extract&&build&&check`→`143dbb89…` (refactor is a no-op); (b) `make extract BINARY=resident` completes; (c) interleave check: `make build BINARY=main` after a resident extract still green.
- [x] **T2 — Iterate split to byte-identical (THE milestone)** (xHigh) ✅ DONE — **MILESTONE REACHED**
  - Converge subseg boundaries vs SHA1; handle leading data word; confirm -G0 (grep `($gp)`); ld_interleave only if a rodata island appears.
  - Exit: clean-rebuild → `8e17e02f…`, last byte @0x80128154; main re-verified `143dbb89…`. **→ progress report to Drew.**
- [x] **T3 — Close per-binary tooling gaps** (xHigh) ✅ DONE
  - `diff_settings.py` + `tools/progress.py` + `tools/difficulty.py` + `tools/dup_report.py` get a `resident` entry; `expected` made per-binary-safe (no sibling clobber).
  - Exit: `make report BINARY=resident` shows 100% INCLUDE_ASM; `make expected BINARY=resident` no-clobber; main report unchanged.
- [x] **T4 — Ghidra 2nd program + seed `config/symbols.resident.txt`** (xHigh) ✅ DONE
  - **+ parameterized `make sig-refresh` by BINARY** (per-binary GHIDRA_PROG; resident → `.run/sig.resident.jsonl`).
  - Import blob as 2nd program @0x800CEDF8 (MCP stopped for the lock); auto-analysis + PsyQ sigs + DetectPsyQ; light seeding; export blob-only symbols (R13/R15, never merged into symbols.us.txt).
  - Exit: rebuild still `8e17e02f…` (symbols don't change bytes); R9 persistence; R23 stop-MCP-before-commit.
- [ ] **Phase close** — P7 checkbox sweep; gate-2 milestone confirm (Drew); PhaseEnd_Phase10.md (Tier-1 Max); archive CURRENT_PHASE.md→logs/Phase10.md (R19); R18 recap; P8 hard stop.

## Commit cadence
Per-task checkpoint commits, each byte-gated (R20 + Phase 8/9 precedent). Claude commits locally; **Drew pushes** (R6). T4 commit includes Ghidra DB → **stop MCP first** (R23).

## Key finding (T4, 2026-06-15) — resident is PsyQ **4.7.0**, not 4.0.0
DetectPsyQ on the imported resident program reports **PsyQ Version = 470** (the EXE is 4.0.0); the import
associated a `psyq470` source archive alongside `psyq400`; the one PsyQ-signature hit in-range is `DsMix`
(libsnd → the resident holds the sound driver). **Drew (2026-06-15): the archive.org PsyQ link has the 4.7
libs.** Provenance (G5): detected, to be CONFIRMED in Phase 11/12 by linking real 4.7 libs and byte-matching.
**Implication:** the resident's PsyQ library linking (Phase 11/12) uses **4.7**, not the EXE's 4.0 — so the
4.7 `.LIB`s are a needed asset (R20: stage the hard-to-source tooling). Does NOT affect the Phase-10
byte-match (100% INCLUDE_ASM, no resident code compiled yet).
**DECISION (Drew 2026-06-15): DEFER the 4.7 `.LIB`s to Phase 11 START (archive.org link); CARRY this
finding into PhaseEnd_Phase10 "Notes for Future Phases" so Phase 11 fetches+sha-verifies them then. Phase 10
needs nothing from PsyQ 4.7.** → also record provenance in docs/memory-map.md.

## Blockers
(none)

## Worklog
- 2026-06-15: Phase planned (Max), 3 Explore + 1 Plan agent; gate-1 approved. Beginning T1.
- 2026-06-15: **T1 DONE.** Makefile: `BINARIES += resident`; `resident_*` block; per-binary
  `ASM_DIR`/`SRC_DIR` + `$(BINARIES)`-derived OBJS prune-list; per-binary `UNDEF_SYMS`/`UNDEF_FUNCS`.
  New: `config/splat.resident.yaml` (flat, no header, no gp_value, single `c` seg @0x800CEDF8,
  stacked symbols, per-binary undefined paths under build/resident/), `config/check.resident.sha`
  (8e17e02f…), `config/symbols.resident.txt` (R13 banner, 0 entries). **Gates all green:** (a) main
  clean rebuild → `143dbb89…` (refactor = no-op); (b) `make extract BINARY=resident` → 144 INCLUDE_ASM
  stubs, src/resident/resident.c + .ld @vram 0x800CEDF8; (c) main OBJS still 81 (excludes resident)
  + main rebuild `143dbb89…` with resident on disk (prune isolates). `src/resident/*.c` left untracked
  WIP (reshaped by T2 boundary carving — commit at T2). Committed config+Makefile checkpoint.
- 2026-06-15: **T2 DONE — MILESTONE REACHED.** Mapped the blob structure vs the bytes:
  word0 = data header (0x36); clean code 0x4..0x4610 (145 funcs, 0 embedded jtbls/trap-ops);
  data tail 0x4610..EOF (pointer tables + 78.5 KB zero run). Split = `[0x0, rodata, hdr]` +
  `[0x4, c, resident]` + `[0x4610, data, tail]`. Two fixes found: (1) leading word before code
  fights section_order → emit it as **rodata** (no-dot; section_order places .rodata first) — a
  1-word analogue of main's island, NO ld_interleave; (2) `build_path: build` (not build/resident)
  so the .ld's object paths match the Makefile's `build/asm/**`+`build/src/**` rules.
  **`make build BINARY=resident` → `8e17e02f…` BYTE-IDENTICAL** (365,404 B, end vram 0x80128154);
  -G0 confirmed (0 gp refs); R22 clean-rebuild green; main still `143dbb89…`. src/resident/resident.c
  (143 stubs) now committed (boundaries final). asm/resident/** regenerated (gitignored, like main).
- 2026-06-15: **T3 DONE.** `resident` entries added to diff_settings.py + progress/difficulty/dup_report.
  Two real bugs fixed: (1) dup_report crashed on the absent `.run/sig.resident.jsonl` → now writes a
  placeholder + exits 0 (sig is a T4 Ghidra export); (2) progress.py listed MAIN's LINKED libs for
  resident → scoped `linked_subsegs()` to BINARY==main (library linking is the EXE's layout, Phase 8).
  `expected` made per-binary-safe (merge-copy, no `rm -rf expected/build` sibling clobber — verified
  both baselines coexist). Reports: resident = 0 REAL / 143 stubs / 100% INCLUDE_ASM; main UNCHANGED
  (52 REAL / 959 LINKED / 50.24%). Carried into T4: parameterize `make sig-refresh` by BINARY.
- 2026-06-15: **T4 DONE.** New reusable tooling: `tools/ghidra_import_raw.sh` (BinaryLoader + base +
  PSX:LE:32 — the Gen2 raw-blob importer, reusable for Phase-13 overlays) and
  `tools/ghidra_scripts/DefineFunctions.java` (seed splat's validated boundaries — raw-binary
  auto-analysis finds only the reachable subset). Imported the resident as the bfm project's **4th
  program** `resident` @0x800CEDF8; auto-analysis (PsyQ sigs) → **PsyQ 4.7.0 detected** + `DsMix`
  (libsnd) named. Defined splat's 143 boundaries (created=120/existed=23/failed=0); **R9-verified
  143 funcs persisted** via read-only sig-refresh. Seeded `config/symbols.resident.txt` with `DsMix`
  (R13 candidate); re-extract applied it; **resident + main both clean-rebuild byte-identical** (R22).
  Makefile: per-binary `GHIDRA_PROG` → `make sig-refresh BINARY=resident`. dup_report now real
  (6 byte-identical groups intra-resident — Phase-11 dedup fodder). Ghidra DB committed (R23, MCP
  stopped): new `resident` program (00000003.*) + main's incidental db.15→db.16 no-op renumber.
  **4.7 libs DEFERRED to Phase 11 (Drew) — carry to PhaseEnd Notes.**
- 2026-06-15: **T5 / phase close.** P7 checkbox sweep complete (all 4 tasks + roadmap items met).
  Final clean-rebuild proof presented; **Drew confirmed gate 2.** SETUP §6.7 extended with the
  flat-blob recipe + 2 new tools (R21). PhaseEnd_Phase10.md written (Tier-1 Max). Rule R24 proposed
  (per-binary SDK provenance). This worklog archived → logs/Phase10.md (R19). v1.9.0 → v1.10.0.
