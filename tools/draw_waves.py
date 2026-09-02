#!/usr/bin/env python3
"""tools/draw_waves.py — draw N drafting waves off the OPEN frontier, cheapest-first (P31 S66).

Usage:
  draw_waves.py --prefix .run/w --waves 2 --per-wave 110 [--max-nins 50] [--min-nins 0]
                [--binaries ov_,md_] [--no-main] [--dry]

WHY (measured, P31 S66). The S65 checkpoint's tier map said "cheap singletons (3-17 ins) ~557 — the
bulk". 557 was the count of one-member FAMILIES, not of small functions: re-measured off
`corpus.stubs`, only 28 undrawn non-main stubs are <=17 ins, and the bulk is 51-120 (258) and >120
(245). A draw tool that reads the FRONTIER rather than a remembered tier count cannot inherit that
conflation (R33: derive, do not re-derive).

WHAT IT ASSERTS
  * population = corpus.stubs (the R32-asserting oracle) over every binary under src/, minus main
    unless --main, minus everything already in the draw ledger (.run/t5/drawn.json, keyed
    "binary:fn" — R48).
  * PACKS ARE NAME-KEYED, so a wave may not contain two functions with the same NAME even in
    different binaries (`claude_wave_packs.py` refuses the whole wave otherwise, measured on r1).
    Collisions are pushed to a LATER wave rather than dropped.
  * every wave's targets.json is written in api_agent's target shape, and the ledger is appended
    only for what is actually written (--dry writes nothing).

Then, per wave: t5_cards.py -> claude_wave_packs.py -> wave_args.py, and launch
tools/workflows/claude_wave_draft.js with the args wave_args.py printed (never hand-typed).
"""
import argparse, collections, glob, json, os, sys
import re

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(REPO)
sys.path.insert(0, 'tools')
import corpus

LEDGER = '.run/t5/drawn.json'


def arm_for(n):
    """Model tier for a target of n instructions.

    RAISED AFTER P31 S69's MEASUREMENT (Drew, 2026-09-01) — the old `sonnet if n <= 120` rule was
    costing MORE, not less, because a cheaper agent that fails 53% of the time is billed for every
    failure. Measured over 129 drafting agents in one session, per MATCHED instruction:

        sonnet   105 agents, 57 MATCH   4,289 tokens / matched instruction
        opus      24 agents, 11 MATCH   2,083   (m1 band alone: 1,291)

    Opus is 2.1x cheaper per banked instruction overall, 3.3x on its own band, while handling
    functions 3-4x larger. Sonnet's per-agent price is not the cost that matters; cost per BANK is.
    Sonnet held a flat ~47% above 30 instructions, so the band where it pays is genuinely small.

    Do NOT re-derive a cheap-tier argument from per-agent price. It was tested (S68 A/B) and
    re-measured (S69); escalating SOONER to a higher tier is the standing finding.

    The TOP of the ladder was wrong too (Drew, 2026-09-01). S69 sent the 347-670 band to opus and it
    returned the session's worst number by a wide margin:

        m1  opus  191-347 ins   10/15 MATCH   1,291 tokens / matched instruction
        m2  opus  347-670 ins    1/9  MATCH   7,158   <-- 5.5x worse, 2.92M tokens for ONE bank

    Above ~350 instructions opus falls off a cliff; that band is Fable's, and Fable measured 3/4 on
    the escalation lane the same session (plus S68's cold-start 85k/93k vs a sonnet median ~271k).
    ESCALATE SOONER: the expensive mistake is running a cheaper tier into a wall, not paying the
    higher tier up front.

    DREW'S RULING, 2026-09-01, after reading the S69 numbers: NO MORE SONNET AT ALL, and anything
    over 150 instructions goes to FABLE. Not a threshold to re-tune from per-agent price — sonnet's
    53% failure rate is billed in full, and opus fell off a cliff above ~350. Two tiers only.
    """
    return 'opus' if n <= 150 else 'fable'


