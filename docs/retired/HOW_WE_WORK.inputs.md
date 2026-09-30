# HOW_WE_WORK.md source candidates

Written by the migration engine.  Each placeholder lists
every candidate found, with its source pointer.

## DATA_PATHS

- `docs/decision-log.md:1`:
  docs/decision-log.md

- `docs/tool-index.md:1`:
  docs/tool-index.md

## OS_AND_SHELLS

- `CLAUDE.md:68`:
  - Ghidra MCP server config: `.mcp.json` (GhidrAssistMCP, SSE on `http://127.0.0.1:8080/sse`). Ghidra must be running with `SLUS_007.26` open in CodeBrowser before any reverse-engineering work — verify with a cheap MCP call first.
  - Builds, splat, and asm-differ run **only in the WSL2 clone** (`~/bfm-decomp`, ext4) — never on `/mnt/z`, never in this Windows tree. Invoke via `wsl.exe` per `docs/SETUP.md`.
  - Volatile facts (tool versions, URLs, commands): `docs/SETUP.md`. File formats: `docs/formats.md`. Address ledger: `docs/memory-map.md`.
  
  ---

## PROJECT_CONVENTION

- `CLAUDE.md:138`:
  - **Document disabled logic.** When disabling or commenting out any logic based on evidence, leave a structured comment:
    ```
    // DISABLED: [name] — [date or phase]
    // Original intent: [what it was supposed to do]
    // Why disabled: [specific evidence — backtest/live numbers]

## PROJECT_TOOL

- `docs/SETUP.md:757`:
  Every script under `tools/` (plus the two report make-targets), grouped by purpose — one line each. Deep HOW-TO is **not** here: see `docs/matching-cookbook.md` (§6 per-module -O0, §8 rodata island, §9.1–§9.5 library linking) and the relevant PhaseEnd.
  
  | Group | Member | One-line purpose |
  |---|---|---|
  | **MCP lifecycle** | `tools/ghidra_mcp_start.sh` | Spawn the headless MCP server detached → `.run/ghidra-mcp.log`, port 8080 (§2.8). |

## PROJECT_TOOL_COMMAND

- `docs/SETUP.md:757`:
  Every script under `tools/` (plus the two report make-targets), grouped by purpose — one line each. Deep HOW-TO is **not** here: see `docs/matching-cookbook.md` (§6 per-module -O0, §8 rodata island, §9.1–§9.5 library linking) and the relevant PhaseEnd.
  
  | Group | Member | One-line purpose |
  |---|---|---|
  | **MCP lifecycle** | `tools/ghidra_mcp_start.sh` | Spawn the headless MCP server detached → `.run/ghidra-mcp.log`, port 8080 (§2.8). |

## PROJECT_TOOL_PURPOSE

- `docs/SETUP.md:757`:
  Every script under `tools/` (plus the two report make-targets), grouped by purpose — one line each. Deep HOW-TO is **not** here: see `docs/matching-cookbook.md` (§6 per-module -O0, §8 rodata island, §9.1–§9.5 library linking) and the relevant PhaseEnd.
  
  | Group | Member | One-line purpose |
  |---|---|---|
  | **MCP lifecycle** | `tools/ghidra_mcp_start.sh` | Spawn the headless MCP server detached → `.run/ghidra-mcp.log`, port 8080 (§2.8). |

