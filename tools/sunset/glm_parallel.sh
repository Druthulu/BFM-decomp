#!/usr/bin/env bash
# glm_parallel.sh — parallel cloud-drafting for the GLM (OpenRouter) matching tier.
#
# Splits a targets JSON into K contiguous slices and runs K concurrent api_draft.py
# workers against the same OpenRouter endpoint (GLM is latency-bound, so N concurrent
# HTTP calls ~= N× throughput; OpenRouter fans out over ~6 providers, no hard cap).
# All workers write <fn>.c + <fn>.reasoning.txt into ONE shared out dir (distinct fn
# names => no collision). The whole-binary byte-gate (gate_stage) is the sole arbiter
# afterward (G3/P9) — this script only DRAFTS.
#
# The OpenRouter key is read from .env (key `open_router_key=`) at runtime and passed
# via env to the workers only — never echoed, never written to a file.
#
# Usage: tools/glm_parallel.sh <targets.json> <out_dir> [K=6] [iters=2] [model=z-ai/glm-5.2] [maxtok=8000]
set -euo pipefail
cd "$(dirname "$0")/.."   # repo root

T="${1:?usage: glm_parallel.sh <targets.json> <out_dir> [K] [iters] [model] [maxtok]}"
OUT="${2:?out_dir required}"
K="${3:-6}"
ITERS="${4:-2}"
MODEL_ID="${5:-z-ai/glm-5.2}"
MAXTOK_V="${6:-8000}"

KEY="$(sed -n 's/^open_router_key=//p' .env | tr -d '"'\''\r ')"
[ -n "$KEY" ] || { echo "glm_parallel: no open_router_key in .env" >&2; exit 1; }

mkdir -p "$OUT"
SLICEDIR="$OUT/.slices"; rm -rf "$SLICEDIR"; mkdir -p "$SLICEDIR"

NSLICES=$(python3 - "$T" "$K" "$SLICEDIR" <<'PY'
import json, sys, math
targets = json.load(open(sys.argv[1])); K = int(sys.argv[2]); sd = sys.argv[3]
n = len(targets); per = max(1, math.ceil(n / K)); w = 0
for i in range(0, n, per):
    json.dump(targets[i:i+per], open('%s/slice_%d.json' % (sd, w), 'w')); w += 1
print(w)
PY
)
echo "glm_parallel: $T -> $NSLICES workers (iters=$ITERS, model=$MODEL_ID) -> $OUT"

pids=()
for f in "$SLICEDIR"/slice_*.json; do
  API_BASE=https://openrouter.ai/api/v1 MODEL="$MODEL_ID" API_KEY="$KEY" \
    LEAN=1 MAXTOK="$MAXTOK_V" REASON=1 TEMP=0.3 \
    .venv/bin/python tools/api_draft.py --targets "$f" --out "$OUT" --iters "$ITERS" \
    > "$OUT/$(basename "$f" .json).log" 2>&1 &
  pids+=($!)
done
echo "glm_parallel: launched ${#pids[@]} workers (pids ${pids[*]})"
fail=0
for p in "${pids[@]}"; do wait "$p" || fail=$((fail+1)); done
echo "glm_parallel: all workers done ($fail failed)"

DRAFTS=$(ls "$OUT"/*.c 2>/dev/null | wc -l)
COST=$(grep -ohE 'cost \$[0-9.]+' "$OUT"/slice_*.log 2>/dev/null | grep -oE '[0-9.]+' | paste -sd+ | bc -l 2>/dev/null || echo 0)
echo "glm_parallel: $DRAFTS drafts written; summed reported cost \$${COST:-0}"
