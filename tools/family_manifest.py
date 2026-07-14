#!/usr/bin/env python3
"""Phase-25 T2: the ranked STRUCTURAL-FAMILY target manifest for the idiom-curriculum endgame.

Regroups the UNMATCHED frontier by structure (h_norm) instead of bytes (h_exact) — the Phase-24 reframe —
and emits, per family, the ONE exemplar to draft (its ov_SC01_077 member where present: the canonical harvest
overlay with cached Ghidra-C) + the family's leverage. An h_norm family is RELOC-ONLY by construction
(sig_image.norm_stream masks only jal/HI16/LO16, keeping registers+true immediates), so its members differ
ONLY in per-overlay symbol addresses; whether ONE C body matches all members is confirmed per-family by the
whole-binary byte-gate (T3 proves the magnitude; T7 banks each). Leverage = the family's INSTANCE count (how
many overlays carry it), NOT h_exact-reach (which is ~1-3 for a byte-shattered family).

  .venv/bin/python tools/family_manifest.py
  -> .run/family_manifest.json (full, ranked by byte-weight) + docs/family-manifest.md (digest, committed)

Ground truth = the sigs (they sign the ORIGINAL bytes, stable across matching); reproducible via
`make sig-overlays`. Companion to the frontier surveys .run/{analyze_frontier,probe_hnorm}.py.
"""
import json, glob, os, re, sys, collections

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import corpus   # the derived corpus oracle (Phase 26-A)

sig_by_ov = {}
for p in sorted(glob.glob(".run/sig.ov_*.jsonl")):
    ov = p.split("sig.")[1][:-6]
    recs = {}
    for line in open(p):
        line = line.strip()
        if not line:
            continue
        d = json.loads(line)
        recs[int(d["addr"], 16)] = (d["nins"], d["h_exact"], d["h_norm"])
    sig_by_ov[ov] = recs

# ---- THE MATCHED SET, DERIVED (Phase 26-A audit, HIGH — R33) --------------------------------------
# The old oracle asked ov_SC01_077 ALONE: matched := {h_exact of its non-stub fns} | dedup hashes.
# That is the wrong question. A function absent from that one overlay — or stubbed there but matched
# in the 133 others — came out "unmatched", so it was ranked as live work.
#
# MEASURED CONSEQUENCE: docs/family-manifest.md, the document the whole Phase-25/26 endgame is planned
# from, advertised "2,758 multi-member families / 11.0 MB of hidden leverage". 1,071 of them (6.80 MB,
# **62% of the advertised byte-weight**) were ALREADY FULLY MATCHED — pure phantom targets. A further
# 253 had their byte-weight inflated by already-matched members. The byte-weight RANKING — the entire
# purpose of the file, "draft these first" — was therefore sorted mostly on dead work, with the real
# targets buried underneath.
#
# The invariant answers it exactly, per overlay, with no oracle at all:
#   an h_exact class is WORK iff at least ONE of its instances is still an INCLUDE_ASM stub somewhere.
# (And the dedup-hash union is now redundant: a dedup-shared member is by definition not a stub. One
#  more scanner deleted — the `hash:` regex over config/dedup.us.yaml is gone.)
stub_by_ov = {ov: set(corpus.stubs(ov)) for ov in sig_by_ov}
sig077 = sig_by_ov.get("ov_SC01_077", {})
stub077 = stub_by_ov.get("ov_SC01_077", set())

# per h_exact class: which overlays carry it, and in which is it STILL A STUB
hexcls = {}
for ov, recs in sig_by_ov.items():
    st = stub_by_ov[ov]
    for v, (n, hx, hn) in recs.items():
        e = hexcls.setdefault(hx, {"ovs": set(), "stub_ovs": set(), "n": n, "rep": v, "hn": hn})
        e["ovs"].add(ov)
        if v in st:
            e["stub_ovs"].add(ov)
        if ov == "ov_SC01_077":
            e["rep"] = v

# UNMATCHED h_exact classes -> group by h_norm (the structural family)
fam = collections.defaultdict(lambda: {"hexclasses": 0, "instances": 0, "nins": 0, "bw": 0, "rep": 0, "maxhexreach": 0})
for hx, e in hexcls.items():
    if not e["stub_ovs"]:
        continue                        # fully matched fleet-wide -> NOT work (was: counted as work)
    n, hn, v = e["n"], e["hn"], e["rep"]
    r = len(e["stub_ovs"])              # the REAL x-N leverage: only the members still to bank
    f = fam[hn]
    f["hexclasses"] += 1
    f["instances"] += r
    f["bw"] += r * n * 4
    f["maxhexreach"] = max(f["maxhexreach"], len(e["ovs"]))
    if n >= f["nins"] or f["rep"] == 0:
        f["rep"] = v
        f["nins"] = n

# the draftable exemplar per family: the largest UNMATCHED ov_SC01_077 stub whose h_norm == the family
ov077_ex = {}   # h_norm -> (vram, nins)
for v, (n, hx, hn) in sig077.items():
    if v not in stub077:
        continue
    if hn not in ov077_ex or n > ov077_ex[hn][1]:
        ov077_ex[hn] = (v, n)


