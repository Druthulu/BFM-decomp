s32 func_800167F0(s32 arg0) {
    u16 x = arg0;
    u8 *base = D_800AF630;
    s32 mask = arg0 & 3;
    u32 raw;
    u32 v;
    u32 level;

    if (mask == 0) {
        D_800AF7CE += D_80062BA0[D_800B9A18];
    } else {
        D_800AF7CE += D_80062BA0[mask];
    }
    raw = *(u16 *)(base + 0x19E);
    if (raw >= 0xFF) {
        v = 0xFF;
    } else {
        v = raw;
    }
    level = (x < 4) ? 0xFF - v : v;
    func_80016224(level & 0xFF, 0);
    return *(u16 *)(base + 0x19E) >= 0xFF;
}
