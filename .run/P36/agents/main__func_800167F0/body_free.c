s32 func_800167F0(s32 arg0) {
    s32 v1;
    s32 x = arg0 + 0;
    u8 *s0 = D_800AF630;
    s32 mask = arg0 & 3;
    u32 raw;
    u32 a0;
    u32 v0;

    if (mask == 0) {
        v1 = D_80062BA0[D_800B9A18];
    } else {
        v1 = D_80062BA0[mask];
    }
    D_800AF7CE = D_800AF7CE + v1;
    raw = *(u16 *)&s0[0x19E];
    a0 = raw + 0;
    if (a0 >= 0xFFU) {
        a0 = 0xFF;
    }
    v0 = ((x & 0xFFFFU) < 4U) ? 0xFF - a0 : a0;
    func_80016224(v0 & 0xFF, 0);
    return *(u16 *)&s0[0x19E] >= 0xFF;
}
