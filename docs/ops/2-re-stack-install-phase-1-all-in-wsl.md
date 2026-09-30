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
- **Context guard (user-level, 2026-09-08 S96).** `~/.claude/statusline.sh` writes the context-window percentage to
  `~/.claude/ctx_pct.<session_id>` on every refresh; the user-settings `PostToolUse` hook `~/.claude/ctx_guard.sh` reads it and,
  once per session at ≥ 90 % (`CTX_GUARD_THRESHOLD`), injects "90% context. decide on the best place to checkpoint for a fresh
  session" (re-arms below the threshold). Hooks receive no context figures — the status line is the only source. S94 died at 91 %
  with no checkpoint; this is the alarm.
- **`ghidra_mcp_stop.sh`** — the **only persistence event**: it requests a clean save+close by dropping the `.run/mcp-stop.req` sentinel, waits for the server to report **"Save succeeded"**, then releases the project `.rep` lock. **Never `SIGKILL` the server to stop it** — that skips the save and loses the work. Clean stop is the save.
- **`ghidra_mcp_verify.sh <addr> <name>`** — read-only persistence re-check (rule R9): after a clean stop, re-reads the named symbol at the address to confirm the write actually landed on disk.

**Client reconnect after a server restart (operational, Phase 13).** Restarting the server (`stop` then `start` — e.g. for a headless raw-blob import per R23, or to serve a different program) **drops the Claude Code MCP client's SSE connection**: every `mcp__ghidra__*` call then **times out** until the client reconnects, and Claude **cannot** run `/mcp` itself. So the rhythm after any server restart / program switch is: **pause and ask Drew to run `/mcp`**, then make one cheap `get_binary_info` call (G2) before continuing. Do not try the calls, hit timeouts, and work around them. (Memory: `mcp-reconnect-after-restart`.)

**Session hooks (committed `.claude/settings.json`, as of 2026-06-15):**

- `SessionStart` → runs `bash "$CLAUDE_PROJECT_DIR"/tools/ghidra_mcp_start.sh` (auto-starts the MCP server when a Claude Code session begins; **P33 B5:** repo-relative, and the script is a silent `exit 0` when `$GHIDRA/support/analyzeHeadless` or `ghidra/bfm.rep` is absent — a contributor's clone has neither).
- `SessionEnd` → runs `bash "$CLAUDE_PROJECT_DIR"/tools/ghidra_mcp_stop.sh` with **`timeout: 150`** s (auto-saves Ghidra on a clean session exit; a no-op when nothing serves on :8080).

These hooks live in the **committed `settings.json`** — NOT the gitignored `settings.local.json` — specifically so they are backed up to the remote. Consequence to internalize: **closing Claude Code does NOT save unless the `SessionEnd` hook fires**, and it fires only on *clean* exits — a hard crash of the CC process still loses RAM-only writes. This is exactly why mid-RE clean-stop checkpoints matter.

**Committing Ghidra RE work:** clean-stop (which saves) **FIRST**, then commit `ghidra/`. The `.rep` lock never blocks git (the lock is gitignored, and ext4 reads open files fine), but do **not** commit `ghidra/` mid-RE — that snapshots a stale on-disk DB that predates the in-RAM writes.

---

