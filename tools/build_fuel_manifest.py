#!/usr/bin/env python3
"""build_fuel_manifest.py — Phase 21 (T1): the automation-run target pool.

Unifies the live INCLUDE_ASM stubs of the canonical harvest overlay (ov_SC01_077)
into ONE ranked, class-tagged, cache-annotated manifest (.run/fuel_manifest.json),
the fuel for the worker/grinder automation.

R14-honest reach: reach is RECOMPUTED here from the current 134 overlay sigs
(distinct-overlay h_exact histogram), NOT trusted from any cached field — Phase 20
proved a cached "reach-134" label can conflate function-present-at-vram with
byte-identical (the -O0 cluster). The 28 giants are independently verified to be
genuinely byte-identical x134; the -O0 cluster is independently shown overlay-local
(reach ~1). Whole-binary harvest_verify remains the sole byte-gate (G3/P9); this
manifest only routes/ranks work.

Classes: O0 (per-file -O0 split build-infra) · O1 (func_80161A90, -O1 split) ·
GIANT (>150 ins, reach-134, verified) · WAVE/PINS/STRUCT/STUB (exemplar_miner lever).
Separately: CAPPED = the 7 matched-but-local fns (recovery pool, not draft fuel).

Usage: .venv/bin/python tools/build_fuel_manifest.py [--source ov_SC01_077] [--out .run/fuel_manifest.json]
Read-only except the manifest write.
"""
import argparse, glob, json, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import corpus   # the derived corpus oracle (Phase 26-A) — never an allowlist

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GOOD_SHA = "d19c9580a02dc63ba1f0e7e0c770f3b10de35635"  # ov_SC01_077 byte-locked reference
INS_RE = re.compile(r"/\* [0-9A-Fa-f]+ [0-9A-Fa-f]{8} [0-9A-Fa-f]{8} \*/")
STUB_RE = re.compile(r"INCLUDE_ASM\([^,]+,\s*(\w+)\)")
FUNC_RE = re.compile(r"^func_[0-9A-Fa-f]{6,8}$")  # address-named fns only (skip curated/named stubs)

# The 7 reach-134 matched-but-local fns (Phase-20 backlog) — recovery pool, not draft fuel.
CAPPED = ["func_80142B2C", "func_801535F4", "func_80155E30", "func_80157580",
          "func_801576A8", "func_80168F40", "func_80170B48"]
O1_FNS = ["func_80161A90"]  # built -O1 inside the -O2 overlay (needs an -O1 split file)


def addr_int(name_or_addr):
    s = name_or_addr.lower().replace("func_", "").replace("0x", "")
    return int(s, 16)


def reach_histogram():
    """distinct-overlay h_exact -> count, over all 134 .run/sig.ov_*.jsonl (authoritative reach)."""
    hist = {}
    sigs = sorted(glob.glob(os.path.join(REPO, ".run/sig.ov_*.jsonl")))
    for p in sigs:
        seen = set()
        with open(p) as f:
            for line in f:
                line = line.strip()
                if not line:
                    continue
                h = json.loads(line).get("h_exact")
                if h:
                    seen.add(h)
        for h in seen:
            hist[h] = hist.get(h, 0) + 1
    return hist, len(sigs)


def load_src_h_exact(source):
    """addr(int) -> {h_exact, nins, ncalls, name} from the source overlay's own sig."""
    by_addr = {}
    p = os.path.join(REPO, f".run/sig.{source}.jsonl")
    with open(p) as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            r = json.loads(line)
            by_addr[addr_int(r["addr"])] = {
                "h_exact": r["h_exact"], "nins": r["nins"],
                "ncalls": r.get("ncalls", 0), "name": r["name"]}
    return by_addr


