#!/usr/bin/env python3
"""Asserting variant generator for func_8017C730.
usage: c730_mk.py <base_body.c> <out.c> [lever ...]
Every lever is a list of (old, new) pairs; each pair MUST apply (count>0) or we abort,
so a 'neutral' reading can never be a silent no-op.  Emits the full compilable file
(common.h + engine_types.h + the GTE macro block + the body)."""
import sys, os

R = '/home/musashi/bfm-decomp'
HDR = ('#include "common.h"\n'
       '#include "/home/musashi/bfm-decomp/src/shared/engine_types.h"\n')
MACROS = open(R + '/.run/c730/macros.inc.c').read()

L = {}

# ---- the dead `mnc = hmid` block: alternative spellings -------------------
L['dead_none'] = [("                if (!(hhi < mid)) mnc = hmid;\n", "")]
L['dead_asm'] = [("                if (!(hhi < mid)) mnc = hmid;",
                  "                if (!(hhi < mid)) { mnc = hmid; __asm__ volatile (\"\" : : \"r\" (mnc)); }")]
L['dead_ternary'] = [("                if (!(hhi < mid)) mnc = hmid;",
                      "                mnc = (hhi < mid) ? mnc : hmid;")]
L['dead_mxc'] = [("                if (!(hhi < mid)) mnc = hmid;",
                  "                if (!(hhi < mid)) mxc = hmid;")]
L['dead_t32'] = [("                if (!(hhi < mid)) mnc = hmid;",
                  "                if (!(hhi < mid)) t32 = hmid;")]
L['dead_hold'] = [("                if (!(hhi < mid)) mnc = hmid;",
                   "                if (!(hhi < mid)) mnc = hmid;\n                __asm__ volatile (\"\" : : \"r\" (mnc));")]

# ---- otp hoisted above the uv stores in arms B / D ------------------------
_OTP_B = """                                        ((PolyFT3 *)pkt)->uvc0 = (tp[1] & 0x3FC0FFFF) | (((cd >> 7) + 0x30) << 16);
                                        ((PolyFT3 *)pkt)->uvp1 = tp[2];
                                        ((PolyFT3 *)pkt)->uv2 = tp[3];
                                        otp = (u32 *)(((g.opz >> 2) << 2) + ot);
"""
_OTP_B2 = """                                        otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                        ((PolyFT3 *)pkt)->uvc0 = (tp[1] & 0x3FC0FFFF) | (((cd >> 7) + 0x30) << 16);
                                        ((PolyFT3 *)pkt)->uvp1 = tp[2];
                                        ((PolyFT3 *)pkt)->uv2 = tp[3];
"""
_OTP_D = """                                            ((PolyFT4 *)pkt)->uvc0 = (tp[1] & 0x3FC0FFFF) | (((cd >> 7) + 0x30) << 16);
                                            ((PolyFT4 *)pkt)->uvp1 = tp[2];
                                            uvw = tp[3];
                                            ((PolyFT4 *)pkt)->uv2 = uvw;
                                            ((PolyFT4 *)pkt)->uv3 = uvw >> 16;
                                            otp = (u32 *)(((g.opz >> 2) << 2) + ot);
"""
_OTP_D2 = """                                            otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                            ((PolyFT4 *)pkt)->uvc0 = (tp[1] & 0x3FC0FFFF) | (((cd >> 7) + 0x30) << 16);
                                            ((PolyFT4 *)pkt)->uvp1 = tp[2];
                                            uvw = tp[3];
                                            ((PolyFT4 *)pkt)->uv2 = uvw;
                                            ((PolyFT4 *)pkt)->uv3 = uvw >> 16;
"""
L['otp_up_b'] = [(_OTP_B, _OTP_B2)]
L['otp_up_d'] = [(_OTP_D, _OTP_D2)]
L['otp_up'] = L['otp_up_b'] + L['otp_up_d']

# ---- prologue: defeat the &rot / &inv CSE --------------------------------
L['rot_ptr'] = [("    func_8004974C(&rot, &inv);", "    func_8004974C(rotp, &inv);"),
                ("    MATRIX2 rot;", "    MATRIX2 rot;\n    MATRIX2 *rotp;"),
                ("    ReadRotMatrix(&rot);", "    rotp = &rot;\n    ReadRotMatrix(rotp);")]
