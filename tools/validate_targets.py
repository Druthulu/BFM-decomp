#!/usr/bin/env python3
"""validate_targets.py — the VALIDITY GATE every wave target list must pass before agents are spawned.

WHY THIS EXISTS (S46, measured): a 47-target wave burned 9.7M tokens and ~29 of the targets were not
real. The list had been derived by joining sig data against `corpus.stubs` with no check that each
address was an actual function boundary with an actual `.s` on disk. The four defect classes, all
diagnosed by the agents themselves after the money was spent:

  1. NO-ASM      the .s simply does not exist anywhere for that (function, binary)
  2. MID-BODY    the address lands INSIDE another function's span (e.g. func_80190B70 was instruction
                 ~545 of func_801902EC's 673-instruction carve, on a load-delay nop)
  3. OUT-OF-RANGE  the address is outside the binary's vram window entirely
  4. ALREADY-DONE  the function is already matched/banked (a Phase-26 family template member)

`wave_snapshot` already refuses a list whose .s files are missing (its R32 coverage assertion) — that
warning fired on this very list, reporting 24 of 57 found, and was routed around instead of heeded.
This tool makes the check explicit, names the class, and exits non-zero, so the next wave cannot be
scoped on phantoms.

WHEN IT IS MEANINGFUL — PRE-DRAFT ONLY (S56).
    Every verdict is read off LIVE state: `DP.load_sig(binary)`, `corpus.stubs(binary)` and the .s on
    disk. Banking removes a stub and prunes its .s, so running this AFTER a wave gates reports
    ALREADY-DONE for precisely the targets that SUCCEEDED. That is not a defect and must not be
    "fixed" by loosening the class — it means the gate belongs where cards are BORN
    (build_wave_atlas), never downstream of drafting. A refusal-check run at the wrong moment
    discards good work silently, which is the R39 failure mode. Do not run it during a gate either:
    corpus misreports substituted drafts while gate_stage holds the tree.

USAGE
    tools/validate_targets.py --targets .run/wave/args.json            # exit 1 if ANY invalid
    tools/validate_targets.py --targets args.json --out clean.json     # write the surviving subset
    tools/validate_targets.py --targets args.json --allow-invalid      # report only, exit 0

The target file is a JSON list of dicts carrying at least a function name and its binary; both the
`{name, source}` and the compact `{n, s}` spellings are accepted.
"""
import argparse
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import corpus
import dedup_propagate as DP

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def _key(t, *names):
    for n in names:
        if n in t:
            return t[n]
    return None


def validate(targets, sig_cache=None, stub_cache=None):
    """[(target, verdict, detail)] — verdict 'OK' or one of the four defect classes."""
    sig_cache = {} if sig_cache is None else sig_cache
    stub_cache = {} if stub_cache is None else stub_cache
    out = []
    for t in targets:
        # `fn` is the CARD spelling (build_wave_atlas), `name`/`n` the older wave-args spellings.
        # Widening only: a dict carrying `fn` previously fell through to MALFORMED.
        name = _key(t, "name", "n", "fn")
        binary = _key(t, "source", "s", "binary")
        if not name or not binary:
            out.append((t, "MALFORMED", "missing name/source"))
            continue
        try:
            addr = int(name[5:], 16)
        except (ValueError, IndexError):
            out.append((t, "MALFORMED", f"cannot parse an address out of {name!r}"))
            continue
        sig = sig_cache.setdefault(binary, DP.load_sig(binary))
        if not sig:
            out.append((t, "OUT-OF-RANGE", f"{binary} has no sig at all"))
            continue
        if addr not in sig:
            # Not a function START in this binary. Distinguish "inside another function" from
            # "outside the binary" — they need different fixes and conflating them hides both.
            lo, hi = min(sig), max(sig)
            if lo <= addr <= hi:
                prev = max((a for a in sig if a < addr), default=None)
                span = sig.get(prev, {}).get("nins", 0) * 4 if prev else 0
                inside = prev is not None and addr < prev + span
                out.append((t, "MID-BODY" if inside else "NO-BOUNDARY",
                            f"0x{addr:08X} is not a function start"
                            + (f"; inside func_{prev:08X} (+{addr - prev} bytes of {span})" if inside else "")))
            else:
                out.append((t, "OUT-OF-RANGE",
                            f"0x{addr:08X} outside {binary} [0x{lo:08X}..0x{hi:08X}]"))
            continue
        stubs = stub_cache.setdefault(binary, corpus.stubs(binary))
        if addr not in stubs:
            out.append((t, "ALREADY-DONE", f"{name} is not a live stub in {binary} (already matched)"))
            continue
        try:
            p = corpus.asm_path(binary, name)
        except Exception as e:                      # noqa: BLE001 - report, never crash the gate
            p = None
        if not p or not os.path.exists(p):
            out.append((t, "NO-ASM", f"no .s on disk for {name} in {binary}"))
            continue
        out.append((t, "OK", p))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--targets", required=True)
    ap.add_argument("--out", help="write the surviving (OK) subset here")
    ap.add_argument("--allow-invalid", action="store_true",
                    help="report and exit 0 instead of failing (use only when triaging)")
    a = ap.parse_args()
    targets = json.load(open(a.targets))
    if isinstance(targets, dict):
        targets = targets.get("targets", [])
    rows = validate(targets)
    counts = {}
    for _t, v, _d in rows:
        counts[v] = counts.get(v, 0) + 1
    ok = [t for t, v, _d in rows if v == "OK"]
    print(f"{len(targets)} targets -> " + ", ".join(f"{k}={v}" for k, v in sorted(counts.items())))
    bad = [(t, v, d) for t, v, d in rows if v != "OK"]
    for t, v, d in bad[:20]:
        print(f"  [{v}] {_key(t, 'name', 'n', 'fn')} ({_key(t, 'source', 's', 'binary')}): {d}")
    if len(bad) > 20:
        print(f"  … and {len(bad) - 20} more")
    if a.out:
        json.dump(ok, open(a.out, "w"), indent=0)
        print(f"-> {a.out} ({len(ok)} valid targets)")
    if bad and not a.allow_invalid:
        print(f"\n*** {len(bad)} INVALID TARGET(S). A wave scoped on these burns agents proving they "
              f"do not exist — in S46 that cost ~29 phantom targets x 3 tiers = 87 wasted agents. "
              f"Fix the list (or pass --allow-invalid deliberately). ***")
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
