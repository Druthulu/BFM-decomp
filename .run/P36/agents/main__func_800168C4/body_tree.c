s32 func_800168C4(s32 arg0) {
    register s32 t __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
    u8 *base = D_800AF630;

    arg0 &= 3;
    if (arg0 == 0) {
        t = D_80062BA0[D_800B9A18];
    } else {
        t = D_80062BA0[arg0];
    }
    D_800AF7CE += t;
    __asm__ __volatile__("" : : : "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus9)

    t = *(u16 *) (base + 0x19E);
    if (t >= 0xFFU) {
        return *(u16 *) (base + 0x188) != 0;
    }
    return 0;
}
