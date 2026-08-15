#!/usr/bin/env python3
"""Build a campaign wave from the FRONTIER ATLAS, optimized for gate throughput.

Why this exists (P31, 2026-08-14): the pre-baked adapt/weak card piles are the smallest,
best-seeded tail (12-42 ins). Drawing from them banks ~1,440 ins/wave against 635,744 open —
0.011pp of fleet per wave. The atlas knows where the mass actually is (cousin-multi 294k ins,
cold 183k, main-only 38k) and what lever each group needs.

TWO selection principles, both measured:
  1. GATE COST SCALES WITH (binary, TU) GROUPS, NOT DRAFTS. Each group is a whole-binary rebuild.
     Wave C was 35 drafts over 27 groups = 1.3 drafts/rebuild, ~50 min of gate for 32 banks.
     So: CONCENTRATE the wave in few binaries. This is free throughput.
  2. MASS BEATS COUNT for the instruction-weighted metric — prefer bigger functions where a seed
     exists, but keep them inside the model ladder's competence.

Selection: open stubs (derived from corpus, R32/R33), not spent in a prior wave, from atlas
groups whose lever is agent-draftable; ranked by binary concentration then instruction mass.

MUST NOT run while a gate is in flight (R35 — corpus.stubs() misreports substituted drafts).

Usage: build_wave_atlas.py <out.json> [N] [--max-bins K] [--min-ins M] [--levers a,b,c]
"""
import json, sys, collections, subprocess, argparse
sys.path.insert(0, 'tools')
import corpus

ap = argparse.ArgumentParser()
ap.add_argument('out')
ap.add_argument('n', nargs='?', type=int, default=96)
ap.add_argument("--max-bins", type=int, default=12, help="concentrate into this many GATE GROUPS (binary,TU)")
ap.add_argument('--min-ins', type=int, default=0)
ap.add_argument('--max-ins', type=int, default=120, help='above this the bulk ladder stops being honest')
ap.add_argument('--levers', default='head-crack,seeded-crack,redraft,len-vein,integration,family-sweep,tiny-direct',
                help='agent-draftable levers; UNKNOWN/tell/jtbl/o0/cc1 need their own lanes')
ap.add_argument('--atlas', default='.run/atlas.json')
ap.add_argument('--exclude-bins', default='main',
                help='comma-separated binaries to skip. main is excluded BY DEFAULT: it is blocked '
                     'on a link-resolution defect (a byte-correct C fn retargets a jal between game '
                     'code and a linked PsyQ archive object), not on matching — see CURRENT_PHASE.md')
a = ap.parse_args()
EXCLUDE = {b for b in a.exclude_bins.split(',') if b}

busy = subprocess.run(['pgrep', '-f', 'tools/(gate_stage|dedup_propagate|gate_lane)'],
                      capture_output=True, text=True)
if busy.returncode == 0 and busy.stdout.strip():
    sys.exit(f"REFUSING: gate in flight (pids {busy.stdout.split()}) — corpus.stubs() would misreport (R35).")

PRIORS = ['.run/wave_p31%s_cards.json' % c for c in 'abcdefghijkl']
taken = set()
for p in PRIORS:
    try:
        taken |= {c.get('fn') or c.get('name') for c in json.load(open(p))}
    except (FileNotFoundError, json.JSONDecodeError):
        pass

levers = set(a.levers.split(','))
atlas = json.load(open(a.atlas))

_open = {}
def _stubmap(binary):
    if binary not in _open:
        # corpus.stubs() is addr -> Stub; the NAME lives on the record
        _open[binary] = {st.symbol: st for st in corpus.stubs(binary).values()}
    return _open[binary]

def is_open(binary, fn):
    return fn in _stubmap(binary)

def home_tu(binary, fn):
    """The stub's home .c — this is the GATE GROUP KEY (gate_lane groups by (binary, src))."""
    st = _stubmap(binary).get(fn)
    return st.path if st else None

def model_for(nins):
    if nins <= 50:  return 'haiku'
    if nins <= 120: return 'sonnet'
    return 'opus'

cands, skipped = [], collections.Counter()
for g in atlas['groups']:
    if g['lever'] not in levers:
        skipped['lever-not-in-lane'] += g['inst']; continue
    ex = g.get('exemplar') or {}
    seed = (g.get('seed') or {}).get('norm') or (g.get('seed') or {}).get('raw') or {}
    for m in g.get('members', []):
        fn, b, nins = m.get('name'), m.get('b'), m.get('nins') or 0
        if not fn or not b:                      skipped['no-name'] += 1; continue
        if b in EXCLUDE:                         skipped['excluded-binary'] += 1; continue
        if fn in taken:                          skipped['already-waved'] += 1; continue
        if not (a.min_ins <= nins <= a.max_ins): skipped['out-of-band'] += 1; continue
        if not is_open(b, fn):                   skipped['already-banked'] += 1; continue
        sub = corpus.asm_path(b, fn)
        if not sub:                              skipped['no-asm'] += 1; continue
        cands.append({
            'tu': home_tu(b, fn),
            'fn': fn, 'binary': b, 'lane': 'mass', 'model': model_for(nins), 'nins': nins,
            'addr': m.get('a'), 'sub': __import__('os').path.dirname(sub),
            'gid': g['gid'], 'lever': g['lever'], 'confidence': g.get('confidence'),
            'lever_alts': g.get('lever_alts', []),
            'exemplar': {'binary': ex.get('b'), 'fn': ex.get('name'), 'nins': ex.get('nins')},
            'seed_sim': seed.get('sim'),
        })

# principle 1: CONCENTRATE ON GATE GROUPS. gate_lane groups by (binary, home .c) and each group
# is one whole-binary rebuild, so drafts-per-GROUP is the throughput number that matters -- not
# drafts per binary. Wave D was 42 drafts over 23 groups (1.8/group, ~40 min of gate).
by_tu = collections.defaultdict(list)
for c in cands:
    by_tu[(c['binary'], c['tu'])].append(c)
ranked = sorted(by_tu, key=lambda k: -len(by_tu[k]))[:a.max_bins]

wave = []
for k in ranked:                            # principle 2: within a group, mass first
    for c in sorted(by_tu[k], key=lambda c: -c['nins']):
        if len(wave) >= a.n: break
        wave.append(c)
    if len(wave) >= a.n: break

json.dump(wave, open(a.out, 'w'), indent=1)
tot = sum(c['nins'] for c in wave)
print(f"candidates {len(cands)} in {len(by_tu)} gate groups (skipped {dict(skipped)})")
ngroups = len({(c['binary'], c['tu']) for c in wave})
print(f"-> wave {len(wave)} drafts / {tot} ins across {len({c['binary'] for c in wave})} binaries "
      f"in {ngroups} GATE GROUPS = {len(wave)/max(ngroups,1):.1f} drafts per rebuild")
if wave:
    print("models:", dict(collections.Counter(c['model'] for c in wave)))
    print("levers:", dict(collections.Counter(c['lever'] for c in wave)))
    print("nins: %d-%d (avg %.0f)" % (min(c['nins'] for c in wave), max(c['nins'] for c in wave), tot/len(wave)))
