## Known-unverified ledger (recheck and update in place)

| # | Item | Status |
|---|---|---|
| 1 | GhidrAssistMCP/psx_ldr 12.1 zips on Ghidra 12.1.2 | **MOOT for us** — pinned Ghidra **12.1** exactly; both extensions load fine at `version=12.1` (confirmed 2026-06-13). The 12.1.2 question stays untested by design. |
| 2 | MCP `types`/`struct` resolution of attached-archive (.gdt) types | **RESOLVED 2026-06-13** — import (`resolve()`) the .gdt types into the program headlessly (`tools/ghidra_scripts/ImportPsyqGdt.java`); MCP `types` then resolves them fully (§2.5 step 5) |
| 3 | GhidrAssistMCP struct-tool ergonomics under matching-decomp load | **UNPROVEN** — psxrecomp never exercised heavy struct creation |
| 4 | PCSX-Redux web-server port config field (8080 collision) | **RESOLVED 2026-06-13** — `pcsx.json` → `emulator.Debug.WebServer=true` + `emulator.Debug.WebServerPort=8081`; dump at `GET http://127.0.0.1:8081/api/v1/cpu/ram/raw` (verified 2 MB; EXE-in-RAM byte-match) |
| 5 | WSL distro is Ubuntu 24.04 (the single all-in-WSL host) | **CONFIRMED 2026-06-14 (Phase 4)** — `/etc/os-release` = Ubuntu 24.04.4 LTS (VERSION_ID 24.04) |
| 6 | binutils ≥2.38 regression on Ubuntu 24.04's shipped binutils | **RESOLVED (Phase 5): 2.42 is byte-clean** — `make build` is SHA1-identical with our flags; no downgrade (§4.5) |
| 7 | sha256 hashes of old-gcc 0.17 tarballs | **RECORDED 2026-06-14 (Phase 4)** — psx `500a459b…`, cdk `42bb0df9…` in `tools/bin/CHECKSUMS.sha256` (§4.7) |
| 8 | `gp_value` in SLUS_007.26 header → -G0 vs -G8 | **RESOLVED (Phase 5): -G0** — zero $gp-relative addressing in the disasm (§5.3) |
| 9 | ASPSX tier for game code: 2.56 vs 2.67 | **OPEN** — Phase 6 empirical (§5.2 tell) |
| 10 | Cross-OS networking | **N/A under all-in-WSL** — MCP is local loopback (§4.2); no mirrored mode, firewall rule, or host-IP discovery |
| 11 | Canonical git remote URL (off-box push/pull backup) | **CLOSED (P33 C9, 2026-09-07):** `https://github.com/Druthulu/BFM-decomp.git`, public from C10; the pre-rewrite history in the private archive `Druthulu/BFM-decomp-archive` (§4.3) |
| 12 | Per-libnum stamp detail (raw-track scan reported 16 hits vs 12 genuine in extracted EXE — extracted-EXE scan is ground truth, see §5.1) | **RESOLVED 2026-06-13** — DetectPsyQ at headless import recorded `PsyQ Version = 4.0.0` (§2.5 step 3) |
| 13 | Overlay load addresses (resident 0x800CDF58 / location 0x80128508, EXE ptr table ~0x62620) | **JP-only — re-derive for US** (owned by docs/memory-map.md) |
| 14 | Greenfield claim: decomp.me scratch search is script-blocked (Cloudflare) | **CLOSED 2026-09-08 (P34 task 2, Drew's E1 browser session):** manual search on decomp.me for `Musashi` → no results; `Brave Fencer` → no results; `SLUS-00726` → no results; `SLUS_007` → many scratches, all other titles sharing the SLUS_007xx prefix under other compilers — none is this game. The only BFM scratch is our own probe, <https://decomp.me/scratch/mIu4d> (100% / score 0). The greenfield claim's last check is done. The preset was proven locally first (2026-09-07, `tools/decompme_replica.sh` PASS through decomp.me's 0.13 + `86ccd7d8` toolchain; 2026-09-08 step D: the paste itself round-trips). |

