#!/usr/bin/env python3
"""Derive the P30 S7 (wave-4) target manifest — nothing asserted, everything derived.

The §135 law that motivated this file: wave 1's args were hand-transcribed and pattern-filled
`_jr_*` split names into overlays that have none; three agents lost time rediscovering the real
paths. So every path here comes from `corpus.stubs` (which reads the self-describing INCLUDE_ASM
line) and is verified present on disk before it is written out. The manifest is then PASTED into
the Workflow call, never retyped.

Slices (the S6-close queue, re-derived at HEAD):
  A  >=10 members, 61-120 ins   -> best per-target value (Opus direct >=90 ins)
  B  10-19 members, <=60 ins    -> volume lane (Haiku)
Both are `kind=modal` (no member matched anywhere, so no sweep can reach them) and non-jr.
"""
import json, os, sys, collections
sys.path.insert(0, 'tools')
import corpus

d = json.load(open('.run/family_hseq.json'))
fams = d['families']

B = [f for f in fams
     if f.get('exemplar') and f['exemplar']['kind'] == 'modal'
     and not f['has_mid_jr'] and f['n_matched'] == 0]

SLICES = {
    'A': lambda f: f['n_members'] >= 10 and 61 <= f['nins'] <= 120,
    'B': lambda f: 10 <= f['n_members'] <= 19 and f['nins'] <= 60,
}

o0 = corpus.o0_sources()
out, dropped = [], []
stub_cache = {}

for name, pred in SLICES.items():
    for f in sorted([x for x in B if pred(x)],
                    key=lambda x: -x['byte_weight_templatable']):
        ex = f['exemplar']
        ov, addr = ex['ov'], int(ex['addr'], 16)
        try:
            st = stub_cache.setdefault(ov, corpus.stubs(ov))
        except Exception as e:
            dropped.append((ov, ex['addr'], f'corpus refused: {e}'))
            continue
        rec = st.get(addr)
        if rec is None:
            dropped.append((ov, ex['addr'], 'not a live stub (banked since the map was built)'))
            continue
        asm = rec.asm_path
        tu = rec.path
        if not os.path.exists(asm):
            dropped.append((ov, ex['addr'], f'missing .s {asm}'))
            continue
        if not os.path.exists(tu):
            dropped.append((ov, ex['addr'], f'missing TU {tu}'))
            continue
        seed = f'.run/ghidra_c/{rec.symbol}.c'
        nins = f['nins']
        out.append({
            'slice': name,
            'fn': rec.symbol,
            'addr': ex['addr'],
            'ov': ov,
            'asm': asm,
            'asm_subdir': rec.asm_dir,
            'tu': tu,
            'o0': tu in o0,
            'nins': nins,
            'members': f['n_members'],
            'templ_ins': f['byte_weight_templatable'] // 4,
            'diff_class': f['diff_class'],
            'seed': seed if os.path.exists(seed) else None,
            # §136i ladder (Drew 2026-08-03): haiku <=50 / sonnet 50-120 / opus >=120
            'model': 'opus' if nins >= 120 else ('sonnet' if nins > 50 else 'haiku'),
        })

json.dump(out, open('.run/s7_targets.json', 'w'), indent=1)

by = collections.Counter(t['slice'] for t in out)
mdl = collections.Counter(t['model'] for t in out)
print(f"targets {len(out)}  (A={by['A']} B={by['B']})  models={dict(mdl)}")
print(f"templatable ins  {sum(t['templ_ins'] for t in out):,}")
print(f"member-slots     {sum(t['members'] for t in out):,}")
print(f"seeded           {sum(1 for t in out if t['seed'])}/{len(out)}")
print(f"-O0 TUs          {sum(1 for t in out if t['o0'])}")
print(f"distinct binaries{len({t['ov'] for t in out}):>4}")
print(f"DROPPED          {len(dropped)}")
for x in dropped[:15]:
    print("   drop:", x)
