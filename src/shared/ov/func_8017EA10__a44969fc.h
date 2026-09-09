/* func_8017EA10 — shared body (overlay slot 0x80128158, h_exact a44969fc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017EA10(s32 *a0) {
    s32 *s0 = a0;
    s32 result;

    if (func_8017EC2C((s32)a0) < 400) {
        result = func_8013767C((s32)&D_80183058);
        s0[0x198 / 4] = result;
        func_80154274(s0, (s32)D_80182D0C);
        func_80147324(0x7E7);
        func_80171990((u8 *)s0);
    }
}
