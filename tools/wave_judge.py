#!/usr/bin/env python3
"""Wave judge (tools/wave_judge.py; born as the T4 judge) — per-arm whole-binary gate (G3/P9, exit codes checked per R53), tree reset between arms,
then the union (best arm per fn) gated once and left in the tree for the commit. Reads targets from
.run/t4/targets.json and drafts from .run/t4/<arm>/<fn>.c. Writes .run/t4/judge.json.
Usage: judge.py [arms...]   (default haiku sonnet opus ds)"""
import sys, os, json, glob, subprocess, shutil, time
REPO = '/home/musashi/bfm-decomp'; os.chdir(REPO)
WAVEDIR = os.environ.get('WAVE', '.run/t4')   # the wave's dir: <WAVEDIR>/targets.json, <WAVEDIR>/<arm>/<fn>.c
sys.path.insert(0, 'tools'); import corpus
UNION = '--union' in sys.argv
ARMS = [a for a in sys.argv[1:] if not a.startswith('--')] or ['haiku', 'sonnet', 'opus', 'ds']
targets = json.load(open(WAVEDIR + '/targets.json'))
T = {t['name']: t for t in targets}
if len(T) != len(targets):   # drafts/targets are keyed by bare fn name; a same-named pair would be mis-gated (R43/R48)
    sys.exit('REFUSED: duplicate fn names in %s/targets.json (name-keyed harness): %s' % (
        WAVEDIR, ' '.join(n for n in T if sum(1 for t in targets if t['name'] == n) > 1)))
def sh(cmd, timeout=3600):
    return subprocess.run(cmd, capture_output=True, text=True, timeout=timeout)
def open_fns():
    out = {}
    for b in {t['binary'] for t in targets}:
        s = corpus.stubs(b); out[b] = {x.symbol for x in (s.values() if isinstance(s, dict) else s)}
    return out
def reset_tree():
    sh(['git', 'checkout', '-q', '--', 'src/', 'config/']); sh(['git', 'clean', '-fq', 'src/'])
    r = sh(['git', 'status', '--porcelain', '--', 'src/', 'config/'])
    assert not r.stdout.strip(), 'tree not clean after reset:\n' + r.stdout
def stage(arm, fns):
    d = WAVEDIR + '/stage_%s' % arm; shutil.rmtree(d, ignore_errors=True)
    n = 0
    for fn in fns:
        src = WAVEDIR + '/%s/%s.c' % (arm, fn)
        if not os.path.exists(src) or os.path.getsize(src) == 0: continue
        b = T[fn]['binary']; os.makedirs('%s/%s' % (d, b), exist_ok=True)
        shutil.copy(src, '%s/%s/%s.c' % (d, b, fn)); n += 1
    return d, n
def gate(arm, fns):
    before = open_fns()
    d, n = stage(arm, fns)
    if n == 0: return {}, 'no drafts'
    bins = ','.join(sorted({T[f]['binary'] for f in fns if os.path.exists(WAVEDIR + '/%s/%s.c' % (arm, f))}))
    t0 = time.time()
    r = sh(['flock', '.run/auto/draw.lock', '.venv/bin/python', 'tools/sweep_parallel.py', '--drafts', d, '--only', bins, '-j', '4'], 7200)
    open(WAVEDIR + '/gate_%s.log' % arm, 'w').write(r.stdout + r.stderr)
    # banked = INCLUDE_ASM lines the gate removed (git diff; immune to corpus's per-process cache)
    d = sh(['git', 'diff', '-U0', '--', 'src/']).stdout
    import re as _re
    removed = set(_re.findall(r'^-INCLUDE_ASM\("[^"]+",\s*(func_\w+)\);', d, _re.M))
    banked = {fn for fn in fns if fn in removed}
    return banked, 'rc=%d %ds %d staged' % (r.returncode, time.time() - t0, n)
def main():
    reset_tree()
    res = {'arms': {}, 'fns': {}}
    if os.path.exists(WAVEDIR + '/judge.json'):
        old = json.load(open(WAVEDIR + '/judge.json')); res['arms'] = old.get('arms', {})
        for a, v in res['arms'].items():
            for f in v.get('banked', []): res['fns'].setdefault(f, []).append(a)
    for arm in ARMS:
        fns = [t['name'] for t in targets]
        banked, note = gate(arm, fns)
        res['arms'][arm] = {'banked': sorted(banked), 'n_banked': len(banked), 'drafts': sum(1 for f in fns if os.path.exists(WAVEDIR + '/%s/%s.c' % (arm, f))), 'note': note}
        print('%-7s banked %2d / %2d drafts  (%s)' % (arm, len(banked), res['arms'][arm]['drafts'], note), flush=True)
        for f in banked: res['fns'].setdefault(f, []).append(arm)
        reset_tree()
    # union: cheapest winning arm per fn (ladder order), gated once and LEFT IN THE TREE for the commit
    order = ['haiku', 'sonnet', 'ds', 'opus']
    pick = {}
    for f, arms in res['fns'].items():
        pick[f] = sorted(arms, key=lambda a: order.index(a) if a in order else 99)[0]
    ud = WAVEDIR + '/stage_union'; shutil.rmtree(ud, ignore_errors=True)
    for f, a in pick.items():
        b = T[f]['binary']; os.makedirs('%s/%s' % (ud, b), exist_ok=True)
        shutil.copy(WAVEDIR + '/%s/%s.c' % (a, f), '%s/%s/%s.c' % (ud, b, f))
    if pick and UNION:
        bins = ','.join(sorted({T[f]['binary'] for f in pick}))
        r = sh(['flock', '.run/auto/draw.lock', '.venv/bin/python', 'tools/sweep_parallel.py', '--drafts', ud, '--only', bins, '-j', '4'], 7200)
        open(WAVEDIR + '/gate_union.log', 'w').write(r.stdout + r.stderr)
        d = sh(['git', 'diff', '-U0', '--', 'src/']).stdout
        import re as _re
        removed = set(_re.findall(r'^-INCLUDE_ASM\("[^"]+",\s*(func_\w+)\);', d, _re.M))
        res['union'] = {'picked': pick, 'banked': sorted(f for f in pick if f in removed), 'rc': r.returncode}
        print('union: %d picked, %d banked (rc=%d) — LEFT IN TREE for the commit' % (len(pick), len(res['union']['banked']), r.returncode))
    json.dump(res, open(WAVEDIR + '/judge.json', 'w'), indent=1)
    # per-band table (R41: denominators)
    band = lambda n: '<=50' if n <= 50 else ('51-120' if n <= 120 else '>120')
    for arm in res['arms']:
        row = {}
        for t in targets:
            k = band(t['nins']); row.setdefault(k, [0, 0]); row[k][1] += 1
            if t['name'] in res['arms'][arm]['banked']: row[k][0] += 1
        print('%-7s ' % arm + '  '.join('%s: %d/%d' % (k, v[0], v[1]) for k, v in sorted(row.items())))
if __name__ == '__main__':
    main()
