/* func_8014CB2C — shared body (overlay slot 0x80128158, h_exact 726804f0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80126D1F;
s32 func_8014CB2C(void) {
    s32 v1 = D_80126D1F;
    if (v1 & 0x80) {
        v1 = (v1 & 0x7F) | 0x80000000;
    }
    return v1;
}
