# Build from your own disc

The repository contains **no game data** — no executable, no disassembly, no assets, no memory dumps, no SDK. Only
source, build configuration, symbol names and hashes. To rebuild the 218 binaries and check them you need your own
dump of the USA disc. Nothing in this page needs the Ghidra database or the emulator; those are reverse-engineering
tools, not build inputs.

## What you need

| Item | Detail |
|---|---|
| The disc | *Brave Fencer Musashi (USA)* (SLUS-00726) in redump layout: a 4-track BIN/CUE. Track 1 SHA1 `b44f0f0a19936f23b26188b658e13201a6a9c211`, CRC32 `c238191b`. A Track-1-only dump also works — the three CD-audio tracks are then reported as *unverified*, never silently passed. |
| Linux | The project uses WSL2 Ubuntu 24.04. Packages: `binutils-mipsel-linux-gnu`, `cpp-mipsel-linux-gnu`, `python3.12`, `git`, `make`. `make bootstrap` prints the exact `apt` line and installs the rest itself. |
| Disk and time | About 3 GB for the build tree. A full clean rebuild takes about five minutes on 16 cores (measured on a fresh clone: 4 min 18 s wall, 45 CPU-minutes). |

The Sony PsyQ SDK objects are **optional and never needed for byte-identity** — see [Toolchain setup](Toolchain-setup.md#the-optional-sony-sdk).

## The recipe

```bash
git clone --recurse-submodules https://github.com/Druthulu/BFM-decomp.git && cd BFM-decomp
make bootstrap                    # -> "check-env: OK"   (one WARN: run make disc-extract)
mkdir -p disks && cp '/path/to/Brave Fencer Musashi (USA)'*.{bin,cue} disks/
make disc-extract                 # -> "disc-extract: OK"
make clean && make -j"$(nproc)" extract-all && make -j"$(nproc)" check-all
                                  # -> "extract-all: 217 extracted, 0 failed of 217 (+ main, serial)"
                                  # -> "check-all: 218 passed, 0 failed of 218"     <- THE contract line
```

Every `make` target exits non-zero on any failure. **Read the exit code, not the presence of an output file:** a failed
build leaves the previous binary in place, so `sha1sum` after a failed `make` can read green on a stale file (this bit
the project twice in one hour, and became rule R53). `make help` lists every target with one line each.

## What each step proves

| Step | Proves | Expected last line |
|---|---|---|
| `make bootstrap` | The toolchain is present and pinned: the venv from [`requirements-python.txt`](../../requirements-python.txt), the four submodules, the two gcc-2.7.2 `cc1` tarballs sha256-checked against [`tools/bin/CHECKSUMS.sha256`](../../tools/bin/CHECKSUMS.sha256) and extracted, binutils on the PATH | `check-env: OK` |
| `make disc-extract` | Your dump is the redump image (`--verify-disc`: SHA1 + CRC32) and it extracts to the **same 1,801 files** the project was built against — compared against the committed manifest [`extracted/retail/manifest.jsonl`](../../extracted/retail/manifest.jsonl) + `.sha1`, which is never rewritten by a build | `disc-extract: OK` — or `PARTIAL: 1,798/1,798 code+data verified; 3 .DA unverified` for Track-1-only |
| `make extract-all` | splat splits every binary from the extracted payloads; `asm/` and the linker scripts are regenerated, never edited (rule H3) | `extract-all: 217 extracted, 0 failed of 217 (+ main, serial)` |
| `make check-all` | **Every binary's build SHA1 equals its `config/check.<alias>.sha`.** The main executable's is `143dbb89f34491258bbc27810d0a12ec8b43a8dd` | `check-all: 218 passed, 0 failed of 218` |

The extractor behind `disc-extract` is the project's own ([`tools/bfm_extract/`](../../tools/bfm_extract/)): an ISO9660
walker, the `.CD` table-of-contents and PAC splitter, and an LZSS decoder implementing the *game's* termination
semantics, byte-validated in Phase 2 against the community's reference extractor on every type-4 payload.

## Optional checks

```bash
make sdk-dual       # only with the SDK objects: main byte-identical WITH and WITHOUT them
make tools-health   # the two independent function-boundary oracles agree; the dedup registry validates; every audit fresh
make report         # the three 100% lines, "INCLUDE_ASM stubs : 0"
```

The whole sequence, as the project runs it, is [`tools/verify_contract.sh`](../../tools/verify_contract.sh); its last
recorded run is in [`docs/verification.md`](../verification.md) (every step's log under `.run/P33/verify/`, tracked).

## When a step fails

- **`disc-extract` refuses the dump.** Only the redump image is accepted; a different rip, a trimmed track or a
  converted image fails `--verify-disc` and nothing is written. A truncated Track 1 is detected the same way.
- **`check-all` reports a red binary.** First re-run the clean sequence — a bare `make check-all` after a source change is
  *incremental* and has lied before (a false 211/213); the clean rebuild is the contract (rule R22). If it stays red on an
  unmodified checkout, open an issue with the binary's name and your `make check BINARY=<alias>` output.
- **A build says `psyq_integrate` or mentions `build/psyq/`.** That is the optional-SDK path; without SDK objects it must
  not run at all. See [Toolchain setup](Toolchain-setup.md#the-optional-sony-sdk).
- **Working on one binary.** `make extract BINARY=<alias> && make check BINARY=<alias>` — the alias is the source directory
  name (`main`, `resident`, `ov_SC01_077`, `md_MAIN_013`, …; see [Overlays and modules](Overlays-and-modules.md)). Pass
  `-j` to every build: a single-binary build without it is single-threaded (measured 7.2 s → 1.2 s).
