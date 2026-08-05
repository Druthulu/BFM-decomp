#!/usr/bin/env python3
"""tools/audit_frontier.py — do the independent "what's left" views agree with the corpus oracle?

WHY THIS EXISTS  (Drew's MASTER_REMAINING proposal, P30 S39; docs/decision-log.md 2026-08-04)
============================================================================================
The project already derives a total / banked / remaining triple, and derives it correctly:

    total     = .run/sig.*.jsonl        (sig_image over the ORIGINAL bytes, independent of splat)
    banked    = sig - stubs             (the proven invariant: INCLUDE_ASM pastes the original asm,
                                         so a function NOT wrapped in it is byte-exact)
    remaining = corpus.stubs(binary)    (derived from the filesystem, coverage-asserted, R32/R33)

So a hand-maintained MASTER_REMAINING file would be strictly worse: it can drift, and — as the
Phase-26 audit proved ~10 times over — it drifts SILENTLY and in the flattering direction (the
canonical case: `.run/fuel_manifest.json` recorded 130 live stubs when the truth was 30, hiding
91.6% of remaining gain, and nobody noticed BECAUSE A TARGET THAT IS NEVER NOMINATED PRODUCES
SILENCE, NOT AN ERROR). R33: derive, don't re-derive; the best outcome is a deleted scanner.

WHAT IS ACTUALLY MISSING, and what this file fixes
--------------------------------------------------
"What's left" is answered today by SIX artifacts — `corpus.stubs`, `docs/worklist.md`,
`docs/backlog.md`, `.run/family_hseq.json`, `.run/fuel_manifest.json`, `docs/progress.fleet.md`.
Each is individually derived. **None of them is ever checked against the others.** That is exactly
the gap that cost P30's T0 a hand-reconciliation (family_hseq said 29,961 remaining instances while
progress.py said 28,296 — an unexplained R32 gap that a human had to chase down).

This is the R34 move: not a better assertion inside one oracle, but a SECOND view that can DISAGREE,
with the disagreement made loud. `corpus.stubs` is the reference; every other view is compared to it.

WHAT IT DOES *NOT* CLAIM
------------------------
Agreement here does NOT mean the denominator is complete. The byte-gate and every view below are
blind to code that was never onboarded (R34/R36) — the 39 un-onboarded type-1 modules, and main's
missing independent boundary oracle (`sig_image` cannot sign a PS-X EXE), are tracked in
`docs/disc-completeness.md` and `docs/second-oracle.md`. This file reconciles the views we HAVE; it
cannot see what none of them can see. That limitation is printed in the report, deliberately.

Usage:  tools/audit_frontier.py [--strict]
        --strict : exit 1 on any unexplained disagreement (for wiring into tools-health later)
"""
import argparse
import collections
import glob
import json
import os
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, "tools"))
import corpus                                            # noqa: E402
import progress                                          # noqa: E402


def reference():
    """THE reference view: open stubs per binary, from the coverage-asserted corpus oracle."""
    per, missing = {}, []
    for p in sorted(glob.glob(os.path.join(REPO, ".run/sig.ov_*.jsonl"))) + \
             [os.path.join(REPO, ".run/sig.resident.jsonl"),
              os.path.join(REPO, ".run/sig.SLUS_007.26.jsonl")]:
        if not os.path.exists(p):
            continue
        b = progress._sig_binary(p)
        try:
            per[b] = set(corpus.stubs(b))
        except Exception as e:                            # R32: a refusal is DATA, not a shrug
            missing.append((b, str(e).split("\n")[0][:90]))
    return per, missing


def view_family_hseq(ref):
    """`.run/family_hseq.json` — the family map's own count of remaining instances."""
    p = os.path.join(REPO, ".run/family_hseq.json")
    if not os.path.exists(p):
        return None
    d = json.load(open(p))
    claimed = (d.get("metrics") or {}).get("unmatched_instances")
    # recount the map's members that the corpus still calls open
    seen = 0
    fams = d.get("families") or []
    for f in (fams.values() if isinstance(fams, dict) else fams):
        for m in (f.get("members") or []):
            ov, addr = (m[0], m[1]) if isinstance(m, list) else (m.get("ov"), m.get("addr"))
            if ov in ref and int(str(addr), 16) in ref[ov]:
                seen += 1
    return {"claimed_unmatched_instances": claimed, "members_still_open_per_corpus": seen}


