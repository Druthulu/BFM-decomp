/* func_80148980 — shared body (overlay slot 0x80128158, h_exact 654c631e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80148980(u8 *a0) {
    u8 c;
    s32 v0;
    c = a0[0xA9];
    switch (c) {
    case 0x41:
        v0 = *(u16 *)(a0 + 0xAA) & 0x4000;
        break;
    case 0x53:
    case 0x73:
        v0 = ((u32)*(u16 *)(a0 + 0xAE) >> 8) < 0xC1;
        v0 = v0 ^ 1;
        break;
    default:
        v0 = 0;
        break;
    }
    return v0;
}
