#!/usr/bin/env bash
# THE MAIN LANE — the EXE's own drafting+gating cadence, beside the overlay lanes.
#
# main is excluded from every overlay wave draw because its gate is a clean whole-EXE rebuild that
# bisects on failure, and on the overlay critical path that cost three measured stalls. The result
# was that main had no lane at all: 1,713 open stubs and no cadence, while the overlay lane ran at
# roughly a quarter of the API ceiling because CARD SUPPLY is its constraint, not throughput.
#
# Safe to kill and restart, like the gater: gate_main holds .run/auto/gate.main.lock (blocking) and
# reverts its own substitution if it dies, so the worst a restart costs is one batch's gate time.
#
# It works the .run/main_queue backlog FIRST (drafts the overlay waves produced before main was
# excluded — already drafted, never gated, free), then draws and drafts its own main cards.
set -u
cd /home/musashi/bfm-decomp
while [ ! -e .run/ox_campaign.stop ]; do
  .venv/bin/python tools/main_lane.py --workers 150 --batch 40 --cards 200 --max-ins 200 --maxtok 16000 2>&1
  echo "[$(date +%H:%M:%S)] [main-lane] exited; restarting in 20s"
  sleep 20
done
