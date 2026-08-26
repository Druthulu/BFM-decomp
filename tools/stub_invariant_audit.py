#!/usr/bin/env python3
"""R39 negative control for the internal-j (jrel) comparer change: INCLUDE_ASM pastes the ORIGINAL
assembly, so for EVERY stub the build object's bytes ARE the target .s bytes and diff_object_s MUST be 0.
Also quotes the denominator (R41): how many stubs actually carry an internal `j` with a .text reloc."""
import sys, os, glob, json, collections
from multiprocessing import Pool
sys.path.insert(0, 'tools'); import corpus, masked_diff
def objs_for(binary, tu):
    stem = os.path.basename(tu)[:-2]
    c = sorted(glob.glob('build/src/%s/%s.o' % (binary, stem), recursive=True))
    return c or sorted(glob.glob('build/**/%s.o' % stem, recursive=True))
def one(args):
    b, fn, tu, s_path = args
    objs = objs_for(b, tu)
    if not objs: return (b, fn, 'NO-OBJ', 0, 0)
    try:
        mine = masked_diff.insns_from_object(objs[0], fn)
        tgt = masked_diff.insns_from_s(s_path)
    except Exception as e:
        return (b, fn, 'ERR:%r' % e, 0, 0)
    nj = sum(1 for i in mine if i.get('jrel') is not None)
    return (b, fn, masked_diff.diff_object_s(mine, tgt), nj, len(mine))
jobs = []
import progress
for b in progress.BINARIES:
    try:
        for st in (corpus.stubs(b).values() if isinstance(corpus.stubs(b), dict) else corpus.stubs(b)):
            jobs.append((b, st.symbol, st.path, st.asm_path))
    except Exception as e:
        print('skip', b, e)
print('stubs enumerated:', len(jobs))
with Pool(8) as p: res = p.map(one, jobs, chunksize=8)
bad = [r for r in res if r[2] != 0]
withj = sum(1 for r in res if r[3]); totj = sum(r[3] for r in res if isinstance(r[3], int))
print('checked %d stubs | nonzero %d | stubs with internal-j(.text reloc) %d | such j instructions %d' % (len(res), len(bad), withj, totj))
c = collections.Counter(str(r[2])[:30] for r in bad); print(c.most_common(8))
for r in bad[:12]: print('  ', r)
json.dump(res, open(".run/stub_invariant_audit.json", "w"))
