void func_80184A68(void) {
    u8 *a0;
    a0 = &D_801AECC5;
    __asm__("" : "=r"(a0) : "0"(a0));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus7)
    if (a0[0] < 0xF8U) {
        a0[0] += 4;
        a0[-1] += 6;
        a0[1] += 4;
    }
}
