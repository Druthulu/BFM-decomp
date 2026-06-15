# CURRENT PHASE — Phase 7: Matching loop at scale + Gen1 close-out

**Status:** Plan APPROVED 2026-06-14. **REORDERED 2026-06-14** (Drew): bank non-switch wins first; the
rodata-island foundation + LZSS match are DEFERRED to a focused sub-project after the easier tasks.
**Full plan:** `~/.claude/plans/confirmed-plan-mode-enabled-jolly-lemon.md`. **Project version:** 1.6.0 → 1.7.0 at PhaseEnd.

> In-phase crash/compaction recovery log (P3 step 4). Update after every task.

---

## Locked decisions (developer-confirmed)
- **≥25 = real substantive matches** (the 42 splat-auto empties do NOT count). 14 real now → need ≥11 more.
- **Loader cluster = match-tractable / draft-hard** (NON_MATCHING-draft the hard state machines).
- **REORDER (2026-06-14):** rodata foundation hit a structural wall (see below); do reports + harvest + non-switch loader FIRST, then a focused LZSS/rodata sub-project. LZSS is still required for Gen1 exit.

## Verified baseline (grounded; R14 corrections)
- Build byte-identical (`143dbb89f34491258bbc27810d0a12ec8b43a8dd`), reproducible. **Only change from committed Phase-6 = one R15 symbol line** (`func_80047CAC = 0x80047CAC; // data`) — fixes a LATENT NON-REPRODUCIBILITY: spimdisasm 1.41.0 auto-detection of that 8-byte inter-fn blob is unstable across clean extracts; declaring it makes `make clean && make extract && make build` deterministic. (Note for PhaseEnd.)
- Switch cohort ~46 funcs / 53 tables (51 in-image, single-ref/migratable). LzssDecodeSector 0x80018730 = gcc switch via `jtbl_80072A38` (write-free rodata island 0x80072A38–0x80074750 / file 0x63238–0x64F50).
- All 13 loader-cluster funcs in text region (< 0x800629DC). Authoritative counts: 14 real / 42 empty / 2 NON_MATCHING / 1998 stubs / 2050 matchable.

---

## Task checklist (REORDERED — execution order top to bottom)
- [x] **Task 3 — Report machinery** ✓ DONE. `tools/{progress,difficulty,dup_report}.py` + `make report` (deterministic) + `make sig-refresh`. Authoritative baseline **14 real / 42 empty / 2 NM / 1992 stubs / 2050 matchable** (REAL/matchable=0.68%); empties audit 42/42 clean; dup leverage 8 h_exact + 44 h_norm redundant; harvest queue 1119 non-jtbl leaves + 313 trivial. Digests → `docs/{progress,difficulty,duplicates}.md`.
- [x] **Task 4 — Harvest to ≥25 real** ✓ DONE. **36 real matches** (14 + 22 trivial accessor leaves: getters/setters of globals, one mask, one two-store), build BYTE-IDENTICAL → all 22 byte-perfect. **≥25 bar PASS** (margin 36/25). `.run/harvest.py` = the applier. Dedup-collapse skipped (the sig dup groups are mostly PsyQ library fragments/epilogues, not real funcs). LZSS still required (Task 2′).
- [x] **Task 5.5 — Per-file -O0 split mechanism** ✓ DONE (session B, Drew-approved). MAJOR FINDING: per-module opt mixing is real (§5.5). The **boot/main/game-mode-dispatch module @ vram 0x80010000–0x800123F0** (~50 funcs incl. start/main/GameModeDispatch/DebugMenuHandler) is **-O0**, not the pinned -O2; everything ≥0x800123F0 is -O2. Mechanism: split text c-subseg → `[0x800,c,boot]→src/boot.c` (-O0 via Makefile target-specific CC1FLAGS) + `[0x2BF0,c,800]→src/800.c` (-O2, matched fns untouched). Regression gate PASS (byte-identical at 100% INCLUDE_ASM). Cookbook §6 added (detect via `21F0A003` frame-ptr sig; `register`-pointer far-member idiom). Reusable for every future flag-divergent module.
- [x] **Task 5.6 — PsyQ CD struct header** ✓ DONE (session B). `include/psyq/libcd.h` (CdlLOC 4B + CdlFILE 24B, offsets from Ghidra `/LIBCD.H`, G1) + 3 libcd protos; added 4 PsyQ symbols to `config/symbols.us.txt` (CdSearchFile/CdPosToInt/CdIntToPos/VSync — Ghidra-confirmed, R15) and renamed their `func_*` stubs in src/800.c. Build BYTE-IDENTICAL (label-only); header compiles, sizeof asserts hold. Unlocks the file-loader cluster (LoaderInitFileTable, ResourceLoadStateMachine, the jtbl loaders). Cookbook §7 added (PsyQ types/symbols pattern). **NB symbols.us.txt now has 983 lines (4 appended, un-sorted — re-merge note for R15).**
- [~] **Task 5 — Loader cluster** PARTIAL (42 real total; non-jtbl 5/7 matched). Matched (score 0, byte-identical): **ResourceGetCdLoc** (15), **LoaderResetReadState** (32), **GameModeDispatch** (29, -O0 `register`-ptr far member), **DebugMenuHandler** (30, -O0, reserved-slot local), **CdQueueBusy** (35, -O2 — if/else order + branch polarity), **CdReadRequest** (53, -O2 — early-return fall-through). Triage of the rest:
    - **jtbl → Task 2′ (rodata-gated):** CdReadStateMachine (385), CdReadSectorReadyCB (424, sole LZSS caller), SaveLoadRoutine (1139), StreamLoadStateMachine (459).
    - **non-jtbl COMPLETE (6 matched + 2 drafted):** **LoaderInitFileTable** (133) + **ResourceLoadStateMachine** (211) → **NON_MATCHING-drafted** (logically faithful, libcd.h-typed; per-function residual notes in src/800.c — LoaderInit: regalloc/loop-invariant hoisting + name=base-0x14; ResourceLoad: block placement (state 0→1→2→3 layout vs nested-if) + reserved-local frame 0x38 vs 0x28 + func_8002D4C8 arg & 0xFFFF). **NON_MATCHING count now 4.** Byte-match both in a later structural/permuter pass.
