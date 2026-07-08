#!/usr/bin/env python3
"""Phase-25 family template-instantiation: mechanically remap a MATCHED exemplar's C to a byte-variant
h_norm SIBLING by positionally pairing their per-overlay symbol references.

The Phase-24 reframe found the unmatched frontier clusters into h_norm STRUCTURAL families (same code
shape across overlays, byte-shattered because each member references PER-OVERLAY symbols). T3 proved these
are NOT free `--tier h_norm` dedup (one C body can't name 134 overlays' different symbols). But two
h_norm-identical members have IDENTICAL instruction streams except in the masked reloc fields (jal target,
lui/lo address) — so: disassemble both overlay images at ADDR, pair the resolved reloc targets in
instruction order, and substitute the exemplar C's per-overlay symbol NAMES (`D_<addr>`/`func_<addr>`)
with the sibling's. Shared EXE/resident symbols map to themselves. The result is the sibling's C —
generated mechanically from ONE crack, for ~0 agent tokens. The whole-binary byte-gate stays the sole
arbiter (G3/P9): a wrong remap is rejected.

  tools/family_remap.py --addr 0xADDR --from ov_SC01_077 --to ov_SC01_000 [--out draft.c]
"""
import struct, json, glob, re, sys, argparse

VRAM = 0x80128158
# lo-type ops whose rs is a hi-base (loads/stores incl. unaligned, addiu, ori)
LO_OPS = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x28, 0x29, 0x2A, 0x2B, 0x2E, 0x09, 0x0D}


def img_path(ov):
    _, sc, fn = ov.split("_")
    p = f"extracted/retail/{sc}.CD.dir/FILE_{fn}.dir/0.4.dec"
    return p if glob.glob(p) else None


def nins_of(ov, addr):
    for line in open(f".run/sig.{ov}.jsonl"):
        d = json.loads(line)
        if int(d["addr"], 16) == addr:
            return d["nins"]
    return None


def reloc_targets(ov, addr):
    """ordered [(kind, resolved_addr)] for jal targets + lui/lo address loads, in instruction order.
    Verified against splat .s ground truth (22/22 on func_80141100)."""
    data = open(img_path(ov), "rb").read()
    n = nins_of(ov, addr)
    off = addr - VRAM
    out, pend = [], {}
    for k in range(n):
        pc = addr + k * 4
        w = struct.unpack_from("<I", data, off + k * 4)[0]
        op = w >> 26
        if op in (2, 3):                                   # j / jal
            out.append(("call", ((pc + 4) & 0xF0000000) | ((w & 0x03FFFFFF) << 2)))
        elif op == 0x0F:                                   # lui -> rt holds the hi
            pend[(w >> 16) & 0x1F] = (w & 0xFFFF) << 16
        elif op in LO_OPS:
            rs = (w >> 21) & 0x1F
            if rs in pend:
                lo = w & 0xFFFF
                if lo >= 0x8000:
                    lo -= 0x10000
                out.append(("data", pend[rs] + lo))
                del pend[rs]
            pend.pop((w >> 16) & 0x1F, None)               # rt overwritten
        elif op == 0:                                      # R-type: rd overwritten
            pend.pop((w >> 11) & 0x1F, None)
    return out


def symbol_map(addr, from_ov, to_ov):
    """{exemplar_name: sibling_name} for the per-overlay symbols (positional zip). None,err if not clean."""
    ex, tg = reloc_targets(from_ov, addr), reloc_targets(to_ov, addr)
    if len(ex) != len(tg):
        return None, f"reloc-count mismatch {len(ex)}!={len(tg)} (not an h_norm-clean pair)"
    m = {}
    for (ke, ae), (kt, at) in zip(ex, tg):
        if ke != kt:
            return None, "reloc-kind mismatch (not h_norm-clean)"
        if ae != at:
            pfx = "func_" if ke == "call" else "D_"
            m[f"{pfx}{ae:08X}"] = f"{pfx}{at:08X}"
    return m, None


def extract_unit(ov, addr):
    """the matched inline def + its contiguous preceding extern/blank/comment lines, from the overlay src.
    func_<addr> names are UPPERCASE-hex in src (func_8013DBE4); match case-insensitively to be safe."""
    pat = re.compile(rf'^\s*[A-Za-z_][\w \*]*\bfunc_{addr:08X}\s*\(', re.I)
    for cf in sorted(glob.glob(f"src/{ov}/{ov}*.c")):
        lines = open(cf).read().split("\n")
        for i, ln in enumerate(lines):
            if pat.search(ln) and "INCLUDE_ASM" not in ln and not ln.rstrip().endswith(";"):
                j = i - 1
                while j >= 0 and (lines[j].strip() == "" or
                                  lines[j].lstrip().startswith(("extern", "//", "/*", "*"))):
                    j -= 1
                start = j + 1
                depth, started, end = 0, False, i
                for k in range(i, len(lines)):
                    depth += lines[k].count("{") - lines[k].count("}")
                    if "{" in lines[k]:
                        started = True
                    if started and depth <= 0:
                        end = k
                        break
                return "\n".join(lines[start:end + 1]), cf
    return None, None


def remap(addr, from_ov, to_ov):
    """returns (draft_text, symbol_map) or (None, error_str)."""
    m, err = symbol_map(addr, from_ov, to_ov)
    if err:
        return None, err
    unit, cf = extract_unit(from_ov, addr)
    if not unit:
        return None, f"no matched unit for func_{addr:08x} in {from_ov}"
    for src, dst in m.items():
        unit = re.sub(rf'\b{src}\b', dst, unit)
    return unit, m


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--addr", required=True)
    ap.add_argument("--from", dest="frm", required=True)
    ap.add_argument("--to", required=True)
    ap.add_argument("--out", default=None)
    a = ap.parse_args()
    addr = int(a.addr, 16)
    draft, m = remap(addr, a.frm, a.to)
    if draft is None:
        print(f"REMAP FAIL (func_{addr:08x} {a.frm}->{a.to}): {m}")
        sys.exit(1)
    out = a.out or f".run/remap_{a.to}_{addr:08x}.c"
    open(out, "w").write(draft + "\n")
    print(f"remapped {len(m)} per-overlay symbol(s) {a.frm}->{a.to}: {m}")
    print(f"-> {out}")


if __name__ == "__main__":
    main()
