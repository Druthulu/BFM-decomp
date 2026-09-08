#!/usr/bin/env bash
set -u
cd /home/musashi/bfm-decomp
KEY=$(grep -m1 '^open_router_key=' .env | cut -d= -f2-)
export API_BASE=https://openrouter.ai/api/v1 API_KEY="$KEY" MODEL=stealth/ox-alpha MAXTOK=16000 MAX_429=10
# A TOOLING-DESIGN brief must read the build config and the tool sources; a decompilation
# brief must not. Granted only for this task, via EXTRA_READABLE.
export EXTRA_READABLE='config,tools,Makefile'
.venv/bin/python -u tools/api_agent.py --targets .run/bakeoff/toolwork/t_jtbl.json \
  --brief .run/bakeoff/toolwork/brief_jtbl.txt --out .run/bakeoff/toolwork/out_jtbl \
  --max-turns 50 --max-cost 2.0 > .run/bakeoff/toolwork/jtbl.log 2>&1 &
.venv/bin/python -u tools/api_agent.py --targets .run/bakeoff/toolwork/t_o0cc1.json \
  --brief .run/bakeoff/toolwork/brief_o0cc1.txt --out .run/bakeoff/toolwork/out_o0cc1 \
  --max-turns 50 --max-cost 2.0 > .run/bakeoff/toolwork/o0cc1.log 2>&1 &
wait
echo "TOOLWORK ANALYSIS DONE"
