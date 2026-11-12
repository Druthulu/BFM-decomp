/* guess_UpdateActorModelMatrix — shared body (overlay slot 0x80128158, h_exact bda8e42f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80049CAC(s32 a0, s32 a1);
/* guess_UpdateActorModelMatrix: rebuilds object a0's model matrix: rotation from the model's +0x10 angles, translation = position + offset (+0x50..+0x54)
 * Confidence high, xref chain: func_80049CAC (libgte RotMatrixZYX per the SLUS map)(model + 0x10, model + 0x34); model +0x8.. and +0x48.. = +6/+A/+E + +0x50/+0x52/+0x54
 * Names ledger: config/names.tsv guess_UpdateActorModelMatrix */
void guess_UpdateActorModelMatrix(s32 a0)
{
    s32 a1;
    s32 p;
    s16 v;
    a1 = *(s32 *)(a0 + 0x20);
    if (a1 != 0) {
        func_80049CAC(a1 + 0x10, a1 + 0x34);
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
