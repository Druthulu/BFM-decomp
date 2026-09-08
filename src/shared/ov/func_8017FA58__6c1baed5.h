/* func_8017FA58 — shared body (overlay slot 0x80128158, h_exact 6c1baed5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80184BD0(u8 a0, u8 a1, u8 a2, u8 a3);
extern void func_8017F500(void *a0);
void func_8017FA58(void *a0) {
    s32 v0;
    *(s32 *)(*(s32 *)((s32)a0 + 0xCC) + 0xB0) = 2;
    v0 = func_80184BD0(0xB, 0, 0x17, 0);
    if (v0) {
        func_8017F500(a0);
    }
}
