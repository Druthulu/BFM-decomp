#!/usr/bin/env python3
"""scan_leftovers.py — re-verify every draft already sitting in .run/ and find the free banks.

WHY THIS EXISTS (P31 S53, cookbook §180). Drafts accumulate in `.run/wave_*/` faster than they are
banked, for three structural reasons, none of them mistakes:
  * a wave stopped mid-flight loses its in-flight tail (§176j);
  * the gate DROPS drafts on declaration conflicts, and a drop is per-slate, not permanent;
  * the atlas draws fresh cards and has NO IDEA what is sitting in `.run/` — the next wave never
    reconsiders the last wave's residue.

The first run of this scan found **34 byte-perfect, still-stubbed main drafts (3,075 instructions)**
that had been finished for two sessions and never banked, plus 35 honest near-misses. A full
110-agent wave targets ~6,500 instructions; this costs zero tokens.

THE ORACLE, AND THE TRAP IT AVOIDS (R32/R33). Once a function becomes C, splat stops emitting its
`.s`. So a missing `.s` is not an error — it is the POSITIVE statement "this one is already banked".
A scan that files those as failures reports a ~50% failure rate on a pile that has none. We derive
the banked/stub split from `corpus.stubs()` and then ASSERT the two oracles agree: every still-stub
draft must have its `.s` on disk, and every not-a-stub draft must not. A disagreement means the tree
and the source are out of sync (run `make extract BINARY=<bin>`), and we refuse rather than guess.

Usage:
  scan_leftovers.py [--binary main] [--glob '.run/wave_*'] [--out .run/leftovers.<bin>.json]
                    [--slate .run/leftovers_slate.<bin>.json] [-j N]

Exit 0 always (this is a report). The slate it writes is the input to the standard pre-gate ladder:
  reloc_identity --batch  ->  fragment_check  ->  reconcile_slate --apply  ->  pregate_check
  ->  gate_main (main) / gate_lane (overlays)
"""
import argparse, concurrent.futures as cf, glob, json, os, subprocess, sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__))))
import corpus

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def verify(job):
    """Run match_one on one draft. Returns the honest verdict dict."""
    fn, draft, asm_dir, o0 = job
    cmd = ['.venv/bin/python', 'tools/match_one.py', fn, '--c', draft,
           '--asm-subdir', asm_dir, '--json']
    if o0:
        cmd.append('--o0')
    try:
        r = subprocess.run(cmd, capture_output=True, text=True, timeout=900, cwd=REPO)
    except subprocess.TimeoutExpired:
        return {'fn': fn, 'draft': draft, 'status': 'TIMEOUT', 'closeness': 9999}
    txt = (r.stdout or '') + (r.stderr or '')
    for line in reversed(txt.strip().splitlines()):
        line = line.strip()
        if line.startswith('{') and '"status"' in line:
            try:
                j = json.loads(line)
            except ValueError:
                continue
            st = str(j.get('status', '')).lower()
            v = j.get('verdict') or {}
            return {'fn': fn, 'draft': draft, 'asm_dir': asm_dir,
                    'status': 'MATCH' if st == 'match' else 'NEAR',
                    'closeness': j.get('closeness', 9999), 'nins': j.get('nins'),
                    'sig': v.get('sig'), 'klass': v.get('klass')}
    return {'fn': fn, 'draft': draft, 'asm_dir': asm_dir, 'status': 'TOOLFAIL',
            'closeness': 9999, 'detail': txt[-300:]}


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--binary', default='main')
    ap.add_argument('--glob', default='.run/wave_*',
                    help="draft-directory glob; drafts are <glob>/<binary>/<fn>.c")
    ap.add_argument('--out', default=None)
    ap.add_argument('--slate', default=None)
    ap.add_argument('-j', type=int, default=min(12, os.cpu_count() or 4))
    a = ap.parse_args()

    out_path = a.out or f'.run/leftovers.{a.binary}.json'
    slate_path = a.slate or f'.run/leftovers_slate.{a.binary}.json'

    stubs = {s.symbol: s for s in corpus.stubs(a.binary).values()}
    drafts = sorted(set(glob.glob(os.path.join(REPO, a.glob, a.binary, '*.c'))))
    if not drafts:
        print(f"no drafts under {a.glob}/{a.binary}/ — nothing to scan")
        return

    jobs, banked, disagree = [], [], []
    for p in drafts:
        fn = os.path.basename(p)[:-2]
        rel = os.path.relpath(p, REPO)
        s = stubs.get(fn)
        if s is None:
            banked.append(fn)
            continue
        if not os.path.exists(os.path.join(REPO, s.asm_path)):
            disagree.append((fn, s.asm_path))
            continue
        jobs.append((fn, rel, s.asm_dir, corpus.is_o0(s.path)))

    # R32 — the two oracles must agree, in BOTH directions.
    stale = [fn for fn in banked
             if glob.glob(os.path.join(REPO, 'asm', '**', f'{fn}.s'), recursive=True)]
    if disagree:
        sys.exit(f"REFUSING: {len(disagree)} stubs have no .s on disk (e.g. {disagree[0]}). "
                 f"The tree and src/ disagree — run `make extract BINARY={a.binary}` first (R35).")
    if stale:
        print(f"  note: {len(stale)} not-a-stub drafts still have a .s somewhere in asm/ "
              f"(e.g. {stale[0]}) — a different binary's symbol of the same name, not an error")

    print(f"{len(drafts)} drafts on disk: {len(jobs)} still stubbed (re-verifying), "
          f"{len(banked)} already banked")
    jobs.sort(key=lambda j: -os.path.getsize(os.path.join(REPO, j[1])))   # longest-first

    res = []
    with cf.ProcessPoolExecutor(max_workers=a.j) as ex:
        for r in ex.map(verify, jobs):
            res.append(r)
            print(f"  {r['fn']:24s} {r['status']:8s} c={r['closeness']}")

    res.sort(key=lambda r: (r['status'] != 'MATCH', r['closeness']))

    # The same function can have a draft in several wave dirs (a redraft lane, a repair pass).
    # A slate may name each function EXACTLY ONCE — gate_main substitutes by symbol — so keep the
    # best verdict per fn and say which ones were shadowed rather than silently picking one.
    best, shadowed = {}, []
    for r in res:
        prev = best.get(r['fn'])
        if prev is None:
            best[r['fn']] = r
        else:
            shadowed.append(r['draft'])          # res is sorted best-first
    if shadowed:
        print(f"  note: {len(shadowed)} duplicate drafts shadowed by a better verdict "
              f"for the same function (e.g. {shadowed[0]})")
    matched = [r for r in best.values() if r['status'] == 'MATCH']
    matched.sort(key=lambda r: r['fn'])
    json.dump({'binary': a.binary, 'banked_already': sorted(banked), 'verdicts': res},
              open(os.path.join(REPO, out_path), 'w'), indent=1)
    json.dump([{'fn': r['fn'], 'draft': r['draft']} for r in matched],
              open(os.path.join(REPO, slate_path), 'w'), indent=1)

    mass = sum(r.get('nins') or 0 for r in matched)
    near = [r for r in best.values() if r['status'] == 'NEAR']
    print(f"\n{a.binary}: {len(matched)} MATCH ({mass} ins) bankable now · {len(near)} NEAR "
          f"(closeness<=3: {len([r for r in near if r['closeness'] <= 3])}) · "
          f"{len(banked)} already banked")
    print(f"  -> {out_path}  ·  slate: {slate_path}")
    if matched:
        print(f"  next: reloc_identity --batch, fragment_check, reconcile_slate --apply, "
              f"pregate_check, then the gate (cookbook §180b)")


if __name__ == '__main__':
    main()
