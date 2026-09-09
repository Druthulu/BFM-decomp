/* func_801372B0 — shared body (overlay slot 0x80128158, h_exact 009f12cb). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void ApplyMatrixSV(void *m, Svec_801372B0 *in, Svec_801372B0 *out);
extern void aGsSortLine(Gline_801372B0 *p, void *ot, s32 z) __asm__("GsSortLine");
extern void aF80137030(s32 x, s32 y) __asm__("func_80137030");
extern void func_80137178(s32 x, s32 y);
extern u8  D_800B9A11;
extern u8  D_800AF630[];
extern u16 aD800B9A02 __asm__("D_800B9A02");
extern u8  D_800A6518[];
void func_801372B0(void) {
    Svec_801372B0 in;
    Svec_801372B0 out;
    Gline_801372B0 prim;
    register u8 *mat __asm__("$23") = D_800AF630;            /* $s7 = base; +0x18 after branch */  // !FAKE: pin $23 — NEEDED DIFFERS (P36 rung B headers1)
    s32 white;                       /* $s3, assigned lazily in-if */
    s16 ax;                          /* $s0 = out.vx+0x7B */
    s16 ay;                          /* $s1 = out.vx+0x75 */
    s16 bx;                          /* $s2 = out.vy-0x57 */
    register s16 by __asm__("$20");                          /* $s4 = out.vy-0x5D */  // !FAKE: pin $20 — NEEDED DIFFERS (P36 rung B headers1)
    in.vz = 0;
    in.vy = 0;
    in.vx = 0;
    if (D_800B9A11 != 1) {
        mat += 0x18;                                         /* addiu $s7, $s7, 0x18 (post-branch) */
        white = 0xFF;
        /* --- corner 0: +X axis, white line from (0x78,-0x5A) --- */
        in.vx = 0x10;
        ApplyMatrixSV(mat, &in, &out);
        {
            s16 vx = out.vx;          /* $a3 */
            s16 vy = out.vy;          /* $v1 */
            prim.attr = 0;                                   /* LEVER B: colors BEFORE x0 here — */
            prim.r = white; prim.g = white; prim.b = white;  /* drops the sb LUIDs below the x0  */
            prim.x0 = 0x78;                                  /* store -> white's S2 boost fires  */
            prim.y0 = -0x5A;                                 /* late -> li $s3,0xFF lands @31    */
            { s16 x1v = vx + 0x78;  prim.x1 = x1v; }
            { s16 y1v = vy - 0x5A;  prim.y1 = y1v; }
            aGsSortLine(&prim, &D_800A6518[(u32)aD800B9A02 * 0x14], 0);
        }
        /* --- corner 1: +X +6, red cross --- */
        in.vx = in.vx + 6;
        ApplyMatrixSV(mat, &in, &out);
        prim.attr = 0;
        prim.r = white; prim.g = 0; prim.b = 0;
        bx = out.vy;                                         /* $s2 = out.vy (load) */
        ay = out.vx;                                         /* $s1 = out.vx (load) */
        by = bx - 0x5D;                                      /* $s4 = out.vy - 0x5D */
        ax = ay + 0x7B;                                      /* $s0 = out.vx + 0x7B */
        bx = bx - 0x57;                                      /* $s2 = out.vy - 0x57 (in place) */
        {
        Gline_801372B0 *op = (Gline_801372B0*)&D_800A6518[(u32)aD800B9A02 * 0x14];
        __asm__("" : "=r"(op) : "0"(op));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B headers1)
        ay = ay + 0x75;                                      /* $s1 = out.vx + 0x75 (in place) */
        prim.x0 = ay; prim.y0 = by; prim.x1 = ax; prim.y1 = bx;
        aGsSortLine(&prim, op, 0);
        }
        __asm__("" : "=r"(ax) : "0"(ax));                    /* LEVER A: 2nd set kills ax's S2   */  // !FAKE: launder — NEEDED DIFFERS (P36 rung B headers1)
        __asm__("" : "=r"(by) : "0"(by));                    /* boost (same for by) -> by/ax/bx/ */  // !FAKE: launder — NEEDED DIFFERS (P36 rung B headers1)
        prim.attr = 0;                                       /* chain/ay revert to source order  */
        prim.r = white; prim.g = 0; prim.b = 0;
        prim.x0 = ax; prim.y0 = by; prim.x1 = ay; prim.y1 = bx;
        aGsSortLine(&prim, &D_800A6518[(u32)aD800B9A02 * 0x14], 0);
        /* --- corner 2: +Y axis, white line + sibling 030 --- */
        in.vx = 0;
        in.vy = 0x10;
        ApplyMatrixSV(mat, &in, &out);
        {
            register s16 vx __asm__("$7") = out.vx;          /* $a3 */  // !FAKE: pin $7 — NEEDED DIFFERS (P36 rung B headers1)
            s16 vy = out.vy;          /* $v0 */
            prim.x0 = 0x78;
            prim.attr = 0;
            prim.r = white; prim.g = white; prim.b = white;
            prim.y0 = -0x5A;
            { s16 x1v = vx + 0x78;  prim.x1 = x1v; }
            { s16 y1v = vy - 0x5A;  prim.y1 = y1v; }
            aGsSortLine(&prim, &D_800A6518[(u32)aD800B9A02 * 0x14], 0);
        }
        in.vy = in.vy + 6;
        ApplyMatrixSV(mat, &in, &out);
        aF80137030((s32)(s16)(out.vx + 0x78), (s32)(s16)(out.vy - 0x5A));
        /* --- corner 3: +Z axis, white line + sibling 178 --- */
        in.vy = 0;
        in.vz = 0x10;
        ApplyMatrixSV(mat, &in, &out);
        {
            s16 vx = out.vx;          /* $a3 */
            s16 vy = out.vy;          /* $v0 */
            prim.x0 = 0x78;
            prim.attr = 0;
            prim.r = white; prim.g = white; prim.b = white;
            prim.y0 = -0x5A;
            { s16 x1v = vx + 0x78;  prim.x1 = x1v; }
            { s16 y1v = vy - 0x5A;  prim.y1 = y1v; }
            aGsSortLine(&prim, &D_800A6518[(u32)aD800B9A02 * 0x14], 0);
        }
        in.vz = in.vz + 6;
        ApplyMatrixSV(mat, &in, &out);
        func_80137178((s32)(s16)(out.vx + 0x78), (s32)(s16)(out.vy - 0x5A));
    }
    return;
}
