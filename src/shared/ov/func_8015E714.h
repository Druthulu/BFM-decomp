/* func_8015E714 — shared body (overlay slot 0x80128158, h_exact 288bb7ed). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);
extern void func_801553C0(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_80154A74(s32 a0, s32 a1);
void func_8015E714(s32 *a0) {
    s16 sp18[4];
    s16 sp20[4];
    s32 s0;
    if (*(s32 *)((s32)a0 + 0x234) == 0) {
        s0 = *(s32 *)((s32)a0 + 0x18C);
        if (s0 != 0) {
            sp18[0] = *(u16 *)((s32)a0 + 0x6);
            sp18[1] = *(u16 *)((s32)a0 + 0xA) - 0x14;
            sp18[2] = *(u16 *)((s32)a0 + 0xE);
            sp20[0] = *(u16 *)(s0 + 0x6);
            sp20[1] = *(u16 *)(s0 + 0xA);
            sp20[2] = *(u16 *)(s0 + 0xE);
            if (func_80133784(0, sp18, (s32)sp20) != 0) {
                *(s16 *)(s0 + 0x6) = sp20[0];
                *(s16 *)(s0 + 0xA) = sp20[1];
                *(s16 *)(s0 + 0xE) = sp20[2];
            }
            func_80015978(s0 + 0x4, (s32 *)sp18);
            sp18[3] = 0;
            func_8014C4AC(s0, 0x1C, 0, sp18, *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12));
            *(s32 *)((s32)a0 + 0x18C) = 0;
        }
    }
    func_801553C0((s32)a0);
    func_80155440(a0);
    *(s32 *)((s32)a0 + 0x44) = *(s32 *)((s32)a0 + 0x44) & -3;
    func_80154A74((s32)a0, 0x11);
    *(s32 *)((s32)a0 + 0x44) = *(s32 *)((s32)a0 + 0x44) & -3;
}
