int func_8017A3D8(void)
{
    switch (D_801EEC94) {
    case 0:
        func_800D0CA0(1);
        D_801EEC94 = D_801EEC94 + 1;
        return 0;
    case 100:
    {
        int a;
        a = D_801EEC90;
        if (a != -1) {
            return ((int (*)(int))func_8001AAA0)(a) != 0;
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
