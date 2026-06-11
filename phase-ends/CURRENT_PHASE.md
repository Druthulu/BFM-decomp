# CURRENT_PHASE — Phase 1: Repo governance + WSL RE stack + first import

**Status:** in progress · **Started:** 2026-06-10 · **Plan approved:** yes (harness plan mode)

> This is the in-phase log (crash/compaction/handoff recovery point). Read it after `PROJECT_CONTEXT.md` and any `PhaseEnd_*.md`. When Phase 1's milestone is confirmed, this content is absorbed into `PhaseEnd_Phase1.md` and this file is deleted.

---

## Corrections to the constitution recorded this phase

These post-generation decisions override the original (Fable-5) `PROJECT_CONTEXT.md` where they conflict. The constitution's env sections were surgically corrected on 2026-06-10 to match; these are the authoritative statements:

1. **All-in-WSL (Linux-first).** Everything runs inside WSL2 Ubuntu 24.04 on a single ext4 clone (`~/bfm-decomp`): Claude Code, Ghidra (GUI via WSLg) + GhidrAssistMCP + ghidra_psx_ldr, build toolchain, PCSX-Redux. No Windows/WSL split, no two-clone, no `wsl.exe`, no `/mnt` builds, no mirrored networking. MCP is local at `127.0.0.1:8080`. (Supersedes the original Windows-hybrid/two-clone design; rule **H2** now = "build on ext4, one clone".)
2. **H1 relaxed while private.** ROM-derived content (asm/, assets/, extracted/, decompressed .CD) MAY be committed; accidental inclusion is not a violation. Compliance = pre-public history scrub + a rom→decoder regeneration tool. The raw multi-GB dump stays ignored (GitHub >100 MB limit; reproducible). Decision: commit freely + push to the private remote + scrub before public.
3. **All tools live under `tools/`** (incl. `tools/bin` for downloaded compilers, `tools/psyq*` for native PsyQ binaries).
4. **Plan mode every phase** (harness plan mode) before executing — Drew's standing preference.

To formalize in `PhaseEnd_Phase1.md` under "Rules Added" (P10): the H1 relaxation, the all-in-WSL H2 restatement, tools-in-`tools/`, plan-mode-per-phase.

---

## Verified facts (this session)

- **Install assets confirmed (web):** Ghidra `ghidra_12.1_PUBLIC_20260513.zip` (pin 12.1 exactly — 12.1.2 exists since 2026-06-05 but extensions only ship 12.1 assets); JDK 21 Temurin; GhidrAssistMCP v2.8.0 (`ghidra_12.1_PUBLIC_20260530_GhidrAssistMCP.zip`); ghidra_psx_ldr 2026.06.04 (`ghidra_12.1_PUBLIC_20260604_ghidra_psx_ldr.zip`). Extension assets are platform-independent Java → same filenames on Linux Ghidra.
- **Disc integrity (redump):** Track-1 SHA1 `b44f0f0a19936f23b26188b658e13201a6a9c211`, CRC32 `c238191b`, build date **1998-08-25**. The `SLUS_007.26` EXE hash is not publicly documented (expected); our extractor produces SHA1 `143dbb89f34491258bbc27810d0a12ec8b43a8dd` (413,696 bytes), independently reproduced from raw sectors. `--verify-disc` checks Track-1 vs redump as the canonical proof.
- **PsyQ stamps (EXE scan):** 12 genuine — 9× 4.0 (libnums 2,3,4,6,7,8,9,17,24), 1× 4.0.1x (16), 1× 4.2 (0), 1× 4.2.1x (12). ⇒ GCC 2.7.2 family. ghidra_psx_ldr detection at import is the final word.

---

## Task checklist (approved plan)

### A. Finalize repo, then hand off to WSL (this Windows session)
- [x] Extractor `tools/bfm_extract` built + adversarially verified (done early)
- [x] Constitution surgical correction (PROJECT_CONTEXT.md env sections → all-in-WSL + H1 note)
- [x] `.gitignore` H1 relaxation (un-ignore asm/ assets/ extracted/ *.CD.dir; keep dump + build churn ignored)
- [~] `docs/SETUP.md` → Linux-first (in progress)
- [~] Extractor hardening + `--verify-disc` (in progress)
- [ ] Root research-file cleanup → `docs/history/` (+ SUPERSEDED banner on starting-point doc)
- [ ] Commit per task + push (clean handoff)

### B. Migrate to WSL (collaborative — user relaunches Claude Code in WSL)
- [ ] Clone `origin` → `~/bfm-decomp` (ext4); make the dump available in `disks/`
- [ ] Relaunch Claude Code inside WSL; this Windows session ends
- [ ] Install RE stack in WSL (JDK 21, Ghidra 12.1, ghidra_psx_ldr, GhidrAssistMCP); start MCP server

### C. First import + milestone (in WSL)
- [ ] Run extractor → `extracted/SLUS_007.26`; `--verify-disc` PASS (Track-1 == redump)
- [ ] Import into Ghidra (WSLg): PSX loader, auto-analyze + PsyQ signatures, record PsyQ version, attach `psyq400.gdt`, MCP type-resolution test
- [ ] MCP round-trip: `/mcp` ~38 tools; `get_binary_info`; decompile `0x80018730`
- [ ] **MILESTONE:** MCP decompile of `0x80018730` ≈ LZSS decompressor; PsyQ version recorded → user confirm → `PhaseEnd_Phase1.md`

## Next task
Finish A (SETUP.md + extractor hardening via workflow, then root cleanup), commit + push, then guide the WSL migration (B).

## Blockers / needs-user
- Confirm the GitHub repo `Druthulu/BFM-decomp` is set to **Private**.
- B requires the user to relaunch Claude Code inside WSL and drive Ghidra's WSLg GUI for install/import.
