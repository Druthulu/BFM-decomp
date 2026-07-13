#!/usr/bin/env python3
"""Isolate a jr-function into its own code subseg (Phase-26 §8 multi-jtbl, the non-contiguous case).

Two matched jr-functions in ONE code object emit their jtbls CONTIGUOUS in that object's .rodata
(gcc source order). That is byte-correct only if their jtbls are adjacent in the overlay's .rodata
island. When an UNMATCHED jtbl sits between them, the object can't reproduce the island layout ->
jtbl_carve refuses (non-contiguous same-subseg). This tool splits the containing code subseg so the
target function becomes its own object (the whale `_o0b` precedent), preserving every other matched C
body (H5, via split_src_region.py trim/inject), after which its jtbl carves independently.

    [s_off, c, SUB]   ->   [s_off,   c, SUB]              (functions < func)
                           [f_off,   c, <ov>_jr_<addr>]   (func alone -> its own object)
                           [f_end,   c, <ov>_after_<addr>](functions >= func's end)

The carve subseg names are re-derived by jtbl_carve from each function's ADDRESS against the current
code subsegs, so after this split jtbl_carve automatically points every carve at its new object -- this
tool only restructures code subsegs; it never edits a `.rodata` carve. Idempotent (no-op if already
isolated). Self-contained: does the config split, the source trim/inject, and the re-extract.

    jr_isolate.py <ov> --func func_XXXX

STATUS (Phase-26 session 4): the config split + `func_subseg`-derived carve are ready, but this is BLOCKED on
`split_src_region.py`, which cannot partition the overlay `.c` — those files carry non-address top-level items
(the Phase-17 global canonical-sig extern layer + per-function callee-extern blocks + `DEFINE_func_X()` dedup
macros + `// @class` annotations) that its "one item = one address" model chokes on (~922 unresolved in
ov_SC01_077_after.c). Finishing this needs an overlay-`.c`-aware source split (header = includes + the global
extern layer; attach leading extern-decl blocks to the following function-block). See cookbook §8b. Stage-2 item.
"""
import argparse
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import jtbl_carve  # cfg_path, func_subseg, overlay_vram_base, PIECE_RE

REPO = jtbl_carve.REPO


def func_end_vram(ov, func):
    """func's end vram = its last .text instruction's vram + 4 (from the nonmatchings .s)."""
    sub = jtbl_carve.func_subseg(ov, func)
    s = open(os.path.join(REPO, "asm", ov, "nonmatchings", sub, f"{func}.s")).read()
    # instruction lines: /* <fileoff> <VRAM> <bytes> */  <mnemonic>
    addrs = [int(m, 16) for m in re.findall(
        r"/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}\s*\*/\s*\S", s)]
    if not addrs:
        sys.exit(f"jr_isolate: no instruction addresses in {func}.s")
    return max(addrs) + 4


def sh(cmd, **kw):
    return subprocess.run(cmd, cwd=REPO, **kw)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("ov")
    ap.add_argument("--func", required=True, help="func_XXXXXXXX to isolate into its own code subseg")
    a = ap.parse_args()
    ov, func = a.ov, a.func
    m = re.fullmatch(r"func_([0-9A-Fa-f]{8})", func)
    if not m:
        sys.exit("jr_isolate: --func must be func_XXXXXXXX")
    faddr_hex = m.group(1)
    base = jtbl_carve.overlay_vram_base(ov)
    cfg = jtbl_carve.cfg_path(ov)
    txt = open(cfg).read()

    jr_name = f"{ov}_jr_{faddr_hex}"
    after_name = f"{ov}_after_{faddr_hex}"
    if f", c, {jr_name}]" in txt:
        print(f"jr_isolate {ov}: {func} already isolated ({jr_name})")
        return

    sub = jtbl_carve.func_subseg(ov, func)         # current containing code subseg
    f_vram = int(faddr_hex, 16)
    f_end = func_end_vram(ov, func)
    f_off, f_end_off = f_vram - base, f_end - base

    # find the [s_off, c, SUB] config line for the containing subseg
    line_re = re.compile(rf"^([ \t]*)- \[(0x[0-9A-Fa-f]+),\s*c,\s*{re.escape(sub)}\]\s*(?:#.*)?$", re.M)
    mm = line_re.search(txt)
    if not mm:
        sys.exit(f"jr_isolate: no `[..., c, {sub}]` line in {cfg}")
    indent, s_off = mm.group(1), int(mm.group(2), 16)
    if not (s_off <= f_off < f_end_off):
        sys.exit(f"jr_isolate: {func} (0x{f_off:x}..0x{f_end_off:x}) not inside subseg {sub} (@0x{s_off:x})")

    block = "\n".join([
        f"{indent}- [{hex(s_off)}, c, {sub}]",
        f"{indent}- [{hex(f_off)}, c, {jr_name}]        # Phase-26 §8 jr isolation (jr_isolate.py)",
        f"{indent}- [{hex(f_end_off)}, c, {after_name}]",
    ])
    txt = line_re.sub(lambda _: block, txt, count=1)
    open(cfg, "w").write(txt)

    # source: keep functions < f_vram in SUB.c, move real-C >= f_end to a frag for the after file
    sub_c = f"src/{ov}/{sub}.c"
    frag = f".run/isolate_{ov}_{func}.frag"
    syms = f"config/symbols.{ov}.txt"
    sh([sys.executable, "tools/split_src_region.py", "--symbols", syms,
        "trim", sub_c, hex(f_vram), hex(f_end), frag], check=True)
    # regenerate: splat emits jr_name.c (func's stub) + after_name.c (stubs for >= f_end)
    if sh(["make", "--no-print-directory", "extract", f"BINARY={ov}"]).returncode:
        sys.exit(f"jr_isolate: extract failed for {ov}")
    # restore the moved matched C into the freshly-generated after file
    sh([sys.executable, "tools/split_src_region.py", "--symbols", syms,
        "inject", f"src/{ov}/{after_name}.c", frag], check=True)
    print(f"jr_isolate {ov}: {func} -> {jr_name}; remainder >= 0x{f_end:x} -> {after_name}")


if __name__ == "__main__":
    main()
