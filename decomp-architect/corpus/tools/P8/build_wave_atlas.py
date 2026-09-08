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
import json, os, re, sys, time, collections, subprocess, argparse, glob
import fcntl
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
                default='head-crack,seeded-crack,redraft,len-vein,integration,family-sweep,tiny-direct,UNKNOWN,cc1,jtbl-carve,extend-tell,swaprepeat-tell,s16-div-tell,remap,needs-autopsy,plumbing',
                help="agent-draftable levers; tell/o0 need their own lanes. JTBL-CARVE JOINED THE "
                     "DEFAULT LANE in P31 S59, once the gate could carve per draft: the members it "
                     "can structurally reach are filtered by jtbl_carve.island_probe and capped at "
                     "ONE PER BINARY PER WAVE (§61c — one table-bearing draft per gate invocation), "
                     "so they MIX INTO ordinary waves rather than forming their own. A dedicated jtbl "
                     "wave draws ~12 cards and would idle a 2,000-agent fleet; mixed in, the cap "
                     "costs nothing and the fleet stays fed. CC1 JOINED THE "
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
                     "groups are mostly singletons, so the free sibling remap yielded ZERO. "
                     "REMAP, NEEDS-AUTOPSY AND PLUMBING JOINED THE DEFAULT LANE in P31 S60 (Drew): "
                     "they were held out because each has a cheaper deterministic owner — the "
                     "family remap banks a `remap` card for zero tokens, `plumbing` is "
                     "recover_integration's, `needs-autopsy` wants a look before a draft. That "
                     "reasoning priced AGENT TOKENS as the scarce resource; on a free model the "
                     "scarce resource is CARDS, and holding 1,219 instances out of every wave to "
                     "protect a token budget that does not bind starves a 2,000-agent fleet. The "
                     "deterministic lanes still run and still bank these first — the byte gate "
                     "refuses a duplicate, so a drafted card that a remap already banked costs one "
                     "wasted shard, not a wrong bank.")
ap.add_argument('--tells-quota', type=int, default=60,
                help="cards per wave reserved for the tell levers (default 60). Like jtbl they are "
                     "spread thin across binaries and lose the gate-group ranking, and a dedicated "
                     "tells WAVE only draws 70-87 cards — a whole 40-minute slot at a fraction of a "
                     "default wave's size. 0 disables.")
ap.add_argument('--tells-max-ins', type=int, default=80,
                help="tell-lever members above this are not drawn at all (default 80). Measured "
                     "bank rate by size: 5-80 = 27-40%%, 81-120 = 10%%, 121-200 = 1%%, 200+ = 0%%. "
                     "The 383 members above the cap are the serial lane's work (idiom_serial), not "
                     "the fan-out's.")
ap.add_argument('--jtbl-quota', type=int, default=6,
                help="cards per wave reserved for the jtbl-carve lever (default 6). They are "
                     "one-per-binary by construction and so always lose the gate-group ranking; "
                     "each costs one extra whole-binary rebuild at gate time. 0 disables.")
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
ap.add_argument('--generational', action='store_true',
                help="draw ONLY the lowest generation present: no function gets a 2nd draft while "
                     "any drawable function still lacks a 1st. OPT-IN, and measured why (P31 S60): "
                     "with 46 never-drafted skeletons left against ~681 drawable, making this the "
                     "default starved the fleet to 46 agents. Use it for a priority pass over the "
                     "untouched population, not as the standing policy. Env BFM_GENERATIONAL=1 "
                     "sets it for a whole run.")
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

# GATES IN FLIGHT: EXCLUDE THE BINARIES BEING GATED, DO NOT REFUSE THE WHOLE DRAW (P31 S59).
# corpus.stubs() misreports for a binary WHILE a gate has draft bodies substituted into its sources
# (R35) — but only for THAT binary. The blanket refusal this replaces cost far more than it saved:
# the gater runs almost continuously, so nearly every fresh draw was refused and the drafter fell
# back to PRE-DRAWN waves (measured 15:20 — `br` refused, wave `bj` drafted instead). Pre-drawn
# waves were drawn under the OLD defaults, so every new draw-time feature — the tells quota, the
# jtbl quota, the -O0 and oversize filters — silently failed to reach the fleet.
# Which binaries are mid-gate is not a guess: gate_stage and gate_main hold `.run/auto/gate.<bin>.lock`
# for exactly that window, so a non-blocking test-lock answers it per binary.
def _gating_now():
    held = set()
    for lk in glob.glob(os.path.join(REPO, ".run/auto/gate.*.lock")):
        b = os.path.basename(lk)[len("gate."):-len(".lock")]
        if b in ("lock", ""):
            continue
        try:
            fh = open(lk, "a")
            try:
                fcntl.flock(fh, fcntl.LOCK_EX | fcntl.LOCK_NB)
                fcntl.flock(fh, fcntl.LOCK_UN)
            except OSError:
                held.add("main" if b == "main" else b)
            fh.close()
        except OSError:
            continue
    return held


