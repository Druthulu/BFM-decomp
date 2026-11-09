#!/usr/bin/env bash
# share_body_cycle.sh — the T5 batch cycle for bucket `new`, mechanised (Phase 35): for each batch k in [START..END]:
#   run `share_body.py --apply --bucket new --batch 120 --batches 1 --label new<k>` on the COMMITTED tree, read its exit code and its
#   `gated N/N binaries green` line (R97/R66), append the batch's log entry to phase-ends/CURRENT_PHASE.md, commit the bank (R42);
#   every R22_EVERY batches run the clean fleet check (make clean && extract-all && check-all → `218 passed, 0 failed of 218`), log + commit.
# Stops on the first red (a non-zero tool exit, a gated N/M with N != M, a fleet run that is not 218/218) or when the bucket is empty.
# Usage: tools/share_body_cycle.sh START END [R22_EVERY=2] [BUCKET=new]   (each batch ≈ 40–100 s, a fleet run ≈ 90 s — size a call to < 10 min)
#   BUCKET (3.42 T4) is passed to `--bucket` (new | cross | …); labels <bucket><k>; logs under .run/3.42/share/; the CURRENT_PHASE.md
#   entry is skipped when that file or its marker is absent.
#   Commits (3.42 T5.c1) go through tools/commit_task.sh $TASK (default T5.c1) with explicit src/ config/ paths; R22 is not committed.
set -o pipefail
cd "$(dirname "$0")/.." || exit 2
START=$1; END=$2; R22_EVERY=${3:-2}; BUCKET=${4:-new}
PY=.venv/bin/python; [ -x "$PY" ] || PY=/usr/bin/python3
TASK=${TASK:-T5.c1}   # 3.42 T5.c1: commit_task.sh task id for the batch commits
LOGS=.run/3.42/share; mkdir -p "$LOGS" .run/3.42/baseline
[ -n "$START" ] && [ -n "$END" ] || { echo "usage: $0 START END [R22_EVERY] [BUCKET]"; exit 2; }
[ -z "$(git status --short -- src config)" ] || { echo "cycle: src/ or config/ is dirty — commit first (share_body edits a committed tree only)"; exit 3; }
FLEET=$(ls config/check.*.sha | wc -l)
for k in $(seq "$START" "$END"); do
  log=$LOGS/run_$BUCKET$k.log
  { /usr/bin/time -f "$BUCKET$k wall=%e s" "$PY" tools/share_body.py --apply --bucket "$BUCKET" --batch 120 --batches 1 --label "$BUCKET$k"; echo "exit=$?"; } > "$log" 2>&1
  grep -q '^exit=0$' "$log" || { echo "cycle: batch $k — share_body exited non-zero"; tail -3 "$log"; exit 1; }
  if { [ "$BUCKET" = new ] && grep -q 'new (unregistered same-vram) 0 classes' "$log"; } || { [ "$BUCKET" != new ] && grep -q 'done — 0 of 0 classes' "$log"; }; then echo "cycle: the bucket is empty at batch $k"; exit 0; fi
  gated=$(grep -oE 'gated [0-9]+/[0-9]+ binaries green' "$log" | head -1)
  n=$(echo "$gated" | grep -oE '[0-9]+/[0-9]+'); [ "${n%/*}" = "${n#*/}" ] || { echo "cycle: batch $k — $gated"; exit 1; }
  "$PY" - "$k" "$BUCKET" <<'EOF' || exit 1
import pathlib, re, sys
k, bucket = sys.argv[1:3]; log = open(f'.run/3.42/share/run_{bucket}{k}.log').read()
m1 = re.search(r'\] (\d+) classes · (\d+) sites in (\d+) TUs · (\d+) new headers · gating (\d+) binaries', log)
m2 = re.search(r'gated (\d+)/(\d+) binaries green · registered (\d+) groups · extended (\d+) members · rejected classes (\d+)', log)
wall = re.search(r'wall=([\d.]+) s', log).group(1)
rej = [l.strip()[:150].replace('`', "'") for l in log.splitlines() if 'REJECTED' in l]
p = pathlib.Path("phase-ends/CURRENT_PHASE.md"); t = p.read_text() if p.exists() else ""
marker = "\n## Approved plan (verbatim, gate 1 — 2026-09-08)"
entry = (f"\n- **S96 — T5 bucket `{bucket}`, batch {k}** (`run_{bucket}{k}.log`, {wall} s; `batch_{bucket}{k}.json`): `{m1.group(1)} classes · {m1.group(2)} sites in\n"
         f"  {m1.group(3)} TUs · {m1.group(4)} new headers · gating {m1.group(5)} binaries` → **`gated {m2.group(1)}/{m2.group(2)} binaries green · registered\n"
         f"  {m2.group(3)} groups · extended {m2.group(4)} members · rejected classes {m2.group(5)}`**" + ("; rejected: " + "; ".join(rej) if rej else "") + ".")
