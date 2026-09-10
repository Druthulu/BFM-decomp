/* func_80166690 — shared body (overlay slot 0x80128158, h_exact 8e3d7914). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
// @class: count
// @crack: MATCH. Every accumulator here is a short, not an int: sVar7/sVar8/sVar9/sVar3 are
// `short`, the colour temp `t` is `u8` (the field width) and `w` is `int`. The four `short`s are
// what emit the target's `move s2,v0` / `move s0,v0` / `move s3,v1` copies — `short v = <int expr>`
// is an SI->HI truncation whose SImode source is still live in the following `sll/sra` test, so
// local-alloc refuses the tie (local-alloc.c:1855) and the copy survives. Writing them as `int`
// (or as `unsigned int` with a hand temp) loses those four copies. `t` must be `u8` and not
// `short`: at `short` it shares uVar7's cse quantity (cse.c:1029) and canon_reg forwards $s0 into
// the first `sb`; at `u8` the mode gate keeps it separate and the `sb` reads the copy. No levers.
s32 func_80166690(s32 param_1, s32 param_2)
{
    extern s32 func_80017758(void *a0, void *a1);
    extern Blk20 D_800AE620;
    extern u8 D_8018E9E0[];

    Frame_80166690_80166690 c;
    Blk20 blk;
    Rec_80166690_80166690 *sub;
    Rec_80166690_80166690 *pv;
    u8 *rec;
    int i6;
    int lt2;
    int p2;
    short sVar7, sVar8, sVar9;
    short sVar3;
    int w;
    u8 t;
    short sVar10;

    blk = D_800AE620;
    i6 = (short)param_1;
    c.tag = 0x50000000;
    rec = &D_8018E9E0[i6 * 0xC4];
    sVar10 = 0;
    if (rec[0] == 0) {
        return 0;
    }
    sub = (Rec_80166690_80166690 *)(rec + 4);
    sVar9 = rec[1];
    sVar8 = rec[3];
    sVar7 = sVar8 >> 1;
    sVar3 = rec[2];
    sVar3 = sVar3 - 1;
    if (sVar3 != -1) {
        lt2 = i6 < 2;
        p2 = (short)param_2;
        do {
            pv = &sub[sVar9];
            c.v0 = pv->h[0];
            c.v1 = pv->h[1];
            c.v2 = pv->h[2];
            c.w0 = pv->h[3];
            c.w1 = pv->h[4];
            c.w2 = pv->h[5];
            sVar10 = sVar10 + 1;

            if (lt2) {
                if (p2 == 0) {
                    t = sVar8;
                    c.c12 = t; c.c02 = t;
                    t = sVar7;
                } else {
                    w = (sVar8 >> 1) + (sVar8 >> 3);
                    sVar7 = w;
                    c.c12 = w; c.c02 = w;
                    t = sVar8;
                }
                c.c11 = t; c.c01 = t; c.c10 = t; c.c00 = t;
            } else {
                t = sVar8;
                c.c10 = t; c.c00 = t;
                t = sVar7;
                c.c12 = t; c.c02 = t; c.c11 = t; c.c01 = t;
            }

            sVar9 = sVar9 - 1;
            if (sVar9 < 0) {
                sVar9 = 0xF;
            }
            pv = &sub[sVar9];
            c.v3 = pv->h[0];
            c.v4 = pv->h[1];
            c.v5 = pv->h[2];
            c.w3 = pv->h[3];
            c.w4 = pv->h[4];
            sVar8 = sVar8 - 0x10;
            sVar7 = sVar7 - 0x10;
            c.w5 = pv->h[5];
            if (sVar7 < 0) {
                sVar7 = 0;
            }

            if (lt2) {
                if (p2 == 0) {
                    t = sVar8;
                    c.c32 = t; c.c22 = t;
                    t = sVar7;
                } else {
                    t = sVar7;
                    c.c32 = t; c.c22 = t;
                    t = sVar8;
                }
                c.c31 = t; c.c21 = t; c.c30 = t; c.c20 = t;
            } else {
                t = sVar8;
                c.c30 = t; c.c20 = t;
                t = sVar7;
                c.c32 = t; c.c22 = t; c.c31 = t; c.c21 = t;
            }

            func_80017758(&c, &blk);
            sVar3 = sVar3 - 1;
        } while (sVar3 != -1);
    }
    return sVar10;
}
