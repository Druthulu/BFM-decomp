#!/usr/bin/env python3
"""disc_code_sweep.py — find code-bearing PAC payloads the onboarding may have missed (Phase-27 T7).

The disc-completeness question the byte-gate is structurally blind to (R34): the build only touches
binaries someone ONBOARDED, so a code payload no one onboarded is invisible to `make check-all` no
matter how green it is. The Phase-27 audit found four such overlays (SC07 FILE_006/007/010/011, code
at PAC entry 1 not 0). This sweeps EVERY extracted PAC payload and reports which decode as MIPS code,
so the onboarded set can be reconciled against the disc rather than trusted.

Method (reuses sig_image's exact rabbitizer decode): decode the first `--window` words of each raw
payload as MIPS-LE, report the fraction rabbitizer calls valid. Overlay/EXE code runs ~0.97-1.00
valid; data/graphics/audio sit far lower. A payload above `--threshold` that is NOT already onboarded
is a candidate the audit must explain (onboard it, or record why it is not a build binary — e.g. a
type-1 blob that loads at its own address like the resident, needing load-address analysis first).

COVERAGE-ASSERTED (R32): every extracted `{index}.{type}` payload is classified; the onboarded set is
cross-checked so a hit that is already a binary is labelled, not re-flagged.

  tools/disc_code_sweep.py                 # sweep all types, print the report
  tools/disc_code_sweep.py --types 1,6,7   # only the non-type-4 unknowns
"""
import argparse
import glob
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import sig_image   # make_insn — the shared rabbitizer decode (GTE-aware)

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
# a raw payload is <dir>/<index>.<type> with NO .dec suffix; type-4 also has a .dec sibling
_PAYLOAD = re.compile(r"/(\d+)\.(\d+)$")


def onboarded_payloads():
    """The set of payload paths already wired as a build binary (main, resident, every overlay).
    Read from the Makefile/overlays.mk *_EXE assignments — the single source of truth (R33)."""
    paths = set()
    for mk in ("Makefile", "config/overlays.mk"):
        p = os.path.join(REPO, mk)
        if not os.path.exists(p):
            continue
        for m in re.finditer(r"^\w+_EXE\s*:=\s*(\S+)", open(p).read(), re.M):
            paths.add(os.path.normpath(m.group(1)))
    return paths


_JR_RA = 0x03E00008   # `jr $ra` — a function return; the discriminator rabbitizer.isValid() lacks


def code_signals(path, window):
    """(valid_ratio, jr_ra_density, nwords). isValid() alone is too permissive — structured DATA
    decodes ~100% valid (type-0/type-2 blobs hit 1.00 with ZERO returns). Real MIPS code carries a
    `jr $ra` roughly once per function (~2.9-3.4% of words across the onboarded overlays + resident);
    data carries ~0%. Requiring BOTH separates code from valid-looking data (verified against the
    positive controls)."""
    data = open(path, "rb").read()
    n = min(window, len(data) // 4)
    if n == 0:
        return 0.0, 0.0, 0
    ok = jr = 0
    for k in range(n):
        word = struct.unpack_from("<I", data, k * 4)[0]
        if sig_image.make_insn(word, 0x80000000 + k * 4).isValid():
            ok += 1
        if word == _JR_RA:
            jr += 1
    return ok / n, jr / n, n


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--root", default="extracted/retail")
    ap.add_argument("--types", default=None, help="comma list of PAC types to sweep (default: all)")
    ap.add_argument("--window", type=int, default=4096, help="words decoded per payload")
    ap.add_argument("--threshold", type=float, default=0.90, help="valid-ratio floor")
    ap.add_argument("--jr-min", type=float, default=0.01, help="jr-$ra density floor (code ~0.03, data ~0)")
    a = ap.parse_args()

    want = set(a.types.split(",")) if a.types else None
    onboard = onboarded_payloads()

    rows, seen = [], 0
    for p in sorted(glob.glob(os.path.join(REPO, a.root, "**"), recursive=True)):
        if not os.path.isfile(p) or p.endswith(".dec"):
            continue
        m = _PAYLOAD.search(p)
        if not m:
            continue
        typ = m.group(2)
        if want and typ not in want:
            continue
        seen += 1
        rel = os.path.relpath(p, REPO)
        ratio, jr, nwords = code_signals(p, a.window)
        is_code = ratio >= a.threshold and jr >= a.jr_min       # BOTH signals (jr is the discriminator)
        rows.append((typ, ratio, jr, nwords, rel, os.path.normpath(rel) in onboard, is_code))

    assert len(rows) == seen, f"classified {len(rows)} of {seen} payloads — a silent skip (R32)"

    hidden = [r for r in rows if r[6] and not r[5]]

    by_type = {}
    for typ, ratio, jr, _, _, onb, is_code in rows:
        d = by_type.setdefault(typ, [0, 0, 0])
        d[0] += 1
        d[1] += is_code
        d[2] += is_code and onb

    print(f"disc code sweep — {seen} payloads under {a.root}"
          + (f" (types {a.types})" if want else "")
          + f", window={a.window}w, valid>={a.threshold}, jr_ra>={a.jr_min}")
    print(f"{'type':>4} {'payloads':>9} {'code':>5} {'onboarded':>9} {'HIDDEN':>7}")
    for typ in sorted(by_type):
        tot, c, onb = by_type[typ]
        print(f"{typ:>4} {tot:>9} {c:>5} {onb:>9} {c - onb:>7}")

    print(f"\nHIDDEN code-bearing payloads (valid>={a.threshold} AND jr_ra>={a.jr_min}, NOT onboarded): {len(hidden)}")
    for typ, ratio, jr, nwords, rel, _, _ in sorted(hidden, key=lambda r: -r[2]):
        print(f"  type {typ}  valid {ratio:5.1%}  jr_ra {jr:5.2%} ({nwords}w)  {rel}")
    if not hidden:
        print("  (none — the onboarded set accounts for every code-bearing payload the sweep sees)")
    return 0 if not hidden else 3


if __name__ == "__main__":
    sys.exit(main())
