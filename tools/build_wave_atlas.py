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
import json, os, sys, collections, subprocess, argparse, glob
sys.path.insert(0, 'tools')
import corpus
import decl_prior as DP

ap = argparse.ArgumentParser()
ap.add_argument('out')
ap.add_argument('n', nargs='?', type=int, default=96)
ap.add_argument("--max-bins", type=int, default=12, help="concentrate into this many GATE GROUPS (binary,TU)")
ap.add_argument('--min-ins', type=int, default=0)
ap.add_argument('--max-ins', type=int, default=120, help='above this the bulk ladder stops being honest')
ap.add_argument('--levers',
                default='head-crack,seeded-crack,redraft,len-vein,integration,family-sweep,tiny-direct,UNKNOWN',
                help="agent-draftable levers; tell/jtbl/o0/cc1 need their own lanes. UNKNOWN IS IN THE "
                     "DEFAULT LANE since P31 S54 (cookbook §198): it was excluded here while the wave "
                     "PROMPT told every agent 'UNKNOWN does NOT mean hard -- it means the atlas could "
                     "not name a lever', so the tool was silently overriding the doctrine. Measured: "
                     "UNKNOWN held 607 of the 1,179 in-band members -- more than every other lane "
                     "COMBINED -- and wave W drew 73 cards from it into 3 gate groups (24.3 drafts per "
                     "rebuild vs wave V's 7.8) for 71/71 drafted and 68 banked. Cost, recorded: UNKNOWN "
                     "groups are mostly singletons, so the free sibling remap yielded ZERO.")
ap.add_argument('--atlas', default='.run/atlas.json')
ap.add_argument('--exclude-bins', default='',
                help='comma-separated binaries to skip. NOTHING is excluded by default. '
                     '(History: main used to be excluded on a "link-resolution defect" — that '
                     'diagnosis was REFUTED 2026-08-15 by a null-draft control: the false diff '
                     'reproduces with ZERO drafts substituted. main simply cannot be gated '
                     'INCREMENTALLY, because its extract runs psyq_integrate/ld_interleave and '
                     'rewrites the .ld. Draft main like any binary; gate it with '
                     'tools/gate_main.py, never gate_lane/gate_stage.)')
ap.add_argument('--rank', choices=('groups','mass','total'), default='groups',
                help="'groups' (default) ranks gate groups by MEMBER COUNT -- right for overlays, "
                     "where every (binary,TU) group costs its own rebuild. 'mass' ranks purely by "
                     "instruction size across all groups -- right for MAIN, whose gate cost is per "
                     "SLATE, not per TU: with 'groups' a wide --min-ins band fills from the "
                     "biggest-by-count group, which is the SMALLEST-by-instruction one, and the "
                     "wave silently collapses to tiny functions (measured: 60 cards / 2,604 ins "
                     "avg 43, when 46 cards / 4,829 ins avg 105 were available).")
ap.add_argument('--target-ins', type=int, default=0,
                help='size the wave by INSTRUCTION MASS: keep drawing cards until this many '
                     'instructions are selected (still capped by n). The public metric is '
                     'instruction-weighted, so this is the number that matters -- 6000+ is the '
                     'P31 S52 standard (wave O: 6,266 ins in 2 gate groups, 47/49 MATCH).')
ap.add_argument('--only-bins', default='',
                help='comma-separated allow-list; if set, ONLY these binaries are eligible. '
                     'Use --only-bins main for a main wave: gate_main.py rebuilds the whole EXE '
                     'once per SLATE, so main has no per-TU gate cost and --max-bins can be large.')
ap.add_argument('--one-per-gid', action='store_true',
                help="draft ONE card per atlas group and defer its same-gid siblings to "
                     "<out>.siblings.json for the post-bank mechanical remap "
                     "(make sig-overlays -> family_hseq.py -> family_sweep --hseq --only). "
                     "Rationale (P31 S54): a fleet-wide draw over SIBLING overlays (ov_SC04_002 vs "
                     "ov_SC04_005) fills half the wave with the SAME skeleton at two addresses -- "
                     "paying an agent twice for work the deterministic remap does for free. The "
                     "representative is the sibling in the heaviest gate group (then largest nins, "
                     "then lexical fn) so concentration is unharmed. Every deferred sibling is "
                     "written to the companion file and accounted (R32): representatives + "
                     "siblings == candidates, asserted.")
a = ap.parse_args()
EXCLUDE = {b for b in a.exclude_bins.split(',') if b}
ONLY = {b for b in a.only_bins.split(',') if b}

busy = subprocess.run(['pgrep', '-f', 'tools/(gate_stage|dedup_propagate|gate_lane)'],
                      capture_output=True, text=True)