_busy_bins = _gating_now()
if _busy_bins:
    EXCLUDE |= _busy_bins
    print(f"draw: {len(_busy_bins)} binary/binaries mid-gate, excluded from THIS draw "
          f"(their stubs would misreport, R35): {sorted(_busy_bins)[:6]}"
          + ("…" if len(_busy_bins) > 6 else ""), file=sys.stderr)
if ONLY and ONLY <= _busy_bins:
    sys.exit(f"REFUSING: every requested binary {sorted(ONLY)} is mid-gate — corpus.stubs() would "
             f"misreport (R35). Retry when its gate finishes.")

# R32/R33: derive the already-waved set from what is ON DISK, never from a hardcoded wave-letter
# list (the literal 'a'..'l' silently missed waves m and n and would have re-issued their cards).
# Exclude OUR OWN output: the glob matches it, so re-running the selector after an aborted or
# re-tuned build marked the previous attempt's cards as 'already waved' and silently shrank the
# pool (measured: 46 candidates instead of 60 on a re-run with identical filters).
PRIORS = [p for p in sorted(glob.glob('.run/wave_*_cards.json'))
          if os.path.abspath(p) != os.path.abspath(a.out)]
taken = set()

# THE RESOLVER HOLDS IT (P31 S61, frontier-analysis-s60 §5.6). A function whose latest
# integration-resolver verdict is STAGED / BANKED / GATE-REJECTED already has a body that matches at
# the real TU (rtu_match) and on symbols (reloc_identity); re-drafting it buys nothing and re-enters
# the gate at ~3 builds per failure. DIFF / CC1 verdicts are NOT held — there a redraft can still help
# (with the CURRENT closeness the resolver demoted it to). Keyed by (binary, fn), never bare name.
RESOLVER_HOLD = set()
try:
    _last = {}
    for _line in open('.run/resolver/verdicts.jsonl', errors='replace'):
        try:
            _r = json.loads(_line)
        except Exception:
            continue
        if _r.get('binary') and _r.get('fn'):
            _last[(_r['binary'], _r['fn'])] = _r.get('verdict')
    RESOLVER_HOLD = {k for k, v in _last.items() if v in ('STAGED', 'BANKED', 'GATE-REJECTED')}
except FileNotFoundError:
    pass
if RESOLVER_HOLD:
    print(f"draw: {len(RESOLVER_HOLD)} (binary,fn) held by the integration resolver (STAGED/BANKED/GATE-REJECTED) — not drawn",
          file=sys.stderr)
