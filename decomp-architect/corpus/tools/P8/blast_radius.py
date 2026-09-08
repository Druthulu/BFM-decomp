#!/usr/bin/env python3
"""blast_radius.py — MEASURE the write set and name the gate it actually requires (§63 enforcement).

THE PROBLEM THIS SOLVES. §63 has defined a blast-radius taxonomy since Phase 26:

    T0  draft-only (.run/**)          -> no gate; nothing in the build tree changed
    T1  binary-local (src/<bin>/**)   -> the PER-BINARY gate is SUFFICIENT
    T2  fleet-shared (src/shared/**,  -> R22 clean-fleet is MANDATORY
        tools/, Makefile, us-wide config)

...and it has never been ENFORCED. Two consequences, both measured in Phase-29 SESSION-20:

  * OVER-VERIFICATION. That session ran ~13 full clean-fleet verifies (~15 min each), most of them
    for batches that were provably T1. Hours of serialised wall-clock spent proving something the
    written rule already guaranteed.
  * UNDER-VERIFICATION, twice, and this is the dangerous half. The §85 return-type widen was BELIEVED
    contained to one overlay; it broke ov_SC01_077 (R22 139/140) because the source overlay carries
    its own local `extern void` decls. And gate_stage's ARITY pre-pass silently rewrote caller decls
    in 40 TUs. In BOTH cases the write set was larger than the belief about it.

So the value is not only speed. **A tier is a CLAIM about the write set; this tool turns it into a
measurement.** `--expect t1` fails loud when the tree disagrees, which is exactly the shape of error
that produced both incidents above.

COVERAGE IS ASSERTED (R32). Every changed path must match a rule. An unclassified path is a DEFECT,
not a no-op: it exits non-zero and names the path, because a silent skip here would re-create the
exact blindness the taxonomy exists to remove. The binary list is DERIVED from config/splat.*.yaml
(R33), never hardcoded — Phase-28's R36 incident was a hardcoded set missing 4 real binaries.

  tools/blast_radius.py                        # report the tier + the gate it requires
  tools/blast_radius.py --expect t1 --binary ov_SC01_000   # assert containment; non-zero if exceeded
  tools/blast_radius.py --json
"""
import argparse
import glob
import json
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def binaries():
    """DERIVED (R33): every binary that has a splat config. Never a hardcoded list (R36)."""
    out = set()
    for p in glob.glob(os.path.join(REPO, "config", "splat.*.yaml")):
        b = os.path.basename(p)[len("splat."):-len(".yaml")]
        if b == "us.overlay.template":
            continue
        out.add("main" if b == "us.exe" else b)
    return out


def changed_paths():
    r = subprocess.run(["git", "status", "--porcelain"], cwd=REPO,
                       capture_output=True, text=True, check=True)
    paths = []
    for line in r.stdout.splitlines():
        if not line.strip():
            continue
        p = line[3:].strip()
        if " -> " in p:                       # rename
            p = p.split(" -> ", 1)[1]
        paths.append(p.strip('"'))
    return paths


def overlays_mk_binaries():
    """Which binaries' var-blocks changed in config/overlays.mk? A change confined to ONE binary's
    block is binary-local despite living in a shared file."""
    r = subprocess.run(["git", "diff", "-U0", "--", "config/overlays.mk"], cwd=REPO,
                       capture_output=True, text=True)
    hits = set()
    for line in r.stdout.splitlines():
        if line.startswith(("+", "-")) and not line.startswith(("+++", "---")):
            for m in re.finditer(r'\b(ov_[A-Za-z0-9_]+?)_(?:JTBL|O0|WHALE|[A-Z])', line):
                hits.add(m.group(1))
            for m in re.finditer(r'\b(ov_[A-Za-z0-9_]+)\.o\b', line):
                hits.add(m.group(1))
    return hits