if busy.returncode == 0 and busy.stdout.strip():
    sys.exit(f"REFUSING: gate in flight (pids {busy.stdout.split()}) — corpus.stubs() would misreport (R35).")

# R32/R33: derive the already-waved set from what is ON DISK, never from a hardcoded wave-letter
# list (the literal 'a'..'l' silently missed waves m and n and would have re-issued their cards).
# Exclude OUR OWN output: the glob matches it, so re-running the selector after an aborted or
# re-tuned build marked the previous attempt's cards as 'already waved' and silently shrank the
# pool (measured: 46 candidates instead of 60 on a re-run with identical filters).
PRIORS = [p for p in sorted(glob.glob('.run/wave_*_cards.json'))
          if os.path.abspath(p) != os.path.abspath(a.out)]
taken = set()
for p in PRIORS:
    try:
        taken |= {c.get('fn') or c.get('name') for c in json.load(open(p))}
    except (FileNotFoundError, json.JSONDecodeError, TypeError):
        pass
if not PRIORS:
    print('NOTE: no prior wave card files found — nothing filtered as already-waved', file=sys.stderr)

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

_DPIDX = DP.load()                    # symbol -> fleet declaration evidence (§196)
knn = atlas.get('knn') or {}          # exemplar key -> neighbours; 'M:' entries are BANKED (§193-A)
_TU_BODIES = {}


def _tu_bodies(tu_path):
    """{fn: body_text} for every function DEFINED in a TU (banked C only -- stubs are INCLUDE_ASM).

    Brace-matched from each definition so a symbol is attributed to the function that uses it, not
    to the file. Memoized per TU: a wave draws many cards from one .c."""
    if tu_path in _TU_BODIES:
        return _TU_BODIES[tu_path]
    out = {}
    try:
        txt = open(tu_path, errors='replace').read()
    except (OSError, TypeError):
        _TU_BODIES[tu_path] = out
        return out
    import re as _re
    for m in _re.finditer(r'^[A-Za-z_][\w \t\*]*?\b(\w+)\s*\([^;{]*\)\s*\{', txt, _re.M):
        i, depth = m.end() - 1, 0
        while i < len(txt):
            if txt[i] == '{': depth += 1
            elif txt[i] == '}':
                depth -= 1
                if depth == 0: break
            i += 1
        out[m.group(1)] = txt[m.start():i + 1]
    _TU_BODIES[tu_path] = out
    return out


_SYM = None