L['rot_first'] = [("""    ReadRotMatrix(&rot);
    PushMatrix();
    dv.vx = org.vx - rot.t[0];
    dv.vy = org.vy - rot.t[1];
    dv.vz = org.vz - rot.t[2];
    func_8004974C(&rot, &inv);
""", """    ReadRotMatrix(&rot);
    PushMatrix();
    func_8004974C(&rot, &inv);
    dv.vx = org.vx - rot.t[0];
    dv.vy = org.vy - rot.t[1];
    dv.vz = org.vz - rot.t[2];
""")]
L['org_late'] = [("""    org.vx = 0;
    org.vy = 0;
    org.vz = 0;
    ReadRotMatrix(&rot);
""", """    ReadRotMatrix(&rot);
    org.vx = 0;
    org.vy = 0;
    org.vz = 0;
""")]

# ---- part-loop body shape ------------------------------------------------
L['wz_late'] = [("        wz = part->zz;\n        mid = (mny + my) / 2;",
                 "        mid = (mny + my) / 2;\n        wz = part->zz;")]
L['wy_late'] = [("""        wy = wz >> 16;
        box[0].vx = mn; box[0].vy = mny; box[0].vz = wz;""",
                 """        box[0].vx = mn; box[0].vy = mny; box[0].vz = wz;
        wy = wz >> 16;""")]
L['no_slider'] = [("        __asm__ volatile (\"\");\n", "")]
L['mid_s32'] = [("    s16 mid;", "    s32 mid;"),
                ("        mid = (mny + my) / 2;\n        if (mid < hv.vy) continue;\n        if (hhi < mid) continue;",
                 "        mid = (mny + my) / 2;\n        if ((s16)mid < hv.vy) continue;\n        if (hhi < (s16)mid) continue;"),
                ("                if (!(hhi < mid)) mnc = hmid;", "                if (!(hhi < (s16)mid)) mnc = hmid;")]

# ---- CLUT: mask tp[1] into a temp BEFORE the cd `if` (so the and/lui/ori sit in BB1)
L['clut_temp'] = [
 ("""                                        cd = g.opz - 0x174;
                                        if (cd < 0) cd = g.opz - 0xF5;
                                        otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                        ((PolyFT3 *)pkt)->uvc0 = (tp[1] & 0x3FC0FFFF) | (((cd >> 7) + 0x30) << 16);""",
  """                                        uvw = tp[1] & 0x3FC0FFFF;
                                        cd = g.opz - 0x174;
                                        if (cd < 0) cd = g.opz - 0xF5;
                                        otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                        ((PolyFT3 *)pkt)->uvc0 = uvw | (((cd >> 7) + 0x30) << 16);"""),
 ("""                                        u32 *tp;
                                        gte_avsz3();""",
  """                                        u32 *tp;
                                        u32 uvw;
                                        gte_avsz3();"""),
 ("""                                            cd = g.opz - 0x174;
                                            if (cd < 0) cd = g.opz - 0xF5;
                                            otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                            ((PolyFT4 *)pkt)->uvc0 = (tp[1] & 0x3FC0FFFF) | (((cd >> 7) + 0x30) << 16);""",
  """                                            uvw = tp[1] & 0x3FC0FFFF;
                                            cd = g.opz - 0x174;
                                            if (cd < 0) cd = g.opz - 0xF5;
                                            otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                            ((PolyFT4 *)pkt)->uvc0 = uvw | (((cd >> 7) + 0x30) << 16);"""),
]
L['cd_block'] = [("    s32 cd;\n", ""),
                 ("                                        uvw = tp[1] & 0x3FC0FFFF;",
                  "                                        s32 cd;\n                                        uvw = tp[1] & 0x3FC0FFFF;"),
                 ("                                            uvw = tp[1] & 0x3FC0FFFF;",
                  "                                            s32 cd;\n                                            uvw = tp[1] & 0x3FC0FFFF;")]

# ---- arm D: separate temp for the CLUT mask (do not reuse uvw) -----------
L['armd_uvm'] = [("                                            uvw = tp[1] & 0x3FC0FFFF;",
                  "                                            uvm = tp[1] & 0x3FC0FFFF;"),
                 ("                                            ((PolyFT4 *)pkt)->uvc0 = uvw | (((cd >> 7) + 0x30) << 16);",
                  "                                            ((PolyFT4 *)pkt)->uvc0 = uvm | (((cd >> 7) + 0x30) << 16);"),
                 ("                                            u32 uvw;", "                                            u32 uvw;\n                                            u32 uvm;")]
