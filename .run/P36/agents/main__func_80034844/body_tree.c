void func_80034844(void)
{
    u8 *a0 = (u8 *)D_800A46E8;
    int a1 = 0;
    int t0 = 0x5;
    int a3 = 0x1;
    int a2 = 0x220;
    register u8 *v1 __asm__("$3") = (u8 *)D_800A46E8 + 0x1A;  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)

    while (a1 < 8) {
        if (*(u16 *)a0 == t0) {
            u8 b = *(u8 *)(v1 + 0x1D);
            if ((b & 0x2) == 0) {
                *(u8 *)(v1 - 0x4) = a3;
                *(u16 *)v1 = a2;
            }
        }
        a1++;
        v1 += 0x54;
        a0 += 0x54;
    }
}
