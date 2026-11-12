#!/usr/bin/python3
# 3.43 T4 fix: SKIP drops an orig uid only while it is still a self-copy in that pass (combine can fold a const into a skipped arg copy, e.g. func_8017DE00 uid 67)
"""wall_probe.py: hard-reg pin wall probe (from 3.43 T4 probe.py, passdiff.py, ctxdiff.py).
Probe:   wall_probe.py --out DIR [--body FILE] [--analyse] <file> <func> [$reg,$reg..]
  drop the $4-$7 pins of func in a scratch copy (or use --body FILE as the variant), --try both variants,
  dump both with cc1_dumps_tu.sh, keep only func's section of each pass, analyse.
  out: DIR/<func>__<tu-tag>[__$PROBE_SUFFIX]/{orig.c,nopin.c,try_*.txt,d_<v>/<pass>,analysis.txt,canon_diff_*.txt}
  --analyse: re-analyse an existing probe dir (no --try, no dumps).
Passdiff: wall_probe.py --passdiff PROBEDIR [--body FILE]   canonical diff summary per pass (rtl..combine)
Ctxdiff:  wall_probe.py --ctxdiff PROBEDIR PASS [N] [--body FILE]   canonical unified diff of one pass, N context (3)
  both re-run the analysis of PROBEDIR (rewrites its analysis files); a __param dir needs its --body FILE.
Env: PROBE_SUFFIX (tag suffix), SHOWN (canon diff lines printed, default 14)."""
import re, sys, os, subprocess, shutil, glob, json, argparse, io
ROOT = '/home/musashi/bfm-decomp/'
os.chdir(ROOT)
ap = argparse.ArgumentParser(usage=__doc__)
ap.add_argument('args', nargs='*')
ap.add_argument('--out')
ap.add_argument('--body')
ap.add_argument('--analyse', action='store_true')
ap.add_argument('--passdiff', metavar='DIR')
ap.add_argument('--ctxdiff', nargs='+', metavar='ARG')
opt = ap.parse_args()
MODE_DIR = opt.passdiff or (opt.ctxdiff[0] if opt.ctxdiff else None)
if MODE_DIR:
    if opt.ctxdiff and not 2 <= len(opt.ctxdiff) <= 3: ap.error('--ctxdiff DIR PASS [N]')
    MODE_DIR = MODE_DIR.rstrip('/') + '/'
    if MODE_DIR.endswith('__param/'):
        if not opt.body: ap.error('a __param probe dir needs --body FILE (its variant body)')
        os.environ['PROBE_SUFFIX'] = 'param'
    f = open(MODE_DIR + 'tu').read().splitlines()[0]; fn = '_'.join(os.path.basename(MODE_DIR[:-1]).split('_')[:2])
    only = None; opt.analyse = True
    _stdout = sys.stdout; sys.stdout = io.StringIO()
else:
    if not opt.out: ap.error('--out DIR is required')
    if len(opt.args) < 2: ap.error('need <file> <func>')
    f, fn = opt.args[0], opt.args[1]
    only = set(opt.args[2].split(',')) if len(opt.args) > 2 and opt.args[2].startswith('$') else None
tag = fn + '__' + re.sub(r'\W', '_', os.path.splitext(os.path.basename(f))[0])
if os.environ.get('PROBE_SUFFIX'): tag += '__' + os.environ['PROBE_SUFFIX']
D = os.path.abspath(MODE_DIR) + '/' if MODE_DIR else os.path.abspath(opt.out) + '/' + tag + '/'
os.makedirs(D, exist_ok=True)
PASSES = ['rtl', 'jump', 'cse', 'loop', 'cse2', 'flow', 'combine', 'sched', 'lreg', 'greg', 'sched2', 'jump2', 'dbr']

raw = open(f, errors='replace').read()

