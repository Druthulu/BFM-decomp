# Third-party components

The project's own work (`tools/`, `docs/`, the build system, the Ghidra scripts) is licensed under the AGPL-3.0
(`LICENSE`); the reimplemented game sources under `src/` carry no license (`src/NOTICE.md`). Everything else the
project uses keeps its own license, listed here. "In the repository" means the files are committed; "download only"
means the project records where to get them and how to verify them, and never redistributes them.

| Component | Role here | License (as published upstream) | In the repository? |
|---|---|---|---|
| [brave-CUE](tools/brave-CUE/) (CUE) | The reference `.CD`/PAC/LZSS extractor our own extractor was validated against, byte for byte | GPL-3.0 (`tools/brave-CUE/license.txt`) | Source only, vendored under `tools/brave-CUE/`. The compiled `brave.exe` was removed from the repository and from its entire history before publication. |
| [maspsx](https://github.com/mkst/maspsx) (Mark Street) | Reproduces the quirks of Sony's ASPSX assembler between cc1 and GNU `as` | MIT | Git submodule `tools/maspsx` (pinned) |
| [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) (Simon Lindholm and contributors) | Search over source permutations for near-miss functions; the project's ILS warm-restart and masked scorer wrap it | MIT | Git submodule `tools/decomp-permuter` (pinned) |
| [asm-differ](https://github.com/simonlindholm/asm-differ) (Simon Lindholm) | Per-function assembly diffs | The Unlicense (public domain) | Git submodule `tools/asm-differ` (pinned) |
| [m2c](https://github.com/matt-kempster/m2c) (Matt Kempster and contributors) | The decompiler used for scaffolds | GPL-3.0 | Git submodule `tools/m2c` (pinned) |
| [old-gcc](https://github.com/decompals/old-gcc) (decompals) | The builds of the era's compilers; the project's pinned `cc1` (gcc 2.7.2, "psx" and "cdk" variants) comes from its release tarballs | The repository publishes no license file; the compilers it builds are GCC, licensed GPL-2.0-or-later, whose source is at gnu.org | The two tarballs are tracked under `tools/bin/` with sha256s (`tools/bin/CHECKSUMS.sha256`: `500a459b…`, `42bb0df9…`) so the toolchain is reproducible; the gcc-2.7.2 source is the reference for the codegen map |
| gcc 2.7.2 source (GNU) | The authoritative reference for the pinned compiler's behaviour (`docs/gcc-2.7.2-map/`, the cookbook's citations) | GPL-2.0 | Download only (`ftp.gnu.org/old-gnu/gcc/gcc-2.7.2.tar.gz`, sha256 recorded in `docs/SETUP.md` §5); cloned under the gitignored `tools/reference/` |
| [Ghidra](https://github.com/NationalSecurityAgency/ghidra) (NSA) | The static-analysis oracle; the project's headless scripts under `tools/ghidra_scripts/` drive it | Apache-2.0 | Not in the repository (installed locally). The project's Ghidra database is not committed either — its hand-authored content is tracked as text under `config/ghidra/` and rebuilt by `tools/ghidra_rebuild.sh` |
| [ghidra_psx_ldr](https://github.com/lab313ru/ghidra_psx_ldr) (lab313ru) | PlayStation executable loader, PsyQ signatures and types for Ghidra | No license file published upstream | Download only; the release zip is verified by sha256 (`docs/SETUP.md` §2.4) and was removed from the repository and its history |
| [GhidrAssistMCP](https://github.com/symgraph/GhidrAssistMCP) | The MCP server through which the AI agent drives Ghidra | MIT | Download only (sha256 in `docs/SETUP.md` §2.3); `tools/ghidra_scripts/BfmMcpServer.java` is the project's own headless wrapper |
| psyq-obj-parser (part of [PCSX-Redux](https://github.com/grumpycoders/pcsx-redux)), built by [decomp.me](https://github.com/decompme/compilers) | Converts Sony's PsyQ `.OBJ`/`.LIB` files to ELF so the real library objects can be linked | GPL-2.0 (PCSX-Redux) | Download only, user-supplied via `tools/fetch_psyq.sh`, sha256 in `tools/psyq_CHECKSUMS.sha256` |
| [PCSX-Redux](https://github.com/grumpycoders/pcsx-redux) | The runtime oracle (live RAM comparisons that proved the overlay map) | GPL-2.0 | Not in the repository |
| Sony PlayStation SDK (PsyQ 4.0 / Runtime Library 4.2) | Optional: with it, the main executable links Sony's real library objects instead of the assembly tiles; without it the build is still byte-identical | Proprietary (Sony) | **Never distributed.** User-supplied (`tools/fetch_psyq.sh`, from a user's own copy of the SDK disc or archive); only sha256 checksums are tracked (`tools/psyq_CHECKSUMS.sha256`) so a supplied copy can be verified |
| [splat](https://github.com/ethteck/splat), [spimdisasm](https://github.com/Decompollaborate/spimdisasm), [rabbitizer](https://github.com/Decompollaborate/rabbitizer) | The binary splitter and disassembler | MIT | Python packages (`requirements-python.txt`), not vendored |
| GNU binutils (`mipsel-linux-gnu`) | The assembler, linker and objcopy | GPL-3.0 | System package, not vendored |
| Other Python packages (`requirements-python.txt`: PyYAML, git-filter-repo, pycparser, …) | Tooling dependencies | Their own (PyPI) | Not vendored |
| [ProjectArchitect](https://github.com/Druthulu/ProjectArchitect) (the author's own) | The governance framework this project ran under; `docs/history/project_architect_v1.3.0.md` is the version used | See its repository | The framework document is kept in `docs/history/` as a historical record |
| [Brave Fencer Musashi Archipelago world](https://github.com/AegeusEvander/Brave-Fencer-Musashi-AP-World) (AegeusEvander), TCRF, gamehacking.org, the LiveSplit autosplitter | Sources of memory addresses and facts, cited with provenance in `docs/memory-map.md` | Facts, cited; no code copied | — |

Removed from the repository **and its history** before publication (they are game-derived or proprietary): the game
executable, the RAM dumps, the Ghidra project database, the Sony SDK, the session-transcript archive, the two Ghidra
extension installers, and `brave.exe`. Every replacement is a checksum or a rebuild path — see
`docs/public-flip-runbook.md`.
