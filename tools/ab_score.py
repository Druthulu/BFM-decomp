#!/usr/bin/env python3
"""ab_score.py — GROUND-TRUTH scorer for the ab-match A/B experiment.

Re-runs tools/match_one.py on EVERY draft in each arm's dir (the gate-truth proxy; a MATCH
here almost always banks at the whole-binary gate). The drafter agents' self-reported status
is deliberately ignored — the byte-gate is the sole arbiter (project rule G3/P9). For each
frozen target it derives the right --asm-subdir from the target's asm path, scores both arms,
prints a per-function head-to-head + per-arm totals, and a matches-per-dollar comparison.

Cost: exact per-agent token counts aren't exposed here, so $/match is computed under an
explicit EQUAL-TOKENS-PER-DRAFT assumption (same prompt+task → comparable spend per attempt);
the decision-grade figure is the gate-true match RATE, multiplied by the known price ratio.
Pass --in-toks/--out-toks to set the assumed per-draft budget, or per-arm prices via the table.

  .venv/bin/python tools/ab_score.py
  .venv/bin/python tools/ab_score.py --targets .run/ab-exp/targets20.json --base .run/ab-exp --arms opus haiku
"""
import argparse, json, os, re, subprocess, sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = '.venv/bin/python'

# blended price ladder ($ per 1M tokens), keyed by arm id substring (June 2026 rates).
PRICES = {
    'opus':   (5.0, 25.0),
    'sonnet': (3.0, 15.0),
    'haiku':  (1.0,  5.0),
    'glm':    (1.0,  4.0),
    'local':  (0.0,  0.0),
}


def price_for(arm):
    for k, v in PRICES.items():
        if k in arm:
            return v
    return (5.0, 25.0)   # default to opus-tier if unknown


MATCH_RE = re.compile(r'MATCH \((\d+) ins\)')
MISMATCH_RE = re.compile(r'(\d+) mismatched')


def score_one(fn, cfile, asm_subdir):
    """Return ('match',0) | ('near',k) | ('compilefail',None) | ('nodraft',None)."""
    if not os.path.exists(cfile):
        return ('nodraft', None)
    p = subprocess.run([PY, 'tools/match_one.py', fn, '--c', cfile, '--asm-subdir', asm_subdir],
                       capture_output=True, text=True, cwd=REPO)
    out = p.stdout + p.stderr
    if MATCH_RE.search(out):
        return ('match', 0)
    m = MISMATCH_RE.search(out)
    if m:
        return ('near', int(m.group(1)))
    return ('compilefail', None)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--targets', default='.run/ab-exp/targets20.json')
    ap.add_argument('--base', default='.run/ab-exp')
    ap.add_argument('--arms', nargs='+', default=['opus', 'haiku'])
    ap.add_argument('--in-toks', type=int, default=8000, help='assumed input tokens per draft (synthetic fallback)')
    ap.add_argument('--out-toks', type=int, default=20000, help='assumed output tokens per draft (synthetic fallback)')
    ap.add_argument('--measured', nargs='+', default=[], metavar='ARM:TOTAL_TOKENS',
                    help='real total tokens per arm from the workflow usage report, e.g. opus:1968371 haiku:1365666 '
                         '(overrides the synthetic per-draft estimate for that arm)')
    ap.add_argument('--split', type=float, default=0.35, help='input fraction of measured tokens (rest output)')
    a = ap.parse_args()

    measured = {}
    for kv in a.measured:
        arm, tok = kv.split(':')
        measured[arm] = int(tok)

    targets = json.load(open(os.path.join(REPO, a.targets)))
    print('A/B ground-truth scoring (match_one) — %d targets × %d arms %s\n' % (
        len(targets), len(a.arms), a.arms))

    # score every (target, arm)
    scores = {arm: {} for arm in a.arms}   # arm -> fn -> (status, closeness)
    for t in targets:
        fn = t['name']
        asm_subdir = os.path.dirname(t['asm']) if t.get('asm') else 'asm/ov_SC01_077/nonmatchings/ov_SC01_077'
        for arm in a.arms:
            cfile = os.path.join(REPO, a.base, arm, fn + '.c')
            scores[arm][fn] = score_one(fn, cfile, asm_subdir)

    # per-function head-to-head
    cols = '  %-16s %-5s' % ('function', 'nins') + ''.join('  %-14s' % arm for arm in a.arms)
    print(cols)
    print('  ' + '-' * (len(cols) - 2))
    for t in targets:
        fn = t['name']
        row = '  %-16s %-5s' % (fn, t.get('nins'))
        for arm in a.arms:
            st, cl = scores[arm][fn]
            cell = 'MATCH' if st == 'match' else ('near %d' % cl if st == 'near' else st)
            row += '  %-14s' % cell
        print(row)

    # per-arm totals + cost
    print('\n=== TOTALS ===')
    n = len(targets)
    summary = {}
    for arm in a.arms:
        sv = list(scores[arm].values())
        matches = sum(1 for st, _ in sv if st == 'match')
        nears = [cl for st, cl in sv if st == 'near']
        fails = sum(1 for st, _ in sv if st in ('compilefail', 'nodraft'))
        pin, pout = price_for(arm)
        if arm in measured:                                       # real total tokens × split → cost
            cost = measured[arm] * (a.split * pin + (1 - a.split) * pout) / 1e6
        else:                                                     # synthetic per-draft estimate
            cost = n * (a.in_toks * pin + a.out_toks * pout) / 1e6   # all n drafts attempted
        summary[arm] = dict(matches=matches, nears=len(nears),
                            med_near=(sorted(nears)[len(nears) // 2] if nears else None),
                            fails=fails, cost=cost)
        print('  %-7s  match %2d/%d  near %2d (median close=%s)  fail %2d   est.cost $%.2f  ($%.2f/match)' % (
            arm, matches, n, len(nears),
            summary[arm]['med_near'] if summary[arm]['med_near'] is not None else '-',
            fails, cost, (cost / matches if matches else float('inf'))))

    # matches-per-dollar comparison (the decision figure)
    print('\n=== MATCHES PER DOLLAR (gate-true match rate × price; equal-tokens-per-draft assumption) ===')
    base_arm = a.arms[0]
    for arm in a.arms:
        c = summary[arm]['cost']
        mpd = summary[arm]['matches'] / c if c else float('inf')
        print('  %-7s  %.2f matches per $   (%d matches / $%.2f)' % (arm, mpd, summary[arm]['matches'], c))
    if len(a.arms) >= 2:
        b, x = a.arms[0], a.arms[1]
        cb, cx = summary[b]['cost'], summary[x]['cost']
        mb = summary[b]['matches'] / cb if cb else 0
        mx = summary[x]['matches'] / cx if cx else 0
        if mb:
            print('\n  => %s closes %.1f× as many functions per dollar as %s' % (x, (mx / mb) if mb else 0, b))
        if measured:
            print('  (cost from MEASURED tokens %s at %.0f%%-in/%.0f%%-out split, June-2026 price ladder.)'
                  % (measured, a.split * 100, (1 - a.split) * 100))
        else:
            print('  (assumes ~%dk in / %dk out tokens per draft for BOTH arms — refine with measured token counts.)'
                  % (a.in_toks // 1000, a.out_toks // 1000))


if __name__ == '__main__':
    main()
