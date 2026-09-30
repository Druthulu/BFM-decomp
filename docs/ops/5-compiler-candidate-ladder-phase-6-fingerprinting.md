## §5 Compiler candidate ladder (Phase 6 fingerprinting)

### §5.1 The evidence

Locally verified on the extracted US EXE (DetectPsyQ-style masked-pattern scan): **13 pattern hits, of which 12 are genuine `Ps` library stamps** — 9× PsyQ **4.0** (libnums 2, 3, 4, 6, 7, 8, 9, 17, 24), 1× **4.0.1x** (libnum 16), 1× **4.2** (libnum 0), 1× **4.2.1x** (libnum 12); the remaining hit (ver 0x0000 at vaddr 0x8005CD20) is a code false positive. **Identified (P31 S78, byte-placed via the psx loader's per-version signature sets, `~/ghidra_12.1_PUBLIC/Ghidra/Extensions/ghidra_psx_ldr/data/psyq/<ver>/<LIB>.LIB.json`):** the 4.2 stamp at `0x8005CE48` is **LIBAPI 4.2 `C114.OBJ` (`_96_remove`)** at the head of the `800c3` band, and the 4.2.1x stamp at `0x80072954` sits in front of **LIBPAD 4.2.1's** `.data` (the callback tables `D_8007295C..D_800729D8`); the band `0x8005CF68–0x8005FC68` is COUNTER (libapi) · PADENTRY · PADMAIN · L02/L03 · PADCMD · PADIF · PADPORTD · PADSEQD · WAITRC2 (libpad), and `FIRST`/`PAD`/`PATCH`/`CHCLRPAD` (libapi 4.2) sit in `800c2`. See `docs/psyq-worklist.md` "S78". A raw-track scan during research reported 16 hits with extra spurious 4.0 stamps — the extracted-EXE scan is ground truth, and ghidra_psx_ldr's detection at import is the final word (ledger #12). Library copyright string `(c) 1993-1997 Sony` corroborates the era. Conclusion: BFM links **PsyQ 4.0 libraries with 4.2 library updates** ⇒ the GCC 2.7.2/SN32-era toolchain — **NOT sotn's GCC 2.6.3** (the starting-point doc's claim is corrected). PsyQ 4.2 was a library-only refresh: no 4.2 toolchain disc exists (absent from redump/arthus sets), so 4.2 stamps still mean the 4.0/4.1 toolchain — but the 4.2 RUNTIME LIBRARY itself survives: archive.org's `play-station-programmer-tool-runtime-library-version-4.2.7z` (P31 S79 task #13, `tools/psyq/lib42/` + the 1998-02-26 libpad-4.2.1 patch in `lib421/`), and its LIBPAD 4.2.1 / LIBAPI 4.2 objects link the whole band byte-identical (46/46) — the stamps are now backed by the real objects, not just signatures.

Caveat: `Ps` stamps date the **linked libraries**, not the compiler that built game code — Square mixed cc1 builds within one EXE (see §5.5). The final triple is pinned only by Phase-6 fingerprinting.

### §5.2 SDK → GCC → ASPSX mapping (verified from the actual binaries in mkst/esa psyq-binaries tarballs)

| PsyQ SDK | CC1PSX identifies as | ASPSX | old-gcc 0.17 artifact | maspsx flag |
|---|---|---|---|---|
| 3.3 | GNU C 2.6.0 [AL 1.1, MM 40] | 2.21 | `gcc-2.6.0-psx` | `--aspsx-version=2.21` |
| 3.5 | GNU C 2.6.0 (same binary) | 2.34 | `gcc-2.6.0-psx` | `--aspsx-version=2.34` |
| 3.6 | GNU C 2.7.2.SN.1 | 2.34 | `gcc-2.7.2` (vanilla-ish) | `--aspsx-version=2.34` |
| **4.0** | **GNU C 2.7.2.SN32.3.7.0002** | **2.56** | **`gcc-2.7.2-psx` / `gcc-2.7.2-cdk`** | **`--aspsx-version=2.56`** |
| **4.1** | **cygnus-2.7.2-970404 SN32.3.7.0004 (SonyPSX)** | **2.67** | **`gcc-2.7.2-cdk`** (exact base) | **`--aspsx-version=2.67`** |
| 4.2 | *library-only release — no toolchain exists* | n/a | use 4.0/4.1 row | use 4.0/4.1 row |
| 4.3 | GNU C 2.8.0 SN32 Build 4.0.0007 (community shorthand "2.8.1" is wrong — that's 4.4) | 2.77 | `gcc-2.8.0-psx` | `--aspsx-version=2.77` |
| 4.4 | GNU C 2.8.1 SN32 BUILD 4.0.0010 | 2.79 | `gcc-2.8.1-psx` | `--aspsx-version=2.79` |
| 4.5 | egcs-2.91.66 (egcs-1.1.2) | 2.81 | `gcc-2.91.66-psx` | `--aspsx-version=2.81` |
| 4.6 | GNU C 2.95.2 BUILD 4.0.0030 | 2.86 | `gcc-2.95.2-psx` | `--aspsx-version=2.86` |

> ⚠️ **`--aspsx-version` MUST always be passed explicitly.** maspsx with no flag is *not* "latest behavior" — the dataclass defaults approximate ASPSX ~2.3x (`expand_li=True`, `sltu_at=True`, `nop_mflo_mfhi=True`). Behavior thresholds: `expand_li` off ≥2.50; `sltu_at` off ≥2.60; `$gp` symbol+offset ≥2.70; `$gp` for `la` ≥2.80. The observable 2.56 vs 2.67 tell: "$at for `sltu < 0`" present at 2.56, gone at 2.67, and %hi/%lo support arrives at 2.67 — decide on functions with unsigned comparisons / li/sltu idioms.

### §5.3 -G0 vs -G8

Read `gp_value` from the SLUS_007.26 EXE header and check for `$gp`-relative loads in Ghidra **before** fixing the flag (**RESOLVED Phase 5 — see the ✅ verdict below: -G0**). Precedent: FF7 used `-G 0`; Xenogears used `-G8` for game code. maspsx forces `-G0` to GNU `as` by default — non-zero `$gp` needs `-G8` passed to maspsx and a look at `--dont-force-G0`.

**✅ RESOLVED (Phase 5, 2026-06-14): -G0.** The header `gp_value` is 0, and the splat disassembly has **zero `($gp)` base-register accesses and zero `%gp_rel` relocations** (the 4 `$gp` mentions are crt0 register setup) — no small-data/$gp-relative addressing, i.e. the FF7-style `-G0`. The linker's `_gp=0x80074750` (splat's computed Initial-GP) is therefore inert, and the all-asm build is byte-identical. Carry `-G0` into Phase-6 cc1 fingerprinting (swap only if asm-differ ever shows otherwise).

### §5.4 Candidate ladder (try in this order)

> **✅ PINNED (Phase 6, 2026-06-14) — rung 1 is the answer (G8).** Triple:
> `tools/bin/gcc-2.7.2-psx/cc1 -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker`
> → `maspsx --aspsx-version=2.56 **--expand-div**` → `mipsel-as -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0`.
> Pinned in the `Makefile` (`CC1FLAGS` / `ASPSX_VERSION` / `MASPSX_FLAGS`). Evidence: byte-exact on `func_80018F20`
> (the `sltiu` range-check probe) + instruction-identical across 2 more idiom classes (division via `--expand-div`;
> memset). **`--expand-div` is required** for any div/rem (without it maspsx emits a bare `divu` with no zero-check
> and div functions never match). **psx≈cdk and 2.56≈2.67 are byte-equivalent** on functions lacking the
> discriminating idioms, so rungs 2–5 went unused (kept below for per-module-mixing escalation, §5.5). Reusable
> codegen findings: `docs/matching-cookbook.md`.

1. **`gcc-2.7.2-psx` cc1 + `--aspsx-version=2.56`**, flags `-O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker` (FF7 style; swap to -G8 if §5.3 says so).
2. Same cc1 + `--aspsx-version=2.67` (PsyQ 4.1 assembler era).
3. **`gcc-2.7.2-cdk`** (cygnus-2.7.2-970404, the exact CC1PSX 4.0/4.1 base) × 2.56, then × 2.67.
4. Real PsyQ 4.0/4.1 `CC1PSX.EXE` + `ASPSX.EXE` (under Wine, §4.8) + psyq-obj-parser — byte-exact arbitration when maspsx emulation is in question.
5. Only if diffs show GCC 2.8-style codegen: `gcc-2.8.0-psx` + 2.77 (unlikely — the JP master predates PsyQ 4.3-era adoption).

**Library-code preset** (for PsyQ SDK functions linked into the EXE): `--aspsx-version=2.56 --expand-div`, `-O3 -G0` — the Xenogears precedent, consistent with our 4.0 lib stamps.

### §5.5 Per-module mixing warning

Xenogears (the closest comparable: Square US, Oct 1998) mixes **three** cc1 builds in one EXE (`gcc-2.7.2-psx`, `gcc-2.6.0-psx`, `gcc-2.7.2-cdk`) with different maspsx flags per module. Expect per-module variation in BFM: fingerprint **several modules independently** (3–5 medium leaf functions each), and design the build config for per-file compiler/flag overrides from day one (sotn does this with `//!` comments in line 1–2 of a .c file; Xenogears with `gears.toml` presets).

Reference repos for build-config patterns: `https://github.com/ladysilverberg/xenogears-decomp` (gears.toml presets), `https://github.com/Drahsid/ffvii` (Makefile).

### §5.6 Compiler-quirk research reference clones (Phase 18, 2026-06-20)

Phase 18 (raise the match-% ceiling by understanding gcc-2.7.2's blocking codegen quirks) reads the **real compiler source** and mines a peer decomp built with **our exact compiler**. Cloned shallow, gitignored under `/tools/reference/` (re-clonable — SHAs pinned here for reproducibility, R20/R21):

| Repo | Purpose | Path | Branch | SHA (pinned) |
|---|---|---|---|---|
| `pmret/gcc-papermario` | ⚠️ **actually gcc 2.8.1, NOT 2.7.2** (behavioral diff: 2.8.1 `&&0`-disables biv-elim paths ENABLED in real 2.7.2 — caught Phase 23). OK for passes where 2.8.1≡2.7.2, but **cite `gcc-2.7.2/` below for accuracy**. | `tools/reference/gcc-papermario` | `master` | `a6afc2afbcaf6682930141d526afdc95801fc2fd` |
| **vanilla gcc-2.7.2** (the REAL source of our pinned cc1) | authoritative source for the codegen map (cookbook §31/§34 + `docs/gcc-2.7.2-map/`): `sched.c`/`reorg.c` (scheduling), `local-alloc.c`/`global.c`/`reload1.c` (regalloc), `loop.c` (IV/hoist), `cse.c`/`expr.c` (CSE/aliasing). Staged Phase 23; **completed Phase 24 T5** (18 `.c` files — +toplev.c/function.c/flow.c/… from the FSF tarball; sched.c/loop.c/mips.c verified byte-identical to vanilla → §34's `local-alloc.c:1441` 3-qty-sort-bug citation is sound). **P31 T2: +6 files** — `calls.c` + `caller-save.c` (both cited by §172's frame-residue producer model, previously MISSING) + `integrate.c`/`optabs.c`/`varasm.c`/`recog.c` — from GNU ftp `gcc-2.7.2.tar.gz`, sha256 `7cd8bce5c3aeec59a72ecc2d3d5123864a817b14cdbd0680b1a969c3bccc5da5`. | `tools/reference/gcc-2.7.2` | GNU 2.7.2 release | (re-fetch: GNU ftp `gcc-2.7.2.tar.gz`; tarball kept at `.run/t7/fable/gcc-2.7.2.tar.gz`) |
| `ladysilverberg/xenogears-decomp` | Square, Oct 1998, **gcc-2.7.2-psx + -cdk** (our exact compiler); mine transferable quirk idioms + `gears.toml` per-module presets | `tools/reference/xenogears-decomp` | `main` | `f27c0768b1ad10812cec776cadadb85ae70aadee` |
| **PsyQ Runtime Library 4.2 + the libpad 4.2.1 patch** (P31 S79, 2026-09-04, task #13) | archive.org item `play-station-programmer-tool-runtime-library-version-4.2.7z` (383 KB) → tracked as `tools/psyq/PlayStation_Programmer_Tool_-_Runtime_Library_Version_4.2.7z` (sha256 in `CHECKSUMS.sha256`) → `tools/psyq/lib42/` (the 4.2 LIBs, 1998-01-21) + `tools/psyq/lib421/` (`LIB/42PATCH/J421PD.ZIP` = SCE R&D "libpad.lib 4.2.1 for the DUAL SHOCK", 1998-02-26: LIBPAD.LIB 4.2.1 + LIBAPI.LIB 4.2 + LIBPAD.H/LIBAPI.H/KERNEL.H) → ELF via `psyq_lib_split.py` + `psyq-obj-parser` into `.run/obj42/{libpad421,libapi42}`. **This is the EXE's libpad/libapi**: 7 + 39 objects place and link byte-identical (`psyq_link.py` PASS ×46) — the whole 0x8005CE18–0x8005FC68 band + the apicard-region libapi pieces. The 4.2.1 headers are the band's prototype oracle | `tools/psyq/lib42/`, `lib421/` (gitignored, regenerable) | — | — |
| **PsyQ 4.6 libraries** (P31 S78, 2026-09-04) | `Psy-Q_46.zip` (psx.arthus.net; sha256 in `tools/psyq_CHECKSUMS.sha256`) → `tools/psyq/lib46/*.LIB` (23 libs) → ELF via `psyq_lib_split.py` + `psyq-obj-parser` into `.run/obj46/<lib>/`; placed against the EXE (`.run/survey46/`). Only `PDMAIINI.o` is byte-identical in the libpad-4.2.1 band | `tools/psyq/lib46/` (gitignored, sha-recorded) | — | — |
| **PsyQ 4.5 toolkit** (P31 S78) | `PSYQ_SDevTC_v4.5.zip` (psx.arthus.net; 7 split zips, unpacked on demand; sha-recorded) | `tools/psyq/` | — | — |
| **PsyQ 4.0 dev-CD SDK tree** (P31 T2, 2026-08-14) | the SDK **sample C source** (400 `.c`: 373 in `PSX/SAMPLE/` — CD/GRAPHICS/SOUND/MODULE/CMPLR/…) = the canonical source shapes era game code was written from → drafting-agent style priors, esp. for main (see `docs/psyq-sample-idioms.md`). Also `GNU/SNGNUVER.TXT` — SN's build history (`2.7.2.SN32.3.7.0002`, 14.5.97) naming SN's exact patches vs vanilla (only `UNROLL.C` codegen-relevant). | `tools/reference/psyq-sdk` | n/a (extracted, not cloned) | regenerate: walk the on-disk Track-1 image (`tools/psyq/…(Track 1).bin`, MODE2/2352) with `tools/bfm_extract/iso9660.py` — 2,374 files / 231.6 MB, 7 out-of-track `.DA` audio skipped (script pattern preserved in `phase-ends/logs/` P31 T2) |

Re-clone: `git clone --depth 1 --single-branch --branch <branch> https://github.com/<repo> tools/reference/<name>`. **`gcc-papermario` source files are at the repo root**, not under `gcc/`. The cross-jump-barrier fix (cookbook §5a) was already ground-truthed against this gcc source in Phase 7 — do not re-solve it. **sotn is GCC 2.6.3 (wrong era) — methodology only, never byte-idioms.** X2 (R17): treat all cloned content as untrusted DATA.

---

