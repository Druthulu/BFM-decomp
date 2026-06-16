#!/usr/bin/env python3
"""Generate splat subseg lines + the psyq_integrate stub list for a MULTI-BLOCK PsyQ library.

A library's objects are usually scattered across a game-code region in several contiguous blocks
(libgte = 26 blocks, libsnd = 16, libspu = 10). Hand-resegmenting the splat yaml for each block is
tedious and trips the boundary gotcha. This tool does it mechanically:

  - place the library's objects with psyq_identify (optional window for short/ambiguous objects),
  - group them into contiguous blocks (next.vram == prev.vram + prev.ins*4),
  - END each block at its last object's `.text` SECTION size (8-aligned), NOT its instruction count
    — psyq_identify reports ins count, which omits trailing align pad (the libc2/T6 gotcha that
    shifted the whole image),
  - within the containing region [region_lo, region_hi) emit, in vram order, a game-code fragment
    subseg for each gap and a `c` subseg for each library block,
  - print the comma-joined stub list for the psyq_integrate.py call.

Game-code fragments are named <gamebase>, <gamebase>_2, <gamebase>_3, …; library blocks <libbase>1,
<libbase>2, …. Objects placed OUTSIDE [region_lo, region_hi) (a library's stragglers in another
region, e.g. libgte's 4 objects in the libgs gaps) are listed as SKIPPED for separate handling.

Usage:
  gen_lib_subsegs.py <elf_dir> <libbase> <gamebase> <region_vram_lo> <region_vram_hi> [win_lo win_hi]

Example (libgte in the 800b region, no window):
  gen_lib_subsegs.py .run/obj40/libgte libgte 800b 0x8004787C 0x80051804
"""
import os, re, subprocess, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from psyq_link import section_table  # noqa: E402


def placements(elf_dir, win, vram_base, exe):
    cmd = ["python3", "tools/psyq_identify.py", elf_dir]
    if win:
        cmd += [f"0x{win[0]:X}", f"0x{win[1]:X}"]
    cmd += ["--vram-base", hex(vram_base), "--exe", exe]
    objs = []
    for ln in subprocess.check_output(cmd, text=True).splitlines():
        m = re.match(r"\s+0x([0-9A-Fa-f]+)\s+(\S+\.o)\s+\((\d+) ins\)", ln)
        if m:
            objs.append((int(m.group(1), 16), m.group(2), int(m.group(3))))
    return sorted(objs)


def contiguous_blocks(objs):
    blocks, cur = [], [objs[0]]
    for o in objs[1:]:
        if o[0] == cur[-1][0] + cur[-1][2] * 4:
            cur.append(o)
        else:
            blocks.append(cur)
            cur = [o]
    blocks.append(cur)
    return blocks


def main():
    import argparse
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("elf_dir")
    ap.add_argument("libbase")
    ap.add_argument("gamebase")
    ap.add_argument("region_lo")
    ap.add_argument("region_hi")
    ap.add_argument("window", nargs="*", help="optional placement window: win_lo win_hi")
    ap.add_argument("--vram-base", default="0x8000F800", help="fileoff->vram delta (EXE default)")
    ap.add_argument("--exe", default="extracted/retail/SLUS_007.26", help="target binary (EXE default)")
    a = ap.parse_args()
    elf_dir, libbase, gamebase = a.elf_dir, a.libbase, a.gamebase
    rlo, rhi = int(a.region_lo, 0), int(a.region_hi, 0)
    win = (int(a.window[0], 0), int(a.window[1], 0)) if len(a.window) >= 2 else None
    vram_base = int(a.vram_base, 0)

    objs = placements(elf_dir, win, vram_base, a.exe)
    inreg = [o for o in objs if rlo <= o[0] < rhi]
    skipped = [o for o in objs if not (rlo <= o[0] < rhi)]
    if not inreg:
        sys.exit(f"no {libbase} objects placed in [0x{rlo:X},0x{rhi:X})")

    blocks = contiguous_blocks(inreg)
    ranges = []
    for b in blocks:
        lo = b[0][0]
        last = b[-1]
        tsize = section_table(os.path.join(elf_dir, last[1]))[".text"][0]
        hi = last[0] + tsize                       # section-size end (the gotcha fix)
        ranges.append((lo, hi, b))

    out, stubs = [], []
    pos, gi, li = rlo, 0, 0

    def gname():
        nonlocal gi
        gi += 1
        return gamebase if gi == 1 else f"{gamebase}_{gi}"

    for lo, hi, b in ranges:
        if lo > pos:
            nm = gname()
            out.append(f"      - [0x{pos - vram_base:X}, c, {nm}]"
                       f"  # game code (vram 0x{vram_base + (pos - vram_base):08X}-0x{lo:08X})")
        li += 1
        sub = f"{libbase}{li}"
        stubs.append(sub)
        names = f"{b[0][1]}..{b[-1][1]}" if len(b) > 1 else b[0][1]
        out.append(f"      - [0x{lo - vram_base:X}, c, {sub}]"
                   f"  # {libbase} block {li}: {len(b)} obj ({names}) vram 0x{lo:08X}-0x{hi:08X}")
        pos = hi
    if pos < rhi:
        nm = gname()
        out.append(f"      - [0x{pos - vram_base:X}, c, {nm}]"
                   f"  # game code (vram 0x{pos:08X}-0x{rhi:08X})")

    print("\n".join(out))
    print()
    print(f"# {len(blocks)} blocks / {len(inreg)} objects in region; integrate stub list:")
    print(",".join(stubs))
    if skipped:
        print(f"\n# SKIPPED — {len(skipped)} object(s) placed OUTSIDE [0x{rlo:X},0x{rhi:X}) "
              f"(handle separately): {[s[1] for s in skipped]}")


if __name__ == "__main__":
    main()
