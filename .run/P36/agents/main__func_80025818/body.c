PG3 *func_80025818(TPRIM_80025818 *prim, SVEC8_80025818 *vtx, SVEC8_80025818 *nrm, PG3 *poly,
                   s32 n, s32 shift, u32 *ot)
{
    s32 otz;
    s32 flag;
    u32 *otp;
    PG3 *p;

    p = poly;
    if (n != 0) {
        do {
            gte_ldv3(&vtx[prim->v0], &vtx[prim->v1], &vtx[prim->v2]);
            gte_rtpt();
            gte_stflg(&flag);
            if ((flag & ~0x1000) == 0) {
                gte_nclip();
                gte_stopz(&otz);
                if (otz > 0) {
                    gte_stsxy3_ft3(p);
                    gte_avsz3();
                    gte_stotz(&otz);
                    gte_ldv0(&nrm[prim->n0]);
                    gte_ldrgb(&prim->rgb0);
                    gte_nccs();
                    gte_strgb(&p->r0);
                    gte_ldrgb(&prim->rgb1);
                    gte_nccs();
                    gte_strgb(&p->r1);
                    gte_ldrgb(&prim->rgb2);
                    gte_nccs();
                    gte_strgb(&p->r2);
                    p->code = (p->code & 2) | 0x30;
                    otp = ot + (otz >> shift);
                    *(u32 *)p = (*otp & 0xFFFFFF) | 0x06000000;
                    *otp = (u32)p & 0xFFFFFF;
                    p++;
                    if (D_800A2B78 != 0) {
                        if (p[-1].code & 2) {
                            /* 2-word DR_MODE packet chained in front of the G3 */
                            otp = ot + (otz >> shift);
                            *((u8 *)p + 3) = 1;
                            *(u32 *)((u8 *)p + 4) =
                                0xE100000A | ((D_800A2B78 & 3) << 5);
                            *(u32 *)p = (*otp & 0xFFFFFF) | 0x01000000;
                            *otp = (u32)p & 0xFFFFFF;
                            p = (PG3 *)((u8 *)p + 8);
                        }
                    }
                }
            }
            n--;
            prim++;
        } while (n != 0);
    }
    return p;
}
