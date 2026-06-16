#!/usr/bin/env python3
"""Build .run/obj40/apicard_used = the combined libapi+libcard objects in the 800c2 region (Phase 8).

libapi (BIOS syscall trampolines) and libcard interleave in 0x80061F38..0x80062888 with one shared
object (C112.o, identical in both libs). Linked as one 22-object combined region. No exclusions — every
object byte-matches. (libapi ALSO has ~22 objects in the 800c3 region 0x5CE18.., DEFERRED — lowest
value, separate resegmentation.) Regenerate: tools/psyq_build_libs.sh LIBAPI LIBCARD first.
"""
import os, re, shutil, subprocess, sys
from collections import defaultdict
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from psyq_link import link_object  # noqa: E402

EXE = "extracted/retail/SLUS_007.26"
RLO, RHI = 0x80061F38, 0x80062888


def place(lib):
    out = subprocess.check_output(["python3", "tools/psyq_identify.py", f".run/obj40/{lib}"], text=True)
    return {m.group(2): int(m.group(1), 16)
            for ln in out.splitlines()
            if (m := re.match(r"\s+0x([0-9A-Fa-f]+)\s+(\S+\.o)\s+\((\d+) ins\)", ln))}


def main():
    exe = open(EXE, "rb").read()
    byaddr = defaultdict(list)
    for lib in ("libapi", "libcard"):
        for nm, a in place(lib).items():
            byaddr[a].append((lib, nm))
    dst = ".run/obj40/apicard_used"
    shutil.rmtree(dst, ignore_errors=True)
    os.makedirs(dst)
    n = 0
    for a in sorted(byaddr):
        if not (RLO <= a < RHI):
            continue
        lib, nm = next(((l, m) for l, m in byaddr[a]
                        if link_object(f".run/obj40/{l}/{m}", a, name=m, exe_bytes=exe)["ok"]),
                       byaddr[a][0])
        shutil.copy(f".run/obj40/{lib}/{nm}", f"{dst}/{nm}")
        n += 1
    print(f"apicard_used: {n} objects (libapi+libcard combined, 800c2 region)")


if __name__ == "__main__":
    main()
