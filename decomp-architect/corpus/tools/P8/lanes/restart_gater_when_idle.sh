#!/usr/bin/env bash
# Restart the gater SHELL once the current gate finishes, so a --gate-jobs change lands without
# killing a sweep mid-flight. bash parses the lane's while-loop up front, so an arg change needs a
# fresh shell (docs/accelerators.md #5); the gater is the lane that IS safe to restart — unlike the
# drafter, nothing is lost but the pause between gates.
set -u
cd /home/musashi/bfm-decomp
DEADLINE=$(( $(date +%s) + 7200 ))
say(){ echo "[$(date +%H:%M:%S)] [gater-restart] $*"; }
say "waiting for the in-flight gate to finish"
while pgrep -f 'tools/sweep_parallel' >/dev/null || pgrep -f 'tools/gate_stage' >/dev/null; do
  [ "$(date +%s)" -ge "$DEADLINE" ] && { say "2h deadline — NOT restarting"; exit 1; }
  sleep 10
done
say "gate idle; restarting the gater shell with the new job count"
pkill -f 'bash .run/gater.sh' 2>/dev/null || true
pkill -f 'ox_campaign.py --gater' 2>/dev/null || true
sleep 3
setsid nohup .run/gater.sh >> .run/gater.log 2>&1 < /dev/null &
sleep 15
pgrep -f 'ox_campaign.py --gater' >/dev/null && say "gater back up: $(tr '\0' ' ' < /proc/$(pgrep -f 'ox_campaign.py --gater' | head -1)/cmdline)" || say "WARNING: gater did not come back"