def find_def(src, name):
    blank = re.sub(r'/\*.*?\*/|//[^\n]*', lambda m: re.sub(r'[^\n]', ' ', m.group(0)), src, flags=re.S)
    for m in re.finditer(r'^[ \t]*[A-Za-z_][^\n;#=(]*\b' + name + r'\s*\([^;{]*\)(?:\s*[A-Za-z_][^;{}()]*;)*\s*\{', blank, re.M):
        i = m.end() - 1; d = 0; j = i
        while True:
            c = src[j]
            if src.startswith('//', j): j = src.index('\n', j); continue
            if src.startswith('/*', j): j = src.index('*/', j) + 2; continue
            if c in '"\'':
                k = j + 1
                while src[k] != c: k += 2 if src[k] == '\\' else 1
                j = k + 1; continue
            if c == '{': d += 1
            elif c == '}':
                d -= 1
                if d == 0: break
            j += 1
        return m.start(), j + 1
    return None

dname = fn
se = find_def(raw, fn)
if not se:
    al = re.search(r'(\w+)\s*\([^;{]*\)\s*__asm__\s*\(\s*"' + fn + r'"\s*\)\s*;', raw)
    if al:
        dname = al.group(1); r2 = raw[:al.start()] + ' ' * (al.end() - al.start()) + raw[al.end():]
        se = find_def(r2, dname)
if not se: sys.exit('no def')
orig = raw[se[0]:se[1]]
pinre = re.compile(r'register\s+([^;={}]*?)\s*\b(?:__asm__|asm)\s*\(\s*"\$?([4-7]|a[0-3])"\s*\)')
dropped = []
def drop(m):
    r = m.group(2); r = str(4 + int(r[1])) if r[0] == 'a' else r
    if only and '$' + r not in only: return m.group(0)
    dropped.append('$' + r)
    return m.group(1)
nopin = pinre.sub(drop, orig)
if opt.body: nopin = open(opt.body).read(); dropped.append('variant ' + opt.body)
open(D + 'orig.c', 'w').write(orig); open(D + 'nopin.c', 'w').write(nopin)
open(D + 'tu', 'w').write(f + '\n')

def run_try(v):
    p = subprocess.run(['/usr/bin/python3', 'tools/delever_search.py', '--try', f, fn, D + v + '.c', '--body'],
                       capture_output=True, text=True)
    open(D + 'try_' + v + '.txt', 'w').write(p.stdout + p.stderr)
    m = re.search(r'score (\d+)', p.stdout + p.stderr)
    return (m.group(1) if m else '?'), ('MATCH' in p.stdout)

ANALYSE = opt.analyse
if ANALYSE:
    def _rd(v):
        t = open(D + 'try_' + v + '.txt').read(); m = re.search(r'score (\d+)', t)
        return (m.group(1) if m else '?'), ('MATCH' in t)
    res = {v: _rd(v) for v in ('orig', 'nopin')}
else:
    res = {v: run_try(v) for v in ('orig', 'nopin')}

# dumps: splice into a TU copy (header rows: inline the spliced header into an including TU)
if f.endswith('.h'):
    hb = os.path.basename(f)
    inc = None
    for c in sorted(glob.glob('src/*/*.c')):
        t = open(c, errors='replace').read()
        if re.search(r'#include\s+"[^"]*' + re.escape(hb) + '"', t): inc = c; break
    base_tu = inc
else:
    base_tu = f
open(D + 'tu', 'a').write('dump_tu ' + base_tu + '\n')

def section(path, names):
    out = []; on = False
    with open(path, errors='replace') as h:
        for line in h:
            if line.startswith(';; Function '):
                on = line.split()[2] in names
            if on: out.append(line)
    return ''.join(out)

