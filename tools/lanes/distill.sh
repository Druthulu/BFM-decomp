#!/usr/bin/env bash
# THE DISTILL LANE — the second half of the flywheel, running BESIDE drafting, never in front of it.
#
# The gater already harvests every wave before the next cards are drawn (idiom_harvest.py, Drew's
# 2026-08-23 rule) and writes .run/idiom_candidates.<tag>.md. That is EXTRACTION. What actually
# changes the next wave's behaviour is the COOKBOOK, because that is what the drafting agents grep —
# and distillation was batched per session, so the ore piled up: 165 novel candidates across four
# waves within three hours of the last cookbook update (P31 S59).
#
# This lane does the zero-token half: watch for new candidate rows, and when a batch is worth a
# reviewer's turn raise a READY marker naming the waves. A human + subagent then distills, lands the
# sections, and records the mined count. Nothing here writes the cookbook, src/ or config/ — a bad
# harvest can never pollute the knowledge base on its own.
#
# It never blocks a draw. Wave N's ore is distilled while wave N+1 drafts, so wave N+2 is the first
# that can grep it; stopping the drafter to think cost 139 of 162 idle minutes on 2026-08-23.
set -u
cd /home/musashi/bfm-decomp
STATE=.run/distill_state.json
READY_DIR=.run/distill_ready
MIN_NOVEL=${MIN_NOVEL:-30}          # a batch worth a reviewer's turn
MIN_WAVES=${MIN_WAVES:-2}
mkdir -p "$READY_DIR"
say(){ echo "[$(date +%H:%M:%S)] [distill] $*"; }
say "lane up (threshold: >=$MIN_NOVEL novel candidates or >=$MIN_WAVES waves)"

while [ ! -e .run/ox_campaign.stop ]; do
  .venv/bin/python tools/distill_scan.py "$STATE" "$READY_DIR" "$MIN_NOVEL" "$MIN_WAVES"
  sleep 300
done
