#!/usr/bin/env python3
"""Refuse to launch a drafting agent at a target that is ALREADY BANKED (P31 S71, R43/R45).

`wave_args.py` asserts a target is open AT DRAW TIME. A wave's payload then sits on disk while gates
run, so by launch time some of its targets are banked — and an agent handed one burns a full run to
report "STALE CARD — already banked today", with no `.s` left to even score against. Measured S71:
`ov_SC01_006/func_8017F9F8` was banked by gate `27cc083de` and drafted afterwards from a payload
built before it.

The open oracle is the same one everything else uses: a bank REMOVES the INCLUDE_ASM stub, so
`corpus.stubs(binary)` not containing the symbol IS the bank.

  python3 tools/launch_check.py <binary> <fn>            # exit 0 = still open, 2 = already banked
  python3 tools/launch_check.py --payload p.json         # filter a {wave,targets} payload in place
"""
import argparse, json, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import corpus


def is_open(binary, fn):
    try:
        return fn in {s.symbol for s in corpus.stubs(binary).values()}
    except Exception as e:                      # an unreadable binary is not a verdict (R40)
        print('launch_check: corpus refused %s (%s) — treating as OPEN' % (binary, e),
              file=sys.stderr)
        return True


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('binary', nargs='?'); ap.add_argument('fn', nargs='?')
    ap.add_argument('--payload')
    a = ap.parse_args()
    if a.payload:
        d = json.load(open(a.payload))
        keep, drop = [], []
        for t in d.get('targets', []):
            (keep if is_open(t['binary'], t.get('name') or t.get('fn')) else drop).append(t)
        d['targets'] = keep
        json.dump(d, open(a.payload, 'w'), indent=1)
        print('launch_check: %d open, %d ALREADY BANKED and dropped%s'
              % (len(keep), len(drop),
                 (': ' + ' '.join('%s:%s' % (t['binary'], t['name']) for t in drop)) if drop else ''))
        return 0 if keep else 2
    if not (a.binary and a.fn):
        ap.error('give <binary> <fn> or --payload')
    ok = is_open(a.binary, a.fn)
    print('%s:%s %s' % (a.binary, a.fn, 'OPEN' if ok else 'ALREADY BANKED — do not launch'))
    return 0 if ok else 2


if __name__ == '__main__':
    sys.exit(main())
