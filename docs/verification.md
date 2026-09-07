# Verify it yourself — the byte-identity contract, and how to check it with your own disc

> BFM-decomp's claim is narrow and machine-checkable: **218 binaries** (the main executable `SLUS_007.26`, the resident
> engine blob, 138 location overlays and 78 code modules) **rebuild byte-for-byte from the C in `src/`**, compared against
> the originals extracted from a redump-verified USA disc. This page is the recipe, the expected output of every step,
> and the record of the last full run. Nothing ROM-derived is in the repository (`tools/audit_public.py` guards that), so
> every check below that touches game bytes needs YOUR disc dump. What CI proves without a disc is at the end.

## 0. What you need

| Item | Detail |
|---|---|
| The disc | *Brave Fencer Musashi (USA)* (SLUS-00726), redump layout: 4-track BIN/CUE. Track 1 SHA1 `b44f0f0a19936f23b26188b658e13201a6a9c211`, CRC32 `c238191b`. A Track-1-only dump also works (the 3 CD-audio tracks are then reported as unverified, never silently passed). |
| Linux (WSL2 Ubuntu 24.04 is what the project uses) | `binutils-mipsel-linux-gnu`, `cpp-mipsel-linux-gnu`, `python3.12`, `git`, `make` — `make bootstrap` prints the exact apt line and installs the rest (venv, submodules, the tracked gcc-2.7.2 `cc1` tarballs, sha256-checked). |
| Disk / time | ≈3 GB for the build tree; the full clean rebuild takes ≈5 min on 16 cores (measured 4 m 18 s on a fresh clone, single user 45 CPU-min). |

The PsyQ SDK objects are **optional** and never needed for byte-identity: without them the main executable links the
project's own `INCLUDE_ASM` fallback tiles for Sony's library regions and is still byte-identical (this is the WITHOUT leg
of `make sdk-dual`, and it is what every fresh clone builds). See `docs/SETUP.md` §P33 B4 if you own the SDK.

## 1. The recipe (R22: a CLEAN rebuild — never an incremental one)

```bash
git clone --recurse-submodules https://github.com/Druthulu/BFM-decomp.git && cd BFM-decomp
make bootstrap                    # -> "check-env: OK"  (one WARN: run make disc-extract)
mkdir -p disks && cp '/path/to/Brave Fencer Musashi (USA)'*.{bin,cue} disks/
make disc-extract                 # -> "disc-extract: OK"  (extracts the disc, compares 1,801 files to the committed manifest)
make clean && make -j"$(nproc)" extract-all && make -j"$(nproc)" check-all
                                  # -> "extract-all: 217 extracted, 0 failed of 217 (+ main, serial)"
                                  # -> "check-all: 218 passed, 0 failed of 218"     <- THE contract line
make sdk-dual                     # optional, only with the SDK objects -> "sdk-dual: OK — main 143dbb89… byte-identical WITH and WITHOUT the PsyQ objects"
make tools-health                 # -> "tools-health: OK — sigs fresh; corpus(+resident) + cdecl + binaries + report(lint+dedup) + cookbook-index all green."
make report                       # -> the three 100% lines below, "INCLUDE_ASM stubs : 0"
```

Every `make` target exits non-zero on any failure; read the exit code, not the presence of an output file (a failed build
leaves the previous binary in place — rule R53). `make help` lists every target with one line each.

### What each step proves

| Step | Proves | Expected last line |
|---|---|---|
| `make bootstrap` | the toolchain is present and pinned (cc1 tarballs sha256 `500a459b…` / `42bb0df9…`, maspsx submodule at the pinned commit, binutils) | `check-env: OK` |
| `make disc-extract` | your disc is the redump image and extracts to the SAME 1,801 files the project was built against (`extracted/retail/manifest.jsonl` + `.sha1`, committed) | `disc-extract: OK` (or `PARTIAL: 1,798/1,798 code+data verified; 3 .DA unverified` for Track-1-only) |
| `make extract-all` | splat splits every binary from the extracted payloads (asm/ and the linker scripts are regenerated, never edited) | `extract-all: 217 extracted, 0 failed of 217 (+ main, serial)` |
| `make check-all` | **every binary's build SHA1 equals `config/check.<alias>.sha`** — main `143dbb89f34491258bbc27810d0a12ec8b43a8dd` | `check-all: 218 passed, 0 failed of 218` |
| `make sdk-dual` | main is byte-identical both with Sony's real objects linked and with the fallback tiles | `sdk-dual: OK — …` |
| `make tools-health` | the two independent function-boundary oracles agree (0 phantom / 0 truncated / 0 pad-tail), the dedup registry validates (2,220 groups / 0 failures), the audits and derived indexes are fresh | `tools-health: OK — …` |
| `make report` | the three progress metrics, source-derived | `FLEET fn-count byte-ident: 363214 / 363214 = 100.00%` · `FLEET instr-weighted : 13492113 / 13492113 = 100.0%` · `FLEET distinct-code(uniq): 5820205 / 5820205 = 100.0%` · `MAIN game-code weighted : 45150 / 45150 = 100.0%` |

### What is NOT our C (stated plainly)

