/* func_8014FA70 — shared body (overlay slot 0x80128158, h_exact 2d021526). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern s32 func_80029178(s32 a0);
extern u8 D_801152A8[];
extern s16 D_801152B0;
extern s32 D_801152BC;
s32 func_8014FA70(s32 a0) {
    s32 s1;
    s32 v0;
    u8 in[8];
    u8 out[8];
    *(s16 *)(in + 0x0) = *(u16 *)(a0 + 0x88);
    *(s16 *)(in + 0x2) = *(u16 *)(a0 + 0x8A);
    *(s16 *)(in + 0x4) = *(u16 *)(a0 + 0x8C);
    *(s16 *)(out + 0x0) = *(u16 *)(a0 + 0x6);
    *(s16 *)(out + 0x2) = *(u16 *)(a0 + 0xA);
    *(s16 *)(out + 0x4) = *(u16 *)(a0 + 0xE);
    s1 = func_80133784(1, &in[0], (s32)&out[0]);
    if (s1 != 0) {
        *(s16 *)(a0 + 0x6) = *(u16 *)(out + 0x0);
        *(s16 *)(a0 + 0xA) = *(u16 *)(out + 0x2);
        *(s16 *)(a0 + 0xE) = *(u16 *)(out + 0x4);
        v0 = *(u8 *)(out + 0x6);
        if (v0 != 0) {
            *(s16 *)(a0 + 0x16C) = v0;
        }
        *(s16 *)(a0 + 0x16E) = *(u16 *)(out + 0x6) >> 13;
        if (*(u16 *)(a0 + 0x16C) == 0x1D) {
            if ((func_80029178(0x21) & 0xFF) == 0) {
                s1 &= ~0x2000;
                s1 |= 0x4000;
                __builtin_memcpy(&D_801152B0, &D_801152A8[0], 8);
                D_801152BC = 1;
            }
        }
        return s1;
    }
    v0 = *(u8 *)(out + 0x6);
    if (v0 != 0) {
        *(s16 *)(a0 + 0x16C) = v0;
    }
    return 0;
}
