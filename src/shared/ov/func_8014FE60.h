/* func_8014FE60 — shared body (overlay slot 0x80128158, h_exact 70e7a6e1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8014FE60(void *e) {
    extern u8 D_801152A8[];
    extern s32 func_8014FFDC(s32 e, void *a1, void *a2);
    extern s32 func_80150150(s32 e, s32 a1);
    u8 a[8];
    u8 b[8];
    u8 out[8];
    s32 r5;
    s32 r6;
    *(s16 *)(a + 0) = *(s16 *)(b + 0) = *(u16 *)(((s32)e) + 6);
    *(s16 *)(a + 2) = *(s16 *)(b + 2) = *(u16 *)(((s32)e) + 0xA) - 0x10;
    *(s16 *)(a + 4) = *(s16 *)(b + 4) = *(u16 *)(((s32)e) + 0xE);
    r5 = func_8014FFDC(((s32)e), a, out);
    r6 = func_80150150(((s32)e), (s32)b);
    if (r6 == 0) {
        *(s16 *)(b + 2) = 0x7fff;
    }
    if ((r5 | r6) != 0) {
        if (*(s16 *)(a + 2) < *(s16 *)(b + 2)) {
            __asm__ __volatile__("" ::: "memory");
            *(s16 *)(((s32)e) + 0x78) = *(u16 *)(a + 0);
            *(s16 *)(((s32)e) + 0x7a) = *(u16 *)(a + 2);
            *(s16 *)(((s32)e) + 0x7c) = *(u16 *)(a + 4);
            __builtin_memcpy((void *)(((s32)e) + 0x80), out, 8);
        } else {
            __asm__ __volatile__("" ::: "memory");
            *(s16 *)(((s32)e) + 0x78) = *(u16 *)(b + 0);
            *(s16 *)(((s32)e) + 0x7a) = *(u16 *)(b + 2);
            *(s16 *)(((s32)e) + 0x7c) = *(u16 *)(b + 4);
            __builtin_memcpy((void *)(((s32)e) + 0x80), D_801152A8, 8);
        }
        *(u16 *)(((s32)e) + 0x7e) &= 0xfffe;
        return 1;
    }
    {
        register s32 c __asm__("$3"); /* $v1 */
        register s32 t __asm__("$4"); /* $a0 */
        t = *(u16 *)(a + 0);
        c = 0x7fff;
        *(s16 *)(((s32)e) + 0x7a) = c;
        *(s16 *)(((s32)e) + 0x78) = t;
        t = *(u16 *)(a + 4);
        *(s16 *)(((s32)e) + 0x7c) = t;
        *(u16 *)(((s32)e) + 0x7e) |= 1;
    }
    return 0;
}
