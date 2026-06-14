#!/usr/bin/env bash
# tools/ghidra_mcp_start.sh
# Idempotent, fully-detached start of the headless GhidrAssistMCP server for BFM,
# using BfmMcpServer.java (server + clean save-on-shutdown — see that file).
# Serves SLUS_007.26 (the "bfm" Ghidra project) over MCP on 127.0.0.1:8080.
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

GHIDRA="${GHIDRA_INSTALL_DIR:-$HOME/ghidra_12.1_PUBLIC}"
PROJ_DIR="$HOME/bfm-decomp/ghidra"
PROJ="bfm"
PROG="SLUS_007.26"
PORT="8080"
RUNDIR="$HOME/bfm-decomp/.run"; mkdir -p "$RUNDIR"   # project-local runtime scratch (never /tmp)
LOG="$RUNDIR/ghidra-mcp.log"
SCRIPTS="$HOME/bfm-decomp/tools/ghidra_scripts"
STOPREQ="${BFM_MCP_STOPREQ:-$RUNDIR/mcp-stop.req}"

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
