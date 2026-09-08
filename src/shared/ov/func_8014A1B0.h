/* func_8014A1B0 — shared body (overlay slot 0x80128158, h_exact 7012b59d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80015978(s32 a0, s32 *a1);
extern u16 func_80156370(u16 a0);
extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);
void func_8014A1B0(s32 a0, s32 a1) {
    s16 sp18[4];
    u16 tmp;
    func_80015978(a0 + 4, (s32 *)sp18);
    sp18[3] = 0;
    tmp = func_80156370(0xA);
    func_8014C4AC(a1, 0xA, tmp, sp18, *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12));
}