for v, body in (() if ANALYSE else (('orig', orig), ('nopin', nopin))):
    spliced = raw[:se[0]] + body + raw[se[1]:]
    if f.endswith('.h'):
        t = open(base_tu, errors='replace').read()
        t = re.sub(r'#include\s+"[^"]*' + re.escape(os.path.basename(f)) + '"', lambda m: spliced, t, count=1)
    else:
        t = spliced
    tuc = D + 'tu.c'
    tdir = os.path.dirname(ROOT + base_tu)
    t = re.sub(r'#include\s+"([^"/]+)"', lambda m: '#include "%s/%s"' % (tdir, m.group(1)) if os.path.exists(tdir + '/' + m.group(1)) else m.group(0), t)
    open(tuc, 'w').write(t)
    env = dict(os.environ, DUMP_ROOT=D + 'dumpraw')
    subprocess.run(['bash', 'tools/cc1_dumps_tu.sh', tuc, v], env=env, capture_output=True, text=True)
    od = D + 'd_' + v + '/'; os.makedirs(od, exist_ok=True)
    for p in PASSES:
        src = D + 'dumpraw/dumps_%s/%s.i.%s' % (v, v, p)
        if os.path.exists(src): open(od + p, 'w').write(section(src, (fn, dname)))
    s = D + 'dumpraw/dumps_%s/%s.s' % (v, v)
    if os.path.exists(s):
        txt = open(s).read()
        m = re.search(r'^(?:%s|%s):\n(.*?)\n\s*\.end\s' % (fn, dname), txt, re.S | re.M)
        open(od + 'asm.s', 'w').write(m.group(1) if m else '')
    os.remove(tuc)
shutil.rmtree(D + 'dumpraw', ignore_errors=True)

# ---- analysis ----
def toks(s):
    return re.findall(r'"(?:[^"\\]|\\.)*"|[()\[\]]|[^\s()\[\]"]+', s)
def parse(ts, i=0):
    if ts[i] in '([':
        close = ')' if ts[i] == '(' else ']'; i += 1; l = []
        while ts[i] != close:
            x, i = parse(ts, i); l.append(x)
        return l, i + 1
    return ts[i], i + 1
def insns(path):
    if not os.path.exists(path): return []
    txt = open(path).read()
    ls = txt.split('\n'); k = next((i for i, l in enumerate(ls) if l.startswith('(')), len(ls))
    ts = toks('\n'.join(l for l in ls[k:] if not l.startswith(';')))
    out = []; i = 0
    while i < len(ts):
        if ts[i] != '(': i += 1; continue
        try: x, i = parse(ts, i)
        except IndexError: break
        if isinstance(x, list) and x and x[0] in ('insn', 'jump_insn', 'call_insn', 'code_label'): out.append(x)
    return out
def isreg(x): return isinstance(x, list) and x and isinstance(x[0], str) and x[0].startswith('reg')
def norm(x):
    if isinstance(x, list) and x and isinstance(x[0], str) and x[0].startswith('subreg') and len(x) > 1 and isreg(x[1]):
        return '(%s)' % x[0].split(':')[-1]
    if isreg(x): return '(%s)' % x[0].split(':')[-1] if ':' in x[0] else '(reg)'
    if isinstance(x, list) and x and x[0] == 'label_ref': return '(label_ref)'
    if isinstance(x, list): return '(' + ' '.join(norm(y) for y in x) + ')'
    return x
def hard(x):
    if isreg(x): return '(r%s)' % x[1]
    if isinstance(x, list): return '(' + ' '.join(hard(y) for y in x) + ')'
    return x
def pat(x): return x[4] if x[0] != 'code_label' else ['L']
SKIP = set()
def selfcopy(x):
    q = pat(x)
    return x[0] == 'insn' and isinstance(q, list) and q[0] == 'set' and isreg(q[1]) and isreg(q[2]) and q[1][1] == q[2][1]
def regs_in(x, acc):
    if isreg(x): acc[x[1]] = acc.get(x[1], 0) + 1
    elif isinstance(x, list):
        for y in x: regs_in(y, acc)
    return acc
def collapse(L):
    # expand artifact: (set P X); (set R P) with P a pseudo seen only there -> (set R X)
    cnt = {}
    for x in L: regs_in(pat(x), cnt)
    out = []; i = 0
    while i < len(L):
        a = pat(L[i])
        if (i + 1 < len(L) and L[i][0] == 'insn' and L[i + 1][0] == 'insn' and isinstance(a, list) and a[0] == 'set' and isreg(a[1])
                and '/v' not in a[1][0] and int(a[1][1]) >= 64 and cnt.get(a[1][1]) == 2):
            b = pat(L[i + 1])
            if isinstance(b, list) and b[0] == 'set' and isreg(b[2]) and b[2][1] == a[1][1]:
                out.append(['set', b[1], a[2]]); i += 2; continue
        out.append(a if L[i][0] != 'code_label' else ['L']); i += 1
    return out
