int func_8017A3D8(void)
{
    switch (D_801EEC94) {
    case 0:
        func_800D0CA0(1);
        D_801EEC94 = D_801EEC94 + 1;
        return 0;
    case 100:
    {
        register int a __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B t3_tus1)
        a = D_801EEC90;
        if (a != -1) {
            return func_8001AAA0() != 0;
        }
        return func_800D0CE0() == 1;
    }
    default:
        D_801EEC94 = D_801EEC94 + 1;
        if (D_801EEC94 < 0x1E) {
            return 0;
        }
        D_801EEC94 = 100;
        return 0;
    }
}
