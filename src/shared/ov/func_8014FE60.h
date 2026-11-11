/* func_8014FE60 — shared body (overlay slot 0x80128158, h_exact 70e7a6e1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8014FE60(void *e) {
    extern u8 guess_g_BoxHitNormalX[];
    extern s32 func_8014FFDC(s32 e, void *a1, void *a2);
    extern s32 func_80150150(s32 e, s32 a1);
    u16 a[4];
    u16 b[4];
    u16 out[4];
    s32 r5;
    s32 r6;
    a[0] = b[0] = *(u16 *)(((s32)e) + 6);
    a[1] = b[1] = *(u16 *)(((s32)e) + 0xA) - 0x10;
    a[2] = b[2] = *(u16 *)(((s32)e) + 0xE);
    r5 = func_8014FFDC(((s32)e), a, out);
    r6 = func_80150150(((s32)e), (s32)b);
    if (r6 == 0) {
        b[1] = 0x7fff;
    }
    if ((r5 | r6) != 0) {
        if ((s16)a[1] < (s16)b[1]) {
            *(s16 *)(((s32)e) + 0x78) = a[0];
            *(s16 *)(((s32)e) + 0x7a) = a[1];
            *(s16 *)(((s32)e) + 0x7c) = a[2];
            __builtin_memcpy((void *)(((s32)e) + 0x80), out, 8);
        } else {
            *(s16 *)(((s32)e) + 0x78) = b[0];
            *(s16 *)(((s32)e) + 0x7a) = b[1];
            *(s16 *)(((s32)e) + 0x7c) = b[2];
            __builtin_memcpy((void *)(((s32)e) + 0x80), guess_g_BoxHitNormalX, 8);
        }
        *(u16 *)(((s32)e) + 0x7e) &= 0xfffe;
        return 1;
    }
    {
        s32 c;
        s32 t;
        t = a[0];
        c = 0x7fff;
        *(s16 *)(((s32)e) + 0x7a) = c;
        *(s16 *)(((s32)e) + 0x78) = t;
        t = a[2];
        *(s16 *)(((s32)e) + 0x7c) = t;
        *(u16 *)(((s32)e) + 0x7e) |= 1;
    }
    return 0;
}
