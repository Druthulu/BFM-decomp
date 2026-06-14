# PhaseEnd — Phase 4: Matching-build toolchain (WSL)
**Date:** 2026-06-14 · **Project Version:** 1.4.0 · **Phase Status:** Complete

## Build Log

**Files created/changed and complete — do not recreate:**
- `Makefile` — **new**, repo root. The live target is **`check-env`** (the Phase-4 milestone preflight):
  `.ONESHELL` bash, default goal `help`. Asserts python ≥ 3.12, venv `import splat`, both cc1 candidates
  (R12-clean stdin smoke), `tools/maspsx/maspsx.py`, the three mipsel binutils (as/ld/objcopy), and
  **sha1(committed `extracted/retail/SLUS_007.26`) == `EXPECTED_EXE_SHA1`** (imported from
  `tools/bfm_extract/extract_exe.py` — no magic literal). binutils ≥ 2.38 → **[WARN]**, not FAIL (§4.5).
  `extract/build/check/expected/clean` are **loud-failing no-op stubs** (names fixed per §6.3; Phase 5
  implements them). Consumed by: the daily build (Phase 5 extends this file).
- `.gitmodules` — **new**; 4 submodules under `tools/`.
- `tools/maspsx`, `tools/asm-differ`, `tools/m2c`, `tools/decomp-permuter` — **new** submodule gitlinks
  (pinned, see Verification). Their working-tree *contents* are gitignored-by-submodule (a fresh clone
  runs `git submodule update --init`).
- `tools/bin/CHECKSUMS.sha256` — **new, committed**; sha256 of the two old-gcc 0.17 tarballs. The ONLY
  thing committed out of the otherwise-ignored `tools/bin/`. Verify with `sha256sum --check`.
- `.gitignore` — **modified**: `/tools/bin/` → `/tools/bin/*` + `!/tools/bin/*.sha256` (contents-exclude
  form so the checksum record commits while all compiler binaries/tarballs stay ignored).
- `docs/SETUP.md` — **modified**: as-built versions (binutils 2.42, splat 0.41.0 + deps, gcc tarball
  sha256, submodule pins, check-env); **§4.7 corrected** (cc1 is 32-bit i386 not x86-64; flat-tarball →
  per-subdir extraction fix); §4.8 deferred-to-Phase-6 note; ledger **#5/#6/#7 resolved**; pin-summary
  splat/binutils rows updated.
- `phase-ends/CURRENT_PHASE.md` — **absorbed into this file and deleted** (P8).
- `phase-ends/PhaseEnd_Phase4.md` — this file.

**Local artifacts (gitignored / outside the repo — present on this machine, do NOT recreate; a fresh clone redoes them):**
- `.venv/` — Python 3.12.3 venv. Recreate: `python3 -m venv .venv && .venv/bin/pip install 'splat64[mips]>=0.41.0,<1.0.0'`.
- `tools/bin/gcc-2.7.2-psx/` + `tools/bin/gcc-2.7.2-cdk/` — old-gcc 0.17 prebuilts (32-bit i386 static
  `cc1`/`cc1plus`/`cpp`/`gcc`/`g++`) + the two `.tar.gz`. Recreate per the corrected §4.7.
- Submodule working trees under `tools/{maspsx,asm-differ,m2c,decomp-permuter}` — `git submodule update --init`.

**Tools/packages installed:**
- **apt:** build-essential (make 4.3, g++ 13.3.0), **binutils-mipsel-linux-gnu 2.42** + cpp/gcc-mipsel-linux-gnu
  12.x, python3-pip 24.0, python3-venv (3.12), ninja-build 1.11.1, libelf-dev, clang-format 18, p7zip-full,
  bchunk, bsdmainutils (curl/wget/unzip/git/coreutils already present, ensured).
- **venv (pip):** splat64 0.41.0; deps spimdisasm 1.41.0, rabbitizer 1.16.2, PyYAML 6.0.3, colorama 0.4.6,
  intervaltree 3.1.0, tqdm 4.67.1.
- **downloaded (gitignored):** old-gcc 0.17 `gcc-2.7.2-psx.tar.gz` + `gcc-2.7.2-cdk.tar.gz`.

