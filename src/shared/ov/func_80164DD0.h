/* func_80164DD0 — shared body (overlay slot 0x80128158, h_exact 92afe6e5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80148534(s32 a0, s32 a1);
extern void func_80015954(s32 a0, s32 a1);
extern void func_80149374(s32 a0, s32 a1);
void func_80164DD0(s32 a0) {
    s32 sp10[2];
    s32 sp18[2];
    s32 s2 = *(s32 *)(a0 + 0x4C);
    func_80148534((s32)sp10, (s32)sp18);
    func_80015954((s32)sp10, a0 + 4);
    func_80149374(s2, a0 + 4);
    *(s16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) - 0x40;
}