# THE RESIDUAL CLASS PREDICTS DIFFICULTY BETTER THAN `nins` DOES (Drew, 2026-09-02, S71).
# Measured over the S71 wave's own agent runs: wall-clock and iteration count track the RESIDUAL,
# not the size. A 26-instruction function took 18 minutes and 31 tool calls (`func_80181294`,
# still NEAR); a 122-instruction one took 80 seconds and 10 (`func_8017DB98`). The 20-30 minute
# runs were all compiler-internal residuals — scheduling ties, birthing boost, register colouring —
# where each hypothesis costs a compile-and-measure cycle:
#
#     func_80185D44   47 ins  opus  21 min  48 tool calls   (LUID contradiction, read cc1 -dS)
#     func_80185F4C   60 ins  opus  22 min  33
#     func_800D24D0  141 ins  opus  33 min  51
#
# `arm_for` keys on size alone, so a 47-instruction regalloc wall was STRUCTURALLY unable to be
# drawn at the higher tier, and nothing escalates mid-run. Now that every pack carries the
# function's own history (§411), the prior residual class is known AT DRAW TIME — and 1,352 of the
# 3,147 functions with history (43%) have a note naming one of these classes.
_WALL_RE = re.compile(
    r'permuter|regalloc|register (?:alloc|colou?ring|pressure)|schedule[- ]reorder|SCHEDULE-'
    r'|birthing|LUID|sched1|sched2|scheduler-internal|cross_?jump|delay[- ]slot|colou?ring',
    re.I)