- **Report tooling fixed for the multi-file split:** `tools/{progress,difficulty}.py` now glob all `src/*.c` + search all `asm/nonmatchings/*` subdirs, and `progress.py` skips `extern …(…);` forward-declarations (they were swallowing the next fn + double-counting). Deterministic; 42 real / 1964 stubs consistent across both. (Note for PhaseEnd.)
- [ ] **Task 2′ — Focused LZSS + rodata-island sub-project** (DEFERRED hard task; Gen1-exit LZSS gate). **Max.** See investigation findings below.
- [ ] **Task 6 — Gen1-exit close-out** (README, checklist, ≥3-session zero-regression evidence). **xHigh.**
- [ ] **Task 7 — PhaseEnd_Phase7** (Gen1 synthesis, milestone gate). **Max · Tier 1.**

## Current task
**Task 5 — Loader cluster** (match-tractable non-switch / draft-hard). Then Task 2′ (LZSS), Task 6, Task 7.
NOTE: Gen1 exit needs ≥3 SESSIONS of green `make check` — cannot complete this session regardless.

## Per-session `make check` green log (≥3 sessions needed for the milestone)
- 2026-06-14 (session A): `make check` → `143dbb89… BYTE-IDENTICAL` ✓ — baseline restored + reproducibility fix, reports built, **38 real matches** (22 accessor leaves + ResourceGetCdLoc + LoaderResetReadState), build byte-identical throughout. [need ≥2 more sessions]
- 2026-06-14 (session B): `make check` → `143dbb89… BYTE-IDENTICAL` ✓ — **per-file -O0 split mechanism** (src/boot.c + Makefile per-file flags); **4 real matches** (GameModeDispatch, DebugMenuHandler, CdQueueBusy, CdReadRequest) → **42 real**; **PsyQ libcd.h infra** (CdlLOC/CdlFILE + 4 named symbols, unlocks the loader cluster); **LoaderInitFileTable + ResourceLoadStateMachine NON_MATCHING-drafted** (→ 4 NM) — **Task 5 non-jtbl loaders COMPLETE** (6 matched + 2 drafted); report tooling fixed (multi-file); cookbook §6/§7/T4. Build byte-identical throughout. [need ≥1 more session]

---

## Rodata-island foundation — investigation findings (DEFERRED, for Task 2′)
Attempted the 3-way data split (`[data front][.rodata island][data tail]` + `ld_legacy_generation: True`).
**What works:** dotted `.rodata` sibling named `800` → spimdisasm MIGRATES each jump table into its owning
function's `.s` (`jtbl_80072A38` lands inside `LzssDecodeSector.s` with `.section .rodata`/`.section .text`),
references resolve intra-800.o, build LINKS. Non-migrated multi-ref rodata becomes `INCLUDE_RODATA` (70 lines)
in a FRESH-regenerated `800.c`.
**What blocks byte-identity (the structural wall):**
1. Adding any `rodata` subseg turns on global jumptable analysis → merges 56 over-split switch fragments (good) but DROPS an 8-byte inter-fn blob (the `func_80047CAC` issue, now fixed via explicit symbol).
2. A separate rodata object can't link to text-local `.L`/`jlabel` jumptable targets → must migrate (co-locate).
3. splat places sections CONTIGUOUSLY (no explicit `. = addr`), so any size drift shifts the whole image. Observed a **24-byte `.text` overrun** (`main_TEXT_END` 0x800629F4 vs 0x800629DC) → +24B size, 85288 bytes differ. Root cause of the 24B NOT fully pinned.
**Candidate fix for Task 2′:** explicit linker addresses (Makefile post-extract `.ld`-patch placing `.text`@0x80010000, front `.data`@0x800629DC, `800.o(.rodata)`@0x80072A38, tail `.data`@0x80074750) + scope migration so only island tables land in `800.o(.rodata)`. Alternative: sotn-style per-file split (Gen2-scale). Reproduce with the migration config (in git stash / reconstruct from this log).

## Blockers / open items
- Task 2′ ld-placement mechanism (above). MCP-mode batching: sig-refresh needs MCP stopped, LZSS needs MCP live.

## Notes
- Commits accumulate UNCOMMITTED; one phase-end commit by the developer (R8/R6).
- `.run/merge_matches.py` = the regenerate-800.c + re-apply-matches helper (reusable for Task 2′).