def classify(paths, bins):
    """-> (tier, affected_binaries, reasons, unclassified). Tier is the MAX over all paths."""
    tier, affected, reasons, unknown = 0, set(), [], []
    for p in paths:
        if p.startswith("ghidra/"):                       # R23 restart churn — never staged
            continue
        if p.startswith((".run/", "build/", "expected/", "asm/", "assets/", ".venv/")):
            continue                                       # T0: scratch / regenerated
        if p.startswith(("docs/", "phase-ends/", "README", ".gitignore", ".claude/")):
            continue                                       # no build impact
        if p.startswith("src/shared/"):
            tier = max(tier, 2); reasons.append(f"T2 shared source: {p}"); continue
        if p.startswith("src/"):
            parts = p.split("/")
            if len(parts) >= 3 and parts[1] in bins:
                tier = max(tier, 1); affected.add(parts[1])
                reasons.append(f"T1 binary-local: {p}"); continue
            unknown.append(p); continue
        if p.startswith("config/"):
            base = os.path.basename(p)
            m = re.fullmatch(r'(?:splat|check|symbols)\.(.+?)\.(?:yaml|sha|txt)', base)
            if m:
                b = "main" if m.group(1) == "us.exe" else m.group(1)
                if b in bins:
                    tier = max(tier, 1); affected.add(b)
                    reasons.append(f"T1 binary config: {p}"); continue
            if base == "overlays.mk":
                hit = overlays_mk_binaries() & bins
                if hit:
                    tier = max(tier, 1); affected |= hit
                    reasons.append(f"T1 overlays.mk (blocks: {','.join(sorted(hit))})"); continue
                tier = max(tier, 2); reasons.append(f"T2 overlays.mk (blocks unattributable): {p}"); continue
            tier = max(tier, 2); reasons.append(f"T2 fleet config: {p}"); continue
        if p.startswith(("tools/", "Makefile", "diff_settings.py", "requirements")):
            tier = max(tier, 2); reasons.append(f"T2 toolchain: {p}"); continue
        unknown.append(p)
    return tier, affected, reasons, unknown


GATE = {
    0: "none — nothing in the build tree changed",
    1: "PER-BINARY: make extract BINARY=<b> && make build BINARY=<b>   (for each affected binary)",
    2: "R22 CLEAN-FLEET MANDATORY: make clean && make extract-all && make check-all",
}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--expect", choices=["t0", "t1", "t2"],
                    help="assert the measured tier does not EXCEED this; non-zero exit if it does")
    ap.add_argument("--binary", help="with --expect t1: assert the write set touches only this binary")
    ap.add_argument("--json", action="store_true")
    a = ap.parse_args()

    bins = binaries()
    paths = changed_paths()
    tier, affected, reasons, unknown = classify(paths, bins)

    if unknown:                                   # R32: an unclassified path is a DEFECT
        print("blast_radius: UNCLASSIFIED PATHS (refusing to guess a tier):", file=sys.stderr)
        for p in unknown:
            print(f"  {p}", file=sys.stderr)
        print("Add a rule for these before trusting any tier.", file=sys.stderr)
        return 2

    if a.json:
        print(json.dumps({"tier": tier, "affected": sorted(affected),
                          "gate": GATE[tier], "reasons": reasons}))
    else:
        print(f"blast_radius: TIER {tier}  ({len(bins)} binaries known)")
        for r in reasons[:12]:
            print(f"  {r}")
        if len(reasons) > 12:
            print(f"  … and {len(reasons)-12} more")
        if affected:
            print(f"  affected binaries: {', '.join(sorted(affected))}")
        print(f"  REQUIRED GATE -> {GATE[tier]}")

    if a.expect:
        want = int(a.expect[1])
        if tier > want:
            print(f"\nBLAST-RADIUS EXCEEDED: measured T{tier}, expected T{want}.\n"
                  f"  The write set is LARGER than the claim. This is the §85/ARITY failure shape:\n"
                  f"  a change believed contained that reaches further. Run: {GATE[tier]}",
                  file=sys.stderr)
            return 1
        if want == 1 and a.binary and affected - {a.binary}:
            print(f"\nBLAST-RADIUS EXCEEDED: expected only {a.binary}, also touched "
                  f"{', '.join(sorted(affected - {a.binary}))}", file=sys.stderr)
            return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
