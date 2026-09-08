/* func_80168AE4 — shared body (overlay slot 0x80128158, h_exact 8ee12b1d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_80168AE4(s32 a0) {
    s32 s0 = a0;
    func_80168BDC(s0, 9, 3, 2);
    func_80168BDC(s0, 9, 2, 1);
    func_80146A6C(3, (void *)s0, *(s16 *)(s0 + 0x6), *(s16 *)(s0 + 0xA),
                  *(s16 *)(s0 + 0xE), -5, 0xC0009C00);
    *(s32 *)(s0 + 0x1C) = 1;
    *(s16 *)(s0 + 0x2) = *(u16 *)(s0 + 0x2) + 1;
}
