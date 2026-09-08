/* func_8015E40C — shared body (overlay slot 0x80128158, h_exact 07fb5ee4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80148534(s32 a0, s32 a1);
extern void func_80149374(s32 a0, s32 a1);
void func_8015E40C(s32 a0) {
    s32 s1 = a0;
    s32 s0;
    s16 sp10[4];
    u16 sp18[4];
    s0 = *(s32 *)(s1 + 0x18C);
    if (s0 == 0) {
        return;
    }
    if (*(u16 *)(s0 + 0x0) == 0) {
        return;
    }
    func_80148534((s32)sp10, (s32)sp18);
    *(s16 *)(s0 + 0x6) = sp18[0] + *(u16 *)(*(s32 *)(s0 + 0x78) + 0xC);
    *(s16 *)(s0 + 0xA) = sp18[1] + *(u16 *)(*(s32 *)(s0 + 0x78) + 0xE);
    *(s16 *)(s0 + 0xE) = sp18[2] + *(u16 *)(*(s32 *)(s0 + 0x78) + 0x10);
    func_80149374(s1, s0 + 0x4);
}
