s32 func_800168C4(s32 arg0) {
    u8 *base = D_800AF630;

    arg0 &= 3;
    if (arg0 == 0) {
        D_800AF7CE += D_80062BA0[D_800B9A18];
    } else {
        D_800AF7CE += D_80062BA0[arg0];
    }
    if (*(u16 *) (base + 0x19E) >= 0xFFU && *(u16 *) (base + 0x188) != 0) {
        return 1;
    }
    return 0;
}
