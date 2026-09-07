# SETUP.md — Environment Setup & Daily Operations Reference

> **This file is the EVOLVABLE reference layer.** Unlike `PROJECT_CONTEXT.md` (permanent, never edited), this document holds volatile facts — pinned versions, URLs, commands, ports — and **may be updated freely** as tools move. Note each change in the active phase log (`CURRENT_PHASE.md`). Items marked **TBD** / **UNVERIFIED** / **JP-only — re-derive for US** are honest gaps: confirm before relying on them, then update this file.

Last full revision: 2026-06-10 (initial authoring, pre-Phase-1 — nothing below is installed yet except the repo itself; same-day conversion to the all-in-WSL / Linux-first architecture — everything now runs inside a single WSL2 Ubuntu 24.04 clone, no Windows/WSL split).
**Refresh 2026-09-07 (P33 D4, the public-clean pass):** the repository is PUBLIC from Phase 33 (in-place flip with the full, rewritten history — `docs/public-flip-runbook.md`); H1 is in force again (no ROM-derived bytes in git); every "private repo / vendored / mirror" passage below was reviewed and rewritten or dated as history; the canonical remote is `https://github.com/Druthulu/BFM-decomp.git`.
**Refresh 2026-06-15:** added a tooling/MCP-lifecycle/session-hooks/backup-posture pass after the doc had drifted past the as-built reality — new §1a (`.run/` scratch), §2.8 (MCP lifecycle, persistence model & session hooks), a `## Tooling inventory` table, and a `## Backup & private-repo posture` section. Rule **R21** (added this session) now requires keeping THIS file current whenever tooling / MCP / hooks / env change.

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
| maspsx | git submodule, `mkst/maspsx` (decomp.me pins commit `874855c53f65f8fa57447e1da6bde6236dbef9d5` — reasonable default pin) | WSL2 (Linux) | 4 |
| asm-differ / m2c / decomp-permuter | git submodules (URLs in §4.6) | WSL2 (Linux) | 4 |
| binutils (mipsel) | apt `binutils-mipsel-linux-gnu` — **as-built 2.42** (Phase 4; ≥2.38 → check-env WARN, verdict deferred to Phase 5), 2.35 known-good | WSL2 (Linux) | 4 |

---

## §1 The all-in-WSL environment (single ext4 clone)

```
┌─ WSL2 Ubuntu 24.04 (ext4) — everything lives here ──────────────────────────┐
│                                                                             │
│  ~/bfm-decomp          ← THE clone (one git working tree, one remote)        │
│   ├─ Ghidra 12.1 PUBLIC  (JDK 21 Temurin, GUI via WSLg)                      │
│   │   ├─ ghidra_psx_ldr 2026.06.04 (PSX loader, PsyQ signatures,            │
│   │   │   .gdt type archives)                                               │
│   │   └─ GhidrAssistMCP v2.8.0 ── SSE 127.0.0.1:8080 (local to WSL)         │
│   │                                                                         │
│   ├─ Ghidra project .gpr/.rep (under ~/bfm-decomp or ~/.ghidra)             │
│   ├─ PCSX-Redux (Linux build: runtime oracle — debugger, Lua,              │
│   │   web API RAM dumps, GDB server :3333)                                  │
│   ├─ Claude Code ← .mcp.json → 127.0.0.1:8080/sse (same box, no boundary)   │
│   │                                                                         │
│   ├─ .venv/            splat64[mips] etc.                                    │
│   ├─ tools/maspsx, tools/asm-differ, tools/m2c, tools/decomp-permuter (subm.)│
│   ├─ tools/bin/gcc-2.7.2-psx, tools/bin/gcc-2.7.2-cdk                       │
│   │   (old-gcc 0.17, Linux x86-64 binaries)                                 │
│   ├─ disks/             BIN/CUE dump, copied in ONCE (gitignored)           │
│   └─ asm/ build/ expected/  (generated, never committed)                     │
│                                                                             │
│  apt: binutils/gcc-mipsel-linux-gnu, make, ninja, python3.12, JDK 21, ...   │
└───────────────────────────────────┬─────────────────────────────────────────┘
                                    │
                                    └── git remote (push/pull off-box only) ──►
```

One repository clone on ext4 at `~/bfm-decomp` holds everything — RE stack, build toolchain, runtime oracle, docs, and Claude Code's working directory. There is **no Windows/WSL split**: no second clone, no cross-OS working-tree edits, no `/mnt` build path. The git remote is used only to push/pull off the machine (backup, collaboration), never to synchronize two local trees. Rationale for keeping the clone on ext4 (not on a `/mnt/*` drvfs mount):