def arm_from_history(binary, fn, n, _cache={}):
    """`fable` when this function's own journal history names a compiler-internal residual.

    Escalating SOONER is the standing finding (see arm_for); this applies it to the axis that
    actually predicts cost. Falls back to the size ladder when there is no history, and never
    DOWNGRADES what the size ladder chose."""
    if not _cache:
        try:
            sys.path.insert(0, os.path.join(REPO, 'tools'))
            import journal_notes
            _cache['idx'] = journal_notes.load()
            _cache['mod'] = journal_notes
        except Exception:
            _cache['idx'] = None
    base = arm_for(n)
    idx = _cache.get('idx')
    if not idx or base == 'fable':
        return base
    rows = _cache['mod'].notes_for(idx, binary, fn)
    if rows and _WALL_RE.search(" ".join(r.get('note') or '' for r in rows)):
        return 'fable'
    return base


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--prefix', required=True, help='wave dir prefix; waves are <prefix>1, <prefix>2, ...')
    ap.add_argument('--waves', type=int, default=1)
    ap.add_argument('--per-wave', type=int, default=100)
    ap.add_argument('--min-nins', type=int, default=0)
    ap.add_argument('--max-nins', type=int, default=10 ** 9)
    ap.add_argument('--main', action='store_true', help='draw from main (default: excluded — main has its own lane, R43)')
    ap.add_argument('--only-main', action='store_true', help='draw ONLY main (the main lane; implies --main)')
    ap.add_argument('--ledger', default=LEDGER)
    ap.add_argument('--exclude', default='', help='comma-separated binary:fn to skip')
    ap.add_argument('--dry', action='store_true')
    a = ap.parse_args()

    ledger = json.load(open(a.ledger)) if os.path.exists(a.ledger) else {}
    drawn = {tuple(k.split(':', 1)) for k in ledger}
    skip = {tuple(x.split(':', 1)) for x in a.exclude.split(',') if ':' in x}

    bins = sorted(os.path.basename(p) for p in glob.glob('src/*') if os.path.isdir(p))
    if a.only_main:
        a.main = True
    bins = [b for b in bins if b != 'shared' and (a.main or b != 'main')]
    if a.only_main:
        bins = ['main']

    # LINKED SUBSEGS ARE REFUSED, NOT MERELY AVOIDED (P31 S66 — R43/R34).
    # 960 of main's 1,099 INCLUDE_ASM lines live in the 49 subsegs whose TUs the linker script never
    # references; the bytes come from linked PsyQ SDK objects and are already byte-identical. But
    # Makefile:595 globs every src/*.c into OBJS, so those TUs ARE still compiled -- as unplaced
    # inputs. Therefore ANY C written into one of them compiles, links, and leaves the SHA1 green
    # WHETHER OR NOT IT IS CORRECT: a wave drawn from the raw 1,099 would mint up to 960 gate-green
    # FALSE MATCHES, and the whole-binary byte gate -- our sole arbiter (G3/P9) -- is structurally
    # blind to it. progress.linked_subsegs() derives the set from the Makefile's own psyq_integrate
    # calls, so it tracks the live link, not a hardcoded list (the reduction is machine-local:
    # .run/obj40 is gitignored, and on a fresh clone those stubs really ARE the link path).
    linked = set()
    if a.main:
        import progress
        progress.set_binary('main')
        linked = set(progress.LINKED_SEGS)
        print('main: refusing %d LINKED subseg(s) — their INCLUDE_ASM is dead text and a draft there '
              'would gate GREEN while wrong' % len(linked), file=sys.stderr)

    pool, refused = [], []
    for b in bins:
        try:
            st = corpus.stubs(b)
        except Exception as e:                      # a refusing oracle is EXCLUDED LOUDLY (R32)
            refused.append((b, str(e)[:80])); continue
        for _, s in st.items():
            if b == 'main' and s.region in linked:
                continue
            n = corpus.s_ins_count(s.asm_path)
            if not (a.min_nins <= n <= a.max_nins):
                continue
            if (b, s.symbol) in drawn or (b, s.symbol) in skip:
                continue
            pool.append(dict(name=s.symbol, addr='0x%08x' % s.addr, nins=n, binary=b,
                             sub=s.asm_dir, asm=s.asm_path, tu=s.path,
                             cls='FRONTIER', arm=arm_from_history(b, s.symbol, n), **{'from': 'draw_waves'}))
    pool.sort(key=lambda t: (t['nins'], t['binary'], t['name']))

    print('population: %d open stub(s) in [%d,%d] ins, undrawn, over %d binaries (%d oracle refusals: %s)'
          % (len(pool), a.min_nins, a.max_nins, len(bins), len(refused), refused[:2]), file=sys.stderr)

    waves, cur, used_names = [], [], set()
    deferred = []
    for t in pool:
        if len(waves) == a.waves and len(cur) >= a.per_wave:
            break
        if t['name'] in used_names:                 # name-keyed packs: push the collision later
            deferred.append(t); continue
        cur.append(t); used_names.add(t['name'])
        if len(cur) >= a.per_wave:
            waves.append(cur); cur, used_names = [], set()
            # a deferred collision can go in the NEXT wave
            keep = []
            for d in deferred:
                if len(cur) < a.per_wave and d['name'] not in used_names:
                    cur.append(d); used_names.add(d['name'])
                else:
                    keep.append(d)
            deferred = keep
            if len(waves) >= a.waves:
                break
    if cur and len(waves) < a.waves:
        waves.append(cur)

    total = sum(len(w) for w in waves)
    print('drawing %d wave(s), %d target(s) total (%d name-collision(s) deferred, %d left in pool)'
          % (len(waves), total, len(deferred), len(pool) - total), file=sys.stderr)

    for i, w in enumerate(waves, 1):
        d = '%s%d' % (a.prefix, i)
        band = collections.Counter('<=17' if t['nins'] <= 17 else '18-50' if t['nins'] <= 50
                                   else '51-120' if t['nins'] <= 120 else '>120' for t in w)
        arms = collections.Counter(t['arm'] for t in w)
        print('  %s: %d target(s)  bands=%s  arms=%s  nins %d..%d'
              % (d, len(w), dict(band), dict(arms), w[0]['nins'], w[-1]['nins']), file=sys.stderr)
        if a.dry:
            continue
        os.makedirs(d, exist_ok=True)
        json.dump(w, open(os.path.join(d, 'targets.json'), 'w'), indent=1)
        for t in w:
            ledger['%s:%s' % (t['binary'], t['name'])] = {'wave': d, 'nins': t['nins'], 'arm': t['arm']}
    if not a.dry:
        json.dump(ledger, open(a.ledger, 'w'), indent=0)
        print('ledger: %d key(s)' % len(ledger), file=sys.stderr)
    print(' '.join('%s%d' % (a.prefix, i) for i in range(1, len(waves) + 1)))


if __name__ == '__main__':
    main()
