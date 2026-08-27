#!/usr/bin/env bash
# tools/t5_bank.sh <wave_dir> [arm ...] — the post-draft half of a Claude-subagent wave (P31 S62 T5).
#   1. REFUSE if any other gate/lane is running (wave_judge resets src/ config/ between arms) or if
#      src/ or config/ is already dirty (R42: never blind-revert; someone's banks may be uncommitted).
#   2. WAVE=<wave> tools/wave_judge.py <arms> --union : whole-binary gate per arm (git-diff bank
#      detection, tree reset between arms), then the union gated once and LEFT IN THE TREE.
#   3. RECOVER the un-banked: a draft whose BODY is byte-correct but whose destination TU declares
#      the function `extern void ...` when it returns a value is refused at closeness 0 with no
#      codegen fault at all. `fix_tu_ret_decls` retypes those decls, re-gates, and restores every
#      edit the gate does not pay for. Measured on wave t5a: 2 of 2 such refusals banked, both
#      self-reported MATCH and both confirmed byte-exact by match_one in isolation.
#   4. R22 clean fleet sweep (make clean -> extract-all -> check-all); the pass line must read
#      "N passed, 0 failed of N" (exit codes checked, R53) or nothing is committed.
#   5. commit the union; the subject carries "— N banked" (the maintenance lane's exemplar counter).
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
# ---- recovery pass over everything the union did not bank (see step 3) --------------------------
UNB=$(.venv/bin/python - "$WAVE" <<'PY'
import json, os, shutil, sys
w = sys.argv[1]
tg = json.load(open(w + '/targets.json')); j = json.load(open(w + '/judge.json'))
banked = set(j.get('union', {}).get('banked', []))
for v in j.get('arms', {}).values(): banked |= set(v.get('banked', []))
best = j.get('union', {}).get('picked', {})
arms = list(j.get('arms', {}))
rec = w + '/recover'; shutil.rmtree(rec, ignore_errors=True)
pairs = []
for t in tg:
    if t['name'] in banked: continue
    for arm in [best.get(t['name'])] + arms:
        src = w + '/%s/%s.c' % (arm, t['name']) if arm else ''
        if src and os.path.exists(src) and os.path.getsize(src):
            os.makedirs('%s/%s' % (rec, t['binary']), exist_ok=True)
            shutil.copy(src, '%s/%s/%s.c' % (rec, t['binary'], t['name']))
            pairs.append([t['binary'], t['name']]); break
json.dump(pairs, open(w + '/ret_pairs.json', 'w'))
print(len(pairs))
PY
)
if [ "${UNB:-0}" != 0 ]; then
  say "recovery: $UNB un-banked draft(s) -> fix_tu_ret_decls (TU 'extern void' on a value-returning fn)"
  flock .run/auto/draw.lock .venv/bin/python tools/fix_tu_ret_decls.py --pairs-file "$WAVE/ret_pairs.json" \
      --drafts "$WAVE/recover" -j 4 2>&1 | tee "$WAVE/recover.log" | tail -3
  N=$(git diff -U0 -- src/ | grep -cE '^-INCLUDE_ASM' || true)
  SUMMARY="$SUMMARY, +recovery"
fi
if [ "$N" = 0 ]; then say "0 banked ($SUMMARY) — nothing to commit"; git status --short -- src/ config/ | head; exit 0; fi
say "$N banked total ($SUMMARY) — R22 clean fleet sweep"
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
