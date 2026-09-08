/* func_80172560 — shared body (overlay slot 0x80128158, h_exact 4ee31a22). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80013450(s32);
s32 func_80172560(u8 *a0, u8 *a1) {
    *(s16 *)(a1 + 2) = *(u16 *)(a0 + 0xA);
    return func_80013450((s32)(a0 + 4)) < 0x10;
}