def view_worklist(ref):
    """`.run/worklist.json` — the ranked decision spine."""
    p = os.path.join(REPO, ".run/worklist.json")
    if not os.path.exists(p):
        return None
    d = json.load(open(p))
    rows = d.get("rows") or []
    stale = sum(1 for r in rows
                if r.get("binary") in ref and r.get("addr")
                and int(str(r["addr"]), 16) not in ref[r["binary"]])
    return {"claimed_n_stubs": d.get("n_stubs"), "rows": len(rows), "rows_already_banked": stale}


def view_backlog(ref):
    """`.run/backlog.jsonl` — the near-miss ledger (append-only; pruned at read)."""
    p = os.path.join(REPO, ".run/backlog.jsonl")
    if not os.path.exists(p):
        return None
    rows = [json.loads(l) for l in open(p) if l.strip()]
    banked = 0
    for r in rows:
        nm, b = r.get("name"), r.get("binary") or "ov_SC01_077"
        if nm and nm.lower().startswith("func_") and b in ref:
            try:
                if int(nm[5:], 16) not in ref[b]:
                    banked += 1
            except ValueError:
                pass
    return {"rows": len(rows), "rows_already_banked": banked}


def view_fuel(ref):
    """`.run/fuel_manifest.json` — the target pool (the artifact whose decay motivated R33)."""
    p = os.path.join(REPO, ".run/fuel_manifest.json")
    if not os.path.exists(p):
        return None
    d = json.load(open(p))
    tg = d.get("targets") or []
    stale = 0
    for t in tg:
        b, a = t.get("binary") or t.get("source_overlay"), t.get("addr")
        if b in ref and a:
            try:
                if int(str(a), 16) not in ref[b]:
                    stale += 1
            except ValueError:
                pass
    return {"targets": len(tg), "targets_already_banked": stale}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--strict", action="store_true",
                    help="exit 1 on any unexplained disagreement (for tools-health)")
    a = ap.parse_args()

    ref, missing = reference()
    total_open = sum(len(v) for v in ref.values())
    print(f"audit-frontier: reference = corpus.stubs over {len(ref)} binaries -> "
          f"{total_open} open stubs")
    if missing:
        print("  !! the reference oracle REFUSED for some binaries (R32) — every count below is "
              "unreliable until fixed:")
        for b, e in missing:
            print(f"       {b}: {e}")

    problems = []
    for name, fn in (("family_hseq", view_family_hseq), ("worklist", view_worklist),
                     ("backlog", view_backlog), ("fuel_manifest", view_fuel)):
        v = fn(ref)
        if v is None:
            print(f"  {name:14s} (absent — regenerate it, or it is simply not in use)")
            continue
        print(f"  {name:14s} {v}")
        for k, n in v.items():
            if k.endswith("already_banked") and n:
                problems.append(f"{name}: {n} row(s)/target(s) name a function the corpus says is "
                                f"BANKED — that view is stale; regenerate it")
        # A view that PUBLISHES its own count must still agree with a recount against the corpus.
        # This is the exact shape of the gap P30's T0 had to hand-reconcile (family_hseq 29,961 vs
        # progress.py 28,296): both numbers were individually derived, neither was ever compared.
        claimed = v.get("claimed_unmatched_instances")
        recount = v.get("members_still_open_per_corpus")
        if claimed is not None and recount is not None and claimed != recount:
            problems.append(
                f"{name}: publishes {claimed} unmatched instances but only {recount} of its members "
                f"are still open per the corpus (delta {claimed - recount:+d}) — the map predates "
                f"{abs(claimed - recount)} bank(s); regenerate with tools/family_hseq.py before "
                f"ranking or scoping ANY work off it")
    if missing:
        problems.append(f"corpus.stubs refused for {len(missing)} binaries")

    print()
    if problems:
        print("DISAGREEMENTS (each one is a view that would mis-scope real work):")
        for p in problems:
            print(f"   - {p}")
    else:
        print("All views agree with the corpus oracle.")
    print()
    print("SCOPE CAVEAT (R34/R36, printed deliberately): agreement here does NOT mean the")
    print("denominator is complete. Every view above — and the byte-gate itself — is blind to code")
    print("that was never onboarded. Open: the 39 un-onboarded type-1 modules")
    print("(docs/disc-completeness.md) and main's missing independent boundary oracle")
    print("(docs/second-oracle.md). No 100% claim is meaningful until those resolve.")
    return 1 if (problems and a.strict) else 0


if __name__ == "__main__":
    sys.exit(main())
