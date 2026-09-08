#!/usr/bin/env python3
"""tools/t5_targets.py — draw ONE routed Claude-wave slate from the S61 frontier classes (P31 S62 T5).

Usage:
  t5_targets.py --wave .run/t5a [--classes K-NEVER-TOUCHED,L-LOW-TOUCH] [--n 48]
                [--residue .run/t5a[,.run/t5b]] [--main-only] [--ledger .run/t5/drawn.json] [--dry]

Population = the named classes' members (.run/frontier_s61/class_members.json, 'binary:fn' strings)
that are STILL OPEN per corpus.stubs (the R32-asserting oracle; a binary whose oracle refuses is
EXCLUDED LOUDLY and counted) and not already drawn (the ledger, keyed (binary, fn) — R48).
main is excluded unless --main-only: sweep_parallel/wave_judge refuse main (R43); main goes through
gate_main (T5.7). Routing (T4-measured, frontier-analysis-s61 Addendum 5): nins<=120 -> sonnet,
>120 -> opus. A --residue wave's un-banked fns are re-drawn on opus ONCE; an fn already refused
on opus is NOT re-drawn — it is printed as T6 wall-ledger fare.
Draw = stratified by band (<=50 / 51-120 / >120) in proportion to the remaining population, so the
plan's falsifier (banks/draft over the first two waves) measures the population, not a cherry-pick;
class order K -> L -> M within a band; within a class prefer binaries with the most open members
(fewer whole-binary builds per bank at the gate) under --max-per-bin (default 4: a calibration
wave must sample many TUs, and many drafts landing in ONE TU multiply decl-conflict risk), then
address order.
Writes <wave>/targets.json in api_agent's target shape (+ arm, cls, from) and appends to the ledger;
prints every denominator it used (R41)."""
import argparse, collections, json, os, sys
REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__))); os.chdir(REPO)
sys.path.insert(0, 'tools')
import corpus

CLASSES = '.run/frontier_s61/class_members.json'
BANDS = ('<=50', '51-120', '>120')
def band(n): return '<=50' if n <= 50 else ('51-120' if n <= 120 else '>120')
def arm_for(n): return 'sonnet' if n <= 120 else 'opus'

