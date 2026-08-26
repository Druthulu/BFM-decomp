#!/usr/bin/env bash
# THE ELASTIC LANE — spend the free-ox window when the campaign cannot (P31 S60, Drew).
#
# WHY NOT JUST ADD DRAFTING AGENTS. When req/min collapses it is almost never a shortage of agents:
# it is the drafter parked on a full gate queue. Measured 19:06 — four waves drafted at 98-99%, four
# more queued for the gater, fleet at 1 agent / 2 req/min. Adding drafters there produces more
# drafts for the same saturated gate and makes the backlog worse, not better.
#
# SO THIS SCALES THE WORK THAT IS NOT GATE-BOUND. tools/idiom_serial.py iterates locally against
# match_one (a per-function compile, no whole-binary build, no lock), gates ONE function at a time
# instead of 500, and distills what it learns into a notes file the next target reads — the
# compounding channel the 2,000-way fan-out structurally lacks. N of those cost N agents, not N*500
# drafts, and they run BESIDE a saturated gater rather than queueing behind it.
#
# THE CONTROL LOOP, every INTERVAL seconds:
#   * measure req/min over the last 5 minutes from .run/api_rate.jsonl (the same source
#     campaign_status uses) and the ready-queue depth;
#   * if the API is idle (< LOW req/min) and the queue is backed up (>= QUEUE_DEEP), the campaign is
#     gate-bound: start one more serial lane, rotating the lever, up to MAX_SERIAL;
#   * if req/min is healthy, or load is high, or MAX_SERIAL is reached, do nothing;
#   * never start one while the fleet R22 sweep is running (it wants a quiet tree).
#
# It only ever ADDS serial lanes and lets them exit on their own. It does not kill campaign lanes,
# does not touch src/ or config/, and every decision is logged with the numbers behind it.
set -u
cd /home/musashi/bfm-decomp

INTERVAL=${INTERVAL:-300}       # seconds between decisions
LOW=${LOW:-120}                 # req/min below this = the API window is going unused
QUEUE_DEEP=${QUEUE_DEEP:-3}     # ready waves at/above this = the gate is the bottleneck
MAX_SERIAL=${MAX_SERIAL:-4}     # never more than this many serial lanes at once
MAX_LOAD=${MAX_LOAD:-24}        # 32 cores; leave room for the gater
LEVERS=(extend-tell head-crack len-vein seeded-crack)

say(){ echo "[$(date +%H:%M:%S)] [elastic] $*"; }
say "up (interval ${INTERVAL}s · low<${LOW} req/min · queue>=${QUEUE_DEEP} · max ${MAX_SERIAL} serial lanes)"

i=0
while [ ! -e .run/ox_campaign.stop ]; do
  RPM=$(.venv/bin/python - <<'PY'
import json, time, collections
per = collections.Counter()
try:
    for line in open('.run/api_rate.jsonl', errors='replace'):
        line = line.strip()
        if not line: continue
        try: r = json.loads(line)
        except Exception: continue
        if str(r.get('ev')) == 'POST': per[int(r.get('t', 0) // 60)] += 1
except OSError:
    pass
m0 = int(time.time() // 60)
print(sum(per.get(m, 0) for m in range(m0 - 5, m0)) // 5)
PY
)
  QUEUE=$(ls .run/ready/ 2>/dev/null | wc -l)
  # COUNT THE PYTHON, NOT ANY SHELL THAT MENTIONS IT (P31 S60). `pgrep -f tools/idiom_serial.py`
  # matches any command line CONTAINING that string — including a monitoring shell running this
  # very check. It reported 4 running lanes when there were zero, which would have pinned this
  # loop at MAX_SERIAL forever and silently disabled it. Match the interpreter invocation.
  # `pgrep -fc ... || echo 0` emits TWO lines when there is no match (its own "0" plus the
  # fallback), so RUNNING became "0\n0", the -ge test errored, bash treated the failed test as
  # FALSE, and the MAX_SERIAL cap silently stopped existing — an unbounded-spawn bug in a loop
  # meant to run unattended. `| wc -l` always prints exactly one integer.
  RUNNING=$(pgrep -f "[.]venv/bin/python tools/idiom_serial.py" 2>/dev/null | wc -l)
  LOAD=$(cut -d' ' -f1 /proc/loadavg | cut -d. -f1)

  if [ "$RPM" -ge "$LOW" ]; then
    say "req/min ${RPM} >= ${LOW} — the window is being used, nothing to add"
  elif [ "$QUEUE" -lt "$QUEUE_DEEP" ]; then
    say "req/min ${RPM} low but queue only ${QUEUE} deep — the drafter is not blocked; leaving it"
  elif [ "$RUNNING" -ge "$MAX_SERIAL" ]; then
    say "req/min ${RPM} · queue ${QUEUE} · already ${RUNNING}/${MAX_SERIAL} serial lanes up"
  elif [ "$LOAD" -ge "$MAX_LOAD" ]; then
    say "req/min ${RPM} · queue ${QUEUE} · load ${LOAD} >= ${MAX_LOAD} — CPU busy, not adding"
  elif pgrep -f "make check-all" >/dev/null; then
    say "fleet R22 sweep in flight — not adding a lane"
  else
    LEV=${LEVERS[$(( i % ${#LEVERS[@]} ))]}
    i=$(( i + 1 ))
    LOG=".run/elastic_${LEV}_$(date +%H%M%S).log"
    say "GATE-BOUND (req/min ${RPM} · queue ${QUEUE} · ${RUNNING} serial up) — starting a serial lane on ${LEV} -> ${LOG}"
    setsid nohup .venv/bin/python tools/idiom_serial.py --lever "$LEV" --n 4 --min-ins 60 \
        --max-turns 60 > "$LOG" 2>&1 &
    disown
  fi
  sleep "$INTERVAL"
done
say "campaign stopped — elastic lane exiting"
