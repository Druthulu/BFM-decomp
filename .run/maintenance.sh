#!/usr/bin/env bash
# TWO PATHS, ONE SCRIPT: this file is tracked at BOTH .run/maintenance.sh and
# tools/lanes/maintenance.sh, and `bash .run/maintenance.sh` is what actually runs. They diverged
# once (P31 S59->S60): tools/lanes/ held a pre-S59 copy, an edit landed there, and copying it over
# .run/ silently reverted the R47 shape filter, the R48 (binary,fn) keying, reloc --fix,
# rtu_second_chance and fix_tu_ret_decls. EDIT ONE, COPY TO THE OTHER, DIFF BOTH BEFORE COMMITTING.
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
  # THRESHOLD 150 -> 50 (Drew, P31 S59): the A-prop pipeline was rebuilt to consume every
  # verdict layer and the lane now also carries the free reject-recovery and the periodic
  # fleet R22, so a pass is worth running on a smaller refill than when it only re-swept an
  # unchanged sibling pool. 150 was tuned for the old dead lane.
  if [ "$NEWFN" -lt 50 ]; then
    say "only $NEWFN functions banked since the last pass (need 50) — skipping"
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
  # MECHANICAL SYMBOL REPAIR (S59): an unambiguous reloc MISMATCH is a RENAME, not a reject —
  # --fix rewrites the draft in place (it refuses ambiguity, R39) and the re-check below refreshes
  # the verdicts so a repaired draft stages on this same pass. Measured: 4 of 4 MISMATCHes of the
  # first fixed batch repaired to AGREE/MATCH this way.
  .venv/bin/python - <<'PY'
import json, subprocess
res = json.load(open('.run/reloc_maint.out.json'))
mm = [r for r in res if r.get('status') == 'MISMATCH']
if mm:
    rows = {(r['binary'], r['fn']) for r in mm}
    batch = [r for r in json.load(open('.run/reloc_maint.json')) if (r['binary'], r['fn']) in rows]
    json.dump(batch, open('.run/reloc_maint_mm.json', 'w'), indent=1)
    subprocess.run(['.venv/bin/python', 'tools/reloc_identity.py', '--batch',
                    '.run/reloc_maint_mm.json', '-j', '4', '--fix'], capture_output=True)
    p = subprocess.run(['.venv/bin/python', 'tools/reloc_identity.py', '--batch',
                        '.run/reloc_maint_mm.json', '-j', '4', '--out',
                        '.run/reloc_maint_mm.out.json'], capture_output=True)
    fixed = {(r['binary'], r['fn']): r for r in json.load(open('.run/reloc_maint_mm.out.json'))}
    res = [fixed.get((r.get('binary'), r['fn']), r) for r in res]
    json.dump(res, open('.run/reloc_maint.out.json', 'w'), indent=1)
    n = sum(1 for r in fixed.values() if r['status'] == 'AGREE')
    print(f'reloc --fix: {n}/{len(mm)} MISMATCH draft(s) repaired to AGREE')
PY
  .venv/bin/python - <<'PY'
import json,os,shutil,collections
res=json.load(open('.run/reloc_maint.out.json'))
# STAGE ONLY WHAT CAN BANK (S59, measured). status==AGREE alone let 82 shape-DIFF drafts through
# — reloc AGREE says the SYMBOLS agree, shape==MATCH says the INSTRUCTIONS do; a shape-DIFF draft
# cannot be byte-identical, so each one staged is a whole-binary build spent to learn what
# match_one already printed. Three consecutive 0-bank passes gated 82 of these every 45 minutes.
# Key by (binary, fn): overlays share function NAMES across binaries (func_80162CCC exists in
# main AND ov_MAIN_012), and an fn-keyed set stages every same-named draft when ONE agrees.
ok={(r.get('binary'), r['fn']) for r in res
   if r.get('status') in ('AGREE','UNRESOLVED') and r.get('shape')=='MATCH'}
sla=json.load(open('.run/aprop_maint_slate.json'))
sel=[r for r in sla if (r['binary'], r['fn']) in ok]
dropped=collections.Counter()
for r in res:
    if (r.get('binary'), r['fn']) not in ok:
        dropped[f"{r.get('status')}/{r.get('shape') or '-'}"] += 1
