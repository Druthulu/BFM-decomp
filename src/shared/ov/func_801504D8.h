/* func_801504D8 — shared body (overlay slot 0x80128158, h_exact 2a5244b7). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80150528(void *a0, void *a1, void *a2);
void func_801504D8(u16 *a0) {
    struct V3 a;
    struct V3 b;
    s32 t6 = a0[3];   /* 0x6 */
    s32 ta;
    s32 te;
    b.x = t6;
    a.x = t6;
    ta = a0[5];       /* 0xA */
    a.y = ta - 3;
    te = a0[7];       /* 0xE */
    b.y = ta + 1;
    b.z = te;
    a.z = te;
    func_80150528(a0, &a, &b);
}
