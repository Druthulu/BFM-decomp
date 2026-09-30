## §4 Build environment (Phase 4)

Everything below installs inside the same WSL2 Ubuntu 24.04 that already hosts Ghidra and Claude Code (§1). Where Phase 1 (§2) already set up the distro and JDK, this phase adds the build toolchain on top.

### §4.1 WSL2 + Ubuntu 24.04 (already present from Phase 1)

The all-in-WSL architecture means WSL2 Ubuntu 24.04 is the single host for the whole project, so it exists before Phase 4 begins (it is the same environment §2 installed Ghidra into). Confirm it is the expected distro and version:

```bash
cat /etc/os-release   # Ubuntu 24.04
uname -a              # Linux kernel (WSL2)
whoami                # the Linux username; ~ resolves to /home/<user>
```

All project paths are plain Linux paths under `~/bfm-decomp` — there is no Windows distro name or `wsl.exe --cd` target to track.

### §4.2 Networking: MCP is local

Under the all-in-WSL architecture there is **no cross-OS networking**. Ghidra/GhidrAssistMCP, PCSX-Redux, and Claude Code all run inside the same WSL2 instance, so the MCP endpoint is plain loopback: **MCP is local to WSL at `http://127.0.0.1:8080`; no mirrored-mode `.wslconfig`, firewall rule, or host-IP discovery is needed.** Smoke-test with Ghidra running: `curl http://127.0.0.1:8080/` from any shell in the same WSL instance.

### §4.3 The clone on ext4

```bash
cd ~ && git clone <remote-url> bfm-decomp
```

The single clone lives at `~/bfm-decomp` (ext4). Builds, splat, asm-differ, Ghidra, and Claude Code all run here. In this clone: `git config core.filemode true`. **Remote (P33):** `origin` = `https://github.com/Druthulu/BFM-decomp.git` (public from Phase 33 C10); the pre-rewrite history lives in the private archive `Druthulu/BFM-decomp-archive`. Claude commits, Drew pushes (R6).

### §4.4 Copy the disc dump into the clone

> **As-built (P33 B1/B8):** after the copy, **`make disc-extract`** regenerates `extracted/` from `disks/` and verifies every
> file against the committed manifest (`disc-extract: OK`, 15.7 s; `PARTIAL` for a Track-1-only dump; the "P33 B1" section
> below has the flags and controls). `make extract-all` runs it once first; `make check-env` warns when the EXE is absent.

One-shot copy onto ext4 is fine (and required once):

```bash
mkdir -p ~/bfm-decomp/disks
cp '<dump-source>/Brave Fencer Musashi (USA)/'*.bin \
   '<dump-source>/Brave Fencer Musashi (USA)/'*.cue ~/bfm-decomp/disks/
```

`<dump-source>` is wherever the disc dump currently lives (e.g. a one-time download into `~/Downloads`, or a one-shot copy from external media). `disks/` is gitignored — no ROM-derived bytes ever reach the remote (rule H1).

**Status (Phase 2, 2026-06-13):** the disc was staged early — extraction needs it before Phase 4. Track 1 alone (it holds all 27 root files) was copied once from the author's dump location (a `<dump-source>` as above) to ext4 at `disks/Brave Fencer Musashi (USA) (Track 1).bin` (364,846,944 bytes). WSL `extract_exe.py --bin "disks/…(Track 1).bin" --verify-disc` **PASSED** — SHA1 `b44f0f0a19936f23b26188b658e13201a6a9c211`, CRC32 `c238191b`, both == redump — which **closes the Phase-1 deferral** (verify-disc had previously only run on Windows; PhaseEnd_Phase1 Deviations).

### §4.5 apt packages

Adapted from sotn-decomp's `tools/requirements-debian.txt` (dropped Saturn/PSP-only items `binutils-sh-elf`, `xfonts-utils`; Rust/Go deferred until a duplicate-detector or asset tool needs them):

```bash
sudo apt-get update && sudo apt-get install -y \
  bchunk binutils-mipsel-linux-gnu bsdmainutils clang-format coreutils curl \
  gcc-mipsel-linux-gnu git libelf-dev make ninja-build p7zip-full \
  python3-pip python3-venv unzip wget
```

