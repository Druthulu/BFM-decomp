#!/usr/bin/env python3
"""Phase-24 W9: roll out the -O0 whale (func_80144B9C) to single-file overlays for the ×134 bank.

The whale is byte-identical in all 134 overlays (reach-134) but only matches at -O0 (gcc-2.7.2 has
no per-function optimize pragma), so each overlay must compile it in its own -O0 TU. Per overlay
(<ov>.c is splat-emitted in vram order, so a line-split at the whale is safe):
  - carve the code subseg into before / o0b(-O0 whale) / after in config/splat.<ov>.yaml
  - <ov>.c  = before-whale (keeps name + nonmatchings/<ov> asm paths)
  - <ov>_o0b.c = a thin wrapper: #include common.h + the shared src/shared/func_80144B9C.h
  - <ov>_after.c = header (includes) + after-whale, asm paths -> nonmatchings/<ov>_after
The Makefile WHALE_O0B_OBJS wildcard rule -O0-compiles every <ov>_o0b.o. Idempotent (skips carved
overlays). The whole-binary byte-gate (make check-all) is the sole arbiter. Usage:
  rollout_whale_o0.py <ov> [<ov> ...]      or      rollout_whale_o0.py --all
"""
import sys, re, os, glob

WHALE = "func_80144B9C"
WHALE_FOFF = 0x1CA44     # vram 0x80144B9C - base 0x80128158
AFTER_FOFF = 0x1D64C     # vram 0x801457A4 (next fn) - base 0x80128158


def header_end(lines):
    """Header = the leading #include block (+ trailing blanks). Single-file overlays have no
    file-scope shared externs (each fn declares its own), so this captures common.h + engine_core.h."""
    last_inc = -1
    for i, l in enumerate(lines):
        s = l.strip()
        if s.startswith("#include"):
            last_inc = i
        elif s and last_inc >= 0:
            break
    he = last_inc + 1
    while he < len(lines) and lines[he].strip() == "":
        he += 1
    return he


def split_overlay(ov):
    cdir = f"src/{ov}"
    main_c, o0b_c, after_c = f"{cdir}/{ov}.c", f"{cdir}/{ov}_o0b.c", f"{cdir}/{ov}_after.c"
    yaml = f"config/splat.{ov}.yaml"
    if os.path.exists(o0b_c):
        return f"SKIP {ov} (o0b exists)"
    if not (os.path.exists(main_c) and os.path.exists(yaml)):
        return f"SKIP {ov} (missing .c or yaml)"
    lines = open(main_c).read().split("\n")
    wi = [i for i, l in enumerate(lines) if WHALE in l and "INCLUDE_ASM" in l]
    if len(wi) != 1:
        return f"SKIP {ov} (whale INCLUDE_ASM count={len(wi)} — not a single-file stub)"
    wi = wi[0]
    he = header_end(lines)
    header = "\n".join(lines[:he]).rstrip("\n")
    before, after = lines[:wi], lines[wi + 1:]
    OLD = f'nonmatchings/{ov}"'
    open(main_c, "w").write("\n".join(before).rstrip("\n") + "\n")
    open(o0b_c, "w").write('#include "common.h"\n#include "../shared/func_80144B9C.h"\n')
    after_body = "\n".join(after).replace(OLD, f'nonmatchings/{ov}_after"')
    open(after_c, "w").write(header + "\n\n" + after_body.rstrip("\n") + "\n")
    # carve the yaml code subseg
    y = open(yaml).read()
    pat = re.compile(r'^(\s*)- \[0x0, c, ' + re.escape(ov) + r'\].*$', re.M)
    m = pat.search(y)
    if not m:
        return f"ERROR {ov}: '- [0x0, c, {ov}]' not found in yaml"
    ind = m.group(1)
    repl = (f'{ind}- [0x0, c, {ov}]  # -O2 before whale (file 0x0..0x{WHALE_FOFF:X})\n'
            f'{ind}- [0x{WHALE_FOFF:X}, c, {ov}_o0b]  # -O0 whale func_80144B9C (0x{WHALE_FOFF:X}..0x{AFTER_FOFF:X})\n'
            f'{ind}- [0x{AFTER_FOFF:X}, c, {ov}_after]  # -O2 after whale (0x{AFTER_FOFF:X}..data tail)')
    open(yaml, "w").write(pat.sub(lambda _m: repl, y, count=1))
    return f"OK {ov}: before {len(before)} / after {len(after)} lines"


def all_overlays():
    ovs = []
    for p in sorted(glob.glob("config/splat.ov_*.yaml")):
        ov = os.path.basename(p)[len("splat."):-len(".yaml")]
        if ov != "ov_SC01_077":          # already carved (the harvest source, different structure)
            ovs.append(ov)
    return ovs


if __name__ == "__main__":
    args = sys.argv[1:]
    targets = all_overlays() if args == ["--all"] else args
    n_ok = 0
    for ov in targets:
        r = split_overlay(ov)
        if r.startswith("OK"):
            n_ok += 1
        print(r)
    print(f"--- {n_ok}/{len(targets)} carved ---")