def seq(path, f_):
    L = [x for x in insns(path) if '/d_nopin/' in path or not (x[1] in SKIP and selfcopy(x))]
    if f_ is norm: return [norm(q) for q in collapse(L)]
    return [f_(pat(x)) for x in L]

A = []
A.append('try orig score=%s match=%s ; nopin score=%s match=%s ; dropped %s' % (res['orig'][0], res['orig'][1], res['nopin'][0], res['nopin'][1], ','.join(dropped)))
o, n = D + 'd_orig/', D + 'd_nopin/'
SKIP = {x[1] for x in insns(o + 'rtl') if selfcopy(x)}
A.append('skip orig self-copy uids: ' + ' '.join(sorted(SKIP, key=int)))
# var -> pseudo: align .rtl insns by uid
oi = {x[1]: x for x in insns(o + 'rtl') if x[0] != 'code_label'}
ni = {x[1]: x for x in insns(n + 'rtl') if x[0] != 'code_label'}
pairs = {}
def walk(a, b):
    if isreg(a) and isreg(b):
        if '/v' in a[0] and a[1] in ('4', '5', '6', '7') and int(b[1]) >= 64: pairs.setdefault(a[1], set()).add(b[1])
        return
    if isinstance(a, list) and isinstance(b, list) and len(a) == len(b):
        for x, y in zip(a, b): walk(x, y)
import difflib
for ps in ('rtl', 'cse', 'combine'):
    ca = collapse([x for x in insns(o + ps) if not (x[1] in SKIP and selfcopy(x))]); cb = collapse(insns(n + ps))
    sa = [norm(q) for q in ca]; sb = [norm(q) for q in cb]
    for blk in difflib.SequenceMatcher(None, sa, sb, autojunk=False).get_matching_blocks():
        for k in range(blk.size): walk(ca[blk.a + k], cb[blk.b + k])
    if pairs: break
VH_ = set(pairs); VP_ = set(q for v in pairs.values() for q in v)
def canon(path, v):
    L = collapse([x for x in insns(path) if v == 'n' or not (x[1] in SKIP and selfcopy(x))]); ids = {}
    def c(x):
        if isinstance(x, list) and x and isinstance(x[0], str) and x[0].startswith('subreg') and len(x) > 1 and isreg(x[1]):
            inner = c(x[1])
            return '(VAR)' if inner == '(VAR)' else '(sub:%s %s)' % (x[0].split(':')[-1], inner)
        if isreg(x):
            r = x[1]
            if r in VH_ or (v == 'n' and r in VP_): return '(VAR)'
            if int(r) < 64 and not path.endswith(('lreg',)) and path.split('/')[-1] in ('greg', 'sched2', 'jump2', 'dbr'): return '(h%s)' % r
            if int(r) < 64: return '(h%s)' % r
            return '(p%d)' % ids.setdefault(r, len(ids))
        if isinstance(x, list) and x and str(x[0]).startswith('label_ref'): return '(label_ref)'
        if isinstance(x, list): return '(' + ' '.join(c(y) for y in x) + ')'
        return x
    return [z for z in (c(q) for q in L) if z != '(set (VAR) (VAR))']
POST = ('greg', 'sched2', 'jump2', 'dbr')
def same(p): return (seq(o + p, norm) == seq(n + p, norm)) if p in POST else (canon(o + p, 'o') == canon(n + p, 'n'))
vec = [(p, same(p)) for p in PASSES]
dec = None
if not dict(vec)['sched']:
    i = PASSES.index('sched')
    while i > 0 and not dict(vec)[PASSES[i - 1]]: i -= 1
    dec = PASSES[i]
