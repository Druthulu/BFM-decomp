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
# HTTP_TIMEOUT 700 (P31 S59) — MUST be raised WITH MAXTOK; they are one setting, not two.
# Measured on ox-alpha with a real MIPS derivation: 30 tok/s, and an UNCAPPED hard prompt ran
# 265 s for 8,067 completion tokens — i.e. it wanted to finish exactly where the old 8k cap cut it
# off, which is the nudge storm we were seeing. At 30 tok/s a full 16k generation needs ~530 s, so
# leaving the socket at 420 s would have killed the very turns the bigger budget exists to allow —
# and a timeout wastes the whole turn, where truncation at least leaves a partial.
# The ordering that must hold: generation < HTTP_TIMEOUT (700) < stallguard's wedged-agent kill
# (1200 s). 420 was itself a deliberate choice after 1800 parked a hung agent for THIRTY minutes;
# this keeps that concern (a hang costs <12 min) without strangling legitimate deep reasoning.
export HTTP_TIMEOUT=700
while [ ! -e .run/ox_campaign.stop ]; do
  .venv/bin/python tools/main_lane.py --workers 150 --batch 40 --cards 200 --max-ins 200 --maxtok 16000 2>&1
  echo "[$(date +%H:%M:%S)] [main-lane] exited; restarting in 20s"
  sleep 20
done
