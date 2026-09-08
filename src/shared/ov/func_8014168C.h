/* func_8014168C — shared body (overlay slot 0x80128158, h_exact 78494126). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80115148[];
extern u8 D_80115149[];
extern u8 D_80115158[];
s16 func_8014168C(s16 a0) {
    s32 i = a0 * 2;
    return D_80115148[i] + D_80115149[i] * D_80115158[i];
}