shutil.rmtree('.run/sweep_maint', ignore_errors=True)
for r in sel:
    d=f".run/sweep_maint/{r['binary']}"; os.makedirs(d, exist_ok=True)
    shutil.copy(r['draft'], f"{d}/{r['fn']}.c")
print('staged', len(sel), 'of', len(sla), '; dropped by class:', dict(dropped))
PY
  # SECOND CHANCE FOR STANDALONE COMPILE-FAILS (P31 S59). reloc_identity compiles each draft
  # STANDALONE, but the draft is written to land in a TU that provides typedefs/decls the
  # standalone compile lacks — the wrong oracle for the question (R33). Re-judge those against the
  # REAL TU via rtu_match (no build tree, no locks) and stage the byte-MATCHes: measured 7 of 27
  # such drafts were TU-byte-identical the day this landed, all previously dropped unjudged.
  .venv/bin/python tools/rtu_second_chance.py --reloc .run/reloc_maint.out.json \
      --slate .run/aprop_maint_slate.json --stage .run/sweep_maint -j 8 2>&1 | tail -2

  # FREE RECOVERY OF PRE-GATE REJECTS (P31 S59). 45% of drafts never reach the gate — the reloc
  # pre-filter drops them — and 13% of those have a body that ALREADY MATCHES with only the symbol
  # names wrong (§171). Rebasing is deterministic and costs no model tokens, so it belongs in this
  # lane beside the A-prop sweep. It only STAGES; the gate below is what decides.
  .venv/bin/python tools/recover_rejects.py --limit 60 2>&1 | tail -3

  if [ -n "$(ls .run/sweep_maint 2>/dev/null)" ]; then
    flock .run/auto/draw.lock .venv/bin/python tools/sweep_parallel.py --drafts .run/sweep_maint -j 10 2>&1 | tail -2
    # THE RETURN-TYPE HALF OF THE STALE-DECL WALL (S59, byte-proven 14/30 on its first run): a
    # draft the gate rejects at closeness 0 has a byte-correct body; the dominant residual is the
    # TU's own 'extern void f(void);' against a value-returning definition — the arity pre-pass
    # relaxes the parens, not the return. fix_tu_ret_decls retypes the TU's decls to the
    # definition's return (byte-neutral: declared-void callers ignore $v0), gates, and restores
    # every edit the gate does not pay for. Zero tokens; the whole-binary SHA stays sole arbiter.
    .venv/bin/python - <<'PY'
import json, glob, os, datetime
cut = (datetime.datetime.now() - datetime.timedelta(hours=1)).strftime('%Y-%m-%d %H:%M')
pairs = []
for d in glob.glob('.run/sweep_maint/*/'):
    b = os.path.basename(d.rstrip('/'))
    p = f'.run/auto/bulk/{b}.backlog.jsonl'
    if not os.path.exists(f'config/splat.{b}.yaml') or not os.path.exists(p):
        continue
    fns = {os.path.basename(c)[:-2] for c in glob.glob(d + '*.c')}
    last = {}
    for line in open(p, errors='replace'):
        try: r = json.loads(line)
        except Exception: continue
        if r.get('name') in fns and r.get('ts', '') >= cut:
            last[r['name']] = r
    pairs += [[b, fn] for fn, r in last.items()
              if r.get('status') == 'near' and r.get('closeness') == 0]
