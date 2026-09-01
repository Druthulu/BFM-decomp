#!/usr/bin/env python3
"""tools/verify_binary.py — the ONLY correct way to byte-verify one binary by hand. (P31 S69)

WHY THIS EXISTS, MEASURED THREE TIMES IN ONE SESSION.
`make build BINARY=<b>` is NOT a verification after a gate that touched `config/`. A carve bank
rewrites splat INPUTS (`JTBL_PADS` in `config/overlays.mk`, the binary's splat yaml), and `asm/` plus
the linker script are GENERATED FROM THEM. Build without re-extracting and you link newly-carved C
against stale extracted state; the SHA that comes out is meaningless.

S69 hit this THREE times, each time reading as a red binary:

    ov_SC04_011  got 9c94d36a want 8bc09c42  -> extract+build: BYTE-IDENTICAL
    ov_SC06_025  got 9cec1d36 want 04036155  -> extract+build: BYTE-IDENTICAL
    ov_SC06_022  (declared red, 23 edits reverted) -> extract+build: BYTE-IDENTICAL

The first cost a legitimate 96-line match, reverted on the false reading and restored later; the
third cost 23 legitimate declaration edits. **The rule was written down (§384) after the FIRST one
and violated twice more by reflex** — which is the whole argument for putting it in a tool instead of
in prose. A habit you have to remember at the exact moment you are impatient is not a control.

WHAT IT DOES
  * decides whether a re-extract is needed — `config/overlays.mk`, `config/splat.<b>.yaml` or
    `config/check.<b>.sha` newer than the binary's generated link inputs — and re-extracts when so;
  * `--always-extract` (default ON) removes the decision entirely: extract costs seconds, a wrong
    "red" costs a revert of good work. Pass `--no-extract` only when you have just extracted;
  * then builds with `-j` (never single-threaded: 7.18s -> 1.18s, 6.1x — and every tool that shells
    `make build` must pass it);
  * prints the SHA verdict and exits non-zero ONLY on a genuine mismatch.

  tools/verify_binary.py ov_SC06_022 [--no-extract] [--quiet]
  tools/verify_binary.py --all-touched          # every binary with uncommitted src/ or config/ changes
"""
import argparse
import glob
import os
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def sh(cmd, **kw):
    return subprocess.run(cmd, cwd=REPO, capture_output=True, text=True, **kw)


def config_touched(binary):
    """True when this binary's splat inputs are newer than its generated link inputs.

    Conservative BY DESIGN: if we cannot tell, say yes. A needless extract costs seconds; a skipped
    one costs a false red and, twice this session, reverted work.
    """
    cfgs = [os.path.join(REPO, "config", "overlays.mk"),
            os.path.join(REPO, "config", "splat.%s.yaml" % binary),
            os.path.join(REPO, "config", "check.%s.sha" % binary)]
    newest_cfg = max([os.path.getmtime(p) for p in cfgs if os.path.exists(p)] or [0])
    gen = glob.glob(os.path.join(REPO, "build", binary, "*.ld"))
    if not gen:
        return True
    return newest_cfg > min(os.path.getmtime(p) for p in gen)


def verify(binary, extract=True, quiet=False):
    if extract:
        why = "always" if extract == "always" else ("config newer" if config_touched(binary) else "")
        if why:
            if not quiet:
                print("[verify] %s: re-extracting (%s) — §384" % (binary, why), flush=True)
            r = sh(["make", "extract", "BINARY=" + binary])
            if r.returncode:
                print("[verify] %s: EXTRACT FAILED\n%s" % (binary, (r.stderr or r.stdout)[-400:]))
                return 2
    r = sh(["make", "build", "BINARY=" + binary, "-j"])          # -j always (6.1x, measured)
    out = r.stdout + r.stderr
    ok = "[ OK ]" in out
    if ok:
        if not quiet:
            print("[verify] %s: BYTE-IDENTICAL" % binary)
        return 0
    tail = [ln for ln in out.splitlines() if any(k in ln for k in ("[FAIL]", "got ", "want ", "Error"))]
    print("[verify] %s: MISMATCH\n  %s" % (binary, "\n  ".join(tail[-4:])))
    return 1


def touched_binaries():
    out = sh(["git", "status", "--porcelain", "--", "src/", "config/"]).stdout
    bins = set()
    for ln in out.splitlines():
        p = ln[3:].strip()
        parts = p.split("/")
        if p.startswith("src/") and len(parts) > 2:
            bins.add(parts[1])
        elif p.startswith("src/") and len(parts) == 2:
            bins.add("main")
        elif p.startswith("config/splat."):
            bins.add(os.path.basename(p)[len("splat."):-len(".yaml")])
    return sorted(bins)


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("binary", nargs="?")
    ap.add_argument("--all-touched", action="store_true",
                    help="verify every binary with uncommitted src/ or config/ changes")
    ap.add_argument("--no-extract", action="store_true",
                    help="skip the re-extract (ONLY when you just extracted — see §384)")
    ap.add_argument("--quiet", action="store_true")
    a = ap.parse_args()

    if a.all_touched:
        bins = touched_binaries()
        if not bins:
            print("[verify] nothing touched under src/ or config/")
            return 0
        print("[verify] %d touched binary/binaries: %s" % (len(bins), " ".join(bins)))
        bad = [b for b in bins if verify(b, extract=not a.no_extract and "always", quiet=a.quiet)]
        print("[verify] %d of %d verified BYTE-IDENTICAL" % (len(bins) - len(bad), len(bins)))
        if bad:
            print("[verify] MISMATCH: %s" % " ".join(bad))
        return 1 if bad else 0
    if not a.binary:
        ap.error("give a binary, or --all-touched")
    return verify(a.binary, extract=not a.no_extract and "always", quiet=a.quiet)


if __name__ == "__main__":
    sys.exit(main())