def live_stubs(source):
    """name -> region ('main'|'a'|'o0'|'o0b'|'after'|'jr_<ADDR>') for every func_<hex> INCLUDE_ASM
    stub. Returns (stubs, named_skipped).

    DERIVED from tools/corpus.py — no file allowlist (Phase 26-A audit, CRITICAL).

    This function used to read a hardcoded 3-file dict {<ov>.c, _a.c, _o0.c}. ov_SC01_077 has
    FOURTEEN .c files, so it saw 30 of 264 stubs and reported success. Downstream, worklist.py
    (100% of its rows) and wave_targets.py (100% of its pools) consume this manifest, so
    **91.6% of all remaining project gain was invisible to target selection**, and 117 of the
    127 reach-134 functions — the entire high-ROI band — were never nominated by anything.

    It rotted silently: .run/fuel_manifest.json (2026-07-08) recorded 130 stubs; the same code
    today returns 30, because the Phase-26 jr splits moved ~100 stubs out from under a dict
    literal last edited in Phase 22. NOBODY NOTICED, BECAUSE A TARGET THAT IS NEVER NOMINATED
    PRODUCES SILENCE, NOT AN ERROR. Never re-introduce an allowlist here: the next split would
    re-open the hole. The filesystem already knows."""
    out, skipped = {}, []
    for st in corpus.stubs(source).values():
        if FUNC_RE.match(st.symbol):
            out[st.symbol] = st.region
        else:
            skipped.append(st.symbol)      # curated-name stub (listCdBuffer) — reported, not silent
    return out, skipped


