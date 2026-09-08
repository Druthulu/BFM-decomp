#!/usr/bin/env python3
"""psyq_bss_probe.py — can this PsyQ object's scattered `.bss` be SPLIT and placed? (P31 S77; S78 #4: yes, and it is)

THE WALL THIS INTERROGATES.  `config/splat.us.exe.yaml` had excluded library objects from the
LINKED build since Phase 8 with one recorded reason:

    SYS.o EXCLUDED — scattered-.bss commons (the GS_001 class: SYS references .bss by section+offset
    but the original linker scattered the commons across 0x80078xxx/0x800c5xxx, so no single NOLOAD
    base reproduces it)

That reason is CORRECT — §9.2's "weaken the `.bss` symbol and `--defsym` it" cannot reach these
sites, because a `R_MIPS_HI16/LO16` against the bare `.bss` SECTION has no name to defsym.  But "no
single base" is not the same claim as "unlinkable", and nobody had asked the next question: **can the
section be cut into pieces that each have ONE base?**  This probe asked it (S77) and
`tools/psyq_bss_split.py` (S78 #4) answers it at link-prepare time for every object in the build.

WHAT "SPLITTABLE" MEANS NOW (the S77 test was too strict — corrected S78).  The S77 probe grouped the
references BY BASE and required the per-base offset ranges to be disjoint.  That verdict was right
for SYS.o and VM_F.o (two bases, two ranges) and WRONG for GS_001.o, which it called "5 interleaved
bases": walked in OFFSET order, GS_001's references form six single-base RUNS, and every cut between
two runs lands on a symbol start (PSDBASEX, CLIP2, PSDBASEY, POSITION, GsDRAWENV) — exactly what
"the linker scattered the commons" predicts.  The linker scattered SYMBOLS, so the right question is
whether the runs can be tiled at symbol boundaries without a sized symbol straddling a cut.  All
three objects can; all three link byte-identical through the split (psyq_link.py PASS).

HOW IT DERIVES THE BASE — from the bytes, not from a config.  For each HI16/LO16 pair against the
section symbol, the OBJECT's immediates encode the addend and the GAME's immediates encode the
resolved address; `base = resolved − addend`.  Grouping by base shows the scatter; the runs give the
cut points.  The object's placement in the game is found by masking every relocated field and
searching for the unique match, so a wrong `--vram` cannot fake a clean answer (and the search
doubles as proof the object is really there).  The analysis itself lives in `psyq_bss_split.analyze`
(R33: one implementation; this file only extracts, locates and reports).

    tools/psyq_bss_probe.py --archive tools/psyq/lib40_elf/LIBGPU.a --object SYS.o
    tools/psyq_bss_probe.py --archive ... --object GS_001.o --vram 0x800525DC
"""
import argparse
import os
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from psyq_bss_split import Elf32, SHT_NOBITS, R_MIPS_HI16, R_MIPS_LO16, SplitRefused, analyze, report  # noqa: E402

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
EXE = os.path.join(REPO, "extracted/retail/SLUS_007.26")
EXE_VRAM0 = 0x8000F800          # file offset 0 -> vram (the 0x800 PS-X EXE header sits below .text)
R_MIPS_26, R_MIPS_32 = 4, 2


def find_vram(e, game):
    """The unique game offset where this object's .text sits, with every relocated field masked.

    Masking is what makes the search honest: relocated immediates DIFFER between the archive object
    and the linked game, so an exact byte search would find nothing and a loose one would find noise.
    A unique hit is also proof the object is present at all (R14)."""
    ti = e.section_index(".text")
    text = bytes(e.data[ti])
    mask = bytearray(b"\xff" * len(text))
    for ri, rl in e.rels.items():
        if e.sh[ri]["info"] != ti:
            continue
        for off, _sym, typ in rl:
            if off + 4 <= len(mask):
                if typ in (R_MIPS_HI16, R_MIPS_LO16):
                    mask[off:off + 2] = b"\x00\x00"          # low half-word (little-endian immediate)
                elif typ in (R_MIPS_26, R_MIPS_32):
                    mask[off:off + 4] = b"\x00\x00\x00\x00"
    tb, mb = text, bytes(mask)
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

    with tempfile.TemporaryDirectory(dir=os.path.join(REPO, ".run")) as td:
        subprocess.run(["ar", "x", os.path.abspath(a.archive), a.object], cwd=td, check=True)
        obj = os.path.join(td, a.object)
        e = Elf32(open(obj, "rb").read())
        names = [e.secname(i) for i in range(len(e.sh))]
        if ".text" not in names:
            sys.exit("%s: no .text section" % a.object)
        nobits = [i for i, s in enumerate(e.sh) if s["type"] == SHT_NOBITS]
        tsize = e.sh[e.section_index(".text")]["size"]
        if not nobits:
            # NOT AN ERROR, AND SAYING SO MATTERS. The first version exited "no .text/.bss" here,
            # which reads as a malformed object; it actually means the scattered-.bss wall CANNOT
            # apply. Measured: 2D_BG0.o and VM_NO1.o both land here, and both were excluded in
            # splat.us.exe.yaml under a reason that is about .bss. (R61a: a tool must not report a
            # clean answer as a failure.)
            print("%s: .text %d ins, NO .bss SECTION — the scattered-.bss wall does not apply to "
                  "this object; whatever excludes it is a different reason." % (a.object, tsize // 4))
            return 0
        game = open(EXE, "rb").read()
        if a.vram:
            goff = int(a.vram, 0) - EXE_VRAM0
        else:
            hits = find_vram(e, game)
            if len(hits) != 1:
                sys.exit("%s: masked .text search found %d placements — pass --vram" % (a.object, len(hits)))
            goff = hits[0]
        print("%s: .text %d ins @ vram %#010x  (%s)"
              % (a.object, tsize // 4, goff + EXE_VRAM0,
                 ", ".join("%s %d bytes" % (e.secname(i), e.sh[i]["size"]) for i in nobits)))
        try:
            plans = analyze(obj, goff + EXE_VRAM0, game, EXE_VRAM0, elf=e)
        except SplitRefused as ex:
            print("   SPLITTABLE: NO — %s" % ex)
            return 1
        if not plans:
            print("   no references through a NOBITS section symbol — nothing blocking a NOLOAD placement here")
            return 0
        print("\n".join(report(plans, a.object).splitlines()[1:]))    # report()'s first line repeats the header
        return 0


if __name__ == "__main__":
    sys.exit(main())
