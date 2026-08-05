#!/usr/bin/env python3
"""Derive the wave pool from the family map the corpus.stubs way (§138 rule 4).

WHY THIS EXISTS (and why it is not a transcription):
  The family map's `exemplar` field is an IN-FAMILY pointer and can name an ALREADY-BANKED
  instance — ranking off it hides whole families (measured: 16,696 ins -> 41,023 on the same map).
  So every number here is DERIVED: for each family we ask corpus.stubs which members are still
  open, and rank by (open members) x nins.  The map supplies structure; the corpus supplies truth.

  Also §138 rule 2: two targets in ONE TU means the first to bank puts its type tags in the
  second's way (wave 4's only failure).  So we allow at most one target per (overlay, TU).

Usage:  .venv/bin/python .run/w6_pool.py <N> <out.json> [--exclude-attempted]
"""
import sys, os, json, glob, collections
sys.path.insert(0, 'tools')
import corpus

N       = int(sys.argv[1]) if len(sys.argv) > 1 else 16
OUT     = sys.argv[2] if len(sys.argv) > 2 else '.run/w6_wave.json'

# --- the standing exclusion ledger (CURRENT_PHASE.md ▶ RESUME, item 1) -----------------------
WALLS = {0x801412a8, 0x80178004, 0x80144b9c}                      # the 3 permanent walls
LEDGERED = {0x8017c294, 0x8017f7b4, 0x801898e4, 0x80186e24,       # ledgered residuals
            0x801758fc, 0x80132018, 0x8018a808}                   # + probed-not-templatable
EXCLUDE = WALLS | LEDGERED

# --- previously-attempted targets that are STILL open == they failed their gate ---------------
attempted = set()
# NB the glob must be `*_wave.json`, not `s*_wave.json`: wave 6's own manifest is `w6_wave.json`,
# so an s-only glob would silently re-offer every target wave 6 already failed.
#
# BUT "attempted" must mean A WAVE THAT RAN, not A MANIFEST THAT EXISTS. Staging a manifest and then
# re-deriving a bigger one made the second run exclude the first's targets — the 64-target pool came
# back MISSING its 16 best entries (pool 2,928 -> 2,913 -> 2,893 across three derivations, each one
# poisoned by the last). So require the wave's drafts directory to exist: `<tag>_wave.json` ran iff
# `.run/<tag>/` holds drafts. A manifest with no drafts dir is a PLAN, not a result.
for p in sorted(glob.glob('.run/*_wave.json')) + ['.run/s10.json']:
    if not os.path.exists(p):
        continue
    tag = os.path.basename(p).replace('_wave.json', '').replace('.json', '')
    if not glob.glob(f'.run/{tag}/*/*.c'):
        print(f"  (skip {p}: staged but never run — no drafts under .run/{tag}/)", file=sys.stderr)
        continue
    try:
        for t in json.load(open(p)):
            fn = t.get('fn') or t.get('func') or ''
            if fn.startswith('func_'):
                attempted.add(int(fn[5:], 16))
    except Exception as e:
        print(f"  (skip {p}: {e})", file=sys.stderr)

fam = json.load(open('.run/family_hseq.json'))['families']

# --- stubs per overlay, fetched once ----------------------------------------------------------
stub_cache = {}
def stubs(ov):
    if ov not in stub_cache:
        try:
            stub_cache[ov] = corpus.stubs(ov)
        except Exception:
            stub_cache[ov] = {}
    return stub_cache[ov]

rows = []
for f in fam:
    nins = f['nins']
    if nins < 40:                      # below this the head is not worth an agent
        continue
    open_sites = []
    for ov, addr_s in f['members']:
        addr = int(addr_s, 16)
        if addr in EXCLUDE:
            open_sites = []            # a walled/ledgered address disqualifies the family
            break
        st = stubs(ov)
        if addr in st:
            open_sites.append((ov, addr, st[addr]))
    if not open_sites:
        continue
    if any(a in attempted for _, a, _ in open_sites):
        continue                       # tried before and still open => it failed; not fresh fuel
    rows.append({
        'h_seq'    : f['h_seq'][:12],
        'nins'     : nins,
        'open'     : len(open_sites),
        'members'  : f['n_members'],
        'ti'       : len(open_sites) * nins,       # OPEN templatable instructions — the ranking key
        'diff'     : f['diff_class'],
        'addr_tag' : f['addr_tag'],
        'mid_jr'   : f['has_mid_jr'],
        'sites'    : open_sites,
    })

rows.sort(key=lambda r: -r['ti'])

# --- pick N, at most one per (overlay, TU) ----------------------------------------------------
picked, used_tu = [], set()
for r in rows:
    if len(picked) >= N:
        break
    for ov, addr, st in r['sites']:
        key = (ov, st.path)
        if key in used_tu:
            continue
        used_tu.add(key)
        picked.append({
            'fn'   : f'func_{addr:08X}',
            'ov'   : ov,
            'sub'  : st.asm_dir,
            'tu'   : st.path,
            'n'    : r['nins'],
            'm'    : r['open'],
            'ti'   : r['ti'],
            'diff' : r['diff'],
            'tag'  : r['addr_tag'],
            'model': 'sonnet',
            'seed' : len(picked) % 2,
        })
        break

json.dump(picked, open(OUT, 'w'), indent=1)

tot_pool = sum(r['ti'] for r in rows)
print(f"POOL   : {len(rows)} fresh families / {tot_pool:,} OPEN templatable ins "
      f"(excluded {len(EXCLUDE)} ledgered addrs, {len(attempted)} previously-attempted)")
print(f"PICKED : {len(picked)} targets / {sum(p['ti'] for p in picked):,} templatable ins -> {OUT}\n")
print(f"{'fn':<16}{'overlay':<15}{'nins':>5}{'open':>6}{'templ ins':>11}  {'class':<7}{'tag':<14}TU")
for p in picked:
    print(f"{p['fn']:<16}{p['ov']:<15}{p['n']:>5}{p['m']:>6}{p['ti']:>11,}  "
          f"{p['diff']:<7}{p['tag']:<14}{os.path.basename(p['tu'])}")
