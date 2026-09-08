#!/bin/bash
# auto_supervisor.sh — keep an LLM-free driver alive across crashes until it exits cleanly
# or a safe-exit is requested. The unattended-run babysitter (Phase 16; Phase 21 grinder).
#
# DRIVER (env, default tools/auto_driver.py) selects the driver — Phase 21 grinds with
#   DRIVER=tools/grinder.py.  All args after the script name pass through to the driver.
#
# Launch detached (survives the shell/session, the ghidra_mcp_start.sh idiom):
#   cd ~/bfm-decomp && DRIVER=tools/grinder.py setsid nohup bash tools/auto_supervisor.sh \
#       --permute-secs 120 -j 14 >/dev/null 2>&1 & disown
#
# Safe exit:  touch .run/auto/STOP   (or tools/auto_stop.sh)  -> driver finishes current fn,
#             commits, exits; supervisor sees STOP and does NOT relaunch.
# Status:     tools/auto_status.sh
set -u
REPO="$(cd "$(dirname "$0")/.." && pwd)"; cd "$REPO"
AUTODIR=".run/auto"; STOP="$AUTODIR/STOP"; LOG="$AUTODIR/supervisor.log"; LOCK="$AUTODIR/supervisor.lock"
mkdir -p "$AUTODIR"
exec 9>"$LOCK"; flock -n 9 || { echo "supervisor already running"; exit 0; }
say(){ echo "[$(date '+%F %T')] $*" | tee -a "$LOG"; }
say "supervisor start (pid $$)"
# the run is build-only — stop the Ghidra MCP to free the .rep lock + RAM
bash tools/ghidra_mcp_stop.sh >/dev/null 2>&1 || true
backoff=5
while true; do
  if [ -f "$STOP" ]; then say "STOP present — not launching; exiting"; break; fi
  say "launching ${DRIVER:-tools/auto_driver.py}"
  .venv/bin/python "${DRIVER:-tools/auto_driver.py}" "$@" >> "$AUTODIR/driver.log" 2>&1
  rc=$?
  # reap leaked permuter workers + clean stale permuter output dirs (WSL2 leak guard + disk)
  pkill -f 'decomp-permuter/permuter.py' 2>/dev/null || true
  find "$AUTODIR" .run/permuter -maxdepth 3 -type d -name 'output-*' -mmin +120 -exec rm -rf {} + 2>/dev/null || true
  if [ -f "$STOP" ]; then say "driver exited rc=$rc with STOP — clean stop"; break; fi
  if [ "$rc" -eq 0 ]; then say "driver exited rc=0 (worklist dry/done) — exiting"; break; fi
  say "driver crashed rc=$rc — relaunch in ${backoff}s (committed state = nothing lost)"; sleep "$backoff"
  backoff=$(( backoff < 120 ? backoff*2 : 120 ))
done
say "supervisor done"