L['armb_uvm'] = [("                                        uvw = tp[1] & 0x3FC0FFFF;",
                  "                                        uvm = tp[1] & 0x3FC0FFFF;"),
                 ("                                        ((PolyFT3 *)pkt)->uvc0 = uvw | (((cd >> 7) + 0x30) << 16);",
                  "                                        ((PolyFT3 *)pkt)->uvc0 = uvm | (((cd >> 7) + 0x30) << 16);"),
                 ("                                        u32 uvw;", "                                        u32 uvm;")]
# ---- CLUT: read g.opz first (cd before the mask) -------------------------
L['cd_first_d'] = [("""                                            uvw = tp[1] & 0x3FC0FFFF;
                                            cd = g.opz - 0x174;""",
                    """                                            cd = g.opz - 0x174;
                                            uvw = tp[1] & 0x3FC0FFFF;""")]
L['cd_first_b'] = [("""                                        uvw = tp[1] & 0x3FC0FFFF;
                                        cd = g.opz - 0x174;""",
                    """                                        cd = g.opz - 0x174;
                                        uvw = tp[1] & 0x3FC0FFFF;""")]
# ---- part-loop head order ------------------------------------------------
L['yy_first'] = [("""        wx = part->xx;
        mn = wx;
        mx = wx >> 16;
        wy = part->yy;
        mny = wy;
        my = wy >> 16;
        wz = part->zz;""",
                  """        wy = part->yy;
        mny = wy;
        wz = part->zz;
        wx = part->xx;
        mn = wx;
        mx = wx >> 16;
        my = wy >> 16;""")]
L['yy_first2'] = [("""        wx = part->xx;
        mn = wx;
        mx = wx >> 16;
        wy = part->yy;
        mny = wy;
        my = wy >> 16;
        wz = part->zz;""",
                   """        wy = part->yy;
        mny = wy;
        my = wy >> 16;
        wz = part->zz;
        wx = part->xx;
        mn = wx;
        mx = wx >> 16;""")]
L['zz_first'] = [("""        wx = part->xx;
        mn = wx;
        mx = wx >> 16;
        wy = part->yy;
        mny = wy;
        my = wy >> 16;
        wz = part->zz;""",
                  """        wy = part->yy;
        wz = part->zz;
        mny = wy;
        wx = part->xx;
        mn = wx;
        mx = wx >> 16;
        my = wy >> 16;""")]

# ---- part head: separate var for wz>>16, computed before the culls -------
_BOXW = """        wy = wz >> 16;
        box[0].vx = mn; box[0].vy = mny; box[0].vz = wz;
        box[1].vx = mx; box[1].vy = mny; box[1].vz = wz;
        box[2].vx = mn; box[2].vy = mny; box[2].vz = wy;
        box[3].vx = mx; box[3].vy = mny; box[3].vz = wy;
        box[4].vx = mn; box[4].vy = my;  box[4].vz = wz;
        box[5].vx = mx; box[5].vy = my;  box[5].vz = wz;
        box[6].vx = mn; box[6].vy = my;  box[6].vz = wy;
        box[7].vx = mx; box[7].vy = my;  box[7].vz = wy;"""
_BOXV = """        box[0].vx = mn; box[0].vy = mny; box[0].vz = wz;
        box[1].vx = mx; box[1].vy = mny; box[1].vz = wz;
        box[2].vx = mn; box[2].vy = mny; box[2].vz = wv;
        box[3].vx = mx; box[3].vy = mny; box[3].vz = wv;
        box[4].vx = mn; box[4].vy = my;  box[4].vz = wz;
        box[5].vx = mx; box[5].vy = my;  box[5].vz = wz;
        box[6].vx = mn; box[6].vy = my;  box[6].vz = wv;
        box[7].vx = mx; box[7].vy = my;  box[7].vz = wv;"""
L['wv_pre'] = [("    u32 wx, wy, wz;", "    u32 wx, wy, wz, wv;"),
               ("        wz = part->zz;\n        mid", "        wz = part->zz;\n        wv = wz >> 16;\n        mid"),
               (_BOXW, _BOXV)]
L['wv_post'] = [("    u32 wx, wy, wz;", "    u32 wx, wy, wz, wv;"),
                (_BOXW, "        wv = wz >> 16;\n" + _BOXV)]
