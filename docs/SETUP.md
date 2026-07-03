# SETUP.md — Environment Setup & Daily Operations Reference

> **This file is the EVOLVABLE reference layer.** Unlike `PROJECT_CONTEXT.md` (permanent, never edited), this document holds volatile facts — pinned versions, URLs, commands, ports — and **may be updated freely** as tools move. Note each change in the active phase log (`CURRENT_PHASE.md`). Items marked **TBD** / **UNVERIFIED** / **JP-only — re-derive for US** are honest gaps: confirm before relying on them, then update this file.

Last full revision: 2026-06-10 (initial authoring, pre-Phase-1 — nothing below is installed yet except the repo itself; same-day conversion to the all-in-WSL / Linux-first architecture — everything now runs inside a single WSL2 Ubuntu 24.04 clone, no Windows/WSL split).
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

- `SessionStart` → runs `ghidra_mcp_start.sh` (auto-starts the MCP server when a Claude Code session begins).
- `SessionEnd` → runs `ghidra_mcp_stop.sh` with **`timeout: 150`** s (auto-saves Ghidra on a clean session exit).

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

The single clone lives at `~/bfm-decomp` (ext4). Builds, splat, asm-differ, Ghidra, and Claude Code all run here. In this clone: `git config core.filemode true`. **TBD:** the canonical remote URL (GitHub private repo planned; not created as of this writing).

### §4.4 Copy the disc dump into the clone

One-shot copy onto ext4 is fine (and required once):

```bash
mkdir -p ~/bfm-decomp/disks
cp '<dump-source>/Brave Fencer Musashi (USA)/'*.bin \
   '<dump-source>/Brave Fencer Musashi (USA)/'*.cue ~/bfm-decomp/disks/
```

`<dump-source>` is wherever the disc dump currently lives (e.g. a one-time download into `~/Downloads`, or a one-shot copy from external media). `disks/` is gitignored — no ROM-derived bytes ever reach the remote (rule H1).

**Status (Phase 2, 2026-06-13):** the disc was staged early — extraction needs it before Phase 4. Track 1 alone (it holds all 27 root files) was copied once from the `/mnt/z` dump to ext4 at `disks/Brave Fencer Musashi (USA) (Track 1).bin` (364,846,944 bytes). WSL `extract_exe.py --bin "disks/…(Track 1).bin" --verify-disc` **PASSED** — SHA1 `b44f0f0a19936f23b26188b658e13201a6a9c211`, CRC32 `c238191b`, both == redump — which **closes the Phase-1 deferral** (verify-disc had previously only run on Windows; PhaseEnd_Phase1 Deviations).

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

