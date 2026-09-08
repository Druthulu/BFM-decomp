/* func_80139A44 — shared body (overlay slot 0x80128158, h_exact c8ebab2c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80127530[4];
void func_80139A44(s32 a0, u16 a1) {
    if (a1 < 4) {
        D_80127530[a1] = a0;
    }
}
