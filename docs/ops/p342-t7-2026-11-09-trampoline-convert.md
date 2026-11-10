# 3.42 T7 — 2026-11-09: the trampoline-family conversion scripts (archived from scratch)

- What: T7.c1 turned the 20 trampoline families (config/verbatim_manifest.json PERMANENT in-function rows) into one parameterized header each, `src/shared/ov/func_<VRAM>.h` (SHARED_FN + SHARED_SLOT, stringified into the asm by SHARED_STR; cookbook C0559). Every header names this file as its generator.
- One-shot: run once from the repo root on commit fefc443d16 (`analyze.py` writes `.run/3.42/T7/insts.json`, then `convert.py` rewrites the sites and headers). The private copies it read are gone, so it cannot be rerun; kept verbatim as the provenance record (rule T3), not as a tool.
- The headers are hand-maintained since T7.c1; edit them, never regenerate.

## analyze.py

```python
"""T7.c1 scratch: per family, every instance (binary, addr, h_exact, form, tu, line..end) from share_census's own scanner."""
import sys, json, collections, re
sys.path.insert(0, 'tools')
import share_census as sc
rows = json.load(open('config/verbatim_manifest.json')); rows = rows if isinstance(rows, list) else rows.get('rows')
FAMS = [r['fn'] for r in rows if '0x1F8003FC' in r.get('why', '') and r['copies']['private_tus'] == 133]
aliases, dirs = sc.fleet_and_dirs()
forms, _ = sc.build_forms(aliases, dirs, 16)
out = {}
for fn in FAMS:
    addr = int(fn[5:], 16); insts = []
    for a in aliases:
        sr = {r[0]: r for r in sc.sig_rows(a)}
        if addr not in sr: continue
        rec = forms.get(a, {}).get(addr)
        insts.append(dict(binary=a, addr=addr, h=sr[addr][2], name=sr[addr][3], form=rec and rec['form'], tu=rec and rec.get('tu'),
                          line=rec and rec.get('line'), end=rec and rec.get('end'), header=rec and rec.get('header')))
    out[fn] = insts
    print(fn, len(insts), dict(collections.Counter(i['form'] for i in insts)), 'tus', len({i['tu'] for i in insts if i['form']=='def'}),
          'hdr', {i['header'] for i in insts if i['header']}, 'distinct h', len({i['h'] for i in insts}))
json.dump(out, open('.run/3.42/T7/insts.json', 'w'), indent=0)
```

## convert.py

