void func_8017CD9C(s32 arg0)
{
    typedef struct { u32 w0, w1, w2; } Prim;

    extern s32 func_800491EC(void);
    extern void func_800547D8(s32, MATRIX2 *);
    extern void func_80052E38(MATRIX2 *);
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern u8 D_800AF630[];

    DVECTOR2 tmpxy[4];
    SVECTOR2 box[8];
    SVECTOR2 sxy[8];
    MATRIX2 mtx;
    struct { long otz, flag, opz, sz0, sz1, sz2, sz3; } g;

    s32 lim;
    s32 j;
    u32 i;
    u8 *vd;
    u32 ot;
    u8 *pkt;
    s16 x3, z3, y3;
    Prim *prim;
    u32 nprim;
    u8 *vtx;
    s32 nparts;
    Part *part;
    s16 lo0x, hi0x, lo0y, hi0y, lo0z, hi0z;
    s16 lo1x, hi1x, lo1y, hi1y, lo1z, hi1z;
    s16 lo2x, hi2x, lo2y, hi2y, lo2z, hi2z;
    s16 cx0, cy0, cz0, cx1, cy1, cz1, cx2, cy2, cz2;
    s16 r0;
    s16 r1;
    s16 r2;
    s16 r0lo;
    s16 r1lo;
    s16 r2lo;
    u8 *va, *vb, *vc;
    u32 w; s32 code;
    u32 vw, vzw;
    u32 wx, wy, wz;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 mnc, mxc;
    s16 my, mny, mx, mn;
    u8 *base;
    s32 f0, f1, f2;
    s16 x0, y0, z0, x1, y1, z1, x2, y2, z2;
    s32 a0v, a1v, a2v;
    s32 d;
    s32 c0, c1, c2, c3;
    u32 *tp;
    u32 uvw;
    u32 cb;
    u32 rgbw;

    base = D_800AF630;
    lim = func_800491EC() + *(s32 *)(arg0 + 0x64);
    func_800547D8(arg0 + 0x10, &mtx);
    func_80052E38(&mtx);

    r2lo = 0;
    r1lo = 0;
    r0lo = 0;
    r2 = 0;
    r1 = 0;
    r0 = 0;

    if (D_801B9B00) {
        cx0 = D_801B9B04;
        cy0 = D_801B9B06;
        r0lo = D_801B9B0C - 0x80;
        r0 = D_801B9B0C;
        cz0 = D_801B9B08;
    } else {
        cz0 = 0x6000;
        cy0 = 0x6000;
        cx0 = 0x6000;
    }
    if (D_801B9B1C) {
        cx1 = D_801B9B20;
        cy1 = D_801B9B22;
        r1 = D_801B9B28;
        r1lo = D_801B9B28 - 0x80;
        cz1 = D_801B9B24;
    } else {
        cz1 = 0x6000;
        cy1 = 0x6000;
        cx1 = 0x6000;
    }
    if (D_801B9B38) {
        cx2 = D_801B9B3C;
        cy2 = D_801B9B3E;
        r2 = D_801B9B44;
        r2lo = D_801B9B44 - 0x80;
        cz2 = D_801B9B40;
    } else {
        cz2 = 0x6000;
        cy2 = 0x6000;
        cx2 = 0x6000;
    }

    lo0x = cx0 - r0;  hi0x = cx0 + r0;
    lo0y = cy0 - r0;  hi0y = cy0 + r0;
    lo0z = cz0 - r0;  hi0z = cz0 + r0;
    lo1x = cx1 - r1;  hi1x = cx1 + r1;
    lo1y = cy1 - r1;  hi1y = cy1 + r1;
    lo1z = cz1 - r1;  hi1z = cz1 + r1;
    lo2x = cx2 - r2;  hi2x = cx2 + r2;
    lo2y = cy2 - r2;  hi2y = cy2 + r2;
    lo2z = cz2 - r2;  hi2z = cz2 + r2;

    pkt = D_800A5E60;
    part = *(Part **)(arg0 + 0xC);
    nparts = *(s32 *)(*(s32 *)(arg0 + 8) + 8);
    vtx = *(u8 **)(*(s32 *)(arg0 + 8) + 0x10);
    ot = (u32)&D_800A6610[(*(u16 *)(base + 0xA3D2)) << 14];

    for (j = 0; j < nparts; j++, part++) {
        wx = part->xx;
        mn = wx;
        mx = wx >> 16;
        wy = part->yy;
        mny = wy;
        my = wy >> 16;
        wz = part->zz;
        box[0].vx = mn; box[0].vy = mny;
        box[1].vx = mx; box[1].vy = mny;
        box[2].vx = mn; box[2].vy = mny;
        box[3].vx = mx; box[3].vy = mny;
        box[4].vx = mn; box[4].vy = my;
        box[5].vx = mx; box[5].vy = my;
        box[6].vx = mn; box[6].vy = my;
        box[7].vx = mx; box[7].vy = my;
        wy = wz >> 16;
        box[0].vz = wz;
        box[1].vz = wz;
        box[4].vz = wz;
        box[5].vz = wz;
        box[2].vz = wy;
        box[3].vz = wy;
        box[6].vz = wy;
        box[7].vz = wy;

        gte_ldv3c(&box[0]);
        gte_rtpt();
        gte_stsxy3(&sxy[0], &sxy[1], &sxy[2]);
        gte_ldv0(&box[3]);
        gte_rtps();
        gte_stsxy(&sxy[3]);
        gte_ldv3c(&box[4]);
        gte_rtpt();
        gte_stsxy3(&sxy[4], &sxy[5], &sxy[6]);
        gte_ldv0(&box[7]);
        gte_rtps();
        gte_stsxy(&sxy[7]);
        gte_stszotz(&g.otz);

        if (lim >= g.otz) {
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
            if ((s16)mxc >= -0xA0 && (s16)mnc < 0xA1) {
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
                if ((s16)mxc >= -0x6E && (s16)mnc < 0x6F) {
                    nprim = part->nprim;
                    prim = (Prim *)part->prim;
                    for (i = 0; i < nprim; i++, prim++) {
                        w = prim->w1;
                        va = vtx + (w & 0xFFFF);
                        vb = vtx + (w >> 16);
                        w = prim->w2;
                        vc = vtx + (w & 0xFFFF);
                        w = w >> 16;
                        gte_ldv3(va, vb, vc);
                        gte_rtpt();
                        gte_stflg(&g.flag);
                        if (!(g.flag & 0x7F85E000)) {
                            gte_nclip();
                            code = w & 7;
                            vd = vtx + (w & 0xFFF8);
                            gte_stopz(&g.opz);
                            if (g.opz > 0) {
                                switch (code) {
                                case 6:
                                case 7:
                                    /* ---------------- TRI (FT3 / GT3) ---------------- */
                                    gte_stsxy3c(&tmpxy[0]);
                                    gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
                                    if (tmpxy[0].vx > tmpxy[1].vx) { mx = tmpxy[0].vx; mn = tmpxy[1].vx; }
                                    else { mn = tmpxy[0].vx; mx = tmpxy[1].vx; }
                                    if (tmpxy[2].vx > mx) mx = tmpxy[2].vx;
                                    else if (tmpxy[2].vx < mn) mn = tmpxy[2].vx;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (tmpxy[0].vy > tmpxy[1].vy) { my = tmpxy[0].vy; mny = tmpxy[1].vy; }
                                        else { mny = tmpxy[0].vy; my = tmpxy[1].vy; }
                                        if (tmpxy[2].vy > my) my = tmpxy[2].vy;
                                        else if (tmpxy[2].vy < mny) mny = tmpxy[2].vy;
                                        if (my >= -0x6E && mny < 0x6F) {
                                            s32 za, zb;
                                            __asm__ __volatile__ ("" :: "r" (mny));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus8)
                                            if (g.sz0 > g.sz1) { za = g.sz0; if (za < g.sz2) za = g.sz2; }
                                            else { za = g.sz1; if (za < g.sz2) za = g.sz2; }
                                            g.opz = za;

                                            f2 = 0; f1 = 0; f0 = 0;

                                            vw = *(u32 *)va;
                                            vzw = *(u32 *)(va + 4);
                                            x0 = vw; y0 = vw >> 16; z0 = vzw;
                                            BOXTEST(f0, x0, y0, z0, lo0x, hi0x, lo0y, hi0y, lo0z, hi0z);
                                            BOXTEST(f1, x0, y0, z0, lo1x, hi1x, lo1y, hi1y, lo1z, hi1z);
                                            BOXTEST(f2, x0, y0, z0, lo2x, hi2x, lo2y, hi2y, lo2z, hi2z);
                                            vw = *(u32 *)vb;
                                            vzw = *(u32 *)(vb + 4);
                                            x1 = vw; y1 = vw >> 16; z1 = vzw;
                                            BOXTEST(f0, x1, y1, z1, lo0x, hi0x, lo0y, hi0y, lo0z, hi0z);
                                            BOXTEST(f1, x1, y1, z1, lo1x, hi1x, lo1y, hi1y, lo1z, hi1z);
                                            BOXTEST(f2, x1, y1, z1, lo2x, hi2x, lo2y, hi2y, lo2z, hi2z);
                                            vw = *(u32 *)vc;
                                            vzw = *(u32 *)(vc + 4);
                                            x2 = vw; y2 = vw >> 16; z2 = vzw;
                                            BOXTEST(f0, x2, y2, z2, lo0x, hi0x, lo0y, hi0y, lo0z, hi0z);
                                            BOXTEST(f1, x2, y2, z2, lo1x, hi1x, lo1y, hi1y, lo1z, hi1z);
                                            BOXTEST(f2, x2, y2, z2, lo2x, hi2x, lo2y, hi2y, lo2z, hi2z);

                                            if (f0 | f1 | f2) {
                                            u32 *otp;
                                                ATTEN(a0v, f0, x0, y0, z0, cx0, cy0, cz0, r0, r0lo);
                                                ATTEN(a1v, f1, x0, y0, z0, cx1, cy1, cz1, r1, r1lo);
                                                ATTEN(a2v, f2, x0, y0, z0, cx2, cy2, cz2, r2, r2lo);
                                                CLAMP80(c0, a0v, a1v, a2v);
                                                ATTEN(a0v, f0, x1, y1, z1, cx0, cy0, cz0, r0, r0lo);
                                                ATTEN(a1v, f1, x1, y1, z1, cx1, cy1, cz1, r1, r1lo);
                                                ATTEN(a2v, f2, x1, y1, z1, cx2, cy2, cz2, r2, r2lo);
                                                CLAMP80(c1, a0v, a1v, a2v);
                                                ATTEN(a0v, f0, x2, y2, z2, cx0, cy0, cz0, r0, r0lo);
                                                ATTEN(a1v, f1, x2, y2, z2, cx1, cy1, cz1, r1, r1lo);
                                                ATTEN(a2v, f2, x2, y2, z2, cx2, cy2, cz2, r2, r2lo);
                                                CLAMP80(c2, a0v, a1v, a2v);

                                                *(u32 *)&((PolyGT3 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((PolyGT3 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((PolyGT3 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                tp = (u32 *)prim->w0;
                                                cb = 0x34000000;
                                                rgbw = (c0 | cb) | (c0 << 8) | (c0 << 16);
                                                ((PolyGT3 *)pkt)->rgb0 = rgbw;
                                                rgbw = (c1 | cb) | (c1 << 8) | (c1 << 16);
                                                ((PolyGT3 *)pkt)->rgb1 = rgbw;
                                                rgbw = (c2 | cb) | (c2 << 8) | (c2 << 16);
                                                ((PolyGT3 *)pkt)->rgb2 = rgbw;
                                                ((PolyGT3 *)pkt)->uv0 = tp[1];
                                                ((PolyGT3 *)pkt)->uv1 = tp[2];
                                                ((PolyGT3 *)pkt)->uv2 = tp[3];
                                                otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x9000000;
                                                *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                pkt += 0x28;
                                            } else {
                                            u32 *otp;
                                                *(u32 *)&((PolyFT3 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((PolyFT3 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((PolyFT3 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                tp = (u32 *)prim->w0;
                                                cb = tp[0] & 0xFF000000;
                                                ((PolyFT3 *)pkt)->rgbc = cb;
                                                ((PolyFT3 *)pkt)->uvc0 = tp[1];
                                                ((PolyFT3 *)pkt)->uvp1 = tp[2];
                                                ((PolyFT3 *)pkt)->uv2 = tp[3];
                                                otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x7000000;
                                                *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                pkt += 0x20;
                                            }
                                        }
                                    }
                                    break;
                                case 2:
                                case 3:
                                    /* ---------------- QUAD (FT4 / GT4) ---------------- */
                                    gte_stsxy3c(&tmpxy[0]);
                                    gte_ldv0(vd);
                                    gte_rtps();
                                    if (tmpxy[0].vx > tmpxy[1].vx) { mx = tmpxy[0].vx; mn = tmpxy[1].vx; }
                                    else { mn = tmpxy[0].vx; mx = tmpxy[1].vx; }
                                    if (tmpxy[2].vx > mx) mx = tmpxy[2].vx;
                                    else if (tmpxy[2].vx < mn) mn = tmpxy[2].vx;
                                    if (tmpxy[0].vy > tmpxy[1].vy) { my = tmpxy[0].vy; mny = tmpxy[1].vy; }
                                    else { mny = tmpxy[0].vy; my = tmpxy[1].vy; }
                                    if (tmpxy[2].vy > my) my = tmpxy[2].vy;
                                    else if (tmpxy[2].vy < mny) mny = tmpxy[2].vy;
                                    gte_stflg(&g.flag);
                                    if (!(g.flag & 0x7F85E000)) {
                                        gte_stsz4(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
                                        gte_stsxy((long *)&((PolyFT4 *)pkt)->x3);
                                        if (((PolyFT4 *)pkt)->x3 < mn) mn = ((PolyFT4 *)pkt)->x3;
                                        else if (mx < ((PolyFT4 *)pkt)->x3) mx = ((PolyFT4 *)pkt)->x3;
                                        if (mx >= -0xA0 && mn < 0xA1) {
                                            if (((PolyFT4 *)pkt)->y3 < mny) mny = ((PolyFT4 *)pkt)->y3;
                                            else if (my < ((PolyFT4 *)pkt)->y3) my = ((PolyFT4 *)pkt)->y3;
                                            if (my >= -0x6E && mny < 0x6F) {
                                                s32 za, zb;
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;

                                                f2 = 0; f1 = 0; f0 = 0;

                                                vw = *(u32 *)va;
                                                vzw = *(u32 *)(va + 4);
                                                x0 = vw; y0 = vw >> 16; z0 = vzw;
                                                BOXTEST(f0, x0, y0, z0, lo0x, hi0x, lo0y, hi0y, lo0z, hi0z);
                                                BOXTEST(f1, x0, y0, z0, lo1x, hi1x, lo1y, hi1y, lo1z, hi1z);
                                                BOXTEST(f2, x0, y0, z0, lo2x, hi2x, lo2y, hi2y, lo2z, hi2z);
                                                vw = *(u32 *)vb;
                                                vzw = *(u32 *)(vb + 4);
                                                x1 = vw; y1 = vw >> 16; z1 = vzw;
                                                BOXTEST(f0, x1, y1, z1, lo0x, hi0x, lo0y, hi0y, lo0z, hi0z);
                                                BOXTEST(f1, x1, y1, z1, lo1x, hi1x, lo1y, hi1y, lo1z, hi1z);
                                                BOXTEST(f2, x1, y1, z1, lo2x, hi2x, lo2y, hi2y, lo2z, hi2z);
                                                vw = *(u32 *)vc;
                                                vzw = *(u32 *)(vc + 4);
                                                x2 = vw; y2 = vw >> 16; z2 = vzw;
                                                BOXTEST(f0, x2, y2, z2, lo0x, hi0x, lo0y, hi0y, lo0z, hi0z);
                                                BOXTEST(f1, x2, y2, z2, lo1x, hi1x, lo1y, hi1y, lo1z, hi1z);
                                                BOXTEST(f2, x2, y2, z2, lo2x, hi2x, lo2y, hi2y, lo2z, hi2z);
                                                vw = *(u32 *)vd;
                                                vzw = *(u32 *)(vd + 4);
                                                x3 = vw; y3 = vw >> 16; z3 = vzw;
                                                BOXTEST(f0, x3, y3, z3, lo0x, hi0x, lo0y, hi0y, lo0z, hi0z);
                                                BOXTEST(f1, x3, y3, z3, lo1x, hi1x, lo1y, hi1y, lo1z, hi1z);
                                                BOXTEST(f2, x3, y3, z3, lo2x, hi2x, lo2y, hi2y, lo2z, hi2z);

                                                if (f0 | f1 | f2) {
                                                u32 *otp;
                                                    ATTEN(a0v, f0, x0, y0, z0, cx0, cy0, cz0, r0, r0lo);
                                                    ATTEN(a1v, f1, x0, y0, z0, cx1, cy1, cz1, r1, r1lo);
                                                    ATTEN(a2v, f2, x0, y0, z0, cx2, cy2, cz2, r2, r2lo);
                                                    CLAMP80(c0, a0v, a1v, a2v);
                                                    ATTEN(a0v, f0, x1, y1, z1, cx0, cy0, cz0, r0, r0lo);
                                                    ATTEN(a1v, f1, x1, y1, z1, cx1, cy1, cz1, r1, r1lo);
                                                    ATTEN(a2v, f2, x1, y1, z1, cx2, cy2, cz2, r2, r2lo);
                                                    CLAMP80(c1, a0v, a1v, a2v);
                                                    ATTEN(a0v, f0, x2, y2, z2, cx0, cy0, cz0, r0, r0lo);
                                                    ATTEN(a1v, f1, x2, y2, z2, cx1, cy1, cz1, r1, r1lo);
                                                    ATTEN(a2v, f2, x2, y2, z2, cx2, cy2, cz2, r2, r2lo);
                                                    CLAMP80(c2, a0v, a1v, a2v);
                                                    ATTEN(a0v, f0, x3, y3, z3, cx0, cy0, cz0, r0, r0lo);
                                                    ATTEN(a1v, f1, x3, y3, z3, cx1, cy1, cz1, r1, r1lo);
                                                    ATTEN(a2v, f2, x3, y3, z3, cx2, cy2, cz2, r2, r2lo);
                                                    CLAMP80(c3, a0v, a1v, a2v);

                                                    *(u32 *)&((PolyGT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                    *(u32 *)&((PolyGT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                    *(u32 *)&((PolyGT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                    gte_stsxy((long *)&((PolyGT4 *)pkt)->x3);
                                                    tp = (u32 *)prim->w0;
                                                    cb = 0x3C000000;
                                                    rgbw = (c0 | cb) | (c0 << 8) | (c0 << 16);
                                                    ((PolyGT4 *)pkt)->rgb0 = rgbw;
                                                    rgbw = (c1 | cb) | (c1 << 8) | (c1 << 16);
                                                    ((PolyGT4 *)pkt)->rgb1 = rgbw;
                                                    rgbw = (c2 | cb) | (c2 << 8) | (c2 << 16);
                                                    ((PolyGT4 *)pkt)->rgb2 = rgbw;
                                                    rgbw = (c3 | cb) | (c3 << 8) | (c3 << 16);
                                                    ((PolyGT4 *)pkt)->rgb3 = rgbw;
                                                    ((PolyGT4 *)pkt)->uv0 = tp[1];
                                                    ((PolyGT4 *)pkt)->uv1 = tp[2];
                                                    uvw = tp[3];
                                                    ((PolyGT4 *)pkt)->uv2 = uvw;
                                                    ((PolyGT4 *)pkt)->uv3 = uvw >> 16;
                                                    otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                                    *(u32 *)pkt = (*otp & 0xFFFFFF) | 0xC000000;
                                                    *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                    pkt += 0x34;
                                                } else {
                                                u32 *otp;
                                                    *(u32 *)&((PolyFT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                    *(u32 *)&((PolyFT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                    *(u32 *)&((PolyFT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                    tp = (u32 *)prim->w0;
                                                    cb = tp[0] & 0xFF000000;
                                                    ((PolyFT4 *)pkt)->rgbc = cb;
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
