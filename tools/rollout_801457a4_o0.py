#!/usr/bin/env python3
"""Move func_801457A4's INCLUDE_ASM stub from <ov>_after.c (-O2) into <ov>_o0b.c (-O0).

§116: `func_801457A4` is an -O0 function. In ov_SC01_077 its definition lives in
ov_SC01_077_o0b.c, which the Makefile's WHALE_O0B_OBJS wildcard compiles -O0. In every other
overlay the same function's stub sits in <ov>_after.c, which is -O2 — so `family_sweep --hseq`
templated the -O0-matched body into an -O2 TU and the byte-gate correctly rejected all 137.

The whale object's .text spans 0x80144B9C..0x801457A4, i.e. it ENDS exactly where this function
begins, so appending the function to that object places it at the same vram. The move is therefore
byte-neutral by construction and needs NO splat change — deliberately avoiding the Phase-29 Arm-A
re-carve wall (+0x20 data-symbol shift on 3 of 4 sampled overlays).

Byte-neutrality is not assumed: run R22 clean-fleet (140/140) on the move ALONE before sweeping.

  tools/rollout_801457a4_o0.py [--apply]     # default is a dry run

Out of scope: ov_SC07_{006,007,010,011} have no _o0b.c (onboarded in Phase 27, never whale-carved).
"""
import argparse
import glob
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
FN = "func_801457A4"
STUB_RE = re.compile(rf'^INCLUDE_ASM\("([^"]+)",\s*{FN}\);\s*$')

NOTE = (f"/* {FN} (@0x801457A4) is an -O0 function; its stub was moved to {{o0b}} (the -O0 whale\n"
        f" * object, whose .text ends exactly at this address) so it compiles at -O0. See there.\n"
        f" * Placement mirrors ov_SC01_077; byte-neutral (same vram). Cookbook §116. */")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--apply", action="store_true", help="write the changes (default: dry run)")
    a = ap.parse_args()

    moved, skipped = [], []
    for after in sorted(glob.glob(os.path.join(REPO, "src/ov_*/ov_*_after.c"))):
        ov = os.path.basename(os.path.dirname(after))
        o0b = os.path.join(REPO, f"src/{ov}/{ov}_o0b.c")
        text = open(after).read()
        lines = text.split("\n")
        hit = [i for i, ln in enumerate(lines) if STUB_RE.match(ln)]
        if not hit:
            continue
        if not os.path.exists(o0b):
            skipped.append((ov, "no _o0b.c (never whale-carved)"))
            continue
        if len(hit) != 1:
            skipped.append((ov, f"{len(hit)} stub lines, expected 1"))
            continue
        i = hit[0]
        stub = lines[i]
        lines[i] = NOTE.format(o0b=os.path.basename(o0b))
        body = open(o0b).read()
        if FN in body:
            skipped.append((ov, "_o0b.c already mentions the function"))
            continue
        if a.apply:
            open(after, "w").write("\n".join(lines))
            open(o0b, "w").write(body.rstrip("\n") + "\n\n" + stub + "\n")
        moved.append(ov)

    print(f"{'MOVED' if a.apply else 'WOULD MOVE'}: {len(moved)} overlays")
    for ov, why in skipped:
        print(f"  SKIP {ov}: {why}")
    if not a.apply:
        print("\n(dry run — pass --apply, then R22 clean-fleet BEFORE sweeping)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
