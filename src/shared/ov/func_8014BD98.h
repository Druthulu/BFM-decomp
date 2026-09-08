/* func_8014BD98 — shared body (overlay slot 0x80128158, h_exact d0f543db). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 D_80078EB6;
extern s16 D_80078EB8;
void func_8014BD98(s32 a0, u16 a1) {
    D_80078EB8 = a1;
    if (D_80078EB6 < a1) {
        D_80078EB8 = D_80078EB6;
    }
}
