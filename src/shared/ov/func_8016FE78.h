/* func_8016FE78 — shared body (overlay slot 0x80128158, h_exact f7a5de7a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801477E8(s32 *a0, s32 a1);
extern s32 func_80171990(u8 *a0);
extern u16 D_8011F73E;
s32 func_8016FE78(s32 *a0) {
    *(u16 *)((s32)a0 + 0xAA) |= 0x40;
    if (D_8011F73E != 0) {
        func_801477E8(a0, D_8011F73E << 16);
    }
    return func_80171990((u8 *)a0);
}
