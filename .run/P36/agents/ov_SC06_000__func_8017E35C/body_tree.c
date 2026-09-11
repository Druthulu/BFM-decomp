void func_8017E35C(s32 arg0)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8   D_800A6610[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8  *D_800A5E60;
    typedef struct { u32 w0, w1, w2; } Prim;
    typedef struct { u8 b[8]; } V8;

    DVec35C tmpxy[4];
    SVec35C box[8];
    SVec35C sxy[8];
    V8 vbuf[3];
    V8 vdbuf;
    Mtx35C mtx;
    struct { long otz, flag, opz, sz0, sz1, sz2, sz3; } g;

    s32 lim;
    s32 j;
    u32 i;
    u8 *pkt;
    Prim *prim;
    u32 nprim;
    u8 *vtx;
    s32 nparts;
    Part35C *part;
    u32 ot;
    u32 w;
    s32 code;
    u8 *va, *vb, *vc, *vd;
    u32 wx, wy, wz, zh;
    s16 my, mny, mx, mn;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 mnc, mxc;
    s32 za, zb, d, oz;
    u32 *tp;
    u32 uvw;

    if (*(s32 *)arg0 != 0) {
        return;
    }

    lim = func_800491EC() + *(s32 *)(arg0 + 0x64);
    func_800547D8(arg0 + 0x10, &mtx);
    func_80052E38(&mtx);

    pkt = D_800A5E60;
    part = *(Part35C **)(arg0 + 0xC);
    nparts = *(s32 *)(*(s32 *)(arg0 + 8) + 8);
    vtx = *(u8 **)(*(s32 *)(arg0 + 8) + 0x10);
    ot = (u32)&D_800A6610[(u16)D_800B9A02 << 14];

    for (j = 0; j < nparts; j++, part++) {
        wx = part->xx;
        wy = part->yy;
        wz = part->zz;
        mn = wx;
        mx = wx >> 16;
        mny = wy;
        my = wy >> 16;
        zh = wz >> 16;
        box[0].vx = mn; box[0].vy = mny; box[0].vz = wz;
        box[1].vx = mx; box[1].vy = mny; box[1].vz = wz;
        box[2].vx = mn; box[2].vy = mny; box[2].vz = zh;
        box[3].vx = mx; box[3].vy = mny; box[3].vz = zh;

        gte_ldv3c(&box[0]);
        gte_rtpt();
        gte_stsxy3(&sxy[0], &sxy[1], &sxy[2]);
        gte_ldv0(&box[3]);
        gte_rtps();

        box[4].vx = mn; box[4].vy = my;  box[4].vz = wz;
        box[5].vx = mx; box[5].vy = my;  box[5].vz = wz;
        box[6].vx = mn; box[6].vy = my;  box[6].vz = zh;
        box[7].vx = mx; box[7].vy = my;  box[7].vz = zh;

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
                    __asm__ __volatile__ ("" :: "r" (nparts));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus7)
                    prim = (Prim *)part->prim;
                    nprim = part->nprim;
                    for (i = 0; i < nprim; i++, prim++) {
                        w = prim->w1;
                        va = vtx + (w & 0xFFFF);
                        vb = vtx + (w >> 16);
                        w = prim->w2;
                        vc = vtx + (w & 0xFFFF);
                        w = w >> 16;
                        vbuf[0] = *(V8 *)va;
                        vbuf[1] = *(V8 *)vb;
                        vbuf[2] = *(V8 *)vc;
                        gte_ldv3c(vbuf);
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
                                    /* ---------------- TRI (FT3) ---------------- */
                                    gte_stsxy3_ft3(pkt);
                                    gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
                                    if (((Ft3_35C *)pkt)->x0 > ((Ft3_35C *)pkt)->x1) {
                                        mx = ((Ft3_35C *)pkt)->x0; mn = ((Ft3_35C *)pkt)->x1;
                                    } else {
                                        mn = ((Ft3_35C *)pkt)->x0; mx = ((Ft3_35C *)pkt)->x1;
                                    }
                                    if (((Ft3_35C *)pkt)->x2 > mx) mx = ((Ft3_35C *)pkt)->x2;
                                    else if (((Ft3_35C *)pkt)->x2 < mn) mn = ((Ft3_35C *)pkt)->x2;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (((Ft3_35C *)pkt)->y0 > ((Ft3_35C *)pkt)->y1) {
                                            my = ((Ft3_35C *)pkt)->y0; mny = ((Ft3_35C *)pkt)->y1;
                                        } else {
                                            mny = ((Ft3_35C *)pkt)->y0; my = ((Ft3_35C *)pkt)->y1;
                                        }
                                        if (((Ft3_35C *)pkt)->y2 > my) my = ((Ft3_35C *)pkt)->y2;
                                        else if (((Ft3_35C *)pkt)->y2 < mny) mny = ((Ft3_35C *)pkt)->y2;
                                        if (my >= -0x6E && mny < 0x6F) {
                                            u32 *otp;
                                            if (g.sz0 > g.sz1) { za = g.sz0; if (za < g.sz2) za = g.sz2; }
                                            else               { za = g.sz1; if (za < g.sz2) za = g.sz2; }
                                            g.opz = za;
                                            if (code == 7) g.opz = za + 0x50;
                                            oz = g.opz;
                                            d = oz - 400;
                                            if (d < 0) d = 0;
                                            d = (d >> 8) << 22;
                                            tp = (u32 *)prim->w0;
                                            ((Ft3_35C *)pkt)->rgbc = tp[0];
                                            ((Ft3_35C *)pkt)->uvc0 = tp[1] + d;
                                            ((Ft3_35C *)pkt)->uvp1 = tp[2];
                                            ((Ft3_35C *)pkt)->uv2  = tp[3];
                                            otp = (u32 *)(((oz >> 2) << 2) + ot);
                                            *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x7000000;
                                            *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                            pkt += 0x28;
                                        }
                                    }
                                    break;
                                case 2:
                                case 3:
                                    /* ---------------- QUAD (FT4) ---------------- */
                                    gte_stsxy3c(&tmpxy[0]);
                                    vdbuf = *(V8 *)vd;
                                    gte_ldv0(&vdbuf);
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
                                        gte_stsxy((long *)&((Ft4_35C *)pkt)->x3);
                                        if (((Ft4_35C *)pkt)->x3 < mn) mn = ((Ft4_35C *)pkt)->x3;
                                        else if (mx < ((Ft4_35C *)pkt)->x3) mx = ((Ft4_35C *)pkt)->x3;
                                        if (mx >= -0xA0 && mn < 0xA1) {
                                            if (((Ft4_35C *)pkt)->y3 < mny) mny = ((Ft4_35C *)pkt)->y3;
                                            else if (my < ((Ft4_35C *)pkt)->y3) my = ((Ft4_35C *)pkt)->y3;
                                            if (my >= -0x6E && mny < 0x6F) {
                                                u32 *otp;
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;
                                                if (code == 3) g.opz = za + 0x50;
                                                oz = g.opz;
                                                d = oz - 400;
                                                if (d < 0) d = 0;
                                                d = (d >> 8) << 22;
                                                *(u32 *)&((Ft4_35C *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((Ft4_35C *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((Ft4_35C *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                tp = (u32 *)prim->w0;
                                                ((Ft4_35C *)pkt)->rgbc = tp[0];
                                                ((Ft4_35C *)pkt)->uvc0 = tp[1] + d;
                                                ((Ft4_35C *)pkt)->uvp1 = tp[2];
                                                uvw = tp[3];
                                                ((Ft4_35C *)pkt)->uv2 = uvw;
                                                ((Ft4_35C *)pkt)->uv3 = uvw >> 16;
                                                otp = (u32 *)(((oz >> 2) << 2) + ot);
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
