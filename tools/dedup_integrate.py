#!/usr/bin/env python3
"""Cross-binary code-share registry validator (Phase 11, G7 "match once, share").

Validates config/dedup.us.yaml — the registry of functions matched ONCE and shared across
>=2 duplicate sites/binaries via a source-level body (see config/dedup.us.yaml for the why).

The share itself is SOURCE-LEVEL: the matched body lives once in `source` (a macro header)
and is instantiated at each member site in that binary's game-code .c, so the same bytes land
at each member vram. The REAL byte-gate is the existing per-binary `make check BINARY=<bin>`
(the image is byte-identical or it is not) — this tool adds the BYTE-HONESTY check that makes a
share's claim trustworthy: every member's CURRENT signature hash must still equal the recorded
`hash`. If a shared function drifts (someone edits it and one site diverges), --check FAILS so
the stale share can never silently mislead (P9/G3). h_exact = guaranteed byte-match; h_norm =
candidate, accepted only when every claiming binary still builds byte-identical.

This is NOT a fork of psyq_integrate's object-swap: that works only for separate library
SUBSEGMENT stubs; game-code functions are interior to one object per binary, so the linker
cannot swap them — sharing is source-level. The .ld interpose stays the library mechanism.

Usage: tools/dedup_integrate.py [--check] [--binary <alias>] [--dedup config/dedup.us.yaml]
       (--apply is reserved for future per-site boilerplate generation; shares are source-level,
        so there is no build-time action — --apply currently just validates.)
"""
import argparse, json, pathlib, sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
from dup_report import BINARIES  # single source of truth for per-binary .run/sig.<bin>.jsonl paths

TIERS = ("h_exact", "h_norm")


def _addr(v):
    """Accept a YAML int (0x.. parsed) or a hex string ('0x..' / bare hex) -> int."""
    return v if isinstance(v, int) else int(str(v), 16)


def _load_sig_index(rel):
    """addr(int) -> sig row for .run/sig.<bin>.jsonl, or None if the file is absent."""
    p = ROOT / rel
    if not p.exists():
        return None
    idx = {}
    for line in p.read_text().splitlines():
        line = line.strip()
        if line:
            r = json.loads(line)
            idx[int(r["addr"], 16)] = r
    return idx


def check(groups, binary_filter=None):
    """Validate every group's byte-honesty. Returns the failure count (0 = all honest).
    A member whose binary has no signature file yet (e.g. an overlay before sig_image runs) is
    UNVALIDATED (warn), never a hard failure; a present-but-mismatched hash is a hard FAIL."""
    sigcache = {}

    def sig_for(binary):
        if binary not in sigcache:
            cfg = BINARIES.get(binary)
            sigcache[binary] = _load_sig_index(cfg["sig"]) if cfg else None
        return sigcache[binary]

    failures = warnings = validated = 0
    for g in groups:
        gid = g.get("id", "?")
        members = g.get("members") or []
        if binary_filter and not any(m.get("binary") == binary_filter for m in members):
            continue
        if g.get("tier") not in TIERS:
            print(f"[FAIL] {gid}: tier must be one of {TIERS} (got {g.get('tier')!r})"); failures += 1; continue
        if len(members) < 2:
            print(f"[FAIL] {gid}: a share needs >=2 members (got {len(members)})"); failures += 1; continue
        src = g.get("source")
        if not src or not (ROOT / src).exists():
            print(f"[FAIL] {gid}: shared source {src!r} missing"); failures += 1; continue
        tier, want = g["tier"], g.get("hash")
        if not want:
            print(f"[FAIL] {gid}: no recorded hash"); failures += 1; continue
        ok = True
        for m in members:
            b, name = m.get("binary"), m.get("name", "?")
            try:
                vram = _addr(m["vram"])
            except (KeyError, ValueError):
                print(f"[FAIL] {gid}: bad/absent vram for {name} in {b}"); failures += 1; ok = False; continue
            idx = sig_for(b)
            if idx is None:
                print(f"[WARN] {gid}: {b} has no sig yet — cannot validate {name} @ {m.get('vram')}")
                warnings += 1; ok = False; continue
            row = idx.get(vram)
            if row is None:
                print(f"[FAIL] {gid}: {b}:{m.get('vram')} ({name}) not found in {b} signature"); failures += 1; ok = False; continue
            got = row.get(tier)
            if got != want:
                print(f"[FAIL] {gid}: {b}:{m.get('vram')} ({name}) {tier}={got} != recorded {want} — SHARE DRIFTED")
                failures += 1; ok = False
        if ok:
            validated += 1
            bins = ",".join(sorted({m["binary"] for m in members}))
            print(f"[ OK ] {gid}: {len(members)} members [{bins}] share {tier} {want[:12]}… (source {src})")
    print(f"dedup-check: {validated} validated, {warnings} unvalidated (sig absent), {failures} failed")
    return failures


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--dedup", default="config/dedup.us.yaml")
    ap.add_argument("--binary", default=None, help="validate only groups with a member in this binary")
    ap.add_argument("--check", action="store_true", help="validate byte-honesty (default mode)")
    ap.add_argument("--apply", action="store_true", help="reserved (shares are source-level; validates only)")
    a = ap.parse_args()

    path = ROOT / a.dedup
    if not path.exists():
        print(f"dedup-check: {a.dedup} absent — no shares registered (build uses INCLUDE_ASM stubs).")
        return
    import yaml  # PyYAML (venv; splat dependency)
    data = yaml.safe_load(path.read_text()) or {}
    groups = data.get("groups") or []
    if a.apply:
        print("dedup_integrate --apply: shares are SOURCE-LEVEL (authored in src/shared/, instantiated "
              "per site); no build-time action — validating byte-honesty instead.")
    if check(groups, a.binary):
        sys.exit(1)


if __name__ == "__main__":
    main()
