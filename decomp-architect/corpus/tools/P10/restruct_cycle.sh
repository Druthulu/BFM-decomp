#!/usr/bin/env bash
# restruct_cycle.sh — the Phase-37 batch cycle, mechanised (T3; cloned from tools/delever_cycle.sh). For each batch k in [START..END]:
#   1. the tree must be clean (src/ + config/); the oracle's calibration is refreshed (it is keyed to HEAD: every commit stales it) and the
#      snapshot baseline is refreshed after a green fleet run (the GUARD refuses an object that does not reproduce, R56/R112);
#   2. `restruct.py --apply --rung R --batch N --label <mode>k` judges every unit of the next N files and leaves the winning texts in place;
#      the tool's exit code and its `final X/X identical` are read (R97/R66);
#   3. the outer gate: the CLEAN fleet run (make clean && extract-all && check-all -> `218 passed, 0 failed of 218`, R22);
#   4. the type census is rerun (the readability series' snapshot reads it), the phase log gets the batch's entry, the 🛑 headline is
#      refreshed (R101), and src/ + the ledger/batch record/log + the census + the phase log are committed (R42).
# Stops on the first red (a non-zero tool exit, a final N/M with N != M, a fleet run that is not 218/218) — the batch's files are then
# still in place: inspect, then `tools/restruct.py --restore` (never git checkout, R102). Stops cleanly when nothing is drawable.
# Usage: [LABEL_PREFIX=t4_] [TASK=T4] [REDRAW="DECL-KEPT"] [CENSUS=0] tools/restruct_cycle.sh START END [BATCH=50] [RUNG=D|S|L] [ONLY="alias1 alias2 …"] [HEADERS=1]
#   RUN IT DETACHED from the Claude Code harness (R115 — its low-memory guard kills a long BACKGROUND task; a SIGKILL skips a restore):
#     setsid nohup bash -c 'TASK=T4 tools/restruct_cycle.sh 1 8 50 D; echo "cycle exit=$?"' > .run/P37/restruct/cycle_<x>.log 2>&1 &
#   and watch the log (`until grep -q 'cycle exit=' <log>; do sleep 60; done`). A killed batch: `tools/restruct.py --restore`.
#   size a call so one batch stays < 10 min: a D unit ≈ 0.15 s per compile (~n+2 compiles per TU on a DIFFERS ladder); an S body ≈ 2 s;
#   a header ≈ 35 s per judgement (every includer) — headers in small batches.
set -o pipefail
cd "$(dirname "$0")/.." || exit 2
START=$1; END=$2; BATCH=${3:-50}; RUNG=${4:-D}; ONLY=${5:-}
[ -n "$START" ] && [ -n "$END" ] || { echo "usage: $0 START END [BATCH] [D|S|L] [ONLY]"; exit 2; }
case "$RUNG" in D|S|L) ;; *) echo "RUNG must be D, S or L"; exit 2;; esac
ONLYFLAG=""; [ -n "$ONLY" ] && ONLYFLAG="--only $ONLY"
REDRAWFLAG=""; [ -n "${REDRAW:-}" ] && REDRAWFLAG="--redraw $REDRAW"
HFLAG=""; [ -n "${HEADERS:-}" ] && HFLAG="--headers"
FLEET=$(ls config/check.*.sha | wc -l)
PY=.venv/bin/python
MARKER='## 🛑 SESSION CHECKPOINT'
mkdir -p .run/P37/restruct .run/P37/baseline
for k in $(seq "$START" "$END"); do
  label="${LABEL_PREFIX:-}${RUNG}${k}"
  log=.run/P37/restruct/run_${label}.log
  r22=.run/P37/baseline/r22_${label}.log
  [ -z "$(git status --short -- src config)" ] || { echo "cycle: src/ or config/ is dirty — commit, or tools/restruct.py --restore (R42/R102)"; exit 3; }
  [ -z "$(git status --short --porcelain src | grep '^??')" ] || { echo "cycle: untracked files under src/ — sweep them first"; exit 3; }
  $PY tools/delever_oracle.py --status >/dev/null 2>&1 || {
    $PY tools/delever_oracle.py --snapshot-baseline > .run/P37/restruct/snapshot_${label}.log 2>&1 || { echo "cycle: the snapshot refresh FAILED/REFUSED"; tail -4 .run/P37/restruct/snapshot_${label}.log; exit 1; }
    grep -q 'REFUSED' .run/P37/restruct/snapshot_${label}.log && { echo "cycle: the snapshot refresh was REFUSED (build/ is not the tree's — run the clean fleet gate first)"; exit 1; }
    $PY tools/delever_oracle.py --calibrate ov_SC04_011 ov_SC03_015 md_SC07_004 main -j 16 > .run/P37/restruct/calibrate_${label}.log 2>&1 \
      || { echo "cycle: calibration FAILED"; tail -5 .run/P37/restruct/calibrate_${label}.log; exit 1; }
  }
  { /usr/bin/time -f "$label wall=%e s" $PY tools/restruct.py --apply --rung "$RUNG" --batch "$BATCH" --label "$label" $HFLAG $ONLYFLAG $REDRAWFLAG -j 12; echo "exit=$?"; } > "$log" 2>&1
  grep -q '^exit=0$' "$log" || { echo "cycle: batch $label — restruct exited non-zero"; tail -4 "$log"; exit 1; }
  if grep -qE 'nothing to do' "$log"; then echo "cycle: nothing drawable at $label — done"; exit 0; fi
  vline=$(grep -oE "restruct: batch .*" "$log" | tail -1)
  [ -n "$vline" ] || { echo "cycle: batch $label — no verify line in $log (R32: an empty line is not a pass)"; tail -3 "$log"; exit 1; }
  final=$(echo "$vline" | grep -oE 'final [0-9]+/[0-9]+' | grep -oE '[0-9]+/[0-9]+')
  [ -n "$final" ] && [ "${final%/*}" = "${final#*/}" ] || { echo "cycle: batch $label — $vline"; exit 1; }
  if [ "$(echo "$vline" | grep -oE 'written [0-9]+' | grep -oE '[0-9]+')" = "0" ]; then echo "cycle: batch $label wrote no file — $vline"; fi
  { /usr/bin/time -f "wall=%e s user=%U s sys=%S s" bash -c 'set -o pipefail; make clean && make extract-all JOBS=16 && make check-all JOBS=16'; echo "exit=$?"; } > "$r22" 2>&1
  line=$(grep -oE "check-all: [0-9]+ passed, [0-9]+ failed of [0-9]+" "$r22")
  if ! grep -q '^exit=0$' "$r22" || [ "$line" != "check-all: $FLEET passed, 0 failed of $FLEET" ]; then echo "cycle: R22 RED after batch $label — $line (the batch's files are in place: inspect, then tools/restruct.py --restore)"; exit 1; fi
  cline="(census skipped)"
  if [ "${CENSUS:-1}" != "0" ]; then
    $PY tools/type_census.py -j 16 --sites > .run/P37/census/census_${label}.log 2>&1 || { echo "cycle: the type census FAILED after batch $label"; tail -3 .run/P37/census/census_${label}.log; exit 1; }
    cline=$(grep -oE "^type_census: .*" .run/P37/census/type_census.txt | tail -1)
    [ -n "$cline" ] || { echo "cycle: the census table carries no type_census line after batch $label"; exit 1; }
    $PY tools/readability_progress.py --snapshot "$label" > /dev/null 2>&1 || echo "cycle: readability snapshot refused (a stale census?) — continuing"
  fi
  TASK=${TASK:-T4} $PY - "$label" "$vline" "$line" "$cline" "$(grep -oE 'wall=[0-9.]+ s' "$r22" | head -1)" "$MARKER" <<'PYEOF' || exit 1
