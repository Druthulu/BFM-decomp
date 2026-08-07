#!/usr/bin/env python3
"""S45 probe 2: for each module fn h_exact-identical to a MATCHED corpus fn, name the source
(alias, addr, symbol) and classify its backing: DEFINE_ macro (engine_core.h) vs inline def."""
import json, sys, glob, os, re
sys.path.insert(0, "tools")
import corpus

matched_hx = {}
for sig in glob.glob(".run/sig.*.jsonl"):
    alias = os.path.basename(sig)[4:-6]
    if alias.startswith("md_") or alias == "main":
        continue
    try:
        stubs = corpus.stubs(alias)
    except Exception:
        continue
    for ln in open(sig):
        r = json.loads(ln)
        addr = int(r["addr"], 16)
        if addr not in stubs:
            matched_hx.setdefault(r["h_exact"], []).append((alias, addr, r.get("name", ""), r["nins"]))

core = open("src/shared/engine_core.h").read()

groups = {}   # h_exact -> (module instances, sources)
for sig in sorted(glob.glob(".run/sig.md_*.jsonl")):
    alias = os.path.basename(sig)[4:-6]
    for ln in open(sig):
        r = json.loads(ln)
        if r["h_exact"] in matched_hx:
            groups.setdefault(r["h_exact"], {"mods": [], "src": matched_hx[r["h_exact"]]})
            groups[r["h_exact"]]["mods"].append((alias, int(r["addr"], 16), r["nins"]))

n_macro = n_inline = 0
for hx, g in sorted(groups.items(), key=lambda kv: -kv[1]["mods"][0][2]):
    sa, saddr, sname, nins = g["src"][0]
    backing = "MACRO" if f"DEFINE_func_{saddr:08X}" in core or f"DEFINE_{sname}" in core else "inline"
    if backing == "MACRO": n_macro += len(g["mods"])
    else: n_inline += len(g["mods"])
    mods = " ".join(f"{a}@{ad:08X}" for a, ad, _ in g["mods"])
    print(f"{nins:>4} ins  src {sa}@{saddr:08X} {sname or ''} [{backing}] x{len(g['src'])} srcs -> {mods}")
print(f"\nclasses: {len(groups)}  module instances: MACRO-backed {n_macro} / inline-backed {n_inline}")