L['wy_pre'] = [("        wz = part->zz;\n        mid", "        wz = part->zz;\n        mid"),
               (_BOXW, _BOXW.replace("        wy = wz >> 16;\n", ""))]

# ---- prologue: the BANKED family idiom (src/ov_SC02_004 func_8017C294) ----
#      s32 arrays + (void *) casts: the address expands STRAIGHT into $a0, so the
#      intervening call invalidates cse's entry and the second use is re-materialised.
L['proto_void'] = [
 ("""    extern void func_8004974C(MATRIX2 *, MATRIX2 *);
    extern void ReadRotMatrix(MATRIX2 *);
    extern void PushMatrix(void);
    extern void PopMatrix(void);
    extern void ApplyMatrixSV(MATRIX2 *, SVECTOR2 *, SVECTOR2 *);""",
  """    extern void func_8004974C(void *, void *);
    extern void ReadRotMatrix(void *);
    extern void PushMatrix(void);
    extern void PopMatrix(void);
    extern void ApplyMatrixSV(void *, void *, void *);"""),
 ("""    SVECTOR2 org;
    SVECTOR2 hv;
    MATRIX2 rot;
    MATRIX2 inv;
    SVECTOR2 dv;""",
  """    u16 org[4];
    s16 hv[4];
    s32 rot[8];
    s32 inv[8];
    s16 dv[4];"""),
 ("""    org.vx = 0;
    org.vy = 0;
    org.vz = 0;
    ReadRotMatrix(&rot);
    PushMatrix();
    dv.vx = org.vx - rot.t[0];
    dv.vy = org.vy - rot.t[1];
    dv.vz = org.vz - rot.t[2];
    func_8004974C(&rot, &inv);
    ApplyMatrixSV(&inv, &dv, &hv);
    PopMatrix();

    hmid = hv.vy + 0x100;
    hhi = hv.vy + 0x280;
    hv.vy = hv.vy - 0x180;""",
  """    org[0] = 0;
    org[1] = 0;
    org[2] = 0;
    ReadRotMatrix((void *)rot);
    PushMatrix();
    dv[0] = (s16)(org[0] - *(s32 *)((u8 *)rot + 0x14));
    dv[1] = (s16)(org[1] - *(s32 *)((u8 *)rot + 0x18));
    dv[2] = (s16)(org[2] - *(s32 *)((u8 *)rot + 0x1C));
    func_8004974C((void *)rot, (void *)inv);
    ApplyMatrixSV((void *)inv, (void *)dv, (void *)hv);
    PopMatrix();

    hmid = hv[1] + 0x100;
    hhi = hv[1] + 0x280;
    hv[1] = hv[1] - 0x180;"""),
 ("        if (mid < hv.vy) continue;", "        if (mid < hv[1]) continue;"),
]

# ---- prologue spelling probes (on top of proto_void) ---------------------
L['pro_arrayidx'] = [
 ("""    dv[0] = (s16)(org[0] - *(s32 *)((u8 *)rot + 0x14));
    dv[1] = (s16)(org[1] - *(s32 *)((u8 *)rot + 0x18));
    dv[2] = (s16)(org[2] - *(s32 *)((u8 *)rot + 0x1C));""",
  """    dv[0] = (s16)(org[0] - rot[5]);
    dv[1] = (s16)(org[1] - rot[6]);
    dv[2] = (s16)(org[2] - rot[7]);""")]
L['pro_nocast'] = [("    ReadRotMatrix((void *)rot);", "    ReadRotMatrix(rot);"),
                   ("    func_8004974C((void *)rot, (void *)inv);", "    func_8004974C(rot, inv);"),
                   ("    ApplyMatrixSV((void *)inv, (void *)dv, (void *)hv);", "    ApplyMatrixSV(inv, dv, hv);")]
L['pro_elem0'] = [("    ReadRotMatrix((void *)rot);", "    ReadRotMatrix((void *)&rot[0]);"),
                  ("    func_8004974C((void *)rot, (void *)inv);", "    func_8004974C((void *)&rot[0], (void *)&inv[0]);"),
                  ("    ApplyMatrixSV((void *)inv, (void *)dv, (void *)hv);", "    ApplyMatrixSV((void *)&inv[0], (void *)&dv[0], (void *)&hv[0]);")]
