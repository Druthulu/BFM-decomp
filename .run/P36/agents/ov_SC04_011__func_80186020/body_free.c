void func_80186020(void *a0) {
    s32 p;
    u16 x;
    /* $v0 pin (cookbook "register pin" lever): without it sched1's birthing boost
       hands $v0 to the wrong temp and the two lhu's swap registers (residual 12). */
    u16 y;

    if ((D_801EFD40 & 2) != 0) {
        if ((s16)D_801EFD48 >= 0x120) {
            *(s16 *)&D_801EFD4C = -0x60;
        } else if ((s16)D_801EFD48 < -0x5F) {
            *(s16 *)&D_801EFD4C = 0x60;
        }
        x = D_801EFD48;
        y = D_801EFD4C;
        p = *(s32 *)((s32)a0 + 0x20);
        x = x + y;
        y = D_801EFD44;
        D_801EFD48 = x;
        y = y + x;
        *(u16 *)(p + 0x10) = y;
    } else {
        if ((D_801EFD40 & 1) != 0) {
            if ((s16)D_801EFD48 >= 0x120) {
                return;
            }
            y = (s16)D_801EFD48 + 0x60;
        } else {
            if ((s16)D_801EFD48 < -0x5F) {
                return;
            }
            y = (s16)D_801EFD48 - 0x60;
        }
        x = D_801EFD44;
        p = *(s32 *)((s32)a0 + 0x20);
        D_801EFD48 = y;
        x = x + y;
        *(u16 *)(p + 0x10) = x;
    }
}
