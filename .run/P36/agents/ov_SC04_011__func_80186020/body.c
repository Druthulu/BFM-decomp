void func_80186020(void *a0) {
    s32 p;

    if ((D_801EFD40 & 2) != 0) {
        s32 a;
        s32 b;

        a = (s16)D_801EFD48;
        if (a >= 0x120) {
            *(s16 *)&D_801EFD4C = -0x60;
        } else if (a < -0x5F) {
            *(s16 *)&D_801EFD4C = 0x60;
        }
        a = D_801EFD48;
        b = D_801EFD4C;
        p = *(s32 *)((s32)a0 + 0x20);
        a = a + b;
        b = D_801EFD44;
        D_801EFD48 = a;
        b = b + a;
        *(u16 *)(p + 0x10) = b;
    } else {
        u16 x;
        u16 y;

        if ((D_801EFD40 & 1) != 0) {
            x = D_801EFD48;
            if ((s16)x >= 0x120) {
                return;
            }
            y = x + 0x60;
        } else {
            x = D_801EFD48;
            if ((s16)x < -0x5F) {
                return;
            }
            y = x - 0x60;
        }
        x = D_801EFD44;
        p = *(s32 *)((s32)a0 + 0x20);
        D_801EFD48 = y;
        x = x + y;
        *(u16 *)(p + 0x10) = x;
    }
}