L['pro_dvlate'] = [
 ("""    dv[0] = (s16)(org[0] - *(s32 *)((u8 *)rot + 0x14));
    dv[1] = (s16)(org[1] - *(s32 *)((u8 *)rot + 0x18));
    dv[2] = (s16)(org[2] - *(s32 *)((u8 *)rot + 0x1C));
    func_8004974C((void *)rot, (void *)inv);""",
  """    func_8004974C((void *)rot, (void *)inv);
    dv[0] = (s16)(org[0] - *(s32 *)((u8 *)rot + 0x14));
    dv[1] = (s16)(org[1] - *(s32 *)((u8 *)rot + 0x18));
    dv[2] = (s16)(org[2] - *(s32 *)((u8 *)rot + 0x1C));""")]
L['pro_nested'] = [
 ("""    u16 org[4];
    s16 hv[4];
    s32 rot[8];
    s32 inv[8];
    s16 dv[4];""", "    u16 org[4];\n    s16 hv[4];"),
 ("""    org[0] = 0;
    org[1] = 0;
    org[2] = 0;
    ReadRotMatrix((void *)rot);""",
  """    org[0] = 0;
    org[1] = 0;
    org[2] = 0;
    {
    s32 rot[8];
    s32 inv[8];
    s16 dv[4];
    ReadRotMatrix((void *)rot);"""),
 ("    PopMatrix();\n", "    PopMatrix();\n    }\n")]

_CUR = '                if (!(hhi < mid)) { mnc = hmid; __asm__ volatile ("" : : "r" (mnc)); }'
L['d_ge'] = [(_CUR, '                if (hhi >= mid) { mnc = hmid; __asm__ volatile ("" : : "r" (mnc)); }')]
L['d_out'] = [(_CUR, '                if (!(hhi < mid)) mnc = hmid;\n                __asm__ volatile ("" : : "r" (mnc));')]
L['d_mxc'] = [(_CUR, '                if (!(hhi < mid)) { mxc = hmid; __asm__ volatile ("" : : "r" (mxc)); }')]
L['d_t32'] = [(_CUR, '                if (!(hhi < mid)) { t32 = hmid; __asm__ volatile ("" : : "r" (t32)); }')]
L['d_hmid'] = [(_CUR, '                if (!(hhi < mid)) { mnc = hmid; __asm__ volatile ("" : : "r" (hmid)); }')]
L['d_xmn1'] = [(_CUR, '                if (!(hhi < mid)) { xmn1 = hmid; __asm__ volatile ("" : : "r" (xmn1)); }')]
L['d_mem'] = [(_CUR, '                if (!(hhi < mid)) { mnc = hmid; __asm__ volatile ("" : : "r" (mnc) : "memory"); }')]
L['d_mid2'] = [(_CUR, '                if (!(hhi < mid)) { mnc = hmid; __asm__ volatile ("" : : "r" (mnc), "r" (mid)); }')]

L['pro_bar1'] = [("    func_8004974C((void *)rot, (void *)inv);",
                  "    __asm__ volatile (\"\");\n    func_8004974C((void *)rot, (void *)inv);")]
L['pro_bar2'] = [("    func_8004974C((void *)rot, (void *)inv);",
                  "    __asm__ volatile (\"\" ::: \"memory\");\n    func_8004974C((void *)rot, (void *)inv);")]
L['pro_bar3'] = [("    ApplyMatrixSV((void *)inv, (void *)dv, (void *)hv);",
                  "    __asm__ volatile (\"\");\n    ApplyMatrixSV((void *)inv, (void *)dv, (void *)hv);")]
L['pro_ptr'] = [("    ReadRotMatrix((void *)rot);", "    rp = (void *)rot;\n    ReadRotMatrix(rp);"),
                ("    func_8004974C((void *)rot, (void *)inv);", "    rp = (void *)rot;\n    ip = (void *)inv;\n    func_8004974C(rp, ip);"),
                ("    ApplyMatrixSV((void *)inv, (void *)dv, (void *)hv);", "    ip = (void *)inv;\n    ApplyMatrixSV(ip, (void *)dv, (void *)hv);"),
                ("    s16 dv[4];", "    s16 dv[4];\n    void *rp; void *ip;")]
