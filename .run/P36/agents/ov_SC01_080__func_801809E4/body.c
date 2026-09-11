void func_801809E4(s32 param_1) {
    s16 i;
    u8 *p;

    if (*(s32 *)(param_1 + 0x1C) != 0) {
        if ((*(s32 *)(param_1 + 0x1C) & 3) == 0) {
            func_8012913C(0x1A);
        }
        *(s32 *)(param_1 + 0x1C) = *(s32 *)(param_1 + 0x1C) - 1;
        i = 0;
        do {
            p = func_801291C0();
            if (p != 0) {
                *(u16 *)p = 0x19;
                *(u16 *)(p + 0x2C) = 0;
                *(s32 *)(p + 0x34) = (s32)&D_801C5D40 + (*(s16 *)(param_1 + 0xDC) << 5);
                *(s16 *)(param_1 + 0xDC) = *(s16 *)(param_1 + 0xDC) + 1;
                if (*(s16 *)(param_1 + 0xDC) >= 0xC0) {
                    *(s16 *)(param_1 + 0xDC) = 0;
                }
            }
            i = i + 1;
        } while (i < 1);
        {
            s16 mask = 0xFF;
            i = 0;
            do {
                p = func_801291C0();
                if (p != 0) {
                    *(u16 *)p = 0x19;
                    *(u16 *)(p + 0x2C) = mask;
                    *(s32 *)(p + 0x34) = (s32)&D_801C5D40 + (*(s16 *)(param_1 + 0xDC) << 5);
                    *(s16 *)(param_1 + 0xDC) = *(s16 *)(param_1 + 0xDC) + 1;
                    if (*(s16 *)(param_1 + 0xDC) >= 0xC0) {
                        *(s16 *)(param_1 + 0xDC) = 0;
                    }
                }
                i = i + 1;
            } while (i < 1);
        }
        {
            s16 mask = 0x1FF;
            i = 0;
            do {
                p = func_801291C0();
                if (p != 0) {
                    *(u16 *)p = 0x19;
                    *(u16 *)(p + 0x2C) = mask;
                    *(s32 *)(p + 0x34) = (s32)&D_801C5D40 + (*(s16 *)(param_1 + 0xDC) << 5);
                    *(s16 *)(param_1 + 0xDC) = *(s16 *)(param_1 + 0xDC) + 1;
                    if (*(s16 *)(param_1 + 0xDC) >= 0xC0) {
                        *(s16 *)(param_1 + 0xDC) = 0;
                    }
                }
                i = i + 1;
            } while (i < 1);
        }
        {
            s16 mask = 0x3FF;
            i = 0;
            do {
                p = func_801291C0();
                if (p != 0) {
                    *(u16 *)p = 0x19;
                    *(u16 *)(p + 0x2C) = mask;
                    *(s32 *)(p + 0x34) = (s32)&D_801C5D40 + (*(s16 *)(param_1 + 0xDC) << 5);
                    *(s16 *)(param_1 + 0xDC) = *(s16 *)(param_1 + 0xDC) + 1;
                    if (*(s16 *)(param_1 + 0xDC) >= 0xC0) {
                        *(s16 *)(param_1 + 0xDC) = 0;
                    }
                }
                i = i + 1;
            } while (i < 2);
        }
    } else {
        {
            s16 mask = 0x3FF;
            i = 0;
            do {
                p = func_801291C0();
                if (p != 0) {
                    *(u16 *)p = 0x19;
                    *(u16 *)(p + 0x2C) = mask;
                    *(s32 *)(p + 0x34) = (s32)&D_801C5D40 + (*(s16 *)(param_1 + 0xDC) << 5);
                    *(s16 *)(param_1 + 0xDC) = *(s16 *)(param_1 + 0xDC) + 1;
                    if (*(s16 *)(param_1 + 0xDC) >= 0xC0) {
                        *(s16 *)(param_1 + 0xDC) = 0;
                    }
                }
                i = i + 1;
            } while (i < 2);
        }
    }
    if (D_80127188 == 3) {
        {
            s16 mask = -0x7C01;
            i = 0;
            do {
                p = func_801291C0();
                if (p != 0) {
                    *(u16 *)p = 0x19;
                    *(u16 *)(p + 0x2C) = mask;
                    *(s32 *)(p + 0x34) = (s32)&D_801C5D40 + (*(s16 *)(param_1 + 0xDC) << 5);
                    *(s16 *)(param_1 + 0xDC) = *(s16 *)(param_1 + 0xDC) + 1;
                    if (*(s16 *)(param_1 + 0xDC) >= 0xC0) {
                        *(s16 *)(param_1 + 0xDC) = 0;
                    }
                }
                i = i + 1;
            } while (i < 0x80);
        }
        *(s32 *)(param_1 + 0x1C) = 0x40;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    }
}
