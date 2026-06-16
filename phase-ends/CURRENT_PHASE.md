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
- [ ] **T2 — Iterate split to byte-identical (THE milestone)** (xHigh→Max if it fights) ← **CURRENT**
  - Converge subseg boundaries vs SHA1; handle leading data word; confirm -G0 (grep `($gp)`); ld_interleave only if a rodata island appears.
  - Exit: clean-rebuild → `8e17e02f…`, last byte @0x80128154; main re-verified `143dbb89…`. **→ progress report to Drew.**
- [ ] **T3 — Close per-binary tooling gaps** (xHigh)
  - `diff_settings.py` + `tools/progress.py` + `tools/difficulty.py` + `tools/dup_report.py` get a `resident` entry; `expected` made per-binary-safe (no sibling clobber).
  - Exit: `make report BINARY=resident` shows 100% INCLUDE_ASM; `make expected BINARY=resident` no-clobber; main report unchanged.
- [ ] **T4 — Ghidra 2nd program + seed `config/symbols.resident.txt`** (xHigh; G2 MCP precondition)
  - Import blob as 2nd program @0x800CEDF8 (MCP stopped for the lock); auto-analysis + PsyQ sigs + DetectPsyQ; light seeding; export blob-only symbols (R13/R15, never merged into symbols.us.txt).
  - Exit: rebuild still `8e17e02f…` (symbols don't change bytes); R9 persistence; R23 stop-MCP-before-commit.
- [ ] **Phase close** — P7 checkbox sweep; gate-2 milestone confirm (Drew); PhaseEnd_Phase10.md (Tier-1 Max); archive CURRENT_PHASE.md→logs/Phase10.md (R19); R18 recap; P8 hard stop.

## Commit cadence
Per-task checkpoint commits, each byte-gated (R20 + Phase 8/9 precedent). Claude commits locally; **Drew pushes** (R6). T4 commit includes Ghidra DB → **stop MCP first** (R23).

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