draw_count = collections.Counter()          # {fn: how many waves have drafted it}
for p in PRIORS:
    try:
        _cards = json.load(open(p))
    except (FileNotFoundError, json.JSONDecodeError, TypeError):
        continue
    _names = {c.get('fn') or c.get('name') for c in _cards}
    taken |= _names
    draw_count.update(n for n in _names if n)

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
    # AN IN-FLIGHT WAVE'S CARDS ARE NOT UNFINISHED WORK — THEY ARE WORK IN PROGRESS (P31 S60).
    # Every card of the wave currently drafting is still an OPEN STUB (its gate has not run yet),
    # so this filter handed the whole wave back to the pool, and the pre-draw — which runs WHILE
    # that wave drafts — rebuilt it card for card. Measured over 18 waves: ck->cl 239/239 shared,
    # co->cp 238/238, cv->cw 222/222, db->dc 208/209, and the pairs that were not identical still
    # shared 50-90%. The duplicate wave then banks almost nothing, because by ITS gate time the
    # first wave has banked the cards: yield alternated 47.6% / 3.8% / 35.3% / 3.6% / 29.9% / 3.7%
    # across the night. Half of all drafting was spent re-drafting work already in flight.
    #
    # A wave is finished when its GATE has run, and the gater says so in its own log (R33 — derive
    # from the artifact that already exists, do not invent a marker). Tags with no GATE line are in
    # flight and stay excluded; a tag whose card file is older than STALE_H with no gate line never
    # got one (a killed wave) and is released, so nothing is locked out forever.
    STALE_H = 6
    # TWO LANES GATE, SO READ BOTH LOGS (P31 S60, caught by its own probe). The overlay gater
    # writes "GATE <tag>: banked N/M"; the MAIN lane gates its own waves and writes
    # "[main-lane] <tag><batch>: N banked" to a different file. Reading only the gater's log made
    # every m## wave look permanently in flight, and main's draw — the lane with 1,291 stubs left —
    # lost 425 cards to an exclusion meant for work in progress.
    gated_tags = set()
    for path, pat in (('.run/gater.log', r'GATE (\w+): banked '),
                      ('.run/main_lane.log', r'\[main-lane\] (m\d+)[a-z]*:.*\bbanked\b')):
        try:
            for line in open(path, errors='replace'):
                m = re.search(pat, line)
                if m:
                    gated_tags.add(m.group(1))
        except OSError:
            pass
    _inflight = 0
    _still_open = set()
    for p in PRIORS:
        tag = os.path.basename(p)[5:-11]          # .run/wave_<tag>_cards.json
        if tag not in gated_tags and (time.time() - os.path.getmtime(p)) < STALE_H * 3600:
            _inflight += 1
            continue
        try:
            for c in json.load(open(p)):
                fn, b = (c.get('fn') or c.get('name')), c.get('binary')
                if fn and b and _open(fn, b) is True:
                    _still_open.add(fn)
        except (FileNotFoundError, json.JSONDecodeError, TypeError):
            pass
    taken -= _still_open
    if _inflight:
        print(f'--retry-unbanked: {_inflight} wave(s) still in flight (no GATE line yet) — their '
              f'cards stay OUT of this draw', file=sys.stderr)
    print(f'--retry-unbanked: {len(_still_open)} previously-waved cards are still OPEN stubs '
          f'and are back in the pool', file=sys.stderr)
if not PRIORS:
    print('NOTE: no prior wave card files found — nothing filtered as already-waved', file=sys.stderr)

levers = set(a.levers.split(','))
atlas = json.load(open(a.atlas))

# CARD FUEL LIVES IN ONE PLACE (R33, P31 S63): _stubmap/is_open/home_tu/_tu_bodies/tu_neighbours
# moved to tools/wave_card_fuel.py so the Claude wave packs (tools/t5_cards.py) build IDENTICAL
# fuel. They were unreachable as a library here: this module parses argv at import.
from wave_card_fuel import _stubmap, is_open, home_tu, _tu_bodies, tu_neighbours  # noqa: F401

def model_for(nins):
    if nins <= 50:  return 'haiku'
    if nins <= 120: return 'sonnet'
    return 'opus'

_DPIDX = DP.load()                    # symbol -> fleet declaration evidence (§196)
knn = atlas.get('knn') or {}          # exemplar key -> neighbours; 'M:' entries are BANKED (§193-A)
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
_TELL_LEVERS = ('extend-tell', 'swaprepeat-tell', 's16-div-tell')


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
        if (b, fn) in RESOLVER_HOLD:             skipped['resolver-holds-it'] += 1; continue
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
        # TELL-LEVER SIZE CAP (P31 S59). Bank rate by size, pooled over the tells waves: 5-80 =
        # 27-40%, 81-120 = 10%, 121-200 = 1%, 200+ = 0%. A tells function stacks 3-5 idioms and
        # p(all of them) falls geometrically, so above the cap a 2,000-agent fan-out is buying
        # almost nothing. Those 383 members / 51,941 ins are the SERIAL lane's work
        # (tools/idiom_serial.py, whose distill step compounds where a fan-out cannot) — R45: do
        # not draw what this pipeline cannot bank at a sane rate, and name who owns it instead.
        if g['lever'] in _TELL_LEVERS and nins > a.tells_max_ins:
            skipped['tells-oversize-serial-lane'] += 1; continue
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

