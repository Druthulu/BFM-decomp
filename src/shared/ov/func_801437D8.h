/* func_801437D8 — shared body (overlay slot 0x80128158, h_exact d5542b9f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 *func_8012913C(s32 a0);
extern s32 rand(void);
void func_801437D8(s32 a0, s32 a1, s32 a2, s32 a3) {
    u8 *s0;
    s32 r;
    s32 d0, d1, d2;
    s32 t;
    s32 pad[6];
    (void)pad;
    if ((*(u16 *)(a0 + 0) & (s16)((1 << a3) - 1)) == 0) {
        s0 = func_8012913C(0x23);
        if (s0 != 0) {
            r = rand();
            d0 = *(s16 *)(a2 + 0);
            *(s16 *)(s0 + 6) = (*(u16 *)(a1 + 0) + (r % (d0 << 1))) - d0;
            r = rand();
            d1 = *(s16 *)(a2 + 2);
            *(s16 *)(s0 + 0xA) = (*(u16 *)(a1 + 2) + (r % (d1 << 1))) - d1;
            r = rand();
            d2 = *(s16 *)(a2 + 4);
            t = *(u16 *)(a1 + 4);
            *(s32 *)(s0 + 0x18) = 0;
            *(s32 *)(s0 + 0x14) = 0;
            *(s32 *)(s0 + 0x10) = 0;
            *(s16 *)(s0 + 0xE) = (t + (r % (d2 << 1))) - d2;
            *(s16 *)(s0 + 0x34) = *(u16 *)(a1 + 6);
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x2C) = 0xC008;
        }
    }
    *(u16 *)(a0 + 0) += 1;
}
