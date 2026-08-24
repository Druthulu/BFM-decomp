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
import json, os, re, sys, collections, subprocess, argparse, glob
sys.path.insert(0, 'tools')
import corpus
import decl_prior as DP

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

ap = argparse.ArgumentParser()
ap.add_argument('out')
ap.add_argument('n', nargs='?', type=int, default=96)
ap.add_argument("--max-bins", type=int, default=12, help="concentrate into this many GATE GROUPS (binary,TU)")
ap.add_argument('--min-ins', type=int, default=0)
ap.add_argument('--max-ins', type=int, default=120, help='above this the bulk ladder stops being honest')
ap.add_argument('--levers',
                default='head-crack,seeded-crack,redraft,len-vein,integration,family-sweep,tiny-direct,UNKNOWN,cc1',
                help="agent-draftable levers; tell/jtbl/o0 need their own lanes. CC1 JOINED THE "
                     "DEFAULT LANE in P31 S59: unlike jtbl (needs a carve before a draft is bankable "
                     "at all) and o0 (needs an -O0 object, Makefile globs cover no md_*), `cc1` is not "
                     "a structural blocker — it records that SOME EARLIER DRAFT failed to compile. "
                     "The gate never needed to exclude it: a compiling draft banks through the normal "
                     "splice->build->SHA path regardless of history, and a non-compiling one fails "
                     "fast at cc1 for the price of one build. Holding 14 groups / 105 instances / "
                     "6,511 ins out of every wave bought nothing. UNKNOWN IS IN THE "
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
ap.add_argument('--allow-invalid', action='store_true',
                help='emit the wave even if the S46 validity gate flags cards as NO-ASM / MID-BODY / '
                     'OUT-OF-RANGE / ALREADY-DONE. Deliberate triage only -- each invalid card costs '
                     'an agent per cascade tier proving a phantom does not exist.')
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
ap.add_argument('--retry-unbanked', action='store_true',
                help='return previously-waved cards to the pool when they are STILL OPEN STUBS. '
                     'The already-waved filter otherwise reads "drawn" as "done", stranding every '
                     'card that was drafted-and-rejected or never drafted at all: 1,785 cards / '
                     '72,961 instructions across 11 waves (P31 S58).')
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

# --retry-unbanked: a card that was DRAWN but never BANKED is not spent work, it is UNFINISHED work.
#
# The already-waved filter treats "this wave drew it" as "this is done", so a card that was drafted
# and gate-rejected, or drafted with wrong symbols, or never drafted at all because its wave was cut
# short, is excluded from every future wave forever. Measured P31 S58 across 11 waves: 4,080 cards
# drawn, 2,295 banked, and **1,785 still-open cards holding 72,961 instructions** locked out of the
# pool — while the drafting lane was simultaneously starving for cards (wave `ak` asked for 1,400
# and the band could only supply 497).
#
# Re-drawing is not a re-run of the same experiment: the cookbook has grown by 26 sections (§207+)
# harvested from those very waves, so a second attempt carries knowledge the first did not. Opt-in,
# because re-drafting a known-hard card is a real cost and that should be a decision, not a default.
if a.retry_unbanked:
    import corpus as _corpus
    _stubs, _kept = {}, 0
    def _open(fn, binary):
        if binary not in _stubs:
            try:
                _stubs[binary] = {st.symbol for st in _corpus.stubs(binary).values()}
            except Exception:
                _stubs[binary] = None
        return None if _stubs[binary] is None else (fn in _stubs[binary])
    _still_open = set()
    for p in PRIORS:
        try:
            for c in json.load(open(p)):
                fn, b = (c.get('fn') or c.get('name')), c.get('binary')
                if fn and b and _open(fn, b) is True:
                    _still_open.add(fn)
        except (FileNotFoundError, json.JSONDecodeError, TypeError):
            pass
    taken -= _still_open
    print(f'--retry-unbanked: {len(_still_open)} previously-waved cards are still OPEN stubs '
          f'and are back in the pool', file=sys.stderr)
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



def _o0_unbankable(spath):
    """True iff this target is an -O0 function sitting in a subseg the build compiles -O2.

    `spath` is corpus.asm_path()'s value: the .s FILE path (e.g.
    asm/md_MAIN_011/nonmatchings/md_MAIN_011/func_800CFC58.s), not a directory. The first draft of
    this helper treated it as a directory, so every open() raised and it returned False for
    everything — a filter that ran on every card and filtered nothing, and whose unit test passed
    because the test fed it the directory the code expected instead of the value the caller passes.
    Read the caller, not the docstring you wish it had.

    Detection is match_one's (cookbook §261): the -O0 frame-pointer prologue `sw $fp` +
    `addu $fp,$sp,$zero` inside the function's first instructions, anchored at `glabel` so a
    migrated jump table or .asciz blob ahead of the code is not read as the prologue."""
    seg = os.path.basename(os.path.dirname(str(spath)))
    parts = os.path.normpath(str(spath)).split(os.sep)
    binary = 'main' if (len(parts) > 1 and parts[1] == 'nonmatchings') else parts[1]
    if corpus.o0_subseg(binary, seg):
        return False                                   # the Makefile compiles this object -O0
    try:
        head, started = [], False
        for ln in open(os.path.join(REPO, str(spath))):
            if 'glabel' in ln and re.match(r'\s*glabel\s', ln):
                started = True; continue
            if not started:
                continue
            m = re.match(r'\s*/\* [0-9A-Fa-f]+ [0-9A-Fa-f]{8} ([0-9A-Fa-f]{8}) \*/\s*(\S.*)?', ln)
            if m:
                head.append((m.group(1).upper(), (m.group(2) or '').strip()))
            if len(head) >= 8:
                break
    except OSError:
        _O0_UNREADABLE.append(str(spath))
        return False
    setup = any(w == '21F0A003' or re.match(r'addu\s+\$fp,\s*\$sp,\s*\$zero', t) for w, t in head)
    save = any(re.match(r'sw\s+\$fp,', t) for _w, t in head)
    return setup and save


_O0_UNREADABLE = []

_JT_MOD = None


def _jtbl_class(binary, fn):
    """None if the gate-time jtbl prep can structurally reach this member's table; else the skip
    class (P31 S59, R43). Inert unless 'jtbl-carve' is in --levers — the default lane never pays
    for the probe.

    The classifier is jtbl_carve.island_probe (one implementation, R33): 'tail' (standard §8a
    gate-time carve), 'covered' and 'island-end' (the §260 md island split, automated in
    harvest_verify._jtbl_prep_one) are bankable-by-construction; 'island-blocked' waits its turn
    on the island stack, 'island-pads' needs §8e pads for modules.mk, 'main-manual' is parked on
    tools/gate_main.py's cadence. Drawing an unreachable member costs a whole draft cascade to
    prove a CARVE-REFUSED that the probe knew statically."""
    global _JT_MOD
    if _JT_MOD is None:
        import jtbl_carve as _JT_MOD  # noqa: PLW0603
    try:
        kind, _detail = _JT_MOD.island_probe(binary, fn)
    except SystemExit:
        return 'probe-refused'
    except Exception:
        return 'probe-error'
    return None if kind in ('tail', 'covered', 'island-end') else kind


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
        # AN -O0 FUNCTION IN AN -O2 OBJECT CANNOT BANK, HOWEVER GOOD THE DRAFT (R43, cookbook §261).
        # The build decides the opt level per OBJECT, and the Makefile's -O0 rules cover `boot`,
        # `ov_SC01_077_o0` and `src/ov_*/ov_*_o0?.c` — nothing else, `src/md_*/` least of all. A
        # function whose target bytes carry the -O0 frame-pointer prologue while its subseg is
        # compiled -O2 is unbankable until it is carved into an -O0 object.
        # MEASURED before this filter existed: 11 such functions had been drawn 79 times across 19
        # waves — 6 per wave in the recent ones — under head-crack/UNKNOWN/tells/len-vein/redraft
        # labels (the atlas `o0-lane` label catches only a fraction of the real -O0 population), and
        # not one of them could ever have banked. That is a standing per-wave tax on agent time,
        # invisible because each draft failed for what looked like an ordinary reason.
        if _o0_unbankable(sub):                  skipped['o0-in-an-O2-object'] += 1; continue
        if g['lever'] == 'jtbl-carve':
            _v = _jtbl_class(b, fn)
            if _v is not None:                   skipped['jtbl-' + _v] += 1; continue
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
            'decl_prior': DP.for_asm(sub, home_tu(b, fn), idx=_DPIDX, binary=b),
        })

