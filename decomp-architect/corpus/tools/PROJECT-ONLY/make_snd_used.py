#!/usr/bin/env python3
"""Build the curated .run/obj40/snd_used dir = the combined libspu+libsnd sound region (Phase 8).

libspu and libsnd are tightly interleaved in 0x8003A444..0x8004239C (the tail of the 800 subseg), so
they are linked as ONE combined region rather than two passes. This:
  - places both libraries' objects (psyq_identify) and merges them by vram,
  - for an aliased address (>1 object, same masked .text) picks the object whose linked .text
    byte-matches the EXE (psyq_link.link_object) — the real one,
  - EXCLUDES 3 ADDRESSES that don't reconcile in the combined region (ALL candidates there stay
    byte-identical stubs — excluding by address, not name, since the alias twin fails identically):
      0x3C438 (S_R/S_W), 0x3D424 (S_GRMDT/FB/T) — commons referenced at a minority address the
        region's single defsym can't satisfy (cookbook §9.1, cross-object form; these objects have NO
        .bss of their own — psyq_bss_probe — so the S78 split does not apply to them),
      0x3D94C (S_IH/UT_RON)                      — false placement: 0x3D94C is INSIDE libsnd SSSTART.o.
    0x3FA64 (VM_F.o, 237 ins) was the 4th exclusion (scattered-.bss commons) until P31 S78 #4: its
    `.bss` is now SPLIT at link-prepare (psyq_bss_split, cookbook §489) and it links as snd12.
  - copies the survivors into .run/obj40/snd_used.

The build is byte-identical with OR without snd_used (stub fallback), so a fresh clone need not run
this unless it wants the SDK objects linked. Regenerate: tools/psyq_build_libs.sh LIBSPU LIBSND first.
"""
import os, re, shutil, subprocess, sys
from collections import defaultdict
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from psyq_link import link_object  # noqa: E402

# EXE-curation tool: --exe/--vram-base default to the retail EXE's values (threaded explicitly into
# psyq_identify + link_object, which require them post-T8). RLO/RHI/EXCLUDE_ADDR are the EXE's sound
# region + the 4 unreconcilable addresses (EXE-specific; an overlay would supply its own).
EXE = "extracted/retail/SLUS_007.26"
VRAM_BASE = 0x8000F800
RLO, RHI = 0x8003A444, 0x8004239C
EXCLUDE_ADDR = {0x8003C438, 0x8003D424, 0x8003D94C}   # see module docstring (VM_F 0x8003FA64 rejoined S78 #4)


def place(lib, exe, vram_base):
    out = subprocess.check_output(["python3", "tools/psyq_identify.py", f".run/obj40/{lib}",
                                   "--vram-base", hex(vram_base), "--exe", exe], text=True)
    d = {}
    for ln in out.splitlines():
        m = re.match(r"\s+0x([0-9A-Fa-f]+)\s+(\S+\.o)\s+\((\d+) ins\)", ln)
        if m:
            d[m.group(2)] = int(m.group(1), 16)
    return d


def main():
    import argparse
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--exe", default=EXE)
    ap.add_argument("--vram-base", default=hex(VRAM_BASE))
    args = ap.parse_args()
    exe_path, vram_base = args.exe, int(args.vram_base, 0)
    exe = open(exe_path, "rb").read()
    byaddr = defaultdict(list)
    for lib in ("libspu", "libsnd"):
        for nm, a in place(lib, exe_path, vram_base).items():
            byaddr[a].append((lib, nm))

    dst = ".run/obj40/snd_used"
    shutil.rmtree(dst, ignore_errors=True)
    os.makedirs(dst)
    n = 0
    for a in sorted(byaddr):
        if not (RLO <= a < RHI) or a in EXCLUDE_ADDR:
            continue
        cands = byaddr[a]
        pick = next(((lib, nm) for lib, nm in cands
                     if link_object(f".run/obj40/{lib}/{nm}", a, name=nm, exe_bytes=exe,
                                    vram_base=vram_base)["ok"]),
                    cands[0])
        lib, nm = pick
        shutil.copy(f".run/obj40/{lib}/{nm}", f"{dst}/{nm}")
        n += 1
    print(f"snd_used: {n} objects (libspu+libsnd combined; {len(EXCLUDE_ADDR)} addresses excluded: "
          f"{[hex(x) for x in sorted(EXCLUDE_ADDR)]})")


if __name__ == "__main__":
    main()
