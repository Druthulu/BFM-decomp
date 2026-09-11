void func_8017FCFC(void *a0) {
    s32 k;

    if (*(s16 *)((s32)a0 + 0xFE) != 0) {
        *(s16 *)((s32)a0 + 0xFE) -= 1;
        return;
    }
    k = *(u16 *)((s32)a0 + 0x5C);
    if ((k & 1) == 0) {
        return;
    }
    *(u16 *)((s32)a0 + 0x5C) = k & 0xFFFE;
    if ((func_800291B4(D_8018E204[*(u16 *)((s32)a0 + 0x70) & 0xF]) & 0xFF) != 0) {
        *(u16 *)((s32)a0 + 0x5E) = 0;
        *(s16 *)((s32)a0 + 0xFE) = 8;
        return;
    }
    k = *(u16 *)((s32)a0 + 0x5E);
    if (k == 0xC) {
        *(s32 *)((s32)a0 + 0x58) = (s32)D_8018E1F4 | 0x40000000 | 0x20000000;
        func_800291A0(D_8018E204[*(u16 *)((s32)a0 + 0x70) & 0xF], 1);
        *(u16 *)((s32)a0 + 0x5C) = 0x8C00;
    } else {
        *(s16 *)((s32)a0 + 0xFE) = 8;
        if (k != 0x1D && *(s32 *)((s32)a0 + 0xDC) == 0) {
            *(s32 *)((s32)a0 + 0xDC) = 1;
            func_801746DC();
            ((void (*)(void))func_80178BF8)();
            *(s16 *)((s32)a0 + 0x2) = 2;
            func_8002D4C8(0x59D, 0);
            *(u16 *)((s32)a0 + 0x5E) = 0;
            return;
        }
    }
    *(u16 *)((s32)a0 + 0x5E) = 0;
}
