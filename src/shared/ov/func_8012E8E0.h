/* guess_SetObjectPosAndYaw — shared body (overlay slot 0x80128158, h_exact dc672e82). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void RotMatrixZYX(s32 a0, s32 a1);
/* guess_SetObjectPosAndYaw: places object a0 at a1's x, y, z (whole units) with y rotation a1[3], and rebuilds its model's matrix and translation
 * Confidence medium, xref chain: +6/+A/+E = a1[0..2], +4/+8/+C = 0; model +0x12 = a1[3]; RotMatrixZYX(model+0x10, model+0x34); model +0x48.. = pos + +0x50..
 * Names ledger: config/names.tsv guess_SetObjectPosAndYaw */
void guess_SetObjectPosAndYaw(s32 a0, s32 a1)
{
    s32 v1;
    s32 p;
    s16 v;
    u16 e;
    v1 = *(s32 *)(a0 + 0x20);
    *(s16 *)(a0 + 0x6) = *(u16 *)(a1 + 0x0);
    *(s16 *)(a0 + 0xA) = *(u16 *)(a1 + 0x2);
    e = *(u16 *)(a1 + 0x4);
    *(s16 *)(a0 + 0xC) = 0;
    *(s16 *)(a0 + 0x8) = 0;
    *(s16 *)(a0 + 0x4) = 0;
    *(s16 *)(a0 + 0xE) = e;
    if (v1 != 0) {
        *(s16 *)(v1 + 0x12) = *(u16 *)(a1 + 0x6);
        a1 = *(s32 *)(a0 + 0x20);
        if (a1 != 0) {
            RotMatrixZYX(a1 + 0x10, a1 + 0x34);
            p = *(s32 *)(a0 + 0x20);
            v = *(u16 *)(a0 + 0x6) + *(u16 *)(a0 + 0x50);
            *(s16 *)(p + 0x8) = v;
            *(s32 *)(p + 0x48) = v;
            v = *(u16 *)(a0 + 0xA) + *(u16 *)(a0 + 0x52);
            *(s16 *)(p + 0xA) = v;
            *(s32 *)(p + 0x4C) = v;
            v = *(u16 *)(a0 + 0xE) + *(u16 *)(a0 + 0x54);
            *(s16 *)(p + 0xC) = v;
            *(u16 *)(p + 0x2C) = *(u16 *)(p + 0x2C) | 1;
            *(s32 *)(p + 0x50) = v;
        }
    }
}
