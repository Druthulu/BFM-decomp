void func_80015208(void) {
    s32 v;
    u8 *base;

    base = D_800AF630;

    if (D_800B9A64) {
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
    {
        s32 mask = 0x800;

        if (D_800B9A13 != 0) {
            return;
        }
        v = *(u16 *)&D_80078DD2 & mask;
        if (v == mask) {
            v = 1;
        } else {
            v = 0;
        }
        if (!v && D_800A5E78 != 0) {
            return;
        }
        base[0xA3E5] = 1;
        func_801281D8();
    }
}
