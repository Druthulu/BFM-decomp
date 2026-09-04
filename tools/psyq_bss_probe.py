#!/usr/bin/env python3
"""psyq_bss_probe.py — can this PsyQ object's scattered `.bss` be SPLIT and placed? (P31 S77)

THE WALL THIS INTERROGATES.  `config/splat.us.exe.yaml` has excluded four library objects from the
LINKED build since Phase 8 with one recorded reason:

    SYS.o EXCLUDED — scattered-.bss commons (the GS_001 class: SYS references .bss by section+offset
    but the original linker scattered the commons across 0x80078xxx/0x800c5xxx, so no single NOLOAD
    base reproduces it)

That reason is CORRECT and this tool confirms it — §9.2's "weaken the `.bss` symbol and `--defsym`
it" cannot reach these sites, because a `R_MIPS_HI16/LO16` against the bare `.bss` SECTION has no
name to defsym.  But "no single base" is not the same claim as "unlinkable", and nobody had asked
the next question: **are the offset ranges behind each base DISJOINT?**  If they are, `.bss` splits
into pieces and each piece gets its own NOLOAD base.

MEASURED ON SYS.o (the biggest, 3,109 ins — `src/800c.c` is 100% this object):

    base 0x80078830 : 23 refs, .bss offsets 0x0000..0x0044
    base 0x800c53cc :  9 refs, .bss offsets 0x0148..0x0150     -> DISJOINT, split at 0x148

and only `.text` references `.bss` at all (`.data` has zero such relocs), so the split covers every
reference in the object.  The wall is real and breakable — two different things.

HOW IT DERIVES THE BASE — from the bytes, not from a config.  For each HI16/LO16 pair against
`.bss`, the OBJECT's immediates encode the addend and the GAME's immediates encode the resolved
address; `base = resolved − addend`.  Grouping by base gives the scatter, and the offsets behind
each group give the split points.  The object's placement in the game is found by masking every
relocated field and searching for the unique match, so a wrong `--vram` cannot fake a clean answer
(and the search doubles as proof the object is really there).

    tools/psyq_bss_probe.py --archive tools/psyq/lib40_elf/LIBGPU.a --object SYS.o
    tools/psyq_bss_probe.py --archive ... --object GS_001.o --vram 0x800525DC
"""
import argparse
import collections
import os
import re
import struct
import subprocess
import sys
import tempfile

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OBJDUMP = "mipsel-linux-gnu-objdump"
EXE = os.path.join(REPO, "extracted/retail/SLUS_007.26")
EXE_VRAM0 = 0x8000F800          # file offset 0 -> vram (the 0x800 PS-X EXE header sits below .text)


def _od(*args):
    return subprocess.run([OBJDUMP, *args], capture_output=True, text=True).stdout


def sections(obj):
    out = {}
    for m in re.finditer(r"^\s*\d+\s+(\.\S+)\s+([0-9a-f]+)\s+\S+\s+\S+\s+([0-9a-f]+)", _od("-h", obj), re.M):
        out[m.group(1)] = (int(m.group(2), 16), int(m.group(3), 16))   # (size, file offset)
    return out


def relocs(obj, section=".text"):
    body = re.search(r"RELOCATION RECORDS FOR \[%s\]:(.*?)(?=\nRELOCATION RECORDS|\Z)" % re.escape(section),
                     _od("-r", obj), re.S)
    if not body:
        return []
    return [(int(m.group(1), 16), m.group(2), m.group(3))
            for m in re.finditer(r"^([0-9a-f]+)\s+(R_MIPS_\w+)\s+(\S+)", body.group(1), re.M)]


