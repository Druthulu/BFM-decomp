/* func_8014BC0C — shared body (overlay slot 0x80128158, h_exact f11eeed5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 D_80078EB2;
void func_8014BC0C(s32 a0, s32 a1) {
    D_80078EB2 += a1;
    if ((u16)D_80078EB2 >= 0x1F5) {
        D_80078EB2 = 0x1F4;
    }
}
