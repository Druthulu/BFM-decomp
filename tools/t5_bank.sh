#!/usr/bin/env bash
# tools/t5_bank.sh <wave_dir> [arm ...] — the post-draft half of a Claude-subagent wave (P31 S62 T5).
#   1. REFUSE if any other gate/lane is running (wave_judge resets src/ config/ between arms) or if
#      src/ or config/ is already dirty (R42: never blind-revert; someone's banks may be uncommitted).
#   2. WAVE=<wave> tools/wave_judge.py <arms> --union : whole-binary gate per arm (git-diff bank
#      detection, tree reset between arms), then the union gated once and LEFT IN THE TREE.
#   3. R22 clean fleet sweep (make clean -> extract-all -> check-all); the pass line must read
#      "N passed, 0 failed of N" (exit codes checked, R53) or nothing is committed.
#   4. commit the union; the subject carries "— N banked" (the maintenance lane's exemplar counter).
# Drafting must be FINISHED before this runs: the judge rewrites src/ and the sweep deletes asm/.
cd /home/musashi/bfm-decomp || exit 2
WAVE=${1:?usage: t5_bank.sh <wave_dir> [arms...]}; shift
ARMS=${*:-sonnet opus}
ID=$(basename "$WAVE")
say(){ echo "[$(date +%H:%M:%S)] [t5_bank $ID] $*"; }
[ -f "$WAVE/targets.json" ] || { say "REFUSED: no $WAVE/targets.json"; exit 2; }
BUSY=$(pgrep -af 'maintenance\.sh|sweep_parallel\.py|gate_stage\.py|gate_main\.py|gate_lane\.py|^make( |$)' | grep -v "$$" || true)
[ -z "$BUSY" ] || { say "REFUSED: another gate/lane is running:"; echo "$BUSY" | head; exit 2; }
DIRTY=$(git status --porcelain -- src/ config/)
[ -z "$DIRTY" ] || { say "REFUSED: src/ or config/ is dirty — inspect/commit first (R42), never revert:"; echo "$DIRTY" | head; exit 2; }
say "judging arms: $ARMS"
WAVE="$WAVE" .venv/bin/python tools/wave_judge.py $ARMS --union 2>&1 | tee "$WAVE/judge.log"
[ "${PIPESTATUS[0]}" = 0 ] || { say "judge exited non-zero — stopping (tree left as is)"; exit 3; }
N=$(python3 -c "import json;j=json.load(open('$WAVE/judge.json'));print(len(j.get('union',{}).get('banked',[])))")
SUMMARY=$(python3 -c "import json;j=json.load(open('$WAVE/judge.json'));print(', '.join('%s %d/%d'%(a,v['n_banked'],v['drafts']) for a,v in j['arms'].items()))")
if [ "$N" = 0 ]; then say "0 banked ($SUMMARY) — nothing to commit"; git status --short -- src/ config/ | head; exit 0; fi
say "$N banked in the union ($SUMMARY) — R22 clean fleet sweep"
( make clean && make extract-all JOBS=32 && make check-all JOBS=32 ) > "$WAVE/sweep.log" 2>&1
RC=$?
PASS=$(grep -E '^check-all: ' "$WAVE/sweep.log" | tail -1)
say "sweep rc=$RC: ${PASS:-<no check-all line>}"
if [ "$RC" != 0 ] || ! echo "$PASS" | grep -qE '^check-all: ([0-9]+) passed, 0 failed of \1$'; then
  say "FLEET NOT GREEN — NOT committing; the union stays in the tree for inspection (R42). See $WAVE/sweep.log"
  grep -E '^\[ *(FAIL|ERR)' "$WAVE/sweep.log" | head; exit 3
fi
git add -A src/ config/
git commit -q -m "feat(t5): Claude wave $ID — $N banked ($SUMMARY); fleet ${PASS#check-all: } (P31 S62 T5)"
say "committed $(git rev-parse --short HEAD)"
