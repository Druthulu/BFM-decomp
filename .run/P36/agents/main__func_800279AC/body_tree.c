LineG4 *func_800279AC(SrcQ *src, Vtx8 *vb, s32 unused, LineG4 *prim, s32 n, s32 shift, u32 *ot)
{
    s32 flag;
    s32 otz;

    /* cookbook §21 zero-byte re-tie: without it loop.c's record_initial takes the biv's
     * initial value straight from the parameter COPY (set prim (reg $a3)), so the +4 giv is
     * emitted as (plus (reg $a3) 4) -- $a3 then stays live past the copy, conflicts with the
     * prim pseudo, and prim/giv land in $t1/$a3 (target: $a3/$t1). The re-tie makes the
     * pre-loop set non-invariant so the giv is derived from the PSEUDO and prim coalesces
     * into $a3. Emits nothing. */
    __asm__ ("" : "=r"(prim) : "0"(prim));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
    for (; n != 0; n--, src++) {
        gte_ldv3(&vb[src->i0], &vb[src->i1], &vb[src->i2]);
        gte_rtpt();
        prim->rgb1 = src->rgb1;
        prim->rgb2 = src->rgb2;
        prim->rgb3 = src->rgb3;
        gte_stflg(&flag);
        if (flag & 0xFFFFEFFF) {
            continue;
        }
        gte_nclip();
        gte_stopz(&otz);
        if (otz <= 0) {
            continue;
        }
        gte_stsxy3_ft3(prim);
        gte_ldv0(&vb[src->i3]);
        gte_rtps();
        gte_stflg(&flag);
        if (flag & 0xFFFFEFFF) {
            continue;
        }
        gte_stsxy(&prim->xy3);
        prim->term = src->term;
        /* §5a zero-byte barrier: else sched2 hoists the D_80078D88 load above this store and
         * eats the two load-delay nops the target keeps (the -2 length drift). */
        if (D_80078D88[0] & 0x8000) {
            s32 sz[4];
            s32 m, k;
            gte_stsz4(&sz[0], &sz[1], &sz[2], &sz[3]);
            m = sz[2];
            if (m < sz[3]) {
                m = sz[3];
            }
            k = sz[0];
            if (k < sz[1]) {
                k = sz[1];
            }
            if (k < m) {
                k = m;
            }
            otz = k >> 2;
        } else {
            gte_avsz4();
            gte_stotz(&otz);
        }
        prim->rgb0 = (src->rgb0 & 0xFFFFFF) | ((u32)src->code << 24);
        /* §5a zero-byte barrier: keeps the rgb0 store ahead of the OT-link block instead of
         * letting sched2 interleave the `otz` reload into the rgb0 chain. */
        __asm__ __volatile__ ("" : : : "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus9)
        {
            u32 *p = &ot[otz >> shift];
            prim->tag = (*p & 0xFFFFFF) | 0x09000000;
            *p = (u32)prim & 0xFFFFFF;
        }
        prim++;
    }
    return prim;
}