- **9P filesystem penalty.** File access on `/mnt/*` drvfs mounts goes through the Plan 9 protocol and is the slowest path WSL2 offers — Microsoft's own numbers put ext4 at 2–20× faster, and community benchmarks measured builds up to 375% faster after moving off `/mnt`. Every `make`, `git status`, and splat extract pays the tax if the build tree sits on a mounted Windows drive. Keeping the clone on ext4 sidesteps this entirely.
- **inotify works on ext4.** Linux file-watchers get no events for changes on `/mnt/*` drvfs mounts (microsoft/WSL [#4739](https://github.com/microsoft/WSL/issues/4739), [#5424](https://github.com/microsoft/WSL/issues/5424)). asm-differ watch mode fires reliably only when source *and* build outputs live on ext4 — which, all-in-WSL, they always do.
- **No ghost-file hazard.** anthropics/claude-code [#28015](https://github.com/anthropics/claude-code/issues/28015): Write/Edit on WSL2 drvfs mounts can hit a statx/9P cache-poisoning kernel bug producing "ghost files" (ENOENT for files that exist). Editing only on ext4 avoids the bug; Claude Code runs inside WSL and never touches a drvfs path.

One-shot file copies onto ext4 (e.g. the disc dump into `disks/`) from any source are fine — it is sustained/random IO and watchers on drvfs that break, not correctness. Ghidra project files (`.gpr`/`.rep`) live on ext4 alongside the clone (or under `~/.ghidra`), consistent with Ghidra's local-drive-storage recommendation; their `~lock` files behave correctly on a native Linux filesystem.

Git hygiene: the committed `.gitattributes` (`* text=auto eol=lf` + binary exclusions) keeps line endings consistent. On the Linux clone `core.filemode true` is fine (ext4) and `core.autocrlf` is `false` by default (LF-native), so no line-ending dance is needed.

### §1a Runtime scratch (`.run/`, rule R12)

Gitignored project-local scratch directory at `~/bfm-decomp/.run/` — the standing replacement for `/tmp` (rule R12: never write to `/tmp`; all runtime data is project-local). Holds purely regenerable transients: the headless MCP server log (`ghidra-mcp.log`), the clean-shutdown sentinel (`mcp-stop.req`, see §2.8), signature dumps (`sig.*.jsonl`, produced by `make sig-refresh`), decomp-permuter scratch (`.run/permuter/`), build/extract logs, and assorted `tmp*` working files. Everything here is regenerated on demand and **never committed** — the directory exists only so no working data ever lands in `/tmp` or pollutes the tree.

---

## §2 RE stack install (Phase 1, all in WSL)

Order matters: JDK → Ghidra → both extensions → import → MCP wiring.

### §2.1 JDK 21 (Temurin)

```bash
sudo apt-get update && sudo apt-get install -y openjdk-21-jdk
```

Required by Ghidra 12.x. (The Temurin apt repo — `https://packages.adoptium.net` — is an equivalent alternative if you prefer Temurin specifically.) Verify: `java -version` reports 21.x, and ensure it is the JDK on `PATH` for the shell that launches Ghidra (`ghidraRun` needs JDK 21 visible).

### §2.2 Ghidra 12.1 PUBLIC — pin EXACTLY

Download **`ghidra_12.1_PUBLIC_20260513.zip`** from
`https://github.com/NationalSecurityAgency/ghidra/releases/tag/Ghidra_12.1_build` — plain zip, no installer; the same cross-platform Java distribution on every OS. Unzip and launch the GUI under WSLg:

```bash
cd ~ && unzip ghidra_12.1_PUBLIC_20260513.zip
~/ghidra_12.1_PUBLIC/ghidraRun      # WSLg supplies the X11/Wayland display
```

`./ghidraRun` needs JDK 21 on `PATH` (§2.1); the Ghidra GUI renders through WSLg with no extra X-server setup.

> ⚠️ **Extension version-lock warning.** Ghidra extensions are point-version-locked via `extension.properties`. Both extension zips below are built against `12.1_PUBLIC`; installing them on 12.1.2 (current latest, 2026-06-05) may trip the version check (red "incompatible" flag — same failure mode as LaurieWired issue #83 on 11.4.1). Whether the 12.1 zips happen to load on 12.1.2 is **UNVERIFIED** — pin **12.1**, and only move to a point release when both extensions ship matching assets or you rebuild them from source (`gradle installExtension` with `GHIDRA_INSTALL_DIR` set). The extension assets are platform-independent Java (`ghidra_12.1_PUBLIC_..._GhidrAssistMCP.zip` / `..._ghidra_psx_ldr.zip` — the "12.1" is the Ghidra version, not the OS), so the same asset filenames install on Linux Ghidra 12.1.

### §2.3 GhidrAssistMCP v2.8.0

- Asset for our Ghidra: **`ghidra_12.1_PUBLIC_20260530_GhidrAssistMCP.zip`** from
  `https://github.com/symgraph/GhidrAssistMCP/releases/tag/2.8.0`
  (repo moved from `jtang613/GhidrAssistMCP` to `symgraph/GhidrAssistMCP`; GitHub redirects. The release carries TWO assets — take the `12.1` one, not `12.0`.)
- **Verify the download (P33 C3):** the copy this project used was tracked as `tools/ghidra-ext/GhidrAssistMCP_2.8.0.zip`
  until 2026-09-06 and is now download-only (gitignored): sha256
  `983e2add88d70552596dc3160c1ece52ca6ba8ac006c6c61446a780696815dc1` (16,462,609 bytes) — `sha256sum` your copy.
- Install: Ghidra → **File → Install Extensions… → `+`** → select zip → restart Ghidra.
- Enable plugin: **File → Configure → Configure Plugins → check `GhidrAssistMCP`**.
- Control panel: **Window → GhidrAssistMCP** → set **Host = localhost, Port = 8080**. Server exposes `/sse` (SSE), `/message`, and `/mcp` (streamable HTTP). No Python bridge process — Claude Code connects directly.
- This is the server the psxrecomp proof-of-concept actually ran with Claude Code (their port was 7777, a user setting; we standardize on 8080 to match the committed `.mcp.json`).

**Fallbacks (documented, not installed):**

| Server | Status | Why fallback only |
|---|---|---|
| bethington/ghidra-mcp v5.13.x | active, claims Ghidra 12.1, 249 tools | Unaudited, single-maintainer with day-apart releases, needs a Python bridge (plugin HTTP :8089), 249 tools swamp Claude's tool context. Consider only if a missing niche tool (mass `create_enum`, `batch_decompile`) becomes a bottleneck. |
| clearbluejar/pyghidra-mcp | active, pip/uvx, headless multi-binary | **No struct-creation or apply-type-at-address tools** — dead end as primary server for matching-decomp data work; fine for scripted headless batch passes. |
| LaurieWired/GhidraMCP 1.4 | **unmaintained — DO NOT INSTALL** | Caps at Ghidra 11.3.2 (issues #83/#131 open, no fix since 2025-06-23); ghidra_psx_ldr dropped 11.x. Older write-ups (including the 1379.tech psxrecomp blog post) credit it incorrectly. |
| ismaelcaraballo-afk/GhidraMCP-12 | stale one-off recompile | 12.0.1 only, no struct tools, not viable. |

### §2.4 ghidra_psx_ldr release 2026.06.04

- Asset: **`ghidra_12.1_PUBLIC_20260604_ghidra_psx_ldr.zip`** (~9.15 MB, PsyQ signatures bundled — no separate OBJ download needed) from
  `https://github.com/lab313ru/ghidra_psx_ldr/releases/tag/2026.06.04`
- **Verify the download (P33 C3):** tracked as `tools/ghidra-ext/ghidra_psx_ldr_2026.06.04.zip` until 2026-09-06, now
  download-only (gitignored): sha256 `dc57cf1ad126c717f69be63f777d747c9cc0af3b2f833af83eeeac644f8e7c11` (9,155,980 bytes).
- Install via the same **File → Install Extensions…** path → restart.
- Coexists with GhidrAssistMCP without conflicts (PSX loader/analyzer/SLEIGH vs HTTP-server plugin).

### §2.5 PSX-EXE import flow (SLUS_007.26)

1. Extract `SLUS_007.26` from the disc image (LBA 24, 0x65000 bytes, track 1 is MODE2/2352) and import into Ghidra. The loader auto-selects **"PSX Executables Loader"**, language `PSX:LE:32:default`, and builds the full PS1 memory map: RAM around the image at 0x80000000, scratchpad 0x1F800000, all IO/DMA/timer/CD/GPU/SPU register blocks, **and a synthetic GTEMAC segment at 0x20000000 automatically** — do NOT run the `CreateGteMacSegment` script (that is only for migrating legacy non-PSX projects).
2. Run auto-analysis with the **"PsyQ Signatures"** analyzer enabled (auto-enabled for PSX-language programs). Analyzer options: "Only first match", "Minimal signature entropy" (default 3.0 — can skip tiny low-entropy library stubs), "PsyQ Version if not found" (manual override).
3. Read the detected PsyQ version: **Edit → Options for Program → Program Information → "PsyQ Version"**. Expected: **4.0** (our own EXE scan found 12 genuine `Ps` stamps: 9× 4.0, one 4.0.1x on libnum 16, one 4.2 on libnum 0, one 4.2.1x on libnum 12 — i.e. PsyQ 4.0 libs + 4.2 library updates; see §5.1). If detection errors with `'psyq/xx' cannot be found`, append `.0` to the version field. Record the detected value in the phase log. **CONFIRMED 2026-06-13 (Phase 1):** DetectPsyQ at headless import recorded `PsyQ Version = 4.0.0` on the extracted US EXE (resolves ledger #12). Import also reported: loader `PSX Executables Loader`, language `PSX:LE:32:default`, ImageBase `80000000`, address range `1f800000–801fffff`, 1726 functions, ~177 s analysis.
   *(Note: a raw track-1 scan during research reported slightly different per-libnum details — raw 2352-byte-sector scans produce false positives; the extracted-EXE scan is the ground truth, and DetectPsyQ at import is the final word.)*
4. **One-time manual `.gdt` attach (GUI only — no MCP tool opens archives):** in the CodeBrowser Data Type Manager, attach the bundled PsyQ type archive for the detected version — `psyq400.gdt` (`psyq420.gdt` also exists). This gives PsyQ struct/typedef types for retyping work.
5. **Early MCP type-resolution test (run before any bulk typing):** via MCP, run the `types` tool with `action=set` applying a PsyQ type (e.g. apply a known PsyQ struct at some address) and confirm it resolves. **RESOLVED 2026-06-13 (Phase 1) — answer: import the types into the program.** The `.gdt` attach is doable **headlessly** (no GUI needed) via `tools/ghidra_scripts/ImportPsyqGdt.java`, which opens `psyq400.gdt` as a `FileDataTypeManager` and `resolve()`s all its types into the program's DataTypeManager — this both copies the types in **and** registers `psyq400` as a SourceArchive. After that, the MCP `types` tool fully resolves them: `types action=list filter=DRAWENV` and `types action=get name=DRAWENV` return the complete struct (`DRAWENV` [/LIBGPU.H], 92 bytes, all fields incl. `RECT`/`DR_ENV`), and `SVECTOR` [/LIBGTE.H]. psyq400.gdt carries **2599 types** (program DTM went 205 → 2609). **Takeaway for the typing workflow:** don't rely on a bare archive *attachment* — import (resolve) the PsyQ types into the program once, and all MCP type/struct tools see them. The bundled archives live at `<ghidra>/Ghidra/Extensions/ghidra_psx_ldr/data/psyq*.gdt` (psyq400.gdt for our SDK).

### §2.6 `.mcp.json` wiring + verification

The committed repo-root `.mcp.json` (already present):

```json
{
  "mcpServers": {
    "ghidra": {
      "type": "sse",
      "url": "http://127.0.0.1:8080/sse"
    }
  }
}
```

Single `ghidra` entry only — do NOT copy psxrecomp's duplicated `ghidra` + `ghidra_psx` pair (same URL twice = every tool duplicated in context).

Verify in Claude Code with `/mcp`: **~38–41 `mcp__ghidra__*` tools** should appear. *(CONFIRMED 2026-06-13: GhidrAssistMCP v2.8.0 reports **41 tools** headless. Operational notes from Phase 1: tool responses come back as SSE frames (`event: message` / `data: {json}`) on the streamable `/mcp` endpoint; heavy tools like `get_code` run **asynchronously** — the `tools/call` returns a `task_id` and you must poll `get_task_status` for the result. `get_code` takes `{function: "0x80018730", format: "decompiler|disassembly|pcode"}`.)* These are the **v2.8.0 names** — e.g. `get_binary_info`, `get_code` (format: disassembly|decompiler), `disassemble_at`, `analyze_function`, `xrefs`, `get_functions` (paginated), `struct` (actions: create/modify/merge/set_field/name_gap/auto_create/rename_field/field_xrefs), `types` (list/get_info/set/delete), `variables` (list/rename/set_type/set_prototype), `rename_symbol`, `batch_rename`, `create_data_var`, `create_function`, `search_bytes`, `patch_bytes`, `assemble_code`, `export_program`. **NOT the pre-2.4.0 names** (`get_function_info`, `list_data`) that appear in psxrecomp's PLAN.md and older write-ups — those were renamed in v2.4.0 (upstream commit `aa3ffc7d`, 2026-03-14).

Operational cautions:
- Tools operate on the program currently open in CodeBrowser and fail (sometimes silently) if none is open.
- Do not run Ghidra auto-analysis concurrently with MCP-driven writes (renames/comments) — both mutate the program DB and can stall each other.

### §2.7 Headless mode (batch passes)

For unattended batch passes, GhidrAssistMCP runs headless (supported since v2.3.0):

```bash
<ghidra>/support/analyzeHeadless <projects-dir> McpHeadless \
  -import <binary> \
  -scriptPath "<extension-dir>/ghidra_scripts" \
  -preScript GAMCPStartServerScript.java "host=127.0.0.1" "port=8080" "wait=true"
```

- **`wait=true` is mandatory** — without it the analyzeHeadless process exits right after the prescript instead of serving MCP clients.
- On subsequent runs use **`-process SLUS_007.26`** (not `-import`) to reuse the existing project. Pair with **`-noanalysis`** so it doesn't re-run analysis on every server start.
- **CONFIRMED 2026-06-13:** this headless flow works end-to-end (server "started on port 8080 … with 41 tools"; `get_binary_info` and `get_code` operate on the `-process` program). **The headless server holds the project `.rep` lock while serving** — stop it (cancel the analyzeHeadless process) before opening the same project in the GUI.
- **Extension install (headless-compatible):** extract each extension zip into `<GHIDRA_INSTALL_DIR>/Ghidra/Extensions/` (e.g. `unzip ext.zip -d ~/ghidra_12.1_PUBLIC/Ghidra/Extensions/`). Both GUI and `analyzeHeadless` then load the extracted module dirs (no GUI "Install Extensions" step needed). Verified for GhidrAssistMCP + ghidra_psx_ldr on Ghidra 12.1.
- **Loader selection in headless:** `-loader "PSX Executables Loader"` is **rejected** (`InvalidInputException: Invalid loader name specified`) even though that is the loader's display name. **Omit `-loader` and let auto-detection pick** — for a real `PS-X EXE` it correctly selects "PSX Executables Loader" over Raw Binary (log line: `Using Loader: PSX Executables Loader`).

### §2.8 MCP server lifecycle, persistence model & session hooks

We drive RE through our own headless MCP server, `tools/ghidra_scripts/BfmMcpServer.java`, run under `analyzeHeadless` (the §2.7 flow). **Persistence model — read this before doing RE:** the server holds an **OPEN TRANSACTION** the entire time it serves, so there is **NO mid-session save** — MCP writes (renames, retypes, comments, structs) live in RAM and are flushed to the program DB **only on a clean shutdown**. A hard crash (or `SIGKILL`) loses every RAM-only write since the last clean stop. Therefore: take **clean-stop checkpoints during long RE** rather than trusting a single save at the end.

Lifecycle scripts (under `tools/`):

- **`ghidra_mcp_start.sh`** — spawns the headless server detached, logging to `.run/ghidra-mcp.log`, serving on port **8080**.
- **`ghidra_mcp_stop.sh`** — the **only persistence event**: it requests a clean save+close by dropping the `.run/mcp-stop.req` sentinel, waits for the server to report **"Save succeeded"**, then releases the project `.rep` lock. **Never `SIGKILL` the server to stop it** — that skips the save and loses the work. Clean stop is the save.
- **`ghidra_mcp_verify.sh <addr> <name>`** — read-only persistence re-check (rule R9): after a clean stop, re-reads the named symbol at the address to confirm the write actually landed on disk.

**Client reconnect after a server restart (operational, Phase 13).** Restarting the server (`stop` then `start` — e.g. for a headless raw-blob import per R23, or to serve a different program) **drops the Claude Code MCP client's SSE connection**: every `mcp__ghidra__*` call then **times out** until the client reconnects, and Claude **cannot** run `/mcp` itself. So the rhythm after any server restart / program switch is: **pause and ask Drew to run `/mcp`**, then make one cheap `get_binary_info` call (G2) before continuing. Do not try the calls, hit timeouts, and work around them. (Memory: `mcp-reconnect-after-restart`.)

**Session hooks (committed `.claude/settings.json`, as of 2026-06-15):**

- `SessionStart` → runs `bash "$CLAUDE_PROJECT_DIR"/tools/ghidra_mcp_start.sh` (auto-starts the MCP server when a Claude Code session begins; **P33 B5:** repo-relative, and the script is a silent `exit 0` when `$GHIDRA/support/analyzeHeadless` or `ghidra/bfm.rep` is absent — a contributor's clone has neither).
- `SessionEnd` → runs `bash "$CLAUDE_PROJECT_DIR"/tools/ghidra_mcp_stop.sh` with **`timeout: 150`** s (auto-saves Ghidra on a clean session exit; a no-op when nothing serves on :8080).

These hooks live in the **committed `settings.json`** — NOT the gitignored `settings.local.json` — specifically so they are backed up to the remote. Consequence to internalize: **closing Claude Code does NOT save unless the `SessionEnd` hook fires**, and it fires only on *clean* exits — a hard crash of the CC process still loses RAM-only writes. This is exactly why mid-RE clean-stop checkpoints matter.

**Committing Ghidra RE work:** clean-stop (which saves) **FIRST**, then commit `ghidra/`. The `.rep` lock never blocks git (the lock is gitignored, and ext4 reads open files fine), but do **not** commit `ghidra/` mid-RE — that snapshots a stale on-disk DB that predates the in-RAM writes.

---

## §3 PCSX-Redux (Linux) — the runtime oracle

**Role:** Ghidra is the static oracle; PCSX-Redux is the **runtime oracle**. It proves overlay load addresses by live RAM comparison, validates decompressed blobs byte-for-byte against what the game actually loads, and drives the debug-menu/loader RE.

- **Install:** Linux AppImage from `https://distrib.app/pub/org/pcsx-redux/project/dev-linux-x64` (no stable pin — record the build date). **As-built (2026-06-13):** `tools/pcsx-redux/PCSX-Redux-HEAD-x86_64.AppImage` (87.5 MB, ELF static-pie, BuildID `db3b55ac…`). **distrib.app is a JS SPA — not curl-able headlessly** (the `dev-linux-x64` URL returns only an HTML shell; the real file is numeric-ID-gated); download via a browser. Runs directly under WSLg (FUSE 3.14.0 present; no `--appimage-extract` needed). Docs: `https://pcsx-redux.consoledev.net`. Ships OpenBIOS (boots without a retail BIOS dump). Launch with disc + auto-run: `./tools/pcsx-redux/PCSX-Redux-HEAD-x86_64.AppImage -iso "<cue>" -run`.
- **RAM dumps (primary use):** enable the built-in web server, then
  **`GET http://127.0.0.1:8081/api/v1/cpu/ram/raw`** returns the full 2 MB RAM image — diff slices of it against our extractor's output to prove byte-identity. (Port **8081**, resolved at Phase 3 install — ledger #4 — moved off 8080 to avoid the GhidrAssistMCP collision. **Verified 2026-06-13:** returns exactly 2,097,152 B; RAM[0x10000:] == extracted `SLUS_007.26`[0x800:] byte-for-byte.)
  > ✅ **Port collision (RESOLVED 2026-06-13):** PCSX-Redux's web server defaults to `localhost:8080` — same as GhidrAssistMCP. GhidrAssistMCP stays on 8080 (`.mcp.json`); the Redux web server moves to **8081** via `~/.config/pcsx-redux/pcsx.json` → `emulator.Debug.WebServer=true` + `emulator.Debug.WebServerPort=8081` (GUI: Configuration → Emulation → Web Server). Edit `pcsx.json` only while Redux is **stopped** (it rewrites the file on exit).
- **Lua scripting:** LuaJIT 2.1.0-beta3 (Lua 5.2 compat), FFI direct memory access; console + editor under the Debug menu. Gotcha: the editor autosaves to `pcsx.lua` and reloads it at startup — a crashing script wedges the emulator across restarts (delete `pcsx.lua` to recover); long-running scripts must yield via coroutines (~15 ms/frame budget).
- **Debugger:** fully featured MIPS debugger, VRAM/SPU viewers. GDB server on port 3333 (Configuration → Emulation → Enable GDB server); for Ghidra-attached debugging launch Redux with `-interpreter -debugger -gdb` (dynarec breaks debugging) and connect `gdb-multiarch -i mi2` → `target remote localhost:3333`.
- PSX RAM at 0x80000000 mirrors physical 0x0 (0x800425D0 ≡ 0x000425D0) — relevant when reading dump offsets.

---

## §4 Build environment (Phase 4)

Everything below installs inside the same WSL2 Ubuntu 24.04 that already hosts Ghidra and Claude Code (§1). Where Phase 1 (§2) already set up the distro and JDK, this phase adds the build toolchain on top.

### §4.1 WSL2 + Ubuntu 24.04 (already present from Phase 1)

The all-in-WSL architecture means WSL2 Ubuntu 24.04 is the single host for the whole project, so it exists before Phase 4 begins (it is the same environment §2 installed Ghidra into). Confirm it is the expected distro and version:

```bash
cat /etc/os-release   # Ubuntu 24.04
uname -a              # Linux kernel (WSL2)
whoami                # the Linux username; ~ resolves to /home/<user>
```

All project paths are plain Linux paths under `~/bfm-decomp` — there is no Windows distro name or `wsl.exe --cd` target to track.

### §4.2 Networking: MCP is local

Under the all-in-WSL architecture there is **no cross-OS networking**. Ghidra/GhidrAssistMCP, PCSX-Redux, and Claude Code all run inside the same WSL2 instance, so the MCP endpoint is plain loopback: **MCP is local to WSL at `http://127.0.0.1:8080`; no mirrored-mode `.wslconfig`, firewall rule, or host-IP discovery is needed.** Smoke-test with Ghidra running: `curl http://127.0.0.1:8080/` from any shell in the same WSL instance.

### §4.3 The clone on ext4

```bash
cd ~ && git clone <remote-url> bfm-decomp
```

The single clone lives at `~/bfm-decomp` (ext4). Builds, splat, asm-differ, Ghidra, and Claude Code all run here. In this clone: `git config core.filemode true`. **Remote (P33):** `origin` = `https://github.com/Druthulu/BFM-decomp.git` (public from Phase 33 C10); the pre-rewrite history lives in the private archive `Druthulu/BFM-decomp-archive`. Claude commits, Drew pushes (R6).

### §4.4 Copy the disc dump into the clone

> **As-built (P33 B1/B8):** after the copy, **`make disc-extract`** regenerates `extracted/` from `disks/` and verifies every
> file against the committed manifest (`disc-extract: OK`, 15.7 s; `PARTIAL` for a Track-1-only dump; the "P33 B1" section
> below has the flags and controls). `make extract-all` runs it once first; `make check-env` warns when the EXE is absent.

One-shot copy onto ext4 is fine (and required once):

```bash
mkdir -p ~/bfm-decomp/disks
cp '<dump-source>/Brave Fencer Musashi (USA)/'*.bin \
   '<dump-source>/Brave Fencer Musashi (USA)/'*.cue ~/bfm-decomp/disks/
```

`<dump-source>` is wherever the disc dump currently lives (e.g. a one-time download into `~/Downloads`, or a one-shot copy from external media). `disks/` is gitignored — no ROM-derived bytes ever reach the remote (rule H1).

**Status (Phase 2, 2026-06-13):** the disc was staged early — extraction needs it before Phase 4. Track 1 alone (it holds all 27 root files) was copied once from the author's dump location (a `<dump-source>` as above) to ext4 at `disks/Brave Fencer Musashi (USA) (Track 1).bin` (364,846,944 bytes). WSL `extract_exe.py --bin "disks/…(Track 1).bin" --verify-disc` **PASSED** — SHA1 `b44f0f0a19936f23b26188b658e13201a6a9c211`, CRC32 `c238191b`, both == redump — which **closes the Phase-1 deferral** (verify-disc had previously only run on Windows; PhaseEnd_Phase1 Deviations).

### §4.5 apt packages

Adapted from sotn-decomp's `tools/requirements-debian.txt` (dropped Saturn/PSP-only items `binutils-sh-elf`, `xfonts-utils`; Rust/Go deferred until a duplicate-detector or asset tool needs them):

```bash
sudo apt-get update && sudo apt-get install -y \
  bchunk binutils-mipsel-linux-gnu bsdmainutils clang-format coreutils curl \
  gcc-mipsel-linux-gnu git libelf-dev make ninja-build p7zip-full \
  python3-pip python3-venv unzip wget
```

> ⚠️ **binutils regression check (mandatory before trusting builds):** open-ribbon documents that `binutils-mipsel-linux-gnu >= 2.38` generated broken binaries; **2.35 is the known-good reference**. Ubuntu 24.04 ships newer binutils — **VERIFY on 24.04**: after Phase 5's first full build, if the SHA1 check mysteriously fails with correct-looking asm, suspect the assembler first (`mipsel-linux-gnu-as --version`), and pin/downgrade or build binutils 2.35 if confirmed. Record the verdict here.
>
> **As-built (Phase 4, 2026-06-14, ledger #6):** apt installed **binutils-mipsel-linux-gnu 2.42** (as/ld/objcopy all 2.42; mipsel-gcc 12.4.0). 2.42 ≥ 2.38, so `make check-env` emits a **[WARN]** (not FAIL) and the regression verdict is **deferred to Phase 5's first full build** exactly as above — no preemptive downgrade.
>
> **✅ VERDICT (Phase 5, 2026-06-14): binutils 2.42 is byte-clean — no regression with our flags.** The all-asm `make build` reproduces `SLUS_007.26` **SHA1-identical** (`143dbb89…`) using `mipsel-as` 2.42 with `-march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0`. The open-ribbon "≥2.38 broken" warning does **not** bite here; **no downgrade to 2.35 needed.** (Revisit only if Phase-6 C-compiled objects ever diff where the asm is right.)

### §4.6 Python venv + splat + submodules

> **As-built (P33 B3/B8): `make bootstrap`** (`tools/bootstrap.sh`) does all of this idempotently on a fresh clone — apt
> presence check (prints the install line), the venv from `requirements-python.txt`, the submodules, the two cc1 tarballs
> sha256-checked and extracted, then `make check-env` — proven fresh-clone → 218/218 in 4 m 18 s (the "P33 B3" section).
> The manual steps below remain the reference for what it does.

```bash
cd ~/bfm-decomp
python3 -m venv .venv                    # Python >= 3.12 required (24.04 ships 3.12; older = f-string SyntaxError mid-build)
.venv/bin/pip install -U 'splat64[mips]>=0.41.0,<1.0.0'
```

The PyPI package is **`splat64`** (not `splat`), and the `[mips]` extra is required for PSX (pulls spimdisasm/rabbitizer). Always invoke as `.venv/bin/splat` or `.venv/bin/python3 -m splat` — `splat: command not found` means you're outside the venv. Once Phase 5 builds green, freeze the exact working version in a committed `tools/requirements-python.txt`.

Submodules (add under `tools/`):

| Submodule | URL | Pin |
|---|---|---|
| `tools/maspsx` | `https://github.com/mkst/maspsx.git` | commit `874855c53f65f8fa57447e1da6bde6236dbef9d5` (decomp.me's pin — keeps local results comparable to decomp.me scratches) |
| `tools/asm-differ` | `https://github.com/simonlindholm/asm-differ.git` | pin current HEAD at adoption |
| `tools/m2c` | `https://github.com/matt-kempster/m2c.git` | pin current HEAD at adoption |
| `tools/decomp-permuter` | `https://github.com/simonlindholm/decomp-permuter` | sotn pins `b44b0622269fb4bff29e79fbbad26b9f47beda79` — sane default |

Pin all four (sotn precedent: blindly updating submodules breaks tooling). Note: sotn's asm-differ `--overlay` flag is **sotn-fork-specific**, not upstream — for BFM overlay diffing use upstream's `-o` object mode or port their fork later.

**As-built (Phase 4, 2026-06-14):** `.venv` created (Python 3.12.3); installed **splat64 0.41.0** (`splat64[mips]`) — deps spimdisasm 1.41.0, rabbitizer 1.16.2, PyYAML 6.0.3, colorama 0.4.6, intervaltree 3.1.0, tqdm 4.67.1; `import splat` OK. Submodule pins as adopted: maspsx `874855c5`, decomp-permuter `b44b0622` (both per the table); **asm-differ `2ad4a4a4`** and **m2c `4266cc28`** (each HEAD-at-adoption). Their pip deps are **not** installed yet (Phase 6, when first invoked); `tools/requirements-python.txt` is frozen only after Phase 5 is green.

### §4.7 Vintage compilers (old-gcc 0.17)

Linux prebuilts from decompals/old-gcc, **release 0.17** (32-bit i386 static — see the correction below):

```bash
mkdir -p ~/bfm-decomp/tools/bin && cd ~/bfm-decomp/tools/bin
wget https://github.com/decompals/old-gcc/releases/download/0.17/gcc-2.7.2-psx.tar.gz
wget https://github.com/decompals/old-gcc/releases/download/0.17/gcc-2.7.2-cdk.tar.gz
sha256sum gcc-2.7.2-*.tar.gz   # record hashes in a committed tools/bin/*.sha256 on first download,
                               # then verify with `sha256sum --check` on every fresh setup (sotn pattern)
# The 0.17 tarballs are FLAT (no top-level dir) and SHARE filenames (cc1, cpp, gcc, ...)
# -> extract each into its OWN subdir, or the second clobbers the first (Phase-4 finding):
mkdir -p gcc-2.7.2-psx gcc-2.7.2-cdk
tar xzf gcc-2.7.2-psx.tar.gz -C gcc-2.7.2-psx
tar xzf gcc-2.7.2-cdk.tar.gz -C gcc-2.7.2-cdk
```

**As-built (P33 B3):** the two tarballs are TRACKED in the repository (`tools/bin/*.tar.gz`, GCC = GPL; sha256s in
`tools/bin/CHECKSUMS.sha256`) and `tools/bootstrap.sh` does exactly the check-and-extract above on a fresh clone — the
`wget` lines are how they were first obtained, not a step a contributor runs.

- `gcc-2.7.2-psx` = community GCC 2.7.2 PSX build (primary candidate).
- `gcc-2.7.2-cdk` = **cygnus-2.7.2-970404**, the exact base of PsyQ 4.0/4.1's CC1PSX (added in old-gcc 0.14).
- **sha256 (RECORDED Phase 4, old-gcc 0.17, ledger #7):** `gcc-2.7.2-psx.tar.gz` = `500a459b3485e885a8d302cac23c2a4632f3900e03a09153f6190699fd723571`; `gcc-2.7.2-cdk.tar.gz` = `42bb0df96db11a9b5d2e23d78bdc962791f40046280d3d360da93fe5eef6f0bb`. Committed to `tools/bin/CHECKSUMS.sha256` (gitignore exception `!/tools/bin/*.sha256`); re-verify with `sha256sum --check tools/bin/CHECKSUMS.sha256`.
- **CORRECTION (Phase 4):** these are **32-bit i386 statically-linked** ELF binaries (NOT x86-64 as previously written) — they run on x86-64 WSL2 via the kernel's IA-32 emulation (verified: `cc1` smoke-compiles to MIPS asm and self-identifies as `GNU C 2.7.2 [AL 1.1, MM 40] Sony Playstation`). Still Linux-only — *why* the build side must be Linux/WSL2. As-built layout: `tools/bin/gcc-2.7.2-psx/cc1` + `tools/bin/gcc-2.7.2-cdk/cc1` (matches the §6.2 path).

### §4.8 Optional: PsyQ 4.0/4.1 binaries for arbitration (via Wine)

> **As-built (P33 B4/B8):** the OPTIONAL Sony SDK *objects* that let `make check BINARY=main` link the real PsyQ libraries
> are obtained, sha256-verified and built by **`tools/fetch_psyq.sh`** (user-supplied 4.0 LIBs from the DTL-S2002 disc or
> `--from DIR`; the RTL 4.2 archive; `psyq-obj-parser`) — see the "P33 B4" section. Byte-identity never needs them
> (`make sdk-dual`). The Wine arbitration path below is the Phase-6 fingerprinting tool, unrelated to linking.

For byte-exact arbitration when maspsx output is in doubt, the **real** PsyQ Win32 tools can be driven from WSL under Wine (`sudo apt-get install -y wine`):

- `https://github.com/mkst/esa/releases/download/psyq-binaries/psyq4.0.tar.gz`
- `https://github.com/mkst/esa/releases/download/psyq-binaries/psyq4.1.tar.gz`
  (contain `CC1PSX.EXE`, `ASPSX.EXE`, `CCPSX.EXE`, `PSYLINK.EXE`, `PSYLIB.EXE`; 1–2.3 MB each)
- Their `.OBJ` output converts to ELF with **psyq-obj-parser** (part of pcsx-redux; prebuilt Linux binary: `https://github.com/decompme/compilers/releases/download/compilers/psyq-obj-parser.tar.gz`).

Keep these under `tools/` on ext4 (not committed); they are a tie-breaker, not the daily pipeline. (decomp.me runs these same Win32 tools under Wine for its psyq presets — the precedent that this works headless.)

> **DEFERRED to Phase 6 (Drew decision, Phase 4):** not staged in Phase 4 — fetched only if/when maspsx output is disputed during fingerprinting. Wine is not installed. The §4.8 "optional native PsyQ binaries" checkbox is consciously skipped for Phase 4.

### §4.9 `make check-env` (Phase 4 exit milestone)

Phase 4's observable milestone: a `check-env` make target that asserts every §4 component (venv + splat import, cc1 binaries executable, maspsx present, mipsel-as/ld/objcopy on PATH, python >= 3.12) and exits 0 when invoked directly in the WSL clone (see §6.1).

**As-built (Phase 4, 2026-06-14):** the root `Makefile` implements `check-env` (`.ONESHELL` bash; default goal `help`). Beyond the components above it also asserts **sha1(committed `extracted/retail/SLUS_007.26`) == `EXPECTED_EXE_SHA1`** (imported from `tools/bfm_extract/extract_exe.py` — fresh-clone-safe; the disc-walk `--verify-disc` needs the gitignored `disks/` and is intentionally NOT in check-env) and WARNs on binutils ≥ 2.38. **`make check-env` exits 0** (milestone met). `extract/build/check/expected/clean` exist as loud-failing Phase-5 stubs (names fixed per §6.3).

---

## §5 Compiler candidate ladder (Phase 6 fingerprinting)

### §5.1 The evidence

Locally verified on the extracted US EXE (DetectPsyQ-style masked-pattern scan): **13 pattern hits, of which 12 are genuine `Ps` library stamps** — 9× PsyQ **4.0** (libnums 2, 3, 4, 6, 7, 8, 9, 17, 24), 1× **4.0.1x** (libnum 16), 1× **4.2** (libnum 0), 1× **4.2.1x** (libnum 12); the remaining hit (ver 0x0000 at vaddr 0x8005CD20) is a code false positive. **Identified (P31 S78, byte-placed via the psx loader's per-version signature sets, `~/ghidra_12.1_PUBLIC/Ghidra/Extensions/ghidra_psx_ldr/data/psyq/<ver>/<LIB>.LIB.json`):** the 4.2 stamp at `0x8005CE48` is **LIBAPI 4.2 `C114.OBJ` (`_96_remove`)** at the head of the `800c3` band, and the 4.2.1x stamp at `0x80072954` sits in front of **LIBPAD 4.2.1's** `.data` (the callback tables `D_8007295C..D_800729D8`); the band `0x8005CF68–0x8005FC68` is COUNTER (libapi) · PADENTRY · PADMAIN · L02/L03 · PADCMD · PADIF · PADPORTD · PADSEQD · WAITRC2 (libpad), and `FIRST`/`PAD`/`PATCH`/`CHCLRPAD` (libapi 4.2) sit in `800c2`. See `docs/psyq-worklist.md` "S78". A raw-track scan during research reported 16 hits with extra spurious 4.0 stamps — the extracted-EXE scan is ground truth, and ghidra_psx_ldr's detection at import is the final word (ledger #12). Library copyright string `(c) 1993-1997 Sony` corroborates the era. Conclusion: BFM links **PsyQ 4.0 libraries with 4.2 library updates** ⇒ the GCC 2.7.2/SN32-era toolchain — **NOT sotn's GCC 2.6.3** (the starting-point doc's claim is corrected). PsyQ 4.2 was a library-only refresh: no 4.2 toolchain disc exists (absent from redump/arthus sets), so 4.2 stamps still mean the 4.0/4.1 toolchain — but the 4.2 RUNTIME LIBRARY itself survives: archive.org's `play-station-programmer-tool-runtime-library-version-4.2.7z` (P31 S79 task #13, `tools/psyq/lib42/` + the 1998-02-26 libpad-4.2.1 patch in `lib421/`), and its LIBPAD 4.2.1 / LIBAPI 4.2 objects link the whole band byte-identical (46/46) — the stamps are now backed by the real objects, not just signatures.

Caveat: `Ps` stamps date the **linked libraries**, not the compiler that built game code — Square mixed cc1 builds within one EXE (see §5.5). The final triple is pinned only by Phase-6 fingerprinting.

### §5.2 SDK → GCC → ASPSX mapping (verified from the actual binaries in mkst/esa psyq-binaries tarballs)

| PsyQ SDK | CC1PSX identifies as | ASPSX | old-gcc 0.17 artifact | maspsx flag |
|---|---|---|---|---|
| 3.3 | GNU C 2.6.0 [AL 1.1, MM 40] | 2.21 | `gcc-2.6.0-psx` | `--aspsx-version=2.21` |
| 3.5 | GNU C 2.6.0 (same binary) | 2.34 | `gcc-2.6.0-psx` | `--aspsx-version=2.34` |
| 3.6 | GNU C 2.7.2.SN.1 | 2.34 | `gcc-2.7.2` (vanilla-ish) | `--aspsx-version=2.34` |
| **4.0** | **GNU C 2.7.2.SN32.3.7.0002** | **2.56** | **`gcc-2.7.2-psx` / `gcc-2.7.2-cdk`** | **`--aspsx-version=2.56`** |
| **4.1** | **cygnus-2.7.2-970404 SN32.3.7.0004 (SonyPSX)** | **2.67** | **`gcc-2.7.2-cdk`** (exact base) | **`--aspsx-version=2.67`** |
| 4.2 | *library-only release — no toolchain exists* | n/a | use 4.0/4.1 row | use 4.0/4.1 row |
| 4.3 | GNU C 2.8.0 SN32 Build 4.0.0007 (community shorthand "2.8.1" is wrong — that's 4.4) | 2.77 | `gcc-2.8.0-psx` | `--aspsx-version=2.77` |
| 4.4 | GNU C 2.8.1 SN32 BUILD 4.0.0010 | 2.79 | `gcc-2.8.1-psx` | `--aspsx-version=2.79` |
| 4.5 | egcs-2.91.66 (egcs-1.1.2) | 2.81 | `gcc-2.91.66-psx` | `--aspsx-version=2.81` |
| 4.6 | GNU C 2.95.2 BUILD 4.0.0030 | 2.86 | `gcc-2.95.2-psx` | `--aspsx-version=2.86` |

> ⚠️ **`--aspsx-version` MUST always be passed explicitly.** maspsx with no flag is *not* "latest behavior" — the dataclass defaults approximate ASPSX ~2.3x (`expand_li=True`, `sltu_at=True`, `nop_mflo_mfhi=True`). Behavior thresholds: `expand_li` off ≥2.50; `sltu_at` off ≥2.60; `$gp` symbol+offset ≥2.70; `$gp` for `la` ≥2.80. The observable 2.56 vs 2.67 tell: "$at for `sltu < 0`" present at 2.56, gone at 2.67, and %hi/%lo support arrives at 2.67 — decide on functions with unsigned comparisons / li/sltu idioms.

### §5.3 -G0 vs -G8

Read `gp_value` from the SLUS_007.26 EXE header and check for `$gp`-relative loads in Ghidra **before** fixing the flag (**RESOLVED Phase 5 — see the ✅ verdict below: -G0**). Precedent: FF7 used `-G 0`; Xenogears used `-G8` for game code. maspsx forces `-G0` to GNU `as` by default — non-zero `$gp` needs `-G8` passed to maspsx and a look at `--dont-force-G0`.

**✅ RESOLVED (Phase 5, 2026-06-14): -G0.** The header `gp_value` is 0, and the splat disassembly has **zero `($gp)` base-register accesses and zero `%gp_rel` relocations** (the 4 `$gp` mentions are crt0 register setup) — no small-data/$gp-relative addressing, i.e. the FF7-style `-G0`. The linker's `_gp=0x80074750` (splat's computed Initial-GP) is therefore inert, and the all-asm build is byte-identical. Carry `-G0` into Phase-6 cc1 fingerprinting (swap only if asm-differ ever shows otherwise).

### §5.4 Candidate ladder (try in this order)

> **✅ PINNED (Phase 6, 2026-06-14) — rung 1 is the answer (G8).** Triple:
> `tools/bin/gcc-2.7.2-psx/cc1 -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker`
> → `maspsx --aspsx-version=2.56 **--expand-div**` → `mipsel-as -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0`.
> Pinned in the `Makefile` (`CC1FLAGS` / `ASPSX_VERSION` / `MASPSX_FLAGS`). Evidence: byte-exact on `func_80018F20`
> (the `sltiu` range-check probe) + instruction-identical across 2 more idiom classes (division via `--expand-div`;
> memset). **`--expand-div` is required** for any div/rem (without it maspsx emits a bare `divu` with no zero-check
> and div functions never match). **psx≈cdk and 2.56≈2.67 are byte-equivalent** on functions lacking the
> discriminating idioms, so rungs 2–5 went unused (kept below for per-module-mixing escalation, §5.5). Reusable
> codegen findings: `docs/matching-cookbook.md`.

1. **`gcc-2.7.2-psx` cc1 + `--aspsx-version=2.56`**, flags `-O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker` (FF7 style; swap to -G8 if §5.3 says so).
2. Same cc1 + `--aspsx-version=2.67` (PsyQ 4.1 assembler era).
3. **`gcc-2.7.2-cdk`** (cygnus-2.7.2-970404, the exact CC1PSX 4.0/4.1 base) × 2.56, then × 2.67.
4. Real PsyQ 4.0/4.1 `CC1PSX.EXE` + `ASPSX.EXE` (under Wine, §4.8) + psyq-obj-parser — byte-exact arbitration when maspsx emulation is in question.
5. Only if diffs show GCC 2.8-style codegen: `gcc-2.8.0-psx` + 2.77 (unlikely — the JP master predates PsyQ 4.3-era adoption).

**Library-code preset** (for PsyQ SDK functions linked into the EXE): `--aspsx-version=2.56 --expand-div`, `-O3 -G0` — the Xenogears precedent, consistent with our 4.0 lib stamps.

### §5.5 Per-module mixing warning

Xenogears (the closest comparable: Square US, Oct 1998) mixes **three** cc1 builds in one EXE (`gcc-2.7.2-psx`, `gcc-2.6.0-psx`, `gcc-2.7.2-cdk`) with different maspsx flags per module. Expect per-module variation in BFM: fingerprint **several modules independently** (3–5 medium leaf functions each), and design the build config for per-file compiler/flag overrides from day one (sotn does this with `//!` comments in line 1–2 of a .c file; Xenogears with `gears.toml` presets).

Reference repos for build-config patterns: `https://github.com/ladysilverberg/xenogears-decomp` (gears.toml presets), `https://github.com/Drahsid/ffvii` (Makefile).

### §5.6 Compiler-quirk research reference clones (Phase 18, 2026-06-20)

Phase 18 (raise the match-% ceiling by understanding gcc-2.7.2's blocking codegen quirks) reads the **real compiler source** and mines a peer decomp built with **our exact compiler**. Cloned shallow, gitignored under `/tools/reference/` (re-clonable — SHAs pinned here for reproducibility, R20/R21):

| Repo | Purpose | Path | Branch | SHA (pinned) |
|---|---|---|---|---|
| `pmret/gcc-papermario` | ⚠️ **actually gcc 2.8.1, NOT 2.7.2** (behavioral diff: 2.8.1 `&&0`-disables biv-elim paths ENABLED in real 2.7.2 — caught Phase 23). OK for passes where 2.8.1≡2.7.2, but **cite `gcc-2.7.2/` below for accuracy**. | `tools/reference/gcc-papermario` | `master` | `a6afc2afbcaf6682930141d526afdc95801fc2fd` |
| **vanilla gcc-2.7.2** (the REAL source of our pinned cc1) | authoritative source for the codegen map (cookbook §31/§34 + `docs/gcc-2.7.2-map/`): `sched.c`/`reorg.c` (scheduling), `local-alloc.c`/`global.c`/`reload1.c` (regalloc), `loop.c` (IV/hoist), `cse.c`/`expr.c` (CSE/aliasing). Staged Phase 23; **completed Phase 24 T5** (18 `.c` files — +toplev.c/function.c/flow.c/… from the FSF tarball; sched.c/loop.c/mips.c verified byte-identical to vanilla → §34's `local-alloc.c:1441` 3-qty-sort-bug citation is sound). **P31 T2: +6 files** — `calls.c` + `caller-save.c` (both cited by §172's frame-residue producer model, previously MISSING) + `integrate.c`/`optabs.c`/`varasm.c`/`recog.c` — from GNU ftp `gcc-2.7.2.tar.gz`, sha256 `7cd8bce5c3aeec59a72ecc2d3d5123864a817b14cdbd0680b1a969c3bccc5da5`. | `tools/reference/gcc-2.7.2` | GNU 2.7.2 release | (re-fetch: GNU ftp `gcc-2.7.2.tar.gz`; tarball kept at `.run/t7/fable/gcc-2.7.2.tar.gz`) |
| `ladysilverberg/xenogears-decomp` | Square, Oct 1998, **gcc-2.7.2-psx + -cdk** (our exact compiler); mine transferable quirk idioms + `gears.toml` per-module presets | `tools/reference/xenogears-decomp` | `main` | `f27c0768b1ad10812cec776cadadb85ae70aadee` |
| **PsyQ Runtime Library 4.2 + the libpad 4.2.1 patch** (P31 S79, 2026-09-04, task #13) | archive.org item `play-station-programmer-tool-runtime-library-version-4.2.7z` (383 KB) → tracked as `tools/psyq/PlayStation_Programmer_Tool_-_Runtime_Library_Version_4.2.7z` (sha256 in `CHECKSUMS.sha256`) → `tools/psyq/lib42/` (the 4.2 LIBs, 1998-01-21) + `tools/psyq/lib421/` (`LIB/42PATCH/J421PD.ZIP` = SCE R&D "libpad.lib 4.2.1 for the DUAL SHOCK", 1998-02-26: LIBPAD.LIB 4.2.1 + LIBAPI.LIB 4.2 + LIBPAD.H/LIBAPI.H/KERNEL.H) → ELF via `psyq_lib_split.py` + `psyq-obj-parser` into `.run/obj42/{libpad421,libapi42}`. **This is the EXE's libpad/libapi**: 7 + 39 objects place and link byte-identical (`psyq_link.py` PASS ×46) — the whole 0x8005CE18–0x8005FC68 band + the apicard-region libapi pieces. The 4.2.1 headers are the band's prototype oracle | `tools/psyq/lib42/`, `lib421/` (gitignored, regenerable) | — | — |
| **PsyQ 4.6 libraries** (P31 S78, 2026-09-04) | `Psy-Q_46.zip` (psx.arthus.net; sha256 in `tools/psyq_CHECKSUMS.sha256`) → `tools/psyq/lib46/*.LIB` (23 libs) → ELF via `psyq_lib_split.py` + `psyq-obj-parser` into `.run/obj46/<lib>/`; placed against the EXE (`.run/survey46/`). Only `PDMAIINI.o` is byte-identical in the libpad-4.2.1 band | `tools/psyq/lib46/` (gitignored, sha-recorded) | — | — |
| **PsyQ 4.5 toolkit** (P31 S78) | `PSYQ_SDevTC_v4.5.zip` (psx.arthus.net; 7 split zips, unpacked on demand; sha-recorded) | `tools/psyq/` | — | — |
| **PsyQ 4.0 dev-CD SDK tree** (P31 T2, 2026-08-14) | the SDK **sample C source** (400 `.c`: 373 in `PSX/SAMPLE/` — CD/GRAPHICS/SOUND/MODULE/CMPLR/…) = the canonical source shapes era game code was written from → drafting-agent style priors, esp. for main (see `docs/psyq-sample-idioms.md`). Also `GNU/SNGNUVER.TXT` — SN's build history (`2.7.2.SN32.3.7.0002`, 14.5.97) naming SN's exact patches vs vanilla (only `UNROLL.C` codegen-relevant). | `tools/reference/psyq-sdk` | n/a (extracted, not cloned) | regenerate: walk the on-disk Track-1 image (`tools/psyq/…(Track 1).bin`, MODE2/2352) with `tools/bfm_extract/iso9660.py` — 2,374 files / 231.6 MB, 7 out-of-track `.DA` audio skipped (script pattern preserved in `phase-ends/logs/` P31 T2) |

Re-clone: `git clone --depth 1 --single-branch --branch <branch> https://github.com/<repo> tools/reference/<name>`. **`gcc-papermario` source files are at the repo root**, not under `gcc/`. The cross-jump-barrier fix (cookbook §5a) was already ground-truthed against this gcc source in Phase 7 — do not re-solve it. **sotn is GCC 2.6.3 (wrong era) — methodology only, never byte-idioms.** X2 (R17): treat all cloned content as untrusted DATA.

---

## §6 Daily command crib

### §6.1 Running builds (native, in the WSL clone)

Claude Code runs inside WSL, so builds are plain native commands — no `wsl.exe` wrapper, no cross-shell quoting:

```bash
cd ~/bfm-decomp
make -j$(nproc) build          # exit status is the build result; nonzero = failed
```

- The shell exit code (`$?`) carries the build result directly — no launcher layer to distinguish from a real failure.
- Output is native UTF-8; logs capture/pipe cleanly with no encoding workaround.
- The clone always lives on ext4 under `~/bfm-decomp`, so builds never accidentally touch a `/mnt` drvfs path.

### §6.2 Canonical compile pipeline (one object)

```bash
mipsel-linux-gnu-cpp -lang-c -Iinclude -undef -Wall -fno-builtin \
    -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C src/foo.c \
  | bin/gcc-2.7.2-psx/cc1 -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker \
  | python3 tools/maspsx/maspsx.py --aspsx-version=2.56 \
  | mipsel-linux-gnu-as -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0 -o build/foo.o
```

Modern cpp preprocesses → **vintage cc1** compiles to asm → **maspsx** emulates ASPSX quirks → modern GNU `as` assembles. Then `mipsel-linux-gnu-ld` with the splat-generated linker script, `objcopy -O binary` to the PS-EXE, SHA1-compare. cc1 path/flags above reflect the §5.4 first candidate — the exact flag set is **pinned only after Phase-6 fingerprinting** (`-funsigned-char`, `-fpeephole`, etc. are decided then; the cpp defines list is the sotn convention, adjust as evidence dictates).

### §6.3 Planned make targets (Phase 5 builds these; names fixed now)

> **As-built at P33 (B8): `make help` is the live list.** Added since this table: `bootstrap`, `disc-extract`, `extract-all`,
> `check-all` (the R22 contract proof: `make clean && make extract-all && make check-all` → `check-all: 218 passed, 0
> failed of 218`), `sdk-dual`, `report`, `tools-health`, the `sig-*` and `audit-*` families, `print-<VAR>`. The public
> recipe with every expected last line is **`docs/verification.md`**.

| Target | Does |
|---|---|
| `make extract` | splat split per `config/splat.us.*.yaml` → `asm/`, linker scripts |
| `make build` | full pipeline → `build/us/SLUS_007.26`, auto-runs the SHA1 check |
| `make check` | standalone SHA1 manifest verification (byte-for-byte = the only "OK") |
| `make expected` | snapshot `build/us` → `expected/build/us` (asm-differ baseline) |
| `make check-env` | toolchain preflight, exit 0 = environment sane (§4.9) |
| `make clean` | mandatory after ANY `config/` change, before re-extract |

**As-built (Phase 5, 2026-06-14):** all five implemented in the root Makefile. The code is **100% assembly** (the phase's "all-asm byte-match"; the cpp→cc1→maspsx→as `c` path is wired-but-dormant until Phase 6). `make extract && make build && make check` → `build/us/SLUS_007.26` **SHA1-identical** to the original. Config `config/splat.us.exe.yaml` (platform psx, compiler PSYQ, subalign 2, gp_value 0x80074750, main segment `align: 4` so the text→data boundary isn't 16-byte-padded); committed checksum `config/check.us.sha`. Build chain = `as -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0` → `ld -T <splat .ld> -T undefined_syms_auto.txt -T undefined_funcs_auto.txt --no-check-sections` → `objcopy -O binary`.

**Fail-closed recipes (Phase-27 T2, 2026-07-15).** The Makefile sets **`.SHELLFLAGS := -ec`** — because `.ONESHELL` sends each whole recipe to ONE `bash -c`, so without `-e` a recipe's exit status is its LAST command's only, and every earlier failure is silently swallowed. That had made `make report`'s middle gates (`lint_symbol_refs`, `progress --audit`, `difficulty`, `dup_report`) into non-gates — the 26-A audit's own thesis (a loud failure nobody counts is as invisible as a silent one) biting the audit's infrastructure. Consequences of the flag, now standing:
- **`make report` is genuinely fail-closed** — any of its gates failing exits non-zero (verified by a negative control: the same broken gate exits 0 under the old `-c`, non-zero under `-ec`).
- **`make check-all` / `extract-all` assert COVERAGE (`pass == N`), not the absence of a failure marker** — the old `fail == 0` form was a *vacuous pass* on an empty pipeline. `check-all`'s `pass=$(grep -c …)` carries `|| true` (grep -c exits 1 on zero matches, which `-e` would otherwise treat as fatal — it would fail check-all exactly when nothing failed).
- **`make check-env` opts OUT** (`set +e` at the top of its recipe) — its contract is accumulate-every-failure-and-report, which `-e` would truncate at the first missing tool. It is the **only** intended opt-out; add `set +e` to a recipe only with the same justification.
- **`make tools-health`** (new) = regenerate the byte-derived sigs (`sig-overlays` + `sig-resident`) then run `audit-corpus` + `audit-cdecl` + `audit-binaries` + `report` + `audit-digest`, fail-closed — the deliberate pre-matching ritual the roadmap's standing invariant names. Deliberately NOT a prerequisite of `report`/`build` (audit-cdecl cross-compiles every C declaration through real gcc, ~minutes). `audit-cdecl` ≈ several minutes; `audit-corpus` ≈ 7 s.
- **`make sig-resident`** (Phase-27 T10; **P31 T0 ELF-seeded** — bootstrap's linear partition fused the +0 data word with the first fn and dropped the last, 144→the true 145; S45 nm-seed pattern, bootstrap fresh-clone fallback) signs the resident flat blob with `sig_image` (byte-derived) so `make audit-corpus`'s second boundary oracle (R34) covers the **resident** — probed clean (0 phantom/truncated). `sig-overlays` derives its payload list from `config/overlays.mk` (not a `0.4.dec` glob, which dropped the 4 SC07 index-1 overlays). `progress.py --fleet` reports a separate **MAIN game-code weighted** line (provisional) — the metrics-contract "main in the denominators", honestly un-folded.
- **`make atlas`** (P31 T5) — the Frontier Atlas regen chain: `family_hseq` → `family_cousins` (+both card emitters) → `tools/atlas_features.py` (per-fn feature layer: 363k rows / 93k distinct bodies in ~21 s; §172b tell detectors live here as importable functions — `li_norm_toks`/`extpair_count`/`dupselect_count`/`sign_mix`/`magic_div_count`, one implementation R33) → `tools/atlas.py` (the survey: cousin units + T1.5 h_seqn merges + calibrated warm tier + seed sweep vs the matched-skeleton pool + kNN graph + evidence joins + lever labels → `.run/atlas.json` + committed `docs/frontier-atlas.md`, partition-asserted). `tools/atlas.py --calibrate` freezes THRESH_WARM/KNN_FLOOR from measured recall/false-accept (seeded RNG, regenerable); `--targets N [--lever L] [--cat C]` emits crack slates. Main joins at the ATLAS layer only (family maps stay non-main by design — four enumerated silent-skip hazards in their consumers).
- **`make sig-main` — REWRITTEN P33 A2 (S86, 2026-09-06):** signs ALL of main's game-code functions at **build-true
  lengths**, Ghidra-free and splat-free: `tools/main_seed_ends.py --map build/us/SLUS_007.26.map` reads each game-code
  object's `.text` input section from the link map and slices it at the object's own `nm` function symbols (the rodata
  islands and the LINKED PsyQ blocks sit BETWEEN objects, so every slice is exact — tiling asserted), emits `0xVRAM NINS`
  seeds, and `sig_image --seeds` hashes the ORIGINAL EXE bytes at those boundaries → `.run/sig.main.jsonl` (809 fns /
  45,150 ins). Needs a built main; without the map it leaves the file alone and says so (R51). `progress.py` weighs main
  by this sig (falling back to the legacy Ghidra sig, and EXITING non-zero when neither exists — it used to print
  "217 binaries" and MAIN 0/0 silently, R32); `dup_report.py` reads it for main; `tools-health` and `make report
  BINARY=main` regenerate it first. **Corrected denominator:** the Ghidra sig's flow-derived boundaries left **3,628
  words of real game code owned by no function** (switch tails after unresolved jump tables, 2–4-ins thunks, and
  `SaveLoadRoutine` = the `case 0:` body inside `func_8002b0b4`), so MAIN game-code weighted is **45,150 / 45,150**, not
  41,534 (P31 S79 had caught one instance, +22). Proof (S86): the derived sig tiles the 15 game-code objects' `.text`
  exactly (45,150 words, no overlaps), is never shorter than Ghidra's for any shared function, and Ghidra covers 41,522
  words all inside that text. The fleet totals moved accordingly (instr 13,488,497 → 13,492,113; distinct 5,816,589 →
  5,820,205); the digest's oracle clause is now DERIVED at render time (`progress.main_oracle_line`, was a literal).
  *(Historical P31 T3 text follows.)*
- **`make sig-main`** (P31 T3 — SUPERSEDED above) signed main's 2,002 game-code stubs at **splat-true lengths**: `corpus.py main --seed-ends` emits `0xADDR NINS` per stub (`corpus.s_ins_count`, the same counter audit() uses) and `sig_image --seeds` treats a seeded nins as authoritative (`[addr, addr+4·nins)`, no `func_end` heuristic — which mis-sliced 3/40 main samples). Verified by a full word cross-check (2,002/2,002 EXE slices == `.s` words; note the `.s` word field is byte-order hex, not the LE value). **Deliberately splat-SEEDED** — the atlas needs the boundaries a match must hit; main's *independent* second oracle stays scoped + deferred in `docs/second-oracle.md` (`sig_is_independent("main")` remains False). `family_remap.vram_of/img_path` special-case `"main"` (derived from `splat.us.exe.yaml`: file0-vram = code-seg `vram − start` = 0x8000F800; target_path), so `stream_words("main", …)` works fleet-wide (verified 25/25 vs `.s`).

### §6.4 asm-differ + baseline discipline

```bash
.venv/bin/python3 tools/asm-differ/diff.py -mwo3 <function>     # -m rebuild, -w watch, -o vs object, -3 three-way
```

- Watch mode works **only** with source and build outputs on ext4, modified from inside Linux (§1).
- **Re-snapshot `expected/` only on green:** run `make expected` exclusively after a build whose check passed. A stale `expected/` makes asm-differ silently diff against the wrong baseline — the classic "phantom regression/phantom match".
- Diff score 0 = matched; anything else is not matched, no matter how close.

### §6.5 decomp.me settings for BFM

- Platform: **PlayStation**; Compiler: **`gcc2.7.2-psx`** (or `gcc2.7.2-cdk`) **+ maspsx** family — these images bundle old-gcc cc1 + maspsx at the same pinned commit we use.
- Starting flags: `-O2 -G0` (adjust per §5).
- **Do NOT use the SOTN preset** (`Castlevania: Symphony of the Night` / `gcc 2.6.3-psx` / `psyq_263_221`) — wrong era, guaranteed near-miss diffs.
- decomp.me's API is Cloudflare-challenged (403 to scripts) — scratch searches/uploads needing the API must be done manually in a browser.
- **The project's preset (P33 E1, `docs/decompme-preset.md`):** platform `ps1`, compiler `gcc2.7.2-psx`, flags
  `-O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker -Wa,--aspsx-version=2.56,--expand-div` (decomp.me's image wraps
  `as` with maspsx and forwards `-Wa,` args). Presets are created in the browser by a logged-in user (Drew, after the flip).

### §6.6 Matching a function (INCLUDE_ASM → C; the NON_MATCHING guard) — As-built Phase 6

Phase 6 flipped the text segment to splat's `c` type: `src/800.c` is one
`INCLUDE_ASM("asm/nonmatchings/800", <fn>);` stub per function (file-scope `__asm__`, pulls
the per-function `asm/nonmatchings/800/<fn>.s` in at assembly time). The build is **byte-identical
at 100% INCLUDE_ASM**; matching replaces stubs with C one function at a time. Harness as-built:
`include/common.h` (committed prelude), `diff_settings.py` (asm-differ, arch `mipsel`, object mode
vs `expected/`), `tools/decompile.py` (m2c wrapper), `-Map build/us/SLUS_007.26.map` for symbol lookup.

📓 **Consult `docs/matching-cookbook.md` before/while matching** — the evolvable catalog of reusable
compiler idioms (asm↔C) and "what makes gcc emit X" techniques. These recur across nearly every
function; shaping the C toward them up front saves asm-differ rounds. **Add to it as you learn.**

Cross-refs (HOW-TO lives in the cookbook / PhaseEnds, not duplicated here): per-module **-O0**
overrides — cookbook §6; the **rodata island** — cookbook §8; PsyQ **library linking** — cookbook
§9.1–§9.5; **symbol curation** (rename in Ghidra + `config/symbols.us.txt`, re-extract) — rule R15.

**The loop (per function):**
1. Scaffold: `tools/decompile.py <fn>` (m2c) — or Ghidra `get_code` via MCP for complex ones.
2. Replace the `INCLUDE_ASM(... <fn>);` line with the C function body — **in the TU that owns
   the function's address** (P31 S72; main's game code is THREE TUs, not one):

   | vram | TU | asm path | owns `.rodata` span |
   |---|---|---|---|
   | `0x800123F0-0x8002B0B4` | `src/800.c`   | `asm/nonmatchings/800`   | A `0x80072A38-0x80072C70` |
   | `0x8002B0B4-0x80035270` | `src/800_b.c` | `asm/nonmatchings/800_b` | B `0x80072E44-0x80073140` |
   | `0x80035270-0x8003A444` | `src/800_c.c` | `asm/nonmatchings/800_c` | C `0x800732A0-0x8007344C` |

   **This is load-bearing for any function with a `switch`:** one code object contributes
   exactly ONE contiguous `.rodata` run, so the TU decides which jump-table span the body's
   table lands in. Put a span-B function in `src/800.c` and you re-create the double-emit
   that cookbook §426 exists to describe. Declarations shared across the three TUs live in
   `src/800_shared.h` (§431).
3. Iterate: `.venv/bin/python tools/asm-differ/diff.py -mo <fn>` until **score 0** (`-m` rebuilds;
   `-w` watch, `-3` three-way). decomp-permuter for stubborn near-misses.
4. `make check` must stay SHA1-green (the whole-binary gate); commit-accumulate (R8).
5. If the symbol name changes, rename in Ghidra + `config/symbols.us.txt` and re-extract (R15/G6/R9).

**Matched** → the C replaces INCLUDE_ASM directly (byte-identical, no guard).

**Correct-but-not-yet-matched C** → keep it OUT of the default build behind the guard (G4):
```c
#ifdef NON_MATCHING
    /* correct-but-unmatched C */
#else
INCLUDE_ASM("asm/nonmatchings/800", <fn>);
#endif
```
The default build (no `-DNON_MATCHING`) links the asm, so `make check` never goes red on
non-matching C (G4). `M2CTX`/`PERMUTER` builds are already handled in `include/include_asm.h`.
`expected/` is the asm-differ baseline (a green-build snapshot = original bytes) — re-`make expected`
**only after a green build** (§6.4), never mid-match.

---

### §6.7 Binary-agnostic toolchain (Phase 9) — `make build BINARY=<alias>`

The toolchain builds any binary, not just the EXE. The Makefile holds a data-driven `BINARIES`
list of **alias keys**; each alias has a namespaced `<alias>_*` variable set, and
`make build [BINARY=<alias>]` selects one (default `main`). `main` = the retail EXE `SLUS_007.26`;
**its artifact paths are preserved verbatim** (`build/us/`, `config/splat.us.exe.yaml`,
`config/check.us.sha`, `config/symbols.us.txt`, `.run/sig.SLUS_007.26.jsonl`) so its rebuild is a
byte-exact no-op. `make report`/`asm-differ` are binary-selectable too (see below).

**Adding a second binary (Phase 10+):** append the alias to `BINARIES` and define its `<alias>_*`
block. New binaries use the clean convention — `config/splat.<bin>.yaml`, `build/<bin>/`,
`config/check.<bin>.sha`, `config/symbols.<bin>.txt`, `.run/sig.<bin>.jsonl` — plus per-binary
`<bin>_VRAM_BASE` (the fileoff→vram delta; overlays are **not** `0x8000F800`-based) and
`<bin>_TEXT_LO/HI`. The EXE-only steps (the 9 PsyQ `psyq_integrate` calls, `ld_interleave`) are
gated under `ifeq ($(BINARY),main)`; a second binary supplies its own.

**Required parameters — no EXE default an overlay could inherit** (the phase's #1-risk mitigation;
a miss fails loud, never a silent wrong-address-later):
- `psyq_link.py` / `psyq_identify.py` / `psyq_link_lib.py` / `psyq_link_region.py`: `--vram-base <hex> --exe <path>`
- `psyq_integrate.py`: `--vram-base --exe --symbols <file>` (flags go BEFORE the positionals)
- `gen_lib_subsegs.py` / `make_snd_used.py` / `make_apicard_used.py`: `--vram-base --exe` (EXE-curation tools — these CLI flags *default* to the EXE's values for convenience, but thread explicit values down to the now-required pipeline)
- `ld_interleave.py`: `--order <address-ordered leaf list>` for **main** since P31 S72 — its island is a 7-piece sandwich that `--front/--tail` cannot express (a `*.data.o` leaf contributes its `(.data)`, a code-object leaf its `(.rodata)` carve). Overlays keep `--front <obj> --tail <obj>` (the sandwich `.data` objects) + `--section .<binary>` (Phase 26: default `.main` = the EXE; overlays with a §8 jtbl-rodata carve pass their own section — derives the `<binary>_TEXT/DATA/RODATA/DATA2/BSS` symbol prefix)
- `split_src_region.py`: `--symbols <file>`
- report scripts (`progress.py` / `difficulty.py` / `dup_report.py`): `--binary <alias>` (default `main`)
- asm-differ: select via the **`BFM_BINARY`** env var (default `main`); `diff_settings.py` maps alias → `{baseimg, myimg, mapfile}`

**Proof it's a no-op:** the EXE rebuilds SHA1 `143dbb89…` through the parameterized path **with AND
without** the SDK objects, `make report` reproduces the counts, and a deliberately wrong
`--vram-base` (e.g. `make build main_VRAM_BASE=0x8000F804`) diverges to a non-`143dbb89` hash
(the negative control — proves the param is load-bearing, not accepted-and-ignored).

**First instantiation — `resident` (Phase 10):** the always-resident engine blob
(`extracted/retail/MAIN.CD.dir/FILE_010.dir/1.1`, 365,404 B, vram `0x800CEDF8`, type-1 uncompressed)
is the project's second binary — `make build BINARY=resident` → `8e17e02f…` at 100% INCLUDE_ASM.
The reusable **flat-blob recipe** (every Gen2 overlay follows it):
- **Per-binary source roots + OBJS prune** — main lives at the repo-level `asm/`+`src/`; a second
  binary nests at `asm/<bin>/`+`src/<bin>/` (`<bin>_ASM_DIR`/`<bin>_SRC_DIR`). The `OBJS` glob is
  scoped to the active root with a `$(BINARIES)`-derived prune (`-not -path 'asm/<sibling>/*'`,
  guarded by `$(if $(filter $(ASM_DIR)/%,…))`) so main's root doesn't sweep in nested siblings.
- **`build_path: build`** in the `<bin>` yaml (NOT `build/<bin>`) — splat writes the `.ld`'s object
  paths under `$(build_path)`, and the Makefile pattern rules build them at `build/asm/**`+`build/src/**`;
  only `elf_path`/`ld_script_path`/output live under `build/<bin>/`. Per-binary `undefined_*_auto_path`
  under `build/<bin>/` (splat options) + `<bin>_UNDEF_SYMS/FUNCS` aliases keep main's at the root verbatim.
- **Flat-image splat config** — NO `header` segment (overlays carry no PS-X EXE header), NO `gp_value`
  (-G0; verify zero `($gp)` in the disasm), single `code` segment at `vram: <base>`, stacked
  `symbol_addrs_path: [config/symbols.us.txt, config/symbols.<bin>.txt]` (the shared EXE globals the
  blob references + blob-local names). Iterate text/data boundaries against `make check` (Phase-5 method).
- **A leading data word *before* the code** (e.g. the resident's 1-word header `0x00000036` at the very
  base, code at +0x04) fights `section_order: [.rodata,.text,.data,.bss]` (which puts `.data` after
  `.text`). Emit it as **`rodata`** (no-dot type → asm rodata, placed FIRST) — a 1-word analogue of
  main's rodata-island, **no `ld_interleave` needed**.
- **§8 jtbl-rodata carve (Phase 26 — only when a jr-function is matched):** an overlay's gcc switch jump
  tables sit in a contiguous `.rodata` island at the TAIL of the blob. Matching a jr-function makes its C
  emit that jtbl into `.rodata` (floated to the front by `section_order`) while the raw copy stays in the
  data tail → duplicate. Fix = carve the fn's jtbl into a dotted `[.rodata, <code-subseg>]` subseg + set
  `<bin>_JTBL_INTERLEAVE := --front <pre>.data.o --tail <post>.data.o …` in `config/overlays.mk` (a
  `$(strip)`-guarded `make extract` branch then runs `ld_interleave --section .<bin>`). The C body needs
  `canon_sig_reconcile` first. Full recipe + gotchas: cookbook **§8a**. (No carve ⇒ this is a no-op.)
- Per-binary `<bin>_GHIDRA_PROG` → `make sig-refresh BINARY=<bin>`; `diff_settings.py` + the three
  report scripts gain a `<bin>` entry; `make expected` is per-binary-safe (merge-copy, no sibling clobber).

**Module-class binaries — `md_*` (P30 S44/S45; the §S44 loader table, `docs/memory-map.md`):**
the small type-1 payloads (per-actor modules, the SC07 endgame pair) load at their OWN statically
derived slots (A `0x800CAE08` · B `0x800CCB1C` · boot/resident `0x800CEDF8` · SC07 `0x801A00D8`),
not the shared overlay slot. Onboard with **`tools/new_binary.sh <alias> <payload> <VRAM>
[TEXT_LO]`** (the generalized `new_overlay.sh`; registry `config/modules.mk` / `MODULE_BINARIES`).
Module-specific facts the recipe encodes:
- **TEXT_LO ≠ 0** (the §154 module-id law: payload word0 is a global module id, sometimes followed
  by a fn-ptr table and/or data): derive per payload from the first-prologue scan (`27BDxxxx`) and
  the min fn-ptr-table target — NOT min-table alone (functions can precede the lowest table entry:
  the SC07 pair's real code start is 0xFC/0x158, their min table targets 0x930/0x370).
- **The header carve is a dot-typed `.rodata` PAIRED with the c segment** (same name), never a
  standalone `rodata, hdr` object and never `bin`: a module header can hold a function's JUMP
  TABLE, whose `.L` labels only resolve when jtbl and function assemble in the SAME object (the
  EXE `[0x63238,.rodata,800]` precedent); `bin` assets link in the data block (wrong placement).
- **A4 symbol-window law:** a module whose window lies INSIDE another binary's symbol region must
  NOT stack that binary's symbol file — the boot trio (`0x800CEDF8`) omits `symbols.resident.txt`
  (DsMix @0x800D1BD8 minted a phantom fn boundary in md_MAIN_011 before this).
- **`make sig-modules`** signs every module at its own vram/TEXT_LO, seeding from the built ELF's
  `func_*` symbols when a build exists (bootstrap's linear partition glues adjacent functions
  around jtbl dispatch); fresh-clone fallback is `--bootstrap`, self-healing on the next run.

### §6.8 Cross-binary dedup & code-sharing (Phase 11) — "one match unlocks many"
Full how-to in `docs/matching-cookbook.md` §11. Command crib:
- **`make sig-overlays`** — Ghidra-FREE sign all 134 location overlays (`SCxx 0.4.dec`) at the shared overlay
  vram `0x80128158` via `tools/sig_image.py` → `.run/sig.ov_<SCxx>_<nnn>.jsonl` (gitignored; ~27 s). Re-run when
  overlays change. (`make sig-refresh` still does the Ghidra-imported EXE/resident sigs.)
- **`make report`** (gated `BINARY=main`) runs **`tools/dup_report.py --cross`** → `docs/duplicates.cross.md`:
  cross-binary duplicate groups across main + resident + all overlay sigs, ranked by collapsible bytes (the
  Phase-12/13 work queue), + **`tools/dedup_integrate.py --check`** (the byte-honesty gate — fail-closed if a
  registered share's sig hash drifts).
- **Share a matched fn across binaries**: author the body ONCE as a macro in `src/shared/<fn>.h`, instantiate at
  each site in each binary's `.c`, register the group in **`config/dedup.us.yaml`** (`{id, tier, hash, source,
  func, members:[{binary, vram, name}]}`). Byte-gate = per-binary `make check`. `h_exact` = risk-free; `h_norm`
  = candidate (accept only if every claiming binary stays byte-identical). NOT an object swap — game-code fns are
  interior to one object per binary (cookbook §11 / deviation D1).
- `tools/sig_image.py`: `h_exact` byte-matches the Ghidra dumper (validated 100% on the resident contiguous set);
  `h_norm` is self-consistent within the overlay fleet (not Ghidra-byte-exact — D2); overlay boundaries via linear
  partition + `detect_code_end` (BFS fails — overlays dispatch via function-pointer tables, not `jal`).
- **PsyQ provenance (R24)**: the resident is PsyQ **4.7** (`tools/psyq/conv47/`, sha-recorded in
  `tools/psyq_CHECKSUMS.sha256`) — Phase 12 links its embedded SDK code from 4.7, not the EXE's 4.0 libs.

## §6.9 Running a matching wave — see `docs/wave-playbook.md`

**GATING IS FULLY PARALLEL AS OF P31 S67 — there is no serial lane.** `tools/parallel_gate.py`
handles jtbl carves too (`isolate_asm()` gives a carving worker a writable copy of the ONE binary's
3.6-5 MB asm subtree instead of symlinking all 448 MB). Measured: 13 fns/13 binaries in 139 s and
19 fns/14 jtbl binaries in 188 s, against 58 minutes for a single jtbl binary serially.
**Always `make -j$(nproc) build`** — a per-binary build is ~35 objects and was single-threaded
(7.18 s -> 1.18 s, byte-identical); every tool that shells `make build` now passes `-j`.

The start-to-finish operational sequence (draw → cards → packs → validate → draft → split-gate →
twin_sweep → harvest → R22 → checkpoint), with the measured failure that justifies each guard.
The tooling-inventory rows below are the per-tool REFERENCE; the playbook is the PROCEDURE.
`docs/automation-runbook.md` is the retired OpenRouter-era campaign — not the current pipeline.

## §7 Session-start ritual

> **Claude Code load order (2026-09-05, R64 candidate):** `PROJECT_CONTEXT.md` → `phase-ends/DIGEST.md` (all phase synopses + all
> rules in full) → the THREE most recent `phase-ends/PhaseEnd_*.md` → `phase-ends/CURRENT_PHASE.md`, then the 🛑 SESSION
> CHECKPOINT block is replayed VERBATIM into the chat. Budget ≈100k tokens + the checkpoint. Never read all PhaseEnds,
> `phase-ends/logs/`, the whole cookbook or `docs/cookbook-index.md` at session start (CLAUDE.md is the authority).
> The Ghidra steps below apply only to RE sessions (G2) — the MCP server now runs headless via the SessionStart hook.

Order is load-bearing — MCP tools fail (sometimes silently) without an open program.

1. **Start Ghidra** (in WSL, under WSLg): `~/ghidra_12.1_PUBLIC/ghidraRun`.
2. **Open the BFM project → open `SLUS_007.26` in CodeBrowser.** Confirm the GhidrAssistMCP control panel (Window → GhidrAssistMCP) shows the server up on `localhost:8080`.
3. **Start/resume Claude Code** in `~/bfm-decomp`. Run `/mcp` — the `ghidra` server must be connected with ~38 tools. Then make one cheap verification call (e.g. `get_binary_info`) before any heavier work. No MCP round-trip = no RE work this session (rule G2).
4. **Build preflight** (when the session involves building, Phase 4+):
   ```bash
   cd ~/bfm-decomp
   git status --short && make check-env
   ```
   One tree to check — clean or intentionally dirty before starting.
5. If PCSX-Redux work is planned: launch it (under WSLg), confirm the web server port (§3) and that a RAM dump fetch returns 2 MB.

Shutdown note: Ghidra writes the program DB on save — save (or deliberately discard) before closing, and never kill Ghidra mid-MCP-write.

---

## §8 Model strategy per phase

Principle: the oracles (SHA1 check, asm-differ, RAM-dump byte-compares) make *correctness* model-independent — a weaker model can't fake a match. Model tier therefore buys **fewer dead ends in ambiguous work**, not safer results. Spend the strongest available model where ambiguity is highest; let the oracle-protected grind run on cheaper tiers. (Precedent: psxrecomp's post-mortem — model capability was load-bearing exactly once, on the most ambiguous subsystem.)

| Phase | Reasoning demand | Recommended tier |
|---|---|---|
| 1 — Installs, EXE import | Mechanical | Standard (Opus-class) |
| 2 — Extraction pipeline | Well-specified coding vs byte-exact oracle | Standard |
| **3 — File-loader & overlay-map RE** | **Highest in project** — raw MIPS reading, US address derivation, RAM-dump experiment design | **Strongest available** |
| 4 — WSL setup | Mechanical; **order-flexible** (nothing in 1–3 depends on it — schedule it when the strong-model window is closed or limits are exhausted) | Any |
| 5 — splat config + build skeleton | Iterative debugging, loud error signals | Standard; strongest if available |
| **6 — Compiler fingerprint + first matches** | **Second highest** — ASPSX 2.56-vs-2.67 idiom discrimination is subtle. The fingerprint *analysis* is pure RE and can be front-run before Phase 4/5 exist if a strong-model window is closing | **Strongest available** |
| 7 — Matching at scale | Pattern grind against hard oracle | Standard; smaller tiers acceptable for bulk iteration (cost = wasted iterations, never wrong matches) |

Budget notes (Max 20x plan): long autonomous RE sessions are token-hungry; prefer single-agent flow with oracle checks for in-phase grind, reserving multi-agent fan-outs for verification moments. *Window note (2026-06-10): Fable 5 access expires ~2026-06-22 — priority order for that window: Phases 1→2 fast, then maximum depth on Phase 3, then Phase 6 fingerprint analysis if time remains; defer Phase 4 past the window.*

---

## Tooling inventory

Every script under `tools/` (plus the two report make-targets), grouped by purpose — one line each. Deep HOW-TO is **not** here: see `docs/matching-cookbook.md` (§6 per-module -O0, §8 rodata island, §9.1–§9.5 library linking) and the relevant PhaseEnd.

| Group | Member | One-line purpose |
|---|---|---|
| **MCP lifecycle** | `tools/ghidra_mcp_start.sh` | Spawn the headless MCP server detached → `.run/ghidra-mcp.log`, port 8080 (§2.8). |
| | `tools/ghidra_mcp_stop.sh` | Clean save+close via the `.run/mcp-stop.req` sentinel — the only persistence event; never SIGKILL (§2.8). |
| | `tools/ghidra_mcp_verify.sh` | Read-only persistence re-check `<addr> <name>` after a clean stop (R9). |
| | `tools/ghidra_scripts/BfmMcpServer.java` | The headless MCP server itself (holds an open transaction while serving). |
| **Ghidra headless scripts** (`tools/ghidra_scripts/`) | `ImportPsyqGdt.java` | Resolve `psyq*.gdt` types into the program DTM headlessly (§2.5 step 5). |
| | `ExportSymbols.java` | Dump curated symbols (feeds `config/symbols.us.txt`, R15). |
| | `DumpProgramInfo.java` | Dump program metadata (loader, language, ImageBase, function count). |
| | `DumpFunctionSignatures.java` | Dump function signatures (feeds `make sig-refresh`). |
| | `ImportOverlay.java` | **RETIRED (S45, R33)** — 1-overlay-era hardcoded import; `tools/ghidra_import_raw.sh` is the live path. |
| | `VerifyOverlay.java` | **RETIRED (S45, R33)** — companion of ImportOverlay.java; retired with it. |
| | `GetSymbolAt.java` | Read the symbol at a given address (scripted lookup). |
| | `DecompileAt.java` | Decompile the function at a given address (scripted scaffold). |
| | `DefineFunctions.java` | Disassemble + create functions at splat's validated entry points (`.run/<prog>_funcs.txt`) — completes a raw-blob program's function set (Phase 10). |
| | `ApplySymbols.java` + `tools/ghidra_apply_symbols.sh` | **(P31 S78) The Ghidra MIRROR of the curated symbol file (R15/G6), headless with a real save.** `tools/ghidra_apply_symbols.sh [PROG] [symbols files…]` (defaults `SLUS_007.26 config/symbols.us.txt`; MCP must be STOPPED first) reads `name = 0xADDR;` rows and sets every function/label to its curated name; a name held by another address is moved to that address's own curated name first (`firstfile`/`firstfile2`), else to `<name>__at_<addr>`. Idempotent; prints `BFMAPPLY renamed_funcs=… unchanged=…`; R9-verify with `ghidra_mcp_verify.sh`. **Use this, not MCP `rename_symbol`/`batch_rename`, for renames:** S78 observed 47 MCP renames NOT persisting through the sentinel stop ("Save succeeded", DB grew, names gone — R9 caught it; cause not yet isolated), while the postScript path persisted 73/73 on the first run. |
| **Public flip / CI** | `.github/workflows/no-rom.yml` | **(P33 B7) The ROM-free CI**: job `audits` (audit_public, audit_text_sources, verbatim_check --strict, cookbook_index --check, ghidra_roster --check, work_evidence --selftest, test_lzss, lint_symbol_refs — ≈45 s of checks) + job `compile-only` (binutils-mipsel + `cpp-mipsel-linux-gnu` from apt, cc1 from the tracked tarball sha256-checked, maspsx submodule; PR scope `main resident ov_SC01_077 md_MAIN_013`; `--all` weekly Mon 06:17 UTC + `workflow_dispatch`). Byte-identity is NOT proven in CI (needs the disc) — `docs/verification.md`. |
| **Verification** | `tools/verify_contract.sh` | **(P33 A5/C8) THE recorded contract run**: 00 tree · 01 check-env · 02 family_hseq · 03 `make clean && extract-all && check-all` · 04 sdk-dual (or a recorded SKIP) · 05 tools-health (zero `[warn]`) · 06 audit-frontier · 07 audit-disc · 08 report; one log per step ending `EXIT=<rc>`, abort on the first red (R53), every step asserted by its contract line (R49), `SUMMARY.md` generated → `.run/P33/verify/` (tracked evidence, quoted by `docs/verification.md` §2); step 00 ignores its own output dir. ≈14 min on 32 CPUs. |
| **Publishing** | `tools/progress.py --json \| --readme [--check]` | **(P33 D1/D3)** The same numbers as DATA: `--json` → `docs/progress.json` (schema 1: the four metrics with numerator/denominator/pct, the counts, 218 per-binary rows incl. instruction totals; no run date) + `docs/badges/{fleet_instr,fleet_fn,distinct,binaries}.json` (shields endpoint format; the README references `fleet_instr` + `binaries` by name); `--readme` rewrites the README's `<!-- progress:begin/end -->` block (refuses a README without the markers); `--check` asserts JSON + block + badges are fresh (in `make audit-digest`). Run by `make report BINARY=main`. |
| | `tools/objdiff_report.py [--in docs/progress.json] [--out report.json]` | **(P33 D3)** progress.json → objdiff's report format (report.proto v2, snake_case — validated with `objdiff-cli` 3.8.1 `report changes`): one unit per binary (code = instructions × 4, functions byte-identical / matchable, metadata complete), categories `game-code` and `linked-sony-objects` (functions only). `.github/workflows/progress.yml` runs it on every push (no rebuild — the committed JSON) and uploads the artifact **`SLUS_007.26_report`** for decomp.dev (Drew registers at decomp.dev/manage/new after the flip). |
| | `tools/frogress_upload.py [--push --project bfm --version us]` | **(P33 D3)** stdlib; `--dry-run` is the default (prints the payload); `--push` POSTs `{"api_key","entries":[{git_hash,timestamp,categories:{default:{measures…}}}]}` to `progress.deco.mp/data/<project>/<version>/` with `FROGRESS_API_SECRET` from the environment (never a file). frogress projects are admin-created — Drew requests the slug + key after the flip. |
| | `tools/public_rewrite/` (P33 C1) | **The history-rewrite package** (`docs/public-flip-runbook.md` §3 is the operating table). `common.py` (shared: the purge rules, the DERIVED content-hash sets, identities from the log, the one hash regex, a persistent `cat-file --batch`) · `hash_dict.py [--write-mailmap]` (every commit OBJECT → `commit:NNNN` / twin / orphan; prefix index 7..40; asserts 0 ambiguous; records content-hash collisions as excluded; writes the scratch mailmap) · `scrub.py --test \| --sample \| --file` (THE scrub: hash tokens, addresses → noreply, trailer lines in messages; 12 known-true cases; the HEAD sample with git's own object lookup as the independent oracle) · `gate_scan.py --all\|--refs … [--worktree] [--expect-fail FIXTURE]` (paths ever touched × purge rules; every reachable blob's content sha1 × the ROM set; 5 byte signatures; 50 MiB; emits `rom_blob_ids.txt` = hits ∪ every blob ever under a purge path; the fixture `expected_offenders.txt` is the R39 negative control) · `run_filter.py [--sample]` (the git-filter-repo 2.47.0 module-API run inside the scratch bare clone; refuses elsewhere) · `verify_rewrite.py --old --new` (the pairwise proof) · `build_commit_map.py [--out]` (`docs/commit-map.tsv`, asserted free of old hashes) · `resolve_tokens.py [--check] [--map]` (tokens → shortest unique ≥9-char new abbreviations at the tip) · `absent_scan.py [--repo] [--tree]` (nothing old anywhere) · `probe_github.sh [--after-flip]` (Drew's purge probe). Scratch (`.run/public_rewrite/`, never committed): `dict.json`, `mailmap`, `rom_blob_ids.txt`, `old-to-new.tsv`, `repo.git`, the bundle. |
| | `.venv/bin/git-filter-repo` 2.47.0 | (P33 C1) `pip install git-filter-repo==2.47.0` (in `requirements-python.txt`); used through its module API by `run_filter.py`. |
| | `tools/audit_public.py [--paths …]` | **(P33 B7) The first-push gate**: no tracked file under `tools/public_rewrite/purge_set.txt` (the C1 rewrite's own input, filter-repo syntax), none whose SHA1 is ROM-derived (DERIVED set: every `sha1` in `extracted/retail/manifest.jsonl` + `config/check.*.sha` + the redump Track-1 SHA1; zero-length files exempt — the empty-file SHA1 is also SC04/SC05 `FILE_029/1.6`'s), none > 50 MiB. Names every offender, exits 1. ≈1 s over 6,798 paths. |
| | `tools/compile_only.py <aliases…> \| --all [-j N] [--list]` | **(P33 B7)** cpp → cc1 → maspsx → as on every eligible TU with the Makefile's flags PARSED at run time; TUs per binary from `<alias>_SRC_DIR` with nested-binary pruning (= the Makefile's `C_SRCS`); skips main's 70 LINKED tiles (`progress._main_linked_segs_from_makefile`) and the 47 `INCLUDE_ASM(`/`INCLUDE_RODATA(` TUs (they `.include` asm/); -O0 TUs (`corpus.o0_sources`) compile at -O0. Coverage line with every denominator. Measured: PR scope 54 of 124 TUs in 1.6 s; fleet 4,170 of 4,287 in 123 s at -j32 (≈50 CPU-min). |
| | `tools/public_rewrite/purge_set.txt` | **(P33 B7)** THE purge set (Drew's decisions 3+11): the EXE at both historical paths, `glob:dumps/*.bin`, `ghidra/`, `tools/psyq/`, `session archive/`, `glob:tools/ghidra-ext/*.zip`, `tools/brave-CUE/brave.exe`. Read by audit_public now and by C1's `git filter-repo --paths-from-file` later. |
| | `ExportAnnotations.java` + `tools/ghidra_export_annotations.sh` | **(P33 B5) The read-only TEXT export of a program** — byte-stable JSONL (fixed key order, sorted, `0x%08x`): `program`/`block`/`archive` container rows, LOCAL-archive types, every function signature (params/locals/storage/sources/comment), defined data, the 5 comment kinds, bookmarks, equates, labels not in the symbol files. `tools/ghidra_export_annotations.sh [PROG…]` → `.run/ghidra_export/<prog>.jsonl` (no arg = all programs in one `-readOnly` run; 129 in 18.5 s). MCP must be STOPPED. |
| | `ImportAnnotations.java` | **(P33 B5)** Idempotent compare-before-write import of that JSONL (creates a missing function for a `func` row; refuses unknown row kinds, R43); prints `BFMANN types=… funcs=… … failed=0 rows=N`. **OSGi gotcha:** Ghidra compiles `tools/ghidra_scripts/` as ONE bundle — a compile error in ANY `.java` there breaks EVERY script ("Failed to get OSGi bundle containing script"); javac diagnostics are not shown — compile by hand: `javac -nowarn -d .run/javac_check -cp "$(find ~/ghidra_12.1_PUBLIC/Ghidra -name '*.jar' -path '*/lib/*' | tr '\n' ':')" tools/ghidra_scripts/*.java`. |
| | `tools/ghidra_annotations_delta.py` | **(P33 B5)** `live.jsonl baseline.jsonl out.jsonl [--census]` — the HAND-AUTHORED part of a program = live rows not in the fresh rebuild's baseline (container rows always kept), minus three counted analysis-drift classes: `Error`/`Analysis` bookmarks; `func` rows absent from the baseline with a DEFAULT signature, no comment and an auto name (function-set drift); `func` rows differing from the baseline only by an auto name (the DB lagging the curated symbol file, R15). Prints the census + the dropped counts. |
| | `tools/ghidra_rebuild.sh <program> [--proof] [--keep]` | **(P33 B5) Rebuild ONE program FROM TEXT + the disc** in a scratch project (`build/ghidra_rebuild/proj` — Ghidra refuses a path component starting with `.`, so not `.run/`): import (PSX loader for the 3 EXEs, raw blob at `make -s print-VRAM_BASE` otherwise) + analysis + psyq400.gdt → `DefineFunctions` from the built ELF → `ApplySymbols` (the yaml's symbol files) → baseline export → `ImportAnnotations config/ghidra/<program>.jsonl` → export → delta. `--proof`: `cmp` delta vs the committed file → `PROOF PASS`/`FAIL` (+ `.run/ghidra_rebuild/<program>.proof` marker). Without a committed file it writes `<program>.candidate.jsonl` to review. MCP must be STOPPED. ≈65 s resident/overlays, ≈200 s the EXEs. |
| | `tools/ghidra_roster.py [--check]` | **(P33 B5)** `config/ghidra/ROSTER.md` from the committed files: kind/payload/vram (from the build registry), blocks, hand-authored census, last proof marker. |
| | `DecompileFunctions.java` | **Batch**-decompile a list of addresses (arg0 = addr-per-line file, arg1 = out-dir) → `<name>.c` each. Headless harvest Ghidra-C pre-pass (Phase 17); no live MCP / `/mcp` needed. Run: stop MCP, `analyzeHeadless ghidra bfm -process <prog> -noanalysis -postScript DecompileFunctions.java <addrfile> <outdir>`. |
| | `tools/ghidra_import.sh` | Headless `analyzeHeadless` import/analysis driver (PS-X EXE; auto-detect PSX loader). |
| | `tools/ghidra_import_raw.sh` | Headless import of a RAW flat blob — `BinaryLoader` + `--loader-baseAddr <vram>` + `PSX:LE:32:default` (resident blob / Gen2 overlays; no PS-X EXE header). |
| | `tools/prefetch_fleet.py` | **The fleet Ghidra-C prefetch batch** (P30 T0.5): one representative per remaining h_seq distinct class + ALL main/resident stubs → `.run/ghidra_c/`, resumable (skips cached), serial on the project lock; auto-stops a serving MCP (R23 — R29 applies at next MCP use); imports a missing overlay program on demand (`ghidra_import_raw.sh`, blob via `family_remap.img_path`, vram via the splat yaml). `--dry-run` / `--limit-programs N` (probe-first). R32: per-program outcome report, batch continues past failures. |
| | `tools/family_cousins.py` | **(P30 S49, cookbook §168)** The COUSIN-UNIT survey — the similarity tier ABOVE h_seq. h_seq is an exact skeleton hash, so ±1 instruction (li-expansion, table-size drift) fragments same-source families into "singletons"; this tool clusters the distinct open skeletons by mnemonic-stream similarity (≥0.85, union-find) and attaches the best MATCHED-skeleton seed per unit → `.run/family_cousins.json` + `docs/family-cousins.md`. Categories A-prop / seeded / cousin-multi / cold. `--targets N --wave waveN` emits the crack_wave.js slate ranked by whole-UNIT open ins, with each seed's C body location (engine_core.h macro or inline src file) resolved. R32 both ways: fails loud on a stale family map (independent stub recount) and on a partition defect. RANKS AND SEEDS ONLY — cousins need a per-member seeded CRACK (skeleton drift ⇒ recompile), never a `family_sweep` remap; the whole-binary byte-gate stays the sole arbiter. |
| | `tools/aprop_symfix.py` | **(P30 S50, cookbook §171)** The stale-SEED-SYMBOL guard for the adapt/A-prop lanes — the second, DISAGREEING oracle (R34) for the one class `match_one` is structurally blind to. A per-location data symbol (`D_8018xxxx`) carried out of a seed body unrebased scores MATCH standalone (encodings identical; the scorer cannot see a relocation's target NAME) and dies in the host TU at link with `undefined reference`. Audits every draft's vram-suffixed symbols against the symbols the TARGET's own `.s` relocates; `--fix` rewrites the 1:1 cases and emits a `gate_lane`-shaped slate. Deterministic, no build — run it BEFORE the gate, never after. Measured on the S49 A-prop residue: 24 of 24 concentrated failures were this class, 23 banked after the rebase (A-prop conversion 57% -> 87%). Its primitives are imported by `family_cousins.py`, whose `--aprop-cards` members now carry an explicit `sym_map` of `{seed -> member}` renames. |
| | `tools/aprop_autodraft.py` | **(P30 S50, cookbook §171a)** Mechanically drafts lane-A members with NO agent in the loop — seed body + `family_remap.symbol_map` (positional reloc zip) + a MINIMAL preamble synthesized from scratch, so the seed's declaration layer never travels (that layer is `family_sweep`'s dominant failure: 331 of 458 S49 verdicts). Handles inline AND `DEFINE_<fn>()` macro seeds (take the DEFINITION; the block is only the decl source — pasting it whole scored 28% vs inline's 68%), and applies T2a's `imm_map_tier1` so a per-location LITERAL resolves like a per-location symbol (131 of 275 IMM members). REFUSES at generation time what cannot work: non-PURE members, arity conflicts, undefined data, and `.s` files carrying data or a jtbl. **256 banked at zero agent tokens.** Every draft is a candidate — gate via `gate_lane.py`. |
| | `tools/draft_prechecks.py` | **(P30 S50)** Static pre-checks shared by the draft tools: arity disagreement vs the destination's own declaration, and symbols nothing in the destination binary defines. Both are real measured build failures and both are decidable WITHOUT compiling — at ~1 min per gate group that difference is the run. Negative-controlled against all 205 banked drafts of the first run (zero false positives; catches 39 of 67 known failures); that control found two bugs in the checks themselves — C89 `f()` declares UNSPECIFIED parameters (not zero), and a member's own definition read as a call to itself. Deliberately CONSERVATIVE: flags only `decl > call` on named parameters, because a pre-check that discards good drafts is worse than one that lets a few builds fail. |
| **Disc/.CD extraction** (`tools/bfm_extract/`) | `extract.py` | Walk the disc / extract root files (`make extract`). |
| | `extract_exe.py` | Extract & verify `SLUS_007.26` (`--verify-disc`, owns `EXPECTED_EXE_SHA1`). |
| | `extract_proto_exe.py` | Extract the prototype/demo EXE for cross-checking. |
| | `cd_archive.py` | Parse the `.CD` container format. |
| | `pac.py` | Parse the PAC archive format. |
| | `lzss.py` | LZSS (de)compression for packed blobs. |
| | `manifest.py` | Build/verify the extraction SHA1 manifest. |
| | `crosscheck.py` | Cross-check extracted bytes against the runtime RAM dump. |
| **Matching harness** | `tools/decompile.py` | m2c wrapper — C scaffold for a function (§6.6). |
| | `tools/match_protos.py` | Match prototype-EXE functions against retail. |
| | `tools/permuter/` | decomp-permuter harness (PERM_ recipes/weights) for stubborn near-misses. |
| | `diff_settings.py` *(repo root)* | asm-differ config (arch `mipsel`, object mode vs `expected/`). |
| | `tools/new_overlay.sh` | One-command location-overlay onboarding: `<SCxx> <FILE_nnn> [ENTRY]` — instantiate `config/splat.<ov>.yaml` from the template (+ non-4-aligned `bin` carve), register the binary in `config/overlays.mk` + the report/diff dicts, `make extract && build` byte-check. Idempotent (Phase 13, cookbook §13). **Phase-27 T7:** the optional `ENTRY` arg (default `0.4`) reaches a non-`0.4.dec` payload — the 4 SC07 overlays put code at PAC entry 1 (`1.4`). difficulty.py dropped from the insertion set (it derives now, T6). |
| | `tools/disc_code_sweep.py` | **RETIRED (S45, R33)** — superseded by `tools/disc_audit.py` / `make audit-disc` (whole-payload, BOTH raw+LZSS layers, residue-0 partition, claimed-by derived from `config/check.<bin>.sha`). The sweep read only the RAW layer through a 4,096-word window and had no notion of a claim; its historical findings are preserved in `docs/disc-completeness.md`. |
| | `tools/new_binary.sh` | **(P30 S44/S45)** One-command onboarding for ANY flat-blob binary class: `<alias> <payload> <VRAM> [TEXT_LO]` — ov_* (overlay slot, registry `overlays.mk`) or md_* (own §S44 slot, registry `modules.mk`). Signs (TEXT_LO-aware §154), instantiates the shared template (non-zero TEXT_LO ⇒ paired-`.rodata` header carve), writes check.sha + symbols, registers in the registry + the 3 report/diff dicts (sentinel-anchored, ast-checked), extract+build byte-check. Idempotent. `new_overlay.sh` is now a thin wrapper over it. §6.7 module recipe. |
| | `tools/find_addr_refs.py` | **Register-tracked** search for code that materializes an absolute address (§155: never window-paired). `<addr> [--binaries a,b]`. **S46:** also follows the hi half through an index `addu`, so gcc's indexed global-array read (`lui`/`addu`/`lh lo(base)`) is no longer invisible — those hits are labelled `-indexed` (cookbook §155c). `scan_all()` is the one tracker other tools import (R33). |
| | `tools/idxtab_map.py` | **(P30 S46)** The master **IDXTAB → payload → owning binary → DESTPTR load address** map, fleet-wide. Controls-gated (R32/R35 — refuses to emit if the two byte-proved rows don't reproduce); process-pooled; `--controls-only` / `--binaries` / `--min-len`. Output `.run/idxtab_map.json`; **read `docs/idxtab-map.md` for what it does and does NOT prove** (it cannot show a payload is dead — byte-proved loaders are absent from this route too). |
| **PsyQ library linking** (cookbook §8/§9) | `tools/psyq_lib_split.py` | Split a PsyQ `.LIB` into per-object members. |
| | `tools/psyq_build_libs.sh` | Build the PsyQ libs from split members. |
| | `tools/psyq_identify.py` | Identify which SDK objects a region's functions belong to. |
| | `tools/psyq_link.py` | Link identified PsyQ objects into the build. **P31 S78 #4:** `link_object` first runs `psyq_bss_split.prepare_object` (the same prepare step the region verify and the build use), so its PASS/FAIL is the build's verdict for scattered-`.bss` objects; links with `--no-check-sections` like the build. |
| | `tools/psyq_bss_split.py` | **(P31 S78 #4, cookbook §489)** Splits a PsyQ object's scattered `.bss` into per-base NOBITS pieces (`.bss`, `.bss2`, …) — a pure-Python ELF32 REL rewrite: bases derived from the game bytes per HI16/LO16 pair, runs in offset order, cuts snapped to symbol starts, relocs retargeted with the addend rewritten in place, self-checked. Refuses (loud, R43) a sized symbol straddling a cut or a HI16 shared across pieces. Runs automatically inside `psyq_link` / `psyq_link_region` / `psyq_integrate` (`prepare_object`); the CLI reports a plan (`--vram --exe --vram-base`, `-o` to write). Takes SYS.o (2 pieces), VM_F.o (2), GS_001.o (6). |
| | `tools/psyq_link_lib.py` | Per-library link driver. |
| | `tools/psyq_link_region.py` | Link a specific address region from PsyQ libs. |
| | `tools/progress.py` (weighted main) | **(P31 S78)** `MAIN game-code weighted` now excludes LINKED subsegs LIVE (`_main_linked_ranges`: Makefile `psyq_integrate` stub lists → yaml ranges, R33); the 2026-08-05 sig had carried all linked-SDK instructions, under-reporting main by ~32 points (59.8% → 91.8%). |
| | `tools/psyq_integrate.py` | Integrate linked PsyQ results back into the source tree. **P31 S78:** `--yaml <splat yaml>` (every main call passes `$(main_SPLAT_YAML)`) maps stub↔objects by SUBSEG RANGE with an exact-tiling check and PRINTS the located-but-unwired objects (`~~ N located object(s) / M ins OUTSIDE the stub subsegs`) — the completion contract's SDK-residue line; and a library object's DEFINED symbol whose recovered address the curated symbol file names differently is `--redefine-sym`'d to the curated name (R15; e.g. libapi 4.0 `A66.o` `firstfile`→`firstfile2`). Without `--yaml` the old contiguity mapping runs (overlay-free libraries only). |
| | `tools/make_libgs.sh` | Build/link the `libgs` block (cookbook §9). |
| | `tools/gen_lib_subsegs.py` | **(Phase 8)** Generate splat subseg lines + integrate stub list for a multi-block library (section-size-correct boundaries; cookbook §9.6). |
| | `tools/make_snd_used.py` | **(Phase 8)** Build the combined libspu+libsnd curated dir (alias dedup by byte-match; 3 address exclusions since S78 #4 — VM_F rejoined via the `.bss` split; §9.6). |
| | `tools/make_apicard_used.py` | **(Phase 8; S79 #5)** Build the combined libapi+libcard curated dir `.run/obj42/apicard_used` — libapi **4.2** (`.run/obj42/libapi42`, the EXE's real libapi, incl. FIRST/PAD/PATCH/CHCLRPAD) + libcard 4.0 (§9.6, §490). |
| | `tools/ld_interleave.py` | Interleave linker inputs to match the original section ordering. Three forms: `--front/--tail` (the original data->rodata->data sandwich), **`--order`** (P31 S72 — an address-ordered leaf list, needed once a binary owns SEVERAL `.rodata` carves: a `*.data.o` leaf contributes its `(.data)`, a code-object leaf its `(.rodata)`; main's island is a 7-piece sandwich `--front/--tail` cannot express), and **`--pre`** (P31 S74, cookbook §440 — a piece that must land BEFORE the text). `--pre` exists for the **resident**, which opens with `- [0x0, rodata, hdr]`, a 1-word `.rodata` header ahead of its code: every `--order` piece is emitted after TEXT_START, so `hdr.rodata.o(.rodata)` would fall into the unchecked `empties` bucket, be parked after the text, and move every byte in the binary. |
| | `tools/jtbl_rodata_pads.py` | **(Phase 29, cookbook §8e)** Post-maspsx filter for multi-table `.rodata` carve spans: REPLACES each cc1 `.align 3` (which is section-relative and would mis-pad a merged/4-mod-8 span) with the ORIGINAL's exact pad bytes per the object's `JTBL_PADS` spec (written by `jtbl_carve` into `config/overlays.mk`; armed via `$(if $(JTBL_PADS),…)` in the Makefile `build/src/%.o` recipe). Fail-loud on table-count drift / non-`.align 3` / non-jtbl rodata content. Unset var ⇒ pipeline byte-identical. |
| | `tools/split_src_region.py` | Split a `src/` region file at object boundaries. |
| | `tools/rollout_whale_o0.py` | **(Phase 24 W9)** Roll out the -O0 whale `func_80144B9C` ×134: per single-file overlay, line-split `<ov>.c` at the whale, carve the yaml code subseg into before/`_o0b`(-O0)/`_after`, write a thin `<ov>_o0b.c` that `#include`s the shared `src/shared/func_80144B9C.h`. Idempotent; the `WHALE_O0B_OBJS` Makefile wildcard -O0-compiles all `_o0b.o` (cookbook §38). |
| **Reports** | `tools/progress.py` | Per-binary decomp progress (`make report`); counts dedup-shared fns as REAL via the registry (Phase 11). **`--fleet`** (Phase 15) aggregates all 136 binaries → `docs/progress.fleet.md` (deterministic, source-derived). **`--weighted`** (Phase 25) prints the two BYTE/instruction-weighted metrics from `.run/sig.*.jsonl` (executable code only): **instr-weighted** (fleet per-overlay, the decomp.dev-display number) + **distinct-code** (dedup, each unique fn once, the distinct-RE number); both also fold into `--fleet` alongside the ×134-inflated function-count %. Needs `make sig-overlays` first; degrades gracefully without sigs. |
| | `tools/difficulty.py` | Per-function difficulty scoring. |
| | `tools/dup_report.py` | Duplicate-function report; `--cross` (Phase 11) buckets all binaries → `docs/duplicates.cross.md`. **Phase 15:** ingests each overlay once (named ∪ `sig.ov_*` glob, deduped by alias) — else onboarded overlays double-count and inflate collapsible bytes ~2×. |
| **Cross-binary dedup** (Phase 11, cookbook §11) | `tools/sig_image.py` | **Ghidra-FREE** per-function signer for a flat image (overlay/resident); `h_exact` byte-matches the Ghidra dumper, self-consistent `h_norm`; linear-partition + `detect_code_end` boundaries. |
| | `tools/dedup_integrate.py` | Byte-honesty validator for `config/dedup.us.yaml` code-shares (`--check`; fail-closed on sig-hash drift). |
| | `tools/dedup_propagate.py` | **(Phase 15, cookbook §14)** Match-once → propagate-many: lift a matched body, author a `DEFINE_func_<ADDR>()` macro in `src/shared/engine_core.h`, instantiate it at every onboarded overlay sharing that `h_exact`, byte-gate each (fail-closed), register in `dedup.us.yaml`. `--addr`/`--auto-from`/`--check-only`. `find_site` accepts brace on the same OR next line (Phase-15 fix — next-line-brace defs were silently un-propagated). |
| | `tools/sig_unify.py` | **(Phase 15, cookbook §14d)** Deterministic hard-tail recovery: unify a gate-failing draft's FULL signature set — callee externs **and** the draft's OWN definition signature — to the banked-canonical decls (`--overlay`/`--in`/`--out`); the whole-binary byte-gate stays the arbiter. Recovered 32 of 191 standalone-MATCH conflict-blocked drafts, zero agent tokens. |
| | `tools/gen_harvest_targets.py` / `tools/canon_draft_decls.py` / `tools/build_engine_types.py` | Callee-sig-aware target manifest (§14b/c) / callee-extern canonicalizer (§14c) / additive shared-types-header extractor (`src/shared/engine_types.h`, §14 struct; **Phase 20: also lifts typedefs — anon-struct / fn-ptr / alias — with collision + tagged-struct-typedef-overlap guards, closing the §19 type-blocked propagation cap**). |
| | `tools/canon_resident_calls.py` | **(Phase 19 / T2, cookbook §17a-3a)** Link-miss recovery: rewrite each `func_<ADDR>` in a draft to the **curated** resident symbol name when that address has one in the stacked symbol files (`0x8004CFEC`→`ratan2`), so the linker resolves it. Pure draft-text (body bytes unchanged); **run FIRST** in the recovery pipeline `draft → canon_resident_calls → sig_unify → harvest_verify`. |
| | `tools/fix_arity_callers.py` | **(Phase 19 / T3, cookbook §17a-3b/§19)** The no-prototype recovery for the dominant gate-failure class: a banked SHARED caller in `engine_core.h` declares the callee `extern <ret> func_X(void);`, conflicting with a real def that takes args. Rewrites that caller decl to `extern <ret> func_X();` (`--apply`, byte-neutral; skips narrow-param defs via `--drafts`; `--revert` undoes). Re-gate after. |
| | `tools/cast_call_sites.py` | **(Phase 20, cookbook §20)** The §17a-1 per-site function-pointer cast recovery for the loose-typing CALLEE-conflict class: per draft, for each callee whose canonical TU sig differs from the draft's intended sig, rewrite the decl line → canonical (kills the in-TU `conflicting types`, keeps the symbol in scope) AND cast each call site → the draft's intended sig `((ret(*)(args))func_X)(args)` (decl lines never cast; gcc folds the cast of a known symbol → direct `jal`). Pure `--in`/`--out`; whole-binary gate is the arbiter. Pipeline `canon_resident_calls → cast_call_sites → sig_unify → harvest_verify --chunk 1`. Recovered 6 of T6 batch-1's 33; the rest are the def-side loose-typing wall (caller-side blocked: INCLUDE_ASM declares nothing). |
| | `tools/reconcile_decls.py` | **(Phase 24 T7b, cookbook §33)** The **DATA-symbol** analog of `cast_call_sites`: a fleet-majority canonical-type **oracle** (`engine_core.h`-authoritative + plurality across all overlays+resident; `--print-canon D_XXXX`) + a byte-neutral access-cast **transform** — rewrite each loose `extern <T> D_XXXX...;` → the canonical decl and cast every use to the intended type (`(Ed*)D_x` array, `(Ed*)&D_x` struct-base, `*(Td*)&D_x` signedness, `(*(P**)&D_x)` ptr-in-scalar). Mechanizes the manual giant decl-reconcile. Pure `--in`/`--out` (+`--overlay`/`--src-file`); wired into `gate_stage` after `cast_call_sites` (idempotent/no-op without a data conflict); whole-binary gate is the arbiter. Byte-proven: full loose `func_80129CF8` → reconcile → `make build BINARY=ov_SC01_077` = `d19c9580`. |
| | `tools/scope_data_externs.py` | **(Phase 26 session 8, cookbook §8d)** The `scoped` stage of `jtbl_family_bank` — places a templated body's **DATA** externs at the scope the target TU can accept. `family_remap.gather_externs` prepends carried decls at FILE scope; for a per-location symbol the sibling declares only at BLOCK scope inside its own later functions, that decl **establishes a global the TU never had** and every later block-scope `extern` must now agree with it (loose typing ⇒ they don't) → `conflicting types for D_801812A4`. Fix: demote the carried `D_` extern to **block scope inside the function body** when the TU has no file-scope decl of it above the insertion point. Byte-neutral (an `extern` emits no code; type + access opcodes unchanged), never worse than raw ⇒ needs no oracle, no type comparator, no fn-ptr parser. **Use this, not `reconcile_decls`, for the templating class** — that tool's oracle is fleet-majority (wrong question) and its regex cannot parse `extern void (*D_x[])(void *);` (silently skips the failing symbols). Library `fix(body, tu, pos, func)`; CLI `--body/--tu/--func[/--out]`. Byte-proven: `func_8015AE2C` (562 ins) ×133. |
| | `tools/scope_tu_externs.py` | **(Phase 29 T48/T51, cookbook §103)** The **TU-side** complement of `scope_data_externs`: move the target TU's **own** file-scope `extern` decl of a contested `D_` symbol down into every later function that references it and lacks its own block-scope decl, then delete the file-scope line. Needed because §8d's give-up branch **drops the draft's decl** when the TU already declares the symbol at file scope — right when the types agree, fatal when the byte-true draft needs a different one (a file-scope decl constrains every LATER function in the TU). Declaration-only ⇒ byte-neutral; verify in two steps (decl move alone rebuilds byte-identical, *then* splice). Contested set is **derived** (the remapped draft's block-scope `D_` externs ∩ the TU's file-scope decls above the splice point), never hand-listed. Built on `cdecl.split_statements`/`_mask` (comment-masked spans — not a 7th regex); **refuses loudly** (R32) on a duplicate file-scope decl, a file-scope reference below the decl, or an ambiguous body brace, and asserts coverage as a **delta** (file-scope −1, block-scope +consumers). Library `scope(tu_text, syms, above)`; CLI `--tu/--syms/--above` or fleet `--family/--from/--from-addr/--members [--in-place]`. **Wired into `jtbl_family_bank` (T53) as the `tu-scoped` stage** — after `raw`/`scoped` (it edits outside the spliced body), before `recovered`/`reconciled` (those bend the DRAFT, measured at +3 ins for this class). Byte-proven: `func_80135260` ×132 TUs banked 132/132, R22 clean-fleet 140/140; counterfactual on a reproduced blocker = raw compile-error / scoped byte-mismatch / **tu-scoped BANKED**. |
| | `tools/inject_capped_externs.py` | **(Phase 23, cookbook §28d)** The "macro-extern-injection" lever for reach-134 fns matched INLINE in ov_SC01_077 but skipped by `dedup_propagate` as "not self-contained": source the EXACT file-scope `extern …;` the overlay already declares for each referenced `func_`/`D_` symbol and inject it BLOCK-scope so the lifted macro body resolves in every overlay. Byte-neutral (gate proves 077 stays `d19c9580…`); fail-safe (only rewrites a fn whose injected body then `compiles_standalone`). `--overlay`/`--src-file`/`--min-reach`/`--apply`. Then `make build BINARY=ov_SC01_077` → `dedup_propagate --auto-from`. |
| | `tools/exemplar_miner.py` | **(Phase 20 / T2, cookbook §20)** Residual router: consume `.run/wall_taxonomy.json` (bucket/nins) + per-overlay reach (dedup_propagate's computation) → route every residual stub to a lever (WAVE / STRUCT / PINS / STUB) ranked by reach×size → `docs/exemplar_curriculum.md` + `.run/exemplar_routing.json` (wave-target list). "Scan all residuals, size the pools, pick the teachers." Caveat: its `mismatch` is the M2C-draft mismatch, not the hand-match floor. |
| | `config/dedup.us.yaml` / `src/shared/*.h` | The code-share registry + the shared bodies (one macro → N sites, byte-gated). |
| | `make report` / `make sig-refresh` / `make sig-overlays` | Convenience targets: reports (+`--cross`) / Ghidra signature-dump / Ghidra-free sign all 134 overlays. |
| **LLM matching tier** (Phase 21–23, `docs/gen2-mips-matching-model.md`) | `tools/gate_stage.py` | The shared deterministic bank/log spine: `canon_resident_calls → cast_call_sites → sig_unify → harvest_verify (byte-gate) → dedup_propagate → backlog`. **Binary-agnostic** (resolves src/asm/out/good_sha + bare-hash from `binary`; Phase-23 fix). **Phase-23 T10:** optional `lock_path` (per-binary lock) / `verified_out` / `failed_out` (per-worker scratch) / `compute_fleet` for `bulk_harvest`'s parallel gate — all default to the serial behavior. |
| | `tools/harvest_verify.py` | The whole-binary byte-gate (substitute draft → `make build` → keep iff byte-identical, else revert). Sole arbiter (G3/P9). `--verified-out`/`--failed-out` = per-worker result paths (parallel gating, Phase-23 T10). **(P31 S74)** The duplicate-typedef strip-set is computed **SCOPED**: `cdecl.typedef_names(path, above=fn)`. Unscoped, it stripped from a draft a typedef declared BELOW its splice point — the draft's own copy was the only one in scope — and the result was `parse error`, logged as PLUMBING and indistinguishable from a real declaration conflict (cookbook §441). One function was blocked by that alone. |
| | `tools/rtu_match.py` | **(Phase 25 wave-3, cookbook §42b)** REAL-TU-faithful per-fn match check that fixes match_one's blind spot: splices a candidate into a copy of the split `.c`, neutralizes `INCLUDE_ASM` (`-DINCLUDE_ASM(a,b)=` → no `asm/` needed) with `-Isrc/<source>` for the relative `../shared/` include, compiles the WHOLE TU (`cc1→maspsx→as`), masked-diffs the fn (shared `masked_diff`). Captures the in-TU decl/global-type/memcpy-builtin drift that isolation (`match_one`) misses, so a MATCH holds at the whole-binary gate; per-fn temp dir → **parallel-safe, no shared overlay build** (enables a real-TU-faithful crack fan-out). Supports `//@EDIT old||new` file-scope pre-edits (the §42b read-global s16→u16 flip). STILL finish on `make build` SHA (G3/P9). |
| | `tools/diff_autopsy.sh` | **(Phase 31 S62 T1, cookbook §301)** The gate said DIFF, this says WHERE: splices the raw draft into the real TU exactly as the gate does, builds, `cmp`s against the byte-good binary, decodes the diverging words, restores tree + build. `tools/diff_autopsy.sh <binary> <fn> <tu.c> <draft.c>`. |
| | `tools/stub_invariant_audit.py` | **(Phase 31 S62 T1, cookbook §301)** Regression test for the masked comparer: INCLUDE_ASM pastes the original bytes, so `diff_object_s(object, .s)` must be 0 for every stub; quotes the denominator (stubs with internal-`j` relocs). Run after ANY change to `masked_diff.py`. |
| | `tools/interleave_check.py` | **(Phase 31 S62 T2, cookbook §302)** Order ⇔ yaml consistency for an overlay's jtbl carve: the `_JTBL_INTERLEAVE` order must equal the yaml subseg sequence position by position. `--fix` regenerates the order from the yaml (never hand-edit it). Run after ANY restore of overlays.mk or a splat yaml (two of the five S61 reds and four of the six clean-sweep failures were exactly this). |
| | `tools/pads_audit.py` | **(Phase 31 S62 T2, cookbook §302)** DERIVES each object's `JTBL_PADS` from the bytes: compiles the TU to count its tables, walks the retail words inside the yaml carve with those sizes (pad 4 ⇔ one zero word), reports SPEC-DRIFT / CARVE-DRIFT / ok with the derived spec. Reproduced 15/15 correct specs as its negative control; replaced S61's blind value searches. |
| | `tools/claude_wave_packs.py` · `tools/workflows/claude_wave_draft.js` · `tools/wave_judge.py` | **(Phase 31 S62 T4)** The Claude-subagent wave harness that ran the model-ladder probe: identical packs from `api_agent` (SYS + user_msg + law-1c warm start + gate feedback) → a Workflow of drafting agents per (arm, fn) with CLI equivalents of grep/read_file/match_one/submit, writing only under `.run/<wave>/<arm>/` → `wave_judge.py` gates each arm with `sweep_parallel` (banked = removed INCLUDE_ASM lines in `git diff`; tree reset between arms; `--union` leaves the cheapest winning drafts in the tree). `tools/workflows/claude_wave_distill.js` = the R16 distill (extract per byte-proven transcript → verify vs the cookbook). Routing rule from T4: ≤50 Sonnet, 51–120 Sonnet, >120 Opus, Opus on residue; haiku retired; DeepSeek optional at ~$0.03/fn. |
| | `tools/t5_targets.py` · `tools/t5_cards.py` · `tools/wave_card_fuel.py` · `tools/t5_bank.sh` | **(Phase 31 S63 T5)** The wave *draw* and the wave *bank* halves around the T4 harness: `t5_targets.py --wave .run/t5x --n 48 [--residue .run/t5w] [--main-only]` draws a routed slate (open per `corpus.stubs`, ledger `.run/t5/drawn.json` keyed (binary,fn), ≤120 ins → sonnet / >120 → opus, residue → opus once, stratified by band, ≤4 per binary, one fn NAME per wave — the harness keys packs/drafts by bare name, so `claude_wave_packs`/`wave_judge` now REFUSE duplicates, R43/R48); then **`t5_cards.py --wave .run/t5x`** BUILDS the target's OWN card fuel (`tu_ref` = in-TU banked neighbours §194-E, `decl_prior` = fleet signatures §196) from `wave_card_fuel.py` — those helpers extracted VERBATIM out of `build_wave_atlas.py` (which parses argv at import and so was unusable as a library) so both consumers share ONE oracle (R33); measured 88% tu_ref / 98% decl_prior on a fresh K-class slate, against 0% correct fuel before the fix. Then `claude_wave_packs.py --cards <wave>/cards.json` → Workflow `tools/workflows/claude_wave_draft.js` `args={wave, targets}` (one agent per target, `model=target.arm`) → `tools/t5_bank.sh .run/t5x sonnet opus` (refuses if a lane/gate runs or src/ config/ is dirty; `wave_judge --union`; then a RECOVERY pass — every un-banked draft through `fix_tu_ret_decls`, which retypes a destination TU's `extern void` decl on a value-returning function and re-gates (wave t5a: 2/2 banked, both byte-exact bodies refused for that decl alone); then the R22 clean fleet sweep parsed `N passed, 0 failed of N`; commit `— N banked`). |
| | `tools/jtbl_rodata_pads.py` — S74 corrections | **(P31 S74, cookbook §436-C/§441)** Three measurement bugs in the island walk, all of which ACCUSE THE CARVE when they fire. (a) `_s_rodata_span` ignored a **trailing `.align`**: a `.s` ending `.asciz "r"` + `.align 2` occupies 4 bytes, not 2. Latent by construction — `--derive`'s `zero_gap` self-corrects a 1-3 byte undershoot whenever the next item is an anchor, and **a C jump table has no anchor**, so it fires only when someone banks a switch function into such an object. (b) `_items` matched a rodata anchor only as `D_xxxxxxxx:`, missing the `labels.inc` macro form **`dlabel D_xxxxxxxx`** that an inline `__asm__` in C produces (as expands it; cc1/maspsx pass it verbatim) — an 8-byte hole in the walk. (c) the `ctable` branch read `word(pos)` without first stepping the sub-word zero gap, so a preceding `.asciz` ending unaligned made it refuse a correct layout. Two agents found (a) independently from opposite directions. Byte-neutral controls: `md_SC07_003` + `md_MAIN_011` clean rebuilds, `gate_main --assert-baseline`, and a full `check-all` 213/213. |
| | `tools/jtbl_carve.py` — the `covered` verdict | **(P31 S74, cookbook §440)** A table already inside an existing `.rodata` carve **bound to the function's own subseg** needs NO carve work: in stub state spimdisasm migrates it into the fn's `.s` and the object fills the piece exactly, so banking swaps that block for cc1's identical one. `island_probe` used to classify such a function `tail` on the table's ADDRESS, `apply()` routed it to `build_carve`, which resolves spans out of the RAW data asm where a carved table no longer is → `not found in the raw data asm` → `harvest_verify` booked **CARVE-REFUSED**, a verdict about the route we chose rather than about the function (R43). Now: a `covered` verdict, a `covered-tpad` wall (the retail copy carries a trailing §8a pad word the matched body will not emit — bankable, needs a `0t<n>` spec entry), and a fully-covered batch is a no-op before either route. |
| | `tools/reconcile_tu.py` — S75 corrections | **(P31 S75, cookbook §442)** Three defects in the `gate_stage` `-rc` rung, found by running S74's "9/9 via `harvest_verify`, 7/9 via `gate_stage`" measurement to ground. (a) **The premise was false at BLOCK scope.** The tool conformed a draft decl to the TU's in either direction because "a decl BELOW still conflicts" — four `cdecl._cc1_accepts` probes say a block-scope `extern` vs a TU decl BELOW the splice point is **ACCEPTED** (pedwarn `type mismatch with previous external decl`), while file-scope-vs-below and block-scope-vs-above both REJECT. Conforming it is destructive, because the TU's decl names the TU's TYPE and a type declared below the splice point is not in scope at it: the emitted result gets `syntax error before 'D_x'`. Byte-witnessed on `resident:func_800D06E8` (344 ins, `match_one` closeness 0) whose block-scoped `extern Blk80078E78` became `extern Struct80078E78` — typedef 388 lines lower. It is also the construct this ladder's OWN `scope_demote_drafts` (§8d) rung emits on purpose, used by three already-banked functions in that TU: one rung undoing another. Now skipped with a note (R43). (b) **The cast pass rewrote COMMENT PROSE** — it looped over lines skipping only `extern`/`typedef`, so a 40-line header comment had the symbol rewritten 8× including inside a quoted cc1 diagnostic; now matches on `cdecl._mask` (length-preserving, mask offset = source offset) and splices into the original. (c) **`&sym` emitted `&` applied to a cast** — legal for the scalar arm, `invalid lvalue in unary '&'` for the array/fnptr/fnptr_array arms (measured); `&` now SELECTS a pointer form built from the address and consumes itself. |
| | `tools/gate_stage.py --skip-stages` | **(P31 S75, cookbook §442)** Switch ladder rungs OFF by tool name (`--skip-stages reconcile_tu,sig_unify`, or `GATE_SKIP_STAGES=`); prints what it skipped, because a silently-disabled recovery rung is the R32 defect class. Exists because stage 0 gates the RAW drafts first, so a broken rung can only cost a RECOVERY — which is exactly what makes it invisible: the function it destroys was already failing, so its DIFF reads as a fact about the function. The next bad rung costs a flag instead of a session. |
| | `tools/verify_worktree.py` step 3c + `tools/jr_isolate_all.py` scan guards | **(P31 S75, cookbook §443)** `provision()` now symlinks every `.run/sig.*.jsonl` into the worktree (main clone 259, provisioned worktree **0** before this) — the third member of the same class as `extracted/` (3) and `.run/obj40` (3b), and the SAME defect `parallel_gate.stage_generated` had fixed per-binary in S69: two worktree provisioners, no shared list, so it had to be fixed twice; they now cross-reference each other. At the other end, `jr_isolate_all`'s carve-ownership scan wrapped `reloc_targets` in `try/except Exception: continue` — correct for one unwalkable function, catastrophic when the cause is environmental: **2,603 of 2,603 functions raised, the scan found 0 owners, and the downstream R32 1:1-ownership assert reported carve CORRUPTION that did not exist** (R54 — a guard downstream of the failure is not a guard). `FileNotFoundError` now aborts at the cause naming `make sig-all`, and `_assert_scan_covered` fails loud when attempted == raised (R32: a scan where everything raised measured nothing, so its zero is an artifact). |
| | `tools/harvest_verify.py` — `_mk_block_spans` | **(P31 S75, cookbook §444)** The `overlays.mk` carve-state snapshot/restore is now **plural**. `_mk_block_span` (singular) took the FIRST `# --- <binary>` header and ran to the next `# --- `, so a binary whose carve state spans more than one block was half-snapshotted and the revert silently half-restored. Measured: a REJECTED gate of `resident:func_800D06E8` left a 4th `JTBL_PADS` entry and dropped `--pre hdr.rodata.o` (the §440 leading-rodata sandwich), so the binary would not build — `consumed 3 rodata jump table(s) but 4 pad spec(s) given` — while `src/` was perfectly clean, which is where everyone looks. `resident` is the only such binary (1 of 142 with a block, 2 blocks). Restore now rewrites blocks tail-first, collapses to the snapshot if the header count changed, and RE-READS and compares the result (the defect it replaces was a reported success, R32). NC: no-op on 142/142 binaries; the real damage undone; the old single-block path provably does NOT undo it. |
| | `tools/jtbl_carve.py` — per-table `sltiu` bound | **(P31 S75, cookbook §446)** Two silent defects that made a byte-identical `.text` gate DIFF for five sessions across four 279-ins siblings. (a) **The over-span clamp disabled itself on the functions that needed it.** spimdisasm runs an island's LAST `jtbl_` dlabel one word into the following NON-ZERO data (string bytes), so the zero-word trim cannot see it; the clamp that would have caught it was guarded by `len(sltiu_bounds)==1`, and `sltiu` is ALSO how gcc emits an unsigned range check (`(u32)(x-lo) < n`, I1) — the four siblings carry five distinct `sltiu` immediates, so the guard stood down. A 0x28 table got 0x2C reserved: image 4 bytes short, ~850 `%lo` shifted, whole-binary DIFF. Fixed with `_table_bound()` — gcc-2.7.2's dispatch is a fixed idiom, so the `sltiu` nearest ABOVE that table's own `%hi(jtbl_X)` is unambiguous per table. (b) **A carve span whose `JTBL_PADS` line has no `tables=` comment** (written by `jtbl_pads_fix`) fell through both merge branches and lost its existing table's start, refusing with "table starts do not fit the span" — which `harvest_verify` then 'repaired' with a needless `jr_isolate_all` that walked back into (a); the merge now seeds from the span start unconditionally, per the invariant the validator already asserts (every carve span begins with a table). NC over every other open table-bearing stub fleet-wide: 11 tables, 10 unchanged, 1 changed — a FIFTH latent victim (`ov_SC06_022:func_80185B80`). All five banked byte-identical. |
| | `tools/dedup_propagate.py` — `_split_masked` memo | **(P31 S75)** `find_site` re-ran `cdecl._mask` (4 regex passes, one `re.S`) + two `splitlines()` over the ENTIRE concatenated source on EVERY call, though the mask is a pure function of the text and the caller loops over every function in the binary. Measured on `ov_SC01_005` (2.50 MB, 2,503 fns): 6.5 + 38.9 + 4.6 = **54 ms per call before any searching**. Memoized via `lru_cache(maxsize=8)` — callers already hold one text object per binary and CPython caches a str's hash, so a repeat lookup is a pointer compare. **2x on that loop (58.3 -> 33.0 ms/call), NC identical results on 120 addresses.** Honest scope: that loop is only ~2.4 min of a 30-min run; the profiler puts 43% of `--check-only` in `family_remap._alias_decl_for` (107 s / 1,312 calls), which is the real target and is NOT fixed here. |
| | `tools/main_diff_locate.py` — `classify()` | **(P31 S75, cookbook §447)** The `TABLE REJECT` class was **unreachable for main** and demanded purity. (a) It summed bytes whose object string contains `(.rodata)`, but main's `section_order` is `[.rodata, .text, .data, .bss]` — its rodata sits BELOW `.text` and its jump tables live in `.data` objects, so the test could never fire on the one binary with the most jump-table functions left. Now matches `(.data)` OR `(.rodata)`. (b) It required `ro == outside`, so a few bytes of perturbed code dropped the verdict through to `PLUMBING REJECT` and its §376 declaration advice. Now **dominance-based** (≥60%), reporting the split and naming which part is the table problem and which the declaration problem. Measured on `SaveLoadRoutine` (1,165 ins, the §434 wall): body BYTE-IDENTICAL, 3,787 of 3,989 differing bytes (94.9%) in `.data` jump tables, 202 (5.1%) in `.text`, built image 4 bytes SHORT — verdict moved `PLUMBING REJECT` → `TABLE REJECT (MIXED)`. The §376 chain had been run on it twice and fixed nothing, because it addresses the 5%. NC over all five pre-existing verdict shapes: 5 of 6 unchanged. |
| | **`tools/asm_in_c.py`** (NEW) | **(P31 S75, cookbook §448)** Finds every function that is **assembly posing as C** — a §265 file-scope `__asm__` body (class A) or a C function whose body is only asm statements (class B) — while correctly EXCLUDING the §3a cross-jump barrier, which is what `__asm__` means in 3,182 of the 4,224 sources. Measured: **199 functions, 154 of them GAME CODE, 171 in main**, largest `SaveLoadRoutine` (1,165 ins). These were in NO `progress.py` bucket, so main's REAL% was overstated (45.88% → **42.15%** once counted; `progress.py` gained a `VERBATIM __asm__ bodies` line that counts them byte-identical but NEVER as REAL). Design is the point: **three independent detectors that must agree**, disagreement reported as a defect (it caught `jtbl_*` being claimed as functions); **SDK-ness derived from the 14 shipped PsyQ archives via `nm`** (2,227 symbols), not a hand list (which had mis-classified `VectorNormalSS`/`SquareRoot12`/`OuterProduct12` as game code); coverage asserted; and **`--selftest`** with a known-true case of EVERY spelling — hand counts went 116→112→108→178→199 because the sources use both `".ent\tNAME\n"` and `".ent NAME\n"`, and a bare `".ent\t"` fragment yields a phantom function called `t`. Run `--selftest` before believing the number. |
| | `tools/jtbl_carve.py` — `_merge_pre` carries `--pre` forward | **(P32 T1a, cookbook §498)** `set_overlays_var` rebuilt `<bin>_JTBL_INTERLEAVE` from the carve set alone and DROPPED the binary's `--pre <obj>` clause (the resident's §8f leading-rodata sandwich, `--pre hdr.rodata.o` — the one binary in the fleet with a `--pre`). `make extract` then refused (`ld_interleave: hdr.rodata.o … would be parked with .text`), the build linked the STALE script, and the gate booked the draft as DIFF (249,252 differing bytes of artefact). `_merge_pre(existing_line, args)` now carries an existing `--pre` into the regenerated value; idempotent; a line without `--pre` is unchanged (every overlay). Unit control on 4 shapes. |
| | `tools/split_indicator.py` — population derived, not stored | **(P32 T2c)** When `.run/S70_bins_sorted.txt` existed it WAS the population: a stored 213-name list that went stale at the first onboarding (R51) — tools-health printed "213 OK of 213" over a 218-binary fleet. The population is now derived from `config/splat.*.yaml` (+ main); the S70 file is an ORDER hint only, new names are appended, and the denominator is asserted equal to the yaml-derived set (R32). Verified 218/218 after the five module onboardings. |
| | `tools/payload_base_evidence.py` | **(P32 T2a, memory-map §S45 p7)** Static, controls-gated base evidence for a never-onboarded payload: module-id word, TEXT_LO estimate (first `addiu $sp,-N`), absolute-pointer set, `lui` hi-half histogram, and a **jal→function-start vote** (every `target − start` pair; ≥2 hits = a self-calling module — starts = prologues ∪ the word after each `jr $ra`+delay, because leaf functions have no prologue). Scores a BOUNDED candidate list (the 5 §S44 slots ∪ all 134 IDXTAB DESTPTRs ∪ the vote's top bases): STRONG (every internal jal lands on a start, ≥2) / CONSISTENT / INCONSISTENT / NO-EVIDENCE; prints an AMBIGUOUS tie set instead of picking; **OUTWARD-EXPLAINED** (T2b): a pure vote base whose internal targets are function starts of the fleet's overlays is downgraded (SC03/56's false STRONG); the requester cross-check (`req_fit`) is informational only — shared engine code makes every requester fit. **R39 `--controls`** (runs before ANY emission): the byte-proven bases of md_MAIN_008/011/013/042, md_SC03_073, md_SC02_009, md_SC07_004 must come out top-ranked from their payloads alone (7/7; every TEXT_LO estimate == the yaml's incl. the header-table modules 0x7C/0x14/0x158). **R43:** a payload with no self-reference at any candidate is REFUSED as base-independent. The byte gate (`new_binary.sh` first build) is the arbiter (P9). `--json` keeps the rows (`.run/P32/t2a/evidence.json`). |
| | `tools/interleave_check.py` — `--pre`-tolerant anchor | **(P32 T1a, cookbook §498)** The `--order` anchor was `:= --order`, so a line carrying `--pre <obj>` first (the resident) parsed as n=0 and printed a false DRIFT (rc 0 — a soft alarm). Now `:= (?:--pre \S+ )?--order`; `--fix` already preserved the prefix (it replaces only the order token). Control: ov_SC02_017 ALIGNED n=44 unchanged; resident ALIGNED n=5. |
| | `tools/harvest_verify.py` — post-carve extract rc checked | **(P32 T1a, cookbook §498)** `_jtbl_prep_one` ran `make extract` after a successful carve and IGNORED its exit code (R49/R61): a refused layout left the stale linker script in place and the whole-binary gate reported the draft as DIFF. Now a failed re-extract prints `!! extract-after-carve FAILED … CARVE refusal, NOT a draft verdict`, restores the carve snapshot, re-extracts, and returns refusal (CARVE-REFUSED class). |
| | `tools/jr_isolate_all.py` — `typedef struct Tag Alias;` keyed by the ALIAS | **(P32 T1b, cookbook §497)** The carried-type dedupe keyed every block by the names its regexes found; for a bodiless `typedef struct Rec801806C8_s Rec801806C8;` that was the TAG, so the typedef block and the tag's own `struct Rec801806C8_s {...} __attribute__((packed, aligned(1)));` definition collided under one key with different bodies and the R43 "CONFLICTING bodies — a rename is needed" refusal fired on legal C (ov_SC02_017). `_type_names` now keys such a line by the alias (`_TYPEDEF_TAG_ALIAS`), and the `carried` set learns the alias too; `typedef struct X X;` (alias == tag) keeps the old key so a second one still dedupes/refuses. Unit control on 7 block shapes; the refusing overlay's dry-run is CLEAN (2 region files) with no source rename. |
| | `tools/jr_isolate_all.py` — include-derived provided types | **(P32 T1a, cookbook §496)** The carried-type test consulted `_engine_types()` (engine_types.h + common.h) for EVERY TU, assuming each region `#include`s engine_core.h. Overlays do; the resident, the `md_*` modules and main's TUs include only `common.h`. A resident file-local typedef whose NAME engine_types.h also defines (`CdFileLoc`) was therefore NOT carried into the new regions ("the shared headers already define it") → `parse error before cdFileLocTable` in both region TUs, build rc 2 while the stale binary on disk read GREEN (R53). Now `_provided_types(header)` derives the provided set from the TU's own `#include` lines (engine_core.h ⇒ engine_types.h + common.h — engine_core's OWN typedefs live inside `DEFINE_func_*` macro bodies and are provided only where invoked; `common.h` ⇒ common.h only) and `_file_scope_decls(items, provided)` uses it at both decision points; `_engine_types()` kept for legacy callers. R39 controls: an overlay header yields exactly the legacy set (1,197 names); the resident header's set lacks `CdFileLoc`. Positive control: the resident 3-region split builds byte-identical (`8e17e02f…`). |
| | `tools/jr_isolate_all.py` — boundary derivation | **(P31 S74, cookbook §441)** `_region_emit_start()`: the yaml offset for a region is derived from the region's **CONTENT** — min of item addresses and of every `.globl`/`.ent` its text names that resolves inside the object — and taken as `min(cut, emit)`, so a boundary can only move DOWN. Reason: **a §265 verbatim `__asm__` body is not one of `parse_overlay_c`'s four addressed-anchor forms, so it attaches to the NEXT anchor as PREAMBLE — and preamble is assumed byte-neutral when it emits bytes.** A cut at `func_800D0268` would have moved 0x168 bytes of three other functions into the new object while the yaml claimed the region started higher. Where no verbatim asm is in play it equals the cut, so every existing isolate is unchanged. Also: an item-less CLOSING region used to emit a duplicate `- [off, c, …]` line (the empty-region skip covered only region 0, and `_partition`'s empty `footer` made the closing region look non-empty). |
| | `tools/jtbl_rodata_pads.py --derive` | **(Phase 31 S62 T3a, cookbook §303)** Module path of the §8e pads filter: the Makefile runs `--derive $(BINARY) --tu <tu>` for every `md_*` object **and for `main` (P31 S72)** — jump-table pads derived at build time from the retail island + the emission stream (trailing pads `0t1`, table-aware, const data passes through). No stored spec; an anchor miss fails the build with the offset. **S72:** `--derive` now serves main too — `_file0_vram` returns the code segment's `vram - start` (the PS-X EXE's 0x800 header), which makes both `raw[a - vram]` and `vram + <yaml offset>` correct for the EXE and leaves flat overlays byte-identical; `_splat_yaml` resolves main to `splat.us.exe.yaml`. |
| | `config/wave_exclude.txt` | **(P31 S72)** THE canonical wave exclude list — **tracked**, and **regenerated, never hand-edited**: `tools/exclude_audit.py config/wave_exclude.txt --write <new>`. Consumed as `draw_waves --exclude-file config/wave_exclude.txt`, which AUDITS it as a PREREQUISITE and refuses to draw on a stale one (`--exclude-stale-ok` overrides, loudly). Two classes: **CARVE-BLOCKED** (derived from `split_indicator`; disappears when the subseg is split — **EMPTY since P31 S74**, all four overlays split) and **WALL** (curated, cannot be re-derived — the `# WALL:` annotation is a PIN that survives regeneration, and its note is the refutation list to beat before reopening the entry). It replaces the nine `.run/S*_exclude.txt` snapshots and seven walls ledgers, none of which was authoritative; measured on its predecessor, 88 of 107 entries were stale one day after it was written, 46 of them open drawable work totalling 12,750 instructions. |
| | **main's TU layout (P31 S72)** | main's game code is no longer one file. `src/800.c` was split at the jtbl-span TU boundaries into **`src/800.c`** (vram 0x800123F0-0x8002B0B4, owns `.rodata` span A 0x80072A38-0x80072C70), **`src/800_b.c`** (0x8002B0B4-0x80035270, span B 0x80072E44-0x80073140) and **`src/800_c.c`** (0x80035270-0x8003A444, span C 0x800732A0-0x8007344C), plus **`src/800_shared.h`** for the 19 typedefs + 2 includes that cross. Reason: one code object contributes exactly ONE contiguous `.rodata` run, so each jump-table span needs its own object or every switch function in it double-emits its table (cookbook §426/§431). main's island is now a 7-piece sandwich and `ld_interleave` runs with `--order`, not `--front/--tail`. **Any tool that reads "main's source" must glob `corpus.src_files('main')`, never hardcode `src/800.c`** — `reconcile_slate` did, and saw 133 of 187 typedefs after the split. |
| | `tools/split_indicator.py` | **(P31 S72, cookbook §426/§431)** Which code subsegs MUST be split before their switch functions can bank: a code object contributes exactly ONE contiguous `.rodata` run, so a subseg owning raw jump tables in ≥2 non-adjacent island spans makes every switch function outside the one carveable span unbankable at any effort. **Decidable from the raw image at 0% matched** — no attempt needed. `--self-test` fires on main's pre-S72 island, stays silent on main today, and does not over-fire on a one-span subseg; linked PsyQ subsegs are excluded on principle. **(P31 S74)** Runs in `make tools-health` as a **HARD GATE** — the four violations it waited on are split, the fleet is **213 OK of 213**, and a new one now fails the build. The owner of a table is derived from the CONFIG by address, never from the stub's directory path: `make extract` does not prune a re-homed subseg's `nonmatchings/<old>/` dir, and reading it made the tool assert NEEDS SPLIT for a split that was already correct and byte-green (cookbook §436). Stale debris is now named in a `note:` line, which prints on an OK verdict too. |
| | `tools/overlay_src_split.py` `comment_open_at()` | **(P31 S74, cookbook §437)** THE comment-state oracle for the TU-split chain: per line, does it BEGIN inside a block comment. Every peeler in the chain used to ask `line.strip().startswith("/*")`, which is blind to a comment a construct OPENS MID-LINE and WRAPS — 238 such lines across 193 tracked `.c` files. The construct ends at its `;` *before* the `/*`, so the caller resumed on comment PROSE and `scan_construct` read it as code (`(s32,s32)` in the prose closes a depth-0 paren -> `seen_header` latches -> every later `;` reads as a K&R param decl -> one 'construct' swallows the whole preamble). Result: `parse_overlay_c` anchored a `def` on a pure declaration run, and `def_proto` emitted `extern #define CALL_… extern void func_…();` into the §8b carried decl layer — **`parse error before '#'`, which blocked five independently-MATCHed jr bodies in `ov_SC06_029`**. Now consulted by `parse_overlay_c`, `def_proto`, `split_src_region.parse` and `jr_isolate_all._file_scope_decls` (which also truncates a hoisted col-0 decl at an unterminated `/*` — that comment used to run on and silently eat the next carried decls). `parse_overlay_c` may now RAISE `ValueError` (R43) when a wrapped comment CLOSES with code after the `*/`, because that construct could never anchor — 0 occurrences fleet-wide, so callers see it only if someone writes one. Building the guard exposed a third defect in the same model: **`_strip` tested for `/*` before stripping `//`**, so a line comment containing `/*` (`// … src/*/*.c`, 7 lines in 5 sources) opened a phantom block comment and blanked every following line until some later `*/`; `_strip` now lexes left to right. Negative-controlled: `ov_SC06_029` byte-identical before the change and after, with the five bodies banked (sha1 `b7b0d4ae…`). |
| | `tools/exclude_audit.py` | **(P31 S72)** Classifies every wave-exclude entry by its CURRENT blocker — `BANKED` / `LINKED` / `RE-PROBE` (blocker since fixed) / `CARVE-BLOCKED` / `WALL` — and regenerates the list keeping only the still-valid classes. **`draw_waves --exclude-file` runs it as a PREREQUISITE and refuses a stale list** (`--exclude-stale-ok` overrides, loudly). Measured on `.run/S71_exclude.txt` one day after it was written: 88 of 107 entries stale, of which 46 were open drawable functions totalling 12,750 instructions — `main:SaveLoadRoutine` among them. |
| | `tools/main_diff_locate.py` | **(P31 S72, cookbook §426/§427)** Turns a RED main gate — whose whole output is two SHA1s — into a NAMED list of divergent symbols: byte-diffs `build/us/SLUS_007.26` against `extracted/retail/SLUS_007.26`, coalesces the differing bytes into runs, and attributes them PER BYTE to symbols via `build/us/SLUS_007.26.map` (file-offset mapping DERIVED from each output section's `load address`, not the 0x800 header constant). `--focus <fn>` prints the routing verdict, FOUR of them: **BODY REJECT** (divergence confined to the function) · **TABLE REJECT** (§405-A — `.text` byte-identical, all divergence in `.rodata`, i.e. its own jump table: fix the case VALUES/ORDER, do NOT respell the body and do NOT route to §376; checked FIRST because it was mislabelled PLUMBING until `func_800316F8` produced it) · **PLUMBING REJECT** (the function is byte-identical, everything differs elsewhere IN CODE → the §376/§378 chain) · **MIXED**. `--self-test <addr>` is the negative control: flips one byte at a known address and asserts the containing symbol is named, plus the identical-pair-reports-zero direction. `gate_main` calls it automatically and preserves the red image + map under `.run/gate_main_fail/` BEFORE the R40 baseline control rebuilds over them. |
| | `tools/blocker_probe.py` | **(Phase 29 SESSION-16, cookbook §65)** WHY a byte-correct draft fails the whole-binary gate. Read-only; **two oracles** (R34): STATIC (`cdecl.parse` + `cdecl.compatible` — cc1's own acceptance question, never text equality) beside the REAL cc1 (via `rtu_match`), leading with the DISAGREEMENT table. Classes `self_decl_hdr`/`self_decl_tu`/`callee_decl`/`data_decl`/`local_type`, each mapped to a blast-radius tier (T0 draft-only / T1 binary-local / T2 fleet-shared). Blockers STACK, so a function's tier is the MAX over them. 36 drafts in ~9 s. Replaced+deleted `.run/diag_plumbing.py`. |
| | `tools/symcheck.py` | **(Phase 29 SESSION-18, cookbook §67a)** The pre-gate SYMBOL-SET guard: diffs the symbols a draft's object references (reloc records) against the target `.s`'s `%hi`/`%lo`/`jal` set. Catches the class **every masked oracle is structurally blind to** — `match_one`/`masked_diff` compare relocation-MASKED words (object-vs-`.s` mode is symbol-agnostic by construction) and `rtu_match` **compiles without linking**, so a draft that invents an extern no symbol table defines reads MATCH in both and can never bank (the SESSION-17 `func_801463A0` `_s`-alias trap). Negative-control-proven: on a draft with one renamed data extern, `match_one` reports the SAME 14 mismatched as the correct draft while `symcheck` exits 1 naming both the MISSING and the INVENTED symbol. `--c` (compiles via `match_one`, so the triple can never drift) or `--obj`. A cheap necessary condition, NOT a match oracle — still finish on the byte-gate (G3/P9). |
| | `tools/demacroize.py` | **(Phase 29 SESSION-16, cookbook §65b)** The per-overlay-local escape from a shared-header decl conflict — the largest stranded class, and the one §20 called unrecoverable. The conflicting `extern` lives INSIDE a `DEFINE_func_*` body, so it exists only at instantiation sites: this expands those instantiations **in the overlay's own TU**, correcting only the conflicting decl to the draft's byte-true sig (never dropping it, §57a-1). **T1** — writes confined to `src/<binary>/**`, so the per-binary gate suffices and no R22 risk is created by construction (contrast `fix_header_decl`, fleet-blind, §63 UPDATE). `--emit-edits` (read-only, feeds `rtu_match`) / `--apply`. **Price: the function can no longer propagate ×138 — such a bank is ×1** (full distinct-code credit, ~1/138 of instr). |
| | `tools/recover_integration.py` | **(Phase 24 T6; extended Phase 29 SESSION-16/17, cookbook §65/§66)** The stranded-draft recovery DRIVER — consumes a wave dir (`--draft-dir`, repeatable; the backlog is the wrong source: unreliable `closeness`, overlay-specific drafts), runs the declared `--stages` (`demacroize` T1 / `arity` T2), then gates in TWO passes (**gate all → exact snapshot-restore → re-stage winners only**), so a non-bank never leaves an edit behind. `--run-id` puts all scratch + `verified_out`/`failed_out` under `.run/recover/<id>/` (closes §55b trap 4); bank truth is `banked_from_source()` (the stub is GONE from src), never a gate report; `stub_map` derives from `corpus.stubs` (R33). **Blast-radius tiers are ENFORCED** (`--max-tier`, write-set assertion), and **propagation is itself fleet-tier**: it needs `--max-tier fleet` AND `--r22`, and is refused outright after `demacroize` (those banks are ×1 by construction; `--auto-from` would re-macroize and undo them) — both refusals negative-control-tested, exit 1. `--probe-only` / `--report`. Success path verified end-to-end by the §66 free re-bank test. |
| | `tools/lift_types.py` · `tools/uniquify_type.py` | **(Phase 29 SESSION-14, cookbook §64/§64a)** Fleet-wide type lift into `src/shared/engine_types.h`, and the camp-uniquify that must precede it for VARIANT names (same identifier, different layouts in different TUs — reconciling them merges two layouts and breaks the minority camp). Both are **T2**: dry-run by default, and **R22 clean-fleet is the arbiter, not the per-binary gate**. |
| | `tools/fix_header_decl.py` | **(Phase 29 SESSION-13, cookbook §63 + its UPDATE)** Rewrites a shared `engine_core.h` caller decl to a draft's byte-true sig. **Effectively retired**: its `[SAFE]` verdict inspects one caller and is structurally blind to the other ~137 overlays the shared decl reaches — 3/3 banked per-binary, then R22 **139/140**. Use `demacroize.py` (T1) instead. |
| | `tools/backlog.py` | Near-miss ledger (`.run/backlog.jsonl` + `docs/backlog.md`); **fleet-aware** `load_best` (a 077-matched-but-stuck-local fn surfaces via its overlay record; Phase 23). | **S84 repair (2026-09-06):** `load_best` now keeps the LATEST record at equal closeness (its docstring's contract; the `(cscore, ts) <= …` compare had kept the EARLIEST, so a re-verdict at the same closeness never rendered — func_80032A74's PROVED row).
| | `tools/lora_grind.py` | Mass-run driver: rotate binaries → draft open ≤N-ins stubs with the served model → gate → propagate. `--min-reach N` (Phase 23) targets shared fns (sig-reach oracle == `dedup_propagate`). |
| | `tools/bulk_harvest.py` | **(Phase 23 / T10)** The phase-separated + parallel-gate harvester (throughput rebuild of `lora_grind`): **(A)** bulk-draft K fresh ≤N-ins stubs (GPU) → **(B)** `ProcessPoolExecutor --workers` byte-gate over DISTINCT binaries (`build/<bin>/**` isolated; `run_gate` per-binary lock + per-worker scratch, `propagate=False`/`commit=False`/`compute_fleet=False`) → **(C)** dedupe-once + ONE commit. Round-robin fuel spread; STOP-sentinel; on-demand/bounded. Measured 2026-07-01: gate **0.4s/fn** (8 workers, ~75× the serial gate) ⇒ drafting is the bottleneck (→ vLLM next). Run: `API_BASE=… MODEL=bfm-match-7b-v3 tools/bulk_harvest.py --binary-glob 'ov_SC03_*' --count 80 --workers 8 --measure`. `lora_grind` kept as the serial fallback. |
| | `tools/grinder.py` | Token-free decomp-permuter daemon on the backlog near-misses; **per-binary** (Phase-23 fix). `auto_supervisor.sh`/`auto_stop.sh` keep-alive + STOP sentinel. **Phase-24 T5:** auto-threads the residual `klass`/`where_stuck` into `p16_permute.setup` (§31-directed weights) + **input-changed idle gating** (`draft_sig`) replacing the blind `tried.clear()` churn. **Phase-29 T13A TARGETING:** `candidates()` filters on the MEASURED residual bucket from `autopsy.verdicts()` (1,303 → 78) and takes its directed profile from the measured class, not the logged label (91% of records have none, so the search silently ran on gcc defaults). Measured: of the 972 records this filter admitted, only **75 (7.7%) were permuter-shaped** — ~92% of the daemon's CPU was going where a search-closer provably cannot win, which is why it banked 0 after Phase 21. Degrades to undirected if the corpus is absent and says which mode it is in; `--no-targeting` A/Bs it. |
| | `tools/residual_class.py` + `tools/test_residual_class.py` | **(Phase 29 T13A, cookbook §60)** The DETERMINISTIC residual→class classifier. Decodes each mismatching MIPS word into `(operation-skeleton, register-fields, immediate)` and names the class from the bytes: `REGALLOC-PERM` (consistent injective register map = §31 S11/RC-3) · `SCHEDULE-REORDER` (same multiset, different order) · `DELAY-SLOT` · `LENGTH-DRIFT` / `SIZE-MISMATCH` (drift detection runs FIRST — one inserted instruction inflates `closeness` by the tail length) · `WIDTH` / `BRANCH-POLARITY` / `STRENGTH` / `ADDRESSING` / `IMM-OFFSET` / `IMM-VALUE`. Every class routes to a **bucket** (`permuter`/`structural`/`integration`/`redraft`) = WHICH TOOL the failure wants. Uncovered opcode → `UNKNOWN`, counted (R32). 16 synthetic unit tests. `classify_streams` is authoritative (full streams); `classify_residual` is the declared-degraded path for capped stored residuals. |
| | `tools/autopsy.py` | **(Phase 29 T13A)** `collect` materialises the residual corpus by recompiling every open backlog draft through the EXISTING `match_one` path (R33), deriving the asm subdir (stub's self-describing INCLUDE_ASM) and the **-O0 flag** (`corpus.is_o0`) — both silent-artefact generators if guessed. 1,752 drafts / ~21 s at -j12; asserts its closeness against `masked_diff.structured_diff` on every row (R34) and refuses the corpus on any disagreement. `report` → `docs/autopsy.md` (buckets, classes, reach-weighted, `sig` clusters, and the second-oracle cross-tab vs the recorded label). `verdicts()` is the consumer accessor. |
| | `tools/corpus.py` `o0_sources()` / `is_o0()` | **(Phase 29 T13A)** The opt-level oracle, DERIVED from the Makefile's own `-O0` `CC1FLAGS` rules (explicit targets + `$(wildcard)`-built object lists) with a coverage assertion: an unrecognised rule form raises rather than mislabelling. Scoring an -O0 target's draft at -O2 makes the whole residual an artefact — the trap this phase hit four times. |
| | `tools/permuter_weights.py` | **(Phase 24 T5, cookbook §3b)** §31-directed permuter mutation: `classify(klass, where)` → `regalloc\|schedule\|cse\|None`, `render_settings_toml()` emits the `[weight_overrides]` table decomp-permuter merges over the gcc defaults (`main.py:336` / `helpers.py:merge`). Biases pass-selection toward the class's §31 levers (`perm_reorder_decls` RC-1/3, `perm_reorder_stmts` RC-2/S1, `perm_temp_for_expr` S2, `perm_commutative` cse) and away from value/type noise. No submodule edit. `klass=None` → gcc defaults (unchanged). |
| | `tools/p16_permute.py` | Per-fn permuter driver: `setup(fn, draft, asm_subdir, klass=, where=)` builds `base.c`+`target.o`+`settings.toml` (now with the T5 `[weight_overrides]`), `run_permuter` via `run_masked.py` (T2 floor-free masked scorer). `--klass` overrides the backlog auto-lookup. |
| | `tools/lint_symbol_refs.py` | **(Phase 24 T5c)** Guard against the Phase-21-class breakage: flags every `func_<ADDR>` token in committed `src/` whose address has a CURATED name in the symbol files and no `func_<ADDR>` symbol (a rename that would break a genuinely-clean rebuild but is masked by incremental builds — R22). Comment/string-aware. Exit 1 on stale refs. **Run after any symbols rename**; candidate for `make report`. Caught the T5b (macro-call) + T5c (INCLUDE_ASM) refs. **P31 S78:** also scans the §265 verbatim `__asm__("...")` string bodies (`.ent\tfunc_X`, `.globl func_X`, `func_X:`), where the masked scan was blind and a `\b`-regex rename misses `\tfunc_X`; `__asm__`-label-bound addresses exempted (negative-controlled on the passing tree). |
| | `tools/api_draft.py` | Provider-agnostic LEAN drafter against the served model's OpenAI endpoint. `LEAN_SYS` carries the "translate every instruction, never an empty body" clause (Phase 23 — fixes the v2 empty-leaf overfit). |
| | `tools/serve_local.py` | **Serve the fine-tuned model on the GPU** (base+LoRA via Unsloth, `.venv-train`, OpenAI endpoint) — the in-repo replacement for LM Studio. Run: `LD_LIBRARY_PATH=$(ls -d .venv-train/lib/python3.12/site-packages/nvidia/*/lib \| tr '\n' :) .venv-train/bin/python tools/serve_local.py --adapter models/bfm-match-7b-v3 --name bfm-match-7b-v3 --port 1234`. (Prebuilt `llama-cpp-python` CUDA wheels SIGILL on this no-AVX-512 CPU; the Unsloth/torch path is reliable, no build.) |
| | `tools/export_pairs.py` / `format_finetune.py` / `train_lora.py` / `eval_lora.py` | The corpus→LoRA pipeline (`.venv-train`): mine (asm↔C) pairs incl. the `engine_core.h` **macro bodies** + `engine_types.h` structs (corpus-v3) → Qwen chat-template + compile-filter → Unsloth QLoRA (3080 Ti) → held-out gate-true eval. Datasets/weights gitignored (`datasets/`, `models/`, `.venv-train/`). |
| **The derived oracles** (Phase 26-A tooling audit; R33 before R32 — *the best outcome is a deleted scanner, not a fixed regex*) | `tools/corpus.py` + **`make audit-corpus`** | THE corpus oracle. Derives from the FILESYSTEM (which `.c` files make a binary; the `INCLUDE_ASM` line is self-describing — its first argument *is* the asm subdir) and from the PROVEN INVARIANT (`matched = sig − stubs`, never re-parsed from C). Killed ~10 hand-maintained layout models. `audit-corpus` is a **second oracle that can disagree**: it cross-checks splat's boundaries against `sig_image`'s independent ones (0 phantom + 0 truncated since A4; was 193 unmatchable slices). |
| | `tools/audit_digest.py` + **`make audit-digest`** | **(P30 S1e, cookbook §140)** The **scoreboard** oracle: recomputes the three headline metrics from the CURRENT tree and fails if the committed `docs/progress.fleet.md` disagrees. Wired into `tools-health` AFTER `report`. Exists because a digest generated from a working tree that later changed (work reverted before the commit landed) is **byte-invisible** — `check-all` stays 140/140 over it forever (R34: the byte-gate is a null oracle for DOCUMENTS) — and the next honest regeneration then reads as a REGRESSION that never happened. That is exactly what the `10f954627` digest did: overstated **+7,879 ins / +130 unique fns**, which parked the phase's best lever on a phantom for a session. Compares **integers, not the printed percentages** (the staleness rendered as "94.4%" on both sides). Negative-control-proven against that stale digest. Same task hardened `progress.py stub_addrs`, which wrapped the fail-closed `corpus.stubs` in a bare `except` → empty stub set → `matched = sig − stubs` credited EVERY function: byte-witnessed reporting **instr 100.00% / distinct 100.00%** in a tree with no `asm/`. The identical swallow was fixed in `cast_call_sites.tu_for` + `reconcile_tu.tu_for`, where it silently reconciled drafts against the default `<ov>.c` instead of the jr/-O0 split TU — the very bug `cast_call_sites`' docstring exists to fix. |
| | `tools/cdecl.py` + **`make audit-cdecl`** | **THE C-declaration oracle (cookbook §51g).** ONE recursive-descent parser of C's **declarator grammar**, replacing fifteen tools' private regex models — models that disagreed with each other and were, all fifteen, blind to fn-ptr/jump-table decls (`extern void (*D_X[])(void);`), sized arrays (`[4]`), and multi-declarators (where the *whole line* was dropped). Total by construction, not by shape enumeration. **Two statement paths, because the inputs differ:** `tu_statements()` derives a TU's file scope from **`cpp`** (a decl inside a `DEFINE_func_*` macro body declares nothing until invoked — §8c; 54 ms/TU), and `split_statements()` is a **span-preserving** raw split for drafts (which get rewritten). API: `parse` / `scope` / `tu_scope` / `Declarator{name,kind,type,params,pnames,is_proto,is_definition}`. Verified: **2,952,246 depth-0 statements → 2,731,521 declarators, 0 parser defects**; **50,405 distinct declarations round-tripped through the real cross-gcc, 0 rejected**; residue adjudicated NOT-C *by gcc*, not by opinion. **Phase-27 T4 — the canonical draft-typedef strip:** `typedef_names(tu_path)` (the names a TU declares as typedefs, robust `tu_statements`-based so a coverage gap can't crash the byte-gate) + `strip_provided_typedefs(draft, provided)` (drop a draft's self-contained typedefs the target already supplies, splitting multi-typedef lines and covering scalar AND struct typedefs). Replaced **six** copied scalar-name regexes with complementary holes: `harvest_verify` now strips per-TU (unblocks the 39 struct-typedef drafts `_TD` dropped) and **surfaces cc1 stderr** so a `redefinition`/`conflicting types` failure reports as **PLUMBING**, not a byte mismatch (`.run/harvest_failed.classified.txt`); `masked_diff.strip_scalar_typedefs()` (used by `match_one`/`p16_permute`) fixes the multi-typedef-line skip that discarded 42 masked-MATCH drafts over whitespace (`func_8015C030` → `MATCH (23 ins)` unedited). `canon_sig_reconcile`/`eval_lora`/`format_finetune` keep their own copies for now (migrate per-bank, byte-gated — the audit-prescribed cadence). |
| | Phase 26-A tool-hygiene close (A9d–A10) | **DELETED** (R33, dead Phase-17 chain): `tools/census_conflict_callees.py` + `tools/derive_canonical_sigs.py` — `reconcile_tu`/`cdecl` answer their question from the build. **`overlay_src_split.py`**: `scan_construct` force_decl latch fixed (no longer swallows a def sharing a line with leading externs) + `hidden_definitions()` R32 coverage oracle wired into `selftest`. **`jr_isolate_all.py` `jr_inventory`**: `banked` DERIVED FROM THE IMAGE (`family_remap.reloc_targets` owns-a-carve) not a gitignored roster (R33) + curated-name via `addr_of` + 1:1 carve-ownership assert. **`family_remap.reloc_targets`**: optional `data=` param (read the image once, pass to N calls). **`backlog.py`**: `BACKLOG_NO_RENDER` env so parallel `gate_stage` workers skip the render race (append is atomic). `reconcile_tu` confirmed live on BOTH banking paths (`gate_stage` + `jtbl_family_bank.recover`→`bank_exemplar`). |
| | **S68 tooling, round 2 — retrieval, triage, walls, liveness** (P31 S68) | **`tools/neighbor_ref.py` (NEW)** — for an OPEN stub, the already-MATCHED functions worth READING as worked examples, ranked SAME-TU first, then same binary, then shape (li-normalised skeleton / call-sequence hash / reloc-kind sequence / CFG counts / opcode cosine, all precomputed in `.run/feat.*.jsonl`), with a hard penalty for opt-level mismatch (§116). Surfaces the neighbour's HEADER COMMENT — the payload agents actually consume. Answers the question `seed_ref` cannot: seed_ref needs a hash-identical twin, this finds a near-twin. **Run it for every card.** Measured motivation: S68's cheapest large matches all came from a neighbour (555 ins/72k, 657 ins/122k first compile, 753 ins/177k) while neighbour-less main fns ran 200-350k for ~80 ins. **`tools/wall_sweep.py` (NEW)** — enumerates the §332 delay-slot macro walls (10 fns / 1,027 ins); `--emit-exclude` feeds `draw_waves --exclude`. **Run before every draw AND before every escalation** — an escalation cannot beat the toolchain. **`tools/residual_rules.py` + `residual_rules_b.py` (NEW, experimental)** — residual→cookbook-lever classifiers; `_b` is the stronger (113/113 classified, 63% certain/high). NOT yet wired into the pipeline: see `docs/next-session-triage-ladder.md`. **`tools/lane_inflight.py` (NEW)** — the RECORDED liveness ledger (`add` on launch, `done` on verdict); `list` exits non-zero while any agent is live and IS the guard. **`tools/r22_verify.sh` (NEW)** — the clean-fleet verify, EXCLUSIVE by construction: it refuses while `lane_inflight` shows live agents, because `make clean` deletes `asm/` and drafting agents READ it. Clears `.run/R22_DEBT` only on a genuinely green run. |
| | **S68 tooling — the gater lane + the -O0 route** (P31 S68) | **`tools/gater_lane.py` (NEW)** — the continuous gater: drains a wave's finished drafts into `parallel_gate`, grouped by binary, `--r22` by default. Ledger AND verdicts keyed **`binary:fn:arm`** (R48 — and an escalation ALWAYS has a prior verdict, so arm-keying is what stops an in-flight fable draft riding the opus one). `--extra BINARY:PATH` for non-wave drafts, `--skip-binary` for lanes that may be writing, and **main is routed IN-TREE via `harvest_verify`** because `parallel_gate`'s worktree cannot stage main's psyq_integrate link inputs. **`tools/workflows/escalate_fable.js` (NEW)** — warm-started escalation: passes the prior draft + its measured closeness + its ruled-out levers, and demands a reusable `new_idiom`. **`tools/o0_boundary.py` (NEW)** — the stranded-boundary -O0 sweep (141 binaries / 288 boundaries / 0 candidates: the class is EXHAUSTED, and that null is negative-controlled). |
| | **S69 tooling — the TRIAGE LADDER** (P31 S69) | **`tools/triage_ladder.py` (NEW)** — the zero-token pass that answers *"does this target need an agent at all?"* before one is spent. **The PRE/POST split is the point:** `--pre <wave>` runs the TARGET-SIDE tiers only (BANKED · WALL-332 · PARKED) — no draft, no build, milliseconds — and writes `<wave>/triage.json` + `triage_exclude.txt`; `--post` runs the full `residual_rules_b` residual routing, which needs a draft and runs `match_one`. `--escalate B:FN` exits 2 on a walled/banked target (the check S68 was missing when it escalated a §332 wall at closeness 8). `--acceptance` is the R39/R32 harness: false-skip over EVERY open stub, recall over sampled matched fns, and a wall negative control over already-banked code — all pure filesystem work, so it runs in seconds over the whole corpus. **It REFUSES on a non-quiescent tree** (`pgrep -af` rows for gate/build lanes + `lane_inflight`): a live gate makes the stub oracle transiently wrong in both directions (§377). Wired into `wave_args.py` (drops walled/parked targets at draw time, reusing `pre_classify` — one implementation, R33) and into `tools/workflows/escalate_fable.js`, which now REFUSES any target that does not carry `triage:'DRAFT'`. **Routing correction (§376):** the `INTEG-STANDALONE-MATCH` / `NOCOMPILE-UNDECLARED-*` tiers are GATE-FIRST candidates, never free banks — S69 gated that class **0/28** raw; the route is `fix_arity_callers --any-proto` then the gate. |
| | **S69 tooling — the §378 SELF-CALLER CAST** (P31 S69) | **`tools/cast_self_callers.py` (NEW)** — the mirror of `cast_call_sites.py`. That one fixes the DRAFT calling a conflicting CALLEE; this one fixes the TU's OWN already-banked code calling the function the draft is about to DEFINE, which nothing handled and which is the terminal blocker of the §376 pile. **Never run it alone** — it answers the error that `fix_arity_callers --any-proto` CREATES: no-protoing the conflicting decl makes the draft's definition the prototype in scope, so the TU's own call fails anew with `too few arguments`. Order is `arity -> self-cast -> [--sync-decls] -> gate`. Byte-neutral because gcc-2.7.2 folds a cast of a known function symbol back to a direct `jal`. `--sync-decls` covers the narrow-param case a no-proto decl CANNOT legally reach (C89 requires promotion-stable parameter types when one declaration has no prototype, so `void f(s16)` is illegal against `extern void f();` — which is exactly why `fix_arity_callers` skips it as 'narrow-param'); safe only once the call sites are cast, because a declaration then emits no code. It REFUSES a function whose return type it cannot read off the draft (R43). **Journals every edit, and `--undo-journal --keep <banked>` after the gate is MANDATORY** — a leftover cast made `ov_SC07_000` stop compiling and every later gate verdict on it measured a broken baseline. Wired into `recover_integration.py --stages arity,self-cast` (tier `binary`), prescribed by `residual_rules_b`'s decl-conflict tiers, and in the playbook §4b. Measured: **8 banked of 28** including `main/func_80036D58` at zero agent tokens; generalises to the callee the diagnostic NAMES (banked `main/func_80021D38` that way). |
| | **S69 tooling — the NEAR-TWIN BAND** (P31 S69) | **`tools/seed_ref.py --near [--max-d N] [--near-control]` (WIDENED, not a new tool — R33)** — the fleet-wide twin oracle gained an edit-distance tier over reloc-normalized instruction streams, because the exact-hash tier answers only *"is there a byte-identical copy?"* while a frontier needs *"is there anything CLOSE?"*. **Measured widening: 22 of 352 reachable open stubs had a d=0 hash twin; 75 of 352 (21%) have a banked match at d<=25 — 3.4x.** Root cause of the gap is §389: `h_norm`'s normalizer drops its pending lui-hi on an intervening R-type, so indexed-global reloc twins hash differently and are invisible to seed_ref/twin_sweep/dedup/family-maps simultaneously. **Do NOT fix `h_norm`** — every stored map and calibration keys on it; the near tier reads through the hole. Verification built in: sound prefilters that cannot lose a true pair, R32 population assertion, R34 cross-check reproducing all 22 exact twins every run, R39 controls (positive 200/200 at d=0; random-pair base rate 1.17%). Classes emitted: HASH-TWIN · RELOC-ONLY (mechanical — remap via `family_remap` and gate; **8 of 10 banked at ~0 agent tokens on first use**) · NEAR-COUSIN (seeded crack). Known remaining gap: `family_sweep.load_sigs` globs `ov_` only, so 38 md_ + 5 resident + 67 main are structurally invisible to it (a 407-ins md_SC05_026 PURE twin of banked ov_MAIN_012 code was found in the wild). Full audit: `.run/S69_fable/report.md`. |
| | **S69 tooling — the CONTAINED tier + the twin LADDER** (P31 S69) | **`tools/seed_ref.py --contained [--contained-control]` (WIDENED again, R33)** — finds an open stub that is a banked body **plus or minus whole blocks** (any gap size), the class edit-distance ranks badly. Needs branch-offset masking (unmasked offsets veto exactly the target pairs) and a min-side-25 floor (89% of raw hits were prologue/epilogue vacuity). **Ranks by (substitutions+regions, cover), NOT by d** — §390's law: a deletion is free, a substitution is thought; the near tier ranked a d=5 substitution twin ABOVE a same-C-minus-one-statement pair that banked at closeness 0. Verified: planted-deletion positive control 60/60, random-pair base rate 0/397, R32 population assert 346/346, `--near` regression reproduces the stored slice exactly (352/22/28). **Use the ladder in playbook §2a-2** (exact → RELOC-ONLY → CONTAINED → cousin → cold), filtering lookalikes at `r = d/min(nins) >= ~0.3`. **Yield: 9 usable stubs, 1 banked.** And the standing conclusion: three fleet-wide probes past RELOC-ONLY returned 0 new / 9 / 2 — **the scanner well is dry; spend integration effort (§376/§378), not scanner effort.** Audit: `.run/S69_fable2/report.md`. |
| | **S69 tooling — the carve artifact fix + `asm_verbatim`** (P31 S69, Fable-3 audit) | **`tools/parallel_gate.py` (FIXED)** — `stage_generated` now symlinks `.run/sig.<binary>.jsonl` into each worktree. It is gitignored, so no worktree had it, so `jr_isolate_all.jr_inventory` read EVERY carve as UNOWNED, R32-aborted, and every jtbl draft was booked **CARVE-REFUSED** — a verdict about the WORKTREE, not the function (§322b). Re-check any CARVE-REFUSED recorded before this fix. Absence is now reported in `missing_generated` rather than silently skipped. **`tools/asm_verbatim.py` (NEW)** — `.s` → §265 file-scope `__asm__` block: decimal immediates AND offsets, comma-no-space operands (maspsx dies on `sltu $v0, $s0, $v1`), derived `.frame`/`.mask`, R43 refusals for rodata/jtbl. Ledger **MATCH 12 / NEAR 1 / REFUSED 2** + a non-wall control. Byte-equivalent to the stub BY CONSTRUCTION — use only for genuine hand-asm; §265 accounting applies. **But prefer the real fix first:** the §332 walls are a per-OBJECT assembler mode, and a 3-line maspsx reorder-passthrough + `as -O2` is byte-inert on the whole 800c3/800c2 objects and gives 0 diffs for 6 walls that already have drafts (§332b) — that route retires `oracle_reorder.py`. Audit: `.run/S69_fable3/report.md`. |
| | **S69 tooling — the two HABIT tools** (P31 S69) | **`tools/verify_binary.py` (NEW)** — the only correct way to byte-verify one binary by hand. `make build BINARY=<b>` is NOT a verification after a gate that touched `config/`: a carve rewrites splat INPUTS, so a build without a re-extract links newly-carved C against stale state and the SHA is meaningless (§384). It ALWAYS re-extracts by default (`--no-extract` to opt out), passes `-j`, and exits non-zero only on a genuine mismatch; `--all-touched` sweeps every binary with uncommitted `src/`/`config/` changes. **Written because the rule was documented after the FIRST violation and then broken twice more by reflex** — costing a reverted 96-line match and 23 reverted decl edits, both later restored byte-identical. **`tools/twin_rescan.py` (NEW)** — run after EVERY gate that banked. The twin oracle answers *is there a BANKED body like this?*, so an open-open cluster reports 'no banked twin' for all members and that answer is stale the moment one banks (§397). It diffs the scan against the previous snapshot and prints **only what just became free**, with the ready-to-run `family_remap` command. Baseline at first run: 318 open stubs, **37 already carry a banked twin at d<=5**. |
| | **S69 fix — `parallel_gate` adopts NEW carve files** (P31 S69) | The merge-safety check compared `git show <pin>:<path>`'s **stdout** (`""` when the path is not at the pin) against `None` (absent from the main tree), so a file present in NEITHER — exactly what a jtbl carve creates when it splits a TU into `src/<bin>/<bin>_jr_<addr>.c` — read as *"main tree moved under them"* and was **refused and left untracked**. Eight accumulated in one session; nothing failed locally (file on disk, R22 green) but the naming yaml IS committed, so a fresh clone would get config without source. Now distinguishes *not at the pin* from *empty at the pin* via git show's RETURN CODE, and **prints every new adoption** rather than merging it silently (R32). Cookbook §400. **Docstring correction while here:** this tool does NOT use `git add -u src/` (that is `gate_stage`'s form) — it adds exactly the adopted paths, which is why the baseline check decides what gets committed; a stale reading of that line misdirected the first diagnosis. |
| | **S68 fixes — six instances of the overlay-layout assumption** (cookbook **§363**) | `dedup_propagate` could not even IMPORT (`os.` at module level in the one module that imports `os as _os`). `seed_ref` offered main's LINKED-subseg DEAD TEXT as bankable twins (43 of 82 hits — a draft there gates GREEN while wrong); now refuses and COUNTS the refusal. `parallel_gate.stage_generated` hard-coded `build/<b>/<b>.ld`; now asks the Makefile for `<b>_LD_SCRIPT`/`<b>_UNDEF_SYMS`/`<b>_UNDEF_FUNCS` and REFUSES when absent. `rtu_match` gained **`--tu`** (+ `blocker_probe` passes `stub.path` and `stub.asm_dir`) — it reconstructed `src/<source>/<split>.c`, which is the overlay layout; main's sources are LOOSE FILES in `src/`. `gate_stage` no longer synthesises `--out`/`--good-sha` — for main those resolved to a nonexistent path and then **ov_SC01_077's SHA** via `DEF_SHA`. **`psyq_integrate`**: the `*_externals.ld` map is now MONOTONIC — it was re-derived against the CURRENT `.ld`, so `firstfile = 0x80061FA8;` was DROPPED on every incremental relink and main was 2 bytes red before any draft was spliced (**the true identity of the 2026-08-15 'main link defect'**). |
| | **S68 — the module-binary -O0 carve route** (cookbook **§371**) | `jr_isolate_all` + `overlay_src_split` + the **Makefile -O0 glob widened to `src/md_*/md_*_o0?.c`** open carving for the single-object `md_*` binaries. Three stacked causes behind one `unaddressable content` message (interior-YAML-comment symbol-list truncation; a trailing verbatim-asm chunk with no region; bare tag forward decls), then the **spimdisasm rodata-migration trap**: migrated rodata follows its function ONLY within the same subseg, so a carve silently drops it and `INCLUDE_RODATA` cannot bring it back — rename the `.rodata` subseg to the object its emitters moved to. **The Makefile hunk MUST be committed with the carve** or a fresh clone loses -O0 on the region and every draft banked there mystery-fails. |
| | `tools/recover_rejects.py` | **(P31 S59)** Free recovery of PRE-GATE rejects, wired into the maintenance lane. Two paths exist for a draft that does not bank and only one was recorded: a gate failure gets a backlog row (closeness/class/best draft), while a draft the reloc pre-filter drops reached nothing — **569 of 1,261 drafts over eight waves, 45%**. Of the `MISMATCH?` rejects, **13% carry `shape: MATCH`** — right body, wrong symbol names, i.e. the §171 stale-seed class `aprop_symfix` rebases deterministically. Reads `.run/reloc_rejects.jsonl` (written by `ox_campaign.reloc_filter`), keeps shape-MATCH rows that are STILL open stubs, runs `aprop_symfix --fix`, and STAGES the rebased bodies into `.run/sweep_maint/<bin>/` for the lane's existing free gate. It never substitutes, gates or commits — a bad recovery can waste a build, never a bank. Tried-once is remembered in `.run/recover_rejects_seen.json`. Zero model tokens. |
| | `tools/lanes/restart_main_lane_when_idle.sh` | **(P31 S59)** Restart the main lane's SHELL at its one safe boundary — no main-lane agents alive AND no `gate_main` running, i.e. between its gate and its next draw — so an env/arg change (`MAXTOK`, `HTTP_TIMEOUT`) lands without discarding drafted work or aborting a batch. Companion to `relaunch_drafter_shell.sh` (wave boundary) and `restart_gater_when_idle.sh` (no sweep in flight); see `docs/accelerators.md` #5 for why a running lane never reads your edit. |
| | **campaign constants** (`MAXTOK` / `HTTP_TIMEOUT`) | **(P31 S59, probed against `stealth/ox-alpha`)** `--maxtok 16000` and `export HTTP_TIMEOUT=700` on both drafting lanes — **one setting, not two**. ox reports `reasoning_tokens=0` (its thinking is IN the content stream), so the output cap WAS the reasoning cap: measured over ALL turns, wave `bk` at 8k truncated **240 of 3,222 = 7.4%** and wave `bt` at 16k truncated **16 of 1,210 = 1.3%** (~6x better); an early count of **240 of 244** compared truncated turns against turns that printed a finish reason — against themselves — and wrongly read as ~100%. A truncated turn is a tax of one turn in 24, not a lost agent: the next turn emits the tool call. An uncapped hard prompt wanted **8,067** tokens. It generates at **~30 tok/s**, so 16k needs ~530 s and the old 420 s socket would have killed those turns (a timeout wastes the whole turn; truncation leaves a partial). Model ceiling is 1M context / **131,072** max completion, so 16k is our choice, not a limit. Ordering that must hold: generation < `HTTP_TIMEOUT` (700) < stallguard's wedged-agent kill (1200 s). `REASON_CAP` works on ox but shortens the ANSWER too (618-672 tokens) — a quality dial, not a truncation fix. Turn caps are NOT binding on the default lane (non-MATCH median 4 oracle calls, p90 12, of 24). |
| | `tools/main_lane.py` + `tools/lanes/main.sh` | **(P31 S59)** The EXE's own draft→gate→commit cadence, beside the overlay lanes. main is excluded from every wave draw because its gate is a clean whole-EXE rebuild that bisects; this lane runs that gate on its own clock. Parked drafts (`.run/main_queue/`) first, then `build_wave_atlas --only-bins main`; reloc pre-filter; `gate_main --apply` in batches of 40 (one rebuild verifies the slate, ~15 s measured); BISECTS a COMPILE conflict that gate_main refuses to bisect; credits a bank only when the INCLUDE_ASM line is gone AND main re-checks byte-identical; commits named paths (R42). Failures parked with a try count, capped at 2. |
| | `tools/lanes/distill.sh` + `tools/distill_scan.py` | **(P31 S59)** The flywheel's second half, beside drafting. The gater's per-wave `idiom_harvest` is EXTRACTION; this raises a READY marker (`.run/distill_ready/`) when ≥30 novel candidates or ≥2 waves accumulate, and a human + an **Opus/Sonnet** subagent (never Fable) distills and lands the sections. State is `{tag: novel-count-when-mined}`, never a done-list — a re-gated wave rewrites its candidate file under the same tag. Measured: ~82-88% of candidates are already covered, and 1 in 3 credited levers is byte-inert (§266). |
| | `tools/lanes/relaunch_drafter_shell.sh`, `restart_gater_when_idle.sh`, `bounce_drafter_on_queue.sh` | **(P31 S59)** Ship a lane change without losing work. bash parses a `while…done` body up front, so a lane-ARG change is invisible to the running shell and a python bounce re-runs the OLD command line. These wait for a safe boundary (a queued wave; an idle gate) and then restart the right thing. See `docs/accelerators.md` #5 for the code/args/draw-defaults table. |
| | `tools/integration_resolver.py` | **(P31 S61)** THE INTEGRATION-RESOLVER LANE, zero model tokens (`frontier-analysis-s60` §4). Intake = backlog rows at closeness 0 ∪ `reloc_rejects` rows with shape MATCH (an INDEX, re-judged against today's tree); per item `rtu_match` at the real split TU → CC1: the gate ladder's draft-side transforms + one retry → MATCH: `reloc_identity` as the disagreeing oracle (rtu masks reloc fields, so a wrong symbol NAME still reads MATCH) → MISMATCH/shape-MATCH: `aprop_symfix` → stage `.run/sweep_resolver/<bin>/<fn>.c` → `sweep_parallel` (whole-binary SHA) → commit at once (R42). Holds `.run/auto/draw.lock` for judge+gate. Ledger `.run/resolver/verdicts.jsonl` (per-candidate verdict + draft/TU hashes; unchanged rejects are not re-judged). `--intake-only` prints the stock with denominators; `--negative-control N` re-judges N banked fns first and refuses on <N/N. Lane wrapper `tools/lanes/resolver_lane.sh`. First run S61: 424 items → 245 staged in 41 s. |
| | `tools/rtu_shadow.py` | **(P31 S61)** Shadow-mode `rtu_match` beside the wave gate to decide the gate INVERSION (§3 of the same analysis). `--wave X` (prospective, before X is gated, never while a gate is in flight) writes `.run/rtu_shadow/X.jsonl`; `--join X` after the gate commit prints the rtu-verdict × outcome matrix, P(bank | rtu MATCH), the false-negative rate, and current-vs-inverted build counts. Drafts map to binaries through the shard's targets file, never by bare name. |
| | `tools/decl_from_use.py` | **(P31 S61)** Infer a MINIMAL C89 extern for a data symbol a draft uses but its destination TU does not declare (the A-prop "no seed decl" / resolver `undeclared` class): access widths/sign/index-scale from the target `.s`, use-forms from the draft, same-binary spellings preferred; refuses STRUCT shapes, conflicting width evidence, function symbols. Negative-controlled on 4,702 banked ground-truth triples (kind agreement 97.4%; the control forced 3 instrument fixes before any case verdict was read). Importable `infer()`/`tu_compiles()` for aprop_autodraft:522 and the resolver. First measured run: 39 of 42 "undeclared" cases were ONE uncompilable TU, not draft defects — classify `undeclared` only after a TU-alone compile probe. Ledger `.run/decl_from_use/verdicts.jsonl`. |
| | `.run/baseline_red.txt` (live gate input) | **(P31 S61)** The binaries whose CLEAN build fails the locked SHA at HEAD. `gate_stage` refuses their drafts pre-build as class BASELINE-RED (a RED binary rejects every draft gated against it — 15/214 binaries were red on 08-26 00:00 and ate 174/245 of the resolver's doubly-verified drafts). Maintained by the fleet audit + repairs; the maintenance lane's lock-aware fleet sweep is the standing detector. Keep it current: a repaired binary comes OFF the list or its drafts stay unjudged. |
| | `tools/jtbl_lane.py` (+ `jtbl_carve --probe/--island-split`, `harvest_verify._ISLAND_WALLS`) | **(P31 S59, cookbook §260-A; design `docs/tool-designs/jtbl-automation-s59.md`)** The jtbl carve→draft→bank lane. The carve stays AT THE GATE (`harvest_verify._jtbl_prep_one`, §61b's proven order — the lane never pre-carves); the lane probes feasibility READ-ONLY (`jtbl_carve.island_probe`: tail / covered / island-end / island-blocked / island-pads / main-manual), drafts (api_agent or `--draft-dir`), gates via the exact `sweep_parallel` worker call (per-binary flock + exclusive shared lock) while HOLDING THE CAMPAIGN'S DRAW LOCK across gate+commit (gates never overlap), and commits the named per-binary paths on a bank (R42). The §260 md island split is automated inside the gate (`_ISLAND_WALLS`: isolate body-spliced → `--island-split` insert → re-extract → covered no-op). One jtbl target per gate invocation (§61c batch constraint, by construction). `jtbl_lane --census` = the ranked work-list (245 members probed: 181/26,445 ins reachable). Wave route: `build_wave_atlas` gained the probe filter + a one-jtbl-card-per-binary cap, both inert unless `--levers jtbl-carve`. `idiom_serial` now REFUSES the jtbl-carve lever (its pre-carve ran the refuted order). Byte-proven ×3, one per class: `b801b499e` (ov tail, §8b merge + §8e pads), `bad793c73` (md covered — §260 stage 2, the FIRST md jr bank), `f74ad7ac8` (md island-end, full split by the gate on a virgin module). |

---

## Backup & repository posture (rules R20/R21) — PUBLIC since Phase 33

The repository is **public** (`https://github.com/Druthulu/BFM-decomp`, AGPL-3.0 for `tools/`+`docs/`, `src/NOTICE.md`
for the game sources, `THIRD_PARTY.md`). **H1 is in force:** no ROM-derived or proprietary bytes are in git or in its
history — the retail EXE, the RAM dumps, the Ghidra project, the Sony SDK, the session archive, the extension zips and
`brave.exe` were purged from every commit before the flip (`docs/public-flip-runbook.md`), and `tools/audit_public.py` +
CI (`.github/workflows/no-rom.yml`) keep it that way. The disc dump (`disks/`), `extracted/`, `build/`, `asm/`, `expected/`
and `.venv/` are regenerable or user-supplied and are never committed (`.venv/` from `requirements-python.txt`).

*Historical note (2026-06-15 → 2026-09-06, the private era):* while the repository was private, rule R1 relaxed H1 and the
Ghidra project, the PsyQ working artifacts (minus the >100 MB raw archives), the cc1 tarballs and the extension installers
were committed as the R20 backup. That state is preserved, unrewritten, in the private archive repository
`Druthulu/BFM-decomp-archive` and in the local bundle made at C4 — it is not the public history.

**P33 update (B5/B8, 2026-09-06) — R20's new home after the public flip.** The Ghidra project, the RAM dumps, the PsyQ
SDK, the session archive and the extension zips leave git at C3 (`tools/public_rewrite/purge_set.txt`). What R20 backs up
INSTEAD: the RE work as text — **`config/ghidra/<program>.jsonl` + `ROSTER.md`**, proven regenerable by
`tools/ghidra_rebuild.sh <program> --proof` (all six PASS); the dumps' identity in `dumps/CHECKSUMS.sha1`; the SDK's
identity in `tools/psyq_CHECKSUMS.sha256` (+ `tools/fetch_psyq.sh`); the zips' sha256s (§2.3/§2.4). The one-time snapshot
of the binaries is the private archive repo `Druthulu/BFM-decomp-archive` (C4). **Never `git clean -x` in this tree** —
the purged paths become ignored files and a `-x` clean deletes the RE database (R20 amendment proposed at PhaseEnd_Phase33).

**Rules:**

- **R20** — back up all irreplaceable RE/decomp work plus gathered hard-to-re-source tooling at per-session checkpoints. This **loosens R8** (which mandated a single commit at phase end): checkpoint commits are now expected within a phase.
- **R21** — keep **THIS file** (`docs/SETUP.md`) current whenever tooling, the MCP setup, the session hooks, or the environment changes.

Sony's **PsyQ libraries are never distributed** (user-supplied, `tools/fetch_psyq.sh`, checksums only); the gcc-2.7.2 **cc1 tarballs ARE tracked** (GCC, GPL; sha256-verified). The two-repo "curated public mirror" plan of `docs/gen2-roadmap.md` was SUPERSEDED by the in-place flip with the full rewritten history (decision log, P33 S86). The four submodules (asm-differ / m2c / maspsx / decomp-permuter) stay **gitlinks** on GitHub (the deliberate no-bloat choice over vendoring); residual risk = upstream deletion of a pinned commit.

---

## Disc provenance (redump — canonical integrity reference)

The `SLUS_007.26` executable's own hash is not published anywhere (redump hashes disc *tracks*, not inner files), so dump authenticity is proven at the track level. `tools/bfm_extract/extract_exe.py --verify-disc` checks the Track-1 BIN against these:

| Track 1 (data) | Value |
|---|---|
| SHA1 | `b44f0f0a19936f23b26188b658e13201a6a9c211` |
| CRC32 | `c238191b` |
| MD5 | `838e9ecf8b4e4810f3f82228b40e77d8` |
| EXE build date | 1998-08-25 |

A Track-1 match proves the dump is the canonical redump dump, which transitively validates the extracted EXE (our own SHA1 `143dbb89f34491258bbc27810d0a12ec8b43a8dd`, 413,696 bytes — stable, independently reproduced from raw sectors). Audio tracks 2–4 SHA1s are in the research archive if ever needed.

---

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
| 14 | Greenfield claim: decomp.me scratch search is script-blocked (Cloudflare) | **TBD → closes at P33 E1:** the preset-creation session (Drew, in the browser, after the flip) includes the one-time manual search for BFM scratches; record the result here |

### `tools/gap_triage.py` — harvest pre-filter (added P31 S55)

Scores a wave's `index_gap` reports against every cookbook section by IDF-weighted distinctive-term
overlap (`file.c:line` cites, `§` refs, register names, MIPS mnemonics, pass names) and names the
sections a reader should open first.

```
.venv/bin/python tools/gap_triage.py .run/wave_<N>_gaps.json [--min-score 0.15] [--top 3]
```

**Why it exists:** the majority verdict of every harvest so far is "already covered" — 61/71 (T),
44/64 (U), 76/67 (V), 41/68 (W), 56/63 (X) — and reaching that verdict is a text search, which does
not need a model. It runs as **step 0 of the harvest reader prompt**.

**What it is not:** an oracle. It is deliberately dumb term overlap, no embeddings; a candidate is a
starting point and an empty list is not evidence of novelty (it misses paraphrase entirely). The
0.15 default was set by measurement, not taste — on wave Y's 67 gaps the top-candidate scores ran
min 0.009 / p50 0.08 / p90 0.26 / max 0.53, and hand-checking below the threshold found generic
co-occurrence ("delay slot" matching every section that says "delay slot"). Emitting those is worse
than emitting nothing: an empty list costs a reader nothing, a plausible-but-wrong section costs a
read. At 0.15 it reports 14 confident candidates out of 67 rather than 51 mostly-noise ones.

### Crack-wave toolchain — the four flow traps, and where each is now caught (P31 S56)

Every one of these was a capability that was **silently off**: the tool ran, exited zero, and
reported a true number about a scope narrower than the caller believed. None was found by the
byte-gate, because the byte-gate is a perfect correctness oracle and a null coverage oracle (R34).
Each now asserts its own coverage (R32) or cannot be mis-called (R33).

| trap | what it cost | where it is caught NOW |
|---|---|---|
| **`wave_snapshot.py` assumed `asm/<bin>/nonmatchings/<bin>/`** — right only for single-TU binaries; every split-TU overlay lives under its own TU stem. Found 9 of 75 wave-Z targets. Its R32 assertion fired correctly, so the snapshot step got hand-rolled instead — **and the S46 validity gate living inside it came off the path for waves T–Z.** | 6 waves ran with no phantom-target check | `wave_snapshot` now honors the card's `sub` (then the old convention, then a single-hit glob). NC: 9/9 legacy targets byte-identical, 66/66 split-TU recovered. |
| **The S46 validity gate was only reachable through the snapshot step.** Its own comment says "a gate that is a separate command is a gate someone forgets" — and then a path bug forgot it. | S46 measured ~29 phantom targets × 3 tiers = 87 wasted agents, 9.7M tokens | Wired into **`build_wave_atlas`**, where cards are BORN, with an `--allow-invalid` escape. `validate_targets._key` also accepts the card spelling `fn` (it knew only `name`/`n`, so every card-shaped dict silently read MALFORMED). |
| **`family_sweep --hseq --only` is keyed on the FAMILY EXEMPLAR address**, but the natural thing to pass after a wave is the addresses you just banked — which are family *members*. Strictly keyed, that selects almost nothing and reports success. | wave Z: 15 addrs → 2 families → **3 banked**. Re-derived through membership: 21 families / 196 open members → **50 banked**. A 17× miss that looked like work. | `--only` now resolves member addrs to their family, **always prints the coverage line** (`N addrs -> M families, K unresolved`), and REFUSES when it resolves to zero families. |
| **`decl_prior._ASM_SYM`'s leading `\b` bound to the whole alternation**, demanding a word boundary before `%` — impossible in a `.s`, where that position follows a space. The `%hi/%lo` arm had **never fired**: the card's promised GLOBAL-TYPE row was 0 of 1,210 across four waves. | four waves of cards missing every data-symbol prior | Fixed (cookbook §204-E). NC over 75 wave-Z targets: `jal` 306 → 306 **zero regressions**, data **0 → 299** symbols recovered. |

**A fifth, in the banking driver rather than the wave tools:** when two slate-mates share a typedef,
`harvest_verify.strip_provided_typedefs` drops the duplicate from both drafts and the one surviving
definition sits wherever its owner splices — so if the *other* function is earlier in ADDRESS order,
its externs reference a type the file has not defined yet (`parse error before '<symbol>'`, which
reads like a codegen residual). `pregate_check` modelled the driver faithfully but never checked the
consequence; it now reports `[DROP-RISK] §203 USE-BEFORE-TYPEDEF` with the fix (hoist to the top of
the TU — never rename in one draft, which gives one symbol two types and just moves the failure).
NC: flags the known-bad pre-hoist splice, 0 false positives on the post-hoist file and on all 7 other
wave-Z TUs (the first draft of the check read a typedef named in its own *comment* as a use — it now
searches a comment-blanked copy with offsets preserved).

**The standing lesson for this flow:** after any wave step that reports a count, ask what
denominator that count is a fraction of. `3 banked` and `50 banked` were the same tool, same tree,
same day — the only difference was whether the scope was asserted.


### WSL2 memory reclaim (2026-09-02)

`C:\Users\user\.wslconfig` sets `memory=32GB` / `swap=16GB` (lowered from 48GB on 2026-09-02 at Drew's request, leaving 32GB to Windows). **`autoMemoryReclaim=gradual` was
added 2026-09-02** and takes effect only after `wsl --shutdown` from Windows.

Without it WSL2 grows `vmmemWSL` to cover Linux's page cache and never returns it to the host:
Windows Task Manager showed **30 GB held while Linux itself was using 4 GB** and ~22 GB was
reclaimable cache (a gate wave reads the 450 MB `asm/` tree plus every build object, so the cache
fills fast). Nothing is leaking — but the host does not get the memory back on its own.

* **Reclaim now, no restart:** `sync; sudo sh -c 'echo 3 > /proc/sys/vm/drop_caches'` (measured
  2026-09-02: 20 GB free -> 43.6 GB free). Costs a re-read on the next build, never correctness.
* **Automatic, until the config applies:** `.run/memkeeper.sh` (nohup'd) drops the cache whenever it
  exceeds 12 GB, every 5 minutes, logging to `.run/memkeeper.log`.
* `autoMemoryReclaim=dropcache` is the aggressive variant if `gradual` proves too slow.


### Tools added 2026-09-02 (S71) — R21 record

| tool | what it does | when you need it |
|---|---|---|
| `tools/journal_notes.py` | mines the agent journals for a `(binary, fn)`'s PAST ATTEMPTS and appends them to its pack; also reads `.run/journal_notes_local.jsonl` for hand-recorded evidence | **automatic** — `claude_wave_packs.py` calls it at the end of pack generation. Run `--wave <dir>` to back-fill a wave built another way (idempotent), `--fn F --binary B` to read what we hold on one function |
| `tools/launch_check.py` | refuses to launch an agent at an **already-banked** target; `--payload p.json` filters a `{wave,targets}` payload in place | before every launch. `wave_args` asserts open-ness at DRAW time, and payloads sit on disk while gates run — S71 launched one stale card and burned a full agent run |
| `tools/gate_triage.py` | routes a `parallel_gate` result set to the repair lane each verdict names (CARVE / UNDEF / CONFLICT / ARITY / PARSE / NO-DIAG / DIFF), asserting the staged-draft denominator | after any gate that banked less than it staged — tells you which lane the failures belong to instead of guessing |
| `tools/restage_matching.py` | rebuilds a gate plan from `recover_integration --probe-only` verdicts, keeping only drafts that compile-and-MATCH in their REAL TU | when a binary banks 0 and you suspect one bad draft is failing its siblings' shared build. **Caveat measured S71:** that probe compiles but never LINKS or CARVES, so its MATCH is not a bank prediction |
| `tools/weave_sweep.py` | the §406/§408 derived-selector sweep: scores each open stub's stored drafts, classifies the `sw $ra` disagreement from the residual, applies the clobber only to WEAVE-SUNK, `--lever-all` is the ablation control | as the template for "price a class by its RESIDUAL, not its SHAPE" — the sweep itself is a measured null (§408) |

### Tools added / changed 2026-09-03 (S76) — R21 record

| tool | what it does | when you need it |
|---|---|---|
| `tools/gate_main_parallel.py` **(NEW)** | runs the REAL `gate_main` inside N git worktrees to discover which drafts pass, then hands the union to ONE authoritative `gate_main` in the real tree. Workers discover; only the final serial pass banks | a main slate large enough that serial bisection hurts. **Measured: one gate cycle is 16 s**, so MAX_STEPS=24 is ~6.4 min serial and ~90 s across four workers. Run `--negative-control` once per environment first |
| `tools/permuter_sweep.py` **(NEW)** | selects a wave's NEARs the permuter can actually search (small residual + SCHEDULE/DELAY-SLOT/REGALLOC class) and runs `permuter_ils` on them; journals are scoped to the wave so an older run's row cannot win on a bare fn name (R48) | after every wave gate — agents are briefed to STOP at permuter-class residuals, so these arrive unattempted and cost no tokens. Measured yield ~3 in 8; there is NO validated predictor of which 3 |
| `tools/psyq_bss_probe.py` **(NEW)** | derives a PsyQ object's `.bss` bases FROM THE BYTES (base = resolved − addend over each HI16/LO16 pair) and reports whether the section can be cut into single-base pieces | before accepting any "scattered .bss, unlinkable" exclusion. Measured S76: SYS.o splits at 0x148 (2 bases), 2D_BG0.o/VM_NO1.o have no `.bss` at all. **S78 #4 correction:** its "GS_001.o: 5 interleaved bases, NOT splittable" grouped by BASE; grouped by RUN in offset order GS_001 is six pieces, every cut on a symbol start — it now reports over `psyq_bss_split.analyze` (one implementation, R33). Locates the object itself by masked search, so a wrong `--vram` cannot fake a clean answer (cookbook §484/§489) |
| `make sig-main-oracle` **(NEW)** | main's INDEPENDENT second boundary oracle (roadmap contract §1.3): signs the ORIGINAL EXE bytes over 28 game-code ranges derived from the splat yaml's SEGMENT TYPES, never its function boundaries | run by `tools-health`; needed before any 100% claim on main. Distinct from `make sig-main`, which is splat-SEEDED on purpose — `corpus.ORACLE_SIG` keeps the audit off that one. Result: 986 fns, 0 phantom / 0 truncated / 1 pad-tail (docs/second-oracle.md); 0 pad-tail since S85 — the digest derives the clause live (P33 A2) |
| `tools/recover_route.py` **(NEW)** | reads a gate's DROP ledger and names the tool that actually applies — SELF / CALLEE / DATA, each with its ordered ladder; refuses a verbatim draft up front. Wired into `gate_main`'s dropped report | after any gate that drops a draft. Replaces the single hardcoded chain gate_main used to print for every drop, which was the SELF chain and measured RED on a callee (S69) and inert on data. Negative-controlled against all 7 S77 drops whose winning tool was already known |
| `tools/sync_tu_decls.py` **(NEW)** | banks a draft the gate refuses by copying the TU's OWN `extern` line for whatever symbol the gate names, re-gating, and repeating | a draft that is byte-correct but rejected on a declaration conflict. Refuses `self_decl_tu` (use `cast_self_callers --sync-decls`) and refuses a NEAR up front, since syncing declarations makes a body COMPILE, never MATCH |

### Tools added / changed 2026-09-04 (S79, task #4) — R21 record

| tool | what it does | when you need it |
|---|---|---|
| `tools/psyq_bss_split.py` **(NEW)** | rewrites a PsyQ ELF object whose `.bss` is referenced through the SECTION symbol at several bases into per-base NOBITS pieces (`.bss`/`.bss2`/…): bases from the game bytes, runs in offset order, cuts snapped to symbol starts, symbols moved, a LOCAL section symbol per piece inserted (REL symbol indices bumped), relocs retargeted with the addend rewritten in the instruction immediates, then self-diffed. No pyelftools — its own 60-line ELF32 reader/writer | never by hand: `psyq_link.link_object`, `psyq_link_region.build_region` and `psyq_integrate.integrate` all call `prepare_object()` before `classify()`, so every library build splits what needs splitting and passes the rest through untouched (R39: 235 placed objects, 0 refusals, exactly 3 splits). CLI = the plan report (`<obj> --vram --exe --vram-base [-o out.o]`) |
| `tools/psyq_bss_probe.py` | now a thin reporter over `psyq_bss_split.analyze` (its own pairing code deleted, R33); "SPLITTABLE" means "tiles into single-base runs at symbol boundaries", which is what the build does | as before — before believing any scattered-`.bss` exclusion |
| `tools/psyq_link.py` / `psyq_link_region.py` / `psyq_integrate.py` | the NOBITS predicate is `^\.s?bss\d*$` (was the literal pair `.bss`/`.sbss`), so split pieces are NOLOAD-placed from their own section symbols; `link_object` links with `--no-check-sections` like the build (piece extents tile the PACKED section, so unreferenced commons overlap other pieces harmlessly) | automatic |
| `LIBGPU_ELF := .run/obj40/libgpu` | the `libgpu_used` curated dir is retired (it existed only to exclude SYS.o); `psyq_identify` drops the 8 objects the EXE never links | fresh clone: `tools/psyq_build_libs.sh LIBGPU` is now the whole libgpu step |
| `tools/make_libgs.sh` (+GS_001) / `tools/make_snd_used.py` (VM_F rejoined) | curated dirs now carry the two objects the split unlocked: libgs 34 objects / 8 blocks (`libgs8`), sound 63 / 12 (`snd12`) | re-run after `psyq_build_libs.sh` on a fresh clone |
| `tools/psyq/lib42/` + `lib421/` (task #13) | PsyQ RTL 4.2 + the 1998-02-26 libpad 4.2.1 patch (see the archive table above); `.run/obj42/libpad421` (7 placed) + `.run/obj42/libapi42` (39 placed), all byte-identical | **wired in task #5** (below); fresh clone: `7z x tools/psyq/PlayStation_Programmer_Tool_-_Runtime_Library_Version_4.2.7z -o.run/psyq_hunt/rtl42 && unzip .run/psyq_hunt/rtl42/LIB/42PATCH/J421PD.ZIP -d tools/psyq/lib421`, then for each of `lib421/LIBPAD.LIB`→`.run/obj42/libpad421` and `lib421/LIBAPI.LIB`→`.run/obj42/libapi42`: `python3 tools/psyq_lib_split.py <LIB> <dir>` and `for o in <dir>/*.obj; do tools/psyq/psyq-obj-parser "$o" -o "${o%.obj}.o"; done` |
| Makefile `LIBAPI42_*` / `LIBPAD_*` blocks + `APICARD_ELF := .run/obj42/apicard_used` (task #5) | the band 0x8005CE18–0x8005FC68 = 4 stub rows (`libapi1`, `libpad1`, `libapi2`, `libpad2`) fed by two WINDOWED `psyq_integrate` calls from the raw obj42 dirs; the apicard region = 7 rows (`apicard1..7`, the former `800c2`/`800c2_2`/`800c2_3` game-code rows were FIRST/PAD/PATCH+CHCLRPAD) from `tools/make_apicard_used.py`, which now takes libapi from `.run/obj42/libapi42` (4.2) and libcard from `.run/obj40/libcard` (4.0). `REORDER_TUS` is EMPTY (all four island TUs were Sony objects; the mechanism stays) | automatic in `make build BINARY=main`; the build is byte-identical WITHOUT any of the obj dirs (stub fallback), as always |
| `tools/exclude_audit.py` | LINKED now outranks a pinned `# WALL` (a function in a linked PsyQ subseg is never a target, whatever compiler fact was recorded about it): dropped the four §332 walls + `func_80062144` + `PopMatrix`/`PushMatrix` (libgte3 since Phase 8) | every regeneration of `config/wave_exclude.txt` |
| `tools/frontier_classify.py` | its LINKED subseg set is DERIVED from the Makefile (`progress._main_linked_segs_from_makefile`) instead of a hard-coded 49-name literal that missed every block wired since it was written (R51; it reported 337 "stubs" after task #5) | every census |
| `tools/p16_permute.py` (task #8) | `run_permuter` no longer swallows run_masked's output: a C-parser refusal of the seed (`register … asm("$7")` pins) is printed as `[permuter] REFUSED <fn>: Syntax error …` and recorded in `<scratch>/PERMUTER_REFUSED.txt` instead of reading as "no improvement" (cookbook §493) | every `permuter_ils` / `permuter_sweep` run |
| `tools/agent_verdicts.py` (S79/S80, task #9) | pulls the FINAL JSON verdict (`fn, binary, arm, status, closeness, draft_path, note`) out of Agent-tool subagent transcripts (`~/.claude/projects/<proj>/<session>/subagents/agent-*.jsonl`, symlinked from `/tmp/claude-1000/<proj>/<session>/tasks/*.output`) without reading them into a session; `--append <ledger.jsonl>`; a transcript with no verdict prints `NO-VERDICT` (R32). S80 aggregated the 11 S79 drafters this way: 2 MATCH banked, 8 NEAR ledgered | whenever Agent-tool drafters outlive the session that spawned them |
| `tools/agent_drafts_restore.py` (P32 T3, 2026-09-05) | REBUILDS a subagent's final deliverable draft from its transcript by replaying every Write/Edit/heredoc/cp/mv op (`<subagents-dir> --out <dir> [--pattern REGEX]`); one line per agent, NO-DELIVERABLE for agents with none (R32), and a count of unreplayable ops (an edit applied after a shell-side change → the rebuilt file may be STALE: verify with `rtu_match`, prefer an on-disk copy). Written when one agent's `find … -exec mv` swept 11 sibling deliverables out of the shared `.run/P32/t3/opus/` (cookbook §500-E; playbook §S80 addendum-2) | when a wave's deliverable file is missing but its transcript exists — the recovery route, never the primary |
| `tools/agent_reports.py` (P32 T3, 2026-09-05) | writes each Agent-tool subagent's FINAL message — the full prose report (closers, INERT levers, residual mechanism, TU-plumbing warnings) — to `<out>/<fn>__<arm>__<agentId>.md`; `agent_verdicts.py` keeps only the JSON line. T3's 31 reports live in `.run/P32/t3/reports/` (tracked) | after any single-agent drafting pass, before routing NEARs or banking MATCHes; the successor's first step after a dead session |
| `tools/transcript_dump.py` (P32 T3, 2026-09-05) | condenses a session transcript (`~/.claude/projects/<proj>/<session>.jsonl`, MBs of JSON) into readable text — assistant text, every tool call (Bash in full), truncated results, timestamps — so a successor can find the last checkpoint/commit and what was in flight | when a session died without a checkpoint; pair with agent_verdicts / agent_reports / agent_drafts_restore |
| `tools/cc1_dumps.sh` (P30 §172; repaired P32 T4b hand pass, 2026-09-06) | `cc1_dumps.sh <self-contained draft.c> <tag>` → `.run/c294/dumps_<tag>/<tag>.i.{rtl,jump,cse,loop,flow,combine,sched,lreg,greg}` + `<tag>.s` with the pinned cc1 (`-dr -ds -dj -df -dc -dS -dl -dg`); prints the `.frame` line (`vars=` is the frame-residue oracle), the instruction count, reload's `Spilling reg` / `now in` lines and the ghost census. The old standalone-`(use)` grep it printed UNDER-COUNTED (§172 note) and is gone | the first artefact of any residual: attribute it to a pass and a dump line before the first probe (accelerators (11)); edit the cc1 line for `-O0` modules |
| `tools/ghost_census.py` (P32 T4b hand pass, 2026-09-06; cookbook §501-M) | `ghost_census.py <tag>.i.lreg …` — every `Register N used …` header whose pseudo has NO occurrence in the post-sched insn stream (a ghost with stale `reg_n_refs`), with its class: `ST_REGS or none` ⇒ reload gives it an 8-byte `alter_reg` slot (combine-minted, pre-regclass); `GR_REGS …` ⇒ allocatable, no slot (`optimize_reg_copy_2`-minted, post-regclass). A census, exit 0 | frame-residue diagnosis (`vars=` off by 8·k); run by `cc1_dumps.sh` |
| `tools/parallel_gate.py` (S80, task #10) | **banked-but-not-merged is loud**: the worker's raw `git status` + scope ride in each result, a binary whose bank oracle fired but whose files were neither adopted nor refused prints `!! [pgate] BANKED-BUT-NOT-MERGED` and the run exits 2 (S80: `ov_SC03_107` banked 1 / merged 0 / exit 0, the bank died with the worktree — cause unrecovered because the fixed-path results JSON was overwritten); every run now also writes `.run/pgate_runs/<ts>.json`. Recovery = `rtu_match` MATCH → in-tree splice → `make build` (exit code) → commit | every `parallel_gate` run |
| `tools/verbatim_to_stub.py` (S80 usage note) | refuses to GUESS the asm subdir when the TU has no sibling `INCLUDE_ASM` left (a fully-decompiled overlay): pass `--asm-subdir asm/<bin>/nonmatchings/<subseg>` (main: `asm/nonmatchings/<subseg>`); `--apply --gate` re-extracts, rebuilds and compares the SHA. Used in #10 to revert S79 #7's assembly "bank" (cookbook §495) | any verbatim → stub conversion |
| `tools/p16_permute.py` + `tools/permuter_ils.py` (S80, task #9c) | **Pinned seeds are permutable now** (cookbook §493 S80 correction): `hide_asm` carries `asm(`/`__asm(` as well as `__asm__(` into the b64 pragma (keyword must be followed by `(`/`volatile`, so `INCLUDE_ASM("asm/…")` path strings are not statements — R39-controlled over 5,311 drafts); `permuter_ils` RE-HIDES every warm-restart waypoint (the permuter serializes pins raw), asserts `defines_fn` survived, aborts exit-2 on a refusal (R61a), and flushes its log (R55); `defines_fn` accepts K&R-style definitions. Any pre-S80 "permuter plateau" on a pinned seed was 1 cycle + silent no-ops — re-measure before citing it | every `permuter_ils` / `permuter_sweep` run; the S79 NEAR ledger re-run |
| `tools/agent_verdicts.py` (task #9 handoff) | extracts the FINAL JSON verdict from Agent-tool subagent transcripts (`.../tasks/<agentId>.output`, huge JSONL — never cat them) and appends them to a ledger; NO-VERDICT rows for files without one (R32) | after any batch of single drafting agents; the S79 handoff's step 2 |
| `tools/jtbl_pads_fix.py` (task #6) | `PAD_ERR_MORE` accepts the current `jtbl_rodata_pads` wording ("more rodata jump tables than pad specs (N)") as well as the old ".align directives" one — it had reported "no pad-count drift" over a red build (cookbook §491 gap 1) | whenever a bank changes a TU's jump-table population and the build dies in `jtbl_rodata_pads` |

**Oracle corrections — re-read any verdict recorded before these:**
* `match_one` and `rtu_match` now route the Makefile's `REORDER_TUS` (`800c2 800c2_2 800c2_3 800c3`)
  through `reorder_passthrough.py + as -O2`, the real build path. They previously modelled
  `maspsx + as -O1` and manufactured a phantom §182/§188 epilogue wall for every function in those
  four TUs. Same draft, `func_8005ECC0`: closeness **5 / 36 ins** before, **2 / 35** after.
* `oracle_reorder.py`'s docstring no longer says the shape is unreachable — for those four TUs the
  second cell of its diagnostic IS the build path, so a 0 there means the draft will bank.
* `draw_waves --main` **drew ZERO main functions** until this session (`bins` came from `src/*`
  DIRECTORIES and main has no `src/main/`), while printing a reassuring "refusing 49 LINKED subsegs".
  Coverage is now asserted: `--main` yielding no main stubs exits 4. Also `--redraw-open`, because
  the ledger records what was ATTEMPTED and a still-open stub is still work.
* A **verbatim-asm draft** is refused at three points — `gate_main`, `harvest_verify`, and
  `api_agent.prior_draft` (which was OFFERING them as warm starts). 1,099 of the 704,375 `.c` files
  in the draft store are §265 bodies under ordinary `<fn>.c` names.
* `verbatim_to_stub` refuses a **§179-C epilogue-less fragment** (no `jr $ra` of its own) — a stub
  there is an unbankable target. Census: of main's verbatim blocks, 37 have `jr $ra` and 100 do not.

**Two gating rules that are now enforced in code, not remembered:**
* `parallel_gate` **REFUSES `main`** — main's extract rewrites the linker script, so an incremental
  gate is a false PASS (§414). Use `tools/gate_main.py`: baseline assert → one clean rebuild per
  slate → bisect on failure.
* `gate_main` **REFUSES a draft containing its own `INCLUDE_ASM`** (substituting it restores the stub,
  so the build passes for free and the function counts as banked), and counts banks from the SOURCE.

### P33 B5 (S86, 2026-09-06) — Ghidra regenerability (IN PROGRESS at the S86 pause; see `phase-ends/CURRENT_PHASE.md`)
- **Model:** the Ghidra database embeds the program bytes, so it leaves git; what it holds beyond the splat symbol files is
  exported to text and the project is rebuilt from the disc + that text. `tools/ghidra_scripts/ExportAnnotations.java`
  (read-only; byte-stable JSONL: container facts, LOCAL types, every function signature, defined data, the 5 comment kinds,
  bookmarks, equates, labels the symbol files lack) via `tools/ghidra_export_annotations.sh [PROG…]` (no PROG = every
  program; **129 programs in 18.5 s** → `.run/ghidra_export/`). The committed file `config/ghidra/<prog>.jsonl` is the
  DELTA (`tools/ghidra_annotations_delta.py live baseline out`) between the live export and a FRESH rebuild's export, so
  analysis-origin rows subtract themselves out. `tools/ghidra_rebuild.sh <prog> [--proof] [--keep]`: import (PSX loader for
  the EXEs, BinaryLoader at `make -s print-VRAM_BASE BINARY=<alias>` for the rest) → `DefineFunctions.java` from the built
  ELF → `ApplySymbols.java` → baseline export → `ImportAnnotations.java config/ghidra/<prog>.jsonl` → export → delta → `cmp`.
  Scratch project under `build/ghidra_rebuild/proj` (**Ghidra refuses a project path with a component starting with '.'**,
  so never `.run/`). `make print-<VAR> BINARY=<alias>` echoes any per-binary Makefile variable (R33).
- **Gotcha (S86):** Ghidra compiles a `-scriptPath` directory as ONE OSGi bundle — a single script that fails to compile
  makes EVERY script in the directory fail with `Failed to get OSGi bundle containing script`. Diagnose by invoking the
  suspect script directly and reading the javac lines.
- Also in this change: `ExportSymbols.java` R15 fix (output path arg, refuses to overwrite, refuses `config/`);
  `DefineFunctions.java` list path = arg 1; `ImportPsyqGdt.java` default gdt from the Ghidra install dir; the six
  `tools/ghidra_*.sh` are repo-relative (`BFM_GHIDRA_PROJ` overrides the project dir; `ghidra_mcp_verify.sh <addr> <name>
  [PROG]`); Makefile `GHIDRA_PROJ := $(or $(BFM_GHIDRA_PROJ),$(CURDIR)/ghidra)`.

### P33 D1–D3 (S87, 2026-09-07) — the README and the published numbers, generated never typed
- **D1 README:** rewritten from the Phase-19 text (every number was stale). Its numbers block is generated: `tools/progress.py
  --json` writes `docs/progress.json` (every metric with its denominator, R41; no run date so `make report` never churns it)
  and `--readme` rewrites the block between `<!-- progress:begin -->` / `<!-- progress:end -->`; `--check` asserts both (and the
  badges) are fresh and sits in `make audit-digest`; `make report BINARY=main` regenerates all of it after the fleet digest.
- **D2:** `LICENSE` (AGPL-3.0 verbatim from gnu.org, 661 lines), `src/NOTICE.md` (no license asserted over `src/`; never the
  phrase "clean-room"), `THIRD_PARTY.md` (every license from the upstream LICENSE file or the GitHub API's license metadata:
  old-gcc and ghidra_psx_ldr publish NONE — download-only rows), `tools/README.md` (the one AGPL statement).
- **D3:** badges (shields endpoint JSON, colour by percentage), `tools/objdiff_report.py` (validated: `objdiff-cli report
  changes report.json report.json` parses and diffs it; a mutated unit shows as a change), `tools/frogress_upload.py`
  (dry-run default), `.github/workflows/progress.yml` (artifact `SLUS_007.26_report`). CI never rebuilds the game: the report
  is the committed `docs/progress.json` from a local clean rebuild. Outward actions after the flip (Drew): decomp.dev
  registration, the frogress slug + key. The `objdiff-cli` binary used for validation lives in scratch (`.run/objdiff/`).

### P33 C1 (S87, 2026-09-07) — the history-rewrite tooling, measured before the irreversible run
- **Design points.** The scrub replaces a hex token only when the WHOLE token is a prefix (≥ 7) of an old commit hash —
  so a 16-char sig hash can never be mistaken for a commit; only 7–8-char tokens carry any false-positive risk (≈1.6e-5
  per 7-char token) and the sample prints every 7-char replacement in context to be READ (R63). Tokens that are also
  prefixes of a cited CONTENT hash (1,480: the manifest, `check.*.sha`, the dumps, the sha256 checksum files, the redump
  CRC32) are excluded — measured 0 collisions. `rom_blob_ids.txt` is content/signature hits ∪ every blob that ever sat
  under a purge path, so `--strip-blobs-with-ids` kills a renamed copy that a path rule would miss. Bare session UUIDs in
  checkpoint prose (68 at HEAD) are NOT scrubbed (out of scope; no `claude.ai` URL exists in any HEAD blob) — reported
  as INFO by `absent_scan`. The mailmap and the dictionary are scratch: no personal address and no old hash is a
  literal in the package.
- **Measured (S87):** dictionary 4,420 commit objects (4,030 main, 339 twins, 51 orphans), 150,280 prefixes, **0
  ambiguous, 0 content-hash collisions**, 2 personal identities → noreply, 4 s. Sample over HEAD: 397 MB of text in
  7.9 s (50 MB/s), 1,238 replacements in 98 files, 731 distinct tokens (7-char 186 · 8-char 326 · 9-char 721 · 40-char
  5), 6 address replacements; **git's own lookup resolves exactly the same 731 tokens** (only-git 0, only-ours 0).
  `gate_scan --all --expect-fail`: 112,390 reachable blobs / 16.79 GB in 2 m 25 s; every purge rule named (ghidra/ 42
  paths ever, tools/psyq/ 190, dumps 28, archive 3, zips 2, brave.exe 1, the EXE 1+1), 0 stray content offenders, 52
  content/signature ids + 269 blobs ever under a purge path. `absent_scan` on the current repo → FAIL with 82,362
  offenders in 7 m 24 s (its positive control). `scrub --test` 12/12.
- **Trial rewrite #1 (S87, on a scratch bare clone — the reason a trial exists):** filter 274 s (72,500 hash replacements
  over every historical blob version, 60 trailers, 81 address replacements, 192 binary blobs untouched); the purge is
  real (archive/ghidra/dump blobs absent from the store; 0 purge paths reachable) but it found TWO defects that would have
  corrupted the real run: (1) the EMPTY blob was in `rom_blob_ids.txt` (an empty file once sat under a purge path) and
  `--strip-blobs-with-ids` dropped every "file emptied" change in history — 7 files silently kept their previous content
  and a restore commit became empty and was pruned (a second zero row); fixed: a blob shared with a non-purge path is
  never stripped by id (content/signature hits always are), and `verify_rewrite` now asserts no purge path survives and
  that the pruned set equals the derived purge-only set; (2) a commit the rewrite leaves byte-identical keeps its hash
  (the noreply-authored "Initial commit") and tripped the map's old-hash assertion — unchanged commits are recorded and
  exempted in the map, `absent_scan` and the probe. Also: the post-rewrite `gate_scan` must accept 0 blobs under purge
  paths (the guard now fires only when path offenders exist), and filter-repo's own gc leaves a ≈500 MB pack (re-deltaing
  16 GB of scrubbed text) — the purged binaries are gone regardless; C9 repacks aggressively.
- **Gotchas:** `git log --raw` abbreviates blob ids — `--no-abbrev` or the id filter drops everything (caught by the
  count "0 ever under a purge path"; the function refuses that result when path offenders exist, R43). git-filter-repo gc's the OLD objects
  out of the clone after the run, so `verify_rewrite` reads the old side from the working repo (`--old`) and the new
  side from the clone (`--new`). The clone stops being a "fresh clone" once the tag is deleted → `--force` is passed by
  `run_filter.py` (the only deviation from filter-repo's defaults). `--prune-empty auto`, never `always`.

### P33 B7 (S87, 2026-09-06) — the ROM-free CI: `.github/workflows/no-rom.yml`, `tools/audit_public.py`, `tools/compile_only.py`
- **What CI proves and what it cannot.** The contract (218 binaries byte-identical) needs the disc, never in CI. CI proves
  the tree is public-clean and the C still compiles with the pinned toolchain; the byte proof is the local recorded run
  (`docs/verification.md`, A5). Two jobs, `ubuntu-24.04`, Python 3.12, `actions/checkout@v4` + `setup-python@v5`.
- **`audits` (≈45 s):** `audit_public` → `audit_text_sources` → `verbatim_check --strict` → `cookbook_index --check` →
  `ghidra_roster --check` → `work_evidence --selftest` → `bfm_extract/test_lzss` → `lint_symbol_refs`. Every command was
  run here under the SYSTEM python with only `requirements-python.txt` installed (no venv, no `.run/obj40`) → all rc 0.
  `cdecl.py --audit --gcc` is NOT in CI: the exhaustive form ran > 5 min here (the Makefile's `audit-cdecl` is the
  sampled form and stays in `tools-health`).
- **`compile-only`:** apt `binutils-mipsel-linux-gnu` + **`cpp-mipsel-linux-gnu`** (the MIPS `cpp` is NOT in binutils —
  measured with `dpkg -S`), cc1 from `tools/bin/gcc-2.7.2-psx.tar.gz` (`sha256sum --check --ignore-missing`, the tarball is
  flat: `cc1 cc1plus cpp g++`), submodules recursive (maspsx). PR scope = 4 binaries / 54 eligible TUs (1.6 s here); the
  weekly + dispatch form = `--all`, 4,170 TUs, 123 s at -j32 ≈ 50 CPU-min (≈13 min on a 4-core runner; job timeout 45).
- **`audit_public` controls (R39):** the current private tree FAILS naming exactly the purge set (255 offender rows: 28
  dumps, the EXE ×2 path+content, 28 `ghidra/` files, 190 `tools/psyq/`, the 3 archive parts ×2 path+size, 2 zips,
  `brave.exe`) — it goes GREEN at C3 when `git rm --cached` lands; a clean 4-path subset → OK; a renamed copy of the EXE →
  caught by content. Empty-file gotcha: two zero-length tracked `.run/` files shared the manifest SHA1 of the zero-length
  payloads SC04/SC05 `FILE_029/1.6` — zero-length files are exempt.
- **Until C3 the `audits` job is RED on purpose** (the purge set is still tracked); `compile-only` is green from the
  first push. The README statement (byte-identity verified locally with the disc) is D1's.

### P33 B5 (S86–S87, 2026-09-06) — Ghidra regenerability: the RE work as text, the binary DB rebuilt and PROVEN from it
- **Why.** The Ghidra project embeds the game's bytes (verified under the page XOR mask) and leaves git at C3. What R20
  backed up as `ghidra/` is now **`config/ghidra/<program>.jsonl`** — the hand-authored rows only — plus the proof that the
  program regenerates from the disc + the symbol files + that file. Roster: `config/ghidra/ROSTER.md` (6 programs: the
  retail EXE, the resident, `ov_SC01_077`, `ov_SC06_018`, the two prototypes); the other 123 live programs carry no
  hand-authored rows and regenerate on demand (`tools/prefetch_fleet.py`).
- **The delta model.** `ExportAnnotations` dumps EVERYTHING; the hand-authored part is what a fresh rebuild does NOT
  reproduce (baseline subtraction), minus three measured analysis-drift classes (see the `ghidra_annotations_delta.py` row).
  Measured (S87): resident / both overlays → container rows only (their names all come from the symbol files); the retail
  EXE → **38 hand-authored rows** (13 annotated functions incl. 3 the ELF does not define — `SaveLoadRoutine`, `SPU_OBJ_B44`,
  `SYS_OBJ_25B0` — 22 plate/EOL comments, 3 labels) after dropping 29 set-drift functions in the LINKED regions and 1 Error
  bookmark; the two prototypes → 0 after dropping 10 + 5 name-lag rows (their DBs were never re-mirrored from the curated
  proto symbol files). **The DB held no hand-authored types at all** (`types=0` in every program).
- **Controls (R39, S87, resident):** negative — one `block` row's end address mutated in the committed file → `PROOF FAIL`
  (rc 1); positive round-trip — a synthetic EOL comment, `Note` bookmark, user label and retyped signature appended → run 1
  `BFMANN funcs=1 comments=1 bookmarks=1 labels=1 failed=0`, the re-exported delta contains them, `PROOF PASS`; run 2 with
  that delta as the file → `PROOF PASS` (idempotent). The delta filter's own controls: the synthetic rows survive it; a
  hand-renamed name-only diff is KEPT (only auto names count as lag).
- **Gotchas that cost the S86 session:** (1) the OSGi bundle — one uncompilable script disables the whole directory and
  the headless log names every script, never the error; the fix was a hand `javac` (3 errors: `Long`→`int` unboxing ×2,
  and no `LocalVariableImpl(String,int,DataType,int,Program)` ctor — use `VariableStorage(program, off, size)`);
  (2) Ghidra refuses a project path with a `.`-prefixed component — the scratch project lives under `build/`;
  (3) `-process` without a name processes every program in the folder (one `-readOnly` run exports all 129);
  (4) `/undefined` is `DataType.DEFAULT`, in NEITHER type manager — main's first proof "passed" the cmp while 13 of 13
  func rows had failed to import (the plate-comment rows had set the same function comments); the resolver maps it
  explicitly and `ghidra_rebuild.sh` now dies unless the import printed `failed=0` (R49; fake `failed=2` refused,
  the passing population re-proven); (5) the live EXE's RAM tail block (0x800c7f08+) is `init:true` from the Phase-1
  import and `init:false` rebuilt — no hand-authored row lives there (7 auto functions + 1 Error bookmark), the
  committed row takes the rebuild's value.
- **Proofs (S87, all `PROOF PASS`, `failed=0`):** resident 65 s · ov_SC01_077 169 s · ov_SC06_018 173 s · SLUS_007.26
  210 s (`BFMANN funcs=11 comments=11 unchanged=16 rows=70`) · sep8 202 s · aug31 206 s. `tools/ghidra_roster.py --check`
  is in `tools-health` (ignores the per-machine proof column; controls: proof marker removed → OK, census edited → STALE).
- **Same change:** `ExportSymbols.java` R15 fix (output-path arg, refuses to overwrite, refuses `config/`); every
  `tools/ghidra_*.sh` and `Makefile` `GHIDRA_PROJ` repo-relative (`BFM_GHIDRA_PROJ` override); `DefineFunctions.java`
  takes its list path as arg 1; `ImportPsyqGdt.java` finds the gdt under the install dir; `make print-<VAR>`; the
  `.claude/settings.json` hooks `$CLAUDE_PROJECT_DIR`-relative with the silent no-op (§2.8).

### P33 B4 (S86, 2026-09-06) — `tools/fetch_psyq.sh`: the OPTIONAL PsyQ SDK objects, user-supplied and verified
- **What it is for.** Byte-identity never needs Sony's libraries (without them main links its INCLUDE_ASM tiles — the
  fresh-clone proof in B3 built all 218 that way). `tools/fetch_psyq.sh [--disc <RTL-4.0 Track 1 .bin>] [--from <dir>]
  [--no-build]` is for a developer who wants `make check BINARY=main` to link Sony's REAL objects (the 1,256 LINKED
  functions): it obtains and verifies every piece against `tools/psyq_CHECKSUMS.sha256` (rows relative to `tools/psyq/`,
  which is gitignored — nothing Sony-copyrighted is redistributed), then runs the existing builders and `make sdk-dual`.
- **Pieces and provenance:** `psyq-obj-parser` — decomp.me's release tarball
  `https://github.com/decompme/compilers/releases/download/compilers/psyq-obj-parser.tar.gz` (tarball sha256 `353495f1…`,
  the static x86-64 binary inside `4fba623a…` — identical to the copy this project used since Phase 7); the **Runtime
  Library 4.2** 7z — archive.org `https://archive.org/download/play-station-programmer-tool-runtime-library-version-4.2.7z/
  PlayStation_Programmer_Tool_-_Runtime_Library_Version_4.2.7z` (383,431 B, sha256 `e4f5a678…`) → `tools/psyq/lib421/`
  (the `LIB/42PATCH/J421PD.ZIP` payload: LIBPAD.LIB 4.2.1 + LIBAPI.LIB 4.2, both sha256-rowed); the **20 PsyQ 4.0 libraries
  — NO public download**: they are `PSX/LIB/*.LIB` on the redump disc *PlayStation - Programmer Tools - Run-time Library
  4.0 (USA) (PC-CD ROM Release 2.0)* (DTL-S2002, ISO volume `PROGTOOL`); `tools/psyq_libs_from_disc.py <Track 1 .bin>
  <out>` extracts them with the project's own ISO9660 walker (`tools/bfm_extract/iso9660.py`, the same reader
  `make disc-extract` uses) — every LIB is checked against its recorded sha256 (LIBCD.LIB from the disc == the copy used
  since Phase 7). Without `--disc`/`--from` and without `tools/psyq/lib40/` the script REFUSES and names the disc (R43).
- **Builders it runs (unchanged, all regenerable):** `tools/psyq_build_libs.sh LIBCD LIBETC LIBGPU LIBMCRD LIBC2 LIBGTE
  LIBGS LIBSPU LIBSND LIBCARD` (→ `.run/obj40/<lib>` + `tools/psyq/lib40_elf/*.a`), `tools/make_libgs.sh` (→
  `.run/obj40/libgs_used`), `tools/make_snd_used.py` (→ `.run/obj40/snd_used`), the lib421 ELF step (→
  `.run/obj42/{libpad421,libapi42}`), `tools/make_apicard_used.py` (→ `.run/obj42/apicard_used`); then `make -j$(nproc)
  sdk-dual`. Which region needs which: `.run/obj40/{libcd,libetc,libgpu,libmcrd,libc2,libgte}` + `libgs_used` + `snd_used`
  from the 4.0 LIBs; `.run/obj42/{apicard_used,libapi42,libpad421}` from LIBCARD 4.0 + the 4.2 archive. `Psy-Q_46.zip`,
  `PSYQ_SDevTC_v4.5.zip`, `conv47/` and the 4.0 Win32 tools feed NO linked region (research artifacts; archive repo only).
- **Controls (S86):** no source → refuse (rc 1, the message); `--from` a directory with one corrupted LIB → `sha256 MISMATCH
  for tools/psyq/lib40/LIBTAP.LIB`, rc 1, nothing built; the disc path → see `phase-ends/CURRENT_PHASE.md` B4 for the run.
- `tools/psyq/CHECKSUMS.sha256` → **`tools/psyq_CHECKSUMS.sha256`** (git mv; the directory it lived in leaves git at C3).

### P33 B3 (S86, 2026-09-06) — `tools/bootstrap.sh` / `make bootstrap`: the fresh-clone setup
- **`tools/bootstrap.sh`** (idempotent, never sudo): apt packages of §4.5 checked with `dpkg -s` and the missing ones printed
  as ONE `sudo apt-get install` line (never run); `.venv` created from `requirements-python.txt` (pinned; a no-op when
  satisfied); `git submodule update --init`; `sha256sum --check tools/bin/CHECKSUMS.sha256` then each cc1 tarball extracted
  into its own `tools/bin/gcc-2.7.2-{psx,cdk}/` unless `cc1` already exists; finally `make check-env` (its exit status is
  the script's). `make bootstrap` is the alias. Idempotent run on a set-up tree: 1.4 s.
- `make check-env` additions: 4b) the other three submodules populated (WARN — matching tooling, not build inputs),
  4c) the four tracked splat preset headers present (FAIL), 8) `[INFO] extracted payloads present: N / 218 binaries`
  (the census of the fleet's inputs; the hint names `make disc-extract`).
- The **fresh-clone proof** (the "stranger with their own dump" criterion, gen2-roadmap Phase-14 milestone (b)): `git clone
  --no-local` → `tools/bootstrap.sh` → `ln -s <your disks> disks` → `make disc-extract && make extract-all && make
  check-all` → `check-all: 218 passed, 0 failed of 218`. Recorded in `phase-ends/CURRENT_PHASE.md` (B3) with timings.

### P33 B2 (S86, 2026-09-06) — portable includes, audited
- 34 lines in 19 `src/ov_*/…_jr_*.c` files (15 binaries) carried `#include "/home/musashi/bfm-decomp/src/shared/
  engine_core.h"` (30) / `engine_types.h` (4) — the absolute spelling the jr-isolation tooling once wrote; byte-neutral
  here, a hard build failure on any other machine. Respelled to the tree's own `../shared/…` form (3,978 prior uses) and
  each of the 15 binaries re-gated (`make extract BINARY=<b> && make check BINARY=<b>`).
- `tools/audit_text_sources.py` (in `tools-health`) gained the **portable-include class**: an absolute path, an
  angle-bracket include (no system/SDK header is on the include path — the build's only include path is `-Iinclude`),
  or a quoted include that resolves to no file / outside the repo is an offender. R39 controls: 34 offenders in 19 files
  before the fix (all ABSOLUTE), 0 after; 4,299 sources scanned (the coverage line, R32).

### P33 B1 (S86, 2026-09-06) — `make disc-extract`: the rom→decoder step, promoted into the build
- **`make disc-extract`** (`DISC_DIR ?= disks`): the repository ships no ROM bytes (H1 in force). The target (1) probes
  `extracted/retail/` against the committed oracle (`extract.py --verify`, **0.7 s** when up to date → no-op), else (2)
  requires `disks/Brave Fencer Musashi (USA) (Track 1).bin` (exit 2 with the staging instruction), (3) verifies the dump
  is the canonical redump one (`extract_exe.py --verify-disc`: Track-1 SHA1 `b44f0f0a…` + CRC32 `c238191b`; a truncated
  or foreign dump FAILS and nothing is written), (4) extracts everything and COMPARES against the committed
  `extracted/retail/manifest.jsonl` (`extract.py --expect-manifest`: identical → nothing written; different → the actual
  manifest goes to `.run/extract/` with the first 20 differences listed, exit 1), (5) re-verifies the tree. Measured:
  **15.7 s wall** for the full 4-track extraction + manifest compare + verify (1,801 files, 759 MB). `extract`/`extract-all`
  call it when a payload is absent / once up front, so the R22 chain on a fresh clone is `make disc-extract && make
  extract-all && make check-all`. A Track-1-only dump is accepted with an explicit **PARTIAL** verdict (`--allow-missing-
  audio`: the 3 `.DA` audio rows from Tracks 2–4 are excluded from the compare and the verify; without the flag a partial
  extraction FAILS, R43). The committed oracle is never overwritten by a build step; regenerating it is a deliberate plain
  `extract.py` run. `extracted/proto/` (the two prototype EXEs) is NOT produced here — it comes from the prototype discs via
  `tools/bfm_extract/extract_proto_exe.py`.
- `make check-env`: the EXE's absence is now a `[WARN]` with the instruction (present-but-wrong stays `[FAIL]`); new step 7
  asserts the oracle is self-consistent (`manifest.sha1 == sha1(manifest.jsonl)`); `[INFO]` disc presence. `make help`
  rewritten for the live targets. `make clean` no longer deletes the four splat preset headers — `include/include_asm.h`,
  `macro.inc`, `labels.inc`, `gte_macros.inc` are TRACKED (generic splat presets, identical for every binary, ROM-free; the
  compile-only CI needs them; a splat preset change shows as a diff).
- `.gitignore` re-tightened to H1: `/dumps/*.bin`, `/session archive/`, `/tools/ghidra-ext/*.zip`, `/tools/brave-CUE/brave.exe`,
  `/ghidra/` (whole), `/tools/psyq/` (whole; checksums move to `tools/psyq_CHECKSUMS.sha256` in C3), the EXE re-include
  dropped (only the two manifest files stay under `extracted/`), the header rewritten. Tracked files under those paths stay
  tracked until the C3 `git rm --cached` commit (ignore rules bind untracked paths only).

### P33 A4 (S86, 2026-09-06) — the family map carries its own coverage
- `tools/family_hseq.py` → `.run/family_hseq.json` now records `"binaries"` (the binaries it SCANNED — 217: 141 overlays +
  75 modules + the resident) and `"open_instances"`; `load()` returns `(instances, scanned)`. Reason: at 100% `families`
  is empty, and `tools/audit_binaries.py` CHECK 4 inferred coverage from family members — a regenerated, COMPLETE map read
  as "217 onboarded overlays missing" (the P32-close `[warn]` about 6 md_ binaries was the stale pre-onboarding file).
  CHECK 4 now reads `binaries` and warns "predates the coverage field" on an old-format map (R39 control run both ways).
  `docs/family-hseq.md` regenerated (0 families — the frontier is empty).

### P33 A3 (S86, 2026-09-06) — the with/without-SDK dual as a first-class target
- **`NO_SDK=1`** (Makefile knob): `make check BINARY=main NO_SDK=1` skips every `psyq_integrate` rewrite AND the `-T`
  externals fragments, so main links the pristine splat script against its INCLUDE_ASM stub tiles — exactly the link a
  public clone without Sony's objects performs (contract §1.2, the fresh-clone fallback invariant). Until now that leg
  was exercised only by hand (`mv .run/obj40 .run/obj40.off`) and it regressed once unnoticed (`config/symbols.us.txt:248`,
  the `CdReadyCallback` name).
- **`make -j$(nproc) sdk-dual`**: leg 1 extract + check WITH the objects (map must list `build/psyq/libcd/`) → leg 2 extract
  + `rm -rf build/psyq` + check `NO_SDK=1` (map must list `build/src/libcd1.o` and no `build/psyq/`) → leg 3 extract + check
  (the tree back in its default WITH state); both legs against `config/check.us.sha`; maps kept in `.run/P33/verify/`.
  The extracts between legs exist because `psyq_integrate` rewrites `build/us/SLUS_007.26.ld` in place (the incremental
  trap `tools/gate_main.py` documents). REFUSES to run when any of the 11 SDK object dirs is absent (one leg twice is not a
  dual, R32); `tools-health` calls it after `sig-main`, or prints `[skip] sdk-dual: no SDK objects on this machine` — there
  the default build already IS the without leg.

### P33 A2 (S86, 2026-09-06) — reporting instruments made regenerable and honest
- `tools/main_seed_ends.py [--map build/us/SLUS_007.26.map] [--out .run/seeds.main.txt]` — main's game-code function
  boundaries DERIVED from the build (link-map `.text` sections × each object's `nm` symbols; LINKED subsegs and
  `build/psyq/` skipped; tiling + 4-alignment + first-symbol-at-0 asserted, R32; totals printed with denominators).
  Feeds the rewritten `make sig-main` (§6.8 above).
- `tools/progress.py`: main's sig = `.run/sig.main.jsonl` (build-derived) → legacy `.run/sig.SLUS_007.26.jsonl` →
  **SystemExit** (no silent `mt=0`); the digest's oracle clause comes from `progress.main_oracle_line()` (live
  `corpus.audit('main')`), the provenance + date of the sig used are printed on the MAIN line.
- `tools/backlog.py`: `linked_closed(binary, addr)` — a main address inside a LINKED PsyQ range is retired by `prune`
  (byte-identical by link, not work); controls: `0x80062144` True, `0x80018730` False, non-main False. The legacy S70
  row `func_80062144` is gone; `docs/backlog.md` reads 0 open.
- `tools/dup_report.py`: main's sig path → `.run/sig.main.jsonl`.

### P32 T4c (S85, 2026-09-06) — real-TU dump instruments
- `tools/cc1_dumps_tu.sh <rtu_match --work dir> <tag>` — dumps every gcc-2.7.2 pass (-dr -ds -dj -dl -dg -df -dc -dS -dL) of the
  SPLICED REAL TU that `rtu_match --work` left behind (`<dir>/<fn>/t.c`); the standalone `tools/cc1_dumps.sh` compile is not
  faithful on main TUs. Output `${DUMP_ROOT:-.run/P32/t4e}/dumps_<tag>/`.
- `tools/alloc_table.py <tag> [fn] [dump_root]` — from those dumps, the function's global allocation ORDER with refs / live
  length / priority / hard reg (global.c `allocno_compare`); the callee-saved bank is that order (§501-R).
- `tools/cc1_dumps.sh` now also writes the `.loop` dump (`-dL`): the "not desirable"/"moved to"/"matches" lines (§501-R).
