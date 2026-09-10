/* func_8016AA50 — shared body (overlay slot 0x80128158, h_exact 68ec3141). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80146C3C();
extern s32 D_8011D030;
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
void func_8016AA50(s32 param_1, s32 param_2) {
    short *psVar3;
    s32 iVar4;
    s32 sVar2;
    s32 t;
    if (param_2 >= 0) {
        ((s32 (*)(s32, void *, s32, s32, s32, s32, s32))func_80146A6C)(
            0x1d, (void *)param_1,
            *(s16 *)(param_1 + 0x7c), *(s16 *)(param_1 + 0x7e),
            *(s16 *)(param_1 + 0x80), 0, param_2);
        return;
    }
    iVar4 = 0;
    psVar3 = (short *)&D_8011D030;
    do {
        sVar2 = (u16)*psVar3;
        if (sVar2 == 0 || sVar2 == 3 || sVar2 == 9) {
            ((void (*)(void))func_80146C3C)();
            ((s32 (*)(s32, void *, s32, s32, s32, s32, s32))func_80146A6C)(
                0x1d, (void *)param_1,
                (s16)D_80126B5E, (s16)((u16)D_80126B62 - 0x20),
                (s16)D_80126B66, 7, 0);
            return;
        }
        t = iVar4 + 1;
        do { iVar4 = t; } while (0);
        psVar3 = psVar3 + 0x2c;
    } while ((s16)t < 0x1e);
}
