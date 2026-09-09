/* func_801536DC — shared body (overlay slot 0x80128158, h_exact fddaaac2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void (*D_8011DB28)(s32 a0);
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_80013294(void *a0, void *a1);
extern void func_80015954(s32 a0, s32 a1);
s32 func_801536DC(s32 param_1) {
    s32 s0 = param_1;
    s32 s1;
    s32 s2;
    s32 sp10[2];
    register s32 r __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B headers1)
    s32 q;
    if (D_8011DB28 != 0) {
        D_8011DB28(s0 + 0xA0);
    }
    *(s16 *)(s0 + 6) = func_80012C6C((s32)*(s16 *)(s0 + 6), (s32)*(s16 *)(s0 + 0xA0), 8);
    *(s16 *)(s0 + 0xA) = func_80012C6C((s32)*(s16 *)(s0 + 0xA), (s32)*(s16 *)(s0 + 0xA2), 8);
    {
    s32 t = func_80012C6C((s32)*(s16 *)(s0 + 0xE), (s32)*(s16 *)(s0 + 0xA4), 8);
    s32 chk = (s32)D_8011DB28;
    *(s16 *)(s0 + 0xE) = t;
    if (chk != 0) {
        s2 = s0 + 4;
        func_80015978(s2, sp10);
        s1 = s0 + 0xA0;
        q = func_80013294(sp10, (void *)s1);
        if (q < 0x40 || *(u8 *)(s0 + 0xDE) == 0) {
            func_80015954(s1, s2);
            return 0;
        }
        *(u8 *)(s0 + 0xDE) = *(u8 *)(s0 + 0xDE) - 1;
    }
    }
    r = 1;
    if (*(s16 *)(s0 + 6) == *(s16 *)(s0 + 0xA0) &&
        *(s16 *)(s0 + 0xA) == *(s16 *)(s0 + 0xA2)) {
        r = *(s16 *)(s0 + 0xE) != *(s16 *)(s0 + 0xA4);
    }
    return r;
}
