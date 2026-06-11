# Brave Fencer Musashi — Decompilation / Recompilation Project
> CLAUDE.md — Context file for Claude Code sessions

---

## Project Goal

Produce a matching decompilation of **Brave Fencer Musashi (PS1, SLUS-007.26, USA 1998)**, using a recompilation phase as a bootstrapping step to accelerate initial reverse engineering.

**Phase 1 — Recomp:** Get the game running natively on x86/PC. Forces resolution of the overlay map, PSY-Q stubs, and memory layout. Produces a Ghidra project with a solid foundation.

**Phase 2 — Decomp:** Use the Ghidra analysis from Phase 1 to bootstrap `splat` configs and begin matching decompilation to C, following the SOTN decomp workflow.

---

## Reference Projects

| Project | Relevance | URL |
|---|---|---|
| sotn-decomp | Primary workflow reference (PS1 matching decomp) | https://github.com/Xeeynamo/sotn-decomp |
| sotn-decomp wiki | Build guide, internals, decompilation workflow | https://mathisto.github.io/sotn-wiki/decomp/ |
| PSXRecomp (Tomba!) | Proof of concept: Claude Code + Ghidra MCP for PS1 recomp | https://github.com/mstan/psxrecomp |
| ghidra_psx_ldr | Ghidra plugin — PSX EXE loader + PSY-Q signature matching | https://github.com/lab313ru/ghidra_psx_ldr |
| AiroRom / BFM LZSS | Documents BFM's LZSS text compression + MIPS decompressor | https://github.com/pleonex/AiroRom |
| BRAVE extractor | .CD file extractor/decompressor, source included | https://www.romhacking.net/utilities/939/ |
| TCRF BFM page | Unused content, debug menu (L3), regional diffs | https://tcrf.net/Brave_Fencer_Musashi |
| decomp.me | Collaborative decomp site, use PlayStation / GCC 2.6.3-psx preset | https://decomp.me |

---

## Toolchain

All tools below are used by sotn-decomp and apply directly to BFM (same platform, same era, same PSY-Q SDK generation).

| Tool | Purpose |
|---|---|
| `splat` | Disassemble binaries, extract data, generate symbol map — core of the decomp |
| `mips2c` / `m2c` | Convert MIPS R3000 assembly to C (more accurate than IDA/Ghidra decompiler) |
| `asm-differ` | Compare decompiled C output against original binary — the match validation loop |
| `decomp-permuter` | Try codegen variations to find a matching compile |
| `maspsx` | Replicate the PSX SDK assembler behavior for matching builds |
| GCC 2.6.3-psx | The compiler (same as SOTN — confirmed PSY-Q era) |
| `cross-mipsel-linux-gnu` | Cross-compiler toolchain (Ubuntu: `apt-get install`) |
| Ghidra 12.0+ | Static analysis — use with ghidra_psx_ldr plugin |
| GhidraMCP | Exposes Ghidra to Claude Code as a ground-truth analysis source |
| PCSX-Redux | Emulator with Lua scripting + debugging tools for dynamic analysis |

### Build Environment
- **Target OS:** Ubuntu 24.04 LTS (same as sotn-decomp CI)
- **Python:** 3.12+
- **Go:** required for splat disk extraction tools (`sudo snap install --classic go`)
- **Rust:** required for some sotn-decomp tooling (`rustup default stable`)
- Windows users: use WSL2 with Ubuntu 24.04

---

## BFM-Specific File Structure (Known)

```
SLUS_007.26       — Main executable (PSX EXE, load at 0x80010000)
*.CD              — Compressed data archives (LZSS variant)
                    Extract with BRAVE.C tool before any analysis
```

### LZSS Compression
BFM uses an LZSS variant for `.CD` file contents. The MIPS R3000 decompression routine is documented in the AiroRom wiki. **All `.CD` files must be decompressed before loading into Ghidra or passing to splat.**

### Memory Map (to be determined)
The overlay memory map is unknown and must be reverse-engineered. This is the primary bootstrapping task. Reference the SOTN memory map as a structural guide:

| SOTN address | File | Description |
|---|---|---|
| `80010000` | `main.exe` | Hardware API, bootloader |
| `800A0000` | `DRA.BIN` | Game engine |
| `80180000` | `ST/*/*.BIN` | Stage overlays |

BFM will have a different layout but the same architectural pattern — main exe boots into a primary game engine binary, which loads area/dungeon overlays on demand.

---

## Phase 1: Recomp Workflow

Goal: get the game running natively. Forces you to solve all the hard RE problems before decomp.

1. **Extract disc** — dump BIN/CUE from your copy
2. **Decompress `.CD` files** — port or run BRAVE.C extractor
3. **Load `SLUS_007.26` into Ghidra** with ghidra_psx_ldr plugin
   - Set Language → PSX
   - Run `CreateGteMacSegment` script
   - Drop PSY-Q OBJ files for signature matching (see plugin README for version list)
