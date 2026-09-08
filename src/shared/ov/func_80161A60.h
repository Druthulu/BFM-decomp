/* func_80161A60 — shared body (overlay slot 0x80128158, h_exact 00488e7e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80078EC0;
s32 func_80161A60(s32 a0) {
    s32 v0;
    if (*(s16*)(a0 + 0x1C8) != 0) {
        v0 = ((D_80078EC0 & 0x7F) ^ 6) == 0;
        return v0;
    }
    return 0;
}