def nins_from_asm(source, name):
    """Instruction count from the function's .s — located via the stub that names it.

    The INCLUDE_ASM line is self-describing (its first arg IS the asm subdir), so there is nothing
    to guess. The old form hardcoded asm/<ov>/nonmatchings/<ov>/ and therefore returned None for
    every function in a split TU — i.e. for 234 of the overlay's 264 stubs."""
    st = corpus.stubs(source)
    hit = next((s for s in st.values() if s.symbol == name), None)
    if hit is None:
        return None
    p = os.path.join(REPO, hit.asm_path)
    if not os.path.exists(p):
        return None
    return len(INS_RE.findall(open(p, errors="replace").read()))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--source", default="ov_SC01_077")
    ap.add_argument("--out", default=".run/fuel_manifest.json")
    ap.add_argument("--emit-prefetch", metavar="PATH", default=None,
                    help="also write the UNCACHED ROI-pool addrs (hex, no 0x) here for "
                         "DecompileFunctions.java (reproducible T2 fuel prefetch). ROI pool = "
                         "reach>=2 OR class in {O0,O1} OR a capped-recovery fn.")
    a = ap.parse_args()
    src = a.source

    hist, n_overlays = reach_histogram()
    src_sig = load_src_h_exact(src)
    stubs, named_skipped = live_stubs(src)
    o0_set = {fn for fn, tag in stubs.items() if tag in ("o0", "o0b")}

    # exemplar_miner routing: addr(int) -> {lever, bucket, mismatch}
    routing = {}
    rp = os.path.join(REPO, ".run/exemplar_routing.json")
    if os.path.exists(rp):
        for k, v in json.load(open(rp)).items():
            routing[addr_int(v.get("addr", k))] = v

    giants = json.load(open(os.path.join(REPO, ".run/giants.json")))
    giant_addrs = {addr_int(g["addr"]) for g in giants}
    cached = {os.path.basename(p)[:-2] for p in glob.glob(os.path.join(REPO, ".run/ghidra_c/*.c"))}

    def reach_of(name):
        s = src_sig.get(addr_int(name))
        return hist.get(s["h_exact"], 1) if s else None

    def classify(name, tag, ai, nins):
        if tag in ("o0", "o0b"):
            return "O0"
        if name in O1_FNS:
            return "O1"
        if ai in giant_addrs and (nins or 0) > 150:
            return "GIANT"
        lev = routing.get(ai, {}).get("lever")
        return lev or "WAVE"

    targets = []
    for name, tag in sorted(stubs.items(), key=lambda kv: addr_int(kv[0])):
        ai = addr_int(name)
        s = src_sig.get(ai)
        nins = (s or {}).get("nins") or nins_from_asm(src, name)
        rch = reach_of(name)
        r = routing.get(ai, {})
        targets.append({
            "addr": f"0x{ai:08x}", "name": name, "nins": nins,
            "ncalls": (s or {}).get("ncalls"), "reach": rch,
            "reach_134": rch == n_overlays, "class": classify(name, tag, ai, nins),
            "lever": r.get("lever"), "bucket": r.get("bucket"),
            "cached": name in cached, "region": tag,
            "leverage": (rch or 1) * (nins or 0)})
    targets.sort(key=lambda t: (t["leverage"], t["reach"] or 0, t["nins"] or 0), reverse=True)

    # ---- R14 verification: giants genuinely x134? -O0 cluster overlay-local? ----
    giant_check = []
    for g in giants:
        ai = addr_int(g["addr"]); s = src_sig.get(ai)
        rch = hist.get(s["h_exact"], 1) if s else None
        giant_check.append({"name": g["name"], "nins": g["nins"],
                            "cached_reach": g.get("reach"), "verified_reach": rch,
                            "is_134": rch == n_overlays, "still_stub": g["name"] in stubs})
    giants_ok = sum(1 for c in giant_check if c["is_134"])
    o0_check = []
    for fn in sorted(o0_set | {t["name"] for t in targets if t["class"] == "O0"}):
        ai = addr_int(fn); s = src_sig.get(ai)
        o0_check.append({"name": fn, "verified_reach": hist.get(s["h_exact"], 1) if s else None})
    o0_local = [c["name"] for c in o0_check if (c["verified_reach"] or 1) < n_overlays]
    o0_shared = [c["name"] for c in o0_check if c["verified_reach"] == n_overlays]

    by_class, cached_n = {}, 0
    for t in targets:
        by_class[t["class"]] = by_class.get(t["class"], 0) + 1
        cached_n += 1 if t["cached"] else 0
    reach_buckets = {}
    for t in targets:
        b = "134" if t["reach"] == n_overlays else ("2-133" if (t["reach"] or 1) > 1 else "1")
        reach_buckets[b] = reach_buckets.get(b, 0) + 1

    manifest = {
        "note": "Phase-21 automation fuel pool. reach RECOMPUTED from current sigs (R14-honest, "
                "distinct-overlay h_exact). Byte-gate (harvest_verify) is the sole arbiter (G3/P9).",
        "source_overlay": src, "good_sha": GOOD_SHA, "n_overlays": n_overlays,
        "reach_verification": {
            "giants_claimed": len(giants), "giants_verified_134": giants_ok,
            "giants_discrepant": [c for c in giant_check if not c["is_134"]],
            "giants": giant_check,
            "o0_overlay_local": o0_local, "o0_reach_134": o0_shared,
            "o0_cluster": o0_check},
        "summary": {"total_stubs": len(targets), "by_class": by_class,
                    "cached": cached_n, "uncached": len(targets) - cached_n,
                    "reach_buckets": reach_buckets, "ghidra_c_cache_total": len(cached),
                    "named_stubs_skipped": named_skipped},
        "capped_recovery": CAPPED,
        "targets": targets}
    outp = os.path.join(REPO, a.out)
    json.dump(manifest, open(outp, "w"), indent=1)

    if a.emit_prefetch:
        cap_uncached = [c for c in CAPPED if c not in cached]
        pool = {t["name"] for t in targets
                if not t["cached"] and ((t["reach"] or 1) >= 2 or t["class"] in ("O0", "O1"))}
        pool |= set(cap_uncached)
        lines = sorted(n[len("func_"):] for n in pool)  # hex, no 0x, for DecompileFunctions.java
        with open(os.path.join(REPO, a.emit_prefetch), "w") as f:
            f.write("\n".join(lines) + ("\n" if lines else ""))
        print(f"  prefetch addr-list -> {a.emit_prefetch} ({len(lines)} uncached ROI-pool fns)")

    print(f"fuel manifest -> {a.out}")
    print(f"  overlays signed: {n_overlays} | live stubs: {len(targets)} | "
          f"ghidra_c cached: {len(cached)} (manifest cached {cached_n}, uncached {len(targets)-cached_n})")
    print(f"  by class: {by_class}")
    print(f"  reach buckets: {reach_buckets}")
    print(f"  R14 giants: {giants_ok}/{len(giants)} verified reach-{n_overlays}"
          + ("" if giants_ok == len(giants) else f"  DISCREPANT: {[c['name'] for c in giant_check if not c['is_134']]}"))
    print(f"  R14 -O0 cluster: {len(o0_local)}/{len(o0_check)} overlay-local (reach<{n_overlays}); "
          f"{len(o0_shared)}/{len(o0_check)} reach-{n_overlays}"
          + (f" -> {o0_shared}" if o0_shared else ""))


if __name__ == "__main__":
    main()