# GENERATIONAL DRAW (P31 S60, Drew): EVERY function gets its FIRST draft before ANY function
# gets its second, and so on. The pool is 83% never-drafted — 3,926 of 4,711 open stubs have
# never had a single shard spent on them — while 471 of the 785 touched-and-still-open have been
# drawn FIVE OR MORE times. Those are not coin flips to re-toss: a card that failed five waves
# needs a LEVER the cookbook does not hold yet, and re-drawing it spends a shard to re-learn what
# five waves already established. Deferring is not abandoning — the corpus grows every wave
# (§274-§277 landed today), so a generation-2 pass drafts against knowledge generation-1 lacked.
#
# The gate keeps only the LOWEST generation present among this lane's candidates, so retries
# become eligible exactly when the untouched population is exhausted, per lane and band (a narrow
# band can reach its own generation 1 while the wide bands are still on 0 — that is correct: the
# rule is about the population a wave can actually draw from).
if (a.generational or os.environ.get('BFM_GENERATIONAL') == '1') and cands:
    _gen = min(draw_count.get(c['fn'], 0) for c in cands)
    _keep = [c for c in cands if draw_count.get(c['fn'], 0) == _gen]
    if len(_keep) != len(cands):
        skipped['later-generation'] += len(cands) - len(_keep)
        print(f"generational draw: generation {_gen} ({'never drafted' if not _gen else str(_gen)+'x drafted'}) "
              f"has {len(_keep)} candidate(s); {len(cands) - len(_keep)} held for a later pass",
              file=sys.stderr)
    cands = _keep

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
# GENERATIONAL TOP-OFF (P31 S60, Drew): a wave fills from the LOWEST generation available and
# only then moves up, instead of either ignoring generations (retries compete with never-drafted
# work) or filtering to one generation (which starved the fleet to 46 cards — see --generational).
# Applied at BOTH levels: gate groups holding never-drafted cards rank ahead of all-retry groups,
# and within a group the untouched cards are taken first. Generation is the primary key and the
# existing mass/count criterion breaks ties, so wave SIZE is untouched — only the ORDER changes.
_mingen = {k: min(draw_count.get(c['fn'], 0) for c in v) for k, v in by_tu.items()}

if a.rank == 'total':
    # P31 S54: rank by the mass a card actually DELIVERS -- its own instructions plus the same-gid
    # siblings the post-bank remap banks for free. Measured on the wave-T draw: the 70 selected
    # cards carried 9,985 sibling instructions, 1.5x the wave's own 6,509, and that leverage is
    # very unevenly spread across gate groups (some carry 3 siblings per card, some carry none).
    # Ranking by face mass is therefore ranking by the smaller half of the number.
    if not a.one_per_gid:
        sys.exit("--rank total requires --one-per-gid (there are no deferred siblings otherwise)")
    _sibins = {g: sum(c['nins'] for c in v) for g, v in siblings.items()}
    ranked = sorted(by_tu, key=lambda k: (_mingen[k],
                                          -sum(c['nins'] + _sibins.get(c['gid'], 0)
                                               for c in by_tu[k])))[:a.max_bins]
elif a.rank == 'mass':
    ranked = sorted(by_tu, key=lambda k: (_mingen[k], -sum(c['nins'] for c in by_tu[k])))[:a.max_bins]
else:
    ranked = sorted(by_tu, key=lambda k: (_mingen[k], -len(by_tu[k])))[:a.max_bins]

# principle 3 (P31 S52): SIZE A WAVE BY INSTRUCTIONS, NOT BY CARDS. The public metric is
# instruction-weighted, so a wave is worth what its instructions are worth: the 12-42-ins card
# lanes produced ~1,400 ins/wave (~0.011pp) while wave O carried 6,266 ins for the same gate cost
# and the same draft rate. --target-ins keeps drawing cards until the instruction budget is met
# (still capped by n, so a wave can never spawn an unbounded fleet).
wave, tot_ins = [], 0
_in_wave = set()
def _full():
    if a.target_ins:
        return tot_ins >= a.target_ins or len(wave) >= a.n
    return len(wave) >= a.n
_deliver = (lambda c: c['nins'] + sum(s['nins'] for s in siblings.get(c['gid'], ()))) \
    if a.rank == 'total' else (lambda c: c['nins'])