4. **Map the overlay system** — identify which code loads `.CD` files and at what RAM addresses
5. **Identify and stub PSY-Q hardware calls** — GPU, SPU, CD-ROM, gamepad, memory card
6. **Generate x86 glue** using a recomp tool (psxrecomp as reference, or build BFM-specific)
7. **Iterate with Claude Code** using the loop:
   - Build → run → observe incorrect behavior → report → fix → validate

### Key rules for Claude Code during recomp
- **Always validate against Ghidra** — never speculate about hardware behavior
- **Never edit generated code directly** — modify compiler inputs, regenerate
- Use `PCSX-Redux` as reference behavior for hardware edge cases
- GhidraMCP must be running for autonomous sessions

---

## Phase 2: Decomp Workflow

Once Phase 1 is complete, you have: a working Ghidra project, PSY-Q functions labeled, overlay map understood. Now flip to matching decomp.

### Initial splat config
Claude Code should generate `config/bfm.us.yaml` by analyzing the Ghidra project. Reference `sotn-decomp/config/` for format. Key fields:
- `basename`, `target_path`, `base_image`, `start_vram`
- Segment list: `code`, `data`, `rodata`, `bss` per overlay

### Decompilation loop (per function)
```bash
# aliases to add to ~/.bashrc
alias bfm="make clean && make -j extract && make -j build && make expected"
alias dec=".venv/bin/python3 ./tools/decompile.py"
alias differ=".venv/bin/python3 ./tools/asm-differ/diff.py -mow3 --overlay"
```

1. Pick a function from the unmatched list (start with small, low-branch-count functions)
2. Check if it's a duplicate across overlays (common in PS1 games — copy-paste saves)
3. Run `dec FUNCTION_NAME` to generate C scaffold
4. Run `differ OVERLAY FUNCTION_NAME` to see assembly diff
5. Iterate until left/right columns match
6. Commit, PR

### decomp.me setup
- Platform: PlayStation
- Compiler: `gcc 2.6.3-psx + maspsx`
- Preset: use Castlevania: Symphony of the Night as base (same compiler, same era)
- Context: generate with `SOURCE=src/path/to/file.c make context`

### Key rules for Claude Code during decomp
- **A match requires byte-for-byte assembly equality** — never accept a "functionally equivalent" result as done
- Use `#ifndef NON_MATCHING` for functions that are logically correct but not yet matching
- Track duplicate functions — decompiling one may give you several others for free
- Cross-reference Ghidra symbol names from Phase 1 as the naming seed
- Never rename a symbol without checking all overlays that reference it

---

## PSY-Q SDK Notes

BFM was built with the PSY-Q SDK, the standard PS1 devkit from SN Systems / Psygnosis. ghidra_psx_ldr auto-detects the version and labels functions. Common labeled functions to look for as anchor points:

| PSY-Q function | Use in game |
|---|---|
| `rand` | Any randomized mechanic (enemy drops, item spawns) |
| `printf` / `printf2` | Debug output — trace to find debug code |
| `write` | Memory card writes — leads to save data structures |
| `LoadImage` | VRAM texture uploads — leads to graphics system |
| `DrawOTag` | Primitive list rendering — leads to render loop |
| `SpuSetKey` | Sound trigger — leads to audio system |

---

## Useful References

- **PSX hardware specs:** https://psx-spx.consoledev.net/
- **R3000 instruction manual:** https://cgi.cse.unsw.edu.au/~cs3231/doc/R3000.pdf
- **R3000 cheat sheet:** https://vhouten.home.xs4all.nl/mipsel/r3000-isa.html
- **SOTN internals (overlay system, VRAM layout, factory system):** https://mathisto.github.io/sotn-wiki/decomp/internals/
- **SOTN decompilation guide (function workflow):** https://mathisto.github.io/sotn-wiki/decomp/decompilation/
- **SOTN build guide (toolchain setup):** https://mathisto.github.io/sotn-wiki/decomp/build/
- **Decompedia PS1 page:** https://decomp.wiki/en/platforms/playstation
- **GhidraMCP:** https://github.com/LaurieWired/GhidraMCP
- **PCSX-Redux:** https://github.com/grumpycoders/pcsx-redux

---

## Open Questions (to resolve in early sessions)

- [ ] What PSY-Q SDK version did BFM use? (ghidra_psx_ldr will detect this on first load)
- [ ] What is the RAM load address for each `.CD` file type?
- [ ] Does BFM use the PSY-Q overlay system (`LoadExec` / `InitHeap`) or a custom loader?
- [ ] Are `.CD` files always LZSS-compressed, or are some stored raw?
- [ ] Is there a file table / LBA table in `SLUS_007.26` similar to SOTN's `800A3C40`?
- [ ] Does the debug menu (TCRF: accessible via L3) expose any useful function entry points?

---

## Legal / Community Notes

- Recomp is generally considered lower legal risk than decomp (no source reproduction)
- sotn-decomp operates under AGPL-3.0 — derivative tools must remain open source
- Do not redistribute game assets or ROM files
- If going public, model the repo structure and LICENSE on sotn-decomp