def bucket(n):
    return "tiny" if n < 20 else "small" if n < 50 else "med" if n < 100 else "large" if n < 150 else "GIANT"


rows = []
for hn, f in fam.items():
    ex = ov077_ex.get(hn)
    rows.append({
        "hnorm": hn,
        "rep_addr": f"0x{f['rep']:08x}",
        "ov077_exemplar": (f"0x{ex[0]:08x}" if ex else None),
        "n_hexcls": f["hexclasses"],
        "instances": f["instances"],
        "max_nins": f["nins"],
        "max_hex_reach": f["maxhexreach"],
        "byte_weight": f["bw"],
        "size_bucket": bucket(f["nins"]),
        "multi_member": f["hexclasses"] >= 2,
    })
rows.sort(key=lambda r: -r["byte_weight"])
json.dump(rows, open(".run/family_manifest.json", "w"), indent=0)

multi = [r for r in rows if r["multi_member"]]
with_ex = [r for r in multi if r["ov077_exemplar"]]

# classify the multi-member families by ov_SC01_077 membership -> the endgame's 3 levers
ov077_matched_hn = {hn for v, (n, hx, hn) in sig077.items() if v not in stub077}
lev = {"draftable": [0, 0], "matched_free": [0, 0], "absent": [0, 0]}
for r in multi:
    k = "draftable" if r["ov077_exemplar"] else ("matched_free" if r["hnorm"] in ov077_matched_hn else "absent")
    lev[k][0] += 1
    lev[k][1] += r["byte_weight"]

L = ["# Phase 25 — Structural-family target manifest (T2)\n"]
L.append("> Generated by `tools/family_manifest.py` from the 134 overlay sigs + ov_SC01_077 matched set + "
         "`config/dedup.us.yaml`. One exemplar per h_norm family, drafted from its **ov_SC01_077 member** where "
         "present. h_norm families are reloc-only by construction; whether one C body matches all members is "
         "confirmed per-family by the byte-gate (T3 magnitude / T7 banks). **Leverage = `inst` (fleet-wide member "
         "count), NOT `hexR` (h_exact-reach, ~1-3 for byte-shattered families).**\n")
L.append(f"**Families:** {len(rows)} · **multi-member (hidden leverage):** {len(multi)} / "
         f"{sum(r['byte_weight'] for r in multi)/1e6:.1f} MB · **with an ov_SC01_077 draftable exemplar:** {len(with_ex)}.\n")
L.append(f"**Endgame levers** (multi-member families × ov_SC01_077 membership): **draftable** {lev['draftable'][0]} / "
         f"{lev['draftable'][1]/1e6:.1f} MB (unmatched ov077 member → draft the exemplar, T5/T7) · **matched-free** "
         f"{lev['matched_free'][0]} / {lev['matched_free'][1]/1e6:.1f} MB (matched ov077 member + unmatched siblings → "
         f"free `--tier h_norm` propagation, T3) · **absent** {lev['absent'][0]} / {lev['absent'][1]/1e6:.1f} MB "
         f"(no ov077 member → draft from another overlay).\n")
L.append("| # | rep addr | ov077 exemplar | nins | hexcls | inst | hexR | byteMB | bucket |")
L.append("|--:|----------|----------------|-----:|-------:|-----:|-----:|-------:|--------|")
for i, r in enumerate(multi[:60], 1):
    L.append(f"| {i} | {r['rep_addr']} | {r['ov077_exemplar'] or '—'} | {r['max_nins']} | {r['n_hexcls']} | "
             f"{r['instances']} | {r['max_hex_reach']} | {r['byte_weight']/1e6:.2f} | {r['size_bucket']} |")
open("docs/family-manifest.md", "w").write("\n".join(L) + "\n")

print(f"families {len(rows)} | multi-member {len(multi)} ({sum(r['byte_weight'] for r in multi)/1e6:.1f} MB) | "
      f"ov077-draftable {len(with_ex)}")
print(f"levers: draftable {lev['draftable'][0]}/{lev['draftable'][1]/1e6:.1f}MB | "
      f"matched-free {lev['matched_free'][0]}/{lev['matched_free'][1]/1e6:.1f}MB | "
      f"absent {lev['absent'][0]}/{lev['absent'][1]/1e6:.1f}MB")
print("-> .run/family_manifest.json + docs/family-manifest.md")

# T3-ready picks: mid-size (100-150 ins) multi-member family, ov077-draftable, spanning most overlays
t3 = [r for r in multi if r["ov077_exemplar"] and 100 <= r["max_nins"] <= 150 and r["instances"] >= 100]
t3.sort(key=lambda r: (-r["instances"], -r["byte_weight"]))
print("\nT3 swing-question candidates (mid-size 100-150 ins, ov077-draftable, inst>=100):")
for r in t3[:10]:
    print(f"  ex={r['ov077_exemplar']} nins={r['max_nins']} inst={r['instances']} hexcls={r['n_hexcls']} "
          f"bw={r['byte_weight']/1e6:.2f}MB")
