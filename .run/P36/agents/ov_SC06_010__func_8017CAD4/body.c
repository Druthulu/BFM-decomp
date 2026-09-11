void func_8017CAD4(s32 *ctx, s32 *model, s32 mtxsrc)
{
    XDV2 tmpxy[4];
    XSV2 box[8];
    XSV2 sxy[8];
    XV8  vt[3];
    XV8  vd8;
    XMTX2 mtx;
    struct { long otz, flag, opz, sz0, sz1, sz2, sz3; } g;

    s32 lim;
    s32 cl;
    s32 nparts;
    XV8 *vtp;
    s32 j;
    u32 nprim;
    u32 i;
    XPart *part;
    XPrim *prim;
    u8 *pkt;
    u32 ot;
    u8 *vtx;
    u8 *vd;
    u8 *va, *vb, *vc;
    u32 w;
    u32 m24;
    s32 code;
    u32 wx, wy, wz, wzh;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 mnc, mxc;
    s16 my, mny, mx, mn;

    if (*ctx != 0) {
        return;
    }

    lim = func_800491EC() + *(s32 *)((u8 *)ctx + 0x64);
    func_800547D8(mtxsrc, &mtx);
    func_80052E38(&mtx);

    pkt = D_800A5E60;
    part = (XPart *)((u8 *)model + 0x14);
    nparts = *(s32 *)((u8 *)model + 8);
    vtx = *(u8 **)((u8 *)model + 0x10);
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];

    for (j = 0; j < nparts; j++, part++) {
        vtp = &vt[0];
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
        box[4].vx = mn; box[4].vy = my; box[4].vz = wz;
        box[5].vx = mx; box[5].vy = my; box[5].vz = wz;
        box[6].vx = mn; box[6].vy = my; box[6].vz = wzh;
        box[7].vx = mx; box[7].vy = my; box[7].vz = wzh;
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
                    prim = (XPrim *)part->prim;
                    nprim = part->nprim;
                    i = 0;
                    if (i >= nprim) goto noprim;
                    m24 = 0xFFFFFF;
                    do {
                        w = prim->w1;
                        va = vtx + (w & 0xFFFF);
                        vb = vtx + (w >> 16);
                        w = prim->w2;
                        vt[0] = *(XV8 *)va;
                        vt[1] = *(XV8 *)vb;
                        vc = vtx + (w & 0xFFFF);
                        w = w >> 16;
                        vt[2] = *(XV8 *)vc;
                        gte_ldv3c(vtp);
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
                                    if (((XFT3 *)pkt)->x0 > ((XFT3 *)pkt)->x1) {
                                        mx = ((XFT3 *)pkt)->x0;
                                        mn = ((XFT3 *)pkt)->x1;
                                    } else {
                                        mn = ((XFT3 *)pkt)->x0;
                                        mx = ((XFT3 *)pkt)->x1;
                                    }
                                    if (((XFT3 *)pkt)->x2 > mx) mx = ((XFT3 *)pkt)->x2;
                                    else if (((XFT3 *)pkt)->x2 < mn) mn = ((XFT3 *)pkt)->x2;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (((XFT3 *)pkt)->y0 > ((XFT3 *)pkt)->y1) {
                                            my = ((XFT3 *)pkt)->y0;
                                            mny = ((XFT3 *)pkt)->y1;
                                        } else {
                                            mny = ((XFT3 *)pkt)->y0;
                                            my = ((XFT3 *)pkt)->y1;
                                        }
                                        if (((XFT3 *)pkt)->y2 > my) my = ((XFT3 *)pkt)->y2;
                                        else if (((XFT3 *)pkt)->y2 < mny) mny = ((XFT3 *)pkt)->y2;
                                        if (my >= -0x6E && mny < 0x6F) {
                                            s32 za, tz, q, rgb;
                                            u32 *otp;
                                            u32 *tp;
                                            /* g.opz stored in each arm: post-reload cross-jump merges the two
                                             * stores back into one, but flow counted both (the &g.sz0/&g.sz1
                                             * allocno tie then falls the target's way). */
                                            if (g.sz0 > g.sz1) {
                                                za = g.sz0;
                                                if (za < g.sz2) za = g.sz2;
                                                g.opz = za;
                                            } else {
                                                za = g.sz1;
                                                if (za < g.sz2) za = g.sz2;
                                                g.opz = za;
                                            }
                                            if (code == 7) g.opz = za + 0x40;
                                            tz = g.opz;
                                            tp = (u32 *)prim->w0;
                                            q = 0x80 - (tz - 0x190) / 24;
                                            if (q < 0) q = 0;
                                            rgb = q | (q << 8) | (q << 16);
                                            ((XFT3 *)pkt)->rgbc = (tp[0] & 0xFF000000) | rgb;
                                            ((XFT3 *)pkt)->uvc0 = tp[1] + (cl << 22);
                                            ((XFT3 *)pkt)->uvp1 = tp[2];
                                            ((XFT3 *)pkt)->uv2 = tp[3];
                                            otp = (u32 *)(((tz >> 2) << 2) + ot);
                                            *(u32 *)pkt = (*otp & m24) | 0x7000000;
                                            *otp = (*otp & 0xFF000000) | ((u32)pkt & m24);
                                            pkt += 0x20;
                                        }
                                    }
                                    break;
                                case 2:
                                case 3:
                                    gte_stsxy3c(&tmpxy[0]);
                                    vd8 = *(XV8 *)vd;
                                    gte_ldv0(&vd8);
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
                                        gte_stsxy((long *)&((XFT4 *)pkt)->x3);
                                        if (((XFT4 *)pkt)->x3 < mn) mn = ((XFT4 *)pkt)->x3;
                                        else if (mx < ((XFT4 *)pkt)->x3) mx = ((XFT4 *)pkt)->x3;
                                        if (mx >= -0xA0 && mn < 0xA1) {
                                            if (((XFT4 *)pkt)->y3 < mny) mny = ((XFT4 *)pkt)->y3;
                                            else if (my < ((XFT4 *)pkt)->y3) my = ((XFT4 *)pkt)->y3;
                                            if (my >= -0x6E && mny < 0x6F) {
                                                s32 za, zb, tz, q, rgb;
                                                u32 *otp;
                                                u32 *tp;
                                                u32 uvw;
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;
                                                if (code == 3) g.opz = za + 0x40;
                                                *(u32 *)&((XFT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((XFT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((XFT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                tz = g.opz;
                                                tp = (u32 *)prim->w0;
                                                q = 0x80 - (tz - 0x190) / 24;
                                                if (q < 0) q = 0;
                                                rgb = q | (q << 8) | (q << 16);
                                                ((XFT4 *)pkt)->rgbc = (tp[0] & 0xFF000000) | rgb;
                                                ((XFT4 *)pkt)->uvc0 = tp[1];
                                                ((XFT4 *)pkt)->uvp1 = tp[2];
                                                uvw = tp[3];
                                                ((XFT4 *)pkt)->uv2 = uvw;
                                                ((XFT4 *)pkt)->uv3 = uvw >> 16;
                                                otp = (u32 *)(((tz >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*otp & m24) | 0x9000000;
                                                *otp = (*otp & 0xFF000000) | ((u32)pkt & m24);
                                                pkt += 0x28;
                                            }
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                        i++;
                        prim++;
                    } while (i < nprim);
                  noprim: ;
                }
            }
        }
    }
    D_800A5E60 = pkt;
}
