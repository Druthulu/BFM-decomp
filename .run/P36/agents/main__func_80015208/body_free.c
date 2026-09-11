void func_80015208(void) {
    u8 flag0;
    s32 v;
    u8 *base;

    flag0 = D_800B9A64;
    base = D_800AF630;

    if (flag0) {
        return;
    }
    if (D_800B9A10 != 1) {
        return;
    }
    if (D_800B9A17 != D_800B9A10) {
        return;
    }
    if (D_800B9A15 == D_800B9A17) {
        return;
    }
    if (D_800B9A16 != 0) {
        D_800B9A15 = 1;
        return;
    }
    if (D_800B9A13 != 0) {
        return;
    }

    {
        s32 mask = 0x800;

        if ((*(u16 *)&D_80078DD2 & 0x800) == mask) {
            v = 1;
        } else {
            v = 0;
        }
        if (!v) {
            if (D_800A5E78 != 0) {
                return;
            }
        }
        v = 1;
        base[0xA3E5] = v;
        func_801281D8();
    }
}