def tu_neighbours(binary, fn, tu_path, asm_file, topn=2):
    """Banked functions in the card's OWN TU, ranked by symbols shared with the target's asm.

    The symbols are read from the TARGET's .s (its relocation operands), so this is evidence about
    the function being drafted, not about the file. See §194-E for why the card needs this at all."""
    global _SYM
    if not tu_path or not asm_file:
        return []
    import re as _re
    if _SYM is None:
        # OPERANDS ONLY. A splat .s carries the encoded WORD in a comment column, so a naive
        # "[A-Z]\w{3,}" reads `D8FFBD27` and `CC00228E` as symbol names and the overlap score
        # becomes noise (measured: 34 "symbols" for one function, 31 of them hex words).
        # Symbols reach the .s in exactly three shapes: a jal target, and %hi()/%lo() operands.
        _SYM = _re.compile(r'\b(?:jal\s+(\w+)|%[hl][io]\(([\w+]+)\))')
    try:
        raw = _SYM.findall(open(asm_file, errors='replace').read())
    except OSError:
        return []
    want = {(a or b).split('+')[0] for a, b in raw if (a or b)}
    want.discard(fn)
    if not want:
        return []
    scored = []
    for other, body in _tu_bodies(tu_path).items():
        if other == fn:
            continue
        shared = [s for s in want if s in body]
        if len(shared) >= 2:
            scored.append((len(shared), other, sorted(shared)[:6]))
    scored.sort(key=lambda x: -x[0])
    if not scored:
        # FALL BACK TO THE BEST SINGLE SHARED SYMBOL rather than emitting nothing. One shared
        # callee is weak evidence, but the card reports the count so the agent can weigh it, and a
        # weak same-TU lead still beats the zero-locality state §194-E measured.
        weak = sorted(((len([s for s in want if s in body]), other)
                       for other, body in _tu_bodies(tu_path).items() if other != fn), reverse=True)
        if weak and weak[0][0] == 1:
            o = weak[0][1]
            body = _tu_bodies(tu_path)[o]
            return [{'fn': o, 'shared': 1, 'symbols': [s for s in sorted(want) if s in body][:6]}]
    return [{'fn': o, 'shared': n, 'symbols': syms} for n, o, syms in scored[:topn]]


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
        if ONLY and b not in ONLY:               skipped['not-in-only-bins'] += 1; continue
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
            # A SELF-POINTER IS NOT A POINTER (§194-E). With --one-per-gid the representative is
            # ranked (TU-mass, nins, fn) while the group exemplar is max-nins, so the two coincide
            # on ~half the cards: exemplar == the card's own target on 42/73 wave-U and 36/71
            # wave-T cards (16/16 singleton groups, mathematically forced). Emit None rather than
            # a field that reads like a lead and is the function the agent is already staring at.
            'exemplar': (None if ex.get('name') == fn else
                         {'binary': ex.get('b'), 'fn': ex.get('name'), 'nins': ex.get('nins')}),
            'seed_sim': seed.get('sim'),
            # THE BANKED TWIN (P31 S54, cookbook §193-A). `exemplar` is the largest OPEN member of
            # the atlas group (atlas.py:96 load_open -> corpus.stubs, :657 max(members)), so it is a
            # STUB 100% of the time -- measured 0/34 on wave T, and it is 0/N at any project
            # maturity because it is a construction invariant, not drainage. Meanwhile the atlas
            # ALREADY computed a matched-pool twin (atlas.py:505-536: pool = sig - stubs, so 26/26
            # of them resolve BANKED) and this builder kept only its similarity SCORE while
            # discarding the identity. Wave T's agents were handed a dead pointer and told to grep
            # for a live one; card func_80184FB4's discarded seed ref was a 0.951-similar banked
            # body that reads line-for-line against the answer the agent spent the session deriving.
            'seed_ref': (lambda rf: {'binary': rf[0], 'fn': 'func_%08X' % rf[1], 'nins': rf[2]}
                         if rf else None)(seed.get('ref')),
            'matched_n': [n for n in knn.get('%s:%s' % (ex.get('b'),
                                              str(ex.get('a') or '')[2:].lower()), [])
                          if str(n[0]).startswith('M:')][:3],
            # DESTINATION-TU LOCALITY (§194-E). Neither `exemplar` nor `seed_ref` can name a banked
            # body in the card's OWN .c -- seed_ref came back same-binary 0/51 on wave U, because
            # the atlas dedups its matched pool by h_seq across the whole fleet. But the same-TU
            # banked neighbour is the highest-yield reading source measured so far: 62% of wave-T
            # targets shared >=2 callees/globals with a pre-wave banked body in their own TU,
            # against 19% for the cross-overlay distinctive-literal grep. Ranked by shared symbol
            # count between the TARGET's .s relocations and each banked sibling's C body.
            'tu_ref': tu_neighbours(b, fn, home_tu(b, fn), sub),
            # THE FLEET'S DECLARATION CONSENSUS (P31 S54, cookbook §196). §195-A proved callee arity
            # has NO positive tell in the asm -- an argument that dies at the call is allocated
            # straight into $aN, so the prescribed procedure is a two-arity A/B, i.e. an extra
            # compile per ambiguous callee. But some other TU has usually banked a caller already:
            # func_8012BEE8 is declared ('s32', ('s32',)) in 4,674 places fleet-wide. Same story for
            # the D_ globals every CONFLICTING-EXTERN drop is about. Deterministic, zero tokens, and
            # the destination TU's own spelling is marked authoritative (wave law 2) when present.
            'decl_prior': DP.for_asm(sub, home_tu(b, fn), idx=_DPIDX),
        })

# principle 4 (P31 S54): ONE CARD PER ATLAS GROUP. Same-gid members are the SAME skeleton in
# different overlays; the deterministic remap (family_sweep --hseq) banks the siblings behind a
# banked exemplar for zero tokens, so drafting both is paying twice. Collapse here, BEFORE the
# gate-group ranking, so the ranking sees distinct work; defer the rest to <out>.siblings.json.
siblings = collections.defaultdict(list)
if a.one_per_gid:
    _mass = collections.Counter()
    for c in cands:
        _mass[(c['binary'], c['tu'])] += c['nins']
    keep = {}
    for c in cands:
        cur = keep.get(c['gid'])
        rank = (_mass[(c['binary'], c['tu'])], c['nins'], c['fn'])
        if cur is None or rank > cur[0]:
            if cur is not None:
                siblings[c['gid']].append(cur[1])
            keep[c['gid']] = (rank, c)
        else:
            siblings[c['gid']].append(c)
    reps = [v[1] for v in keep.values()]
    n_sib = sum(len(v) for v in siblings.values())
    assert len(reps) + n_sib == len(cands), \
        f"coverage (R32): {len(reps)} reps + {n_sib} siblings != {len(cands)} candidates"
    print(f"--one-per-gid: {len(cands)} candidates -> {len(reps)} groups "
          f"({n_sib} same-gid siblings deferred to the mechanical remap)")
    cands = reps