json.dump(pairs, open('.run/ret_pairs_maint.json', 'w'))
print('fix_tu_ret candidates:', len(pairs))
PY
    if [ -s .run/ret_pairs_maint.json ] && [ "$(cat .run/ret_pairs_maint.json)" != "[]" ]; then
      .venv/bin/python tools/fix_tu_ret_decls.py --pairs-file .run/ret_pairs_maint.json \
          --drafts .run/sweep_maint -j 6 2>&1 | tail -2
    fi
    if [ -n "$(git status --porcelain -- src/ config/)" ]; then
      git add -A src/ config/
      # NEVER stage main's TUs (top-level src/*.c) from this lane (S59): sweep_parallel refuses
      # main, so any dirt there is another lane's in-flight gate_main work — unverified by
      # construction. One writer (gate_main), one committer (main_lane); adopting a mid-flight
      # substitution is how 24bd25993 turned main's baseline RED for 3h46m.
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
  # PERIODIC FLEET CHECK (P31 S59, cadence tightened S60). Two binaries sat RED for hours — every
  # lane only ever checks the binary it is currently touching, and a byte gate is a correctness
  # oracle with a null coverage model: it is silent about everything it did not build. So sweep the
  # whole fleet and report REDs loudly.
  #
  # EVERY PASS, not every 4th (S60). Detection latency is the real cost of a RED: the binary fails
  # at BUILD, so every draft gated against it is rejected regardless of quality, and the wave reads
  # as a drafting failure. Five REDs in one day, each burning drafts until the ~3 h sweep noticed.
  # Gates now finish in ~35 min instead of 60, so the check is affordable at every pass.
  # LOCK-AWARE WINDOW (S61). The pgrep guard above this line's history ("skip while any gate is in
  # flight") meant the sweep NEVER ran — the gater gates back-to-back, so one was always in flight
  # (last real sweep 12:54 on 08-25, S60 open thread #4). The wave gater, the maintenance sweep and
  # the resolver all hold .run/auto/draw.lock for exactly their gate window, so taking that lock IS
  # the "no overlay gate in flight" condition, and blocking on it gives the sweep a turn instead of
  # a skip. gate_main holds its own lock and is short (~1 min per batch): skip and retry next pass.
  if pgrep -f 'tools/gate_main' >/dev/null; then
    say "fleet R22 sweep skipped this pass: gate_main in flight (retry next pass)"
  else
    say "fleet R22 sweep — taking .run/auto/draw.lock (waits for the current gate), then checks every binary"
    flock .run/auto/draw.lock make check-all JOBS=12 >.run/fleet_check.log 2>&1 || true
    grep -E "^\[FAIL\]" .run/check-all.txt 2>/dev/null | awk '{print $2}' > .run/fleet_red.txt || true
    NRED=$(grep -c . .run/fleet_red.txt 2>/dev/null || echo 0)
    if [ "$NRED" -gt 0 ]; then
      say "*** $NRED BINARY/BINARIES ARE RED — see .run/fleet_red.txt ***"
      head -8 .run/fleet_red.txt | sed 's/^/      RED: /'
      # THE ONE AUTO-REPAIR, AND ONLY BECAUSE IT PROVES ITSELF (S60). Everything else here still
      # fixes NOTHING by design — a guessed pad spec or config edit is how a silent byte shift gets
      # committed. jtbl_pads_fix is different in kind: it does not derive or guess, it ENUMERATES
      # the 2^(N-1) candidate specs and accepts one only if it is the UNIQUE spec that rebuilds the
      # binary byte-identical to config/check.<bin>.sha, restoring the original otherwise. Three of
      # the five REDs on 08-25 were this one class: JTBL_PADS stores a DERIVED property (how many
      # jump tables an object emits) that every bank carrying a `switch` can change under it.
      while read -r RB; do
        [ -n "$RB" ] || continue
        .venv/bin/python tools/jtbl_pads_fix.py "$RB" --apply 2>&1 | sed 's/^/      /'
      done < .run/fleet_red.txt
      if [ -n "$(git status --porcelain -- config/overlays.mk)" ]; then
        make check-all JOBS=12 >.run/fleet_check.log 2>&1 || true
        grep -E "^\[FAIL\]" .run/check-all.txt 2>/dev/null | awk '{print $2}' > .run/fleet_red2.txt || true
        N2=$(grep -c . .run/fleet_red2.txt 2>/dev/null || echo 0)
        if [ "$N2" -lt "$NRED" ]; then
          git add config/overlays.mk
          git commit -q -m "fix(jtbl): byte-proven pad-spec repair ($((NRED-N2)) binary/binaries) — maintenance lane"
          say "pad-spec repair: $NRED RED -> $N2 RED, committed $(git rev-parse --short HEAD)"
        else
          say "pad-spec repair changed nothing measurable — left for a human"
        fi
      fi
    else
      say "fleet R22: all binaries byte-identical ($(grep -c '^\[ OK \]' .run/check-all.txt 2>/dev/null || echo 0) checked)"
    fi
  fi

  say "pass complete; sleeping 45m"
  sleep 2700
done
