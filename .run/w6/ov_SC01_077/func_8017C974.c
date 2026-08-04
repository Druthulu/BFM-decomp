// func_8017C974 — grid-tiled TMD model renderer (947 ins, jr-function).
// Sibling of the banked func_8017C294 (ov_SC06_008_jr_8017C294.c): identical inner
// per-prim RTPT/cull/switch, but the outer loop walks a 64-wide cell grid instead of
// a part array. GTE ops are verbatim PsyQ inline_c.h macro bodies.

#define gte_ldv0_C974(r0) __asm__ volatile (      \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_ldv3_C974(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldv3c_C974(r0) __asm__ volatile (     \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 8( %0 );"                          \
    "lwc2 $3, 12( %0 );"                         \
    "lwc2 $4, 16( %0 );"                         \
    "lwc2 $5, 20( %0 )"                          \
    :                                            \
    : "r"( r0 ) )

#define gte_rtps_C974() __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt_C974() __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip_C974() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz3_C974() __asm__ volatile ("nop;nop;avsz3")
#define gte_avsz4_C974() __asm__ volatile ("nop;nop;avsz4")

#define gte_stsxy_C974(r0) __asm__ volatile (     \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3_C974(r0, r1, r2) __asm__ volatile ( \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 0( %1 );"                         \
    "swc2 $14, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_stsxy3c_C974(r0) __asm__ volatile (   \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 4( %0 );"                         \
    "swc2 $14, 8( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3_f3_C974(r0) __asm__ volatile ( \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 12( %0 );"                        \
    "swc2 $14, 16( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsz3_C974(r0, r1, r2) __asm__ volatile ( \
    "swc2 $17, 0( %0 );"                         \
    "swc2 $18, 0( %1 );"                         \
    "swc2 $19, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_stsz4_C974(r0, r1, r2, r3) __asm__ volatile ( \
    "swc2 $16, 0( %0 );"                         \
    "swc2 $17, 0( %1 );"                         \
    "swc2 $18, 0( %2 );"                         \
    "swc2 $19, 0( %3 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ), "r"( r3 ) )

#define gte_stflg_C974(r0) __asm__ volatile (     \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stopz_C974(r0) __asm__ volatile (     \
    "swc2 $24, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

void func_8017C974(s32 arg0)
{
    typedef struct { u32 w0, w1, w2; } Prim;
    typedef struct { u8 *vtx; u32 pad4; u32 xx, yy, zz; Prim *prim, *pend; } Cell;

    extern s32 func_800491EC(void);
    extern void func_800547D8(s32, MATRIX2 *);
    extern void func_80052E38(MATRIX2 *);
    extern void func_8017C294(void *, void *, s32);
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern s16 D_801DA9A0;

    DVECTOR2 rect[2];
    DVECTOR2 tmpxy[4];
    SVECTOR2 box[8];
    SVECTOR2 sxy[8];
    MATRIX2 mtx;
    struct { long flag, opz, sz0, sz1, sz2, sz3; } g;

    s32 xmn, xmx, ymn, ymx;
    s32 idx;
    s32 x, y;
    Cell **rowp, **p;
    Cell *obj;
    register Prim *prim __asm__("$13"); Prim *pend;
    u8 *pkt;
    u32 ot;
    u8 *vtx;
    u8 *va, *vb, *vc, *vd;
    u32 w, code;
    u32 wx, wy, wz;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 mnc, mxc;
    s32 my, mny, mx, mn;
    u32 bxlo, bxhi, bylo, byhi, bzlo, bzhi;

    func_800491EC();
    func_800547D8(arg0 + 0x10, &mtx);
    func_80052E38(&mtx);
    func_8017C294(&D_801DA9A0, rect, *(s32 *)(arg0 + 0x60));

    pkt = D_800A5E60;
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];

    xmn = (rect[0].vx + 0x4000) / 512;
    xmx = (rect[0].vx + rect[1].vx + 0x4000) / 512 + 2;
    xmn = (xmn < 0) ? 0 : ((xmn > 0x3F) ? 0x3F : xmn);
    xmx = (xmx < 0) ? 0 : ((xmx > 0x3F) ? 0x3F : xmx);

    ymn = (rect[0].vy + 0x4000) / 512 - 1;
    ymx = (rect[0].vy + rect[1].vy + 0x4000) / 512 + 2;
    ymn = (ymn < 0) ? 0 : ((ymn > 0x3F) ? 0x3F : ymn);
    ymx = (ymx < 0) ? 0 : ((ymx > 0x3F) ? 0x3F : ymx);

    idx = ymn * 64 + xmn;
    rowp = *(Cell ***)(arg0 + 0xC) + idx;

    for (y = ymn; y < ymx; y++, rowp += 64) {
        for (x = xmn, p = rowp; x < xmx; x++, p++) {
            obj = *p;
            if (obj == 0) continue;

            wx = obj->xx;
            wy = obj->yy;
            wz = obj->zz;
            bxlo = wx & 0xFFFF; bxhi = wx >> 16;
            bylo = wy & 0xFFFF; byhi = wy >> 16;
            bzlo = wz & 0xFFFF; bzhi = wz >> 16;
            box[0].vx = bxlo; box[0].vy = bylo; box[0].vz = bzlo;
            box[1].vx = bxhi; box[1].vy = bylo; box[1].vz = bzlo;
            box[2].vx = bxlo; box[2].vy = bylo; box[2].vz = bzhi;
            box[3].vx = bxhi; box[3].vy = bylo; box[3].vz = bzhi;
            box[4].vx = bxlo; box[4].vy = byhi; box[4].vz = bzlo;
            box[5].vx = bxhi; box[5].vy = byhi; box[5].vz = bzlo;
            box[6].vx = bxlo; box[6].vy = byhi; box[6].vz = bzhi;
            box[7].vx = bxhi; box[7].vy = byhi; box[7].vz = bzhi;

            gte_ldv3c_C974(&box[0]);
            gte_rtpt_C974();
            gte_stsxy3_C974(&sxy[0], &sxy[1], &sxy[2]);
            gte_ldv0_C974(&box[3]);
            gte_rtps_C974();
            gte_stsxy_C974(&sxy[3]);
            gte_ldv3c_C974(&box[4]);
            gte_rtpt_C974();
            gte_stsxy3_C974(&sxy[4], &sxy[5], &sxy[6]);
            gte_ldv0_C974(&box[7]);
            gte_rtps_C974();
            gte_stsxy_C974(&sxy[7]);

            xa32 = sxy[0].vx;
            xb32 = sxy[1].vx;
            if (xb32 < xa32) { xmx1 = xa32; xmn1 = xb32; } else { xmn1 = xa32; xmx1 = xb32; }
            t32 = sxy[2].vx;
            if (xmx1 < t32) xmx1 = t32; else if (t32 < xmn1) xmn1 = t32;
            t32 = sxy[3].vx;
            if (xmx1 < t32) xmx1 = t32; else if (t32 < xmn1) xmn1 = t32;
            xa32 = sxy[4].vx;
            xb32 = sxy[5].vx;
            if (xb32 < xa32) { xmx2 = xa32; xmn2 = xb32; } else { xmn2 = xa32; xmx2 = xb32; }
            t32 = sxy[6].vx;
            if (xmx2 < t32) xmx2 = t32; else if (t32 < xmn2) xmn2 = t32;
            t32 = sxy[7].vx;
            if (xmx2 < t32) xmx2 = t32; else if (t32 < xmn2) xmn2 = t32;
            mnc = xmn1;
            if (xmn2 < xmn1) mnc = xmn2;
            mxc = xmx1;
            if (mxc < xmx2) mxc = xmx2;
            if (mxc >= -0xA0 && mnc < 0xA1) {
                xa32 = sxy[0].vy;
                xb32 = sxy[1].vy;
                if (xb32 < xa32) { xmx1 = xa32; xmn1 = xb32; } else { xmn1 = xa32; xmx1 = xb32; }
                t32 = sxy[2].vy;
                if (xmx1 < t32) xmx1 = t32; else if (t32 < xmn1) xmn1 = t32;
                t32 = sxy[3].vy;
                if (xmx1 < t32) xmx1 = t32; else if (t32 < xmn1) xmn1 = t32;
                xa32 = sxy[4].vy;
                xb32 = sxy[5].vy;
                if (xb32 < xa32) { xmx2 = xa32; xmn2 = xb32; } else { xmn2 = xa32; xmx2 = xb32; }
                t32 = sxy[6].vy;
                if (xmx2 < t32) xmx2 = t32; else if (t32 < xmn2) xmn2 = t32;
                t32 = sxy[7].vy;
                if (xmx2 < t32) xmx2 = t32; else if (t32 < xmn2) xmn2 = t32;
                mnc = xmn1;
                if (xmn2 < xmn1) mnc = xmn2;
                mxc = xmx1;
                if (mxc < xmx2) mxc = xmx2;
                if (mxc >= -0x78 && mnc < 0x79) {
                    prim = obj->prim;
                    pend = obj->pend;
                    vtx = obj->vtx;
                    for (; prim < pend; prim++) {
                        w = prim->w1;
                        va = vtx + (w & 0xFFFF);
                        vb = vtx + (w >> 16);
                        w = prim->w2;
                        vc = vtx + (w & 0xFFFF);
                        w = w >> 16;
                        gte_ldv3_C974(va, vb, vc);
                        gte_rtpt_C974();
                        gte_stflg_C974(&g.flag);
                        if (!(g.flag & 0x7F85E000)) {
                            gte_nclip_C974();
                            code = w & 0xF;
                            vd = vtx + ((w & 0xFFF0) >> 1);
                            gte_stopz_C974(&g.opz);
                            if (g.opz > 0) {
                                switch (code) {
                                case 4:
                                case 5:
                                    gte_stsxy3_f3_C974(pkt);
                                    gte_stsz3_C974(&g.sz0, &g.sz1, &g.sz2);
                                    if (((PolyFT3 *)pkt)->x0 > ((PolyFT3 *)pkt)->x1) {
                                        mx = ((PolyFT3 *)pkt)->x0;
                                        mn = ((PolyFT3 *)pkt)->x1;
                                    } else {
                                        mn = ((PolyFT3 *)pkt)->x0;
                                        mx = ((PolyFT3 *)pkt)->x1;
                                    }
                                    if (((PolyFT3 *)pkt)->x2 > mx) mx = ((PolyFT3 *)pkt)->x2;
                                    else if (((PolyFT3 *)pkt)->x2 < mn) mn = ((PolyFT3 *)pkt)->x2;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (((PolyFT3 *)pkt)->y0 > ((PolyFT3 *)pkt)->y1) {
                                            my = ((PolyFT3 *)pkt)->y0;
                                            mny = ((PolyFT3 *)pkt)->y1;
                                        } else {
                                            mny = ((PolyFT3 *)pkt)->y0;
                                            my = ((PolyFT3 *)pkt)->y1;
                                        }
                                        if (((PolyFT3 *)pkt)->y2 > my) my = ((PolyFT3 *)pkt)->y2;
                                        else if (((PolyFT3 *)pkt)->y2 < mny) mny = ((PolyFT3 *)pkt)->y2;
                                        if (my >= -0x78 && mny < 0x79) {
                                            s32 za;
                                            u32 *otp;
                                            if (g.sz0 > g.sz1) {
                                                za = g.sz0;
                                                if (za < g.sz2) za = g.sz2;
                                            } else {
                                                za = g.sz1;
                                                if (za < g.sz2) za = g.sz2;
                                            }
                                            g.opz = za;
                                            if (code != 4) g.opz = za + 0x200;
                                            ((PolyF3 *)pkt)->rgbc = prim->w0;
                                            otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                            *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x4000000;
                                            *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                            pkt += 0x14;
                                        }
                                    }
                                    break;
                                case 6:
                                case 7:
                                    gte_stsxy3c_C974(&tmpxy[0]);
                                    gte_stsz3_C974(&g.sz0, &g.sz1, &g.sz2);
                                    if (tmpxy[0].vx > tmpxy[1].vx) {
                                        mx = tmpxy[0].vx;
                                        mn = tmpxy[1].vx;
                                    } else {
                                        mn = tmpxy[0].vx;
                                        mx = tmpxy[1].vx;
                                    }
                                    if (tmpxy[2].vx > mx) mx = tmpxy[2].vx;
                                    else if (tmpxy[2].vx < mn) mn = tmpxy[2].vx;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (tmpxy[0].vy > tmpxy[1].vy) {
                                            my = tmpxy[0].vy;
                                            mny = tmpxy[1].vy;
                                        } else {
                                            mny = tmpxy[0].vy;
                                            my = tmpxy[1].vy;
                                        }
                                        if (tmpxy[2].vy > my) my = tmpxy[2].vy;
                                        else if (tmpxy[2].vy < mny) mny = tmpxy[2].vy;
                                        if (my >= -0x78 && mny < 0x79) {
                                            s32 za;
                                            u32 *otp;
                                            u32 *tp;
                                            gte_avsz3_C974();
                                            if (g.sz0 > g.sz1) {
                                                za = g.sz0;
                                                if (za < g.sz2) za = g.sz2;
                                            } else {
                                                za = g.sz1;
                                                if (za < g.sz2) za = g.sz2;
                                            }
                                            g.opz = za;
                                            if (code != 6) g.opz = za + 0x200;
                                            *(u32 *)&((PolyFT3 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                            *(u32 *)&((PolyFT3 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                            *(u32 *)&((PolyFT3 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                            tp = (u32 *)prim->w0;
                                            ((PolyFT3 *)pkt)->rgbc = tp[0];
                                            ((PolyFT3 *)pkt)->uvc0 = tp[1];
                                            ((PolyFT3 *)pkt)->uvp1 = tp[2];
                                            ((PolyFT3 *)pkt)->uv2 = tp[3];
                                            otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                            *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x7000000;
                                            *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                            pkt += 0x20;
                                        }
                                    }
                                    break;
                                case 0:
                                case 1:
                                    gte_stsxy3_f3_C974(pkt);
                                    gte_ldv0_C974(vd);
                                    gte_rtps_C974();
                                    if (((PolyF4 *)pkt)->x0 > ((PolyF4 *)pkt)->x1) {
                                        mx = ((PolyF4 *)pkt)->x0;
                                        mn = ((PolyF4 *)pkt)->x1;
                                    } else {
                                        mn = ((PolyF4 *)pkt)->x0;
                                        mx = ((PolyF4 *)pkt)->x1;
                                    }
                                    if (((PolyF4 *)pkt)->x2 > mx) mx = ((PolyF4 *)pkt)->x2;
                                    else if (((PolyF4 *)pkt)->x2 < mn) mn = ((PolyF4 *)pkt)->x2;
                                    if (((PolyF4 *)pkt)->y0 > ((PolyF4 *)pkt)->y1) {
                                        my = ((PolyF4 *)pkt)->y0;
                                        mny = ((PolyF4 *)pkt)->y1;
                                    } else {
                                        mny = ((PolyF4 *)pkt)->y0;
                                        my = ((PolyF4 *)pkt)->y1;
                                    }
                                    if (((PolyF4 *)pkt)->y2 > my) my = ((PolyF4 *)pkt)->y2;
                                    else if (((PolyF4 *)pkt)->y2 < mny) mny = ((PolyF4 *)pkt)->y2;
                                    gte_stflg_C974(&g.flag);
                                    if (!(g.flag & 0x7F85E000)) {
                                        gte_stsz4_C974(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
                                        gte_stsxy_C974((long *)&((PolyF4 *)pkt)->x3);
                                        if (((PolyF4 *)pkt)->x3 < mn) mn = ((PolyF4 *)pkt)->x3;
                                        else if (mx < ((PolyF4 *)pkt)->x3) mx = ((PolyF4 *)pkt)->x3;
                                        if (mx >= -0xA0 && mn < 0xA1) {
                                            if (((PolyF4 *)pkt)->y3 < mny) mny = ((PolyF4 *)pkt)->y3;
                                            else if (my < ((PolyF4 *)pkt)->y3) my = ((PolyF4 *)pkt)->y3;
                                            if (my >= -0x78 && mny < 0x79) {
                                                s32 za, zb;
                                                u32 *otp;
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;
                                                if (code != 0) g.opz = za + 0x200;
                                                ((PolyF4 *)pkt)->rgbc = prim->w0;
                                                otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x5000000;
                                                *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                pkt += 0x18;
                                            }
                                        }
                                    }
                                    break;
                                case 2:
                                case 3:
                                    gte_stsxy3c_C974(&tmpxy[0]);
                                    gte_ldv0_C974(vd);
                                    gte_rtps_C974();
                                    gte_stflg_C974(&g.flag);
                                    if (!(g.flag & 0x7F85E000)) {
                                        gte_stsxy_C974(&tmpxy[3]);
                                        gte_stsz4_C974(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
                                        if (tmpxy[0].vx > tmpxy[1].vx) {
                                            mx = tmpxy[0].vx;
                                            mn = tmpxy[1].vx;
                                        } else {
                                            mn = tmpxy[0].vx;
                                            mx = tmpxy[1].vx;
                                        }
                                        if (tmpxy[2].vx > mx) mx = tmpxy[2].vx;
                                        else if (tmpxy[2].vx < mn) mn = tmpxy[2].vx;
                                        if (tmpxy[3].vx > mx) mx = tmpxy[3].vx;
                                        else if (tmpxy[3].vx < mn) mn = tmpxy[3].vx;
                                        if (mx >= -0xA0 && mn < 0xA1) {
                                            if (tmpxy[0].vy > tmpxy[1].vy) {
                                                my = tmpxy[0].vy;
                                                mny = tmpxy[1].vy;
                                            } else {
                                                mny = tmpxy[0].vy;
                                                my = tmpxy[1].vy;
                                            }
                                            if (tmpxy[2].vy > my) my = tmpxy[2].vy;
                                            else if (tmpxy[2].vy < mny) mny = tmpxy[2].vy;
                                            if (tmpxy[3].vx > my) my = tmpxy[3].vx;
                                            else if (tmpxy[3].vx < mny) mny = tmpxy[3].vx;
                                            if (my >= -0x78 && mny < 0x79) {
                                                s32 za, zb;
                                                u32 *otp;
                                                u32 *tp;
                                                u32 uvw;
                                                gte_avsz4_C974();
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;
                                                if (code != 2) g.opz = za + 0x200;
                                                *(u32 *)&((PolyFT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((PolyFT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((PolyFT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                *(u32 *)&((PolyFT4 *)pkt)->x3 = *(u32 *)&tmpxy[3];
                                                tp = (u32 *)prim->w0;
                                                ((PolyFT4 *)pkt)->rgbc = tp[0];
                                                ((PolyFT4 *)pkt)->uvc0 = tp[1];
                                                ((PolyFT4 *)pkt)->uvp1 = tp[2];
                                                uvw = tp[3];
                                                ((PolyFT4 *)pkt)->uv2 = uvw;
                                                ((PolyFT4 *)pkt)->uv3 = uvw >> 16;
                                                otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x9000000;
                                                *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                pkt += 0x28;
                                            }
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    D_800A5E60 = pkt;
}
