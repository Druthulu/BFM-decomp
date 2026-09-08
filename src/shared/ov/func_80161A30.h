/* func_80161A30 — shared body (overlay slot 0x80128158, h_exact 8d71c657). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80078EC0;
s32 func_80161A30(s32 a0) {
    if (*(s16*)(a0 + 0x1C8) != 0) {
        return ((D_80078EC0 & 0x7F) ^ 0x5) == 0;
    }
    return 0;
}
