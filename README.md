# BFM-decomp

A matching decompilation of **Brave Fencer Musashi** (PlayStation, SLUS-00726, USA 1998) — the first public decompilation effort for this game.

## What "matching" means

The goal is C source code that, compiled with the original-era toolchain (PsyQ 4.x / GCC 2.7.2-family + ASPSX via maspsx), produces a byte-for-byte identical `SLUS_007.26` and, eventually, byte-identical overlay binaries. SHA1 checksums are the ground truth; "functionally equivalent" does not count.

## No ROM content

This repository contains **no game assets, no disassembly output, and no ROM-derived data** — only source code, build configuration, symbol names/addresses, hashes, and documentation. To build or contribute you must provide your own dump of the game disc (4-track BIN/CUE, redump layout). See `.gitignore` for the firewall.

## Project status

> **Latest (Phase 19, 2026-06-20):** the project builds **136 binaries byte-identical from a clean tree** (the EXE + the resident engine + all **134 location overlays**); **`make check-all` → 136/136**. Fleet byte-identical-from-source is **58.0%** (function-instance-weighted; see the PhaseEnds for the byte-weighted ~30% figure and what it includes). Shared engine functions are matched once in `ov_SC01_077` and propagated **×134** via `tools/dedup_propagate.py`. *(The narrative below is Phase-11/12-era; a full refresh is part of the public-flip prep.)*

**Gen1 (foundation) complete — the matching pipeline is proven end-to-end.** `make extract && make build && make check` rebuilds `SLUS_007.26` **byte-for-byte identical** (SHA1 `143dbb89…`) from C + assembly, reproducibly across many sessions.

- **Compiler pinned by evidence:** `gcc-2.7.2-psx -O2 -G0 -mips1 -mcpu=3000` + `maspsx --aspsx-version=2.56 --expand-div`.
- **52 functions hand-matched** to byte-identical machine code — including the LZSS streaming decompressor — with a decomp-permuter + matching-cookbook "flywheel" to accelerate the next.
- **959 PsyQ SDK functions linked byte-identical** (libcd, libgs, libgte, libspu/libsnd, libgpu, libc2, libmcrd, libapi/libcard, libetc) straight from the real PsyQ 4.0 libraries instead of re-decompiling them — bringing byte-identical-from-source coverage of the EXE to **~50%**.
- **File-loader / overlay system reverse-engineered**, with the resident engine blob + location overlays' load addresses **proven byte-identical against a live PCSX-Redux RAM dump**.

About half the EXE is still `INCLUDE_ASM` stubs (correct bytes, not yet C), and the bulk of the game lives in compressed overlays inside the `.CD` archives — **Gen2** (overlays & engine at scale) is underway:

- The build toolchain is **binary-agnostic** (one parameterized pipeline builds any binary), and the always-resident **engine blob** rebuilds **byte-for-byte from source** (SHA1 `8e17e02f…`) — the *second* binary reconstructed exactly, after the EXE — and is now **86% hand-matched C** (123 / 146 functions, up from 0): its scripting turned out to be **compiled-MIPS state/mode dispatch, not a bytecode VM**, and the save-file + sound (SQV) formats are documented. The harvest used a reusable **swarm-of-agents + bit-for-bit byte-gate** method (a wrong match can't be accepted) — `tools/harvest_verify.py` + `tools/match_one.py`, which carry straight into the overlay phase.
- A **cross-binary deduplication pipeline** is live: a Ghidra-free signer fingerprints all 134 location overlays, and the report finds **~9,000 byte-identical function groups shared across binaries (~28 MB of collapsible code)** — a single engine function is byte-identical in all 134 overlays. This is "one match unlocks many": each engine match will be auto-credited across the overlay fleet.

Current phase and detailed progress live in `phase-ends/` (newest `PhaseEnd_*.md` = current state); methodology, rules, and the full roadmap are in `PROJECT_CONTEXT.md`; environment setup in `docs/SETUP.md`.

This project is developed primarily by Claude Code driving Ghidra through an MCP server; see `CLAUDE.md`.

## License

Private repository for now. **AGPL-3.0 is planned at public release**, modeled on [sotn-decomp](https://github.com/Xeeynamo/sotn-decomp). `tools/brave-CUE/` is CUE's BRAVE extractor (GPL, source included) and retains its own license.
