/* func_80169E44 — shared body (overlay slot 0x80128158, h_exact a2923d0d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_80146C3C();
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_80169E44(s32 a0) {
    s32 r;
    s32 p;
    if (func_80128ED8((void *)*(s32 *)(a0 + 0x20), (void *)(a0 + 0x24)) != 0) {
        ((void (*)(s32))func_80146C3C)(a0);
        return;
    }
    r = *(s32 *)(a0 + 0x1C);
    *(s32 *)(a0 + 0x1C) = r + 1;
    if (r < 3) {
        p = func_80146A6C(9, (void *)a0, *(s16 *)(a0 + 0x6),
                          *(s16 *)(a0 + 0xA),
                          *(s16 *)(a0 + 0xE),
                          *(s32 *)(a0 + 0x1C) & 1, 0);
        if (p != 0) {
            *(s16 *)(p + 0x12) = *(u16 *)(a0 + 0x12);
            *(s16 *)(p + 0x16) = *(u16 *)(a0 + 0x16);
            *(s16 *)(p + 0x1A) = *(u16 *)(a0 + 0x1A);
        }
    }
}
