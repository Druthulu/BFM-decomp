#!/usr/bin/env python3
"""Re-stage ONLY the drafts that compile-and-MATCH in their REAL TU (P31 S71).

A gate stages every draft a binary has and builds the binary ONCE. One draft that cc1 rejects fails
that build, so every OTHER draft staged with it is booked as a failure it had nothing to do with —
measured S71: 4 of 9 probed drafts were `MATCH <n> ins` in their real TU inside binaries that banked
ZERO. `recover_integration --probe-only` already answers, per draft, what the REAL TU does with it
(it splices and runs cc1); this reads those probe logs and rebuilds the gate plan from the winners.

  python3 tools/restage_matching.py --probe-dir .run/S71_probe --src .run/S71_bank \\
      --out .run/S71_bank2 --plan .run/S71_bank2_plan.json

R32: prints the per-binary denominators (drafts probed vs drafts kept) and asserts every kept draft
exists on disk.
"""
import argparse, json, os, re, shutil, sys

ROW = re.compile(r'^(func_[0-9A-Fa-f]{8})\s+(\S+)\s+(\S+)\s+(MATCH|CC1-FAIL|DIFF)\b(.*)$')


def parse(logpath):
    """-> {fn: (verdict, detail)} from a --probe-only table."""
    out = {}
    for line in open(logpath, errors='replace'):
        m = ROW.match(line.strip())
        if m:
            out[m.group(1)] = (m.group(4), m.group(5).strip())
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--probe-dir', required=True)
    ap.add_argument('--src', required=True, help='the original staged tree <src>/<binary>/<fn>.c')
    ap.add_argument('--out', required=True)
    ap.add_argument('--plan', required=True)
    a = ap.parse_args()

    shutil.rmtree(a.out, ignore_errors=True)
    plan, tot, kept, byv = [], 0, 0, {}
    for log in sorted(os.listdir(a.probe_dir)):
        if not log.endswith('.log') or log == 'all.log':
            continue
        b = log[:-4]
        rows = parse(os.path.join(a.probe_dir, log))
        tot += len(rows)
        win = [fn for fn, (v, _) in rows.items() if v == 'MATCH']
        for _, (v, _) in rows.items():
            byv[v] = byv.get(v, 0) + 1
        if not win:
            continue
        d = os.path.join(a.out, b)
        os.makedirs(d)
        n = 0
        for fn in win:
            src = os.path.join(a.src, b, fn + '.c')
            if not os.path.exists(src):
                print('  MISSING %s/%s.c — probe named a draft that is not staged' % (b, fn))
                continue
            shutil.copyfile(src, os.path.join(d, fn + '.c')); n += 1
        if n:
            plan.append({"binary": b, "drafts": os.path.abspath(d)})
            kept += n
            print('  %-14s keep %d of %d probed' % (b, n, len(rows)))
    json.dump(plan, open(a.plan, 'w'), indent=1)
    print('\nprobed drafts: %d  (%s)' % (tot, '  '.join('%s=%d' % kv for kv in sorted(byv.items()))))
    print('re-staged    : %d draft(s) across %d binaries -> %s' % (kept, len(plan), a.plan))
    return 0


if __name__ == '__main__':
    sys.exit(main())
