void func_8017E558(void *arg0) {
    extern u8 D_801EEDC8[];
    s32 cnt2;
    s32 i;
    s32 j;
    s32 base;
    s32 p;
    s32 vel;
    s32 pos;
    u16 life;
    s32 f18;

    cnt2 = 0;
    for (i = 0; i < 8; i++) {
        {
            s32 sym = (s32)((u8 *)D_801EEDC8);
            base = sym + i * 0x1D0;
        }
        if (*(s16 *)(base) == 0) {
            *(s32 *)(base + 0xC) = *(s32 *)(base + 0xC) + 0x10000;
        }
        for (j = 0; j < 16; j++) {
            p = base + 0x10 + j * 0x1C;
            switch (*(s16 *)(p)) {
            case 0:
                vel = *(s32 *)(p + 0xC) + *(s32 *)(p + 0x10);
                pos = *(s32 *)(p + 0x14);
                life = *(u16 *)(p + 2) - 1;
                pos = pos + vel;
                *(s32 *)(p + 0x14) = pos;
                *(s32 *)(p + 0xC) = vel;
                *(u16 *)(p + 2) = life;
                if ((s16)life == -1) {
                    *(u16 *)(p) = *(u16 *)(p) + 1;
                }
                *(u16 *)(p + 4) = *(u16 *)(p + 4) + *(u16 *)(p + 6);
                *(u16 *)(p + 0xA) = *(u16 *)(p + 0xA) + 0x10;
                break;
            case 1:
                *(u16 *)(p + 4) = *(u16 *)(p + 4) + 0x80;
                f18 = *(s32 *)(p + 0x18) - 8;
                *(s32 *)(p + 0x18) = f18;
                if (f18 < 0) {
                    *(s32 *)(p + 0x18) = 0;
                    *(u16 *)(p) = *(u16 *)(p) + 1;
                }
                break;
            case 2:
                cnt2 = cnt2 + 1;
                break;
            }
        }
        func_8017E6EC(arg0);
    }
    if (cnt2 == 0x80) {
        ((void (*)(u8 *))func_80146C3C)(arg0);
    }
}
