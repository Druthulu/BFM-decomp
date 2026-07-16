#!/usr/bin/env python3
"""Phase-28 T4: EXTEND the existing dedup registry to newly-onboarded binaries.

THE GAP THIS FILLS (byte-measured, P28 T3-A). `tools/new_overlay.sh` produces a byte-clean binary
that is NOT a citizen of the shared-body ecosystem: its `.c` includes only `common.h` (never
`../shared/engine_core.h`), so not one shared engine body can reach it, and it appears in ZERO of
`config/dedup.us.yaml`'s groups. The 4 SC07 overlays the Phase-27 disc audit onboarded therefore sat
at ~80 matched / ~2,400 stubs while their siblings were ~2,150 matched — and 1,689 registry groups
still read "134 binaries", never 138.

WHY THE EXISTING TOOL CANNOT DO IT. `dedup_propagate` is built for CRACK -> AUTHOR MACRO ->
INSTANTIATE: `--auto-from` scans a source overlay's INLINE DEFS (it planned only 11 fns here,
skipping the ~1,600 whose bodies are ALREADY `DEFINE_func_*` macros in engine_core.h), and `--addr`
dies with "no source overlay has it matched" because no overlay holds an inline def — every one of
the 134 uses the macro. Extending an existing MACRO-BACKED group to a new binary is a different
operation, and nothing implemented it.

WHY IT IS SAFE (the correctness argument — this is a byte-gate feeder, so it must be explicit).
`h_exact` is the SHA1 of RAW INSTRUCTION BYTES (tools/sig_image.py). Two instances sharing an
h_exact are therefore identical *including* their `jal`/`lui`/`%lo` reloc immediates — same callee
addresses, same data addresses, same symbols. So the body that compiles byte-identically at one
member compiles byte-identically at the other, with no remap at all. (This is exactly why
dup_report calls h_exact "guaranteed byte-match" and h_norm "candidate-only".) The whole-binary
byte-gate remains the sole arbiter (G3/P9): a wrong instantiation changes the bytes and fails SHA1.
A bug here can make this tool FAIL TO BANK; it cannot make it falsely bank.

REUSE, DON'T REBUILD (R33). This owns only the SET COMPUTATION and the REGISTRY EDIT. The splice and
the gate are `tools/harvest_verify.py` verbatim — which already derives each stub's home TU from the
corpus oracle, chunks + bisects, and reverts on failure. h_exact members are byte-identical by
construction, so the happy path is ONE build per binary (not one per function).

  tools/dedup_extend.py --binaries ov_SC07_006,ov_SC07_007,ov_SC07_010,ov_SC07_011 [--check-only]
                        [--chunk N] [--limit N]
"""
import argparse
import glob
import json
import os
import re
import subprocess
import sys

import yaml

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import corpus

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = sys.executable
REGISTRY = "config/dedup.us.yaml"
SHARED_INCLUDE = '#include "../shared/engine_core.h"'
EXTEND_DIR = ".run/extend"


def sig_hashes(binary):
    """{vram_int: h_exact} from the binary's sig — the ORIGINAL bytes, independent of splat."""
    out = {}
    p = os.path.join(REPO, f".run/sig.{binary}.jsonl")
    for line in open(p):
        d = json.loads(line)
        out[int(d["addr"], 16)] = d["h_exact"]
    return out


def load_groups():
    doc = yaml.safe_load(open(os.path.join(REPO, REGISTRY)))
    groups = doc if isinstance(doc, list) else doc.get("groups", doc)
    if not isinstance(groups, list):
        sys.exit(f"dedup_extend: unexpected {REGISTRY} shape: {type(groups).__name__}")
    return doc, groups


def _addr(v):
    return int(v, 16) if isinstance(v, str) else int(v)


def plan_for(binary, groups):
    """[(group, vram, macro)] for every h_exact group this binary could join.

    A group is extendable into `binary` iff: it is h_exact tier, the binary is not already a member,
    the binary has a LIVE STUB at the group's vram, and that stub's original bytes hash to the
    group's recorded h_exact (the C1 equivalence the registry itself asserts).
    """
    sig = sig_hashes(binary)
    stubs = corpus.stubs(binary)
    out = []
    for g in groups:
        if g.get("tier") != "h_exact":
            continue
        if "vram" not in g or "binaries" not in g:
            continue                                   # verbose-form group: not position-locked, skip
        if binary in g["binaries"]:
            continue
        vram = _addr(g["vram"])
        if vram not in stubs:
            continue                                   # not a live stub here (matched already, or absent)
        if sig.get(vram) != g["hash"]:
            continue                                   # DIFFERENT CODE at the same vram — the whole point of the check
        out.append((g, vram, g["func"]))
    return out


