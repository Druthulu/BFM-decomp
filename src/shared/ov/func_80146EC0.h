/* func_80146EC0 — shared body (overlay slot 0x80128158, h_exact 4722b653). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80015954(s32 a0, s32 a1);
extern void func_80149374(s32 a0, s32 a1);
extern void func_80146F58(s32 a0, s32 a1);
void func_80146EC0(s32 a0, s32 a1, s32 a2, s32 a3) {
    s32 s2 = a0;
    s32 s0 = a1;
    s32 s1 = a3;
    u16 buf[3];
    func_80015954(a2, a1);
    func_80149374(s2, s0);
    func_80146F58(s1, (s32)&buf[0]);
    *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + buf[0];
    *(u16 *)(s0 + 6) = *(u16 *)(s0 + 6) + buf[1];
    *(u16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) + buf[2];
}