import os, pathlib, re, sys, time, subprocess
label, vline, r22line, cline, wall, marker = sys.argv[1:7]
task = os.environ.get("TASK", "T4")
p = pathlib.Path("phase-ends/CURRENT_PHASE.md"); t = p.read_text()
head = subprocess.run(["git", "rev-parse", "--short", "HEAD"], capture_output=True, text=True).stdout.strip()
entry = (f"\n- **{time.strftime('%Y-%m-%d')} — {task} batch `{label}`** (`.run/P37/restruct/run_{label}.log`, `batch_{label}.json`): `{vline}` → R22 "
         f"(`.run/P37/baseline/r22_{label}.log`) **`{r22line}`** (`{wall}`) → census `{cline}`.")
assert ("\n" + marker) in t, "phase log marker (the checkpoint heading) not found"
t = t.replace("\n" + marker, entry + "\n\n" + marker, 1)
lines = t.split("\n")
for i, l in enumerate(lines):
    if l.startswith("## 🛑 SESSION CHECKPOINT"):
        base = re.sub(r"\s*\|\s*last batch.*$", "", l)
        lines[i] = f"{base} | last batch `{label}` on {head}: {vline.split(' — ', 1)[-1][:160]}"
        break
p.write_text("\n".join(lines))
print("log:", label)
PYEOF
  for i in 1 2 3 4 5 6; do
    [ -e .git/index.lock ] || break
    if [ -z "$(ps -eo cmd | grep -E '^git |/git ' | grep -v grep)" ]; then echo "cycle: stale .git/index.lock (no git process) — removed"; rm -f .git/index.lock; break; fi
    sleep 10
  done
  git add -A src && git add .run/P37/restruct .run/P37/census .run/P37/baseline phase-ends/CURRENT_PHASE.md docs/readability.md docs/readability-progress.tsv 2>/dev/null; git add .run/P36/delever/calibration.json 2>/dev/null
  git commit -q -m "src(phase-37): ${TASK:-T4} batch $label — $vline | R22 $line | $cline (restruct_cycle)" || exit 1
  echo "cycle: batch $label committed $(git log --oneline -1 | cut -c1-9) — $vline | $line"
done
echo "cycle: batches $START..$END done"