- **1,256 functions of the main executable are Sony's PsyQ library objects**, linked byte-identical from the SDK when you
  have it and represented by assembly fallback tiles when you do not (`src/lib*.c`, `src/apicard*.c` — `INCLUDE_ASM`
  stubs whose bytes come from the disc). Reimplementing Sony's libraries from source is out of scope.
- **5 functions fleet-wide are hand-written assembly in the original** (`config/verbatim_manifest.json`, PERMANENT rows);
  they are kept as verbatim `__asm__` bodies, audited by `tools/verbatim_check.py --strict`.
- Everything else — every game-code function in all 218 binaries — is C.

## 2. The last recorded run

The project's own full run is recorded, log by log, under `.run/P33/verify/` (tracked: `NN_<step>.log`, each ending in
`EXIT=<rc>` and a timestamp, plus `SUMMARY.md`), produced by `tools/verify_contract.sh` on the committed tree. The table
below is copied from that `SUMMARY.md`; regenerate it with the script, never by hand.

- **Tree:** `5bc4a5c0ab27c94fd52f45d0cc1647427ed0468f` (2026-09-06) · **Host:** Linux 6.18.33.1-microsoft-standard-WSL2, 32 CPUs, JOBS=16 · **Run:** 2026-09-07T05:44:24Z

| # | Step | EXIT | wall | contract line |
|---|---|---|---|---|
| 00 | `tree` | 0 | 1s | HEAD 5bc4a5c0ab27c94fd52f45d0cc1647427ed0468f 2026-09-06 fix(phase-33): verify_contract step 00 ignores its own output directory — the per |
| 01 | `check-env` | 0 | 1s | check-env: OK — Phase-4 toolchain ready. |
| 02 | `family-hseq` | 0 | 13s | family_hseq regenerated: 217 binaries scanned, 0 open instances |
| 03 | `r22-clean-fleet` | 0 | 176s | check-all: 218 passed, 0 failed of 218 |
| 04 | `sdk-dual` | 0 | 29s | sdk-dual: OK — main 143dbb89f34491258bbc27810d0a12ec8b43a8dd byte-identical WITH and WITHOUT the PsyQ objects (maps: .run/P33/verify/main_ |
| 05 | `tools-health` | 0 | 358s | tools-health: OK — sigs fresh; corpus(+resident) + cdecl + binaries + report(lint+dedup) + cookbook-index all green. |
| 06 | `audit-frontier` | 0 | 10s | audit-frontier: reference = corpus.stubs over 218 binaries -> 1258 open stubs |
| 07 | `audit-disc` | 0 | 40s | UNCLAIMED code payloads: 0 |
| 08 | `report` | 0 | 223s | FLEET distinct-code(uniq): 5820205 / 5820205 = 100.0%   (90984/90984 unique fns; the DISTINCT-RE number) |

Every `NN_<step>.log` is tracked under `.run/P33/verify/`; the tools-health log also carries `sig-main-oracle: main is now INDEPENDENT — 0 in-domain stubs, 0 PHANTOM, 0 TRUNCATED, 0 PAD-TAIL` and the report `INCLUDE_ASM stubs : 0`, `Open near-misses: 0`. Total wall 14 min on 32 CPUs.

This run (C8) is on the REWRITTEN history: before the public flip the repository's history was rewritten (ROM-derived paths
purged from every commit, personal addresses mapped, old commit hashes in historical documents replaced by inert tokens —
`docs/commit-map.tsv`, `docs/public-flip-runbook.md`). A content-preserving rewrite changes no tracked-content byte, and this
run proves it: the same 218/218 and the same three 100% lines as the pre-rewrite run (A5, 2026-09-07T03:11Z, tree ordinal
4030 of the original history).

The same run was performed after every banked batch of Phases 30–32 (218/218 at every one; the P32 close run is
`.run/P32/t4e/r22_check.log`) and the history-rewrite of the public flip is followed by one more (C8) on the adopted tree —
a content-preserving rewrite changes no tracked byte, and that run proves it.

## 3. What CI proves without the disc

`.github/workflows/no-rom.yml` runs on every push and pull request:

- **audits** — no ROM-derived bytes, purge paths or >50 MiB files among the tracked files (`tools/audit_public.py`, whose
  ROM-hash set is derived from the committed manifest + every `config/check.*.sha`); every source is text with portable
  includes; the verbatim manifest has no drift; the derived indexes (cookbook, Ghidra roster) are fresh; the LZSS decoder's
  unit tests; no stale symbol references.
- **compile-only** — every eligible translation unit (4,170 of 4,287; the rest are the library tiles that `.include`
  disc-derived assembly) goes through cpp → gcc-2.7.2 `cc1` → maspsx → GNU `as` with the Makefile's exact flags. A PR
  compiles four representative binaries (≈1 min); the whole fleet runs weekly and on demand.

CI cannot compare bytes to the originals — that is your step 1. The two together are the full claim.

## 4. Reverse-engineering artifacts you can also regenerate

The Ghidra project is not in the repository (its database embeds the game's bytes). Its hand-authored content is tracked
as text under `config/ghidra/` (`ROSTER.md` lists the programs) and `tools/ghidra_rebuild.sh <program> --proof` rebuilds a
program from your disc + the symbol files + that text and proves the result equals it (`PROOF PASS`). The 28 RAM images
the memory map was derived from are local-only; `dumps/CHECKSUMS.sha1` records their identity.