def find_vram(text, rels, game):
    """The unique game offset where this object's .text sits, with every relocated field masked.

    Masking is what makes the search honest: relocated immediates DIFFER between the archive object
    and the linked game, so an exact byte search would find nothing and a loose one would find noise.
    A unique hit is also proof the object is present at all (R14)."""
    mask = bytearray(b"\xff" * len(text))
    for off, kind, _t in rels:
        if off + 4 <= len(mask):
            if kind in ("R_MIPS_HI16", "R_MIPS_LO16"):
                mask[off:off + 2] = b"\x00\x00"          # low half-word (little-endian immediate)
            elif kind == "R_MIPS_26":
                mask[off:off + 4] = b"\x00\x00\x00\x00"
            elif kind == "R_MIPS_32":
                mask[off:off + 4] = b"\x00\x00\x00\x00"
    tb, mb = bytes(text), bytes(mask)
    hits = []
    for base in range(0, len(game) - len(tb), 4):
        ok = True
        for i in range(0, len(tb), 4):
            if mb[i] == 0 and mb[i + 1] == 0 and mb[i + 2] == 0xff:      # HI/LO: compare top half only
                if game[base + i + 2:base + i + 4] != tb[i + 2:i + 4]:
                    ok = False; break
            elif mb[i] == 0:
                continue
            elif game[base + i:base + i + 4] != tb[i:i + 4]:
                ok = False; break
        if ok:
            hits.append(base)
            if len(hits) > 1:
                break
    return hits


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--archive", required=True)
    ap.add_argument("--object", required=True)
    ap.add_argument("--vram", default=None, help="skip the search; the object's .text vram")
    a = ap.parse_args()

    with tempfile.TemporaryDirectory() as td:
        subprocess.run(["ar", "x", os.path.abspath(a.archive), a.object], cwd=td, check=True)
        obj = os.path.join(td, a.object)
        secs = sections(obj)
        if ".text" not in secs:
            sys.exit("%s: no .text section" % a.object)
        if ".bss" not in secs:
            # NOT AN ERROR, AND SAYING SO MATTERS. The first version exited "no .text/.bss" here,
            # which reads as a malformed object; it actually means the scattered-.bss wall CANNOT
            # apply. Measured: 2D_BG0.o and VM_NO1.o both land here, and both are excluded in
            # splat.us.exe.yaml under a reason that is about .bss. (R61a: a tool must not report a
            # clean answer as a failure.)
            print("%s: .text %d ins, NO .bss SECTION — the scattered-.bss wall does not apply to "
                  "this object; whatever excludes it is a different reason."
                  % (a.object, secs[".text"][0] // 4))
            return 0
        tsize, toff = secs[".text"]
        text = open(obj, "rb").read()[toff:toff + tsize]
        rels = relocs(obj, ".text")
        game = open(EXE, "rb").read()

        if a.vram:
            goff = int(a.vram, 0) - EXE_VRAM0
        else:
            hits = find_vram(text, rels, game)
            if len(hits) != 1:
                sys.exit("%s: masked .text search found %d placements — pass --vram" % (a.object, len(hits)))
            goff = hits[0]
        print("%s: .text %d ins @ vram %#010x  (.bss %d bytes)"
              % (a.object, tsize // 4, goff + EXE_VRAM0, secs[".bss"][0]))

        # every section's .bss references, so the split is provably complete (R32)
        other = {s: sum(1 for _o, _k, t in relocs(obj, s) if t == ".bss")
                 for s in secs if s not in (".text", ".bss", ".note")}
        by = collections.defaultdict(list)
        i, rl = 0, [r for r in rels if r[2] == ".bss"]
        while i < len(rl) - 1:
            (o1, k1, _), (o2, k2, _) = rl[i], rl[i + 1]
            if k1 == "R_MIPS_HI16" and k2 == "R_MIPS_LO16":
                ohi = struct.unpack_from("<I", text, o1)[0] & 0xFFFF
                olo = struct.unpack_from("<I", text, o2)[0] & 0xFFFF
                addend = (ohi << 16) + ((olo ^ 0x8000) - 0x8000)
                ghi = struct.unpack_from("<I", game, goff + o1)[0] & 0xFFFF
                glo = struct.unpack_from("<I", game, goff + o2)[0] & 0xFFFF
                resolved = (ghi << 16) + ((glo ^ 0x8000) - 0x8000)
                by[resolved - addend].append(addend)
                i += 2
            else:
                i += 1
        if not by:
            print("   no .bss HI16/LO16 pairs — nothing blocking a NOLOAD placement here")
            return 0
        groups = sorted((b, min(v), max(v), len(v)) for b, v in by.items())
        for b, lo, hi, n in groups:
            print("   base %#010x : %2d ref(s), .bss offsets %#06x..%#06x" % (b, n, lo, hi))
        disjoint = all(groups[i][2] < groups[i + 1][1] for i in range(len(groups) - 1))
        extra = {s: n for s, n in other.items() if n}
        print("   SPLITTABLE: %s%s" % (
            "YES — ranges are disjoint, split at %s" % ", ".join(hex(g[1]) for g in groups[1:])
            if disjoint else "NO — the offset ranges interleave; a split cannot separate them",
            "" if not extra else "  ⚠ but %s also reference .bss (%s) — those must be covered too"
                                 % (",".join(extra), extra)))
        return 0


if __name__ == "__main__":
    sys.exit(main())
