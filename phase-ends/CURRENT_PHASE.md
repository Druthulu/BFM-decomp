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
- [~] **Task 5 — Loader cluster** PARTIAL. Matched: **ResourceGetCdLoc** (15, table lookup), **LoaderResetReadState** (32, store seq) → byte-identical. Triage of the rest:
    - **jtbl → Task 2′ (rodata-gated):** CdReadStateMachine (385), CdReadSectorReadyCB (424, sole LZSS caller), SaveLoadRoutine (1139), StreamLoadStateMachine (459).
    - **non-jtbl, need Ghidra+iteration:** GameModeDispatch (29, base+offset addr + callee-saved across jalr), DebugMenuHandler (30), CdReadRequest (53), LoaderInitFileTable (133), ResourceLoadStateMachine (211), CdQueueBusy (35). Match or NON_MATCHING-draft in continuation.
- [ ] **Task 2′ — Focused LZSS + rodata-island sub-project** (DEFERRED hard task; Gen1-exit LZSS gate). **Max.** See investigation findings below.
- [ ] **Task 6 — Gen1-exit close-out** (README, checklist, ≥3-session zero-regression evidence). **xHigh.**
- [ ] **Task 7 — PhaseEnd_Phase7** (Gen1 synthesis, milestone gate). **Max · Tier 1.**

## Current task
**Task 5 — Loader cluster** (match-tractable non-switch / draft-hard). Then Task 2′ (LZSS), Task 6, Task 7.
NOTE: Gen1 exit needs ≥3 SESSIONS of green `make check` — cannot complete this session regardless.

## Per-session `make check` green log (≥3 sessions needed for the milestone)
- 2026-06-14 (session A): `make check` → `143dbb89… BYTE-IDENTICAL` ✓ — baseline restored + reproducibility fix, reports built, **38 real matches** (22 accessor leaves + ResourceGetCdLoc + LoaderResetReadState), build byte-identical throughout. [need ≥2 more sessions]

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
