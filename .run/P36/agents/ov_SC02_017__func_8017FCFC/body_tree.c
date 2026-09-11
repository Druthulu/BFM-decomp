void func_8017FCFC(void *a0) {
    s32 t;
    register s32 u __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus8)
    register s32 zr __asm__("$0");  // !FAKE: pin $0 — NEEDED DIFFERS (P36 rung B tus8)
    s32 frame_pad;
    s32 k;
    s32 *p;

    (void)(s32 *)&frame_pad;
    t = *(s16 *)((s32)a0 + 0xFE);
    if (t != 0) {
        u = t + zr;
        t = u - 1;
        *(s16 *)((s32)a0 + 0xFE) = t;
        return;
    }
    k = *(u16 *)((s32)a0 + 0x5C);
    if ((k & 1) == 0) {
        return;
    }
    *(u16 *)((s32)a0 + 0x5C) = k & 0xFFFE;
    p = D_8018E204;
    t = func_800291B4(D_8018E204[(*(u16 *)((s32)a0 + 0x70)) & 0xF]) & 0xFF;
    if (t != 0) {
        *(u16 *)((s32)a0 + 0x5E) = 0;
        t = 8;
        *(s16 *)((s32)a0 + 0xFE) = t;
        return;
    }
    k = *(u16 *)((s32)a0 + 0x5E);
    if (k == 0xC) {
        __asm__("" : "=r"(p) : "0"(p));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus8)
        *(s32 *)((s32)a0 + 0x58) = (s32)D_8018E1F4 | 0x40000000 | 0x20000000;
        func_800291A0(p[(*(u16 *)((s32)a0 + 0x70)) & 0xF], 1);
        t = 0x8C00;
        *(u16 *)((s32)a0 + 0x5C) = t;
    } else {
        t = 8;
        *(s16 *)((s32)a0 + 0xFE) = t;
        if (k != 0x1D && *(s32 *)((s32)a0 + 0xDC) == 0) {
            *(s32 *)((s32)a0 + 0xDC) = 1;
            func_801746DC();
            ((void (*)(void))func_80178BF8)();
            *(s16 *)((s32)a0 + 0x2) = 2;
            func_8002D4C8(0x59D, 0);
            *(u16 *)((s32)a0 + 0x5E) = 0;
            return;
        }
    }
    *(u16 *)((s32)a0 + 0x5E) = 0;
}