# THE JTBL QUOTA (P31 S59). A jtbl card is one-per-binary by construction, so jtbl cards are
# maximally UN-concentrated — and the gate-group ranking above exists precisely to pack many drafts
# behind ONE rebuild. The two are in direct opposition: a mixed draw with `jtbl-carve` in the lever
# list produced 71 jtbl candidates and selected ZERO of them, every wave, forever. Reserve a small
# quota so the lane advances inside ordinary waves instead of needing a dedicated wave (a jtbl-only
# draw is ~12 cards and would idle a 2,000-agent fleet). Cost is exactly `--jtbl-quota` extra
# whole-binary rebuilds at gate time; largest-first, since the carve pays the same either way.
# THE TELLS QUOTA (P31 S59), same reasoning as the jtbl one: tell-lever members are spread thin
# across binaries, so the gate-group ranking never picks them, and giving them their own rotation
# slot instead produced 70-87-card waves — a full 40-minute drafting slot at a quarter of a default
# wave's size. Mixed in with a quota, the size discipline is kept and the fleet stays fed.
_tl_pool = sorted((c for grp in by_tu.values() for c in grp if c['lever'] in _TELL_LEVERS),
                  key=lambda c: -c['nins'])
for c in _tl_pool[:a.tells_quota]:
    if _full(): break
    wave.append(c); tot_ins += c['nins']; _in_wave.add(id(c))
if _tl_pool:
    print(f"tells: reserved {min(len(_tl_pool), a.tells_quota)} of {len(_tl_pool)} eligible "
          f"tell-lever card(s) (quota; <= {a.tells_max_ins} ins)", file=sys.stderr)

_jt_pool = sorted((c for grp in by_tu.values() for c in grp if c['lever'] == 'jtbl-carve'),
                  key=lambda c: -c['nins'])
for c in _jt_pool[:a.jtbl_quota]:
    if _full(): break
    wave.append(c); tot_ins += c['nins']; _in_wave.add(id(c))
if _jt_pool:
    print(f"jtbl: reserved {min(len(_jt_pool), a.jtbl_quota)} of {len(_jt_pool)} eligible jtbl "
          f"card(s) (quota; one per binary, each one extra rebuild at gate time)", file=sys.stderr)

for k in ranked:                            # principle 2: within a group, mass first
    for c in sorted(by_tu[k], key=lambda c: (draw_count.get(c['fn'], 0), -_deliver(c))):
        if _full(): break
        if id(c) in _in_wave: continue      # already seeded by a quota
        # QUOTA-ONLY LEVERS. A quota is a FLOOR unless it is also a ceiling: with the tell levers in
        # the default list, the ranked fill picked them up again and a 300-card test wave came back
        # 122 tells (41%) — the size cap was respected and the MIX was not. Tells enter through the
        # quota or not at all.
        if c['lever'] in _TELL_LEVERS: continue
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

# 6.3 TELL COUNTS ON THE CARD (P31 S60, tells-lane-s59.md). A tell-lever card named a lever and
# then made the agent go find its sites: the card said "extend-tell" and nothing about WHERE or HOW
# MANY. atlas_features already computed the per-function detector counts into .run/feat.<bin>.jsonl
# at atlas time, so this is a join, not a computation — one dict load per binary in the wave.
# Attached for EVERY card, not just tell-lever ones: a sll/sra pair site or a repeated select is
# worth knowing about whatever lever the card was drawn under.
_feat_cache = {}
def _feat_rows(binary):
    if binary not in _feat_cache:
        rows = {}
        try:
            with open(f'.run/feat.{binary}.jsonl', errors='replace') as fh:
                for ln in fh:
                    ln = ln.strip()
                    if not ln.startswith('{'):
                        continue
                    try:
                        r = json.loads(ln)
                    except ValueError:
                        continue
                    try:
                        rows[int(str(r.get('addr')), 16)] = r
                    except (TypeError, ValueError):
                        pass
        except OSError:
            rows = {}
        _feat_cache[binary] = rows
    return _feat_cache[binary]

_n_tells = 0
for c in wave:
    try:
        _r = _feat_rows(c['binary']).get(int(str(c.get('addr')), 16))
    except (TypeError, ValueError):
        _r = None
    if not _r:
        continue
    t = {k: _r.get(k, 0) for k in ('extpair', 'dupselect', 'magic_div', 'sign_lh', 'sign_lb')}
    if any(t.values()):
        c['tells'] = t
        _n_tells += 1
print(f"tell counts attached to {_n_tells} of {len(wave)} card(s) "
      f"(extpair/dupselect/magic_div/sign_lh/sign_lb from .run/feat.<bin>.jsonl)", file=sys.stderr)

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
