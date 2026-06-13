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
- [x] **USER — sign into Anthropic in WSL** — DONE: this session IS Claude Code running signed-in inside the WSL clone. Git needs no WSL auth — push/pull is GitHub Desktop on Windows (correction #6).

**B1. Establish the clone + sync:**
- [x] Seeded `~/bfm-decomp` (ext4, `/dev/sdd`) from the **local Windows repo** (`git clone /mnt/z/Storage/git/BFM-decomp ~/bfm-decomp`; HEAD up to date with this log). `origin` re-pointed to `https://github.com/Druthulu/BFM-decomp.git`; `core.filemode=false` set. **First push is via GitHub Desktop on Windows** (Add Local Repository → `\\wsl.localhost\Ubuntu-24.04\home\musashi\bfm-decomp` → Push), NOT `git push` from WSL.
- [ ] Make the dump available in `disks/` (one-shot copy onto ext4) — **NOT needed for the milestone**: the EXE is already extracted + committed + sha1-verified (`143dbb89…`). Only needed to re-run `--verify-disc` (Track-1 vs redump) inside WSL.
- [x] Relaunch Claude Code inside WSL — DONE (this session runs in `~/bfm-decomp` on ext4 `/dev/sdd`)
- [x] Install RE stack in WSL — **DONE 2026-06-13** (this session): JDK 21.0.11; Ghidra 12.1 PUBLIC at `~/ghidra_12.1_PUBLIC` (zip integrity-verified, 6693 files); both extensions extracted into `~/ghidra_12.1_PUBLIC/Ghidra/Extensions/` at `version=12.1` (GhidrAssistMCP v2.8.0, ghidra_psx_ldr 2026.06.04); headless GhidrAssistMCP server starts on 127.0.0.1:8080 with **41 tools**.

### C. First import + milestone (in WSL)
- [x] EXE present at `extracted/SLUS_007.26` (sha1 `143dbb89f34491258bbc27810d0a12ec8b43a8dd`, 413,696 bytes, "PS-X EXE" magic). `--verify-disc` re-run in WSL is **pending the dump copy** (it PASSED on Windows: Track-1 == redump `b44f0f0a…`).
- [x] Imported into Ghidra (**headless** `analyzeHeadless`, not WSLg GUI): PSX loader auto-selected (`PSX:LE:32:default`), auto-analysis + PsyQ Signatures ran (177 s), **PsyQ Version = 4.0.0 recorded** (DetectPsyQ), 1726 functions, program saved to `ghidra/bfm.{gpr,rep}`. **PENDING (GUI-only):** `.gdt` attach (`psyq400.gdt`) + MCP type-resolution test (ledger #2) — no headless/MCP path opens a `.gdt` archive.
- [x] MCP round-trip **verified via raw JSON-RPC over the live server** (curl): `tools/list` = 41 tools; `get_binary_info` → SLUS_007.26 / 1726 funcs; `get_code(0x80018730, decompiler)` → LZSS code. **PENDING:** the *literal* in-Claude-Code-session round-trip needs a `/mcp` reconnect (server came up after this session started, so `mcp__ghidra__*` aren't live in-session yet).
- [~] **MILESTONE — substance proven, gate pending user.** `0x80018730` decompiles to the documented LZSS streaming decompressor (scratchpad ring @ `0x1F800000`, 0x3ff window mask, resumable state machine via `DAT_800c7d24`, `pos==0` terminator), confirmed via BOTH Ghidra headless decompiler AND the MCP `get_code` tool; PsyQ 4.0.0 recorded. Awaiting: user confirmation (P8 gate), and a decision on the `/mcp` reconnect + GUI `.gdt` step (see Next task).

## Next task
**Close Phase 1 (milestone gate).** The RE stack is installed, the EXE is imported+analyzed (PsyQ 4.0.0, 1726 funcs), and the LZSS decompile at `0x80018730` is proven via both the headless decompiler and the live MCP `get_code` tool. Two touches remain before the gate, and they hinge on a user choice (the headless MCP server currently holds the `bfm.rep` project lock, so the GUI can't open it until that server is stopped):

- **(literal milestone) `/mcp` reconnect** — run `/mcp` in this session so the `ghidra` server connects (it's listening now); then a real `mcp__ghidra__*` decompile of `0x80018730` closes the milestone wording exactly. *(Keep the headless server running for this.)*
- **(checklist item, GUI-only) `.gdt` attach + MCP type-resolution test (ledger #2)** — needs the Ghidra GUI under WSLg: stop the headless server, launch `ghidraRun`, open `bfm`, attach `psyq400.gdt`, confirm the GhidrAssistMCP panel on 8080, then `/mcp` reconnect and run the type-resolution test. This GUI session also becomes the documented steady-state (SETUP.md §7).

Recommendation queued for the user (see chat): do the one GUI session — it delivers the literal in-session MCP round-trip AND the `.gdt`/type test in one go, fully clearing the Phase 1 checklist. Alternatively, defer `.gdt` (record a deviation) and close on the headless-proven milestone now.

## Blockers / needs-user
- **Milestone gate (P8):** user confirms the milestone (LZSS decompile + PsyQ version) before `PhaseEnd_Phase1.md` is written.
- **`/mcp` reconnect** (trivial, in this session) for the literal Claude-Code MCP round-trip — server is live on 127.0.0.1:8080.
- **`.gdt` attach + type-resolution test** — GUI-only; requires stopping the headless MCP server (it locks `bfm.rep`) and driving `ghidraRun` under WSLg.
- **GitHub Desktop (Windows):** Add Local Repository → `\\wsl.localhost\Ubuntu-24.04\home\musashi\bfm-decomp` → Push. If it warns "unsafe / dubious ownership," accept its one-click fix.
- Confirm the GitHub repo `Druthulu/BFM-decomp` is **Private** before any push.
- (optional) Copy the disc dump into `disks/` to re-run `--verify-disc` in WSL — not required for the milestone.

## WSL session log — 2026-06-13 (RE stack live + headless import + milestone substance)
- **Installs:** JDK 21.0.11 (apt). Ghidra 12.1 PUBLIC (`ghidra_12.1_PUBLIC_20260513.zip`, 567 MB, central-dir verified) → `~/ghidra_12.1_PUBLIC`. Extensions extracted into `Ghidra/Extensions/`: GhidrAssistMCP v2.8.0 (`…20260530…`), ghidra_psx_ldr 2026.06.04 (`…20260604…`), both `version=12.1` (no version-lock issue — exact 12.1 pin held).
- **Import:** `analyzeHeadless ~/bfm-decomp/ghidra bfm -import extracted/SLUS_007.26` (auto-detect loader). Loader = **PSX Executables Loader**, lang `PSX:LE:32:default`, ImageBase `80000000`, Min/Max addr `1f800000`/`801fffff`, **1726 functions**, analysis 177 s, **PsyQ Version = 4.0.0** (resolves ledger #12 / confirms §2.5 step 3). Saved to `ghidra/bfm.{gpr,rep}` (gitignored).
- **MCP:** headless server (`-process SLUS_007.26 -preScript GAMCPStartServerScript.java host=127.0.0.1 port=8080 wait=true`) → "started on port 8080 … with **41 tools**". JSON-RPC over `/mcp` verified: `initialize`/`tools/list`/`get_binary_info` ok; `get_code(0x80018730, decompiler)` returns the LZSS decompressor. **Note:** `get_code` (and likely other heavy tools) run **async** — return a `task_id`; poll `get_task_status`. Wire format is SSE (`event: message` / `data: {json}`).
- **SETUP.md corrections recorded** (see commit): headless `-loader "PSX Executables Loader"` is rejected (`InvalidInputException`) — use loader auto-detect; tool count is 41 (not ~38); async task pattern for `get_code`; extensions install by extracting into `<install>/Ghidra/Extensions/`.
- **Helper scripts added:** `tools/ghidra_scripts/DumpProgramInfo.java`, `DecompileAt.java`.