L['pro_ohv'] = [("""    u16 org[4];
    s16 hv[4];""", "    s16 ohv[8];"),
                ("    org[0] = 0;\n    org[1] = 0;\n    org[2] = 0;", "    ohv[0] = 0;\n    ohv[1] = 0;\n    ohv[2] = 0;"),
                ("    dv[0] = (s16)(org[0] - *(s32 *)((u8 *)rot + 0x14));", "    dv[0] = (s16)(ohv[0] - *(s32 *)((u8 *)rot + 0x14));"),
                ("    dv[1] = (s16)(org[1] - *(s32 *)((u8 *)rot + 0x18));", "    dv[1] = (s16)(ohv[1] - *(s32 *)((u8 *)rot + 0x18));"),
                ("    dv[2] = (s16)(org[2] - *(s32 *)((u8 *)rot + 0x1C));", "    dv[2] = (s16)(ohv[2] - *(s32 *)((u8 *)rot + 0x1C));"),
                ("    ApplyMatrixSV((void *)inv, (void *)dv, (void *)hv);", "    ApplyMatrixSV((void *)inv, (void *)dv, (void *)&ohv[4]);"),
                ("    hmid = hv[1] + 0x100;\n    hhi = hv[1] + 0x280;\n    hv[1] = hv[1] - 0x180;",
                 "    hmid = ohv[5] + 0x100;\n    hhi = ohv[5] + 0x280;\n    ohv[5] = ohv[5] - 0x180;"),
                ("        if (mid < hv[1]) continue;", "        if (mid < ohv[5]) continue;")]

# ---- prologue: put &rot/&inv STRAIGHT into the arg reg (c294's shape) ----
L['pin_rd'] = [("    ReadRotMatrix((void *)rot);",
 """    { register void *_p0 __asm__("$4"); _p0 = (void *)rot; ReadRotMatrix(_p0); }""")]
L['pin_tr'] = [("    func_8004974C((void *)rot, (void *)inv);",
 """    { register void *_p0 __asm__("$4"); register void *_p1 __asm__("$5");
      _p0 = (void *)rot; _p1 = (void *)inv; func_8004974C(_p0, _p1); }""")]
L['pin_ap'] = [("    ApplyMatrixSV((void *)inv, (void *)dv, (void *)hv);",
 """    { register void *_p0 __asm__("$4"); _p0 = (void *)inv; ApplyMatrixSV(_p0, (void *)dv, (void *)hv); }""")]
L['pin_ap2'] = [("    ApplyMatrixSV((void *)inv, (void *)dv, (void *)hv);",
 """    { register void *_p0 __asm__("$4"); register void *_p1 __asm__("$5"); register void *_p2 __asm__("$6");
      _p0 = (void *)inv; _p1 = (void *)dv; _p2 = (void *)hv; ApplyMatrixSV(_p0, _p1, _p2); }""")]

L['pin_fn'] = [("    s32 cd;", "    s32 cd;\n    register void *_p0 __asm__(\"$4\");\n    register void *_p1 __asm__(\"$5\");"),
               ("    ReadRotMatrix(&rot);", "    _p0 = (void *)&rot;\n    ReadRotMatrix((MATRIX2 *)_p0);"),
               ("    func_8004974C(&rot, &inv);", "    _p0 = (void *)&rot;\n    _p1 = (void *)&inv;\n    func_8004974C((MATRIX2 *)_p0, (MATRIX2 *)_p1);"),
               ("    ApplyMatrixSV(&inv, &dv, &hv);", "    _p0 = (void *)&inv;\n    ApplyMatrixSV((MATRIX2 *)_p0, &dv, &hv);")]
L['pin_fn2'] = [("    s32 cd;", "    s32 cd;\n    register MATRIX2 *_p0 __asm__(\"$4\");\n    register MATRIX2 *_p1 __asm__(\"$5\");"),
               ("    ReadRotMatrix(&rot);", "    _p0 = &rot;\n    ReadRotMatrix(_p0);"),
               ("    func_8004974C(&rot, &inv);", "    _p0 = &rot;\n    _p1 = &inv;\n    func_8004974C(_p0, _p1);"),
               ("    ApplyMatrixSV(&inv, &dv, &hv);", "    _p0 = &inv;\n    ApplyMatrixSV(_p0, &dv, &hv);")]

L['bb_goto'] = [("    func_8004974C(&rot, &inv);",
                 "    goto _l1;\n_l1:\n    func_8004974C(&rot, &inv);")]