def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--wave', required=True, help='wave dir, e.g. .run/t5a (targets.json is written here)')
    ap.add_argument('--classes', default='K-NEVER-TOUCHED,L-LOW-TOUCH')
    ap.add_argument('--n', type=int, default=48)
    ap.add_argument('--max-per-bin', type=int, default=4, help='cap per binary (spreads a calibration wave; 0 = no cap)')
    ap.add_argument('--residue', default='', help='comma-separated prior wave dirs whose un-banked fns escalate to opus')
    ap.add_argument('--main-only', action='store_true')
    ap.add_argument('--ledger', default='.run/t5/drawn.json')
    ap.add_argument('--dry', action='store_true')
    a = ap.parse_args()

    cm = json.load(open(CLASSES))
    ledger = json.load(open(a.ledger)) if os.path.exists(a.ledger) else {}
    wid = os.path.basename(a.wave.rstrip('/'))
    # running the tool for a wave DEFINES that wave: drop its own earlier ledger entries first
    ledger = {k: [d for d in v if d.get('wave') != wid] for k, v in ledger.items()}
    ledger = {k: v for k, v in ledger.items() if v}
    key = lambda b, f: '%s:%s' % (b, f)

    # --- population: (cls, binary, fn) in class order ------------------------------------------
    members, seen = [], set()
    for cls in a.classes.split(','):
        if cls not in cm: sys.exit('unknown class %r; have: %s' % (cls, sorted(cm)))
        for s in cm[cls]:
            b, f = s.split(':', 1)
            if key(b, f) in seen: continue
            seen.add(key(b, f)); members.append((cls, b, f))
    want_main = a.main_only
    members = [m for m in members if (m[1] == 'main') == want_main]

    # --- residue: a prior wave's un-banked fns, escalated to opus once ---------------------------
    # DEDUPE BY (binary, fn) ACROSS WAVES: the same function can be drawn by two waves (a fresh draw
    # and a residue re-draw), so scanning several prior waves yields duplicates — which the
    # name-keyed pack builder then REFUSES (R43/R48, caught for real on the t5i draw: 4 duplicate
    # names, 2 of them the SAME function listed twice from two waves).
    residue, wall, seen_res = [], [], set()
    for w in filter(None, a.residue.split(',')):
        tg = json.load(open(os.path.join(w, 'targets.json')))
        jd = json.load(open(os.path.join(w, 'judge.json'))) if os.path.exists(os.path.join(w, 'judge.json')) else {}
        banked = set(jd.get('union', {}).get('banked', []))
        for v in jd.get('arms', {}).values(): banked |= set(v.get('banked', []))
        for t in tg:
            if t['name'] in banked: continue
            k = key(t['binary'], t['name'])
            if k in seen_res: continue          # already collected from an earlier wave in this list
            seen_res.add(k)
            if any(d.get('arm') == 'opus' for d in ledger.get(k, [])):
                wall.append((t['binary'], t['name'])); continue
            residue.append((t.get('cls', '?'), t['binary'], t['name'], w))

    # --- open filter via the corpus oracle (per binary; refusals are loud, counted, excluded) ----
    stubs, refused = {}, {}
    for b in sorted({m[1] for m in members} | {r[1] for r in residue}):
        try:
            s = corpus.stubs(b); stubs[b] = {x.symbol: x for x in s.values()}
        except Exception as e:
            refused[b] = str(e).split('\n')[0][:120]
    cnt = collections.Counter()
    pool = []   # dicts in api_agent target shape
    for cls, b, f in members:
        if b in refused: cnt['excluded:oracle-refused'] += 1; continue
        st = stubs[b].get(f)
        if st is None: cnt['closed:already-banked'] += 1; continue
        if key(b, f) in ledger: cnt['drawn-before'] += 1; continue
        nins = corpus.s_ins_count(st.asm_path)
        pool.append(dict(name=f, addr='0x%08x' % st.addr, nins=nins, binary=b, sub=st.asm_dir, asm=st.asm_path,
                         tu=st.path, cls=cls, arm=arm_for(nins), **{'from': 'fresh'}))
    esc, esc_names, deferred = [], set(), []
    for cls, b, f, w in residue:
        if b in refused or f not in stubs.get(b, {}): cnt['residue:closed-or-refused'] += 1; continue
        if f in esc_names:      # two BINARIES' same-named fns cannot share one name-keyed wave (R48)
            deferred.append('%s:%s' % (b, f)); continue
        esc_names.add(f)
        st = stubs[b][f]; nins = corpus.s_ins_count(st.asm_path)
        esc.append(dict(name=f, addr='0x%08x' % st.addr, nins=nins, binary=b, sub=st.asm_dir, asm=st.asm_path,
                        tu=st.path, cls=cls, arm='opus', **{'from': 'residue:' + os.path.basename(w)}))

    # --- denominators (R41) ---------------------------------------------------------------------
    print('population: %d class members (%s, %s) -> %s' % (len(members), a.classes, 'main only' if want_main else 'main excluded',
          dict(cnt) or 'no exclusions'))
    if refused:
        print('ORACLE REFUSED %d binar%s (excluded, %d members): %s' % (len(refused), 'y' if len(refused) == 1 else 'ies',
              cnt['excluded:oracle-refused'], '; '.join('%s: %s' % kv for kv in refused.items())))
    rem = collections.Counter(band(t['nins']) for t in pool)
    print('remaining open+undrawn: %d fns / %d ins  bands %s  classes %s  binaries %d' % (
          len(pool), sum(t['nins'] for t in pool), dict(rem), dict(collections.Counter(t['cls'] for t in pool)),
          len({t['binary'] for t in pool})))
    if residue or wall:
        print('residue: %d escalate to opus, %d refused-on-opus already -> T6 wall ledger: %s' % (
              len(esc), len(wall), ' '.join('%s:%s' % w for w in sorted(set(wall))[:20])))
        if deferred:
            print('residue DEFERRED to a later wave (name already taken in this wave, R48): %s'
                  % ' '.join(deferred))

    # --- stratified draw ------------------------------------------------------------------------
    per_bin = collections.Counter(t['binary'] for t in pool)
    clsrank = {c: i for i, c in enumerate(a.classes.split(','))}
    pool.sort(key=lambda t: (clsrank[t['cls']], -per_bin[t['binary']], t['binary'], int(t['addr'], 16)))
    n = min(a.n, len(pool)); quota = {}
    if n:
        for bd in BANDS: quota[bd] = int(round(n * rem[bd] / len(pool)))
        while sum(quota.values()) > n: quota[max(quota, key=quota.get)] -= 1
        while sum(quota.values()) < n: quota[max(BANDS, key=lambda bd: rem[bd] - quota[bd])] += 1
    drawn, left, used = [], [], collections.Counter()
    # the harness keys packs/drafts by bare fn NAME (<wave>/packs/<fn>.md, <arm>/<fn>.c); overlays
    # share names at equal addresses, so a wave must hold each name ONCE (R48) — duplicates wait
    names = {t['name'] for t in esc}
    capped = lambda t: (a.max_per_bin and used[t['binary']] >= a.max_per_bin) or t['name'] in names
    def take(t): drawn.append(t); used[t['binary']] += 1; names.add(t['name'])
    for t in pool:
        bd = band(t['nins'])
        if quota.get(bd, 0) > 0 and not capped(t): quota[bd] -= 1; take(t)
        else: left.append(t)
    for t in left:                       # spill: a band short of members hands its quota on
        if len(drawn) >= n: break
        if capped(t): continue
        take(t)
    slate = esc + drawn
    print('drawn: %d fresh (bands %s) + %d residue = %d targets; arms %s; binaries %d (= gate builds per arm)' % (
          len(drawn), dict(collections.Counter(band(t['nins']) for t in drawn)), len(esc), len(slate),
          dict(collections.Counter(t['arm'] for t in slate)), len({t['binary'] for t in slate})))
    if a.dry: return
    os.makedirs(a.wave, exist_ok=True)
    json.dump(slate, open(os.path.join(a.wave, 'targets.json'), 'w'), indent=1)
    for t in slate: ledger.setdefault(key(t['binary'], t['name']), []).append({'wave': wid, 'arm': t['arm']})
    os.makedirs(os.path.dirname(a.ledger) or '.', exist_ok=True)
    json.dump(ledger, open(a.ledger, 'w'), indent=0)
    print('wrote %s/targets.json; ledger %s now %d keys' % (a.wave, a.ledger, len(ledger)))
if __name__ == '__main__':
    main()
