/* func_8017CDF0 — shared body (overlay slot 0x80128158, h_exact 922320b0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017CDF0(s32 a0, s32 a1, s32 a2)
{

    extern s32 func_800491EC(void);
    extern void func_800547D8(s32, MATRIX2_8017CDF0 *);
    extern void func_80052E38(MATRIX2_8017CDF0 *);
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];

    DVECTOR2_8017CDF0 tmpxy[4];
    SVECTOR2_8017CDF0 box[8];
    SVECTOR2_8017CDF0 sxy[8];
    SVECTOR2_8017CDF0 tri[4];
    MATRIX2_8017CDF0 mtx;
    struct { long otz, flag, opz, sz0, sz1, sz2, sz3; } g;

    s32 lim;
    s32 nparts;
    s32 j;
    u32 nprim;
    u32 i;
    Part_8017CDF0 *part;
    Prim_8017CDF0 *prim;
    u8 *pkt;
    u32 ot;
    u8 *vtx;
    u8 *va, *vb, *vc, *vd;
    u32 w;
    s32 code;
    u32 wx, wy, wz, wzh;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 mnc, mxc;
    s16 my, mny, mx, mn;

    if (*(s32 *)a0 != 0) {
        return;
    }

    lim = func_800491EC() + *(s32 *)(a0 + 0x64);
    func_800547D8(a2, &mtx);
    func_80052E38(&mtx);

    pkt = D_800A5E60;
    part = (Part_8017CDF0 *)(a1 + 0x14);
    nparts = *(s32 *)(a1 + 8);
    vtx = *(u8 **)(a1 + 0x10);
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];

    for (j = 0; j < nparts; j++, part++) {
        wx = part->xx;
        mn = wx;
        mx = wx >> 16;
        wy = part->yy;
        mny = wy;
        my = wy >> 16;
        wz = part->zz;
        wzh = wz >> 16;
        box[0].vx = mn; box[0].vy = mny; box[0].vz = wz;
        box[1].vx = mx; box[1].vy = mny; box[1].vz = wz;
        box[2].vx = mn; box[2].vy = mny; box[2].vz = wzh;
        box[3].vx = mx; box[3].vy = mny; box[3].vz = wzh;

        gte_ldv3c(&box[0]);
        gte_rtpt();
        gte_stsxy3(&sxy[0], &sxy[1], &sxy[2]);
        gte_ldv0(&box[3]);
        gte_rtps();
        /* the far-face corners are filled inside the RTPS latency window — the
           volatile asms are hard sched barriers, so this ordering is SOURCE order */
        box[4].vx = mn; box[4].vy = my;  box[4].vz = wz;
        box[5].vx = mx; box[5].vy = my;  box[5].vz = wz;
        box[6].vx = mn; box[6].vy = my;  box[6].vz = wzh;
        box[7].vx = mx; box[7].vy = my;  box[7].vz = wzh;
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
                    prim = (Prim_8017CDF0 *)part->prim;
                    nprim = part->nprim;
                    for (i = 0; i < nprim; i++, prim++) {
                        w = prim->w1;
                        va = vtx + (w & 0xFFFF);
                        vb = vtx + (w >> 16);
                        w = prim->w2;
                        tri[0] = *(SVECTOR2_8017CDF0 *)va;
                        tri[1] = *(SVECTOR2_8017CDF0 *)vb;
                        vc = vtx + (w & 0xFFFF);
                        w = w >> 16;
                        tri[2] = *(SVECTOR2_8017CDF0 *)vc;
                        gte_ldv3c(&tri[0]);
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
                                    gte_stsxy3_ft3(pkt);
                                    gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
                                    if (((PolyFT3_8017CDF0 *)pkt)->x0 > ((PolyFT3_8017CDF0 *)pkt)->x1) {
                                        mx = ((PolyFT3_8017CDF0 *)pkt)->x0;
                                        mn = ((PolyFT3_8017CDF0 *)pkt)->x1;
                                    } else {
                                        mn = ((PolyFT3_8017CDF0 *)pkt)->x0;
                                        mx = ((PolyFT3_8017CDF0 *)pkt)->x1;
                                    }
                                    if (((PolyFT3_8017CDF0 *)pkt)->x2 > mx) mx = ((PolyFT3_8017CDF0 *)pkt)->x2;
                                    else if (((PolyFT3_8017CDF0 *)pkt)->x2 < mn) mn = ((PolyFT3_8017CDF0 *)pkt)->x2;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (((PolyFT3_8017CDF0 *)pkt)->y0 > ((PolyFT3_8017CDF0 *)pkt)->y1) {
                                            my = ((PolyFT3_8017CDF0 *)pkt)->y0;
                                            mny = ((PolyFT3_8017CDF0 *)pkt)->y1;
                                        } else {
                                            mny = ((PolyFT3_8017CDF0 *)pkt)->y0;
                                            my = ((PolyFT3_8017CDF0 *)pkt)->y1;
                                        }
                                        if (((PolyFT3_8017CDF0 *)pkt)->y2 > my) my = ((PolyFT3_8017CDF0 *)pkt)->y2;
                                        else if (((PolyFT3_8017CDF0 *)pkt)->y2 < mny) mny = ((PolyFT3_8017CDF0 *)pkt)->y2;
                                        if (my >= -0x6E && mny < 0x6F) {
                                            s32 za;
                                            u32 *otp;
                                            u32 *tp;
                                            u32 c0;
                                            if (g.sz0 > g.sz1) {
                                                za = g.sz0;
                                                if (za < g.sz2) za = g.sz2;
                                            } else {
                                                za = g.sz1;
                                                if (za < g.sz2) za = g.sz2;
                                            }
                                            tp = (u32 *)prim->w0;
                                            c0 = tp[0];
                                            g.opz = za;
                                            ((PolyFT3_8017CDF0 *)pkt)->rgbc = c0;
                                            ((PolyFT3_8017CDF0 *)pkt)->uvc0 = tp[1];
                                            ((PolyFT3_8017CDF0 *)pkt)->uvp1 = tp[2];
                                            ((PolyFT3_8017CDF0 *)pkt)->uv2 = tp[3];
                                            otp = (u32 *)(((za >> 2) << 2) + ot);
                                            *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x7000000;
                                            *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                            pkt += 0x28;
                                        }
                                    }
                                    break;
                                case 2:
                                case 3:
                                    gte_stsxy3c(&tmpxy[0]);
                                    tri[3] = *(SVECTOR2_8017CDF0 *)vd;
                                    gte_ldv0(&tri[3]);
                                    gte_rtps();
                                    if (tmpxy[0].vx > tmpxy[1].vx) {
                                        mx = tmpxy[0].vx;
                                        mn = tmpxy[1].vx;
                                    } else {
                                        mn = tmpxy[0].vx;
                                        mx = tmpxy[1].vx;
                                    }
                                    if (tmpxy[2].vx > mx) mx = tmpxy[2].vx;
                                    else if (tmpxy[2].vx < mn) mn = tmpxy[2].vx;
                                    if (tmpxy[0].vy > tmpxy[1].vy) {
                                        my = tmpxy[0].vy;
                                        mny = tmpxy[1].vy;
                                    } else {
                                        mny = tmpxy[0].vy;
                                        my = tmpxy[1].vy;
                                    }
                                    if (tmpxy[2].vy > my) my = tmpxy[2].vy;
                                    else if (tmpxy[2].vy < mny) mny = tmpxy[2].vy;
                                    gte_stflg(&g.flag);
                                    if (!(g.flag & 0x7F85E000)) {
                                        gte_stsz4(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
                                        gte_stsxy((long *)&((PolyFT4_8017CDF0 *)pkt)->x3);
                                        if (((PolyFT4_8017CDF0 *)pkt)->x3 < mn) mn = ((PolyFT4_8017CDF0 *)pkt)->x3;
                                        else if (mx < ((PolyFT4_8017CDF0 *)pkt)->x3) mx = ((PolyFT4_8017CDF0 *)pkt)->x3;
                                        if (mx >= -0xA0 && mn < 0xA1) {
                                            if (((PolyFT4_8017CDF0 *)pkt)->y3 < mny) mny = ((PolyFT4_8017CDF0 *)pkt)->y3;
                                            else if (my < ((PolyFT4_8017CDF0 *)pkt)->y3) my = ((PolyFT4_8017CDF0 *)pkt)->y3;
                                            if (my >= -0x6E && mny < 0x6F) {
                                                s32 za, zb;
                                                u32 *otp;
                                                u32 *tp;
                                            u32 c0;
                                                u32 uvw;
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;
                                                *(u32 *)&((PolyFT4_8017CDF0 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((PolyFT4_8017CDF0 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((PolyFT4_8017CDF0 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                tp = (u32 *)prim->w0;
                                                ((PolyFT4_8017CDF0 *)pkt)->rgbc = tp[0];
                                                ((PolyFT4_8017CDF0 *)pkt)->uvc0 = tp[1];
                                                ((PolyFT4_8017CDF0 *)pkt)->uvp1 = tp[2];
                                                uvw = tp[3];
                                                ((PolyFT4_8017CDF0 *)pkt)->uv2 = uvw;
                                                ((PolyFT4_8017CDF0 *)pkt)->uv3 = uvw >> 16;
                                                otp = (u32 *)(((za >> 2) << 2) + ot);
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
        /* §47 live-length slider: +1 static insn inside the loop-bound
           pseudo's range only (past the tri-base's last use) — splits the
           $fp contest toward &tri[0] so the bound spills, as the target does */
        __asm__ volatile ("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B headers2)
    }
    D_800A5E60 = pkt;
}
