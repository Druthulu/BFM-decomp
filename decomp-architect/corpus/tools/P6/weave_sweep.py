#!/usr/bin/env python3
"""§406 PROLOGUE-WEAVE SWEEP — one known lever, applied where the BYTES say it belongs.

THE CLASS (cookbook §406). gcc-2.7.2 sched2 sinks a function's prologue `sw $ra` down to just above
the first branch: bb0 is all constant-address MEMs, so `memrefs_conflict_p` (sched.c:614) finds no
dependence, `sw $ra` is ready early and `schedule_select`'s `potential_hazard` (memory beats ALU,
sched.c:2616) promotes it. The lever is a NON-volatile `__asm__("" : : : "memory")` as the first
STATEMENT of the body: the BLK clobber gives `sw $ra` a successor so it is only ready after the load
is picked, and it lands back in the prologue. Twelve other variants are measured INERT (§406).

SELECTION IS DERIVED, NOT PATTERN-MATCHED (R33/R34). The §406 census — "sw $s0 / move $s0,$a0 / sw
$ra in the first 24 lines of the target" — is the shape of the FAMILY, not of the DEFECT, and it is
symmetric: `main/func_8002EED8` has that shape with the target's `sw $ra` ALREADY SUNK, where this
lever pushes exactly the wrong way. The defect is a DISAGREEMENT, so we read it off the residual:

    WEAVE-SUNK   mine sinks `sw ra` BELOW where the target keeps it   -> the lever applies
    WEAVE-EARLY  mine keeps it above where the target sank it         -> the lever is BACKWARDS
    (neither)    the `sw $ra` slot is not the residual                -> not this class

Stages: baseline-score every member's stored drafts -> classify from the residual -> apply the lever
to WEAVE-SUNK only -> re-score. Nothing here drafts; every body already exists.

  python3 tools/weave_sweep.py --limit 5                       # R37 probe
  python3 tools/weave_sweep.py --members .run/S71_frontier.json # the whole real frontier

R32: every input member gets a row or an explicit reason, asserted at the end.
R41: every rate is printed with its denominator.
"""
import argparse, hashlib, json, os, re, subprocess, sys
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CLOBBER = '__asm__("" : : : "memory");'
MINE_RA = re.compile(r'\bsw\s+ra\b')          # objdump form (mine)
TGT_RA = re.compile(r'\bsw\s+\$ra\b')         # splat .s form (target)
KEYWORD = re.compile(r'^\s*(return|if|while|for|do|switch|goto|break|continue|else|case|default)\b')
# A STATEMENT at body top level. Everything else that ends in ';' is treated as a declaration —
# including `register u8 *p __asm__("$16");`, which an earlier decl-side regex missed and so put the
# clobber ABOVE the declarations, where C89 rejects every one of them (cc1-fail on 2 of 5 probes).
STMT = re.compile(r'^\s*(?:[*(!&+\-{}]|'
                  r'[A-Za-z_]\w*\s*(?:\[|\(|\.|->|\+\+|--|=[^=]|[+\-*/%&|^]=|<<=|>>=))')


def score(fn, cfile, asm_dir, timeout=240):
    cmd = ['python3', 'tools/match_one.py', fn, '--c', cfile, '--asm-subdir', asm_dir, '--json']
    try:
        p = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, timeout=timeout)
    except subprocess.TimeoutExpired:
        return {'status': 'timeout', 'closeness': None, 'residual': []}
    for line in reversed(p.stdout.strip().split('\n')):
        line = line.strip()
        if line.startswith('{'):
            try:
                return json.loads(line)
            except ValueError:
                pass
    return {'status': 'no-json', 'closeness': None, 'residual': [],
            'err': (p.stderr or p.stdout)[-200:]}


def is_match(s):
    return (s or {}).get('status', '').lower() == 'match'


