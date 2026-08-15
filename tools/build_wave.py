#!/usr/bin/env python3
"""Build the next campaign wave from a card pool (adapt | weak), in the proven wave-B shape.

Selection: still an open stub (derived from the corpus oracle, R32/R33 — never a stale label),
not already spent in a prior wave, ranked by fleet leverage (reach desc, then similarity desc).
Model routed by size per the subagent ladder (haiku <=50 ins, sonnet 51-120); larger is left to a
targeted lane, not a bulk wave.

MUST be run with NO gate in flight — gate_lane transiently substitutes drafts into src/, so a
concurrent read of corpus.stubs() reports substituted functions as already-banked (R35).

Usage: build_wave.py <pool: adapt|weak> <out.json> [N]
"""
import json, sys, collections, subprocess
sys.path.insert(0, 'tools')
import corpus

pool = sys.argv[1]
out = sys.argv[2]
n = int(sys.argv[3]) if len(sys.argv) > 3 else 48

# NB: invoke pgrep WITHOUT a shell. With shell=True the wrapping `sh -c` carries the pattern in
# its own command line and pgrep -f matches it — the self-match false positive (cookbook §174
# ops note, same class as the grinder pgrep). pgrep excludes only its own PID, not its parent.
_busy = subprocess.run(['pgrep', '-f', 'tools/(gate_stage|dedup_propagate|gate_lane)'],
                       capture_output=True, text=True)
if _busy.returncode == 0 and _busy.stdout.strip():
    sys.exit(f"REFUSING: a gate is in flight (pids {_busy.stdout.split()}) — corpus.stubs() would "
             f"misreport substituted drafts as banked (R35). Wait for it.")

PRIORS = ['.run/wave_p31a_cards.json', '.run/wave_p31b_cards.json', '.run/wave_p31c_cards.json',
          '.run/wave_p31d_cards.json', '.run/wave_p31e_cards.json', '.run/wave_p31f_cards.json',
          '.run/wave_p31g_cards.json', '.run/wave_p31h_cards.json']
taken = set()
for p in PRIORS:
    try:
        taken |= {c.get('fn') or c.get('name') for c in json.load(open(p))}
    except (FileNotFoundError, json.JSONDecodeError):
        pass

src = {'adapt': '.run/adapt_cards.json', 'weak': '.run/weak_cards.json'}[pool]
cards = json.load(open(src))

_open = {}
def is_open(binary, fn):
    if binary not in _open:
        # corpus.stubs() is addr -> Stub; the NAME lives on the record (R35: I read the
        # container, not the contract, and every card looked 'already-banked')
        _open[binary] = {st.symbol for st in corpus.stubs(binary).values()}
    return fn in _open[binary]

def model_for(nins):
    if not nins:   return 'haiku'
    if nins <= 50: return 'haiku'
    if nins <= 120: return 'sonnet'
    return None

sel, skipped = [], collections.Counter()
for c in cards:
    fn = c.get('fn') or c.get('name')
    binary = c['binary']
    if pool == 'adapt' and c.get('klass') != 'SMALL-EDIT':
        skipped['not-small-edit'] += 1; continue
    if fn in taken:
        skipped['already-waved'] += 1; continue
    m = model_for(c.get('nins'))
    if not m:
        skipped['too-big-for-wave'] += 1; continue
    if not is_open(binary, fn):
        skipped['already-banked'] += 1; continue
    rec = {'fn': fn, 'binary': binary, 'lane': pool, 'model': m,
           'nins': c.get('nins'), 'sim': c.get('sim'), 'reach': c.get('reach'),
           'sub': c.get('sub'), 'addr': c.get('addr')}
    if pool == 'adapt':
        rec.update(klass=c.get('klass'),
                   seed_path=(c.get('seed') or {}).get('path'),
                   seed_kind=(c.get('seed') or {}).get('kind'),
                   seed_name=(c.get('seed') or {}).get('name'),
                   sites=[{'at': d.get('member_at'), 'kind': d.get('kind'),
                           'member': d.get('member_disasm', []), 'seed': d.get('seed_disasm', [])}
                          for d in (c.get('diff') or [])])
    else:
        rec.update(seed=c.get('seed'), note=c.get('note'), unit_ins=c.get('unit_ins'))
    sel.append(rec)

sel.sort(key=lambda c: (-(c.get('reach') or 0), -(c.get('sim') or 0)))
wave = sel[:n]
json.dump(wave, open(out, 'w'), indent=1)
print(f"pool={pool} total={len(cards)} candidates={len(sel)} skipped={dict(skipped)} -> wave {len(wave)} -> {out}")
if wave:
    print("models:", dict(collections.Counter(c['model'] for c in wave)))
    ni = [c['nins'] for c in wave if c.get('nins')]
    if ni: print(f"nins {min(ni)}-{max(ni)}")
    print("binaries:", len({c['binary'] for c in wave}))
    json.dump([{'fn': c['fn'], 'binary': c['binary'], 'lane': c['lane'], 'model': c['model'],
                'sim': c.get('sim'), 'seed_path': c.get('seed_path'), 'seed_name': c.get('seed_name')}
               for c in wave], open(out.replace('.json', '_index.json'), 'w'))
