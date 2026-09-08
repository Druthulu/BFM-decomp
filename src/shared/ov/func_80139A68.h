/* func_80139A68 — shared body (overlay slot 0x80128158, h_exact 0e18d7e5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_80127540[4];
void func_80139A68(s32 a0, u16 a1) {
    if (a1 < 4) {
        D_80127540[a1] = (s16)a0;
    }
}
