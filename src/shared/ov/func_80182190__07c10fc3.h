/* func_80182190 — shared body (overlay slot 0x80128158, h_exact 07c10fc3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_800167B8(s32 a0);
extern void func_801824E0(void *a0);
extern s32 D_801E8770;
s32 func_80182190(s32 param_1) {
    D_801E8770 = 0;
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801824E0, 0x1000000);
    func_800167B8(0);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    return 0;
}