- `gcc-2.7.2-psx` = community GCC 2.7.2 PSX build (primary candidate).
- `gcc-2.7.2-cdk` = **cygnus-2.7.2-970404**, the exact base of PsyQ 4.0/4.1's CC1PSX (added in old-gcc 0.14).
- **sha256 (RECORDED Phase 4, old-gcc 0.17, ledger #7):** `gcc-2.7.2-psx.tar.gz` = `500a459b3485e885a8d302cac23c2a4632f3900e03a09153f6190699fd723571`; `gcc-2.7.2-cdk.tar.gz` = `42bb0df96db11a9b5d2e23d78bdc962791f40046280d3d360da93fe5eef6f0bb`. Committed to `tools/bin/CHECKSUMS.sha256` (gitignore exception `!/tools/bin/*.sha256`); re-verify with `sha256sum --check tools/bin/CHECKSUMS.sha256`.
- **CORRECTION (Phase 4):** these are **32-bit i386 statically-linked** ELF binaries (NOT x86-64 as previously written) — they run on x86-64 WSL2 via the kernel's IA-32 emulation (verified: `cc1` smoke-compiles to MIPS asm and self-identifies as `GNU C 2.7.2 [AL 1.1, MM 40] Sony Playstation`). Still Linux-only — *why* the build side must be Linux/WSL2. As-built layout: `tools/bin/gcc-2.7.2-psx/cc1` + `tools/bin/gcc-2.7.2-cdk/cc1` (matches the §6.2 path).

### §4.8 Optional: PsyQ 4.0/4.1 binaries for arbitration (via Wine)

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

Locally verified on the extracted US EXE (DetectPsyQ-style masked-pattern scan): **13 pattern hits, of which 12 are genuine `Ps` library stamps** — 9× PsyQ **4.0** (libnums 2, 3, 4, 6, 7, 8, 9, 17, 24), 1× **4.0.1x** (libnum 16), 1× **4.2** (libnum 0), 1× **4.2.1x** (libnum 12); the remaining hit (ver 0x0000 at vaddr 0x8005CD20) is a code false positive. A raw-track scan during research reported 16 hits with extra spurious 4.0 stamps — the extracted-EXE scan is ground truth, and ghidra_psx_ldr's detection at import is the final word (ledger #12). Library copyright string `(c) 1993-1997 Sony` corroborates the era. Conclusion: BFM links **PsyQ 4.0 libraries with 4.2 library updates** ⇒ the GCC 2.7.2/SN32-era toolchain — **NOT sotn's GCC 2.6.3** (the starting-point doc's claim is corrected). PsyQ 4.2 was a library-only refresh: no 4.2 toolchain disc survives (absent from redump/arthus sets), so 4.2 stamps still mean the 4.0/4.1 toolchain.

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
| **vanilla gcc-2.7.2** (the REAL source of our pinned cc1) | authoritative source for the codegen map (cookbook §31 + `docs/gcc-2.7.2-map/`): `sched.c`/`reorg.c` (scheduling), `local-alloc.c`/`global.c`/`reload1.c` (regalloc), `loop.c` (IV/hoist), `cse.c`/`expr.c` (CSE/aliasing). Staged Phase 23. | `tools/reference/gcc-2.7.2` | GNU 2.7.2 release | (re-fetch: GNU ftp `gcc-2.7.2.tar.gz`) |
| `ladysilverberg/xenogears-decomp` | Square, Oct 1998, **gcc-2.7.2-psx + -cdk** (our exact compiler); mine transferable quirk idioms + `gears.toml` per-module presets | `tools/reference/xenogears-decomp` | `main` | `f27c0768b1ad10812cec776cadadb85ae70aadee` |

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

| Target | Does |
|---|---|
| `make extract` | splat split per `config/splat.us.*.yaml` → `asm/`, linker scripts |
| `make build` | full pipeline → `build/us/SLUS_007.26`, auto-runs the SHA1 check |
| `make check` | standalone SHA1 manifest verification (byte-for-byte = the only "OK") |
| `make expected` | snapshot `build/us` → `expected/build/us` (asm-differ baseline) |
| `make check-env` | toolchain preflight, exit 0 = environment sane (§4.9) |
| `make clean` | mandatory after ANY `config/` change, before re-extract |

**As-built (Phase 5, 2026-06-14):** all five implemented in the root Makefile. The code is **100% assembly** (the phase's "all-asm byte-match"; the cpp→cc1→maspsx→as `c` path is wired-but-dormant until Phase 6). `make extract && make build && make check` → `build/us/SLUS_007.26` **SHA1-identical** to the original. Config `config/splat.us.exe.yaml` (platform psx, compiler PSYQ, subalign 2, gp_value 0x80074750, main segment `align: 4` so the text→data boundary isn't 16-byte-padded); committed checksum `config/check.us.sha`. Build chain = `as -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0` → `ld -T <splat .ld> -T undefined_syms_auto.txt -T undefined_funcs_auto.txt --no-check-sections` → `objcopy -O binary`.

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
2. In `src/800.c`, replace the `INCLUDE_ASM(... <fn>);` line with the C function body.
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
- `ld_interleave.py`: `--front <obj> --tail <obj>` (the EXE's LZSS-sandwich `.data` objects)
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
- Per-binary `<bin>_GHIDRA_PROG` → `make sig-refresh BINARY=<bin>`; `diff_settings.py` + the three
  report scripts gain a `<bin>` entry; `make expected` is per-binary-safe (merge-copy, no sibling clobber).

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
  `tools/psyq/CHECKSUMS.sha256`) — Phase 12 links its embedded SDK code from 4.7, not the EXE's 4.0 libs.

## §7 Session-start ritual

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
| | `ImportOverlay.java` | Import an overlay segment into the project. |
| | `VerifyOverlay.java` | Verify an imported overlay against expected bytes. |
| | `GetSymbolAt.java` | Read the symbol at a given address (scripted lookup). |
| | `DecompileAt.java` | Decompile the function at a given address (scripted scaffold). |
| | `DefineFunctions.java` | Disassemble + create functions at splat's validated entry points (`.run/<prog>_funcs.txt`) — completes a raw-blob program's function set (Phase 10). |
| | `DecompileFunctions.java` | **Batch**-decompile a list of addresses (arg0 = addr-per-line file, arg1 = out-dir) → `<name>.c` each. Headless harvest Ghidra-C pre-pass (Phase 17); no live MCP / `/mcp` needed. Run: stop MCP, `analyzeHeadless ghidra bfm -process <prog> -noanalysis -postScript DecompileFunctions.java <addrfile> <outdir>`. |
| | `tools/ghidra_import.sh` | Headless `analyzeHeadless` import/analysis driver (PS-X EXE; auto-detect PSX loader). |
| | `tools/ghidra_import_raw.sh` | Headless import of a RAW flat blob — `BinaryLoader` + `--loader-baseAddr <vram>` + `PSX:LE:32:default` (resident blob / Gen2 overlays; no PS-X EXE header). |
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
| | `tools/new_overlay.sh` | One-command location-overlay onboarding: instantiate `config/splat.<ov>.yaml` from the template (+ non-4-aligned `bin` carve), register the binary in `config/overlays.mk` + the 4 report/diff dicts, `make extract && build` byte-check. Idempotent (Phase 13, cookbook §13). |
| **PsyQ library linking** (cookbook §8/§9) | `tools/psyq_lib_split.py` | Split a PsyQ `.LIB` into per-object members. |
| | `tools/psyq_build_libs.sh` | Build the PsyQ libs from split members. |
| | `tools/psyq_identify.py` | Identify which SDK objects a region's functions belong to. |
| | `tools/psyq_link.py` | Link identified PsyQ objects into the build. |
| | `tools/psyq_link_lib.py` | Per-library link driver. |
| | `tools/psyq_link_region.py` | Link a specific address region from PsyQ libs. |
| | `tools/psyq_integrate.py` | Integrate linked PsyQ results back into the source tree. |
| | `tools/make_libgs.sh` | Build/link the `libgs` block (cookbook §9). |
| | `tools/gen_lib_subsegs.py` | **(Phase 8)** Generate splat subseg lines + integrate stub list for a multi-block library (section-size-correct boundaries; cookbook §9.6). |
| | `tools/make_snd_used.py` | **(Phase 8)** Build the combined libspu+libsnd curated dir (alias dedup by byte-match, scattered-`.bss` exclusions; §9.6). |
| | `tools/make_apicard_used.py` | **(Phase 8)** Build the combined libapi+libcard curated dir (§9.6). |
| | `tools/ld_interleave.py` | Interleave linker inputs to match original section ordering. |
| | `tools/split_src_region.py` | Split a `src/` region file at object boundaries. |
| **Reports** | `tools/progress.py` | Per-binary decomp progress (`make report`); counts dedup-shared fns as REAL via the registry (Phase 11). **`--fleet`** (Phase 15) aggregates all 136 binaries → `docs/progress.fleet.md` (deterministic, source-derived). |
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
| | `tools/inject_capped_externs.py` | **(Phase 23, cookbook §28d)** The "macro-extern-injection" lever for reach-134 fns matched INLINE in ov_SC01_077 but skipped by `dedup_propagate` as "not self-contained": source the EXACT file-scope `extern …;` the overlay already declares for each referenced `func_`/`D_` symbol and inject it BLOCK-scope so the lifted macro body resolves in every overlay. Byte-neutral (gate proves 077 stays `d19c9580…`); fail-safe (only rewrites a fn whose injected body then `compiles_standalone`). `--overlay`/`--src-file`/`--min-reach`/`--apply`. Then `make build BINARY=ov_SC01_077` → `dedup_propagate --auto-from`. |
| | `tools/exemplar_miner.py` | **(Phase 20 / T2, cookbook §20)** Residual router: consume `.run/wall_taxonomy.json` (bucket/nins) + per-overlay reach (dedup_propagate's computation) → route every residual stub to a lever (WAVE / STRUCT / PINS / STUB) ranked by reach×size → `docs/exemplar_curriculum.md` + `.run/exemplar_routing.json` (wave-target list). "Scan all residuals, size the pools, pick the teachers." Caveat: its `mismatch` is the M2C-draft mismatch, not the hand-match floor. |
| | `config/dedup.us.yaml` / `src/shared/*.h` | The code-share registry + the shared bodies (one macro → N sites, byte-gated). |
| | `make report` / `make sig-refresh` / `make sig-overlays` | Convenience targets: reports (+`--cross`) / Ghidra signature-dump / Ghidra-free sign all 134 overlays. |
| **LLM matching tier** (Phase 21–23, `docs/gen2-mips-matching-model.md`) | `tools/gate_stage.py` | The shared deterministic bank/log spine: `canon_resident_calls → cast_call_sites → sig_unify → harvest_verify (byte-gate) → dedup_propagate → backlog`. **Binary-agnostic** (resolves src/asm/out/good_sha + bare-hash from `binary`; Phase-23 fix). **Phase-23 T10:** optional `lock_path` (per-binary lock) / `verified_out` / `failed_out` (per-worker scratch) / `compute_fleet` for `bulk_harvest`'s parallel gate — all default to the serial behavior. |
| | `tools/harvest_verify.py` | The whole-binary byte-gate (substitute draft → `make build` → keep iff byte-identical, else revert). Sole arbiter (G3/P9). `--verified-out`/`--failed-out` = per-worker result paths (parallel gating, Phase-23 T10). |
| | `tools/backlog.py` | Near-miss ledger (`.run/backlog.jsonl` + `docs/backlog.md`); **fleet-aware** `load_best` (a 077-matched-but-stuck-local fn surfaces via its overlay record; Phase 23). |
| | `tools/lora_grind.py` | Mass-run driver: rotate binaries → draft open ≤N-ins stubs with the served model → gate → propagate. `--min-reach N` (Phase 23) targets shared fns (sig-reach oracle == `dedup_propagate`). |
| | `tools/bulk_harvest.py` | **(Phase 23 / T10)** The phase-separated + parallel-gate harvester (throughput rebuild of `lora_grind`): **(A)** bulk-draft K fresh ≤N-ins stubs (GPU) → **(B)** `ProcessPoolExecutor --workers` byte-gate over DISTINCT binaries (`build/<bin>/**` isolated; `run_gate` per-binary lock + per-worker scratch, `propagate=False`/`commit=False`/`compute_fleet=False`) → **(C)** dedupe-once + ONE commit. Round-robin fuel spread; STOP-sentinel; on-demand/bounded. Measured 2026-07-01: gate **0.4s/fn** (8 workers, ~75× the serial gate) ⇒ drafting is the bottleneck (→ vLLM next). Run: `API_BASE=… MODEL=bfm-match-7b-v3 tools/bulk_harvest.py --binary-glob 'ov_SC03_*' --count 80 --workers 8 --measure`. `lora_grind` kept as the serial fallback. |
| | `tools/grinder.py` | Token-free decomp-permuter daemon on the backlog near-misses; **per-binary** (Phase-23 fix). `auto_supervisor.sh`/`auto_stop.sh` keep-alive + STOP sentinel. |
| | `tools/api_draft.py` | Provider-agnostic LEAN drafter against the served model's OpenAI endpoint. `LEAN_SYS` carries the "translate every instruction, never an empty body" clause (Phase 23 — fixes the v2 empty-leaf overfit). |
| | `tools/serve_local.py` | **Serve the fine-tuned model on the GPU** (base+LoRA via Unsloth, `.venv-train`, OpenAI endpoint) — the in-repo replacement for LM Studio. Run: `LD_LIBRARY_PATH=$(ls -d .venv-train/lib/python3.12/site-packages/nvidia/*/lib \| tr '\n' :) .venv-train/bin/python tools/serve_local.py --adapter models/bfm-match-7b-v3 --name bfm-match-7b-v3 --port 1234`. (Prebuilt `llama-cpp-python` CUDA wheels SIGILL on this no-AVX-512 CPU; the Unsloth/torch path is reliable, no build.) |
| | `tools/export_pairs.py` / `format_finetune.py` / `train_lora.py` / `eval_lora.py` | The corpus→LoRA pipeline (`.venv-train`): mine (asm↔C) pairs incl. the `engine_core.h` **macro bodies** + `engine_types.h` structs (corpus-v3) → Qwen chat-template + compile-filter → Unsloth QLoRA (3080 Ti) → held-out gate-true eval. Datasets/weights gitignored (`datasets/`, `models/`, `.venv-train/`). |

---

## Backup & private-repo posture (rules R20/R21)

This project lives in a **private** remote (rule H1, relaxed: ROM-derived material may be committed while the repo is private). Per-session checkpoint backups (R20) push all irreplaceable work; the lists below record what is and is not pushed as of 2026-06-15.

**Backed up to the private remote (2026-06-15):**

- The **Ghidra project** (`ghidra/`) — with `*.lock` / `tmp*.ps` transients excluded (regenerable / ext4-local lock files).
- **PsyQ SDK working artifacts** (`tools/psyq/`) **MINUS** the two >100 MB raw source archives — the `psyq40usa.zip` and the DTL-S2002 disc `.bin`/`.cue` (re-sourceable, over GitHub's file-size limit).
- **Old-gcc cc1 compiler tarballs** (`tools/bin/*.tar.gz`) — the extracted binaries are regenerable from these, so only the tarballs are kept.
- **Ghidra extension installers** — `tools/ghidra-ext/GhidrAssistMCP_2.8.0.zip` + `ghidra_psx_ldr_2026.06.04.zip` (hard to re-source at exact pinned versions).

**Deliberately NOT backed up** (regenerable, or >100 MB and re-sourceable):

- The disc dump (`disks/`).
- The `extracted/` bulk — regenerate via `make extract`.
- `build/`, `expected/`, `asm/` — all generated.
- `.venv/` — recreate from `tools/requirements-python.txt`.
- The two >100 MB raw PsyQ archives (the `psyq40usa.zip` + DTL-S2002 disc).
- The unused PCSX-Redux Linux AppImage — the real runtime oracle is the Windows-native build.

**Rules:**

- **R20** — back up all irreplaceable RE/decomp work plus gathered hard-to-re-source tooling at per-session checkpoints. This **loosens R8** (which mandated a single commit at phase end): checkpoint commits are now expected within a phase.
- **R21** — keep **THIS file** (`docs/SETUP.md`) current whenever tooling, the MCP setup, the session hooks, or the environment changes.

Sony **PsyQ libs and cc1 stay PRIVATE** — they are excluded from the future curated public mirror (the two-repo public-release plan; see `docs/gen2-roadmap.md`). The four submodules (asm-differ / m2c / maspsx / decomp-permuter) stay **gitlinks** on GitHub (the deliberate no-bloat choice over vendoring); residual risk = upstream deletion of a pinned commit.

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
| 11 | Canonical git remote URL (off-box push/pull backup) | **TBD** (§4.3) |
| 12 | Per-libnum stamp detail (raw-track scan reported 16 hits vs 12 genuine in extracted EXE — extracted-EXE scan is ground truth, see §5.1) | **RESOLVED 2026-06-13** — DetectPsyQ at headless import recorded `PsyQ Version = 4.0.0` (§2.5 step 3) |
| 13 | Overlay load addresses (resident 0x800CDF58 / location 0x80128508, EXE ptr table ~0x62620) | **JP-only — re-derive for US** (owned by docs/memory-map.md) |
| 14 | Greenfield claim: decomp.me scratch search is script-blocked (Cloudflare) | **TBD** — one-time manual browser check for BFM scratches |
