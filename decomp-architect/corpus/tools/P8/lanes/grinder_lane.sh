#!/usr/bin/env bash
# THE PERMUTER LANE (P31 S60, Drew). tools/grinder.py has existed since Phase 21 and has never run
# this campaign, while 5,388 backlog rows sit at closeness <= 2 — functions one or two instructions
# from byte-exact, with no consumer. It is LLM-FREE and CPU-bound, so it runs BESIDE a saturated
# gater instead of queueing behind it, and it banks through the same gate_stage (G3/P9 sole arbiter).
# --max-closeness 6 targets the near pile first; -j 10 leaves cores for the gater and serial lanes.
set -u
cd /home/musashi/bfm-decomp
say(){ echo "[$(date +%H:%M:%S)] [grinder-lane] $*"; }
while [ ! -e .run/ox_campaign.stop ] && [ ! -e .run/auto/STOP ]; do
  say "starting a grinder pass"
  .venv/bin/python tools/grinder.py --permute-secs 120 -j 10 --batch 10 \
      --max-closeness 6 --max-nins 220 --idle-secs 120 2>&1 | tail -40
  say "grinder exited; restarting in 60s"
  sleep 60
done
say "stopped"
