#!/usr/bin/env bash
# The restartable lane. Kill and relaunch this freely — drafting is unaffected.
set -u
cd /home/musashi/bfm-decomp
while [ ! -e .run/ox_campaign.stop ]; do
  # GATE JOBS 24 (P31 S59, Drew approved the CPU). Each job is one whole-binary rebuild and the box
  # is 32 cores running at ~6% (load 3.1, 211% of 3200%) with 39 GB free — 12 was leaving the machine
  # idle. It matters now because the tells and jtbl QUOTAS deliberately pull cards from binaries
  # outside the ranked gate groups: a measured draw went from ~24 groups to 63, i.e. 63 rebuilds per
  # wave, and at 12 jobs that is five serial batches. Raise this with the quota sizes, not on its own.
  .venv/bin/python tools/ox_campaign.py --gater --gate-jobs 32 2>&1
  echo "[$(date +%H:%M:%S)] [gater] exited; restarting in 20s"
  sleep 20
done
