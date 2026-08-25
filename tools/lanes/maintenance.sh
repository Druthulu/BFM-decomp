#!/usr/bin/env bash
# The FREE lane on a loop: re-run the A-prop sibling remap whenever the gater is idle.
#
# It compounds — every exemplar the waves bank creates new PURE seeds — and costs zero model
# tokens. Measured: 390 banked on the first pass, 338 NEW members appeared on the second after a
# day of banking. Only runs when .run/ready/ is empty, so it never competes with a wave's gate.
set -u
cd /home/musashi/bfm-decomp
say(){ echo "[$(date +%H:%M:%S)] [maint] $*"; }
while [ ! -e .run/ox_campaign.stop ]; do
  # A pre-CHECK is not a lock. This one raced: it saw an empty ready queue during a gater bounce,
  # started, and then a wave was queued — so two sweeps ran at once (measured P31 S58). Per-binary
  # flocks keep each BUILD safe, but both lanes commit, so a stale staged body from one lane can
  # revert the other lane's bank. Hold the same draw lock the gater takes, so gates never overlap.
  if [ -n "$(ls .run/ready/ 2>/dev/null)" ] || pgrep -f 'tools/sweep_parallel' >/dev/null; then
    sleep 300; continue
  fi
  # EXEMPLAR-COUNT TRIGGER, not a timer. The A-prop pool only refills when waves bank NEW
  # exemplars that create fresh PURE seeds; on a 45-minute timer it re-swept an unchanged
  # population and banked 390 -> 7 -> 0 -> 0 (P31 S58), holding a sweep slot and the draw lock for
  # ~25 minutes each pass to do nothing. Wait for real new banks before spending the machine.
  # Count BANKED FUNCTIONS, not commits. The gater makes ONE commit per wave, so wave `av`'s 428
  # banked functions registered as 4 revisions — a 12-commit threshold meant ~12 WAVES (hours),
  # not "enough new exemplars to refill the pool". The pool refills per EXEMPLAR, so that is the
  # unit to threshold on. (Miscalibration caught P31 S58, ~2h after the trigger was introduced.)
  NOW=$(git rev-list --count HEAD)
  LAST=$(cat .run/maint_last_rev 2>/dev/null || echo 0)
  NEWFN=$(git log -$(( NOW - LAST > 0 ? NOW - LAST : 1 )) --format=%s 2>/dev/null \
          | grep -oP '— \K[0-9]+(?= banked)' | paste -sd+ | bc 2>/dev/null || echo 0)
  NEWFN=${NEWFN:-0}
  if [ "$NEWFN" -lt 150 ]; then
    say "only $NEWFN functions banked since the last pass (need 150) — skipping"
    sleep 1800; continue
  fi
  echo "$NOW" > .run/maint_last_rev
  say "gater idle and $NEWFN new functions banked — running the free A-prop sibling lane"
  .venv/bin/python tools/family_cousins.py --aprop-cards 2>&1 | tail -1
  .venv/bin/python tools/aprop_autodraft.py --outdir .run/aprop_maint --slate .run/aprop_maint_slate.json 2>&1 | tail -1
  .venv/bin/python - <<'PY'
import json
s=json.load(open('.run/aprop_maint_slate.json'))
json.dump([{'fn':r['fn'],'binary':r['binary'],'draft':r['draft']} for r in s],
          open('.run/reloc_maint.json','w'), indent=1)
print('drafts:',len(s))
PY
  .venv/bin/python tools/reloc_identity.py --batch .run/reloc_maint.json -j 12 --out .run/reloc_maint.out.json 2>&1 | tail -1
  .venv/bin/python - <<'PY'
import json,os,shutil
res=json.load(open('.run/reloc_maint.out.json'))
ok={r['fn'] for r in res if r.get('status')=='AGREE'}
sel=[r for r in json.load(open('.run/aprop_maint_slate.json')) if r['fn'] in ok]
shutil.rmtree('.run/sweep_maint', ignore_errors=True)
for r in sel:
    d=f".run/sweep_maint/{r['binary']}"; os.makedirs(d, exist_ok=True)
    shutil.copy(r['draft'], f"{d}/{r['fn']}.c")