if marker in t: p.write_text(t.replace(marker, entry + "\n" + marker, 1))
print("log:", m1.groups(), m2.groups())
EOF
  # 3.42 T5.c1: commit via commit_task.sh with explicit paths (every changed/new file under src/ and config/:
  # sites, src/shared headers, dedup.us.yaml, rekeyed ledgers); was `git add -A src/shared && git add -u src config && git commit`.
  mapfile -t paths < <(git status --porcelain --untracked-files=all -- src config | sed -E 's/^...//; s/^.* -> //')
  [ -f phase-ends/CURRENT_PHASE.md ] && paths+=(phase-ends/CURRENT_PHASE.md)
  msg="$BUCKET batch $BUCKET$k: $(grep -oE 'registered [0-9]+ groups' "$log" | head -1), $(grep -oE '[0-9]+ sites in [0-9]+ TUs' "$log" | head -1), $gated, $(grep -oE 'rejected classes [0-9]+' "$log" | head -1)"
  if [ ${#paths[@]} -eq 0 ]; then echo "cycle: batch $k changed nothing under src/ config/ — no commit"
  else bash tools/commit_task.sh "$TASK" "${msg:0:100}" "${paths[@]}" > "$LOGS/commit_$BUCKET$k.log" 2>&1 || { echo "cycle: batch $k — commit_task failed"; tail -3 "$LOGS/commit_$BUCKET$k.log"; exit 1; }
    echo "cycle: batch $k committed $(git log --oneline -1 | cut -c1-9) — $gated, $(grep -oE 'rejected classes [0-9]+' "$log" | head -1)"; fi
  if [ $((k % R22_EVERY)) -eq 0 ]; then
    r22=.run/3.42/baseline/r22_t5_$BUCKET$k.log
    { /usr/bin/time -f "wall=%e s user=%U s sys=%S s" bash -c 'set -o pipefail; make clean && make extract-all JOBS=16 && make check-all JOBS=16'; echo "exit=$?"; } > "$r22" 2>&1
    line=$(grep -oE "check-all: [0-9]+ passed, [0-9]+ failed of [0-9]+" "$r22")
    if ! grep -q '^exit=0$' "$r22" || [ "$line" != "check-all: $FLEET passed, 0 failed of $FLEET" ]; then echo "cycle: R22 RED after batch $k — $line"; exit 1; fi
    "$PY" - "$k" "$line" "$(grep -oE 'wall=[0-9.]+ s' "$r22")" "$BUCKET" <<'EOF' || exit 1
import pathlib, sys
k, line, wall, bucket = sys.argv[1:5]
p = pathlib.Path("phase-ends/CURRENT_PHASE.md"); t = p.read_text() if p.exists() else ""
marker = "\n## Approved plan (verbatim, gate 1 — 2026-09-08)"
entry = f"\n- **S96 — R22 after bucket `{bucket}` batch {k}** (`.run/3.42/baseline/r22_t5_{bucket}{k}.log`): `{line}` · `{wall}` · `exit=0`."
if marker in t: p.write_text(t.replace(marker, entry + "\n" + marker, 1))
EOF
    # 3.42 T5.c1: no marker commit (commit_task.sh refuses an empty commit; was `git commit --allow-empty`); the result is this line + $r22.
    echo "cycle: R22 after batch $k — $line ($(grep -oE 'wall=[0-9.]+ s' "$r22")) at $(git log --oneline -1 | cut -c1-9)"
  fi
done
echo "cycle: batches $START..$END done"