A.append('decisive struct pass: %s' % (dec or 'none (sched1 output equal)'))
A.append('struct vector: ' + ' '.join('%s=%s' % (p, '=' if same(p) else 'X') for p in PASSES))
gtxt = open(n + 'greg').read() if os.path.exists(n + 'greg') else ''
m = re.search(r';; \d+ regs to allocate:([^\n]*)', gtxt); galloc = set(m.group(1).split()) if m else set()
disp = dict(re.findall(r'(\d+) in (\d+)', gtxt.split(';; Register dispositions:')[-1].split(';; Hard regs used')[0])) if 'dispositions' in gtxt else {}
ftxt = open(n + 'flow').read() if os.path.exists(n + 'flow') else ''
m = re.search(r'Basic block 0:.*?Registers live at start:([^\n]*)', ftxt, re.S); live0 = set(m.group(1).split()) if m else set()
ltxt = open(n + 'lreg').read() if os.path.exists(n + 'lreg') else ''
for r, ps in sorted(pairs.items()):
    for P in sorted(ps, key=int):
        lm = re.search(r'^Register %s used[^\n]*' % P, ltxt, re.M)
        A.append('pin $%s -> pseudo %s: alloc=%s hard=%s live_at_entry=%s | %s' % (
            r, P, 'global' if P in galloc else ('local' if P in disp else 'none'), disp.get(P, '-'),
            P in live0, lm.group(0) if lm else 'no lreg line'))
if not pairs: A.append('no pin->pseudo pair found')
# first post-greg insn whose hard regs differ (orig vs nopin)
a, b = seq(o + 'greg', hard), seq(n + 'greg', hard)
k = next((i for i in range(min(len(a), len(b))) if a[i] != b[i]), None)
if k is not None: A.append('greg first hard-reg diff insn #%d: orig %s | nopin %s' % (k, a[k][:160], b[k][:160]))
open(D + 'analysis.txt', 'w').write('\n'.join(A) + '\n')
print(tag); print('\n'.join(A))
# 3.43 T4: first divergent pass and whether the divergence runs unbroken through combine
first = next((p for p, s in vec if not s), None)
ci = PASSES.index('combine')
surv = None if first is None else (PASSES.index(first) <= ci and all(not dict(vec)[q] for q in PASSES[PASSES.index(first):ci + 1]))
A2 = ['first divergent pass: %s' % (first or 'none'), 'survives combine: %s' % surv]
open(D + 'analysis.txt', 'a').write('\n'.join(A2) + '\n'); print('\n'.join(A2))
# 3.43 T4: canonical diff at the first divergent pass and at combine (pin var mapped to VAR, pseudos renumbered)
for ps in ([first, 'combine'] if first else []):
    a_, b_ = canon(o + ps, 'o'), canon(n + ps, 'n')
    dl = [l for l in difflib.unified_diff(a_, b_, 'orig.' + ps, 'nopin.' + ps, n=1, lineterm='')]
    open(D + 'canon_diff_%s.txt' % ps, 'w').write('\n'.join(dl) + '\n')
    print('-- canon %s: orig %d insns, nopin %d insns, diff lines %d' % (ps, len(a_), len(b_), len(dl)))
    print('\n'.join(x[:200] for x in dl[:int(os.environ.get('SHOWN', '14'))]))

# passdiff / ctxdiff modes (were 3.43 T4 passdiff.py, ctxdiff.py): diff the canonical passes of MODE_DIR
if MODE_DIR:
    sys.stdout = _stdout
    if opt.passdiff:
        for ps in ['rtl', 'jump', 'cse', 'loop', 'cse2', 'flow', 'combine']:
            a, b = canon(D + 'd_orig/' + ps, 'o'), canon(D + 'd_nopin/' + ps, 'n')
            dl = [l for l in difflib.unified_diff(a, b, n=0, lineterm='') if l[:1] in '+-' and l[:3] not in ('---', '+++')]
            print('== %s orig %d nopin %d' % (ps, len(a), len(b)))
            for l in dl[:8]: print('  ' + l[:170])
    else:
        ps = opt.ctxdiff[1]; nctx = int(opt.ctxdiff[2]) if len(opt.ctxdiff) > 2 else 3
        a, b = canon(D + 'd_orig/' + ps, 'o'), canon(D + 'd_nopin/' + ps, 'n')
        for l in difflib.unified_diff(a, b, 'orig', 'nopin', n=nctx, lineterm=''): print(l[:170])
