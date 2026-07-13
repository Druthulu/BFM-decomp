#!/usr/bin/env python3
"""Phase-26 §8 (overlay ×134): set up the jtbl-rodata carve for an overlay's matched jr-functions.

An overlay's gcc switch jump tables sit in one contiguous `.rodata` island at the TAIL of the flat
blob. Matching a jr-function makes its C emit that jtbl into `.rodata` (floated to the FRONT by
section_order) while the raw copy stays in the data tail -> duplicate + wrong address. This tool
carves each named jr-function's jtbl(s) out of the `[…, data, tail]` subseg into a dotted
`[.rodata, <code-subseg>]` subseg (spimdisasm migrates it into the fn's `.s`), splitting the data tail
into pre/post `data` subsegs, and sets the `<ov>_JTBL_INTERLEAVE` var in config/overlays.mk so
`make extract` runs `ld_interleave --section .<ov>` (the data->rodata->data sandwich; cookbook §8a).

Per-sibling: the SAME function is at the same vram across overlays but its jtbl is at a DIFFERENT
address in each (the island floats with the overlay's size), so the carve is recomputed per overlay.

SINGLE-jtbl scope (this slice): one jr-function -> one jtbl -> a 3-region data->rodata->data carve
(--front tail / --tail tail2). Multiple matched jr-functions per overlay (scattered jtbls) need the
address-ordered `ld_interleave --order` mode -> raised as NotImplementedError (the next slice).

Usage:  jtbl_carve.py <ov> --func func_XXXX [--func ...]   # apply the carve for these matched jr-fns
        jtbl_carve.py <ov> --revert                        # restore the config from git (drop carves)
Idempotent: re-running with the same funcs reproduces the same config.
"""
import argparse
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def cfg_path(ov):
    return os.path.join(REPO, f"config/splat.{ov}.yaml")


def overlay_vram_base(ov):
    """The overlay's load vram (all location overlays share the 0x80128158 slot, but read it)."""
    txt = open(cfg_path(ov)).read()
    m = re.search(r"vram:\s*(0x[0-9A-Fa-f]+)", txt)
    if not m:
        sys.exit(f"jtbl_carve: no vram in {cfg_path(ov)}")
    return int(m.group(1), 16)


def func_subseg(ov, func):
    """The code subseg name that owns `func` (= the dir under asm/<ov>/nonmatchings/)."""
    base = os.path.join(REPO, "asm", ov, "nonmatchings")
    for sub in os.listdir(base):
        if os.path.exists(os.path.join(base, sub, f"{func}.s")):
            return sub
    sys.exit(f"jtbl_carve: {func}.s not found under asm/{ov}/nonmatchings/ (extract first)")


def func_jtbls(ov, func):
    """The jtbl label(s) `func` references (from its .s %hi(jtbl_...))."""
    sub = func_subseg(ov, func)
    s = open(os.path.join(REPO, "asm", ov, "nonmatchings", sub, f"{func}.s")).read()
    return sub, sorted(set(re.findall(r"jtbl_([0-9A-Fa-f]{8})", s)))


def jtbl_range(ov, jtbl_hex):
    """(start_vram, end_vram) of jtbl_<hex> from the data-tail asm (dlabel .. next label)."""
    tail = os.path.join(REPO, "asm", ov, "data", "tail.data.s")
    lines = open(tail).read().splitlines()
    start = int(jtbl_hex, 16)
    # find the dlabel, then the next (glabel|dlabel) at a higher address = end.
    labels = []
    for ln in lines:
        m = re.match(r"\s*(?:dlabel|glabel)\s+(?:jtbl_|D_)([0-9A-Fa-f]{8})", ln)
        if m:
            labels.append(int(m.group(1), 16))
    labels = sorted(set(labels))
    if start not in labels:
        sys.exit(f"jtbl_carve: jtbl_{jtbl_hex} not found in asm/{ov}/data/tail.data.s (carved already? --revert first)")
    nxt = next((a for a in labels if a > start), None)
    if nxt is None:
        sys.exit(f"jtbl_carve: jtbl_{jtbl_hex} is the last label — cannot bound its size")
    return start, nxt


def has_trailing(ov):
    return bool(re.search(r"\[0x[0-9A-Fa-f]+,\s*bin,\s*trailing\]", open(cfg_path(ov)).read()))


