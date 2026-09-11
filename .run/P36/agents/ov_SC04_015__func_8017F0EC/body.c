void func_8017F0EC(s32 a0) {
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern s32 func_80013328(s32 a0, s32 a1);
    extern s32 func_80128ED8(s32 param_1, s32 *param_2);
    extern s32 VectorNormalSS(void *a0, void *a1);
    extern s32 func_800132BC(void *a0, void *a1);
    extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
    extern s32 func_80132EF4(s32 arg0, s32 arg1);
    extern u8 D_80126B5C;
    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern u16 D_801C8B64;
    extern u16 D_801C8B66;
    extern u16 D_801C8B68;
    extern s16 D_801C8B70;
    extern s32 D_801C8B78;
    u16 sp18[3];
    u16 sp20[3];
    u16 *q;
    s32 v0;
    s32 p;
    s32 t;
    s32 d;

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        v0 = func_80013328(a0 + 4, (s32)&D_80126B5C);
        if (v0 < D_801C8B78) {
            D_801C8B78 = v0;
        }
        q = sp18;
        q[0] = *(u16 *)(a0 + 0x6);
        q[1] = *(u16 *)(a0 + 0xA);
        q[2] = *(u16 *)(a0 + 0xE);
        sp20[0] = D_80126B5E;
        sp20[1] = D_80126B62;
        sp20[2] = D_80126B66;
        if (func_800132BC(sp20, q) < 0x401) {
            D_801C8B64 = sp20[0] - q[0];
            D_801C8B66 = sp20[1] - q[1];
            D_801C8B68 = sp20[2] - q[2];
            VectorNormalSS(&D_801C8B64, &D_801C8B64);
            func_8012F568(1, 0x4201, 0, 4, (s32)q, (s32)&D_801C8B64);
        }
        v0 = *(u16 *)(a0 + 0x76) + 1;
        *(u16 *)(a0 + 0x76) = v0;
        if ((s16)v0 > 0x64) {
            *(u16 *)(a0 + 0x76) = 0x64;
        }
        if (*(u16 *)(a0 + 0x5C) & 1) {
            if (*(u16 *)(a0 + 0x5E) == 0x23) {
                v0 = *(u16 *)(a0 + 0x76) - 8;
                *(u16 *)(a0 + 0x76) = v0;
                if ((s16)v0 > 0) {
                    *(u16 *)(a0 + 0x34) = 1;
                    *(s32 *)(a0 + 0x1C) = 3;
                    func_8002D4C8(0x76D, 0);
                } else {
                    t = (u16)D_801C8B70;
                    *(u16 *)(a0 + 0x34) = 2;
                    *(u16 *)(a0 + 0x5C) = 0;
                    *(u16 *)(a0 + 0x76) = 0;
                    D_801C8B70 = t - 1;
                    func_8002D4C8(0x76B, 0);
                    func_80132EF4(a0, 0x4E);
                    func_8002D4C8(4, 0x76C);
                }
            }
        }
        break;
    case 1:
        v0 = func_80013328(a0 + 4, (s32)&D_80126B5C);
        if (v0 < D_801C8B78) {
            D_801C8B78 = v0;
        }
        v0 = *(u16 *)(a0 + 0x76) + 1;
        *(u16 *)(a0 + 0x76) = v0;
        if ((s16)v0 > 0x64) {
            *(u16 *)(a0 + 0x76) = 0x64;
        }
        v0 = *(s32 *)(a0 + 0x1C) - 1;
        *(s32 *)(a0 + 0x1C) = v0;
        if (v0 == 0) {
            *(u16 *)(a0 + 0x34) = 0;
        }
        *(u16 *)(a0 + 0x5C) = 0x8000;
        break;
    case 2:
        *(u16 *)(a0 + 0x5C) = 0;
        break;
    }
    d = (*(s16 *)(a0 + 0x76) * 12288) / 100;
    p = *(s32 *)(a0 + 0xCC);
    *(u16 *)(p + 0x1A) = d;
    *(u16 *)(p + 0x18) = d;
    p = *(s32 *)(a0 + 0xCC);
    *(u16 *)(p + 0x8) = *(u16 *)(a0 + 0x6);
    *(u16 *)(p + 0xA) = *(u16 *)(a0 + 0xA);
    *(u16 *)(p + 0xC) = *(u16 *)(a0 + 0xE);
    func_80128ED8(p, (s32 *)(a0 + 0xD0));
}