**Verification results (literal):**
- **MILESTONE — `make check-env` → exit 0:** `[PASS]` python3 3.12; venv `import splat` (splat64 0.41.0);
  cc1 runs `tools/bin/gcc-2.7.2-psx/cc1` **and** `…-cdk/cc1`; maspsx present; mipsel `as`/`ld`/`objcopy`
  all 2.42; `extracted/retail/SLUS_007.26` sha1 `143dbb89f34491258bbc27810d0a12ec8b43a8dd` ==
  `EXPECTED_EXE_SHA1`. Plus `[WARN]` mipsel binutils 2.42 ≥ 2.38. `check-env: OK`.
- `git submodule status`: **maspsx `874855c5` ✓**, **decomp-permuter `b44b0622` ✓** (both pinned per the
  table), asm-differ `2ad4a4a4` (HEAD@adoption), m2c `4266cc28` (HEAD@adoption).
- `sha256sum --check tools/bin/CHECKSUMS.sha256`: **both OK** — psx `500a459b…`, cdk `42bb0df9…`.
- cc1 binaries are **32-bit i386 statically-linked** ELF (run via IA-32 emulation); psx cc1 smoke emits
  `GNU C 2.7.2 [AL 1.1, MM 40] Sony Playstation` + valid MIPS asm; psx/cdk cc1 are **distinct** (different
  sha256 — the naive flat extraction would have silently kept only one).
- **Hygiene:** `git add tools/bin/` stages **only** `CHECKSUMS.sha256`; `git status` shows **zero
  ROM-derived/binary bytes** would stage (`.venv`, compiler binaries, `.tar.gz` all ignored). bare `make`
  → help; `make extract` → loud fail (`make: *** Error 1`).
