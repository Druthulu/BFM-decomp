/* func_801588CC — shared body (overlay slot 0x80128158, h_exact 7b0e7bcb). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801588CC(int param_1) {

    extern void (*D_80181618[])(void);
    extern int D_8018E854;
    extern int D_8018E858;
    short sVar1;

    D_80181618[*(unsigned short *)(param_1 + 2)]();
    switch (D_8018E850) {
    case 0:
        break;
    case 1:
        func_800D0CA0(2);
        D_8018E858 = 0;
        D_8018E854 = 0x46;
        D_8018E850 += 1;
        break;
    case 2:
        if (D_8018E854 == 0) {
            if (SsGetMute() == 0) {
                D_8018E850 += 1;
            }
        } else {
            D_8018E854 -= 1;
        }
        break;
    case 3:
        if (func_8001AAA0(0x83) != 0) {
            D_8018E850 += 1;
        }
        break;
    case 4:
        D_8018E85C = 0;
        sVar1 = ((int (*)(int))func_80159464)(param_1);
        if (sVar1 != 0) {
            D_8018E854 = 0xd2;
        } else {
            D_8018E854 = 1;
        }
        break;
    case 5:
        D_8018E854 -= 1;
        if (D_8018E854 == -1 || D_8018E860 != 0) {
            D_8018E854 = 0;
            D_8018E850 += 1;
        }
        break;
    case 6:
        func_800D0CA0(1);
        D_8018E854 = 0x28;
        D_8018E850 += 1;
        break;
    case 7:
        if (D_8018E854 == 0) {
            if (SsGetMute() == 0) {
                D_8018E850 += 1;
            }
        } else {
            D_8018E854 -= 1;
        }
        break;
    case 8:
        D_8018E858 = 1;
        break;
    }
}
