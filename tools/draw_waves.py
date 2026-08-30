#!/usr/bin/env python3
"""tools/draw_waves.py — draw N drafting waves off the OPEN frontier, cheapest-first (P31 S66).

Usage:
  draw_waves.py --prefix .run/w --waves 2 --per-wave 110 [--max-nins 50] [--min-nins 0]
                [--binaries ov_,md_] [--no-main] [--dry]

WHY (measured, P31 S66). The S65 checkpoint's tier map said "cheap singletons (3-17 ins) ~557 — the
bulk". 557 was the count of one-member FAMILIES, not of small functions: re-measured off
`corpus.stubs`, only 28 undrawn non-main stubs are <=17 ins, and the bulk is 51-120 (258) and >120
(245). A draw tool that reads the FRONTIER rather than a remembered tier count cannot inherit that
conflation (R33: derive, do not re-derive).

WHAT IT ASSERTS
  * population = corpus.stubs (the R32-asserting oracle) over every binary under src/, minus main
    unless --main, minus everything already in the draw ledger (.run/t5/drawn.json, keyed
    "binary:fn" — R48).
  * PACKS ARE NAME-KEYED, so a wave may not contain two functions with the same NAME even in
    different binaries (`claude_wave_packs.py` refuses the whole wave otherwise, measured on r1).
    Collisions are pushed to a LATER wave rather than dropped.
  * every wave's targets.json is written in api_agent's target shape, and the ledger is appended
    only for what is actually written (--dry writes nothing).

Then, per wave: t5_cards.py -> claude_wave_packs.py -> wave_args.py, and launch
tools/workflows/claude_wave_draft.js with the args wave_args.py printed (never hand-typed).
"""
import argparse, collections, glob, json, os, sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(REPO)
sys.path.insert(0, 'tools')
import corpus

LEDGER = '.run/t5/drawn.json'


def arm_for(n):
    return 'sonnet' if n <= 120 else 'opus'


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--prefix', required=True, help='wave dir prefix; waves are <prefix>1, <prefix>2, ...')
    ap.add_argument('--waves', type=int, default=1)
    ap.add_argument('--per-wave', type=int, default=100)
    ap.add_argument('--min-nins', type=int, default=0)
    ap.add_argument('--max-nins', type=int, default=10 ** 9)
    ap.add_argument('--main', action='store_true', help='draw from main (default: excluded — main has its own lane, R43)')
    ap.add_argument('--ledger', default=LEDGER)
    ap.add_argument('--exclude', default='', help='comma-separated binary:fn to skip')
    ap.add_argument('--dry', action='store_true')
    a = ap.parse_args()

    ledger = json.load(open(a.ledger)) if os.path.exists(a.ledger) else {}
    drawn = {tuple(k.split(':', 1)) for k in ledger}
    skip = {tuple(x.split(':', 1)) for x in a.exclude.split(',') if ':' in x}

    bins = sorted(os.path.basename(p) for p in glob.glob('src/*') if os.path.isdir(p))
    bins = [b for b in bins if b != 'shared' and (a.main or b != 'main')]

    pool, refused = [], []
    for b in bins:
        try:
            st = corpus.stubs(b)
        except Exception as e:                      # a refusing oracle is EXCLUDED LOUDLY (R32)
            refused.append((b, str(e)[:80])); continue
        for _, s in st.items():
            n = corpus.s_ins_count(s.asm_path)
            if not (a.min_nins <= n <= a.max_nins):
                continue
            if (b, s.symbol) in drawn or (b, s.symbol) in skip:
                continue
            pool.append(dict(name=s.symbol, addr='0x%08x' % s.addr, nins=n, binary=b,
                             sub=s.asm_dir, asm=s.asm_path, tu=s.path,
                             cls='FRONTIER', arm=arm_for(n), **{'from': 'draw_waves'}))
    pool.sort(key=lambda t: (t['nins'], t['binary'], t['name']))

    print('population: %d open stub(s) in [%d,%d] ins, undrawn, over %d binaries (%d oracle refusals: %s)'
          % (len(pool), a.min_nins, a.max_nins, len(bins), len(refused), refused[:2]), file=sys.stderr)

    waves, cur, used_names = [], [], set()
    deferred = []
    for t in pool:
        if len(waves) == a.waves and len(cur) >= a.per_wave:
            break
        if t['name'] in used_names:                 # name-keyed packs: push the collision later
            deferred.append(t); continue
        cur.append(t); used_names.add(t['name'])
        if len(cur) >= a.per_wave:
            waves.append(cur); cur, used_names = [], set()
            # a deferred collision can go in the NEXT wave
            keep = []
            for d in deferred:
                if len(cur) < a.per_wave and d['name'] not in used_names:
                    cur.append(d); used_names.add(d['name'])
                else:
                    keep.append(d)
            deferred = keep
            if len(waves) >= a.waves:
                break
    if cur and len(waves) < a.waves:
        waves.append(cur)

    total = sum(len(w) for w in waves)
    print('drawing %d wave(s), %d target(s) total (%d name-collision(s) deferred, %d left in pool)'
          % (len(waves), total, len(deferred), len(pool) - total), file=sys.stderr)

    for i, w in enumerate(waves, 1):
        d = '%s%d' % (a.prefix, i)
        band = collections.Counter('<=17' if t['nins'] <= 17 else '18-50' if t['nins'] <= 50
                                   else '51-120' if t['nins'] <= 120 else '>120' for t in w)
        arms = collections.Counter(t['arm'] for t in w)
        print('  %s: %d target(s)  bands=%s  arms=%s  nins %d..%d'
              % (d, len(w), dict(band), dict(arms), w[0]['nins'], w[-1]['nins']), file=sys.stderr)
        if a.dry:
            continue
        os.makedirs(d, exist_ok=True)
        json.dump(w, open(os.path.join(d, 'targets.json'), 'w'), indent=1)
        for t in w:
            ledger['%s:%s' % (t['binary'], t['name'])] = {'wave': d, 'nins': t['nins'], 'arm': t['arm']}
    if not a.dry:
        json.dump(ledger, open(a.ledger, 'w'), indent=0)
        print('ledger: %d key(s)' % len(ledger), file=sys.stderr)
    print(' '.join('%s%d' % (a.prefix, i) for i in range(1, len(waves) + 1)))


if __name__ == '__main__':
    main()
