# PhaseEnd — Phase 8: Finish the EXE — remaining PsyQ libraries + final harvest
**Date:** 2026-06-15 · **Project Version:** 1.8.0 · **Phase Status:** Complete · **Generation:** Gen2 (first phase)

> First Gen2 phase (the global count continues from Gen1's 1–7). The granular per-library trail
> (survey, per-integration addresses, the hard-case diagnostics) is preserved on-demand at
> **`phase-ends/logs/Phase8.md`** (R19 — NOT auto-loaded; consult only when researching a mechanism).
> Owner decisions (2026-06-15): progress metric = a **LINKED** category; exit bar = **full ceiling**
> (link every footprint-confirmed library; defer the rest as documented honest stubs).

## Build Log

**Files created/changed and complete — do not recreate:**

*Tooling (new, committed):*
- `tools/gen_lib_subsegs.py` — generate splat subseg lines + the `psyq_integrate` stub list for a
  MULTI-block library; block ends use the last object's `.text` **section size** (8-aligned), not the
  instruction count (the boundary gotcha). Used for libgte / the combined sound + apicard regions.
- `tools/make_snd_used.py` — build `.run/obj40/snd_used`: the **combined libspu+libsnd** curated dir
  (merge by vram, pick the byte-matching object per aliased address, exclude 4 unreconcilable addresses).
- `tools/make_apicard_used.py` — build `.run/obj40/apicard_used`: the **combined libapi+libcard** 800c2
  curated dir (C112 dedup, 0 exclusions).

*Tooling (modified):*
- `tools/progress.py` — **LINKED category** (owner decision Q1): INCLUDE_ASM stubs in integrated library
  subsegs counted as a distinct byte-identical bucket, separate from REAL and stubs. The linked-subseg set
  is parsed from the Makefile's `psyq_integrate` calls (single source of truth), resolving `$(VAR)` stub
  lists. Re-baselined libcd+libgs (340) → LINKED.

*Config / build:*
- `config/splat.us.exe.yaml` — resegmented for 8 libraries: `libetc`; `libgpu`(EXT+PRIM)+`800c`;
  `libmcrd1/2`+`800c2/800c3`; `libc2_1/2`; `libgte1..22`+`800b/800b_2..7`; the combined sound region
  `snd1..9`+`sgap*`; the combined apicard region `apicard1..4`+`800c2*`. (Game-code subseg names multiplied
  as regions were carved; all boundaries section-size-correct.)
- `Makefile` — per-library `LIB*_/SND_/APICARD_` vars + gated `psyq_integrate` calls (conditional on the
  SDK ELF dir → fresh-clone stub fallback) + each library's `-T <syms>` on the `ld` line. `LIBGTE_STUBS`/
  `SND_STUBS`/`APICARD_STUBS` vars hold the long stub lists.
- `src/*.c` — **committed stub records** for every new library subseg (`libetc`, `libgpu`, `libmcrd1/2`,
  `libc2_1/2`, `libgte1..22`, `snd1..9`, `apicard1..4`) and the new game-code fragments (`800c`, `800c2`,
  `800c3`, `800b`, `800b_2..7`, `sgap`, `sgap_2..8`); **9 game-code REAL matches** added to `src/800.c`
  (trivial D_* accessors). `src/800.c`/`800b.c`/`800b2.c` trimmed (matched C preserved).

*Docs / knowledge base:*
- `docs/psyq-worklist.md` — **new**: byte-confirmed footprint map (9 footprint libs / 3 skipped), the
  per-library recipe, the boundary gotcha, and the **deferred/excluded-objects table**.
- `docs/matching-cookbook.md` — **§9.6** "Scaling library linking to the whole EXE" (R16 flywheel): survey-
  first, `gen_lib_subsegs` + the section-size boundary, combined-region for interleaved libs, scattered-`.bss`
  cross-object exclusion-by-address, and the **clean-rebuild-to-verify** gotcha.
- `docs/SETUP.md` — the 3 new tools added to the inventory (R21). `docs/progress.md` — regenerated.
- `phase-ends/CURRENT_PHASE.md` → **`phase-ends/logs/Phase8.md`** (R19 archive). `phase-ends/PhaseEnd_Phase8.md` — this file.

**Local artifacts (gitignored / regenerable — do NOT recreate; a fresh clone redoes them):**
- `.run/obj40/{libgpu_used,snd_used,apicard_used}` — curated SDK-object dirs (regenerate: `psyq_build_libs.sh`
  then the `make_*_used.py` scripts / a 2-file `cp` for libgpu_used). Build is byte-identical without them.
- `build/psyq/*` — prepared objects + `*_externals.ld` (regenerated each `make build`). `.run/survey/*` — the placement survey.

**Tools/packages installed:** None (used the existing Phase-4/6 toolchain entirely).

**Verification results (literal):**
- **MILESTONE — full clean cycle, BOTH ways byte-identical:** `make clean && make extract && make build &&
  make check` → `build/us/SLUS_007.26` SHA1 `143dbb89f34491258bbc27810d0a12ec8b43a8dd` (a) **with** all 8
  newly-linked PsyQ libraries present, and (b) **without** any SDK ELF dir (the fresh-clone all-stubs
  fallback) — both `[ OK ] BYTE-IDENTICAL`.
- **`make report` (deterministic):** REAL **52** · LINKED **959** · NON_MATCHING 7 · empties 42 · stubs 1036
  · blobs 2. **byte-identical/matchable 1053/2096 = 50.24%** (was 20.31% at phase start with libcd+libgs only).
- **8 PsyQ libraries linked byte-identical** (object counts): libetc 5, libgpu 2 (EXT+PRIM), libmcrd 2,
  libc2 17, libgte 53/58, libspu+libsnd 60 (combined), libapi+libcard 22 (combined 800c2). Per-region
  byte-verified by `psyq_link_region` before wiring; each integration **dual byte-gated** (with + without).
- **0 NON_MATCHING in the default build** (the 7 are `#ifdef NON_MATCHING`-guarded) — G4 preserved.
- **3 libraries have zero footprint** (recorded skipped): libmath, libc (BFM links libc2), libsn.
- `git status`: only `config/`, `Makefile`, `tools/`, `src/`, `docs/`, `phase-ends/` tracked — **zero
  ROM-derived/generated bulk staged** (curated dirs + build/ + `.run/` gitignored).

**Milestone achieved:** The EXE rebuilds **byte-for-byte identical with AND without** all 8 newly-linked PsyQ
libraries (fresh-clone-safe), `make report` shows byte-identical coverage risen **20.31% → 50.24%** (LINKED
340 → 959, REAL 43 → 52), 0 NON_MATCHING in the default build, and every footprint library is linked or a
documented honest deferral — confirmed by Drew (gate 2).

**Next:** **Phase 9 — Binary-agnostic toolchain refactor** (Gen2 roadmap). Start by parameterizing the
single-binary tools (`psyq_*.py`, `progress/difficulty/dup_report.py`, the Makefile) by `--binary`/
`--text-vram`, proving the refactor a no-op via the EXE rebuilding SHA1 `143dbb89…`.

## Deviations
| Item | Plan | Actual | Reason |
|---|---|---|---|
| Integration order | ascending difficulty (libgpu→…→libgte) | **value-first** (libetc/gpu/mcrd/c2 → libgte → sound → apicard) | libcard/libapi turned out fiddliest (dense aliases); libgte/sound are highest-value and matched-C-free |
| Interleaved libs | one library per task | **combined-region integration** (libspu+libsnd as one; libapi+libcard as one) | the libs interleave object-by-object; two passes would tangle (each's objects span the other's gaps) |
| Multi-block resegment | (manual per the §9.5 pattern) | built **`gen_lib_subsegs.py`** (libgte=22, sound=9, apicard=4 blocks) | hand-editing ~50 subsegs is impractical/error-prone; the tool bakes in the section-size boundary |
| libgpu / sound completeness | link the whole library | **excluded scattered-`.bss` objects** (libgpu SYS.o; sound S_R/S_GRMDT/VM_F; + S_IH false-positive) | the §9.1 GS_001 class (cross-object form): `.bss`+offset refs the original linker scattered; honest stubs (P9) |
| libgte / libapi completeness | whole library | **5 libgte libgs-gap objects + libapi's 800c3 remnant DEFERRED** | low value vs the gsgap sub-split / extra region resegment; documented, byte-identical stubs |
| Harvest size | a modest bank | **9 trivial game-code accessors** (REAL 43→52) | "bank, don't exhaust"; more trivial leaves remain |
| Boundary discovery | (not anticipated) | **section-size boundary gotcha** found+fixed at libc2 (SETJMP.o `.text` 0x80 vs 0x78 ins) | a too-low boundary shifted the whole image; lesson → cookbook §9.6 + the tool |
| Verification | (incremental implied) | **clean-rebuild required** (an incremental build falsely diffed in libmcrd) | the incremental `psyq_integrate` `.ld` rewrite can go stale → R22 candidate |
| difficulty.md regen | regen in the harvest | **deferred** (sig-refresh needs the Ghidra server stopped) | next-session follow-up; not a milestone item |

## Commit Message
```
feat(phase-8): finish the EXE — 8 PsyQ libraries linked byte-identical + harvest (v1.8.0)

- 8 libraries linked byte-identical (libetc/libgpu/libmcrd/libc2/libgte/libspu+libsnd/
  libapi+libcard); byte-identical coverage 20.31% -> 50.24% (LINKED 340 -> 959)
- new tooling: gen_lib_subsegs.py (multi-block subseg generator, section-size boundaries),
  make_snd_used.py + make_apicard_used.py (combined-region curated dirs), progress.py LINKED
- combined-region integration for interleaved libs (libspu+libsnd, libapi+libcard); value-
  first order; scattered-.bss objects excluded as honest stubs (libgpu SYS.o, sound, GS_001)
- 9 game-code accessors harvested (REAL 43 -> 52); cookbook §9.6 + SETUP tool inventory
- MILESTONE: make clean && build && check -> 143dbb89 byte-identical WITH and WITHOUT all
  SDK objects (fresh-clone-safe); 0 NON_MATCHING in default build; deferrals documented
- worklog archived -> phase-ends/logs/Phase8.md (R19); bumps 1.7.0 -> 1.8.0
```

## Rules Added This Phase
| Rule | Reason |
|---|---|
| **R22 — Verify byte-matches from a CLEAN rebuild, never an incremental build.** A byte check (`make check` / SHA1) is trustworthy only after `make clean && make extract && make build`. The `psyq_integrate` step rewrites the linker script in place, so an *incremental* build after a source change can re-run it on an already-rewritten `.ld` and transiently mis-resolve a sibling library's externals — producing a **false** diff (or, in principle, a false pass). Extends G3/P9. | A Phase-8 harvest incrementally "diffed" in libmcrd; the identical source built byte-identical from a clean tree. Caught a verification-integrity hole that could otherwise mislead a match/no-match conclusion. |

*(Not elevated to rules — captured as cookbook §9.6 techniques: the section-size boundary rule, the combined-region pattern for interleaved libraries, scattered-`.bss` exclusion-by-address, survey-first. Owner decision recorded: library linking is reported as a distinct **LINKED** bucket, never folded into REAL — a P9 measurement-honesty practice, implemented in progress.py.)*

## PhaseEnd Changelog
**v1.7.0 → v1.8.0 — Phase 8 complete (first Gen2 phase).** The EXE is driven to its practical matching
ceiling: **8 more PsyQ libraries linked byte-identical** (libetc, libgpu, libmcrd, libc2, libgte, libspu,
libsnd, libapi, libcard), taking byte-identical-from-source coverage from **20.31% to 50.24%** (LINKED 340 →
959) — proven byte-identical **with and without** every SDK object (fresh-clone-safe). The phase's reusable
output: **`gen_lib_subsegs.py`** (mechanical multi-block resegmentation with section-size-correct
boundaries), the **combined-region** technique for interleaved libraries (`make_snd_used.py` /
`make_apicard_used.py`, alias dedup by byte-match + scattered-`.bss` exclusion-by-address), and the
**LINKED** progress metric (Makefile-sourced). A modest game-code harvest banked **9** trivial accessors
(REAL 43 → 52). Three zero-footprint libraries skipped (libmath/libc/libsn); a small set of scattered-`.bss`
objects and two low-value remnants (libgte's libgs-gap objects, libapi's 800c3 cluster) deferred as
documented honest stubs — none block the byte-identical build. One rule (R22 clean-rebuild verification).
Knowledge fed back (cookbook §9.6, R16). The EXE is now the fully-understood, half-from-source reference
that Gen2's binary-agnostic refactor (Phase 9), resident-blob (Phase 10), and overlays build on.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase8.md` (R19). The Phase-8 work is
committed (`commit:0030`→ this commit); **Drew pushes** (R6). Gen2 is underway — do NOT start Phase 9 here.
Start a **fresh session** (effort **Max**, plan mode) for **Phase 9 — Binary-agnostic toolchain refactor**
(a Tier-1 Phase-Start planning task). Keep this file forever.
