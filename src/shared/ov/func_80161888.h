/* func_80161888 — shared body (overlay slot 0x80128158, h_exact 28282182). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80161888(s32 a0, u32 a1)
{
    s32 s0 = a0;
    if (a1 & 1) {
        func_8014C010(s0, 1);
        func_80161D20(s0, *(u16*)(s0 + 0x16E));
        return 1;
    }
    if (a1 & 0x4000) {
        func_8014C010(s0, 1);
        func_80161D20(s0, *(u16*)(s0 + 0x16E));
        return 2;
    }
    if (a1 & 0x2000) {
        func_8014C010(s0, 1);
        func_80161D20(s0, *(u16*)(s0 + 0x16E));
        return 4;
    }
    return 0;
}