```python
"""T7.c1 scratch (not a tool): share the scratchpad trampoline families — one src/shared/ov/F.h each, parameterized by
SHARED_FN (the site's name) and SHARED_SLOT (the site's result datum). Reads .run/3.42/T7/insts.json (analyze.py, fresh
census forms of the COMMITTED tree). Usage: convert.py F [F ...] [--apply]."""
import sys, os, re, json, hashlib, subprocess, collections
sys.path.insert(0, 'tools')
import share_census as sc
import shared_lock

COMMIT = subprocess.check_output(['git', 'rev-parse', '--short=10', 'HEAD'], text=True).strip()
SIG = {'func_8014D3E0': 'void SHARED_FN(s32 _arg0)', 'func_8014ED28': 'void SHARED_FN(s32 _arg0)',
       'func_8014FBC0': 's32 SHARED_FN()', 'func_8014F6F4': 'int SHARED_FN(void)', 'func_80150480': 's32 SHARED_FN(s32 _arg0)',
       'func_8014E934': 'void SHARED_FN(s32 _arg0)', 'func_8014F468': 's32 SHARED_FN(void)',
       'func_8014FA04': 'void SHARED_FN(s32 a0)', 'func_80150A70': 'void SHARED_FN(s32 a0)'}   # fixsig.py: first run missed the last 3
# minority binaries' prototypes aligned to the family signature (no direct calls there; a K&R `()` decl is compatible and stays)
ALIGN = [(r'extern void func_8014D3E0\(void\);', 'extern void func_8014D3E0(s32 _arg0);'),
         (r'extern void func_8014ED28\(void\);', 'extern void func_8014ED28(s32 _arg0);'),
         (r'extern void func_8014FBC0\(void\);', 'extern s32 func_8014FBC0();')]
ALIGN_BINS = ['ov_MAIN_012', 'ov_SC02_037', 'ov_SC03_107', 'ov_SC07_006', 'ov_SC07_007', 'ov_SC07_010', 'ov_SC07_011']
DATUM = re.compile(r'%%(?:hi|lo)\((\w+)\)')
BEXT = re.compile(r'^[ \t]*extern[^;]*;[ \t]*\n', re.M)

fams = [a for a in sys.argv[1:] if not a.startswith('--')]
apply = '--apply' in sys.argv
insts = json.load(open('.run/3.42/T7/insts.json'))
files = {}
def lines(p):
    if p not in files: files[p] = open(p).read().split('\n')
    return files[p]

edits = collections.defaultdict(list)       # tu -> [(first_line, last_line, [new lines])]  (1-based, inclusive)
headers, registry, old_headers = {}, {}, set()
for F in fams:
    L = insts[F]
    defs = {}
    for i in L:
        if i['form'] == 'def':
            defs[(i['tu'], i['line'], i['end'])] = None
    assert len({k[0] for k in defs}) == 133, (F, len(defs))
    canon = None; canon_ext = False
    for (tu, a, b) in sorted(defs):
        ls = lines(tu)
        txt = '\n'.join(ls[a - 1:b])
        ds = set(DATUM.findall(txt))
        assert len(ds) == 1, (F, tu, ds)
        d = ds.pop()
        body = txt[txt.index('{'):]
        body = BEXT.sub('', body)
        assert len(re.findall(r'\b%s\b' % d, body)) == len(DATUM.findall(body)), (F, tu, 'datum outside %hi/%lo')
        gen = re.sub(r'\b%s\b' % d, '" SHARED_STR(SHARED_SLOT) "', body)
        if canon is None or (canon_ext and not BEXT.search(txt)):
            canon, canon_ext = gen, bool(BEXT.search(txt))
        assert re.sub(r'\s+', ' ', gen) == re.sub(r'\s+', ' ', canon), (F, tu, 'body differs')
        first = a
        name = F
        prev = ls[a - 2] if a >= 2 else ''
        am = re.match(r'\s*\w+\s+(aF[0-9A-F]{8})\s*\([^)]*\)\s*__asm__\s*\(\s*"%s"\s*\)\s*;\s*$' % F, prev)
        if am:
            first = a - 1
        rel = '../shared/ov/'
        edits[tu].append((first, b, [f'#define SHARED_FN {name}', f'#define SHARED_SLOT {d}', f'#include "{rel}{F}.h"',
                                     '#undef SHARED_SLOT', '#undef SHARED_FN']))
    # the old partial header's includers
    olds = {i['header'] for i in L if i['form'] == 'include'}
    assert len(olds) == 1
    old = olds.pop(); old_headers.add(old)
    od = set(DATUM.findall(open(old).read())); assert len(od) == 1; od = od.pop()
    base = os.path.basename(old)
    for i in L:
        if i['form'] != 'include': continue
        tu = i['tu']
        ls = lines(tu)
        if any(e[0] == i['line'] for e in edits[tu]): continue      # twins share the TU
        ln = ls[i['line'] - 1]
        m = re.match(r'\s*#\s*include\s+"([^"]*)%s"\s*$' % re.escape(base), ln)
        assert m, (tu, i['line'], ln)
        edits[tu].append((i['line'], i['line'], [f'#define SHARED_FN {F}', f'#define SHARED_SLOT {od}', f'#include "{m.group(1)}{F}.h"',
                                                 '#undef SHARED_SLOT', '#undef SHARED_FN']))
    head = SIG.get(F, 'void SHARED_FN(void)')
    sigs = {i['binary']: i for i in L}
    n_h = len({i['h'] for i in L})
    hdr = (f"/* {F} — scratchpad stack-switch trampoline family (fleet slot 0x{F[5:].upper()}; {len(L)} instances, {n_h} distinct\n"
           f" * h_exact: each copy stores its callee's result in its own overlay datum). ONE source, parameterized: the site\n"
           f" * defines SHARED_FN (its name) and SHARED_SLOT (its result datum, spelled into the asm by SHARED_STR), includes\n"
           f" * this, undefines both. Members: config/dedup.us.yaml S_{F} (h_text); verbatim row ov_* {F}.\n"
           f" * Generated by .run/3.42/T7/convert.py (3.42 T7.c1) from commit {COMMIT}. */\n"
           f"#ifndef SHARED_STR\n#define SHARED_STR_(x) #x\n#define SHARED_STR(x) SHARED_STR_(x)\n#endif\n\n"
           f"{head}\n{canon}\n")
    headers[f'src/shared/ov/{F}.h'] = hdr
    th = hashlib.sha1(re.sub(r'\s+', ' ', head + canon).strip().encode()).hexdigest()
    mem = sorted((i['binary'], i['addr'], F, i['h']) for i in L)
    registry[F] = (th, f'src/shared/ov/{F}.h', mem)

# overlapping edits guard
for tu, es in edits.items():
    es.sort()
    for x, y in zip(es, es[1:]):
        assert x[1] < y[0], (tu, x, y)
print('families', len(fams), 'TUs', len(edits), 'site edits', sum(len(v) for v in edits.values()), 'old headers', len(old_headers))
if not apply:
    sys.exit(0)

with shared_lock.hold(exclusive=True, announce='T7.c1 convert'):
    for p, t in headers.items():
        assert not os.path.exists(p), p
        open(p, 'w').write(t)
    for tu, es in edits.items():
        ls = lines(tu)
        for a, b, new in sorted(es, reverse=True):
            ls[a - 1:b] = new
        t = '\n'.join(ls)
        if any(tu.startswith(f'src/{b}/') for b in ALIGN_BINS):
            for pat, rep in ALIGN:
                t = re.sub(pat, rep, t)
        open(tu, 'w').write(t)
    # alignment in the minority binaries' other TUs
    for b in ALIGN_BINS:
        for root, _d, fs in os.walk(f'src/{b}'):
            for f in fs:
                p = os.path.join(root, f)
                if p in edits or not f.endswith(('.c', '.h')): continue
                t = open(p).read(); t2 = t
                for pat, rep in ALIGN:
                    t2 = re.sub(pat, rep, t2)
                if t2 != t: open(p, 'w').write(t2)
    subprocess.check_call(['git', 'rm', '-q'] + sorted(old_headers))
    # registry: each S_func_<F> h_exact group -> an h_text group listing every instance (own h_exact each)
    p = 'config/dedup.us.yaml'
    y = open(p).read()
    for F, (th, src, mem) in registry.items():
        m = re.search(r'^  - id: S_%s\n(?:(?!  - id: ).*\n)*' % F, y, re.M)
        assert m and y.count(f'  - id: S_{F}\n') == 1, F
        blk = (f'  - id: S_{F}\n    tier: h_text\n    hash: {th}\n    source: {src}\n    func: SHARED_FN\n    members:\n' +
               ''.join(f'      - {{ binary: {b}, vram: 0x{a:08X}, name: {n}, h_exact: {h} }}\n' for b, a, n, h in mem))
        y = y[:m.start()] + blk + y[m.end():]
    open(p, 'w').write(y)
print('applied')
```
