# BFM-decomp

A matching decompilation of **Brave Fencer Musashi** (PlayStation, SLUS-00726, USA 1998) — the first public decompilation effort for this game.

## What "matching" means

The goal is C source code that, compiled with the original-era toolchain (PsyQ 4.x / GCC 2.7.2-family + ASPSX via maspsx), produces a byte-for-byte identical `SLUS_007.26` and, eventually, byte-identical overlay binaries. SHA1 checksums are the ground truth; "functionally equivalent" does not count.

## No ROM content

This repository contains **no game assets, no disassembly output, and no ROM-derived data** — only source code, build configuration, symbol names/addresses, hashes, and documentation. To build or contribute you must provide your own dump of the game disc (4-track BIN/CUE, redump layout). See `.gitignore` for the firewall.

## Project status

Early foundation. Current phase and progress live in `phase-ends/` (newest `PhaseEnd_*.md` = current state). Project methodology, rules, and the full roadmap are in `PROJECT_CONTEXT.md`. Environment setup is in `docs/SETUP.md`.

This project is developed primarily by Claude Code driving Ghidra through an MCP server; see `CLAUDE.md`.

## License

Private repository for now. **AGPL-3.0 is planned at public release**, modeled on [sotn-decomp](https://github.com/Xeeynamo/sotn-decomp). `tools/brave-CUE/` is CUE's BRAVE extractor (GPL, source included) and retains its own license.
