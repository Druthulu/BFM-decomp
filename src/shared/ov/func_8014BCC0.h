/* func_8014BCC0 — shared body (overlay slot 0x80128158, h_exact 4055e35f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_80078EB4;
void func_8014BCC0(s32 a0, s32 a1) {
    s32 v1 = (u16)D_80078EB4;
    if (a1 < v1) {
        D_80078EB4 = v1 - a1;
    } else {
        D_80078EB4 = 1;
    }
}
