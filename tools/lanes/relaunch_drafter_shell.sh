#!/usr/bin/env bash
# Wait for the in-flight wave to QUEUE, then restart the drafter SHELL (not just its python).
#
# WHY THE SHELL. bash parses a `while … done` compound command in full before executing it, so the
# loop body — including the python command line — is fixed in memory for the life of that shell.
# Editing .run/drafter.sh, or bouncing only the python, therefore re-runs the OLD arguments: at
# 11:02 the bounced python came back on the pre-S59 lane/band list even though the file on disk had
# been updated 18 minutes earlier (it logged `lane tells, band (5, 2000)`, which only the old list
# produces at rotation index 36). A lane-ARG change needs a fresh shell; only a lane-CODE change
# (tools/*.py) is picked up by a python bounce.
#
# Cost is one shell exec, taken at the moment a wave has just queued, so no drafts are lost.
set -u
cd /home/musashi/bfm-decomp
# WATCH BY NAME, NOT BY COUNT. The queue is two-sided: the gater CONSUMES markers while the drafter
# produces them, so "the count went up" is not "a wave queued". The first version latched BEFORE=1,
# the gater consumed that marker, and the next wave queuing took the count back to 1 — not greater
# than 1 — so it would have waited out its whole deadline while the thing it waits for happened.
# The condition was true about a number and false about the world.
BEFORE=" $(ls .run/ready/ 2>/dev/null | tr '\n' ' ')"
DEADLINE=$(( $(date +%s) + 5400 ))
say(){ echo "[$(date +%H:%M:%S)] [relaunch] $*"; }
say "waiting for a ready marker not in:$BEFORE (5s poll — the running python still carries the PAID lane)"
new_marker(){
  for m in $(ls .run/ready/ 2>/dev/null); do
    case "$BEFORE" in *" $m "*) ;; *) return 0;; esac
  done
  return 1
}
while ! new_marker; do
  [ "$(date +%s)" -ge "$DEADLINE" ] && { say "deadline passed — NOT restarting"; exit 1; }
  [ -e .run/ox_campaign.stop ] && { say "campaign stopped"; exit 0; }
  sleep 5
done
say "a wave queued; restarting the drafter shell"
pkill -f 'bash .run/drafter.sh' 2>/dev/null || true
pkill -f 'ox_campaign.py --drafter' 2>/dev/null || true
sleep 3
setsid nohup .run/drafter.sh >> .run/drafter.log 2>&1 < /dev/null &
sleep 20
say "new rotation line:"; grep 'resuming rotation' .run/drafter.log | tail -1
