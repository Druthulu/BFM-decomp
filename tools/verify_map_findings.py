#!/usr/bin/env python3
"""verify_map_findings.py — machine-check a codegen-map audit's findings against the bytes.

The regalloc.md re-derivation asks agents to classify each claim CONFIRMED / LINE-DRIFT / REFUTED /
UNVERIFIABLE and to justify it with `real_file` + `real_line` + `source_quote`. An agent's verdict is
a CLAIM, not evidence (R14) — and the specific failure mode this guards against is the one that makes
a false REFUTED nearly undetectable by reading: gcc 2.8.1 -> 2.7.2 drifts by +300..+600 lines in
reload1.c / local-alloc.c, so a naive line lookup lands inside a DIFFERENT FUNCTION and every
subsequent sentence reads plausibly.

So: re-open each cited file at each cited line and compare the agent's verbatim quote to what is
actually there. A quote that does not match its line invalidates the finding.

Comparison is whitespace-normalised (agents reflow leading tabs) but otherwise exact. A quote is also
searched for in a +/-40 line window so a NEAR-MISS (right code, wrong line) is reported separately
from a FABRICATION (text appears nowhere near) — those two need very different responses.

  python3 tools/verify_map_findings.py <journal.jsonl|result.json>

Generic over docs/gcc-2.7.2-map/*: any audit whose agents return {real_file, real_line, source_quote}.
"""
import json
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(REPO, "tools/reference/gcc-2.7.2")
WINDOW = 40


# NB — LINE NUMBERING: split("\n"), never splitlines(). GNU C sources use FORM FEED (\f) page
# separators (loop.c has 47, cse.c 36, reload1.c 27), and Python's splitlines() splits on \f while
# grep/sed/editors do not. Using splitlines() shifts every computed line number after the first \f
# — by up to 47 in loop.c, which is larger than this file's +/-40 search window, so a REAL quote can
# be reported FABRICATED. Self-inflicted and caught 2026-07-28 by cross-checking one known value.

def norm(s):
    return re.sub(r"\s+", " ", (s or "")).strip()


def load_findings(path):
    """Accept either the workflow's return value or the raw journal."""
    txt = open(path, errors="replace").read()
    out = []
    # journal: one JSON object per line, agent results under .result
    for line in txt.splitlines():
        line = line.strip()
        if not line.startswith("{"):
            continue
        try:
            o = json.loads(line)
        except Exception:
            continue
        r = o.get("result", o)
        if isinstance(r, dict) and isinstance(r.get("findings"), list):
            for f in r["findings"]:
                f = dict(f)
                f.setdefault("_chunk", r.get("chunk", "?"))
                out.append(f)
    if out:
        return out
    # otherwise: a single result blob containing .findings
    i = txt.find('{"counts"')
    if i < 0:
        i = txt.find("{")
    try:
        blob = json.loads(txt[i:])
    except Exception:
        return []
    return blob.get("findings", [])


def check(f):
    st = f.get("status")
    if st == "UNVERIFIABLE":
        return "SKIP", "declared unverifiable"
    rf, rl, q = f.get("real_file"), f.get("real_line"), f.get("source_quote")
    if not (rf and rl and q):
        return "NO-EVIDENCE", "status=%s but no file/line/quote" % st
    p = os.path.join(SRC, rf.replace("tools/reference/gcc-2.7.2/", "").lstrip("/"))
    if not os.path.exists(p):
        return "BAD-FILE", "no such file: %s" % rf
    lines = open(p, errors="replace").read().split("\n")
    if not (1 <= rl <= len(lines)):
        return "BAD-LINE", "%s has %d lines, cited %d" % (rf, len(lines), rl)
    nq = norm(q)
    if not nq:
        return "NO-EVIDENCE", "empty quote"
    if nq in norm(lines[rl - 1]) or norm(lines[rl - 1]) in nq:
        return "OK", ""
    lo, hi = max(0, rl - 1 - WINDOW), min(len(lines), rl - 1 + WINDOW)
    for j in range(lo, hi):
        if nq in norm(lines[j]) or (norm(lines[j]) and norm(lines[j]) in nq):
            return "NEAR", "quote found at %d, cited %d (off by %+d)" % (j + 1, rl, (j + 1) - rl)
    return "FABRICATED", "quote appears nowhere within +/-%d lines of %s:%d" % (WINDOW, rf, rl)


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(2)
    findings = load_findings(sys.argv[1])
    if not findings:
        print("NO FINDINGS PARSED from", sys.argv[1])
        sys.exit(1)
    tally = {}
    bad = []
    for f in findings:
        v, why = check(f)
        tally[v] = tally.get(v, 0) + 1
        if v not in ("OK", "SKIP"):
            bad.append((v, f, why))
    print("findings checked: %d" % len(findings))
    for k in sorted(tally):
        print("  %-12s %d" % (k, tally[k]))
    if bad:
        print("\n--- EVIDENCE PROBLEMS (these findings are NOT usable as-is) ---")
        for v, f, why in bad:
            print("\n[%s] %s :: %s" % (v, f.get("_chunk", "?"), f.get("status")))
            print("  claim: %s" % (f.get("claim_excerpt", "")[:150]))
            print("  cited: %s -> %s:%s" % (f.get("cited"), f.get("real_file"), f.get("real_line")))
            print("  why  : %s" % why)
    st = {}
    for f in findings:
        st[f.get("status")] = st.get(f.get("status"), 0) + 1
    print("\nstatus distribution: %s" % st)


if __name__ == "__main__":
    main()
