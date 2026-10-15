# mcp-reconnect-after-restart

Whenever the Ghidra MCP server is **stopped+restarted** (e.g. `ghidra_mcp_stop.sh` then `ghidra_mcp_start.sh` for a headless import) **or restarted to serve a different program**, the Claude Code MCP client's SSE connection goes **stale** — every `mcp__ghidra__*` call then **times out** until the client reconnects. I **cannot** run `/mcp` myself.

**So: the moment I restart the MCP server or switch which program it serves, I must PAUSE work and prompt Drew to run `/mcp`** to reconnect the client. Do not try the calls, hit timeouts, and work around them (that wastes turns) — pause first, ask for `/mcp`, then make one cheap verification call (`get_binary_info`, G2) before continuing.

**Why:** Drew flagged this 2026-06-16 (Phase 13): I restarted MCP to serve a freshly-imported overlay (`ov_SC01_077`), my `get_binary_info`/`get_code` calls timed out, and I noted "client may need reconnect" while proceeding instead of stopping to ask. The correct move is to pause and request `/mcp`.

**How to apply:** This is the standard Gen2 RE rhythm — a headless Ghidra import (R23: stop MCP → import → restart) ALWAYS ends with "🔌 I restarted the MCP server (now serving `<program>`); please run `/mcp` to reconnect, then I'll verify and continue." Related: [[bfm-decomp-context-system]], R23 (MCP stop = persistence), G2 (MCP precondition before RE). SETUP §2.8 documents the lifecycle.
