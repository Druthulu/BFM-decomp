void *func_800277DC(void *a0, SVECTOR800277DC *a1, void *a2, u8 *a3,
                     s32 count, s32 shift, s32 *ot)
{
    struct { s32 flag, otz, sz0, sz1, sz2; } g;
    struct { u8 pad[3]; u8 code; u32 rgb1, rgb2, term, rgb0; u16 i0, i1, i2, i3; } *src = a0;
    struct { u32 tag, rgb0, xy0, rgb1, xy1, rgb2, xy2, term; } *p = (void *)a3;
    s32 m;

    for (; count != 0; count--, src++) {
        gte_ldv3(&a1[src->i0], &a1[src->i1], &a1[src->i2]);
        gte_rtpt();
        p->rgb1 = src->rgb1;
        p->rgb2 = src->rgb2;
        p->term = src->term;
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
        if (D_80078D88[0] & 0x8000) {
            gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
            if (g.sz0 > g.sz1) {
                m = g.sz0;
                if (m < g.sz2) m = g.sz2;
            } else {
                m = g.sz1;
                if (m < g.sz2) m = g.sz2;
            }
            g.otz = m >> 2;
        } else {
            gte_avsz3();
            gte_stotz(&g.otz);
        }
        p->rgb0 = (src->rgb0 & 0xFFFFFF) | ((u32)src->code << 24);
        {
            u32 *q = (u32 *)&ot[g.otz >> shift];
            p->tag = (*q & 0xFFFFFF) | 0x07000000;
            *q = (u32)p & 0xFFFFFF;
        }
        p++;
    }
    return p;
}
