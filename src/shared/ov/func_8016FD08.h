/* func_8016FD08 — shared body (overlay slot 0x80128158, h_exact 7036de6d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80172658(s32 *a0);
extern void func_80146D90(s32 a0);
extern s32 func_80171990(u8 *a0);
extern void *D_8011F738;
void func_8016FD08(u8 *s0) {
    s32 *p;
    if (func_80172658((s32 *)s0)) {
        func_80146D90((s32)s0);
        *(u16 *)(s0 + 0xAC) = *(u16 *)(s0 + 0xAC) | 0x40;
        *(u16 *)(s0 + 0xAA) = *(u16 *)(s0 + 0xAA) | 0x40;
        p = (s32 *)&D_8011F738;
        if ((*p = *p - 1) == 0) {
            func_80171990(s0);
        }
    }
}