def classify(res):
    """Direction of the `sw $ra` disagreement, read off the residual [(i, mine, tgt), ...]."""
    mi = next((i for i, me, tg in res if MINE_RA.search(me)), None)
    ti = next((i for i, me, tg in res if TGT_RA.search(tg)), None)
    if mi is None and ti is None:
        return 'no-ra-residual'
    if mi is None or ti is None:
        return 'ra-one-sided'          # one stream's sw ra moved into a slot the other matches
    if mi > ti:
        return 'WEAVE-SUNK'            # mine below target -> the lever pulls it back up
    if mi < ti:
        return 'WEAVE-EARLY'           # mine above target -> the lever is backwards
    return 'ra-same-index'


def insert_clobber(src, fn, skip=0):
    """Clobber as the first statement of fn's body, skipping `skip` further candidate lines."""
    if CLOBBER.replace(' ', '') in src.replace(' ', ''):
        return None, 'already-has-clobber'
    m = re.search(r'^[^\n;#]*?\b%s\s*\([^;{]*\)\s*\{' % re.escape(fn), src, re.M | re.S)
    if not m:
        return None, 'no-definition'
    lines = src.split('\n')
    i = src[:m.end()].count('\n') + 1
    left = skip
    while i < len(lines):
        s = lines[i].strip()
        if not s or s.startswith('//') or s.startswith('/*') or s.startswith('*/') or s.startswith('*'):
            i += 1; continue
        if s == '}':
            return None, 'empty-body'
        if STMT.match(lines[i]) or KEYWORD.match(lines[i]):
            if left == 0:
                break
            left -= 1
        i += 1
    if i >= len(lines):
        return None, 'no-statement'
    ind = re.match(r'\s*', lines[i]).group(0) or '    '
    body = lines[:i] + [
        '%s/* §406: non-volatile memory clobber. The prologue `sw $ra` has no memory' % ind,
        '%s * dependence in bb0, so sched2 promotes it over the ALU candidates and sinks' % ind,
        '%s * it above the branch; the BLK clobber gives it a successor. */' % ind,
        ind + CLOBBER, ''] + lines[i:]
    return '\n'.join(body), None


def dedup(paths, cap):
    seen, out = set(), []
    for p in paths:
        try:
            h = hashlib.sha1(open(p, 'rb').read()).hexdigest()
        except OSError:
            continue
        if h in seen:
            continue
        seen.add(h); out.append(p)
        if len(out) >= cap:
            break
    return out


