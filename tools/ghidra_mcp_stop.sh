#!/usr/bin/env bash
# tools/ghidra_mcp_stop.sh — clean stop WITH save (the way headless MCP work is persisted).
# Touches the stopreq sentinel; BfmMcpServer stops the MCP server and returns, then
# analyzeHeadless COMMITS the pending transaction and saves+closes the project (releasing
# the .rep lock). The next session resumes from the saved state. Use at task/phase boundaries.
set -uo pipefail
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"   # P33 B5: repo-relative, no $HOME/bfm-decomp assumption

PORT="8080"
RUNDIR="$REPO/.run"
LOG="$RUNDIR/ghidra-mcp.log"
STOPREQ="${BFM_MCP_STOPREQ:-$RUNDIR/mcp-stop.req}"

if ! ss -tln 2>/dev/null | grep -qE ":$PORT([^0-9]|$)"; then
  echo "ghidra-mcp: not serving on :$PORT — nothing to stop"
  exit 0
fi

before=$(wc -l < "$LOG" 2>/dev/null || echo 0)
echo "ghidra-mcp: requesting clean save+stop (touch $STOPREQ)"
: > "$STOPREQ"

# Wait for the port to free (server stopped)...
port_closed=0
for i in $(seq 1 90); do
  if ! ss -tln 2>/dev/null | grep -qE ":$PORT([^0-9]|$)"; then echo "ghidra-mcp: server stopped after ${i}s"; port_closed=1; break; fi
  sleep 1
done
[ "$port_closed" -eq 1 ] || { echo "WARN: still serving on :$PORT after 90s — inspect $LOG (do NOT SIGKILL; that loses the save)"; exit 1; }

# ...then wait for analyzeHeadless to report the save (commit happens during project close).
saved=0
for i in $(seq 1 45); do
  if tail -n +"$((before+1))" "$LOG" 2>/dev/null | grep -qiE 'Save succeeded for processed file'; then
    echo "ghidra-mcp: ✅ Save succeeded (committed on close) after ${i}s"; saved=1; break
  fi
  sleep 1
done
[ "$saved" -eq 1 ] || echo "WARN: did not see 'Save succeeded' in $LOG within 45s — verify before relying on the save"

echo "=== shutdown log tail ==="
tail -n +"$((before+1))" "$LOG" 2>/dev/null | grep -iE 'stop requested|server stopped|Save succeeded|FAILED|lock|read-only' | tail -10
