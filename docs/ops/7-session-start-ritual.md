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

