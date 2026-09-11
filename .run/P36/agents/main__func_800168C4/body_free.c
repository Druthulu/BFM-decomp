s32 func_800168C4(s32 arg0) {
    s32 t;
    u8 *base = D_800AF630;

    arg0 &= 3;
    if (arg0 == 0) {
        t = D_80062BA0[D_800B9A18];
    } else {
        t = D_80062BA0[arg0];
    }
    D_800AF7CE += t;

    t = *(u16 *) (base + 0x19E);
    if (t >= 0xFFU) {
        return *(u16 *) (base + 0x188) != 0;
    }
    return 0;
}
