void func_80185574(s32 arg0) {
    s32 self;
    register s32 zr __asm__("$0");  // !FAKE: pin $0 — NEEDED DIFFERS (P36 rung B tus8)
    s32 mask;
    s32 flag;

    self = arg0 + zr;
    flag = *(s16 *)(self + 0xAA);
    *(s16 *)(self + 0x5C) = 0;
    *(s16 *)(self + 0x98) = 0;
    *(s32 *)(self + 0x1C) = 0;
    if (flag == 0) {
        s32 p;
        register s32 f __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus8)
        mask = ~0x80;
        p = *(s32 *)(self + 0x20);
        f = *(s32 *)(self + 0xDC);
        p = *(u16 *)(p + 0x18);
        *(s32 *)(self + 0xDC) = f & mask;
        *(s16 *)(self + 0x100) = p;
    } else {
        s32 q;
        register s32 g __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus8)
        q = *(s32 *)(self + 0x20);
        g = *(s32 *)(self + 0xDC);
        q = *(u16 *)(q + 0x18);
        g |= 0x80;
        *(s32 *)(self + 0xDC) = g;
        *(s16 *)(self + 0x104) = q;
    }
}
