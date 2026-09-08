#!/usr/bin/env bash
# Restart the MAIN lane's shell at a safe boundary, so an env/arg change (MAXTOK, HTTP_TIMEOUT)
# takes effect without throwing away work. bash fixes a lane's command line when it parses the
# loop, so only a fresh SHELL picks these up (docs/accelerators.md #5).
#
# The safe boundary is: no main-lane drafting agents alive AND no gate_main running — i.e. the lane
# is between its gate and its next draw. Restarting during the draw would only cost a re-draw;
# restarting mid-draft would discard drafted work, and mid-gate would abort a batch (gate_main
# reverts its own substitution, so that is safe but wasteful).
set -u
cd /home/musashi/bfm-decomp
DEADLINE=$(( $(date +%s) + 7200 ))
say(){ echo "[$(date +%H:%M:%S)] [main-restart] $*"; }
say "waiting for the main lane to be between gate and draw"
while :; do
  agents=$(pgrep -f 'tools/api_agent' 2>/dev/null | while read -r p; do
             tr '\0' ' ' < "/proc/$p/cmdline" 2>/dev/null | grep -q 'wave_m' && echo x; done | wc -l)
  gate=$(pgrep -cf 'tools/gate_main' 2>/dev/null || true)
  [ "${agents:-0}" -eq 0 ] && [ "${gate:-0}" -eq 0 ] && break
  [ "$(date +%s)" -ge "$DEADLINE" ] && { say "2h deadline — NOT restarting"; exit 1; }
  [ -e .run/ox_campaign.stop ] && { say "campaign stopped"; exit 0; }
  sleep 20
done
say "idle boundary reached; restarting the main lane shell"
for p in $(pgrep -f '^bash \.run/main\.sh'); do kill "$p"; done
for p in $(pgrep -f '^\.venv/bin/python tools/main_lane\.py'); do kill "$p"; done
sleep 3
setsid nohup .run/main.sh >> .run/main_lane.log 2>&1 < /dev/null &
sleep 15
pgrep -f '^bash \.run/main\.sh' >/dev/null && say "main lane back up with the new config" || say "WARNING: it did not come back"
