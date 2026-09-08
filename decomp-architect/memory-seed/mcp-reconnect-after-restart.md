---
name: mcp-reconnect-after-restart
description: After restarting the disassembler's MCP server or switching the program it serves, PAUSE and ask the developer to reconnect the client (/mcp) — the agent's calls time out until then and it cannot reconnect itself
metadata:
  type: feedback
---

Whenever the reverse-engineering MCP server is stopped and restarted — for a headless import, or to serve a different program —
the coding agent's client connection goes stale and every call to that server times out until the client reconnects. The agent
cannot run the reconnect command itself.

**Why:** the first time it happened the agent noted "client may need reconnect" and kept going, burning turns on timeouts and
working around them. The correct move is to stop and ask.

**How to apply:** a server restart always ends with one message — "I restarted the MCP server (now serving X); please run
`/mcp` to reconnect, then I will verify and continue" — followed by one cheap verification call before any real work. Treat
the reverse-engineering database's persistence the same way: the server holds an open transaction while serving, so work is
saved only on a clean stop; renames made through the server may not persist at all — mirror symbols through a headless script
and verify with a read-only reopen.