# AT MOST ONE JTBL CARD PER BINARY PER WAVE (P31 S59). The gate's per-draft carve/undo is
# byte-proven for ONE table-bearing draft per harvest_verify invocation (§61c/§62: a second one
# in the same batch repartitions shared source under the first one's snapshot — the batch case
# was never re-proven after the S22 fixes). Keeping it unreachable by construction costs one
# deferred card, which --retry-unbanked returns to the pool next wave.
if any(c['lever'] == 'jtbl-carve' for c in cands):
    _jt_keep = {}
    for c in cands:
        if c['lever'] != 'jtbl-carve':
            continue
        cur = _jt_keep.get(c['binary'])
        if cur is None or (c['nins'], c['fn']) > (cur['nins'], cur['fn']):
            _jt_keep[c['binary']] = c
    _n0 = len(cands)
    cands = [c for c in cands if c['lever'] != 'jtbl-carve' or _jt_keep[c['binary']] is c]
    if _n0 != len(cands):
        skipped['jtbl-one-per-binary'] += _n0 - len(cands)
        print(f'jtbl: {_n0 - len(cands)} same-binary jtbl card(s) deferred '
              f'(one table-bearing draft per gate invocation — §61c)', file=sys.stderr)

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

# ---- THE S46 VALIDITY GATE, AT THE POINT CARDS ARE BORN (S56).
# It has always lived in wave_snapshot.py, whose comment argues "a gate that is a separate command
# is a gate someone forgets". It was right, and then it was forgotten: wave_snapshot hardcodes
# asm/<bin>/nonmatchings/<bin>/, which is structurally wrong for every split-TU overlay, so the
# snapshot step got hand-rolled and the gate came off the path for waves T-Z. Here it cannot be
# skipped, and here is the only moment it is MEANINGFUL: every verdict reads live sig/stub/.s state,
# so the same check after drafting would condemn precisely the targets that banked (see
# validate_targets' "PRE-DRAFT ONLY" note). A card that fails burns an agent per cascade tier
# proving a phantom absent -- S46 measured ~29 phantoms x 3 tiers = 87 wasted agents, 9.7M tokens.
try:
    import validate_targets as _VT
    _rows = _VT.validate(wave)
    _bad = [(t, v, d) for t, v, d in _rows if v != 'OK']
    if _bad:
        import collections as _c
        _cls = _c.Counter(v for _t, v, _d in _bad)
        print(f"VALIDITY GATE: {len(_bad)} of {len(wave)} cards are INVALID -- "
              + ', '.join(f'{k}={n}' for k, n in _cls.most_common()), file=sys.stderr)
        for _t, _v, _d in _bad[:12]:
            print(f"    [{_v}] {_t.get('fn')} ({_t.get('binary')}): {_d}", file=sys.stderr)
        if not a.allow_invalid:
            sys.exit("*** Refusing to emit a wave scoped on phantoms. Fix the atlas/family inputs, "
                     "or pass --allow-invalid deliberately. (If these read ALREADY-DONE, a gate is "
                     "probably running: corpus misreports substituted drafts -- wait for it.) ***")
except ImportError:
    print('build_wave_atlas: validate_targets not importable -- VALIDITY GATE SKIPPED', file=sys.stderr)

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