> ⚠️ **binutils regression check (mandatory before trusting builds):** open-ribbon documents that `binutils-mipsel-linux-gnu >= 2.38` generated broken binaries; **2.35 is the known-good reference**. Ubuntu 24.04 ships newer binutils — **VERIFY on 24.04**: after Phase 5's first full build, if the SHA1 check mysteriously fails with correct-looking asm, suspect the assembler first (`mipsel-linux-gnu-as --version`), and pin/downgrade or build binutils 2.35 if confirmed. Record the verdict here.
>
> **As-built (Phase 4, 2026-06-14, ledger #6):** apt installed **binutils-mipsel-linux-gnu 2.42** (as/ld/objcopy all 2.42; mipsel-gcc 12.4.0). 2.42 ≥ 2.38, so `make check-env` emits a **[WARN]** (not FAIL) and the regression verdict is **deferred to Phase 5's first full build** exactly as above — no preemptive downgrade.
>
> **✅ VERDICT (Phase 5, 2026-06-14): binutils 2.42 is byte-clean — no regression with our flags.** The all-asm `make build` reproduces `SLUS_007.26` **SHA1-identical** (`143dbb89…`) using `mipsel-as` 2.42 with `-march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0`. The open-ribbon "≥2.38 broken" warning does **not** bite here; **no downgrade to 2.35 needed.** (Revisit only if Phase-6 C-compiled objects ever diff where the asm is right.)

### §4.6 Python venv + splat + submodules

> **As-built (P33 B3/B8): `make bootstrap`** (`tools/bootstrap.sh`) does all of this idempotently on a fresh clone — apt
> presence check (prints the install line), the venv from `requirements-python.txt`, the submodules, the two cc1 tarballs
> sha256-checked and extracted, then `make check-env` — proven fresh-clone → 218/218 in 4 m 18 s (the "P33 B3" section).
> The manual steps below remain the reference for what it does.

```bash
cd ~/bfm-decomp
python3 -m venv .venv                    # Python >= 3.12 required (24.04 ships 3.12; older = f-string SyntaxError mid-build)
.venv/bin/pip install -U 'splat64[mips]>=0.41.0,<1.0.0'
```

The PyPI package is **`splat64`** (not `splat`), and the `[mips]` extra is required for PSX (pulls spimdisasm/rabbitizer). Always invoke as `.venv/bin/splat` or `.venv/bin/python3 -m splat` — `splat: command not found` means you're outside the venv. Once Phase 5 builds green, freeze the exact working version in a committed `tools/requirements-python.txt`.

Submodules (add under `tools/`):

| Submodule | URL | Pin |
|---|---|---|
| `tools/maspsx` | `https://github.com/mkst/maspsx.git` | commit `874855c53f65f8fa57447e1da6bde6236dbef9d5` (decomp.me's pin in June 2026; decomp.me now runs `86ccd7d8` — measured byte-equivalent for our aspsx version, `docs/decompme-preset.md` §3; `tools/decompme_replica.sh --upstream` reports drift) |
| `tools/asm-differ` | `https://github.com/simonlindholm/asm-differ.git` | pin current HEAD at adoption |
| `tools/m2c` | `https://github.com/matt-kempster/m2c.git` | pin current HEAD at adoption |
| `tools/decomp-permuter` | `https://github.com/simonlindholm/decomp-permuter` | sotn pins `b44b0622269fb4bff29e79fbbad26b9f47beda79` — sane default |

Pin all four (sotn precedent: blindly updating submodules breaks tooling). Note: sotn's asm-differ `--overlay` flag is **sotn-fork-specific**, not upstream — for BFM overlay diffing use upstream's `-o` object mode or port their fork later.

**As-built (Phase 4, 2026-06-14):** `.venv` created (Python 3.12.3); installed **splat64 0.41.0** (`splat64[mips]`) — deps spimdisasm 1.41.0, rabbitizer 1.16.2, PyYAML 6.0.3, colorama 0.4.6, intervaltree 3.1.0, tqdm 4.67.1; `import splat` OK. Submodule pins as adopted: maspsx `874855c5`, decomp-permuter `b44b0622` (both per the table); **asm-differ `2ad4a4a4`** and **m2c `4266cc28`** (each HEAD-at-adoption). Their pip deps are **not** installed yet (Phase 6, when first invoked); `tools/requirements-python.txt` is frozen only after Phase 5 is green.

### §4.7 Vintage compilers (old-gcc 0.17)

Linux prebuilts from decompals/old-gcc, **release 0.17** (32-bit i386 static — see the correction below):

```bash
mkdir -p ~/bfm-decomp/tools/bin && cd ~/bfm-decomp/tools/bin
wget https://github.com/decompals/old-gcc/releases/download/0.17/gcc-2.7.2-psx.tar.gz
wget https://github.com/decompals/old-gcc/releases/download/0.17/gcc-2.7.2-cdk.tar.gz
sha256sum gcc-2.7.2-*.tar.gz   # record hashes in a committed tools/bin/*.sha256 on first download,
                               # then verify with `sha256sum --check` on every fresh setup (sotn pattern)
# The 0.17 tarballs are FLAT (no top-level dir) and SHARE filenames (cc1, cpp, gcc, ...)
# -> extract each into its OWN subdir, or the second clobbers the first (Phase-4 finding):
mkdir -p gcc-2.7.2-psx gcc-2.7.2-cdk
tar xzf gcc-2.7.2-psx.tar.gz -C gcc-2.7.2-psx
tar xzf gcc-2.7.2-cdk.tar.gz -C gcc-2.7.2-cdk
```

**As-built (P33 B3):** the two tarballs are TRACKED in the repository (`tools/bin/*.tar.gz`, GCC = GPL; sha256s in
`tools/bin/CHECKSUMS.sha256`) and `tools/bootstrap.sh` does exactly the check-and-extract above on a fresh clone — the
`wget` lines are how they were first obtained, not a step a contributor runs.

- `gcc-2.7.2-psx` = community GCC 2.7.2 PSX build (primary candidate).
- `gcc-2.7.2-cdk` = **cygnus-2.7.2-970404**, the exact base of PsyQ 4.0/4.1's CC1PSX (added in old-gcc 0.14).
- **sha256 (RECORDED Phase 4, old-gcc 0.17, ledger #7):** `gcc-2.7.2-psx.tar.gz` = `500a459b3485e885a8d302cac23c2a4632f3900e03a09153f6190699fd723571`; `gcc-2.7.2-cdk.tar.gz` = `42bb0df96db11a9b5d2e23d78bdc962791f40046280d3d360da93fe5eef6f0bb`. Committed to `tools/bin/CHECKSUMS.sha256` (gitignore exception `!/tools/bin/*.sha256`); re-verify with `sha256sum --check tools/bin/CHECKSUMS.sha256`.
- **CORRECTION (Phase 4):** these are **32-bit i386 statically-linked** ELF binaries (NOT x86-64 as previously written) — they run on x86-64 WSL2 via the kernel's IA-32 emulation (verified: `cc1` smoke-compiles to MIPS asm and self-identifies as `GNU C 2.7.2 [AL 1.1, MM 40] Sony Playstation`). Still Linux-only — *why* the build side must be Linux/WSL2. As-built layout: `tools/bin/gcc-2.7.2-psx/cc1` + `tools/bin/gcc-2.7.2-cdk/cc1` (matches the §6.2 path).

### §4.8 Optional: PsyQ 4.0/4.1 binaries for arbitration (via Wine)

> **As-built (P33 B4/B8):** the OPTIONAL Sony SDK *objects* that let `make check BINARY=main` link the real PsyQ libraries
> are obtained, sha256-verified and built by **`tools/fetch_psyq.sh`** (user-supplied 4.0 LIBs from the DTL-S2002 disc or
> `--from DIR`; the RTL 4.2 archive; `psyq-obj-parser`) — see the "P33 B4" section. Byte-identity never needs them
> (`make sdk-dual`). The Wine arbitration path below is the Phase-6 fingerprinting tool, unrelated to linking.

For byte-exact arbitration when maspsx output is in doubt, the **real** PsyQ Win32 tools can be driven from WSL under Wine (`sudo apt-get install -y wine`):

- `https://github.com/mkst/esa/releases/download/psyq-binaries/psyq4.0.tar.gz`
- `https://github.com/mkst/esa/releases/download/psyq-binaries/psyq4.1.tar.gz`
  (contain `CC1PSX.EXE`, `ASPSX.EXE`, `CCPSX.EXE`, `PSYLINK.EXE`, `PSYLIB.EXE`; 1–2.3 MB each)
- Their `.OBJ` output converts to ELF with **psyq-obj-parser** (part of pcsx-redux; prebuilt Linux binary: `https://github.com/decompme/compilers/releases/download/compilers/psyq-obj-parser.tar.gz`).

Keep these under `tools/` on ext4 (not committed); they are a tie-breaker, not the daily pipeline. (decomp.me runs these same Win32 tools under Wine for its psyq presets — the precedent that this works headless.)

> **DEFERRED to Phase 6 (Drew decision, Phase 4):** not staged in Phase 4 — fetched only if/when maspsx output is disputed during fingerprinting. Wine is not installed. The §4.8 "optional native PsyQ binaries" checkbox is consciously skipped for Phase 4.

### §4.9 `make check-env` (Phase 4 exit milestone)

Phase 4's observable milestone: a `check-env` make target that asserts every §4 component (venv + splat import, cc1 binaries executable, maspsx present, mipsel-as/ld/objcopy on PATH, python >= 3.12) and exits 0 when invoked directly in the WSL clone (see §6.1).

**As-built (Phase 4, 2026-06-14):** the root `Makefile` implements `check-env` (`.ONESHELL` bash; default goal `help`). Beyond the components above it also asserts **sha1(committed `extracted/retail/SLUS_007.26`) == `EXPECTED_EXE_SHA1`** (imported from `tools/bfm_extract/extract_exe.py` — fresh-clone-safe; the disc-walk `--verify-disc` needs the gitignored `disks/` and is intentionally NOT in check-env) and WARNs on binutils ≥ 2.38. **`make check-env` exits 0** (milestone met). `extract/build/check/expected/clean` exist as loud-failing Phase-5 stubs (names fixed per §6.3).

---

