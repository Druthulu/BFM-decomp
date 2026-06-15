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
- **⚠️ PHASEEND AFTER LIBGS (Drew 2026-06-14):** do NOT write PhaseEnd_Phase7 / delete this CURRENT_PHASE.md until **libgs is done**. This file holds the libgs placement + working notes (see the session-E "libgs placement" block) and must stay intact so libgs work can resume. Sequence: LZSS → libgs → Task 6 close-out → (only then) Task 7 PhaseEnd. Task graph enforces it (#8 blocked by #9).

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
- [x] **Task 2′ — Focused LZSS + rodata-island sub-project** ✓ DONE (session F, 2026-06-15). **LzssDecodeSector MATCHED byte-for-byte** (asm-differ score 0; `make clean && make extract && make build && make check` → `143dbb89… BYTE-IDENTICAL`). The Gen1-exit LZSS gate is satisfied. **43 real matches** (42 + LZSS). The NON_MATCHING guard is DROPPED — the C is the default build. Close required 5 load-bearing constructs (all documented in src/800.c + cookbook §10): (A) decoupled `nh` high-byte var + `(code&0xFF)|(nh<<8)` operand order [local-alloc combine_regs]; (B) `result` set in save predecessors [reorg fill_simple_delay_slots]; (B/state-2) explicit `register $2` local + early read-only input-asm pin [sched list-order]; (B3) NO switch `default`/trailing return → state≥5 reuses the `sltiu` result; (§5a) the zero-byte cross-jump barrier. The surgical rodata carve + ld_interleave place gcc's generated jtbl at 0x80072A38 (links byte-identical). Cookbook §10 added (the reusable regalloc/schedule-tail idioms + the floor-free `.text` metric); §5a cross-linked.
- [ ] **Task 6 — Gen1-exit close-out** (README, checklist, ≥3-session zero-regression evidence). **xHigh.**
- [ ] **Task 7 — PhaseEnd_Phase7** (Gen1 synthesis, milestone gate). **Max · Tier 1.**

## Current task
**LZSS DONE (session F, 2026-06-15) — the Gen1-exit LZSS gate is SATISFIED.** `LzssDecodeSector` matches
byte-for-byte (asm-differ score 0; full clean build `143dbb89… BYTE-IDENTICAL`); the `#ifdef NON_MATCHING`
guard is dropped — the C is the default build. 43 real matches. Full close detail in the Task 2′ checklist
entry above + the 5 LOAD-BEARING comments in `src/800.c` + cookbook §10.
- ✅ **libcd wired into the byte-identical build** (session D) — 58 SDK funcs.
- ✅ **LZSS matched** (session F) — surgical rodata carve + ld_interleave place gcc's generated switch jtbl at
  0x80072A38 (links byte-identical); the §5a cross-jump barrier + 4 regalloc/schedule idioms (§10) closed it.
  Method: §3a web-research ground-truthed all levers against the pinned gcc-2.7.2 source; a floor-free `.text`
  metric (objcopy `--only-section=.text` + `cmp`, bypasses the rodata/jtbl floor) measured the close; the
  permuter could NOT (score floor + random divergence).
- ✅ **libgs BLOCK 6 integrated byte-identical** (session F, Drew: "block 6 alone first, then the integration").
  **16 contiguous libgs objects → 26 SDK functions banked** (vram 0x80053AF8–0x80057928), `make clean/extract/
  build/check` → `143dbb89… BYTE-IDENTICAL`, reproducible; fresh-clone stub fallback verified; zero spurious
  warnings. Mechanism (the libcd §9.3 pattern): resegment 800b → [800b pre][libgs6][800b2 post]; regenerate the
  3 split src files; `psyq_integrate libgs6`. **Three new fixes (all in this commit):**
  - **splat instability the resegment exposed:** shrinking 800b shifted spimdisasm's auto-detected boundaries.
    Declared `GsMulCoord2/3` (real MATRIX.o funcs, verified via the PsyQ object — R15, Ghidra-mirror pending);
    and carved the §8 data descriptor table `[0x53198,data,53198]` (boot.c's `D_80062998` was being shadowed by
    a mis-detected `func_80062998`). ld_interleave FRONT_DATA → `53198.data.o`.
  - **psyq_integrate multi-library support:** NOLOAD section names namespaced per-library (`.nl_<tag>_*`) so the
    2nd integration's NOLOAD placement isn't skipped (was discarding OBJT3 .rdata/.bss); trial-link now includes
    already-emitted sibling `*_externals.ld` (kills the "31 UNRESOLVED" false alarm — they're libcd's externals);
    NOLOAD lines globally re-sorted by vram across libraries (kills "dot moved backwards").
  - **reproducibility:** `tools/make_libgs_block6.sh` regenerates the curated 16-object dir (disambiguated:
    GS_131/137 not RVWUNIT/RVWLUNIT, PRESET3/OBJT3 not PRESET2/OBJT2).
- ▶ **NEXT — full libgs integration** (the other 5 blocks: ~37 more SDK funcs; **GS_001 excluded**, scattered
  `.bss` commons §9.1). Drew pre-approved ("then the integration"). Same pattern, now de-risked (the splat-
  instability + multi-lib fixes are in). Then Task 6 close-out, Task 7 PhaseEnd (PhaseEnd gated on libgs per Drew).
NOTE: Gen1 exit needs ≥3 SESSIONS of green `make check` — **satisfied** (A, B, C, D, E, +F); Tasks 6/7 pending.

### Island ownership map (session E — the decisive finding)
Rodata island 0x80072A38–0x80074750, 102 jtbls total (~52 in-island). By owner segment:
- **0x80072A38–0x800734F4 (~35 jtbls): 800-segment GAME code** (targets 0x80018xxx–0x80039xxx; incl.
  `jtbl_80072A38`=LZSS first entry, and S_SCA/SR_SV which resolve to `asm/nonmatchings/800/`). **MIGRATE these.**
- **0x800737CC–0x800746B0 (~17 jtbls): 800b + LIBRARY** — BIOS(libcd, already integrated), GS_123/PRESET/
  PRESET2/OBJT/OBJT2(libgs), PRNT(libc2), LIBMCRD. **STAY RAW** (untouched flat data → byte-identical).
- **+24 root cause = 6 library jtbls, ALL in 800b** (PRESET_OBJ_744/8FC, PRESET2_OBJ_4D8/A88, OBJT2_OBJ_614, PRNT_OBJ_24C).
  LZSS+game jtbls are in 800; the only libgs object in 800 (GS_013, 0x8003D40C) has **no jtbl** → 800-only migration has no library TU → no +24.

### libgs placement (session E — preserved for the BONUS task #9)
36/201 located; byte-test disambiguation: **PRESET3** (not PRESET2) @0x80055D40, **OBJT3** (not OBJT2) @0x80057094
(losers have a spurious .data + .text mismatch); GS_131≡RVWUNIT, GS_137≡RVWLUNIT are .text-identical aliases (keep GS_*).
GS_106 @0x80053308 fills a gap (narrow-window). GS_013 @0x8003D40C = far outlier in 800 (6 ins). 4 ambiguous
(GS_101/102/124/125) don't fit gaps → not linked. Main block 0x80051804–0x80057928 (800b), ~4 sub-blocks; gaps 96/48/304 B.
Patched `tools/psyq_identify.py` to skip data-only objects (no .text, e.g. GLOBAL.o). PRESET3/OBJT3 .rdata land in-island (0x80073c98/0x80073ee8).
- **libgs BYTE-VERIFIED (session E):** curated `.run/obj40/libgs_used/` (31 objects). `psyq_link_region … --emit .run/libgs_region`
  → **31/32 byte-identical**, 0 conflicts, 69 externals; `.run/libgs_region.{ld,syms}` emitted. Confirms BFM links real
  PsyQ libgs 4.0 objects byte-for-byte. **GS_001 EXCLUDED** (known-issue: psyq-obj-parser packs scattered PSD* commons
  into `.bss` referenced via `.bss`+offset; 35 words differ at the global-zeroing run — needs per-symbol .bss resolution,
  cookbook §9.1 hard case). Block structure: **6 contiguous blocks + 5 gaps** (80/48/1536[GS_001]/48/304 B, all non-libgs
  → stay stubs). REMAINING (mechanical): resegment splat 800b into the 6 blocks + 5 gap stubs (~13 subsegs) + split_src +
  wire `psyq_integrate` (6 block stubs) → byte-identical → banks ~63 SDK funcs. Simpler first win = block 6 alone (16 objs
  incl. PRESET3/OBJT3) as [pre][libgs6][post] → ~35 funcs. Deferred at session-E end (long session); clean continuation.

## Per-session `make check` green log (≥3 sessions needed for the milestone)
- 2026-06-14 (session A): `make check` → `143dbb89… BYTE-IDENTICAL` ✓ — baseline restored + reproducibility fix, reports built, **38 real matches** (22 accessor leaves + ResourceGetCdLoc + LoaderResetReadState), build byte-identical throughout. [need ≥2 more sessions]
- 2026-06-14 (session B): `make check` → `143dbb89… BYTE-IDENTICAL` ✓ — **per-file -O0 split mechanism** (src/boot.c + Makefile per-file flags); **4 real matches** (GameModeDispatch, DebugMenuHandler, CdQueueBusy, CdReadRequest) → **42 real**; **PsyQ libcd.h infra** (CdlLOC/CdlFILE + 4 named symbols, unlocks the loader cluster); **LoaderInitFileTable + ResourceLoadStateMachine NON_MATCHING-drafted** (→ 4 NM) — **Task 5 non-jtbl loaders COMPLETE** (6 matched + 2 drafted); report tooling fixed (multi-file); cookbook §6/§7/T4. Build byte-identical throughout. [need ≥1 more session]
- 2026-06-15 (session C): `make check` → `143dbb89… BYTE-IDENTICAL` ✓ (full `clean && extract && build`, restored after the Task-2′ experiments). **≥3-session bar MET.** This session: fully diagnosed + built the **rodata-island mechanism** (works); root-caused the +24; **proved the PsyQ-library-linking GO** (see below). No new matches (architectural session). Build green at start and after restore.
- 2026-06-14 (session D): `make clean && make extract && make build && make check` → `143dbb89… BYTE-IDENTICAL` ✓ — **libcd LINKED INTO THE BUILD** (Drew-approved push-through). The first real PsyQ library is now sourced from real SDK objects in the byte-identical build: **58 libcd SDK functions** linked (not stubs), replacing the libcd-region asm stubs. Idempotent; Makefile-automated; conditional (fresh clone w/o `tools/psyq/` builds via stubs). New committed tooling: `tools/psyq_link.py` (per-object byte-link engine — recovers externals from resolved relocs, weakens psyq-obj-parser's mislabelled `.bss` commons), `psyq_link_lib.py` (whole-lib verify, 18/18 libcd), `psyq_link_region.py` (region link via **NOLOAD** = no data carving), `psyq_integrate.py` (build wiring: splat resegment + .ld swap + external resolution), `split_src_region.py` (H5-safe src split). Cookbook §9.1/9.2/9.3 + R16. **No data carving** (NOLOAD data placement; flat data subseg unchanged). Build green throughout.
- 2026-06-15 (session E): `make clean && make extract && make build && make check` → `143dbb89… BYTE-IDENTICAL` ✓ — start-of-session baseline + after the **LZSS surgical rodata carve** (jtbl_80072A38 migrated + sandwiched) + LZSS C **NON_MATCHING-guarded** (default build = stub). **≥3-session bar already MET (A/B/C/D); E is margin.** Findings: lean LZSS path proven (no libgs needed for it); LZSS C structurally matches (111/122) but blocked on a gcc cross-jump-merge hard-tail (see LZSS block above); libgs placement+disambiguation done (bonus, task #9, deferred per Drew until before PhaseEnd).
- 2026-06-15 (session F): `make clean && make extract && make build && make check` → `143dbb89… BYTE-IDENTICAL` ✓ — TWO milestones. **(1) LZSS MATCHED byte-for-byte** (asm-differ score 0; C compiled in, NON_MATCHING guard dropped). Closed the session-E ~4 regalloc/scheduling residuals via §3a web-research (ground-truthed against pinned gcc-2.7.2 `reorg.c`/`jump.c`/`local-alloc.c`) + a floor-free `.text` object metric: decoupled high-byte var + OR operand order (residual A); `result`-in-predecessor + explicit-`$2`-local-with-early-pin (residual B); no-`default` sltiu-reuse (residual B3); §5a barrier retained. **43 real matches; Gen1-exit LZSS gate SATISFIED.** Cookbook §10. **(2) libgs BLOCK 6 integrated** (16 objects / 26 SDK funcs byte-identical; the libcd §9.3 pattern). Fixed a resegment-triggered spimdisasm boundary instability (declared GsMulCoord2/3; carved the §8 data table `[0x53198,data]`) + made psyq_integrate multi-library-safe (per-lib NOLOAD namespacing + global sort; sibling externals in the trial); `tools/make_libgs_block6.sh` for reproducibility; cookbook §9.4. Build byte-identical with OR without the SDK objects; fresh-clone stub fallback verified. Changed: `src/800.c`, `config/{splat.us.exe.yaml,symbols.us.txt}`, `Makefile`, `tools/{psyq_integrate.py,ld_interleave.py,make_libgs_block6.sh}`, `docs/matching-cookbook.md` (zero generated/ROM bulk staged). **Tasks: full libgs → 6 → 7 remain** (PhaseEnd gated on libgs per Drew).

---

## Rodata-island foundation — RESOLVED end-to-end (session C, 2026-06-15)
The mechanism now WORKS; only the +24 (a known file-split/alignment artifact) blocks full byte-identity, and
the PsyQ-lib pivot (below) is the chosen fix. Experimental configs saved: `.run/{splat.island.yaml,
symbols.island.txt,Makefile.island,800.c.fresh-throwaway}`; new committed tool `tools/ld_interleave.py`.
**Proven mechanism (3 parts, all validated this session):**
1. **Migration** — dotted `.rodata` sibling named `800` (`[0x63238, .rodata, 800]`) → spimdisasm migrates all
   50 jtbls + single-ref consts into their owning `asm/nonmatchings/800/<fn>.s` (99 .s got `.section .rodata`,
   `.L`-refs resolve intra-object). Multi-ref consts → 70 `INCLUDE_RODATA` lines (needs a FRESH `800.c`; for the
   PERMANENT file, surgically INSERT those 70 lines into the curated 800.c — do NOT regen-fresh, it drops
   comments/H5). All 301 jtbl targets ∈ the `800` text seg (none in `boot`), so the single sibling is correct.
2. **Placement** — `tools/ld_interleave.py` (wired into `make extract`) rewrites splat's section-major `.main`
   into the real `.data→.rodata→.data` sandwich order (text, front-data@0x800629DC, rodata@0x80072A38,
   tail-data@0x80074750). Front/tail split by object basename. rodata + both data sizes came out **byte-exact**.
3. **Data-in-text carve** — the 68-B descriptor table at 0x80062998–0x800629DC (ptrs to start/D_80062998/
   D_80074778) must be its own `[0x53198, data, 53198]` subseg or the jumptable analyzer mis-extends the last
   code function across it.
**The ONLY residual = +24 (ROOT-CAUSED):** 6× `.align 3` jumptable padding nops injected into `.text` (at
PRESET_OBJ_744, PRESET_OBJ_8FC, PRESET2_OBJ_4D8, PRESET2_OBJ_A88, OBJT2_OBJ_614, PRNT_OBJ_24C). GCC 8-aligns
each switch jtbl, but the original built these as SEPARATE translation units; our single 800.o concatenation
adds padding the original lacked. spimdisasm itself printed **8 file-split suggestions** (rodata 0x6324C,
0x63388, 0x633FC, 0x63920, 0x63C94, 0x64420, 0x64AB4, 0x64CA0). Canonical fix = per-file split — OR the PsyQ-lib
pivot below (most of these are library code).

## PsyQ-library-linking SPIKE — GO PROVEN (session C, the chosen +24 fix + free SDK code)
**Finding:** BFM's PsyQ library functions are **byte-identical to the real PsyQ SDK objects** → link them
directly (byte-exact) instead of hand-decompiling, which ALSO gives each library `.o` correct per-object
alignment (dissolving the library-half of the +24). Validated: `CdPosToInt` (32 instrs) + `CdIntToPos` (65)
EXACT vs PsyQ **4.7** `libcd.a`; `CdPosToInt` also in **4.0** `LIBCD.LIB`; `PRESET_OBJ_108` (a +24 culprit) is
in **4.0 `LIBGS.LIB`** → library code, not game. (Raw-byte lib search has false-negatives on relocated funcs,
e.g. `_spu_FsetPCR`/`OBJT2`/`PRNT` "missed" — needs the real ELF-link test to classify those.)
**Assets staged (gitignored `tools/psyq/`):** `psyq-obj-parser` (decompme prebuilt, works on `.OBJ`; rejects
`.LIB` archives — needs splitting); `psyq4.0/` (4.0 tools: CC1PSX/ASPSX/PSYLIB/…); `conv47/` (4.7 pre-converted
ELF `.a` — quick reference); **`lib40/*.LIB`** = the 20 PsyQ **4.0 USA** libraries (DTL-S2002 R2.0, BFM's exact
version) extracted from the redump via our `tools/bfm_extract/iso9660.py` walker. Footprint in BFM: ~350 funcs
(libsnd 131, libapi/gs 69+, libmcrd 63, libsn 37, libcd 28, libspu 21, …) of 2050 matchable.
**Integration pipeline — BUILT + PROVEN end-to-end (session C):**
- `tools/psyq_lib_split.py` (committed) — splits a `LIB\x01` archive into its member `.OBJ` (locates each
  member header by the invariant `u32@(header+12) == LNK_offset − header`). LIBCD → 25 objects ✓.
- `tools/psyq_build_libs.sh` (committed) — `.LIB → .OBJ → psyq-obj-parser → ELF .o → ar` per lib. **Built all
  14 BFM libs → `tools/psyq/lib40_elf/*.a`** (gitignored): LIBCD 25, LIBGS 201, LIBSPU 129, LIBSND 163,
  LIBMCRD 2, LIBSN 51, LIBAPI 90, LIBETC 7, LIBGTE 381, LIBGPU 12, LIBMATH 48, LIBCARD 18, LIBC 56, LIBC2 46.
- **Byte-match PROVEN at object level:** in libcd `SYS.o`, leaves `CdPosToInt`/`CdIntToPos` are EXACT; relocated
  funcs (`CdComstr` …) differ ONLY at their relocation sites → link byte-exact once relocs resolve to BFM
  symbol addrs. So every step (split, convert, leaf-match, reloc-resolve) is validated.

**FULL OBJECT LINK — PROVEN BYTE-IDENTICAL (session C):** libcd `SYS.o` (483 instrs, the full TU: leaves +
relocated funcs + 21 externals + internal .rdata/.data) links **byte-for-byte identical to BFM**. The pipeline
+ the 3 last pieces:
- **Identify placement** (`tools/psyq_identify.py`, committed) — relocation-masked search locates each object's
  `.text` in BFM. libcd: **18/25 objects found, CONTIGUOUS** at 0x80043088–0x80046D1C in object order (the 7
  unused — CDPLAY, C_012–015… — BFM doesn't link). So per-library placement = link the used objects in order at
  the region base; addresses are read off, not guessed.
- **Recover externals from BFM** — symbols the object references but doesn't define (e.g. libcd's `CD_pos`,
  `CD_com`, `DMACallback`) are NOT in symbols.us.txt, but their addresses are encoded in the EXE's already-
  RESOLVED relocations: parse the object's reloc records, read BFM at each site, reconstruct (R_MIPS_26 →
  target; HI16/LO16 pair → addr). Recovered all 21 for SYS.o. (Feeds symbols.us.txt over time.)
- **Alignment fix** — psyq-obj-parser sets `.text/.rdata/.data` align=2**3 (8); the original placed them
  4-aligned, so an 8-align bumps them +4. `objcopy --set-section-alignment .rdata=4 .data=4` before linking →
  exact. (The +4 mismatch is the tell.)
- **Link recipe:** `ld -T <script placing .text@<objaddr> .rdata@<island> .data@<addr>> --defsym <recovered…>
  obj.o` → objcopy .text → byte-compare. Proven on SYS.o.

**REMAINING (replication + wiring, NEXT session, Task #5):** generalize the SYS.o recipe to all used objects
per library (identify region → recover externals → set-align → place sections in order → link), then wire into
the build: drop the linked functions' INCLUDE_ASM + carve their raw data, add the lib objects to the link via a
generated `.ld` fragment. ~350 SDK funcs become byte-exact + the library-region jtbl alignment resolves. GAME
switches + **LZSS** (jtbl_80072A38 = island's first entry, before any misalignment) take the proven
migration+ld_interleave path above.

## Blockers / open items
- `.LIB`→`.OBJ` splitter (LIB\x01 format) — the gate for the lib-linking integration.
- Which 4.x version matches each BFM lib object best (4.0 USA primary; BFM mixes 4.0+4.2 stamps, so some objects
  may need 4.2/4.3 libs — determine per-lib during integration via the ELF-link byte test).
- LZSS via the proven migration+ld_interleave path (independent of the lib pivot).

## Notes
- **Rule candidate (PhaseEnd, Drew-flagged session E):** web-research the compiler internals (real compiler
  source e.g. `pmret/gcc-papermario`) + decomp community for **compiler-quirk residuals** (cross-jump,
  scheduling, regalloc) — a proven escalation tier above the permuter, below decomp.me. Found the LZSS
  cross-jump barrier. Captured in cookbook §3a/§5a + memory `web-research-compiler-quirks`.
- **Session-E checkpoint commit:** Drew directed a checkpoint commit (deviates from R8's strict
  one-commit-at-phase-end; consistent with the session A–D checkpoint commits in the git log). Commit local in
  WSL (no push, no Co-Authored-By per R5); Drew pushes via GitHub Desktop (R6).
- `.run/merge_matches.py` = regenerate-800.c + re-apply-matches helper. **H5 caveat:** regen-fresh drops
  file-level/stub comments; for the permanent 800.c, surgically insert the 70 INCLUDE_RODATA lines instead.
- `tools/ld_interleave.py` (committed) = the `.data→.rodata→.data` linker-script interleaver.
