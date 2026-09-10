s32 func_80166690(s32 param_1, s32 param_2)
{
    extern s32 func_80017758(void *a0, void *a1);
    extern Blk20 D_800AE620;
    extern u8 D_801EDD28[];

    Frame_80166690_80166690 c;
    Blk20 blk;
    Rec_80166690_80166690 *sub;
    Rec_80166690_80166690 *pv;
    u8 *rec;
    int i6;
    int lt2;
    int p2;
    short uVar7, uVar8, uVar9;
    short iVar3;
    int w;
    u8 t;
    short sVar10;

    blk = D_800AE620;
    i6 = (short)param_1;
    c.tag = 0x50000000;
    rec = &D_801EDD28[i6 * 0xC4];
    sVar10 = 0;
    if (rec[0] == 0) {
        return 0;
    }
    sub = (Rec_80166690_80166690 *)(rec + 4);
    uVar9 = rec[1];
    uVar8 = rec[3];
    uVar7 = uVar8 >> 1;
    iVar3 = rec[2];
    iVar3 = iVar3 - 1;
    if (iVar3 != -1) {
        lt2 = i6 < 2;
        p2 = (short)param_2;
        do {
            pv = &sub[uVar9];
            c.v0 = pv->h[0];
            c.v1 = pv->h[1];
            c.v2 = pv->h[2];
            c.w0 = pv->h[3];
            c.w1 = pv->h[4];
            c.w2 = pv->h[5];
            sVar10 = sVar10 + 1;

            if (lt2) {
                if (p2 == 0) {
                    t = uVar8;
                    c.c12 = t; c.c02 = t;
                    t = uVar7;
                } else {
                    w = (uVar8 >> 1) + (uVar8 >> 3);
                    uVar7 = w;
                    c.c12 = w; c.c02 = w;
                    t = uVar8;
                }
                c.c11 = t; c.c01 = t; c.c10 = t; c.c00 = t;
            } else {
                t = uVar8;
                c.c10 = t; c.c00 = t;
                t = uVar7;
                c.c12 = t; c.c02 = t; c.c11 = t; c.c01 = t;
            }

            uVar9 = uVar9 - 1;
            if (uVar9 < 0) {
                uVar9 = 0xF;
            }
            pv = &sub[uVar9];
            c.v3 = pv->h[0];
            c.v4 = pv->h[1];
            c.v5 = pv->h[2];
            c.w3 = pv->h[3];
            c.w4 = pv->h[4];
            uVar8 = uVar8 - 0x10;
            uVar7 = uVar7 - 0x10;
            c.w5 = pv->h[5];
            if (uVar7 < 0) {
                uVar7 = 0;
            }

            if (lt2) {
                if (p2 == 0) {
                    t = uVar8;
                    c.c32 = t; c.c22 = t;
                    t = uVar7;
                } else {
                    t = uVar7;
                    c.c32 = t; c.c22 = t;
                    t = uVar8;
                }
                c.c31 = t; c.c21 = t; c.c30 = t; c.c20 = t;
            } else {
                t = uVar8;
                c.c30 = t; c.c20 = t;
                t = uVar7;
                c.c32 = t; c.c22 = t; c.c31 = t; c.c21 = t;
            }

            func_80017758(&c, &blk);
            iVar3 = iVar3 - 1;
        } while (iVar3 != -1);
    }
    return sVar10;
}
