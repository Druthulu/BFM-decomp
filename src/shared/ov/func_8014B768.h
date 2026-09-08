/* func_8014B768 — shared body (overlay slot 0x80128158, h_exact f4237e1d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80078E9C;
void func_8014B768(s32 a0, s32 a1) {
    D_80078E9C -= a1;
    if (*(s16 *)((s32)&D_80078E9C + 2) < 0) {
        D_80078E9C = 0;
    }
}
