#!/usr/bin/env python3
"""Locate where PsyQ library objects are linked in the target EXE.

For each ELF .o (converted from a PsyQ .LIB member), extract its `.text` and the
relocation offsets, build a relocation-masked word pattern (relocated immediate
fields zeroed), and scan the EXE text for the single position where every
NON-relocated word matches. That position is the object's link address in the EXE
(or "absent" if the EXE doesn't link it). This is the placement map the library
linker step consumes.

Usage:  psyq_identify.py <elf_dir> [text_lo_vram text_hi_vram]
        (defaults to the BFM .text window 0x80010000..0x800629DC)
"""
import struct, subprocess, re, sys, glob, os

EXE = "extracted/retail/SLUS_007.26"
VRAM_BASE = 0x8000F800
ELF_DIR = sys.argv[1] if len(sys.argv) > 1 else ".run/obj40/libcd"
TLO = int(sys.argv[2], 0) if len(sys.argv) > 2 else 0x80010000
THI = int(sys.argv[3], 0) if len(sys.argv) > 3 else 0x800629DC

b = open(EXE, "rb").read()
text = b[TLO - VRAM_BASE: THI - VRAM_BASE]
twords = [struct.unpack_from("<I", text, i)[0] for i in range(0, len(text), 4)]

def obj_text_pattern(o):
    """Return (words, mask) for the object's .text; mask[i]=0 on relocated/jump words."""
    d = subprocess.check_output(["mipsel-linux-gnu-objdump", "-dr", "-j", ".text", o],
                                text=True, stderr=subprocess.DEVNULL)
    words, mask = [], []
    pending_reloc = False
    for line in d.splitlines():
        mi = re.match(r"\s+([0-9a-f]+):\s+([0-9a-f]{8})\s", line)
        if mi:
            w = int(mi.group(2), 16)
            words.append(w)
            # mask jal/j (opcode 2/3) always (R_MIPS_26 target is link-resolved)
            mask.append(0 if (w >> 26) in (2, 3) else 0xFFFFFFFF)
        elif "R_MIPS" in line and words:
            # relocation annotation follows its instruction line -> mask low 16 (hi/lo/pc16)
            if "_26" in line:
                mask[-1] = 0
            else:
                mask[-1] = 0xFFFF0000
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
