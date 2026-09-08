/* func_80150F80 — shared body (overlay slot 0x80128158, h_exact 65594f58). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80151184(s32 a0, s32 a1, s32 a2);
extern u8 D_80078EC1;
void func_80150F80(s32 a0) {
    if (D_80078EC1 != 0xC) {
        func_80151184(a0, 0xC007, 0x20);
    }
}