# principle 1: CONCENTRATE ON GATE GROUPS. gate_lane groups by (binary, home .c) and each group
# is one whole-binary rebuild, so drafts-per-GROUP is the throughput number that matters -- not
# drafts per binary. Wave D was 42 drafts over 23 groups (1.8/group, ~40 min of gate).
by_tu = collections.defaultdict(list)
for c in cands:
    by_tu[(c['binary'], c['tu'])].append(c)
if a.rank == 'total':
    # P31 S54: rank by the mass a card actually DELIVERS -- its own instructions plus the same-gid
    # siblings the post-bank remap banks for free. Measured on the wave-T draw: the 70 selected
    # cards carried 9,985 sibling instructions, 1.5x the wave's own 6,509, and that leverage is
    # very unevenly spread across gate groups (some carry 3 siblings per card, some carry none).
    # Ranking by face mass is therefore ranking by the smaller half of the number.
    if not a.one_per_gid:
        sys.exit("--rank total requires --one-per-gid (there are no deferred siblings otherwise)")
    _sibins = {g: sum(c['nins'] for c in v) for g, v in siblings.items()}
    ranked = sorted(by_tu, key=lambda k: -sum(c['nins'] + _sibins.get(c['gid'], 0)
                                              for c in by_tu[k]))[:a.max_bins]
elif a.rank == 'mass':
    ranked = sorted(by_tu, key=lambda k: -sum(c['nins'] for c in by_tu[k]))[:a.max_bins]
else:
    ranked = sorted(by_tu, key=lambda k: -len(by_tu[k]))[:a.max_bins]

# principle 3 (P31 S52): SIZE A WAVE BY INSTRUCTIONS, NOT BY CARDS. The public metric is
# instruction-weighted, so a wave is worth what its instructions are worth: the 12-42-ins card
# lanes produced ~1,400 ins/wave (~0.011pp) while wave O carried 6,266 ins for the same gate cost
# and the same draft rate. --target-ins keeps drawing cards until the instruction budget is met
# (still capped by n, so a wave can never spawn an unbounded fleet).
wave, tot_ins = [], 0
def _full():
    if a.target_ins:
        return tot_ins >= a.target_ins or len(wave) >= a.n
    return len(wave) >= a.n
_deliver = (lambda c: c['nins'] + sum(s['nins'] for s in siblings.get(c['gid'], ()))) \
    if a.rank == 'total' else (lambda c: c['nins'])
for k in ranked:                            # principle 2: within a group, mass first
    for c in sorted(by_tu[k], key=lambda c: -_deliver(c)):
        if _full(): break
        wave.append(c); tot_ins += c['nins']
    if _full(): break
if a.target_ins and tot_ins < a.target_ins:
    print(f"NOTE: only {tot_ins} ins available under these filters (target {a.target_ins}) — "
          f"widen --min-ins/--max-ins/--levers or raise n ({len(wave)} of max {a.n} cards used)")

json.dump(wave, open(a.out, 'w'), indent=1)
if a.one_per_gid:
    # Only the siblings of gids that ACTUALLY made the wave are actionable this session; the rest
    # stay in the atlas for a later draw. Both counts are printed so nothing is silently dropped.
    in_wave = {c['gid'] for c in wave}
    sib_out = {g: v for g, v in siblings.items() if g in in_wave}
    sib_path = a.out.replace('.json', '') + '.siblings.json'
    json.dump(sib_out, open(sib_path, 'w'), indent=1)
    n_act = sum(len(v) for v in sib_out.values())
    print(f"-> {n_act} siblings ({sum(c['nins'] for v in sib_out.values() for c in v)} ins) behind "
          f"{len(sib_out)} of this wave's gids -> {sib_path} (remap after the bank); "
          f"{sum(len(v) for v in siblings.values()) - n_act} more sit behind un-drawn gids")
tot = sum(c['nins'] for c in wave)
print(f"candidates {len(cands)} in {len(by_tu)} gate groups (skipped {dict(skipped)})")
ngroups = len({(c['binary'], c['tu']) for c in wave})
print(f"-> wave {len(wave)} drafts / {tot} ins across {len({c['binary'] for c in wave})} binaries "
      f"in {ngroups} GATE GROUPS = {len(wave)/max(ngroups,1):.1f} drafts per rebuild")
if wave:
    print("models:", dict(collections.Counter(c['model'] for c in wave)))
    print("levers:", dict(collections.Counter(c['lever'] for c in wave)))
    print("nins: %d-%d (avg %.0f)" % (min(c['nins'] for c in wave), max(c['nins'] for c in wave), tot/len(wave)))
