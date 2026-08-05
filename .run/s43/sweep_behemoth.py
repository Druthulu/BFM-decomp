#!/usr/bin/env python3
"""P30 S43 task #10 — measure the 41 permuter-unblocked behemoth drafts against the RIGHT body.

Until today the permuter was silently dead on every draft carrying `#define ... __asm__` + `#include`
(p16_permute's cpp fallback). 41 of those 63 drafts are behemoth renderer drafts and have never had a
working permuter run. func_8017EF68 came out of this pool at 2-of-969.

TRAP THIS GUARDS: the same address holds DIFFERENT bodies in different overlays (S43: 0x8017C6F4 is
15 ins in three overlays and 948 in four others; 0x8017EF68 is 12 vs 970). A draft measured against
the wrong variant reads as garbage. So: measure every draft against EVERY variant and keep the best.
"""
import glob, os, re, subprocess, json, sys

DIRS = ('.run/drafts-behemoth3', '.run/drafts-p30beh', '.run/drafts-behemoth2')
DEF = re.compile(r'^\s*#\s*define\b[^\n]*__asm__', re.M)
INC = re.compile(r'^\s*#\s*include', re.M)
FN = re.compile(r'\bfunc_[0-9A-Fa-f]{8}\b')


def variants(fn):
    """[(binary, asm_subdir, nins)] for every overlay that has this function."""
    out = []
    for p in subprocess.run(['find', 'asm', '-name', f'{fn}.s'],
                            capture_output=True, text=True).stdout.split():
        parts = p.split('/')
        if len(parts) < 5:
            continue
        n = sum(1 for l in open(p, errors='replace') if l.lstrip().startswith('/*'))
        out.append((parts[1], '/'.join(parts[:4]), n))
    return sorted(out, key=lambda t: -t[2])


def measure(fn, draft, subdir):
    p = subprocess.run(['.venv/bin/python', 'tools/match_one.py', fn, '--c', draft,
                        '--asm-subdir', subdir], capture_output=True, text=True, timeout=400)
    first = (p.stdout or p.stderr or '?').strip().splitlines()
    first = first[0] if first else '?'
    if 'MATCH' in first and 'DIFF' not in first:
        return 0, first
    m = re.search(r'(\d+) mismatched', first)
    return (int(m.group(1)) if m else None), first


rows = []
drafts = []
for d in DIRS:
    for p in sorted(glob.glob(d + '/*.c')):
        t = open(p, errors='replace').read()
        if DEF.search(t) and INC.search(t):
            drafts.append(p)
print(f'{len(drafts)} permuter-unblocked behemoth drafts', flush=True)

for p in drafts:
    names = FN.findall(os.path.basename(p)) or FN.findall(open(p, errors='replace').read()[:4000])
    if not names:
        print(f'  {p}: no function name'); continue
    fn = names[0]
    best = None
    for (b, sub, n) in variants(fn):
        try:
            score, line = measure(fn, p, sub)
        except subprocess.TimeoutExpired:
            continue
        if score is not None and (best is None or score < best[0]):
            best = (score, b, sub, n)
    if best:
        rows.append({'draft': p, 'fn': fn, 'closeness': best[0],
                     'binary': best[1], 'asm_subdir': best[2], 'nins': best[3]})
        print(f'  {fn:18s} best={best[0]:5d} of {best[3]:4d} ins  in {best[1]}  [{os.path.basename(os.path.dirname(p))}]', flush=True)
    else:
        print(f'  {fn:18s} no measurable variant', flush=True)

rows.sort(key=lambda r: r['closeness'])
json.dump(rows, open('.run/s43/behemoth_sweep.json', 'w'), indent=1)
print('\n=== RANKED (permuter-tractable first) ===')
for r in rows[:20]:
    print(f"  {r['fn']}  close={r['closeness']}  nins={r['nins']}  {r['binary']}")
