#!/usr/bin/env python3
"""Emit wave_binary.js args from a fuel manifest (build_fuel_manifest.py output).

Selects draft-now targets (WAVE class, reach>=REACH, Ghidra-C cached), resolves the
per-function asm / asm_subdir / ghidra_c paths by globbing the overlay's asm tree,
and detects own_jtbl (an in-body computed jump: a `jr` to a register other than $ra).

Splits output into a NON-JTBL list (plain harvest_verify / family_sweep --hseq path)
and a JTBL list (needs the §8e carve path), sorted by leverage desc. Writes a
batch-sized wave-args file plus the full pool for later batches.

Usage:
  build_wave_args.py --fuel .run/fuel_ov_SC07_006.json --binary ov_SC07_006 \
      --batch 24 --out-prefix .run/wave_sc07006 --draft-dir .run/drafts-sc07006-b1
"""
import argparse, glob, json, os, re, sys

JR = re.compile(r"\bjr\s+\$(\w+)")

def has_own_jtbl(asm_path):
    try:
        with open(asm_path) as f:
            for line in f:
                for m in JR.finditer(line):
                    if m.group(1) != "ra":
                        return True
    except OSError:
        return False
    return False

def resolve_asm(binary, name):
    """Find func_<ADDR>.s under asm/<binary>/nonmatchings/*/. Returns (asm, subdir) or (None,None)."""
    hits = glob.glob(f"asm/{binary}/nonmatchings/*/{name}.s")
    if not hits:
        return None, None
    asm = hits[0]
    return asm, os.path.dirname(asm)

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--fuel", required=True)
    ap.add_argument("--binary", required=True)
    ap.add_argument("--reach", type=int, default=134)
    ap.add_argument("--batch", type=int, default=24)
    ap.add_argument("--out-prefix", required=True)
    ap.add_argument("--draft-dir", required=True)
    ap.add_argument("--klass", default="WAVE")
    ap.add_argument("--max-nins", type=int, default=150, help="skip GIANT-sized bodies")
    args = ap.parse_args()

    targets = json.load(open(args.fuel))["targets"]
    pool = [t for t in targets
            if t["class"] == args.klass and t["reach"] >= args.reach
            and t.get("cached") and t["nins"] <= args.max_nins]
    pool.sort(key=lambda t: -t["leverage"])

    recs_nonjtbl, recs_jtbl, missing = [], [], []
    for t in pool:
        name = t["name"]
        asm, subdir = resolve_asm(args.binary, name)
        if asm is None:
            missing.append(name)
            continue
        rec = {
            "name": name, "addr": t["addr"], "nins": t["nins"], "reach": t["reach"],
            "asm": asm, "asm_subdir": subdir, "ghidra_c": f".run/ghidra_c/{name}.c",
            "own_jtbl": has_own_jtbl(asm), "o0": False, "sibling_ov077": None,
            "leverage": t["leverage"], "region": t.get("region"),
        }
        (recs_jtbl if rec["own_jtbl"] else recs_nonjtbl).append(rec)

    batch = recs_nonjtbl[:args.batch]
    b1 = {"binary": args.binary, "draftDir": args.draft_dir, "targets": batch}
    json.dump(b1, open(f"{args.out_prefix}_b1_args.json", "w"), indent=1)
    json.dump(recs_nonjtbl, open(f"{args.out_prefix}_nonjtbl_pool.json", "w"), indent=1)
    json.dump(recs_jtbl, open(f"{args.out_prefix}_jtbl_pool.json", "w"), indent=1)

    print(f"binary={args.binary} reach>={args.reach} class={args.klass} cached-pool={len(pool)}")
    print(f"  non-jtbl: {len(recs_nonjtbl)}  jtbl: {len(recs_jtbl)}  asm-missing: {len(missing)}")
    if missing:
        print(f"  missing asm (skipped): {missing[:8]}{'...' if len(missing)>8 else ''}")
    print(f"  batch-1 = top {len(batch)} non-jtbl by leverage "
          f"(sum leverage {sum(r['leverage'] for r in batch)}):")
    for r in batch:
        print(f"    {r['name']} {r['addr']} nins={r['nins']} reach={r['reach']} lever={r['leverage']}")
    print(f"  -> {args.out_prefix}_b1_args.json / _nonjtbl_pool.json / _jtbl_pool.json")

if __name__ == "__main__":
    main()
