#!/usr/bin/env python3
"""Link every used object of a PsyQ library and byte-verify each against the BFM EXE.

Driver over `psyq_identify.py` (placement) + `psyq_link.link_object` (per-object byte link).
For a library's ELF-object dir it:
  1. runs psyq_identify to get {object: text_vram} for the objects the EXE actually links,
  2. links each object at its vram, recovering externals from the EXE relocations,
  3. byte-compares each `.text`, prints a PASS/FAIL table + summary,
  4. aggregates recovered externals across objects and flags any inconsistency (the same
     symbol recovered to two addresses = a bug to investigate),
  5. writes a JSON report to .run/psyq_link.<lib>.json (consumed by the build-wiring step 2'.3).

Usage:  psyq_link_lib.py <elf_dir> [text_lo text_hi]      e.g. .run/obj40/libcd
"""
import json, os, re, subprocess, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from psyq_link import link_object, VRAM_BASE  # noqa: E402  (VRAM_BASE = transitional default, removed T8)

EXE = "extracted/retail/SLUS_007.26"


def placement(elf_dir, lo, hi, vram_base=VRAM_BASE, exe=EXE):
    cmd = ["python3", "tools/psyq_identify.py", elf_dir]
    if lo and hi:
        cmd += [lo, hi]
    cmd += ["--vram-base", hex(vram_base), "--exe", exe]
    out = subprocess.check_output(cmd, text=True)
    placed = {}
    for ln in out.splitlines():
        m = re.match(r"\s+0x([0-9A-Fa-f]+)\s+(\S+\.o)\s+\((\d+) ins\)", ln)
        if m:
            placed[m.group(2)] = int(m.group(1), 16)
    return placed, out


def main():
    import argparse
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("elf_dir")
    ap.add_argument("window", nargs="*", help="optional scan-narrowing window: text_lo text_hi")
    ap.add_argument("--vram-base", default=hex(VRAM_BASE),
                    help="fileoff->vram delta of the target binary (default the EXE's; required T8)")
    ap.add_argument("--exe", default=EXE, help="target binary path (default: the retail EXE)")
    args = ap.parse_args()
    elf_dir = args.elf_dir
    lo = args.window[0] if len(args.window) > 0 else None
    hi = args.window[1] if len(args.window) > 1 else None
    vram_base = int(args.vram_base, 0)
    lib = os.path.basename(elf_dir.rstrip("/"))

    placed, idout = placement(elf_dir, lo, hi, vram_base, args.exe)
    print(idout.strip())
    print(f"\n=== linking {len(placed)} located {lib} objects ===")

    exe = open(args.exe, "rb").read()
    results, all_ext = [], {}
    conflicts = []
    npass = 0
    for name, vram in sorted(placed.items(), key=lambda kv: kv[1]):
        obj = os.path.join(elf_dir, name)
        r = link_object(obj, vram, name=name, exe_bytes=exe, vram_base=vram_base)
        results.append(r)
        tag = "PASS" if r["ok"] else "FAIL"
        if r["ok"]:
            npass += 1
        extra = ""
        if not r["ok"]:
            extra = "  " + (r.get("error") or f"{r.get('ndiff','?')} word(s) diff @ "
                            f"{hex(r['first_diff']) if r.get('first_diff') else '(size)'}")
        print(f"  [{tag}] 0x{vram:08X}  {name:12s} ({r['tsize']:5d} B){extra}")
        for s, a in r["externals"].items():
            if s in all_ext and all_ext[s] != a:
                conflicts.append((s, all_ext[s], a, name))
            all_ext.setdefault(s, a)

    print(f"\n{npass}/{len(results)} objects byte-identical (.text)")
    if conflicts:
        print("  !! external address conflicts:")
        for s, a0, a1, nm in conflicts:
            print(f"     {s}: 0x{a0:08X} vs 0x{a1:08X} (at {nm})")
    print(f"  {len(all_ext)} distinct externals recovered across the library")

    rep = {
        "lib": lib,
        "elf_dir": elf_dir,
        "objects": [
            {"name": r["name"], "text_vram": r["text_vram"], "tsize": r["tsize"],
             "rdata_vram": r["rdata_vram"] if isinstance(r["rdata_vram"], int) else None,
             "data_vram": r["data_vram"] if isinstance(r["data_vram"], int) else None,
             "ok": r["ok"], "externals": {s: a for s, a in r["externals"].items()},
             "unrecovered": r["unrecovered"]}
            for r in results
        ],
        "externals_union": all_ext,
        "conflicts": [{"sym": s, "a": a0, "b": a1, "at": nm} for s, a0, a1, nm in conflicts],
        "npass": npass, "ntotal": len(results),
    }
    os.makedirs(".run", exist_ok=True)
    path = f".run/psyq_link.{lib}.json"
    json.dump(rep, open(path, "w"), indent=1)
    print(f"  report -> {path}")
    sys.exit(0 if npass == len(results) else 1)


if __name__ == "__main__":
    main()
