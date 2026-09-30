## Version pin summary

All components run inside WSL2 Ubuntu 24.04 (single ext4 clone). The "Side" column below is retained for historical continuity but every entry is now **WSL2 (Linux)**.

| Component | Pinned version | Side | Phase |
|---|---|---|---|
| JDK | 21 (Temurin) | WSL2 (Linux) | 1 |
| Ghidra | **12.1 PUBLIC exactly** (`ghidra_12.1_PUBLIC_20260513.zip`) — NOT 12.1.2 | WSL2 (Linux) | 1 |
| GhidrAssistMCP | v2.8.0 (`ghidra_12.1_PUBLIC_20260530_GhidrAssistMCP.zip`) | WSL2 (Linux) | 1 |
| ghidra_psx_ldr | release 2026.06.04 (`ghidra_12.1_PUBLIC_20260604_ghidra_psx_ldr.zip`) | WSL2 (Linux) | 1 |
| PCSX-Redux | Linux build (AppImage/flatpak; no version pin; record build on install) | WSL2 (Linux) | 3 |
| WSL2 distro | Ubuntu-24.04 (Python 3.12 ships with it) | WSL2 (Linux) | 4 |
| splat | pip `splat64[mips]` `>=0.41.0,<1.0.0` — **as-built 0.41.0** (Phase 4); freeze exact once Phase 5 green | WSL2 (Linux) | 4 |
| Vintage compiler | decompals/old-gcc **release 0.17**: `gcc-2.7.2-psx` + `gcc-2.7.2-cdk` | WSL2 (Linux) | 4 |
| maspsx | git submodule, `mkst/maspsx` at `874855c53f65f8fa57447e1da6bde6236dbef9d5` (decomp.me's pin when we adopted it, June 2026; decomp.me moved to `86ccd7d8` on 2026-08-29 — 4 commits later, behaviour identical for `--aspsx-version` ≥ 2.30; see `docs/decompme-preset.md` §3) | WSL2 (Linux) | 4 |
| asm-differ / m2c / decomp-permuter | git submodules (URLs in §4.6) | WSL2 (Linux) | 4 |
| binutils (mipsel) | apt `binutils-mipsel-linux-gnu` — **as-built 2.42** (Phase 4; ≥2.38 → check-env WARN, verdict deferred to Phase 5), 2.35 known-good | WSL2 (Linux) | 4 |

---

