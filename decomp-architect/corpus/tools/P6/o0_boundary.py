#!/usr/bin/env python3
"""o0_boundary.py — find (and optionally bank) -O0 functions STRANDED at an -O0 region's end. (P31 S68)

THE SHAPE, byte-proven three times this session. An `-O0` function that is the FIRST function of the
`-O2` object immediately following an existing `-O0` region can be banked with **NO splat change at
all**, because that region's `.text` ends exactly at its address:

    - [0x5b020, c, ov_SC03_118_o0d]          <- -O0 region, .text ends at ...
    - [0x5b6d8, c, ov_SC03_118_jr_80183830]  <- ... exactly 0x80183830, where the stub sits

The edit is **ATOMIC ACROSS TWO FILES** — append the definition to `<ov>_o0<L>.c` AND delete the
`INCLUDE_ASM` from the following object's TU in one change — so the two object sizes cancel and no
address moves. Banked this way: `func_801457A4` x3 (79 ins, at the whale's end) and `func_80183830`
x2 (29 ins, one region lower). Cookbook §362 + its addendum.

WHY A SWEEP AND NOT `rollout_o0`. That driver refuses these for a bookkeeping reason rather than a
structural one — `family with exemplar func_80183830 not found in the map` — and it is separately
BLIND to any stub whose basename contains `_o0` (its `stub_file_of` skips them), which is exactly
where a carve puts them. The recipe does not need the family map, so this does not consult it.

COVERAGE (R32). The candidate set is derived from the splat yamls themselves — every `c` subseg whose
name matches `_o0<letter>` in every binary — crossed with `corpus.stubs` and the `o0_detect` prologue
tell. The denominator is printed and every rejected candidate is printed WITH ITS REASON, because a
sweep that reports only its hits cannot be distinguished from one that scanned nothing.

    tools/o0_boundary.py                 # report candidates fleet-wide
    tools/o0_boundary.py --binary ov_SC03_118
"""
import argparse
import collections
import glob
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(REPO)
sys.path.insert(0, os.path.join(REPO, "tools"))
import corpus          # noqa: E402
import progress        # noqa: E402
from o0_detect import detect_o0   # noqa: E402

SUBSEG = re.compile(r'^\s*-\s*\[\s*(0x[0-9a-fA-F]+)\s*,\s*c\s*,\s*([A-Za-z0-9_]+)\s*\]')
O0NAME = re.compile(r'_o0[a-z]?$')


def vram_base(binary):
    """The binary's code vram base, read from its own splat yaml (never hard-coded)."""
    for y in (("config/splat.us.exe.yaml",) if binary == "main"
              else ("config/splat.%s.yaml" % binary,)):
        if not os.path.exists(y):
            continue
        txt = open(y).read()
        m = re.search(r'^\s*vram:\s*(0x[0-9a-fA-F]+)', txt, re.M)
        s = re.search(r'^\s*start:\s*(0x[0-9a-fA-F]+)', txt, re.M)
        if m:
            return int(m.group(1), 16) - (int(s.group(1), 16) if s else 0)
    return None


def pairs(binary):
    """[(o0_subseg_name, next_subseg_name, boundary_vaddr)] from the splat yaml, in file order."""
    y = "config/splat.us.exe.yaml" if binary == "main" else "config/splat.%s.yaml" % binary
    if not os.path.exists(y):
        return []
    base = vram_base(binary)
    if base is None:
        return []
    rows = []
    for ln in open(y):
        m = SUBSEG.match(ln)
        if m:
            rows.append((int(m.group(1), 16), m.group(2)))
    out = []
    for i, (off, name) in enumerate(rows[:-1]):
        if O0NAME.search(name):
            noff, nname = rows[i + 1]
            out.append((name, nname, base + noff))
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--binary", help="one binary (default: every binary with an _o0 subseg)")
    a = ap.parse_args()

    bins = [a.binary] if a.binary else sorted(progress.BINARIES)
    scanned = collections.Counter()
    hits, rejected = [], []
    for b in bins:
        ps = pairs(b)
        if not ps:
            continue
        scanned["binaries with an _o0 subseg"] += 1
        try:
            st = {s.addr: s for s in corpus.stubs(b).values()}
        except Exception as e:
            rejected.append((b, "-", "-", "oracle refused: %r" % (e,)))
            continue
        for o0name, nxt, vaddr in ps:
            scanned["boundaries examined"] += 1
            s = st.get(vaddr)
            if s is None:
                rejected.append((b, o0name, "0x%08x" % vaddr, "no OPEN stub at the boundary"))
                continue
            sp = os.path.join(s.asm_dir, s.symbol + ".s")
            if not os.path.exists(sp):
                rejected.append((b, o0name, s.symbol, "no .s (run make extract)"))
                continue
            if not detect_o0(sp):
                rejected.append((b, o0name, s.symbol, "target is -O2 (no -O0 prologue tell)"))
                continue
            hits.append(dict(binary=b, o0_tu="src/%s/%s.c" % (b, o0name), stub_tu=s.path,
                             fn=s.symbol, addr="0x%08x" % vaddr,
                             nins=corpus.s_ins_count(sp)))

    print("scanned: %s" % dict(scanned))
    print("REJECTED %d boundary/-ies, with reasons:" % len(rejected))
    why = collections.Counter(r[3].split(":")[0] for r in rejected)
    for k, v in why.most_common():
        print("   %-42s %d" % (k, v))
    print()
    print("CANDIDATES (stranded -O0 at an -O0 region's end boundary): %d" % len(hits))
    for h in hits:
        print("   %-14s %-18s %-12s %4d ins   append to %s, drop stub from %s"
              % (h["binary"], h["fn"], h["addr"], h["nins"],
                 os.path.basename(h["o0_tu"]), os.path.basename(h["stub_tu"])))
    return 0


if __name__ == "__main__":
    sys.exit(main())
