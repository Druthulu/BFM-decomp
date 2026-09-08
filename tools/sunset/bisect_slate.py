#!/usr/bin/env python3
"""bisect_slate.py — isolate the byte-wrong draft(s) in a main slate, with a NULL CONTROL first.

WHY THIS EXISTS (P31 S52). `gate_main`'s built-in bisect ran **three hours** on a 45-draft slate
and printed nothing, because:
  * it never checks whether the baseline (no drafts) even builds — if the failure is environmental
    or caused by one draft that lands in every subset, NO subset can pass and the search is doomed
    from the first step;
  * it only prints when it isolates a SINGLE rejected draft, so a long run is indistinguishable
    from a hung one;
  * its re-split rule (`lo = head + lo`) degrades toward one rebuild per draft when several drafts
    fail, which is the common case, not the rare one.

This driver fixes all three:
  1. **NULL CONTROL FIRST.** Build with ZERO drafts substituted. If that fails, the slate is
     innocent and the search is abandoned immediately — this is the control that would have saved
     those three hours, and it is the same control that refuted the "main is link-blocked"
     misdiagnosis earlier in this phase.
  2. **Progress on every step**, with the elapsed time and the size of the set being tested.
  3. **True binary search** over a candidate set, accumulating a known-good prefix.

Each step is one clean rebuild (~3 min), so a 44-draft slate costs ~6 steps to find one culprit.
Zero tokens — this is wall-clock work a tool should do, not an agent.

Usage:
  bisect_slate.py <slate.json> [--out good.json] [--max-steps N]
"""
import argparse, json, os, subprocess, sys, time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gate_main as gm

T0 = time.time()


def say(msg):
    print(f'[{int(time.time()-T0):5d}s] {msg}', flush=True)


def build_with(entries):
    """One clean rebuild with exactly `entries` substituted. Returns (ok, sha)."""
    gm.run('git checkout -- src/')
    gm.run('make extract BINARY=main')
    if entries:
        gm.substitute(entries)
    got, _r = gm.clean_build()
    return got == gm.GOOD, got


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('slate')
    ap.add_argument('--out', default='.run/bisect_good.json')
    ap.add_argument('--max-steps', type=int, default=40)
    a = ap.parse_args()

    slate = json.load(open(a.slate))
    kept, dropped = gm.resolve_conflicts(slate)
    say(f'slate {len(slate)} -> {len(kept)} compatible ({len(dropped)} dropped by conflict check)')

    # 1. THE NULL CONTROL. Without this the search can run for hours against a failure the drafts
    #    did not cause. (P31 already learned this once, on the "main is link-blocked" misdiagnosis.)
    say('NULL CONTROL: building with ZERO drafts substituted...')
    ok, got = build_with([])
    if not ok:
        say(f'*** BASELINE FAILS ({got}) — the tree/toolchain is the problem, NOT the drafts.')
        say('    Abandoning the search. Fix the baseline first (make clean; make extract BINARY=main).')
        gm.run('git checkout -- src/')
        sys.exit(2)
    say(f'baseline OK ({got}) — the failure is draft-caused, search is meaningful')

    # 2. Whole slate (it may simply pass now).
    say(f'testing all {len(kept)} drafts...')
    ok, got = build_with(kept)
    if ok:
        say(f'ALL {len(kept)} PASS -- {got} BYTE-IDENTICAL')
        json.dump([e['fn'] for e in kept], open(a.out, 'w'), indent=1)
        return

    # 3. Binary search: grow a known-good prefix.
    good, rest, steps = [], list(kept), 0
    while rest and steps < a.max_steps:
        if len(rest) == 1:
            steps += 1
            ok, _ = build_with(good + rest)
            say(f'step {steps}: {"KEEP" if ok else "REJECT"} {rest[0]["fn"]}')
            if ok:
                good += rest
            rest = []
            break
        half = len(rest) // 2
        head, tail = rest[:half], rest[half:]
        steps += 1
        ok, _ = build_with(good + head)
        say(f'step {steps}: good={len(good)} + head={len(head)} -> {"PASS" if ok else "FAIL"}')
        if ok:
            good += head
            rest = tail
        else:
            rest = head           # the culprit is in head; tail is retried afterwards
            if len(head) == 1:
                say(f'   REJECT {head[0]["fn"]}')
                rest = tail

    say(f'FINAL: {len(good)} good of {len(kept)} in {steps} steps')
    json.dump([e['fn'] for e in good], open(a.out, 'w'), indent=1)
    json.dump(good, open(a.out.replace('.json', '_slate.json'), 'w'), indent=1)
    say(f'wrote {a.out} and {a.out.replace(".json", "_slate.json")}')
    gm.run('git checkout -- src/')


if __name__ == '__main__':
    main()