L['bb_goto2'] = [("    func_8004974C(&rot, &inv);",
                  "    goto _l1;\n_l1:\n    func_8004974C(&rot, &inv);"),
                 ("    ApplyMatrixSV(&inv, &dv, &hv);",
                  "    goto _l2;\n_l2:\n    ApplyMatrixSV(&inv, &dv, &hv);")]

_C2 = '                if (!(hhi < mid)) { mnc = hmid; __asm__ volatile ("" : : "r" (mnc)); }'
L['e_ge']   = [(_C2, '                if (hhi >= mid) { mnc = hmid; __asm__ volatile ("" : : "r" (mnc)); }')]
L['e_out']  = [(_C2, '                if (!(hhi < mid)) mnc = hmid;\n                __asm__ volatile ("" : : "r" (mnc));')]
L['e_mxc']  = [(_C2, '                if (!(hhi < mid)) { mxc = hmid; __asm__ volatile ("" : : "r" (mxc)); }')]
L['e_t32']  = [(_C2, '                if (!(hhi < mid)) { t32 = hmid; __asm__ volatile ("" : : "r" (t32)); }')]
L['e_x1']   = [(_C2, '                if (!(hhi < mid)) { xmn1 = hmid; __asm__ volatile ("" : : "r" (xmn1)); }')]
L['e_x2']   = [(_C2, '                if (!(hhi < mid)) { xmx1 = hmid; __asm__ volatile ("" : : "r" (xmx1)); }')]
L['e_hmid'] = [(_C2, '                if (!(hhi < mid)) { mnc = hmid; __asm__ volatile ("" : : "r" (hmid)); }')]
L['e_both'] = [(_C2, '                if (!(hhi < mid)) { mnc = hmid; __asm__ volatile ("" : : "r" (mnc), "r" (mid)); }')]
L['e_mid']  = [(_C2, '                if (!(hhi < mid)) { mnc = hmid; __asm__ volatile ("" : : "r" (mid)); }')]
L['e_tern'] = [(_C2, '                mnc = (hhi < mid) ? mnc : hmid;\n                __asm__ volatile ("" : : "r" (mnc));')]
L['e_pre']  = [(_C2, '                __asm__ volatile ("" : : "r" (mid));\n' + _C2)]
L['e_mnc2'] = [(_C2, '                if (!(hhi < mid)) { mnc = hmid; __asm__ volatile ("" : "=r" (mnc) : "0" (mnc)); }')]

_C3 = '                if (!(hhi < mid)) { mnc = hmid; __asm__ volatile ("" : : "r" (mnc)); }'
L['f_pin3'] = [(_C3, '                { register s32 _m2 __asm__("$3"); _m2 = mid;\n                  if (!(hhi < _m2)) { mnc = hmid; __asm__ volatile ("" : : "r" (mnc)); } }')]
L['f_pin3b'] = [(_C3, '                { register s32 _m2 __asm__("$3"); _m2 = mid;\n                  if (!(hhi < _m2)) mnc = hmid; __asm__ volatile ("" : : "r" (mnc)); }')]
L['f_tmp'] = [(_C3, '                { s32 _m2 = mid;\n                  if (!(hhi < _m2)) { mnc = hmid; __asm__ volatile ("" : : "r" (mnc)); } }')]
L['f_le'] = [(_C3, '                if (mid <= hhi) { mnc = hmid; __asm__ volatile ("" : : "r" (mnc)); }')]
L['f_ngt'] = [(_C3, '                if (!(mid > hhi)) { mnc = hmid; __asm__ volatile ("" : : "r" (mnc)); }')]
L['f_t32'] = [(_C3, '                t32 = mid;\n                if (!(hhi < t32)) { mnc = hmid; __asm__ volatile ("" : : "r" (mnc)); }')]
L['f_x'] = [(_C3, '                xa32 = mid;\n                if (!(hhi < xa32)) { mnc = hmid; __asm__ volatile ("" : : "r" (mnc)); }')]

def main():
    base, out = sys.argv[1], sys.argv[2]
    src = open(base).read()
    for name in sys.argv[3:]:
        if name not in L:
            sys.exit('unknown lever: %s' % name)
        for old, new in L[name]:
            n = src.count(old)
            if n == 0:
                sys.exit('lever %s: pattern NOT FOUND:\n%r' % (name, old[:120]))
            src = src.replace(old, new)
    open(out, 'w').write(HDR + MACROS + src)
    print('OK %s -> %s (%s)' % (base, out, ','.join(sys.argv[3:]) or 'bare'))

main()
