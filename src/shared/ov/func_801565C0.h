/* func_801565C0 — shared body (overlay slot 0x80128158, h_exact dbafe1e0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_801151E0[];
s32 func_801565C0(void) {
    s32 result;
    u32 i;
    result = 0;
    for (i = 0; i < 3; i++) {
        if (D_801151E0[i] & 1) {
            result |= 1;
        }
    }
    return result;
}
