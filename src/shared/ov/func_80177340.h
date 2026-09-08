/* func_80177340 — shared body (overlay slot 0x80128158, h_exact 484845ef). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u32 func_801783D0(s32 a0, s32 a1);
extern void func_801778A8(int param_1, unsigned int param_2, short param_3, short param_4);
extern u16 D_8011F830;
extern u16 D_8011F82E;
void func_80177340(s32 a0) {
    s32 v0;
    a0 += 0x50;
    func_801778A8(a0, (s16)func_801783D0(D_8011F830, 4), 3, 0xFF);
    a0 += 0x3C;
    func_801778A8(a0, (s16)func_801783D0(D_8011F82E, 4), 3, 0xFF);
    a0 += 0x3C;
    *(s16 *)(a0 + 0xC) = (u32)(D_8011F830 * 10355) >> 15;
    a0 += 0x14;
    v0 = ((s32)(D_8011F82E * 10355) << 1) >> 16;
    *(s16 *)(a0 + 0xC) = v0;
    *(s16 *)(a0 + 0x20) = v0 + 2;
}