def ensure_include(binary, apply=True):
    """Add the shared-header include if absent. Byte-neutral: engine_core.h is only `#define`s, so
    including it without instantiating emits no code (proven: ov_SC07_006 built 7ca772be with the
    include + one macro). Returns True if the file was changed."""
    p = os.path.join(REPO, f"src/{binary}/{binary}.c")
    t = open(p).read()
    if SHARED_INCLUDE in t:
        return False
    if apply:
        t = t.replace('#include "common.h"', '#include "common.h"\n' + SHARED_INCLUDE, 1)
        open(p, "w").write(t)
    return True


def write_drafts(binary, plan):
    d = os.path.join(REPO, EXTEND_DIR, binary)
    subprocess.run(["rm", "-rf", d], check=False)
    os.makedirs(d, exist_ok=True)
    for g, vram, macro in plan:
        fn = f"func_{vram:08X}"
        body = f"{macro}()  /* dedup: shared engine-core @0x{vram:08x} (src/shared) */\n"
        open(os.path.join(d, fn + ".c"), "w").write(body)
    return d


def gate(binary, drafts_dir, chunk):
    """The EXISTING whole-binary byte-gate is the sole arbiter (G3/P9). Returns the banked fn set."""
    good = open(os.path.join(REPO, f"config/check.{binary}.sha")).read().split()[0]
    vout = f".run/extend_verified.{binary}.txt"
    fout = f".run/extend_failed.{binary}.txt"
    cmd = [PY, "tools/harvest_verify.py", "--binary", binary,
           "--out", f"build/{binary}/{binary}", "--good-sha", good,
           "--drafts", os.path.relpath(drafts_dir, REPO), "--chunk", str(chunk),
           "--verified-out", vout, "--failed-out", fout]
    subprocess.run(cmd, cwd=REPO, timeout=7200)
    p = os.path.join(REPO, vout)
    return set(open(p).read().split()) if os.path.exists(p) else set()


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--binaries", required=True, help="comma list of newly-onboarded binaries to wire in")
    ap.add_argument("--chunk", type=int, default=512,
                    help="drafts per build (h_exact is byte-identical by construction, so the happy "
                         "path is ONE build; harvest_verify bisects on failure). default 512")
    ap.add_argument("--limit", type=int, default=0, help="cap #groups per binary (0 = all)")
    ap.add_argument("--check-only", action="store_true", help="print the plan, touch nothing")
    a = ap.parse_args()
    os.chdir(REPO)

    doc, groups = load_groups()
    targets = [b.strip() for b in a.binaries.split(",") if b.strip()]

    dirty = subprocess.run("git status --porcelain -- config/ src/", shell=True,
                           capture_output=True, text=True).stdout.strip()
    if dirty and not a.check_only:
        sys.exit("dedup_extend: config/ or src/ is dirty — commit first so a failed gate reverts "
                 "cleanly.\n" + dirty[:400])

    total_banked, total_planned = 0, 0
    for b in targets:
        plan = plan_for(b, groups)
        if a.limit:
            plan = plan[:a.limit]
        total_planned += len(plan)
        print(f"[{b}] {len(plan)} extendable h_exact group(s); "
              f"include {'ABSENT -> add' if ensure_include(b, apply=False) else 'present'}")
        if a.check_only or not plan:
            continue

        ensure_include(b)
        d = write_drafts(b, plan)
        banked = gate(b, d, a.chunk)
        print(f"[{b}] BANKED {len(banked)} / {len(plan)}")
        total_banked += len(banked)

        if not banked:
            ensure_include_revert(b)
            continue
        for g, vram, _ in plan:                        # registry: only what the GATE accepted (P9)
            if f"func_{vram:08X}" in banked and b not in g["binaries"]:
                g["binaries"].append(b)

    if not a.check_only and total_banked:
        yaml.safe_dump(doc, open(REGISTRY, "w"), sort_keys=False, width=10**6, default_flow_style=None)
        print(f"registry: {REGISTRY} updated")
    print(f"\n=== dedup_extend: banked {total_banked} / {total_planned} planned "
          f"across {len(targets)} binaries ===")
    if a.check_only:
        print("(--check-only: no files touched)")


def ensure_include_revert(binary):
    p = os.path.join(REPO, f"src/{binary}/{binary}.c")
    t = open(p).read().replace('#include "common.h"\n' + SHARED_INCLUDE, '#include "common.h"', 1)
    open(p, "w").write(t)


if __name__ == "__main__":
    main()
