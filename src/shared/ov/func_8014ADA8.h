/* func_8014ADA8 — shared body (overlay slot 0x80128158, h_exact ca0ea4bc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80078E8C;
void func_8014ADA8(s32 a0, s32 a1) {
    s32 v0;
    v0 = D_80078E8C + a1;
    D_80078E8C = v0;
    if (0x1869F < (u32)v0) {
        D_80078E8C = 0x1869F;
    }
}
