# CLAUDE.md — Brave Fencer Musashi Decompilation

Matching decompilation of **Brave Fencer Musashi** (PS1, SLUS-00726 USA). Goal: byte-for-byte identical binaries from C source.

## Mandatory load order — before doing ANYTHING else

1. Read `PROJECT_CONTEXT.md` in full (the permanent constitution: rules, protocols, roadmap).
2. Read every `phase-ends/PhaseEnd_*.md` in numeric order (the build history).
3. Read `phase-ends/CURRENT_PHASE.md` if it exists (the in-phase state).
4. Then follow the **Session Start Protocol** in `PROJECT_CONTEXT.md` — state phase, completed tasks, the single next task, and acknowledge the rules before working.

## Fail-safe hard rules (duplicated from PROJECT_CONTEXT.md in case the above is ever skipped)

- **Never commit ROM-derived content.** The game dump, `disks/`, `asm/`, `assets/`, `build/`, `expected/`, extracted `.CD` contents, and the Ghidra project stay out of git. Review `git status` before every commit.
- **Never edit `PROJECT_CONTEXT.md`.** It is permanent and static. Corrections and state go in `phase-ends/`.
- **A "match" is byte-for-byte assembly equality AND the full-binary SHA1 check staying green.** Never report a functionally-equivalent function, a passing-looking build, or any unverified outcome as done.

## Environment

- Ghidra MCP server config: `.mcp.json` (GhidrAssistMCP, SSE on `http://127.0.0.1:8080/sse`). Ghidra must be running with `SLUS_007.26` open in CodeBrowser before any reverse-engineering work — verify with a cheap MCP call first.
- Builds, splat, and asm-differ run **only in the WSL2 clone** (`~/bfm-decomp`, ext4) — never on `/mnt/z`, never in this Windows tree. Invoke via `wsl.exe` per `docs/SETUP.md`.
- Volatile facts (tool versions, URLs, commands): `docs/SETUP.md`. File formats: `docs/formats.md`. Address ledger: `docs/memory-map.md`.
