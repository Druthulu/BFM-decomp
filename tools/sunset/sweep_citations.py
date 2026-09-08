#!/usr/bin/env python3
"""sweep_citations.py — deterministically localise every gcc-source citation in a markdown doc.

WHY THIS IS A TOOL AND NOT AN AGENT WAVE. The codegen-map audits (T34/T35) established that our
docs cite `tools/reference/gcc-papermario/` = gcc **2.8.1**, while we build with **2.7.2**
(`tools/reference/gcc-2.7.2/`), and that the drift is large and NON-uniform (+27 in sched.c, +611 in
reload1.c) — large enough that a citation lands inside a DIFFERENT FUNCTION and every sentence built
on it still reads plausibly. Deciding *whether a claim is true* needs judgement. Deciding *where a
line number actually points* does not: it is a lookup, and a lookup belongs in zero-token tooling.

So this tool answers the mechanical half exactly, and leaves only genuine judgement for a human/agent:

  symbol-form cite (`combine_regs:1825`)  -> compare to the symbol's REAL 2.7.2 definition line.
                                             Verdict is fully determined: OK / DRIFT(+N) / NO-SYMBOL.
  file-form cite (`cse.c:8626`)           -> report which function that line falls INSIDE in 2.7.2,
                                             so a reader can see at a glance whether the doc's
                                             surrounding prose is talking about that function at all.

A cite whose enclosing function differs from the symbol the prose names is the exact signature of the
"landed in a neighbouring function" failure — that is what to grep the report for.

  python3 tools/sweep_citations.py docs/matching-cookbook.md [--src tools/reference/gcc-2.7.2]
"""
import argparse
import os
import re
import sys

DEF_RE = re.compile(r"^([a-z_][a-z0-9_]*)\s*\(")          # K&R definition: name on its own line
# `sym:1234`  or  `file.c:1234`  (optionally a range `1234-1250`)
CITE_RE = re.compile(r"([A-Za-z_][A-Za-z0-9_./-]*?)\s*:\s*(\d{2,5})(?:\s*-\s*\d{2,5})?")
SKIP_PREFIX = ("http", "https", "ftp", "Phase", "phase", "§")


def index_source(src):
    """(defs, lines) — defs: symbol -> [(file, line)] ; lines: file -> [text]."""
    defs, lines = {}, {}
    for root, _dirs, files in os.walk(src):
        for f in files:
            if not f.endswith((".c", ".h", ".md")):
                continue
            p = os.path.join(root, f)
            rel = os.path.relpath(p, src)
            try:
                L = open(p, errors="replace").read().split("\n")
            except Exception:
                continue
            lines[rel] = L
            lines.setdefault(os.path.basename(rel), L)   # allow bare "cse.c"
            for i, ln in enumerate(L, 1):
                m = DEF_RE.match(ln)
                if m:
                    defs.setdefault(m.group(1), []).append((rel, i))
    return defs, lines


def enclosing(lines, fname, line):
    """Name of the function whose K&R definition most recently precedes `line`."""
    L = lines.get(fname) or lines.get(os.path.basename(fname))
    if not L or not (1 <= line <= len(L)):
        return None, len(L) if L else 0
    best = None
    for i in range(line - 1, -1, -1):
        m = DEF_RE.match(L[i])
        if m:
            best = (m.group(1), i + 1)
            break
    return best, len(L)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("doc")
    ap.add_argument("--src", default="tools/reference/gcc-2.7.2")
    ap.add_argument("--only-problems", action="store_true")
    a = ap.parse_args()

    if not os.path.isdir(a.src):
        print("no source tree at %s" % a.src)
        sys.exit(2)
    defs, lines = index_source(a.src)

    rows, seen = [], set()
    for n, raw in enumerate(open(a.doc, errors="replace").read().split("\n"), 1):
        for m in CITE_RE.finditer(raw):
            who, ln = m.group(1), int(m.group(2))
            if who.startswith(SKIP_PREFIX) or who.isdigit():
                continue
            key = (who, ln)
            if key in seen:
                continue
            seen.add(key)
            is_file = who.endswith((".c", ".h", ".md")) or "/" in who
            if is_file:
                base = os.path.basename(who)
                if base not in lines and base.replace(".md", "") not in lines:
                    continue
                enc, total = enclosing(lines, base, ln)
                if enc is None:
                    rows.append((n, who, ln, "OUT-OF-RANGE", "file has %d lines" % total))
                else:
                    rows.append((n, who, ln, "IN-FN", "%s (defined :%d)" % (enc[0], enc[1])))
            else:
                if who not in defs:
                    continue                     # not a gcc symbol we can resolve; skip quietly
                cands = defs[who]
                near = min(cands, key=lambda c: abs(c[1] - ln))
                d = ln - near[1]
                verdict = "OK" if abs(d) <= 3 else "DRIFT %+d" % d
                rows.append((n, who, ln, verdict, "%s real :%d" % (near[0], near[1])))

    probs = [r for r in rows if r[3].startswith("DRIFT") or r[3] == "OUT-OF-RANGE"]
    print("%s — %d resolvable citations" % (a.doc, len(rows)))
    print("  symbol-form OK      : %d" % len([r for r in rows if r[3] == "OK"]))
    print("  symbol-form DRIFTED : %d" % len([r for r in rows if r[3].startswith("DRIFT")]))
    print("  file-form localised : %d" % len([r for r in rows if r[3] == "IN-FN"]))
    print("  out of range        : %d" % len([r for r in rows if r[3] == "OUT-OF-RANGE"]))
    print()
    show = probs if a.only_problems else rows
    print("%-6s %-30s %-7s %-12s %s" % ("mdline", "cite", "line", "verdict", "in real 2.7.2"))
    for n, who, ln, v, note in show:
        print("%-6d %-30s %-7d %-12s %s" % (n, who[:30], ln, v, note))


if __name__ == "__main__":
    main()
