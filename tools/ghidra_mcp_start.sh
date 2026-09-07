#!/usr/bin/env bash
# tools/ghidra_mcp_start.sh
# Idempotent, fully-detached start of the headless GhidrAssistMCP server for BFM,
# using BfmMcpServer.java (server + clean save-on-shutdown — see that file).
# Serves a program from the "bfm" Ghidra project over MCP on 127.0.0.1:8080.
# Program defaults to SLUS_007.26 (retail); pass an alternate as $1 to serve a
# prototype, e.g.  tools/ghidra_mcp_start.sh sep8_SLUS_007.26
# (only ONE program is served per session; stop with ghidra_mcp_stop.sh to switch).
#
# Designed to run from a SessionStart hook:
#   * no-op if the server is already serving on :8080 (safe to run every session),
#   * the launched server is fully detached (setsid+nohup+disown) so it OUTLIVES the
#     launching shell and the Claude Code session (persists across sessions in a phase).
#
# After "serving" appears in the log, run `/mcp` in Claude Code once per session to
# attach the mcp__ghidra__* tools (a running session cannot self-reconnect).
#
# PERSISTENCE: MCP writes are saved only on CLEAN SHUTDOWN (analyzeHeadless commits the
# open transaction + saves on close). Save+stop with tools/ghidra_mcp_stop.sh; resume by
# re-running this script. There is no mid-session save (GhidrAssist holds an open txn).
set -uo pipefail
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"   # P33 B5: repo-relative, no $HOME/bfm-decomp assumption

GHIDRA="${GHIDRA_INSTALL_DIR:-$HOME/ghidra_12.1_PUBLIC}"
PROJ_DIR="${BFM_GHIDRA_PROJ:-$REPO/ghidra}"
PROJ="bfm"
PROG="${1:-SLUS_007.26}"   # program to serve; default retail, pass a proto name to override
PORT="8080"
RUNDIR="$REPO/.run"; mkdir -p "$RUNDIR"   # project-local runtime scratch (never /tmp)
LOG="$RUNDIR/ghidra-mcp.log"
SCRIPTS="$REPO/tools/ghidra_scripts"
STOPREQ="${BFM_MCP_STOPREQ:-$RUNDIR/mcp-stop.req}"

# 0) Not this machine's job? A contributor's clone has no Ghidra install and no ghidra/ project
#    (the DB left git at P33 B5); the SessionStart hook must then be a silent, successful no-op.
if [ ! -x "$GHIDRA/support/analyzeHeadless" ] || [ ! -d "$PROJ_DIR/$PROJ.rep" ]; then
  exit 0
fi

# 1) Already serving? no-op (idempotent across sessions).
if ss -tln 2>/dev/null | grep -qE ":$PORT([^0-9]|$)"; then
  echo "ghidra-mcp: already serving on :$PORT — no-op"
  exit 0
fi

# 2) Clear stale stop sentinel + a stale project lock (only when no analyzer is alive).
rm -f "$STOPREQ" 2>/dev/null || true
if ! pgrep -f 'ghidra.app.util.headless.AnalyzeHeadless' >/dev/null 2>&1; then
  rm -f "$PROJ_DIR/$PROJ.lock" "$PROJ_DIR/$PROJ.lock~" 2>/dev/null || true
fi

# 3) Launch fully detached so it survives this shell and the Claude session.
echo "ghidra-mcp: starting headless server (detached) -> $LOG"
setsid nohup "$GHIDRA/support/analyzeHeadless" "$PROJ_DIR" "$PROJ" \
  -process "$PROG" -noanalysis \
  -scriptPath "$SCRIPTS" \
  -preScript BfmMcpServer.java host=127.0.0.1 "port=$PORT" "stopreq=$STOPREQ" \
  >"$LOG" 2>&1 </dev/null &
disown 2>/dev/null || true

echo "ghidra-mcp: launched (pid $!). Project load takes ~10-60s."
echo "ghidra-mcp: wait for 'serving' in $LOG, then run /mcp in Claude Code."
