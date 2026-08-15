#!/usr/bin/env python3
"""P31 T6 — group the recorded PLUMBING failures into sweepable campaign groups (R38: the ledgers
already name every conflict; this derives the work queue from them instead of re-diagnosing).

Reads every classified failure ledger (newest verdict per (binary, fn)), keeps the still-open
PLUMBING rows, parses the conflict out of the recorded detail, and groups:

  SELF    — `conflicting types for 'FN'` where FN is the function itself
            -> recover_integration --stages demacroize,tu-scope   (the measured self_decl class)
  CALLEE  — conflicting types for another function                -> --stages tu-scope (+ the
            gate ladder's cast_call_sites, already standing)
  DATA    — conflicting types for / undefined reference to a D_* symbol
            -> tu-scope where decl-shaped; the §171b-1 data-definition carry where undefined
  OTHER   — unparsed detail (counted, printed — R32: never silently dropped)

Output: .run/plumbing_groups.json — rows {binary, fn, sym, klass, detail}; groups keyed
(klass, binary) with per-symbol clusters, sized for the sweep order (biggest first).
"""
import collections, glob, json, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import corpus

LEDGER_RE = re.compile(r"failed\.(?P<bin>[A-Za-z0-9_]+?)(?:\.\d+)?\.classified\.txt$")
CONF_RE = re.compile(r"conflicting types for [`']([A-Za-z_]\w*)")
UNDEF_RE = re.compile(r"undefined reference to [`']([A-Za-z_]\w*)")

_stub_cache = {}


def is_stub(b, fn):
    if b not in _stub_cache:
        try:
            _stub_cache[b] = {s.symbol for s in corpus.stubs(b).values()}
        except Exception:
            _stub_cache[b] = set()
    return fn in _stub_cache[b]


def main():
    newest = {}
    files = glob.glob(".run/*failed*.classified.txt") + glob.glob(".run/c294/*failed*.classified.txt")
    for f in files:
        m = LEDGER_RE.search(os.path.basename(f))
        if not m:
            continue
        b = m.group("bin")
        mt = os.path.getmtime(f)
        for ln in open(f, errors="replace"):
            if "\t" not in ln:
                continue
            fn, verdict = ln.rstrip("\n").split("\t", 1)
            k = (b, fn)
            if k not in newest or newest[k][0] < mt:
                newest[k] = (mt, verdict)

    rows = []
    other = 0
    for (b, fn), (mt, verdict) in sorted(newest.items()):
        if not verdict.startswith("PLUMBING"):
            continue
        if not is_stub(b, fn):
            continue
        mc, mu = CONF_RE.search(verdict), UNDEF_RE.search(verdict)
        sym = (mc or mu).group(1) if (mc or mu) else None
        if sym is None:
            other += 1
            klass, sym = "OTHER", "?"
        elif sym == fn:
            klass = "SELF"
        elif sym.startswith(("D_", "jtbl_")):
            klass = "DATA-UNDEF" if mu else "DATA-DECL"
        else:
            klass = "CALLEE"
        rows.append({"binary": b, "fn": fn, "sym": sym, "klass": klass, "detail": verdict[:160]})

    by_kb = collections.Counter((r["klass"], r["binary"]) for r in rows)
    by_sym = collections.Counter((r["klass"], r["sym"]) for r in rows if r["sym"] != "?")
    out = {"n_open_plumbing": len(rows),
           "by_class": dict(collections.Counter(r["klass"] for r in rows)),
           "top_groups_by_binary": [{"klass": k, "binary": b, "n": n}
                                    for (k, b), n in by_kb.most_common(30)],
           "top_symbols": [{"klass": k, "sym": s, "n": n} for (k, s), n in by_sym.most_common(20)],
           "rows": rows}
    json.dump(out, open(".run/plumbing_groups.json", "w"), indent=1)
    print(f"plumbing_groups: {len(rows)} still-open PLUMBING rows from {len(files)} ledgers")
    print(f"  by class: {out['by_class']}  (OTHER unparsed: {other})")
    for g in out["top_groups_by_binary"][:12]:
        print(f"  {g['klass']:10} {g['binary']:14} n={g['n']}")
    print("wrote .run/plumbing_groups.json")


if __name__ == "__main__":
    main()
