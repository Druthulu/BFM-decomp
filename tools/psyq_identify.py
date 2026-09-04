#!/usr/bin/env python3
"""Locate where PsyQ library objects are linked in the target EXE.

For each ELF .o (converted from a PsyQ .LIB member), extract its `.text` and the
relocation offsets, build a relocation-masked word pattern (relocated immediate
fields zeroed), and scan the EXE text for the single position where every
NON-relocated word matches. That position is the object's link address in the EXE
(or "absent" if the EXE doesn't link it). This is the placement map the library
linker step consumes.

Usage:  psyq_identify.py <elf_dir> [text_lo_vram text_hi_vram] [--vram-base HEX] [--exe PATH]
        (window defaults to the BFM .text 0x80010000..0x800629DC; --vram-base/--exe default to
        the EXE's values, becoming required in Phase-9 T8 once every caller passes them)
"""
import struct, subprocess, re, sys, glob, os, argparse

# Phase 9: --vram-base (fileoff->vram delta) and --exe are REQUIRED (no EXE default an overlay
# could silently inherit). The optional [lo hi] window only narrows the placement scan.
_ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
_ap.add_argument("elf_dir", nargs="?", default=".run/obj40/libcd")
_ap.add_argument("window", nargs="*", help="optional scan-narrowing window: text_lo_vram text_hi_vram")
_ap.add_argument("--vram-base", required=True,
                 help="fileoff->vram delta of the target binary (e.g. the EXE's 0x8000F800)")
_ap.add_argument("--exe", required=True, help="target binary path")
_a = _ap.parse_args()
ELF_DIR = _a.elf_dir
EXE = _a.exe
VRAM_BASE = int(_a.vram_base, 0)
TLO = int(_a.window[0], 0) if len(_a.window) > 0 else 0x80010000
THI = int(_a.window[1], 0) if len(_a.window) > 1 else 0x800629DC

b = open(EXE, "rb").read()
text = b[TLO - VRAM_BASE: THI - VRAM_BASE]
twords = [struct.unpack_from("<I", text, i)[0] for i in range(0, len(text), 4)]

def obj_text_pattern(o):
    """Return (words, mask) for the object's `.text`, READ FROM THE SECTION BYTES.

    WHY NOT `objdump -dr` (P31 S77).  The first version parsed one word per DISASSEMBLY LINE, and
    objdump COLLAPSES a run of identical words into a single `...` line.  Every collapsed word was
    silently missing from the pattern, so from the first run onward the pattern was MISALIGNED
    against the image and `find` returned None -- reported as the confident, wrong sentence
    "not linked by EXE".

    Measured on `2D_BG0.o` (libgs): 3 `...` lines, **520 words parsed for a 526-word object**, so
    it was listed as absent while 507 of its 507 non-relocated words match the EXE exactly at
    0x8005080C.  It had been excluded from the LINKED build under a `.bss` reason that cannot even
    apply to it -- the object has no `.bss` section at all.  Any object whose `.text` holds a run of
    >=3 identical words was invisible to this map, which is the map the whole library-linking
    pipeline consumes.

    Reading the section bytes and taking relocation offsets from `objdump -r` removes the rendering
    from the loop entirely (R33: derive from the bytes, do not re-parse a pretty-printer)."""
    h = subprocess.run(["mipsel-linux-gnu-objdump", "-h", o], capture_output=True, text=True).stdout
    m = re.search(r"^\s*\d+\s+\.text\s+([0-9a-f]+)\s+\S+\s+\S+\s+([0-9a-f]+)", h, re.M)
    if not m:
        return [], []                      # data-only object (e.g. libgs GLOBAL.o)
    size, off = int(m.group(1), 16), int(m.group(2), 16)
    blob = open(o, "rb").read()[off:off + size]
    words = list(struct.unpack("<%dI" % (len(blob) // 4), blob[:len(blob) // 4 * 4]))
    mask = [0 if (w >> 26) in (2, 3) else 0xFFFFFFFF for w in words]   # jal/j always link-resolved
    rr = subprocess.run(["mipsel-linux-gnu-objdump", "-r", o], capture_output=True, text=True).stdout
    body = re.search(r"RELOCATION RECORDS FOR \[\.text\]:(.*?)(?=\nRELOCATION RECORDS|\Z)", rr, re.S)
    if body:
        for rm in re.finditer(r"^([0-9a-f]+)\s+(R_MIPS_\w+)", body.group(1), re.M):
            i = int(rm.group(1), 16) // 4
            if 0 <= i < len(mask):
                mask[i] = 0 if "_26" in rm.group(2) else 0xFFFF0000
    return words, mask


def find(words, mask):
    n = len(words)
    if n < 2:
        return None  # too short to anchor uniquely
    hits = []
    for s in range(0, len(twords) - n + 1):
        ok = True
        for i in range(n):
            if (twords[s + i] & mask[i]) != (words[i] & mask[i]):
                ok = False; break
        if ok:
            hits.append(s)
            if len(hits) > 1:
                break
    if len(hits) == 1:
        return TLO + hits[0] * 4
    return ("ambiguous" if len(hits) > 1 else None)

results = []
for o in sorted(glob.glob(os.path.join(ELF_DIR, "*.o"))):
    words, mask = obj_text_pattern(o)
    if not words:
        results.append((os.path.basename(o), "no-.text", len(words))); continue
    r = find(words, mask)
    results.append((os.path.basename(o), r, len(words)))

found = [(n, a, l) for n, a, l in results if isinstance(a, int)]
found.sort(key=lambda x: x[1])
print(f"{ELF_DIR}: {len(found)}/{len(results)} objects located in EXE text "
      f"[0x{TLO:X}..0x{THI:X}]")
for n, a, l in found:
    print(f"  0x{a:08X}  {n:18s} ({l} ins)")
absent = [n for n, a, l in results if a is None]
amb = [n for n, a, l in results if a == "ambiguous"]
if absent:
    print(f"  not linked by EXE ({len(absent)}): {', '.join(absent[:12])}{' …' if len(absent)>12 else ''}")
if amb:
    print(f"  ambiguous ({len(amb)}): {', '.join(amb)}")
