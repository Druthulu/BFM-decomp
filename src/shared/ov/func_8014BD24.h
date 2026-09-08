/* func_8014BD24 — shared body (overlay slot 0x80128158, h_exact 04790f9a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_80078EB8;
extern u16 D_80078EB6;
void func_8014BD24(s32 a0, s32 a1) {
    u16 v;
    v = *(u16 *)&D_80078EB8 + a1;
    D_80078EB8 = v;
    if (D_80078EB6 < v) {
        D_80078EB8 = D_80078EB6;
    }
}
