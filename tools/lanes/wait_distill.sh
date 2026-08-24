#!/usr/bin/env bash
# Blocks until the distill lane raises the NEXT batch, then exits — the harness re-invokes the main
# loop on completion, so this is a self-reminder without polling (no sleep-then-tail loops).
set -u
cd /home/musashi/bfm-decomp
DEADLINE=$(( $(date +%s) + 10800 ))          # 3h, then report back regardless
while [ -z "$(ls .run/distill_ready/*.json 2>/dev/null)" ]; do
  [ "$(date +%s)" -ge "$DEADLINE" ] && { echo "[wait_distill] 3h with no new batch — lane may be idle"; exit 0; }
  [ -e .run/ox_campaign.stop ] && { echo "[wait_distill] campaign stopped"; exit 0; }
  sleep 60
done
echo "[wait_distill] BATCH READY: $(ls .run/distill_ready/*.json)"
.venv/bin/python -c "
import json,glob
for p in glob.glob('.run/distill_ready/*.json'):
    d=json.load(open(p)); print(f\"  waves {' '.join(d['waves'])} · {d['novel']} novel candidates\")"
