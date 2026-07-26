#!/usr/bin/env python3
"""Drop-one ablations against the MATCHing func_8017C730 draft.
usage: c730_abl.py <base_body.c>   -- prints each ablation's match_one result."""
import sys, os, subprocess, concurrent.futures

BASE = sys.argv[1] if len(sys.argv) > 1 else '/home/musashi/bfm-decomp/.run/c730/base3.c'
R = '/home/musashi/bfm-decomp'
src = open(BASE).read()

INLINE_BLOCK = (
 "    { MATRIX2 rot; MATRIX2 inv; SVECTOR2 dv;\n"
 "      extern void func_8004974C(MATRIX2 *, MATRIX2 *);\n"
 "      extern void ReadRotMatrix(MATRIX2 *);\n"
 "      extern void PushMatrix(void);\n"
 "      extern void PopMatrix(void);\n"
 "      extern void ApplyMatrixSV(MATRIX2 *, SVECTOR2 *, SVECTOR2 *);\n"
 "      ReadRotMatrix(&rot);\n"
 "      PushMatrix();\n"
 "      dv.vx = org.vx - rot.t[0];\n"
 "      dv.vy = org.vy - rot.t[1];\n"
 "      dv.vz = org.vz - rot.t[2];\n"
 "      func_8004974C(&rot, &inv);\n"
 "      ApplyMatrixSV(&inv, &dv, &hv);\n"
 "      PopMatrix(); }")

ABL = {
 'L1-no-inline-helper':      [("    bandsetup(&org, &hv);", INLINE_BLOCK)],
 'L2-g-as-struct':           [("    long gflag, gopz, gsz0, gsz1, gsz2, gsz3;",
                               "    struct { long flag, opz, sz0, sz1, sz2, sz3; } g;"),
                              ("gflag","g.flag"),("gopz","g.opz"),("gsz0","g.sz0"),
                              ("gsz1","g.sz1"),("gsz2","g.sz2"),("gsz3","g.sz3")],
 'L3-rgbc-via-struct-A+C':   [("                                        *(u32 *)(pkt + 4) = prim->w0;",
                               "                                        ((PolyF3 *)pkt)->rgbc = prim->w0;"),
                              ("                                            *(u32 *)(pkt + 4) = prim->w0;",
                               "                                            ((PolyF4 *)pkt)->rgbc = prim->w0;")],
 'L4-no-t32-launder':        [("                t32 = mid;\n                if (!(hhi < t32))",
                               "                if (!(hhi < mid))")],
 'L5-no-mnc-dial':           [(' __asm__ volatile ("" : : "r" (mnc));', '')],
 'L6-wv-computed-late':      [("        wv = wz >> 16;\n        mid", "        mid"),
                              ("        box[0].vx = mn; box[0].vy = mny; box[0].vz = wz;",
                               "        wv = wz >> 16;\n        box[0].vx = mn; box[0].vy = mny; box[0].vz = wz;")],
 'L7-armB-otp-last':         [("                                        otp = (u32 *)(((gopz >> 2) << 2) + ot);\n                                        ((PolyFT3 *)pkt)->uvc0",
                               "                                        ((PolyFT3 *)pkt)->uvc0"),
                              ("                                        ((PolyFT3 *)pkt)->uv2 = tp[3];",
                               "                                        ((PolyFT3 *)pkt)->uv2 = tp[3];\n                                        otp = (u32 *)(((gopz >> 2) << 2) + ot);")],
 'L8-armD-share-uvw':        [("                                            uvm = tp[1] & 0x3FC0FFFF;",
                               "                                            uvw = tp[1] & 0x3FC0FFFF;"),
                              ("                                            ((PolyFT4 *)pkt)->uvc0 = uvm |",
                               "                                            ((PolyFT4 *)pkt)->uvc0 = uvw |"),
                              ("                                            u32 uvm;\n", "")],
 'L9-armB-clut-inline':      [("                                        uvw = tp[1] & 0x3FC0FFFF;\n", ""),
                              ("((PolyFT3 *)pkt)->uvc0 = uvw |", "((PolyFT3 *)pkt)->uvc0 = (tp[1] & 0x3FC0FFFF) |")],
 'L10-add-sec47-slider':     [("        gte_ldv3c(&box[4]);", "        gte_ldv3c(&box[4]);\n        __asm__ volatile (\"\");")],
 'L11-no-avsz3':             [("                                        gte_avsz3();\n", "")],
 'L12-nprim-after-nparts':   [("    u32 nprim;\n    s32 nparts;", "    s32 nparts;\n    u32 nprim;")],
}

def run(item):
    name, edits = item
    s = src
    for old, new in edits:
        if s.count(old) == 0:
            return '%-26s :: PATTERN-NOT-FOUND %r' % (name, old[:50])
        s = s.replace(old, new)
    d = R + '/.run/c730/abl'
    os.makedirs(d, exist_ok=True)
    body = d + '/b_%s.c' % name
    out = d + '/v_%s.c' % name
    open(body, 'w').write(s)
    subprocess.run(['python3', R + '/.run/giants/c730_mk.py', body, out],
                   capture_output=True, cwd=R)
    r = subprocess.run(['python3', 'tools/match_one.py', 'func_8017C730', '--c', out,
                        '--asm-subdir', 'asm/ov_SC03_010/nonmatchings/ov_SC03_010_jr_8017AE2C'],
                       capture_output=True, text=True, cwd=R)
    line = (r.stdout + r.stderr).strip().splitlines()
    return '%-26s :: %s' % (name, ' | '.join(l.strip() for l in line[:2]))

with concurrent.futures.ThreadPoolExecutor(max_workers=8) as ex:
    for res in ex.map(run, sorted(ABL.items())):
        print(res)
