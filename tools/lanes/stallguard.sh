#!/usr/bin/env bash
# Automatic stall detection and repair. Runs every 60s, costs nothing, works at 3am.
#
# Each rule fires on a MEASURED condition, not a guess, and logs what it did so the morning
# ledger shows whether the night was healthy or held together with tape.
set -u
cd /home/musashi/bfm-decomp
say(){ echo "[$(date +%H:%M:%S)] [stallguard] $*"; }

while [ ! -e .run/ox_campaign.stop ]; do
  # 1. A LANE'S SHELL DIED. Each lane's own while-loop restarts its python, but nothing restarts
  #    the shell. Without this, one crash silently ends that lane for the night.
  for lane in drafter gater maintenance; do
    if ! pgrep -f "bash .run/$lane.sh" >/dev/null; then
      say "$lane shell is gone — relaunching"
      setsid nohup ".run/$lane.sh" >> ".run/$lane.log" 2>&1 < /dev/null
      sleep 2
    fi
  done

  # 2. AGENTS HUNG PAST THE SOCKET TIMEOUT. HTTP_TIMEOUT is 420s and the retry loop treats a
  #    timeout as transient, so an agent silent for >20 min is not waiting on the API — it is
  #    wedged. Its shard's remaining targets are lost, which is cheaper than a wedged worker
  #    holding a slot all night. (Measured P31 S58: one agent sat 1,690s silent.)
  .venv/bin/python - <<'PY'
import json,os,subprocess,time
live={int(p) for p in subprocess.run(
    ['bash','-c','pgrep -f "^\\.venv/bin/python -u tools/api_agent" || true'],
    capture_output=True,text=True).stdout.split()}
if live:
    last={}
    try:
        for l in open('.run/api_rate.jsonl'):
            l=l.strip()
            if not l: continue
            try: r=json.loads(l)
            except Exception: continue
            if r.get('ev')=='POST': last[r.get('pid')]=r.get('t',0)
    except OSError: pass
    now=time.time(); killed=0
    for p in live:
        if p in last and now-last[p] > 1200:
            try: os.kill(p,15); killed+=1
            except OSError: pass
    if killed: print(f'  killed {killed} wedged agent(s) (>20 min since last request)')
PY

  # 3. A GATE RUNNING TOO LONG. main is parked off the critical path now, so any gate_main here is
  #    a leftover; and a sweep past 90 min is wedged rather than slow.
  for pat in gate_main sweep_parallel; do
    for pid in $(pgrep -f "tools/$pat" 2>/dev/null || true); do
      age=$(ps -o etimes= -p "$pid" 2>/dev/null | tr -d ' ')
      [ -n "${age:-}" ] && [ "$age" -gt 5400 ] && { say "$pat pid $pid running ${age}s — killing"; kill "$pid" 2>/dev/null; }
    done
  done

  # 4. DRAFTING IDLE WHILE WORK EXISTS. Zero agents for 3 consecutive checks with the drafter alive
  #    means it is stuck between waves; bounce its python and let the while-loop restart it.
  if [ "$(pgrep -cf '^\.venv/bin/python -u tools/api_agent')" = "0" ]; then
    IDLE=$(( ${IDLE:-0} + 1 ))
    if [ "$IDLE" -ge 3 ]; then
      say "no drafting agents for 3 checks — bouncing the drafter's python"
      pkill -f 'ox_campaign.py --drafter' 2>/dev/null || true
      IDLE=0
    fi
  else
    IDLE=0
  fi
  sleep 60
done
