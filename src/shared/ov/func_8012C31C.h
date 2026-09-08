/* func_8012C31C — shared body (overlay slot 0x80128158, h_exact 7b266c49). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80120194[];
s32 func_8012C31C(void) {
    s32 a0;
    s32 v1;
    a0 = (s32)D_80120194;
    v1 = a0 + 0x6480;
    if (v1 != a0) {
        do {
            if (*(u16 *)v1 == 0) {
                return v1;
            }
            v1 -= 0x10C;
        } while (v1 != a0);
    }
    return 0;
}
