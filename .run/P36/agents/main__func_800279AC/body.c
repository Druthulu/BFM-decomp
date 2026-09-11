LineG4 *func_800279AC(SrcQ *src, Vtx8 *vb, s32 unused, LineG4 *prim, s32 n, s32 shift, u32 *ot)
{
    struct { s32 flag, otz, sz0, sz1, sz2, sz3; } g;
    LineG4 *p = prim;
    s32 m, k;

    for (; n != 0; n--, src++) {
        gte_ldv3(&vb[src->i0], &vb[src->i1], &vb[src->i2]);
        gte_rtpt();
        p->rgb1 = src->rgb1;
        p->rgb2 = src->rgb2;
        p->rgb3 = src->rgb3;
        gte_stflg(&g.flag);
        if (g.flag & 0xFFFFEFFF) {
            continue;
        }
        gte_nclip();
        gte_stopz(&g.otz);
        if (g.otz <= 0) {
            continue;
        }
        gte_stsxy3_ft3(p);
        gte_ldv0(&vb[src->i3]);
        gte_rtps();
        gte_stflg(&g.flag);
        if (g.flag & 0xFFFFEFFF) {
            continue;
        }
        gte_stsxy(&p->xy3);
        p->term = src->term;
        if (D_80078D88[0] & 0x8000) {
            gte_stsz4(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
            m = g.sz2;
            if (m < g.sz3) {
                m = g.sz3;
            }
            k = g.sz0;
            if (k < g.sz1) {
                k = g.sz1;
            }
            if (k < m) {
                k = m;
            }
            g.otz = k >> 2;
        } else {
            gte_avsz4();
            gte_stotz(&g.otz);
        }
        p->rgb0 = (src->rgb0 & 0xFFFFFF) | ((u32)src->code << 24);
        {
            u32 *q = &ot[g.otz >> shift];
            p->tag = (*q & 0xFFFFFF) | 0x09000000;
            *q = (u32)p & 0xFFFFFF;
        }
        p++;
    }
    return p;
}
