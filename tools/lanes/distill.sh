#!/usr/bin/env bash
# THE DISTILL LANE — the second half of the flywheel, running BESIDE drafting, never in front of it.
#
# The gater already harvests every wave before the next cards are drawn (idiom_harvest.py, Drew's
# 2026-08-23 rule) and writes .run/idiom_candidates.<tag>.md. That is EXTRACTION. What actually
# changes the next wave's behaviour is the COOKBOOK, because that is what the drafting agents grep —
# and distillation was batched per session, so the ore piled up: 172 novel candidates had
# accumulated within three hours of the last cookbook update (P31 S59).
#
# This lane does the zero-token half: it watches for new candidate files, counts the novel rows,
# and when a batch is worth a reviewer's time it writes a READY marker naming the waves. A human +
# subagent then distills and lands the sections (Drew, S59: "that should be us with a subagent each
# time it's needed"). Nothing here writes the cookbook, src/ or config/ — a bad harvest can never
# pollute the knowledge base on its own.
#
# It also never blocks a draw. Stopping the drafter to think cost 139 of 162 idle minutes on
# 2026-08-23; wave N's ore is distilled while wave N+1 drafts, and wave N+2 is the first to grep it.
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
  .venv/bin/python - "$STATE" "$READY_DIR" "$MIN_NOVEL" "$MIN_WAVES" <<'PY'
import glob, json, os, re, sys, time
state_p, ready_dir, min_novel, min_waves = sys.argv[1], sys.argv[2], int(sys.argv[3]), int(sys.argv[4])
try:
    st = json.load(open(state_p))
except Exception:
    st = {"done": [], "queued": []}
seen = set(st.get("done", [])) | set(st.get("queued", []))

NOVEL = re.compile(r"\*\*(\d+) novel-idiom candidates\*\*")
pend = []
for p in sorted(glob.glob(".run/idiom_candidates.*.md")):
    tag = os.path.basename(p).split(".")[1]
    if tag in seen or tag == "ALL":
        continue
    m = NOVEL.search(open(p, errors="replace").read(4000))
    n = int(m.group(1)) if m else 0
    if n:                                   # a wave with zero novel rows is nothing to review
        pend.append((tag, n, p))
    else:
        st.setdefault("done", []).append(tag)     # nothing to mine; close it out

tot = sum(n for _t, n, _p in pend)
if pend and (tot >= min_novel or len(pend) >= min_waves):
    batch = "".join(t for t, _n, _p in pend)[:24]
    out = os.path.join(ready_dir, f"{batch}.json")
    json.dump({"waves": [t for t, _n, _p in pend],
               "novel": tot,
               "files": [p for _t, _n, p in pend],
               "t": time.time()}, open(out, "w"), indent=1)
    st.setdefault("queued", []).extend(t for t, _n, _p in pend)
    print(f"  BATCH READY: {len(pend)} wave(s) / {tot} novel candidates -> {out}")
elif pend:
    print(f"  accumulating: {len(pend)} wave(s) / {tot} novel candidates "
          f"(need {min_novel} or {min_waves} waves)")
json.dump(st, open(state_p, "w"), indent=1)
PY
  sleep 300
done
