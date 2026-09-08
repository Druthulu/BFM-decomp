/* func_80148A48 — shared body (overlay slot 0x80128158, h_exact 713f8cef). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80148A48(s32 a0) {
    u8 v1;
    v1 = *(u8*)(a0 + 0xA9);
    switch (v1) {
    case 0x41:
        return *(u16*)(a0 + 0xAA) & 0x2000;
    case 0x53:
    case 0x73:
        return *(u8*)(a0 + 0xAE) >= 0xC1;
    }
    return 0;
}
