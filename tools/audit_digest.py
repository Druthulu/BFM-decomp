#!/usr/bin/env python3
"""tools/audit_digest.py — does the COMMITTED fleet digest still describe the CURRENT tree?

WHY THIS EXISTS  (Phase 30 S1e)
===============================
`docs/progress.fleet.md` is the project's headline instrument: the burn-down, the roadmap's
re-baselines, and every "is this lever paying?" call are read off its three numbers. It is written
by `tools/progress.py --fleet` from whatever tree happened to be on disk at that moment — and then
COMMITTED, at which point nothing ever checks it again.

That gap produced a real, costly false alarm. The S38 digest committed at `commit:1426` claimed:

    instr 12402412   distinct 5029324   (78025 uniq)

The same metric recomputed from `commit:1426`'s own committed tree gives:

    instr 12394533   distinct 5022306   (77895 uniq)

— overstated by +7,879 instructions and +130 unique functions, because the digest was generated
from a working tree that still held banked work which was REVERTED before the commit landed, and
was never regenerated afterwards. The next honest digest was therefore LOWER than the stale one, so
the metric appeared to FALL (distinct-code 89.3 -> 89.2) while the tree had in fact only gained
(true delta over that span: instr +10,869, distinct +2,776 ins / +57 unique fns — everything rose).

A session then opened with "distinct-code FELL — UNEXPLAINED; do NOT scale the alias lever until it
is resolved", i.e. the project's best-performing lever was gated on a phantom regression, and the
recorded lead (a name-scanning regex in classify()) pointed at a function that does not feed either
weighted metric at all.

WHY THE EXISTING GATES CANNOT SEE IT (R34)
==========================================
The whole-binary byte-gate is a perfect CORRECTNESS oracle and a NULL oracle for documents: a stale
digest is byte-irrelevant, so `make check-all` stays 140/140 across it forever. `audit-corpus` and
`audit-binaries` assert things about the CODE. Nothing asserted that the number we publish about the
tree is a number OF that tree. This is that second, disagreeing oracle — and its only job is to
disagree when the digest and the tree have drifted apart.

WHAT IT ASSERTS
===============
Recompute the three headline metrics from the CURRENT tree and require the committed digest to
match. A mismatch is not "the numbers moved" — it is "the published number was never true of this
tree", and the fix is always the same: `make report`.

Exit 0 = the digest describes this tree. Exit 1 = it does not (message says which metric drifted).
Usage:  tools/audit_digest.py [--fix]
"""
import re
import sys
import os

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, "tools"))

DIGEST = os.path.join(REPO, "docs/progress.fleet.md")

# The three headline lines, exactly as progress.fleet() writes them. Parsed as integers (the
# printed percentages are rounded to 1dp, so they are far too coarse to catch a 130-function drift —
# the +7,879-instruction staleness above still rendered as "94.4%" both before and after).
_LINES = {
    "fn-count":     re.compile(r'^FLEET fn-count byte-ident:\s*(\d+)\s*/\s*(\d+)', re.M),
    "instr":        re.compile(r'^FLEET instr-weighted\s*:\s*(\d+)\s*/\s*(\d+)', re.M),
    "distinct":     re.compile(r'^FLEET distinct-code\(uniq\):\s*(\d+)\s*/\s*(\d+)\s*=\s*[\d.]+%\s*\((\d+)/(\d+)', re.M),
}


def committed():
    """The three metrics as published in docs/progress.fleet.md."""
    if not os.path.exists(DIGEST):
        raise SystemExit(f"audit-digest: {os.path.relpath(DIGEST, REPO)} does not exist — run `make report`.")
    txt = open(DIGEST).read()
    out = {}
    for key, rx in _LINES.items():
        m = rx.search(txt)
        if not m:
            # R32: a line we cannot read is a DEFECT, not a skip — a silently-unparsed headline is
            # exactly the blindness this file exists to remove.
            raise SystemExit(f"audit-digest: cannot parse the '{key}' line out of "
                             f"{os.path.relpath(DIGEST, REPO)} — the digest format changed and this "
                             f"oracle went blind. Fix the pattern, do not delete the check.")
        g = [int(x) for x in m.groups()]
        out[key] = tuple(g)
    return out


def live():
    """The same three metrics, recomputed from the CURRENT tree."""
    import progress
    # fn-count comes from the per-binary classification; the weighted pair from the derived stub
    # oracle. Both are recomputed here exactly as `progress.fleet()` does it.
    order = [b for b in ("main", "resident") if b in progress.BINARIES] + \
            sorted(b for b in progress.BINARIES if b not in ("main", "resident"))
    rows = [progress.report(b, write=False) for b in order]
    byte = sum(r["byteident"] for r in rows)
    match = sum(r["matchable"] for r in rows)
    wm = progress.weighted_metrics()
    if not wm:
        raise SystemExit("audit-digest: no .run/sig.*.jsonl — run `make sig-overlays sig-resident`.")
    return {
        "fn-count": (byte, match),
        "instr":    (wm["fleet_m"], wm["fleet_t"]),
        "distinct": (wm["dedup_m"], wm["dedup_t"], wm["dedup_fns"], wm["dedup_total_fns"]),
    }


def main():
    fix = "--fix" in sys.argv
    have, want = committed(), live()
    bad = [k for k in want if have.get(k) != want[k]]
    if not bad:
        print(f"audit-digest: OK — docs/progress.fleet.md describes the current tree "
              f"(instr {want['instr'][0]}/{want['instr'][1]}, "
              f"distinct {want['distinct'][2]}/{want['distinct'][3]} uniq).")
        return 0
    print("audit-digest: FAIL — the committed digest does not describe the current tree.")
    print("  A stale digest is BYTE-INVISIBLE (check-all stays green over it), and a later honest")
    print("  regeneration then reads as a REGRESSION that never happened. See this file's header.")
    for k in bad:
        print(f"    {k:9s}  committed {have.get(k)}   actual {want[k]}")
    if fix:
        print("  --fix: regenerating…")
        import progress
        progress.fleet()
        return 0
    print("  Fix: `make report` (regenerates the digest), then commit it WITH the work it describes.")
    return 1


if __name__ == "__main__":
    sys.exit(main())
