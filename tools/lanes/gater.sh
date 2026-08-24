#!/usr/bin/env bash
# The restartable lane. Kill and relaunch this freely — drafting is unaffected.
set -u
cd /home/musashi/bfm-decomp
while [ ! -e .run/ox_campaign.stop ]; do
  .venv/bin/python tools/ox_campaign.py --gater --gate-jobs 12 2>&1
  echo "[$(date +%H:%M:%S)] [gater] exited; restarting in 20s"
  sleep 20
done
