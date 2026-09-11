void func_80182498(s32 a0) {

    extern s16 D_801AAB60;
    extern s16 D_801AAB62;
    extern u8 D_801AAB68;
    extern u8 D_801AAB69;
    extern u8 D_801AAB6A;

    extern s16 D_801AAB6C;
    extern u8 *D_800A5E60;
    extern s32 D_800AE620;
    extern u8 D_800A6518[];
    extern Ot_8018B23C_80182498 D_800A651C[];

    s32 m[8];       /* sp+0x10 */
    u8 sv[8];       /* sp+0x30 */
    u16 out[4];     /* sp+0x38 */
    s32 scale[4];   /* sp+0x40 */

    u8 *q;
    Rec_8018B23C_80182498 *p;
    s32 x;
    s32 y;

    q = D_800A5E60;

    *(Mat32_8018B23C_80182498 *)m = *(Mat32_8018B23C_80182498 *)&D_800AE620;

    D_800A5E60 = q + 0x14;
    *(u8 *)(q + 3) = 4;
    *(u8 *)(q + 7) = 0x22;
    *(u8 *)(q + 4) = D_801AAB68;
    *(u8 *)(q + 5) = D_801AAB69;
    *(u8 *)(q + 6) = D_801AAB6A;

    p = (Rec_8018B23C_80182498 *)((s32)&D_801AAB6C + (a0 << 4));
    x = p->fA + (u16)D_801AAB60;
    y = p->fE + (u16)D_801AAB62;
    RotMatrixZ(p->f6, m);

    scale[0] = *(s16 *)((s32)p + 2);
    scale[1] = *(s16 *)((s32)p + 2);
    scale[2] = *(s16 *)((s32)p + 2);
    func_8004901C(m, scale);

    *(s16 *)(sv + 4) = 0;
    *(s16 *)(sv + 2) = 0;
    *(s16 *)(sv + 0) = p->f0;
    ApplyMatrixSV(m, sv, out);

    *(s16 *)(q + 0x8) = x + ((s16)out[0] >> 1) * 3;
    *(s16 *)(q + 0xA) = y + ((s16)out[1] >> 1) * 3;
    *(s16 *)(q + 0xC) = x - ((s16)out[0] >> 1);
    *(s16 *)(q + 0xE) = y - ((s16)out[1] >> 1);
    x = x + out[0];
    *(s16 *)(q + 0x10) = x;
    y = y + out[1];
    *(s16 *)(q + 0x12) = y;

    if (p->f0 & 1) {
        RotMatrixZ(0x400, m);
    } else {
        RotMatrixZ(-0x400, m);
    }

    *(s16 *)(sv + 0) = 2;
    ApplyMatrixSV(m, sv, out);

    *(s16 *)(q + 0x10) = *(u16 *)(q + 0x10) + out[0];
    *(s16 *)(q + 0x12) = *(u16 *)(q + 0x12) + out[1];

    {
        Bidx_8018B23C_80182498 *bp = (Bidx_8018B23C_80182498 *)&D_800B9A02;

        /* addPrim(&D_800A651C[bp->f].a[0x10], q) */
        ((PTag_8018B23C_80182498 *)q)->addr =
            ((PTag_8018B23C_80182498 *)(D_800A651C[bp->f].a + 0x40))->addr;
        ((PTag_8018B23C_80182498 *)(D_800A651C[bp->f].a + 0x40))->addr = (u32)q;
        func_80016638(&D_800A6518[bp->f * 20], 0x10, 1);
    }
}
