#!/usr/bin/env python3
"""Bank func_801457A4 across the fleet by moving its DEFINITION into <ov>_o0b.c (the -O0 object).

§116: `func_801457A4` is an -O0 function. In ov_SC01_077 its definition lives in
ov_SC01_077_o0b.c, which the Makefile's WHALE_O0B_OBJS wildcard compiles -O0. In every other
overlay the same function's stub sits in <ov>_after.c, which is -O2 — so `family_sweep --hseq`
templated the -O0-matched body into an -O2 TU and the byte-gate correctly rejected all 137.

WHY THIS TOOL EXISTS AND family_sweep CANNOT DO IT (Phase 29 T80, the refuted shortcut):
the obvious move is to relocate the member's `INCLUDE_ASM(...)` line into <ov>_o0b.c and let the
existing sweep stage there. That is NOT byte-neutral — it is unbuildable. splat emits
`asm/<ov>/nonmatchings/<seg>/<fn>.s` for EXACTLY the functions the segment's own .c marks with
INCLUDE_ASM (measured: 12 lines <-> 12 .s files, identical sets). Delete the line from
<ov>_after.c and the .s stops being generated, so the relocated reference cannot assemble.
`asm/` follows the SEGMENT; object membership follows the .c FILE.

So the substitution has to be ATOMIC ACROSS TWO FILES — append the remapped body to <ov>_o0b.c
AND drop the INCLUDE_ASM from <ov>_after.c in one edit — which `harvest_verify`/`family_sweep`
do not do (they substitute a draft for a stub *in the stub's own file*). Hence this driver.
Deliberately no splat change: a re-carve is the Phase-29 Arm-A wall (+0x20 data-symbol shift on
3 of 4 sampled overlays).

The whole-binary byte-gate stays the sole arbiter (G3/P9): per overlay, build and compare against
config/check.<ov>.sha; on any mismatch BOTH files are restored from their snapshots.

  tools/rollout_801457a4_o0.py [--apply] [--limit N] [--jobs N]

Out of scope: ov_SC07_{006,007,010,011} have no _o0b.c (onboarded in Phase 27, never whale-carved).
"""
import argparse
import concurrent.futures as futures
import glob
import hashlib
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, "tools"))
import family_remap as FR  # noqa: E402

FN = "func_801457A4"
ADDR = 0x801457A4
EX_OV = "ov_SC01_077"
STUB_RE = re.compile(rf'^INCLUDE_ASM\("([^"]+)",\s*{FN}\);\s*$', re.M)

NOTE = (f"/* {FN} (@0x{ADDR:08X}) is an -O0 function; its definition lives in {{o0b}} (the -O0\n"
        f" * whale object, whose .text ends exactly at this address). Mirrors ov_SC01_077. §116 */")


def sha1(p):
    h = hashlib.sha1()
    with open(p, "rb") as fh:
        for b in iter(lambda: fh.read(1 << 20), b""):
            h.update(b)
    return h.hexdigest()


def good_sha(ov):
    return open(os.path.join(REPO, f"config/check.{ov}.sha")).read().split()[0]


def build_ok(ov):
    r = subprocess.run(["make", "build", f"BINARY={ov}"], cwd=REPO,
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    out = os.path.join(REPO, f"build/{ov}/{ov}")
    return r.returncode == 0 and os.path.exists(out) and sha1(out) == good_sha(ov)


def candidates():
    out = []
    for after in sorted(glob.glob(os.path.join(REPO, "src/ov_*/ov_*_after.c"))):
        ov = os.path.basename(os.path.dirname(after))
        o0b = os.path.join(REPO, f"src/{ov}/{ov}_o0b.c")
        if not os.path.exists(o0b):
            continue                                   # never whale-carved (the 4 SC07 tail overlays)
        if not STUB_RE.search(open(after).read()):
            continue                                   # already banked, or no stub here
        out.append((ov, after, o0b))
    return out


def attempt(ov, after, o0b, apply):
    draft, info = FR.remap_hseq(ADDR, EX_OV, ov, ADDR)
    if draft is None:
        return ov, "remap-refused", str(info)[:60]
    a_txt, b_txt = open(after).read(), open(o0b).read()
    m = STUB_RE.search(a_txt)
    new_after = a_txt[:m.start()] + NOTE.format(o0b=os.path.basename(o0b)) + a_txt[m.end():]
    new_o0b = b_txt.rstrip("\n") + "\n\n" + draft.rstrip("\n") + "\n"
    if not apply:
        return ov, "would-try", ""
    open(after, "w").write(new_after)
    open(o0b, "w").write(new_o0b)
    if build_ok(ov):
        return ov, "BANKED", ""
    open(after, "w").write(a_txt)                       # restore BOTH, always (§61)
    open(o0b, "w").write(b_txt)
    return ov, "gate-reject", ""


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--apply", action="store_true", help="write + gate (default: dry run)")
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--jobs", type=int, default=1, help="overlays gated in parallel (distinct binaries)")
    a = ap.parse_args()

    cands = candidates()
    if a.limit:
        cands = cands[:a.limit]
    print(f"in scope: {len(cands)} overlays", flush=True)

    res = []
    if a.jobs > 1 and a.apply:
        with futures.ThreadPoolExecutor(max_workers=a.jobs) as ex:
            for r in ex.map(lambda c: attempt(*c, a.apply), cands):
                res.append(r)
                print(f"  {r[0]}: {r[1]} {r[2]}", flush=True)
    else:
        for c in cands:
            r = attempt(*c, a.apply)
            res.append(r)
            print(f"  {r[0]}: {r[1]} {r[2]}", flush=True)

    from collections import Counter
    print(Counter(r[1] for r in res))
    return 0


if __name__ == "__main__":
    sys.exit(main())
