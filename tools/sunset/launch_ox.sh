#!/usr/bin/env bash
# S58 ox campaign launcher.  usage: launch_ox.sh <wave-tag> <n-shards>
set -u
cd /home/musashi/bfm-decomp
TAG=${1:-ab}; N=${2:-12}
KEY=$(grep -m1 '^open_router_key=' .env | cut -d= -f2-)
export API_BASE=https://openrouter.ai/api/v1
export API_KEY="$KEY"
export MODEL=stealth/ox-alpha
# MAXTOK: api_draft's default is 512 — an output cap sized for a LOCAL model. A reasoning
# model asked to emit a whole C function truncates every time: measured 348 of 918 turns in
# waves AB/AC came back finish=length, and those runs reported 'no compiling draft after 0
# oracle calls' — a harness verdict wearing a model's name (R40). 8000 fits a 50-ins function
# with room for the reasoning preamble.
export MAXTOK=8000
export MAX_429=10   # ride out provider bursts: ~14 min of backoff before a call is abandoned
mkdir -p .run/wave_$TAG
for ((i=0;i<N;i++)); do
  .venv/bin/python -u tools/api_agent.py \
      --targets .run/wave_${TAG}_targets.$i.json \
      --cards   .run/wave_${TAG}_cards.json \
      --out     .run/wave_$TAG/shard$i \
      --max-turns 24 --max-cost 1.0 --max-cost-per-fn 0.15 \
      > .run/wave_$TAG/shard$i.log 2>&1 &
done
wait
echo "WAVE $TAG: ALL $N SHARDS DONE"
