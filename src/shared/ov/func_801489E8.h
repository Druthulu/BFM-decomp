/* func_801489E8 — shared body (overlay slot 0x80128158, h_exact 67d61a9f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_801489E8(s32 a0) {
    u8 v1;
    v1 = *(u8*)(a0 + 0xA9);
    switch (v1) {
    case 0x41:
        return *(u16*)(a0 + 0xAA) & 0x8000;
    case 0x53:
    case 0x73:
        return *(u8*)(a0 + 0xAE) < 0x40;
    }
    return 0;
}
