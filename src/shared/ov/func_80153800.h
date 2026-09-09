/* func_80153800 — shared body (overlay slot 0x80128158, h_exact 22b73ecc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void (*D_8011DB28)(s32 a0);
extern u8 D_80126DB0[];
extern u16 D_80126DB6;
extern void func_80015954(s32 a0, s32 a1);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_800139C8(s32 a0, void *a1, void *a2);
extern s32 func_80153978(s32 a0, u16 *src);
extern void *memcpy(void *dst, const void *src, u32 n);
s32 func_80153800(s32 a0) {
    s32 s1 = a0;
    s32 s0;
    s32 s2;
    u8 bVar1;
    s16 buf1[4];
    s16 buf2[4];
    if (D_8011DB28 != 0) {
        ((void (*)(s32, s32))func_80015978)(s1 + 4, s1 + 0x88);
        memcpy((void *)(s1 + 0x90), (void *)(s1 + 0x88), 8);
ret0:
        return 0;
    }
    bVar1 = *(u8 *)(s1 + 0xDE);
    if (bVar1 >= 0x21) {
        s32 base = (s32)D_80126DB0;
        func_80015954(base, s1 + 4);
        memcpy((void *)(s1 + 0x88), (void *)base, 8);
        memcpy((void *)(s1 + 0x90), (void *)(s1 + 0x88), 8);
        *(s16 *)(*(s32 *)(s1 + 0x20) + 0x12) = D_80126DB6;
        return 0;
    }
    {
        register s32 m __asm__("$3") = bVar1 * 4;  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B headers1)
        s2 = m;
        buf2[1] = *(u16 *)(s1 + 0xA2) - m;
    }
    for (s0 = 0; s0 < 0x80; s0++) {
        s32 ang = s0 * 0x200000;
        buf1[0] = 0;
        buf1[1] = 0;
        buf1[2] = s2;
        func_800139C8(ang >> 0x10, buf1, buf1);
        buf2[0] = *(u16 *)(s1 + 0xA0) + buf1[0];
        buf2[2] = *(u16 *)(s1 + 0xA4) + buf1[2];
        if (((s32 (*)(s32, void *))func_80153978)(s1, buf2) == 0) {
            goto ret0;
        }
    }
    *(u8 *)(s1 + 0xDE) = *(u8 *)(s1 + 0xDE) + 1;
    return 1;
}
