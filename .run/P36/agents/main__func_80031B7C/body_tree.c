void func_80031B7C() {
    s32 a0 = 0;
    u8 a2 = 1;
    u16 a1 = 0x7FFF;
    register u8 *v1 asm("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)

    v1 = D_800A49D2;

    do {
        if (v1[4] && !v1[2] && v1[3]) {
            v1[2] = a2;
            *(u16 *)v1 = a1;
        }
        v1 += 0x54;
        a0++;
    } while (a0 < 8);
}