- Ubuntu 24.04.4 LTS confirmed (ledger #5).
- **Nothing committed** (R8): all work is staged/untracked and uncommitted, awaiting Drew's phase-end commit.

**Milestone achieved:** `make check-env` exits 0 in the WSL ext4 clone — both cc1 candidates execute and
emit MIPS asm, splat imports in the venv, the mipsel binutils are present, and the committed `SLUS_007.26`
sha1 equals `EXPECTED_EXE_SHA1` — the matching-build toolchain is stood up and self-verifying.

**Next:** Phase 5 — splat config + build skeleton (all-asm byte-match). Start with `config/splat.us.exe.yaml`
authored (section boundaries iterated until a clean link), `config/symbols.us.txt` already seeded from
Phase 3. (Phase 5 RE-reads gp_value for -G0/-G8, ledger #8; implements the Makefile's stub targets.)

## Deviations
| Item | Plan | Actual | Reason |
|---|---|---|---|
| cc1 architecture | "x86-64 Linux ELF" (§4.7) | **32-bit i386 statically-linked** | old-gcc 0.17 ships i386 binaries; run on x86-64 via IA-32 emulation; §4.7 corrected |
| old-gcc extraction | `tar xzf psx ; tar xzf cdk` flat (§4.7) | per-subdir `-C gcc-2.7.2-{psx,cdk}` | tarballs are flat **and** share filenames → flat extraction clobbers psx with cdk; §4.7 command fixed |
| check-env "dump hash" | disc-level implied by milestone | sha1(committed EXE) == `EXPECTED_EXE_SHA1`, reused constant | fresh-clone-safe (disc-walk needs gitignored `disks/`); reuses existing code (no magic literal) |
| cc1 liveness check | "cc1 runs (--version)" | trivial **stdin** compile | gcc-2.7.2 cc1 rejects `--version`; stdin→/dev/null compile is the real test, and R12-clean (no temp file) |
| §4.8 native PsyQ binaries | optional Phase-4 checkbox | **deferred to Phase 6** | Drew decision; tie-breaker only if maspsx output is disputed during fingerprinting |
| submodule pip deps + requirements freeze | implied by "installed" | **deferred** (Phase 6 / after Phase-5 green) | milestone names only splat/cc1/maspsx/binutils; avoids polluting the to-be-frozen `requirements-python.txt` |
| binutils version | 2.35 known-good target | **2.42 installed + WARN**, verdict deferred | §4.5 mandates deferral to Phase 5's first full build; Ubuntu 24.04 ships 2.42 |
| Makefile scope | check-env only (milestone) | check-env + Phase-5 target **name stubs** | §6.3 fixes the names now; loud-failing stubs prevent a silent false-success build |

## Commit Message
```
feat(phase-4): matching-build toolchain (WSL) — make check-env green

- apt: build-essential, binutils-mipsel-linux-gnu 2.42 (+gcc-mipsel 12.x), ninja
  1.11.1, python3-pip/venv, libelf-dev, clang-format, p7zip, bchunk, bsdmainutils
- .venv + splat64 0.41.0 ([mips]: spimdisasm 1.41.0, rabbitizer 1.16.2, PyYAML 6.0.3)
- 4 pinned submodules under tools/: maspsx@874855c5, decomp-permuter@b44b0622,
  asm-differ@2ad4a4a4, m2c@4266cc28 (.gitmodules)
- old-gcc 0.17 cc1 candidates -> tools/bin/gcc-2.7.2-{psx,cdk}/ (32-bit i386 static;
  tarballs are flat + same-named -> per-subdir extraction); CHECKSUMS.sha256 committed
  (gitignore exception !/tools/bin/*.sha256); psx cc1 self-id "GNU C 2.7.2 [AL 1.1,
  MM 40] Sony Playstation"
- Makefile: check-env (.ONESHELL bash) asserts python>=3.12, venv import splat, both
  cc1 (stdin smoke), maspsx, mipsel as/ld/objcopy, sha1(EXE)==EXPECTED_EXE_SHA1;
  binutils>=2.38 -> WARN (verdict deferred to Phase 5, §4.5); extract/build/check/
  expected/clean are loud-failing Phase-5 stubs (names per §6.3)
- docs/SETUP.md: as-built versions; §4.7 corrected (i386, flat-tarball fix); §4.8
  deferred to Phase 6; ledger #5 confirmed (Ubuntu 24.04.4), #6 (2.42), #7 (sha256)
- MILESTONE: make check-env exits 0; zero ROM-derived bytes staged
- bumps project version 1.3.1 -> 1.4.0
```

## Rules Added This Phase
| Rule | Reason |
|---|---|
| **None** | Phase 4's findings are *deviations / doc-corrections* (cc1 is i386 not x86-64; the flat-tarball extraction trap; binutils 2.42 WARN; §4.8 deferral), not governance rules. **Noted practice (not elevated to a rule):** build/preflight targets should be *fresh-clone-safe* and *reuse single-source constants* (no magic literals, no gitignored deps) — applied in `check-env` (imports `EXPECTED_EXE_SHA1`, hashes the committed EXE). Elevate later if Phase 5's build targets benefit. |

## PhaseEnd Changelog
**v1.3.1 → v1.4.0** — Phase 4 complete. The matching-build toolchain is stood up and self-verifying in the
WSL ext4 clone: the apt cross-toolchain (binutils-mipsel **2.42**), a Python 3.12 venv with **splat64
0.41.0**, four pinned submodules (maspsx/asm-differ/m2c/decomp-permuter), and the old-gcc 0.17 cc1
candidates (`gcc-2.7.2-psx` + `gcc-2.7.2-cdk`) — all asserted by a new **`make check-env`** target that
**exits 0**. Two SETUP.md corrections caught by the bytes: the cc1 prebuilts are **32-bit i386** (not
x86-64), and the 0.17 tarballs are **flat & same-named** so each must extract into its own subdir. binutils
2.42 is WARN-flagged with the regression verdict **deferred to Phase 5's first build** (§4.5). Ledger
#5/#6/#7 resolved; §4.8 native-PsyQ arbitration deferred to Phase 6; submodule pip deps + requirements
freeze deferred. **No new rules.** Next: Phase 5 (splat config + all-asm byte-match).

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` absorbed and removed. **Drew commits AND pushes** this PhaseEnd
(R6/R8 — the single Phase-4 commit lands everything: Makefile, .gitmodules, submodule gitlinks,
tools/bin/CHECKSUMS.sha256, .gitignore, docs/SETUP.md, PhaseEnd_Phase4.md). Start a **fresh session for
Phase 5 — splat config + build skeleton**. Keep this file forever.
