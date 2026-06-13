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
5. **No `Co-Authored-By` trailer on commits** (overrides the harness default) — Drew's instruction 2026-06-11.
6. **Git workflow = WSL-commit / GitHub-Desktop-push (decided 2026-06-13).** The clone lives on ext4 in WSL (H2). Claude makes commits *in WSL* (local, auth-free — only name/email needed). The user reviews and **pushes/pulls with GitHub Desktop on Windows**, pointed at the repo over `\\wsl.localhost\Ubuntu-24.04\home\musashi\bfm-decomp`. So **no git credentials are configured in WSL** and **`git push` is never run from the WSL CLI** (it would prompt for auth that isn't set up) — pushing is GitHub Desktop's job. `core.filemode=false` is set in the clone to avoid cross-OS mode churn (supersedes the `core.filemode true` line in docs/SETUP.md §4.3 for this topology). `gh` is installed but unused for auth.

To formalize in `PhaseEnd_Phase1.md` under "Rules Added" (P10): the H1 relaxation, the all-in-WSL H2 restatement, tools-in-`tools/`, plan-mode-per-phase, no-commit-co-author, and the WSL-commit/GitHub-Desktop-push workflow.

---

## Verified facts (this session)

- **Install assets confirmed (web):** Ghidra `ghidra_12.1_PUBLIC_20260513.zip` (pin 12.1 exactly — 12.1.2 exists since 2026-06-05 but extensions only ship 12.1 assets); JDK 21 Temurin; GhidrAssistMCP v2.8.0 (`ghidra_12.1_PUBLIC_20260530_GhidrAssistMCP.zip`); ghidra_psx_ldr 2026.06.04 (`ghidra_12.1_PUBLIC_20260604_ghidra_psx_ldr.zip`). Extension assets are platform-independent Java → same filenames on Linux Ghidra.
- **Disc integrity (redump):** Track-1 SHA1 `b44f0f0a19936f23b26188b658e13201a6a9c211`, CRC32 `c238191b`, build date **1998-08-25**. The `SLUS_007.26` EXE hash is not publicly documented (expected); our extractor produces SHA1 `143dbb89f34491258bbc27810d0a12ec8b43a8dd` (413,696 bytes), independently reproduced from raw sectors. `--verify-disc` checks Track-1 vs redump as the canonical proof.
- **PsyQ stamps (EXE scan):** 12 genuine — 9× 4.0 (libnums 2,3,4,6,7,8,9,17,24), 1× 4.0.1x (16), 1× 4.2 (0), 1× 4.2.1x (12). ⇒ GCC 2.7.2 family. ghidra_psx_ldr detection at import is the final word.

---

## Task checklist (approved plan)

### A. Finalize repo, then hand off to WSL (this Windows session) — COMPLETE
- [x] Extractor `tools/bfm_extract` built + adversarially verified (done early)
- [x] Constitution surgical correction (PROJECT_CONTEXT.md env sections → all-in-WSL + H1 note)
- [x] `.gitignore` H1 relaxation (un-ignore asm/ assets/ extracted/ *.CD.dir; keep dump + build churn ignored)
- [x] `docs/SETUP.md` → Linux-first (verified pass; all facts preserved; redump disc-provenance added)
- [x] Extractor hardening + `--verify-disc` (PASS: Track-1 SHA1 == redump b44f0f0a…)
- [x] Root research-file cleanup → `docs/history/` (+ SUPERSEDED banner on starting-point doc)
- [x] Commit per task (clean handoff) — section-A commits on `main`, not yet pushed (push from WSL where auth works)

### B. Migrate to WSL (collaborative — user relaunches Claude Code in WSL)

**B0. WSL environment bootstrap — DONE 2026-06-13 (from the Windows session, after the user enabled BIOS virtualization):**
- [x] WSL2 confirmed healthy (v2.7.8.0, kernel 6.18, WSLg present, default v2) — but **no distro was installed**; that was the gap the BIOS change exposed
- [x] `Ubuntu-24.04` installed (24.04.4 LTS "Noble") as the default WSL2 distro (`--no-launch`, no interactive first-run)
- [x] User `musashi` created (uid 1000): passwordless sudo via `/etc/sudoers.d/90-musashi` (visudo-validated), set as default login user via `/etc/wsl.conf` `[user] default=musashi`
- [x] Git identity set global: `user.name=Drew T`, `user.email=50529377+Druthulu@users.noreply.github.com`, `init.defaultBranch=main`; `gh` 2.45.0 + `unzip` 6.0 installed
- [x] Claude Code 2.1.177 installed (native installer → `~/.local/bin/claude`; `~/.local/bin` appended to `~/.bashrc` PATH; `claude --version` resolves in a fresh interactive shell)
- [ ] **USER — interactive: run `claude` in a WSL terminal → sign into Anthropic** (OAuth code/paste flow). Git needs no WSL auth — push/pull is GitHub Desktop on Windows (see correction #6).

**B1. Establish the clone + sync:**
- [x] Seeded `~/bfm-decomp` (ext4, `/dev/sdd`) from the **local Windows repo** (`git clone /mnt/z/Storage/git/BFM-decomp ~/bfm-decomp`; HEAD up to date with this log). `origin` re-pointed to `https://github.com/Druthulu/BFM-decomp.git`; `core.filemode=false` set. **First push is via GitHub Desktop on Windows** (Add Local Repository → `\\wsl.localhost\Ubuntu-24.04\home\musashi\bfm-decomp` → Push), NOT `git push` from WSL.
- [ ] Make the dump available in `disks/` (one-shot copy onto ext4 — the dump is not in the repo)
- [ ] Relaunch Claude Code inside WSL (in `~/bfm-decomp`); this Windows session ends
- [ ] Install RE stack in WSL (JDK 21, Ghidra 12.1, ghidra_psx_ldr, GhidrAssistMCP); start MCP server

### C. First import + milestone (in WSL)
- [ ] Run extractor → `extracted/SLUS_007.26`; `--verify-disc` PASS (Track-1 == redump)
- [ ] Import into Ghidra (WSLg): PSX loader, auto-analyze + PsyQ signatures, record PsyQ version, attach `psyq400.gdt`, MCP type-resolution test
- [ ] MCP round-trip: `/mcp` ~38 tools; `get_binary_info`; decompile `0x80018730`
- [ ] **MILESTONE:** MCP decompile of `0x80018730` ≈ LZSS decompressor; PsyQ version recorded → user confirm → `PhaseEnd_Phase1.md`

## Next task
**Section B — migrate to WSL (bootstrap + clone done; sign-in + relaunch next).** The WSL2 environment is up and `~/bfm-decomp` is cloned on ext4 with `origin`→GitHub (B0/B1). Remaining: the user signs into Anthropic by running `claude` in a WSL terminal (git needs no WSL auth — GitHub Desktop on Windows pushes, correction #6); push the current commits once via GitHub Desktop; copy the dump into `disks/`; relaunch Claude Code inside `~/bfm-decomp`; then install the RE stack per docs/SETUP.md §2. Resume from this log inside the WSL clone.

## Blockers / needs-user
- **Anthropic sign-in (only the user can do this):** run `claude` in a WSL terminal → sign in (OAuth code/paste flow). Git needs no WSL auth.
- **GitHub Desktop (Windows):** Add Local Repository → `\\wsl.localhost\Ubuntu-24.04\home\musashi\bfm-decomp` → Push to sync. If it warns "unsafe / dubious ownership," accept its one-click fix (Git-for-Windows `safe.directory`).
- Confirm the GitHub repo `Druthulu/BFM-decomp` is set to **Private** before any push.
- RE-stack install + EXE import (Section C) require driving Ghidra's WSLg GUI; do them from the in-WSL Claude session.
