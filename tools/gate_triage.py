#!/usr/bin/env python3
"""Route a parallel_gate result set to the repair lane its OWN verdict names (§376/§378, R47).

A gate that banks 0 is not a codegen verdict. `match_one` compiles a draft ALONE; the TU it must
live in already carries declarations written for its call sites, and C rejects the pair. Each of
those refusals names its own fix, and the fixes are byte-neutral (a declaration emits no code), so
the whole-binary gate stays the sole arbiter (G3/P9).

  conflicting types for `f`      -> cast_self_callers / fix_arity_callers --any-proto   (§376/§378)
  too few|many arguments to `f`  -> fix_arity_callers --any-proto                       (§376)
  undefined reference to D_*     -> aprop_symfix (stale seed symbol)                    (§171)
  redeclared / previous decl     -> the draft redeclares what the TU owns               (§378c)

R47: consume EVERY verdict layer — the class alone is not the verdict, the diagnostic text is.
R41: every count is printed against the number of drafts staged.
"""
import argparse, collections, json, os, re, sys

LANES = [
    ('CARVE',    re.compile(r'CARVE-REFUSED'),                              'jtbl_carve: probe it — the '
     'dominant sub-class is NON-CONTIGUOUS .rodata in one subseg, fixed by jr_isolate_all (§8b)'),
    ('NO-DIAG',  re.compile(r'CC1-FAIL\(no-diagnostic\)'),                  'the cc1 error was not captured — '
     'recompile the TU to get it'),
    ('ARITY',    re.compile(r'too (few|many) arguments to function'),        '§376 fix_arity_callers --any-proto'),
    ('CONFLICT', re.compile(r'conflicting types for'),                       '§378 cast_self_callers / fix_arity_callers'),
    ('REDECL',   re.compile(r'redeclared|previous declaration|previously declared'), '§378c draft redeclares a TU-owned decl'),
    ('UNDEF-D',  re.compile(r'undefined reference to `?D_[0-9A-Fa-f]{8}'),   '§171 aprop_symfix (stale seed symbol)'),
    ('UNDEF-FN', re.compile(r'undefined reference to `?func_[0-9A-Fa-f]{8}'), 'missing callee definition/decl'),
    ('UNDEF',    re.compile(r'undefined reference to'),                       'unresolved symbol'),
    ('IMPLICIT', re.compile(r'implicit declaration'),                         'missing extern'),
    ('PARSE',    re.compile(r'parse error|syntax error'),                     'draft does not parse in-TU'),
    ('DIFF',     re.compile(r'\bDIFF\b|closeness'),                           'real codegen residual'),
]


def lane_of(text):
    for name, rx, _ in LANES:
        if rx.search(text):
            return name
    return 'OTHER'


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--results', default='.run/pgate_results.json')
    ap.add_argument('--plan', default=None, help='the gate plan, to assert the denominator (R32)')
    ap.add_argument('--out', default='.run/gate_triage.json')
    a = ap.parse_args()

    res = json.load(open(a.results))
    staged = None
    if a.plan:
        staged = 0
        for job in json.load(open(a.plan)):
            staged += len([f for f in os.listdir(job['drafts']) if f.endswith('.c')])

    rows, banked = [], []
    for r in res:
        b = r['binary']
        for fn in r.get('banked') or []:
            banked.append((b, fn))
        for v in r.get('verdicts') or []:
            fn, _, text = v.partition('\t')
            rows.append({'binary': b, 'fn': fn.strip(), 'lane': lane_of(text),
                         'verdict': text.strip()})
        if not (r.get('verdicts') or r.get('banked')) and r.get('tail'):
            rows.append({'binary': b, 'fn': '(binary)', 'lane': lane_of(r['tail']),
                         'verdict': r['tail'].strip()[-200:]})

    seen = {(x['binary'], x['fn']) for x in rows} | set(banked)
    print('== gate triage (R41) ==')
    if staged is not None:
        print('drafts staged            : %d' % staged)
        # R32: a verdict for every staged draft, or say how many went unaccounted.
        print('accounted (banked+verdict): %d / %s' % (len(seen), staged))
    print('banked                   : %d' % len(banked))
    c = collections.Counter(x['lane'] for x in rows)
    for lane, n in c.most_common():
        why = next((w for nm, _, w in LANES if nm == lane), '')
        print('  %-9s %4d   %s' % (lane, n, why))
    json.dump({'banked': banked, 'rows': rows, 'staged': staged},
              open(a.out, 'w'), indent=1)
    print('rows -> %s' % a.out)
    for lane, _, _ in LANES:
        ex = [x for x in rows if x['lane'] == lane][:3]
        for x in ex:
            print('   %-9s %-14s %-16s %s' % (lane, x['binary'], x['fn'], x['verdict'][:110]))
    return 0


if __name__ == '__main__':
    sys.exit(main())
