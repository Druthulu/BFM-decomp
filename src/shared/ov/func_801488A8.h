/* func_801488A8 — shared body (overlay slot 0x80128158, h_exact 0932c9ba). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_801488A8(u8 *a0) {
    u8 c;
    s32 v0;
    u32 h;
    s32 lo;
    c = a0[0xA9];
    switch (c) {
    case 0x41:
        v0 = *(u16 *)(a0 + 0xAA) & 0xF000;
        break;
    case 0x53:
    case 0x73:
        h = *(u16 *)(a0 + 0xAE);
        lo = h & 0xFF;
        if (lo != 0x80) {
            return 1;
        }
        if ((s32)(h >> 8) != lo) {
            return 1;
        }
        v0 = 0;
        break;
    default:
        v0 = 0;
        break;
    }
    return v0;
}
