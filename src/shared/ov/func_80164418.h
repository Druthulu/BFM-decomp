/* func_80164418 — shared body (overlay slot 0x80128158, h_exact 1db8c7d3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 ratan2(s32 a0, s32 a1);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_801630C4(s32, s32, s32, s32);
extern void func_80162FC0(s32 *a0);
extern void func_80162D88(s32 *a0);
void func_80164418(s32 s0) {
    s16 v[6];
    s32 s1 = *(s32 *)(s0 + 0x20);
    s32 a1 = *(s32 *)(s0 + 0x4C);
    v[0] = *(u16 *)(a1 + 0x6) - *(u16 *)(s0 + 0x6);
    v[1] = *(u16 *)(a1 + 0xA) - (*(u16 *)(s0 + 0xA) + 0x1E);
    v[2] = *(u16 *)(a1 + 0xE) - *(u16 *)(s0 + 0xE);
    v[5] = ratan2(v[0], v[2]);
    if (v[2] < 0) {
        v[2] = -v[2];
    }
    if (v[2] == 0) {
        v[4] = 0;
    } else {
        v[4] = ratan2(-v[1], v[2]);
    }
    *(u16 *)(s1 + 0x14) = (*(u16 *)(s1 + 0x14) + 0x71) & 0xFFF;
    *(s16 *)(s1 + 0x10) = func_80012ABC(*(s16 *)(s1 + 0x10), v[4], 0x2);
    *(s16 *)(s1 + 0x12) = func_80012ABC(*(s16 *)(s1 + 0x12), v[5], 0x2);
    ((s32 (*)(s32, s32, s32, s32))func_801630C4)(s0, 0, 0, 0x8000);
    func_80162FC0((s32 *)s0);
    func_80162D88((s32 *)s0);
}
