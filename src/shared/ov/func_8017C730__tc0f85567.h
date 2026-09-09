/* func_8017C730 — shared body (overlay slot 0x80128158, h_text c0f85567). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017C730(s32 arg0)
{
    typedef struct { u32 w0, w1, w2; } Prim;

    extern s32 func_800491EC(void);
    extern void func_800547D8(s32, MATRIX2 *);
    extern void func_80052E38(MATRIX2 *);
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern short D_800B9A02;

    DVECTOR2 tmpxy[4];
    SVECTOR2 box[8];
    SVECTOR2 sxy[8];
    MATRIX2 mtx;
    SVECTOR2 org;
    SVECTOR2 hv;
    long gflag, gopz, gsz0, gsz1, gsz2, gsz3;

    s32 lim;
    s16 hmid;
    s16 hhi;
    u32 nprim;
    s32 nparts;
    s32 j;
    u32 i;
    Part *part;
    Prim *prim;
    u8 *pkt;
    u32 ot;
    u8 *vtx;
    u8 *va, *vb, *vc, *vd;
    u32 w, code;
    u32 wx, wy, wz, wv;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 mnc, mxc;
    s16 my, mny, mx, mn;
    s16 mid;
    s32 cd;

    lim = func_800491EC();
    func_800547D8(arg0 + 0x10, &mtx);
    func_80052E38(&mtx);

    org.vx = 0;
    org.vy = 0;
    org.vz = 0;
    bandsetup(&org, &hv);

    hmid = hv.vy + 0x100;
    hhi = hv.vy + 0x280;
    hv.vy = hv.vy - 0x180;

    pkt = D_800A5E60;
    part = *(Part **)(arg0 + 0xC);
    nparts = *(s32 *)(*(s32 *)(arg0 + 8) + 8);
    vtx = *(u8 **)(*(s32 *)(arg0 + 8) + 0x10);
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];

    for (j = 0; j < nparts; j++, part++) {
        wx = part->xx;
        mn = wx;
        mx = wx >> 16;
        wy = part->yy;
        mny = wy;
        my = wy >> 16;
        wz = part->zz;
        wv = wz >> 16;
        mid = (mny + my) / 2;
        if (mid < hv.vy) continue;
        if (hhi < mid) continue;
        box[0].vx = mn; box[0].vy = mny; box[0].vz = wz;
        box[1].vx = mx; box[1].vy = mny; box[1].vz = wz;
        box[2].vx = mn; box[2].vy = mny; box[2].vz = wv;
        box[3].vx = mx; box[3].vy = mny; box[3].vz = wv;
        box[4].vx = mn; box[4].vy = my;  box[4].vz = wz;
        box[5].vx = mx; box[5].vy = my;  box[5].vz = wz;
        box[6].vx = mn; box[6].vy = my;  box[6].vz = wv;
        box[7].vx = mx; box[7].vy = my;  box[7].vz = wv;

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
                t32 = mid;
                if (!(hhi < t32)) { mnc = hmid; __asm__ volatile ("" : : "r" (mnc)); }  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B headers2)
                prim = (Prim *)part->prim;
                nprim = part->nprim;
                for (i = 0; i < nprim; i++, prim++) {
                    w = prim->w1;
                    va = vtx + (w & 0xFFFF);
                    vb = vtx + (w >> 16);
                    w = prim->w2;
                    vc = vtx + (w & 0xFFFF);
                    w = w >> 16;
                    gte_ldv3(va, vb, vc);
                    gte_rtpt();
                    gte_stflg(&gflag);
                    if (!(gflag & 0x7F85E000)) {
                        gte_nclip();
                        code = w & 7;
                        vd = vtx + (w & 0xFFF8);
                        gte_stopz(&gopz);
                        if (gopz > 0) {
                            switch (code) {
                            case 4:
                            case 5:
                                gte_stsxy3_f3(pkt);
                                gte_stsz3(&gsz0, &gsz1, &gsz2);
                                if (((PolyF3 *)pkt)->x0 > ((PolyF3 *)pkt)->x1) {
                                    mx = ((PolyF3 *)pkt)->x0;
                                    mn = ((PolyF3 *)pkt)->x1;
                                } else {
                                    mn = ((PolyF3 *)pkt)->x0;
                                    mx = ((PolyF3 *)pkt)->x1;
                                }
                                if (((PolyF3 *)pkt)->x2 > mx) mx = ((PolyF3 *)pkt)->x2;
                                else if (((PolyF3 *)pkt)->x2 < mn) mn = ((PolyF3 *)pkt)->x2;
                                if (mx >= -0xA0 && mn < 0xA1) {
                                    if (((PolyF3 *)pkt)->y0 > ((PolyF3 *)pkt)->y1) {
                                        my = ((PolyF3 *)pkt)->y0;
                                        mny = ((PolyF3 *)pkt)->y1;
                                    } else {
                                        mny = ((PolyF3 *)pkt)->y0;
                                        my = ((PolyF3 *)pkt)->y1;
                                    }
                                    if (((PolyF3 *)pkt)->y2 > my) my = ((PolyF3 *)pkt)->y2;
                                    else if (((PolyF3 *)pkt)->y2 < mny) mny = ((PolyF3 *)pkt)->y2;
                                    if (my >= -0x6E && mny < 0x6F) {
                                        s32 za, zb;
                                        u32 *otp;
                                        if (gsz0 < lim && gsz1 < lim && gsz2 < lim) break;
                                        if (gsz0 > gsz1) {
                                            za = gsz0;
                                            if (za < gsz2) za = gsz2;
                                        } else {
                                            za = gsz1;
                                            if (za < gsz2) za = gsz2;
                                        }
                                        gopz = za;
                                        if (code != 4) gopz = za + 0x200;
                                        *(u32 *)(pkt + 4) = prim->w0;
                                        otp = (u32 *)(((gopz >> 2) << 2) + ot);
                                        *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x4000000;
                                        *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                        pkt += 0x14;
                                    }
                                }
                                break;
                            case 6:
                            case 7:
                                gte_stsxy3_ft3(pkt);
                                gte_stsz3(&gsz0, &gsz1, &gsz2);
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
                                    if (my >= -0x6E && mny < 0x6F) {
                                        s32 za, zb;
                                        u32 *otp;
                                        u32 *tp;
                                        u32 uvw;
                                        gte_avsz3();
                                        if (gsz0 > gsz1) {
                                            za = gsz0;
                                            if (za < gsz2) za = gsz2;
                                        } else {
                                            za = gsz1;
                                            if (za < gsz2) za = gsz2;
                                        }
                                        gopz = za;
                                        if (code != 6) gopz = za + 0x200;
                                        tp = (u32 *)prim->w0;
                                        ((PolyFT3 *)pkt)->rgbc = tp[0];
                                        uvw = tp[1] & 0x3FC0FFFF;
                                        cd = gopz - 0x174;
                                        if (cd < 0) cd = gopz - 0xF5;
                                        otp = (u32 *)(((gopz >> 2) << 2) + ot);
                                        ((PolyFT3 *)pkt)->uvc0 = uvw | (((cd >> 7) + 0x30) << 16);
                                        ((PolyFT3 *)pkt)->uvp1 = tp[2];
                                        ((PolyFT3 *)pkt)->uv2 = tp[3];
                                        *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x7000000;
                                        *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                        pkt += 0x20;
                                    }
                                }
                                break;
                            case 0:
                            case 1:
                                gte_stsxy3_f4(pkt);
                                gte_ldv0(vd);
                                gte_rtps();
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
                                gte_stflg(&gflag);
                                if (!(gflag & 0x7F85E000)) {
                                    gte_stsz4(&gsz0, &gsz1, &gsz2, &gsz3);
                                    gte_stsxy((long *)&((PolyF4 *)pkt)->x3);
                                    if (((PolyF4 *)pkt)->x3 < mn) mn = ((PolyF4 *)pkt)->x3;
                                    else if (mx < ((PolyF4 *)pkt)->x3) mx = ((PolyF4 *)pkt)->x3;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (((PolyF4 *)pkt)->y3 < mny) mny = ((PolyF4 *)pkt)->y3;
                                        else if (my < ((PolyF4 *)pkt)->y3) my = ((PolyF4 *)pkt)->y3;
                                        if (my >= -0x6E && mny < 0x6F) {
                                            s32 za, zb;
                                            u32 *otp;
                                            if (gsz0 < lim && gsz1 < lim && gsz2 < lim && gsz3 < lim) break;
                                            zb = gsz2;
                                            if (zb < gsz3) zb = gsz3;
                                            za = gsz0;
                                            if (za < gsz1) za = gsz1;
                                            if (za < zb) za = zb;
                                            gopz = za;
                                            if (code != 0) gopz = za + 0x200;
                                            *(u32 *)(pkt + 4) = prim->w0;
                                            otp = (u32 *)(((gopz >> 2) << 2) + ot);
                                            *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x5000000;
                                            *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                            pkt += 0x18;
                                        }
                                    }
                                }
                                break;
                            case 2:
                            case 3:
                                gte_stsxy3c(&tmpxy[0]);
                                gte_ldv0(vd);
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
                                gte_stflg(&gflag);
                                if (!(gflag & 0x7F85E000)) {
                                    gte_stsz4(&gsz0, &gsz1, &gsz2, &gsz3);
                                    gte_stsxy((long *)&((PolyFT4 *)pkt)->x3);
                                    if (((PolyFT4 *)pkt)->x3 < mn) mn = ((PolyFT4 *)pkt)->x3;
                                    else if (mx < ((PolyFT4 *)pkt)->x3) mx = ((PolyFT4 *)pkt)->x3;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (((PolyFT4 *)pkt)->y3 < mny) mny = ((PolyFT4 *)pkt)->y3;
                                        else if (my < ((PolyFT4 *)pkt)->y3) my = ((PolyFT4 *)pkt)->y3;
                                        if (my >= -0x6E && mny < 0x6F) {
                                            s32 za, zb;
                                            u32 *otp;
                                            u32 *tp;
                                            u32 uvw;
                                            u32 uvm;
                                            zb = gsz2;
                                            if (zb < gsz3) zb = gsz3;
                                            za = gsz0;
                                            if (za < gsz1) za = gsz1;
                                            if (za < zb) za = zb;
                                            gopz = za;
                                            if (code != 2) gopz = za + 0x200;
                                            *(u32 *)&((PolyFT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                            *(u32 *)&((PolyFT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                            *(u32 *)&((PolyFT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                            tp = (u32 *)prim->w0;
                                            ((PolyFT4 *)pkt)->rgbc = tp[0];
                                            uvm = tp[1] & 0x3FC0FFFF;
                                            cd = gopz - 0x174;
                                            if (cd < 0) cd = gopz - 0xF5;
                                            otp = (u32 *)(((gopz >> 2) << 2) + ot);
                                            ((PolyFT4 *)pkt)->uvc0 = uvm | (((cd >> 7) + 0x30) << 16);
                                            ((PolyFT4 *)pkt)->uvp1 = tp[2];
                                            uvw = tp[3];
                                            ((PolyFT4 *)pkt)->uv2 = uvw;
                                            ((PolyFT4 *)pkt)->uv3 = uvw >> 16;
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
    D_800A5E60 = pkt;
}
