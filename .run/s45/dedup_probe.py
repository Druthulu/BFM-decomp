#!/usr/bin/env python3
"""S45 II.1c probe: how many md_* module functions are h_exact-identical to a function
already MATCHED somewhere in the corpus? (R37: measure before building/running machinery.)"""
import json, sys, glob, os
sys.path.insert(0, "tools")
import corpus  # the derived oracle (R33)

# corpus side: every non-module binary's sig; matched = sig - stubs (the proven invariant)
matched_hx = {}   # h_exact -> (alias, addr)
all_hx = {}       # h_exact -> (alias, addr)  (matched or not)
for sig in glob.glob(".run/sig.*.jsonl"):
    alias = os.path.basename(sig)[4:-6]
    if alias.startswith("md_") or alias == "main":
        continue
    try:
        stubs = corpus.stubs(alias)
    except Exception as e:
        print(f"  [skip] {alias}: {e}")
        continue
    for ln in open(sig):
        r = json.loads(ln)
        hx, addr = r["h_exact"], int(r["addr"], 16)
        all_hx.setdefault(hx, (alias, addr))
        if addr not in stubs:
            matched_hx.setdefault(hx, (alias, addr))

rows = []
tot = tot_matched = tot_known = 0
for sig in sorted(glob.glob(".run/sig.md_*.jsonl")):
    alias = os.path.basename(sig)[4:-6]
    n = n_matched = n_known = 0
    for ln in open(sig):
        r = json.loads(ln)
        n += 1
        if r["h_exact"] in matched_hx:
            n_matched += 1
        elif r["h_exact"] in all_hx:
            n_known += 1
    rows.append((alias, n, n_matched, n_known))
    tot += n; tot_matched += n_matched; tot_known += n_known

print(f"{'alias':<14} {'fns':>5} {'hx=MATCHED':>10} {'hx=stub-only':>12}")
for alias, n, m, k in rows:
    flag = "" if (m + k) == 0 else "  <-- overlap"
    print(f"{alias:<14} {n:>5} {m:>10} {k:>12}{flag}")
print(f"{'TOTAL':<14} {tot:>5} {tot_matched:>10} {tot_known:>12}")
print("\nhx=MATCHED: identical bytes to an already-matched corpus fn (free propagation candidate)")
print("hx=stub-only: identical to a corpus fn that is itself still a stub (shared frontier)")
