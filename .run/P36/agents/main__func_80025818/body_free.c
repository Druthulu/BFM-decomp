PG3 *func_80025818(TPRIM_80025818 *prim, SVEC8_80025818 *vtx, SVEC8_80025818 *nrm, PG3 *poly,
                   s32 n, s32 shift, u32 *ot)
{
    s32 otz;
    s32 flag;
    u32 *otp;

    if (n != 0) {
        /* Zero-instruction launder of the `poly` biv's initial value.
         * Without it, loop.c's record_initial (loop.c:3454-3511) takes the biv's
         * initial value straight from the parameter copy `poly = $a3`, so the GIV
         * preheader init is emitted as `giv = (hard $a3) + 4`.  That keeps hard
         * $a3 live to the preheader, which makes the `poly` pseudo CONFLICT with
         * $a3 (dump: `75 conflicts: ... 7`), so $a3 goes to the GIV and `poly`
         * needs an extra `move`.  An asm_operands SET_SRC fails
         * valid_initial_value_p, so bl->initial_value stays the pseudo and $a3
         * stays free for `poly` -- byte-exact, 135 -> 134 instructions.
         * It MUST sit below the `n != 0` guard: above it the #APP/#NO_APP pair
         * blocks the `prim` parameter copy from hopping into the beqz delay slot
         * (cookbook RC-11). */
        do {
            gte_ldv3(&vtx[prim->v0], &vtx[prim->v1], &vtx[prim->v2]);
            gte_rtpt();
            gte_stflg(&flag);
            if ((flag & ~0x1000) == 0) {
                gte_nclip();
                gte_stopz(&otz);
                if (otz > 0) {
                    gte_stsxy3_ft3(poly);
                    gte_avsz3();
                    gte_stotz(&otz);
                    gte_ldv0(&nrm[prim->n0]);
                    gte_ldrgb(&prim->rgb0);
                    gte_nccs();
                    gte_strgb(&poly->r0);
                    gte_ldrgb(&prim->rgb1);
                    gte_nccs();
                    gte_strgb(&poly->r1);
                    gte_ldrgb(&prim->rgb2);
                    gte_nccs();
                    gte_strgb(&poly->r2);
                    poly->code = (poly->code & 2) | 0x30;
                    otp = ot + (otz >> shift);
                    *(u32 *)poly = (*otp & 0xFFFFFF) | 0x06000000;
                    *otp = (u32)poly & 0xFFFFFF;
                    poly++;
                    if (D_800A2B78 != 0) {
                        if (poly[-1].code & 2) {
                            /* 2-word DR_MODE packet chained in front of the G3 */
                            otp = ot + (otz >> shift);
                            *((u8 *)poly + 3) = 1;
                            *(u32 *)((u8 *)poly + 4) =
                                0xE100000A | ((D_800A2B78 & 3) << 5);
                            *(u32 *)poly = (*otp & 0xFFFFFF) | 0x01000000;
                            *otp = (u32)poly & 0xFFFFFF;
                            poly = (PG3 *)((u8 *)poly + 8);
                        }
                    }
                }
            }
            n--;
            prim++;
        } while (n != 0);
    }
    return poly;
}
