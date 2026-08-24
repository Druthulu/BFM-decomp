#!/usr/bin/env bash
# One-shot: wait until the IN-FLIGHT wave has queued its drafts, then bounce the drafter's PYTHON
# (not its shell) so it re-execs from .run/drafter.sh and picks up the S59 lane/band pinning.
#
# Why not just restart it now: the running process still carries the pre-S59 args, and killing it
# mid-wave throws away every draft the fleet has produced for that wave. Waiting for the ready
# marker costs nothing and loses nothing. The drafter SHELL is never touched — its while-loop is
# what relaunches the python, and that is the lane that must never stop.
set -u
cd /home/musashi/bfm-decomp
WAVE="${1:?wave tag, e.g. bi}"
DEADLINE=$(( $(date +%s) + 5400 ))          # give up after 90 min rather than linger for days
say(){ echo "[$(date +%H:%M:%S)] [bounce] $*"; }
say "waiting for .run/ready/$WAVE.json"
while [ ! -e ".run/ready/$WAVE.json" ]; do
  [ "$(date +%s)" -ge "$DEADLINE" ] && { say "deadline passed with $WAVE still drafting — NOT bouncing"; exit 1; }
  [ -e .run/ox_campaign.stop ] && { say "campaign stopped — nothing to bounce"; exit 0; }
  sleep 30
done
say "$WAVE queued; bouncing the drafter python"
pkill -f 'ox_campaign.py --drafter' 2>/dev/null || true
sleep 25
if pgrep -f 'ox_campaign.py --drafter' >/dev/null; then
  say "relaunched — new rotation:"
  grep -m1 'resuming rotation' <(tail -40 .run/drafter.log) || tail -3 .run/drafter.log
else
  say "WARNING: no drafter python after 25s — check .run/drafter.log and the drafter shell"
fi
