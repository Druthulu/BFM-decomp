/* func_8015F260 — shared body (overlay slot 0x80128158, h_exact ded9a06a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801553A8(s32 *a0);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80149048(s32 *a0);
void func_8015F260(s32 *a0) {
    s32 v;
    func_801553A8(a0);
    func_80154A74((s32)a0, 0x11);
    v = a0[0x11];
    v &= -0x3;
    v &= -0x2;
    a0[0x11] = v;
    func_80149048(a0);
    *(s16 *)((u8 *)a0 + 0xF6) = 0x1000;
}