print('staged', len(sel))
PY
  # FREE RECOVERY OF PRE-GATE REJECTS (P31 S59). 45% of drafts never reach the gate — the reloc
  # pre-filter drops them — and 13% of those have a body that ALREADY MATCHES with only the symbol
  # names wrong (§171). Rebasing is deterministic and costs no model tokens, so it belongs in this
  # lane beside the A-prop sweep. It only STAGES; the gate below is what decides.
  .venv/bin/python tools/recover_rejects.py --limit 60 2>&1 | tail -3

  if [ -n "$(ls .run/sweep_maint 2>/dev/null)" ]; then
    flock .run/auto/draw.lock .venv/bin/python tools/sweep_parallel.py --drafts .run/sweep_maint -j 10 2>&1 | tail -2
    if [ -n "$(git status --porcelain -- src/ config/)" ]; then
      git add -A src/ config/
      # NEVER stage main's TUs (top-level src/*.c) from this lane (S59): sweep_parallel refuses
      # main, so any dirt there is another lane's in-flight gate_main work — unverified by
      # construction. One writer (gate_main), one committer (main_lane); adopting a mid-flight
      # substitution is how commit:2693 turned main's baseline RED for 3h46m.
      git reset -q -- src/*.c 2>/dev/null || true
      if git diff --cached --quiet; then
        say "only main-TU dirt found — leaving it to gate_main/main_lane; nothing to commit"
      else
        git commit -q -m "feat(decomp): free A-prop sibling lane (maintenance pass) — zero model tokens"
        say "committed $(git rev-parse --short HEAD)"
      fi
    else
      say "nothing banked this pass"
    fi
  fi
  # PERIODIC FLEET CHECK (P31 S59). Two binaries sat RED for hours — ov_SC07_010 from a commit whose
  # tree state was never built, ov_SC07_002 from a stale 2-table jtbl pad spec — and NOTHING noticed,
  # because every lane only ever checks the binary it is currently touching. A byte-gate is a
  # correctness oracle with a null coverage model: it is silent about everything it did not build.
  # So sweep the whole fleet on a slow cadence, report REDs loudly, and FIX NOTHING automatically —
  # a wrong repair to a pad spec or a config is exactly how a silent byte shift gets committed.
  # Every 4th pass (~3 h). Skipped while any gate is in flight: check-all rebuilds stale objects and
  # must not race a gate's build for the same binary.
  FC=$(cat .run/maint_fleet_count 2>/dev/null || echo 0); FC=$((FC+1)); echo "$FC" > .run/maint_fleet_count
  if [ $((FC % 4)) -eq 0 ] && ! pgrep -f 'tools/sweep_parallel|tools/gate_stage|tools/gate_main' >/dev/null; then
    say "fleet R22 sweep (every 4th pass) — this checks binaries no lane has touched"
    make check-all JOBS=12 >.run/fleet_check.log 2>&1 || true
    grep -E "^\[FAIL\]" .run/check-all.txt 2>/dev/null | awk '{print $2}' > .run/fleet_red.txt || true
    NRED=$(grep -c . .run/fleet_red.txt 2>/dev/null || echo 0)
    if [ "$NRED" -gt 0 ]; then
      say "*** $NRED BINARY/BINARIES ARE RED — see .run/fleet_red.txt (NOT auto-fixed, by design) ***"
      head -8 .run/fleet_red.txt | sed 's/^/      RED: /'
    else
      say "fleet R22: all binaries byte-identical ($(grep -c '^\[ OK \]' .run/check-all.txt 2>/dev/null || echo 0) checked)"
    fi
  fi

  say "pass complete; sleeping 45m"
  sleep 2700
done
