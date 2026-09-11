void func_8017E2CC(s32 param_1) {
    s32 *s2 = &D_80126B58;
    s32 *s1 = &D_800AE6A8;
    register s32 v1 asm("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus7)
    register s32 v0 asm("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus7)

    if (D_801C8B74 != 0) {
        v1 = D_801C8B78;
        if (v1 == 0x7FFF) {
            func_8002D4C8(4, 0x76C);
        } else {
            if (v1 >= 0x300) {
                func_8002D4C8(4, 0x76C);
            } else if (v1 < 0x101) {
                func_8002D4C8(0x76C, 0x107F);
            } else {
                v0 = 0x300 - v1;
                v1 = (v0 << 7) - v0;
                func_8002D4C8(0x76C, (v1 / 512 & 0x7F) | 0x1000);
            }
            D_801C8B78 = 0x7FFF;
        }
        switch (D_801C8B60) {
        case 0:
            if (func_800CF8B4() != 0) {
                if ((s1[2] & 0x80FFFFFF) == 0 && (s2[0x11] & 0x8000000) != 0) {
                    func_8014CBE8();
                    func_80178B18(param_1, &D_80188590);
                    D_801C8B60 = 1;
                }
            }
            break;
        case 1:
            func_801789AC(param_1);
            break;
        }
    } else {
        D_801C8B60 = 0;
        func_8017EA2C();
        func_8017ED28();
        v1 = D_801C8B78;
        if (v1 == 0x7FFF) {
            func_8002D4C8(4, 0x76C);
        } else {
            if (v1 >= 0x300) {
                func_8002D4C8(4, 0x76C);
            } else if (v1 < 0x101) {
                func_8002D4C8(0x76C, 0x107F);
            } else {
                v0 = 0x300 - v1;
                v1 = (v0 << 7) - v0;
                func_8002D4C8(0x76C, (v1 / 512 & 0x7F) | 0x1000);
            }
            D_801C8B78 = 0x7FFF;
        }
    }
}