def build_carve(ov, funcs):
    """Return (subsegs, interleave_args) for the given matched jr-functions.
    subsegs: list of (file_off, kind, name) replacing the single [tail] data subseg.
    Single-jtbl only in this slice."""
    base = overlay_vram_base(ov)
    jtbls = []   # (start_vram, end_vram, subseg_name)
    for f in funcs:
        sub, js = func_jtbls(ov, f)
        for jh in js:
            s, e = jtbl_range(ov, jh)
            jtbls.append((s, e, sub))
    jtbls.sort()
    if len(jtbls) != 1:
        raise NotImplementedError(
            f"jtbl_carve: {len(jtbls)} jtbls for {ov} — the multi-jtbl address-ordered carve "
            f"(ld_interleave --order) is the next slice; single-jtbl only for now.")
    s, e, sub = jtbls[0]
    tail_start = current_tail_start(ov)
    j_off, j_end = s - base, e - base
    subsegs = [
        (tail_start, "data", "tail"),
        (j_off, ".rodata", sub),
        (j_end, "data", "tail2"),
    ]
    args = "--front tail.data.o --tail tail2.data.o" + (" --tail trailing.o" if has_trailing(ov) else "")
    return subsegs, args


def current_tail_start(ov):
    """The file offset of the overlay's data-tail `data` subseg (before any carve)."""
    txt = open(cfg_path(ov)).read()
    m = re.search(r"\[(0x[0-9A-Fa-f]+),\s*data,\s*tail\]", txt)
    if not m:
        sys.exit(f"jtbl_carve: no `[…, data, tail]` subseg in {cfg_path(ov)}")
    return int(m.group(1), 16)


def apply(ov, funcs):
    subsegs, args = build_carve(ov, funcs)
    txt = open(cfg_path(ov)).read()
    # Replace the single `[<off>, data, tail]` line with the carve block (preserve indent).
    line_re = re.compile(r"^(\s*)- \[0x[0-9A-Fa-f]+,\s*data,\s*tail\].*$", re.M)
    m = line_re.search(txt)
    if not m:
        sys.exit(f"jtbl_carve: could not find the data-tail subseg line in {cfg_path(ov)}")
    indent = m.group(1)
    block = "\n".join(
        f"{indent}- [{hex(off)}, {kind}, {name}]" + (
            "  # Phase-26 §8 jtbl-rodata carve (jtbl_carve.py)" if kind == ".rodata" else "")
        for off, kind, name in subsegs)
    txt = line_re.sub(lambda _: block, txt, count=1)
    open(cfg_path(ov), "w").write(txt)
    set_overlays_var(ov, args)
    print(f"jtbl_carve {ov}: carved {funcs} -> {[hex(o) for o, _, _ in subsegs]}; JTBL_INTERLEAVE = {args}")


def set_overlays_var(ov, args):
    mk = os.path.join(REPO, "config/overlays.mk")
    txt = open(mk).read()
    var = f"{ov}_JTBL_INTERLEAVE := {args}  # Phase-26 §8 jtbl-rodata carve"
    if re.search(rf"^{re.escape(ov)}_JTBL_INTERLEAVE\b", txt, re.M):
        txt = re.sub(rf"^{re.escape(ov)}_JTBL_INTERLEAVE.*$", var, txt, count=1, flags=re.M)
    else:
        # insert right after the overlay's SPLAT_YAML line
        anchor = f"{ov}_SPLAT_YAML := config/splat.{ov}.yaml"
        if anchor not in txt:
            sys.exit(f"jtbl_carve: no {anchor} anchor in overlays.mk")
        txt = txt.replace(anchor, anchor + "\n" + var, 1)
    open(mk, "w").write(txt)


def revert(ov):
    subprocess.check_call(["git", "-C", REPO, "checkout", "--", cfg_path(ov)])
    mk = os.path.join(REPO, "config/overlays.mk")
    txt = open(mk).read()
    txt = re.sub(rf"^{re.escape(ov)}_JTBL_INTERLEAVE.*\n", "", txt, flags=re.M)
    open(mk, "w").write(txt)
    print(f"jtbl_carve {ov}: reverted config + dropped JTBL_INTERLEAVE")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("ov")
    ap.add_argument("--func", action="append", default=[], help="matched jr-function to carve (repeatable)")
    ap.add_argument("--revert", action="store_true", help="restore config from git + drop the var")
    a = ap.parse_args()
    if a.revert:
        revert(a.ov)
    elif a.func:
        apply(a.ov, a.func)
    else:
        ap.error("give --func <fn> (repeatable) or --revert")


if __name__ == "__main__":
    main()