def run_member(m, workdir, cap, lever_all):
    fn, asm_dir = m['symbol'], m['asm_dir']
    r = dict(binary=m['binary'], addr=m['addr'], fn=fn, asm_dir=asm_dir, lever=None, klass=None)
    drafts = dedup(m.get('drafts', []), cap)
    r['ndrafts_scored'] = len(drafts)
    if not drafts:
        r['baseline'] = None; r['reason'] = 'no-draft-file'; return r
    best = None
    for d in drafts:
        s = score(fn, d, asm_dir)
        c = s.get('closeness')
        key = c if isinstance(c, (int, float)) else 10 ** 9
        if best is None or key < best[0]:
            best = (key, d, s)
        if is_match(s):
            break
    _, bd, bs = best
    r['baseline'] = {'draft': bd, 'status': bs.get('status'), 'closeness': bs.get('closeness'),
                     'residual_n': len(bs.get('residual') or []), 'nins': bs.get('nins')}
    if is_match(bs):
        r['klass'] = 'baseline-MATCH'; r['reason'] = 'standalone match — an integration target, '\
            'not a lever target (a standalone match is not a bank)'
        return r
    r['klass'] = classify(bs.get('residual') or [])
    if r['klass'] != 'WEAVE-SUNK' and not lever_all:
        r['reason'] = 'not-weave-sunk'; return r
    os.makedirs(workdir, exist_ok=True)
    src = open(bd, errors='replace').read()
    for skip in range(0, 4):                       # self-correcting: walk past a mis-read decl
        new, why = insert_clobber(src, fn, skip)
        if new is None:
            r['reason'] = 'lever-not-applicable:' + why; return r
        lp = os.path.join(workdir, '%s.%s.lever%d.c' % (m['binary'], fn, skip))
        open(lp, 'w').write(new)
        s = score(fn, lp, asm_dir)
        if s.get('status') != 'cc1-fail':
            r['lever'] = {'draft': lp, 'skip': skip, 'status': s.get('status'),
                          'closeness': s.get('closeness')}
            return r
    r['reason'] = 'lever-cc1-fail-all-positions'
    return r


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--members', default='.run/S71_frontier.json')
    ap.add_argument('--out', default='.run/S71_weave.jsonl')
    ap.add_argument('--workdir', default='.run/S71_weave')
    ap.add_argument('--limit', type=int, default=0)
    ap.add_argument('--only', default=None, help='comma-separated binary:0xADDR')
    ap.add_argument('--drafts-per-fn', type=int, default=4)
    ap.add_argument('--workers', type=int, default=12)
    ap.add_argument('--lever-all', action='store_true',
                    help='apply the lever regardless of class (the ABLATION control: it must do '
                         'worse on WEAVE-EARLY than on WEAVE-SUNK, or the classifier is noise)')
    a = ap.parse_args()

    members = json.load(open(a.members))
    if a.only:
        want = {(t.split(':')[0], int(t.split(':')[1], 0)) for t in a.only.split(',')}
        members = [m for m in members if (m['binary'], m['addr']) in want]
    if a.limit:
        seen, first, rest = set(), [], []
        for m in members:
            (first if m['binary'] not in seen else rest).append(m); seen.add(m['binary'])
        members = (first + rest)[:a.limit]
    n_in = len(members)
    print('weave_sweep: %d members / %d workers / <=%d drafts each%s'
          % (n_in, a.workers, a.drafts_per_fn, ' / LEVER-ALL ablation' if a.lever_all else ''),
          flush=True)

    results = []
    with ThreadPoolExecutor(max_workers=a.workers) as ex:
        futs = [ex.submit(run_member, m, a.workdir, a.drafts_per_fn, a.lever_all) for m in members]
        for k, f in enumerate(futs, 1):
            r = f.result(); results.append(r)
            b = r['baseline'] or {}; l = r['lever'] or {}
            print('[%3d/%d] %-14s %-16s base=%s/%-5s %-15s lever=%s/%s %s'
                  % (k, n_in, r['binary'], r['fn'], b.get('status'), b.get('closeness'),
                     r.get('klass'), l.get('status'), l.get('closeness'), r.get('reason', '')),
                  flush=True)
    with open(a.out, 'w') as fh:
        for r in results:
            fh.write(json.dumps(r) + '\n')
    assert len(results) == n_in, 'COVERAGE: %d rows for %d members' % (len(results), n_in)

    from collections import Counter
    cls = Counter(r['klass'] for r in results)
    tried = [r for r in results if r['lever']]
    hit = [r for r in tried if is_match(r['lever'])]
    better = [r for r in tried
              if isinstance(r['lever'].get('closeness'), (int, float))
              and isinstance((r['baseline'] or {}).get('closeness'), (int, float))
              and r['lever']['closeness'] < r['baseline']['closeness']]
    print('\n== §406 weave sweep (R41: rates carry their denominators) ==')
    print('members in                    : %d' % n_in)
    for k, v in cls.most_common():
        print('  class %-18s      : %d / %d' % (k, v, n_in))
    print('lever applied                 : %d / %d' % (len(tried), n_in))
    if tried:
        print('lever MATCH                   : %d / %d applied (%d / %d members)'
              % (len(hit), len(tried), len(hit), n_in))
        print('lever improved, still near    : %d / %d applied' % (len(better), len(tried)))
        for r in hit:
            print('   MATCH %-14s %s' % (r['binary'], r['fn']))
    for r in results:
        if str(r.get('reason', '')).startswith('lever-'):
            print('   skipped %-14s %-16s %s' % (r['binary'], r['fn'], r['reason']))
    print('rows -> %s' % a.out)
    return 0


if __name__ == '__main__':
    sys.exit(main())
