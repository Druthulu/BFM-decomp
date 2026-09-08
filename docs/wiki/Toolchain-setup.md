# Toolchain setup

> **Every tool, by need:** the [tool index](../tool-index.md) (generated; its authored half is `config/tool_dictionary.tsv`).

Everything runs inside one Linux environment (the project uses WSL2 Ubuntu 24.04 on a single ext4 clone; builds never
run on a Windows-mounted path — the 9P bridge is slow and breaks file watching). The authoritative, evolvable reference
for every version, path and command is [`docs/SETUP.md`](../SETUP.md); this page is the map of it.

## The pinned triple — and why it is pinned

The compiler, assembler and their flags were fixed in Phase 6 **by fingerprint evidence from the binary itself**, not by
copying a sibling project (the tempting choice, sotn-decomp's GCC 2.6.3, would have produced systematic near-miss diffs on
every function — an invisible poison). The evidence: twelve genuine PsyQ library version stamps in the executable
(PsyQ 4.0 with 4.2 updates ⇒ the GCC 2.7.2 family), then idiom-revealing probe functions run down a candidate ladder of
`cc1` builds × ASPSX assembler versions × `-G` settings until one reproduced the bytes.

```
cpp (modern, mipsel)  →  gcc-2.7.2-psx cc1 -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker
                      →  maspsx --aspsx-version=2.56 --expand-div
                      →  mipsel-linux-gnu-as -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0
                      →  ld (splat's linker script)  →  objcopy
```

Two details that cost time and are worth knowing: `--expand-div` turned out to be mandatory (Phase 6), and maspsx's
default ASPSX version is *not* the latest, so the version is always passed explicitly (rule G8). A handful of modules
compile at `-O0` where the bytes demand it (the boot module and the `_o0` splits carved out of otherwise `-O2` files);
the Makefile carries those as per-file flags.

## Versions (as built)

| Component | Version / pin | Notes |
|---|---|---|
| Ubuntu / Python | 24.04 / 3.12 | older Pythons fail mid-build on f-string syntax |
| `binutils-mipsel-linux-gnu` | 2.42 | the "≥ 2.38 is broken for PS1" warning did **not** bite: the all-assembly build was SHA1-identical on the first try (Phase 5) — no downgrade to 2.35 |
| splat | `splat64[mips]` 0.41.0 | the PyPI package is `splat64`, and the `[mips]` extra is required |
| gcc-2.7.2 `cc1` | old-gcc release 0.17, `gcc-2.7.2-psx` (primary) and `gcc-2.7.2-cdk` (cygnus-2.7.2-970404, the base of PsyQ's CC1PSX) | 32-bit i386 static binaries, run under the kernel's IA-32 emulation; the tarballs are tracked (GCC is GPL) with sha256s `500a459b…` / `42bb0df9…` in [`tools/bin/CHECKSUMS.sha256`](../../tools/bin/CHECKSUMS.sha256) |
| maspsx | submodule, commit `874855c5` | decomp.me's pin, so local results compare to decomp.me scratches |
| decomp-permuter | submodule, commit `b44b0622` | with the project's masked scorer and warm-restart wrapper ([`tools/permuter/`](../../tools/permuter/)) |
| asm-differ / m2c | submodules, `2ad4a4a4` / `4266cc28` | pinned at adoption; blindly updating submodules breaks tooling (sotn precedent) |

`make bootstrap` ([`tools/bootstrap.sh`](../../tools/bootstrap.sh)) performs the whole setup idempotently — apt presence
check (prints the install line, never runs `sudo`), the venv, the submodules, the checksummed tarballs — and ends with
`make check-env`, which asserts each component and the state of the extracted disc.

## The optional Sony SDK

The main executable links 1,256 functions of Sony's PsyQ libraries (libcd, libgs, libgte, libgpu, libspu/libsnd, libetc,
libapi, libcard, libpad 4.2.1 …). They are **not our C** and are never redistributed. The build handles them two ways,
and both produce the identical executable:

- **Without the SDK** (every fresh clone): the library regions are carried as `INCLUDE_ASM` tiles whose bytes come from
  your disc (`src/lib*.c`, `src/apicard*.c`). This is the public build.
- **With the SDK** (`tools/fetch_psyq.sh`): if you own the PsyQ 4.0 libraries (the DTL-S2002 disc) and the RTL 4.2
  archive, the script verifies each file against [`tools/psyq_CHECKSUMS.sha256`](../../tools/psyq_CHECKSUMS.sha256),
  converts the objects with `psyq-obj-parser`, and the link uses Sony's real objects.

`make sdk-dual` proves the two are the same bytes (`sdk-dual: OK — main 143dbb89… byte-identical WITH and WITHOUT the
PsyQ objects`) and is part of `make tools-health` when the objects exist. Twelve functions that had been recorded as
"compiler walls" in Phase 31 were in fact the libpad 4.2.1 objects — provenance is asked before the compiler is blamed.

## Reverse-engineering tools (not needed to build)

- **Ghidra 12.1** with **ghidra_psx_ldr** (the PlayStation loader: PsyQ signatures, the GTE macro segment) and
  **GhidrAssistMCP** — the static oracle. The project runs it *headless* with an MCP server ([`tools/ghidra_mcp_start.sh`](../../tools/ghidra_mcp_start.sh)
  / [`tools/ghidra_mcp_stop.sh`](../../tools/ghidra_mcp_stop.sh)) so the agent can query it; symbol renames persist only
  through the headless `ApplySymbols` script, never through MCP renames. The database itself is not in git — see
  [Ghidra rebuild from text](Ghidra-rebuild-from-text.md). Install steps and the pinned extension zips (sha256-recorded,
  download-only) are in SETUP §2.
- **PCSX-Redux** — the runtime oracle, bridged over its web API for RAM snapshots; every overlay load address in
  [`docs/memory-map.md`](../memory-map.md) was proven against a live RAM image (SETUP §3).
- **The gcc-2.7.2 source** (`tools/reference/`, gitignored; GPL, from ftp.gnu.org) — read, not built: it is what the
  codegen map ([`docs/gcc-2.7.2-map/`](../gcc-2.7.2-map/)) cites. A community "2.7.2" tree in circulation is gcc 2.8.1;
  the map's audit found the drift and the vanilla source was staged.
