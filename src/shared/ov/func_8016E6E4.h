/* func_8016E6E4 — shared body (overlay slot 0x80128158, h_exact de77bc24). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8016E778();
void func_8016E6E4(s32 a0) {
    s32 v0 = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = v0;
    if (v0 == -1) {
        *(u16 *)(a0 + 2) = *(u16 *)(a0 + 2) + 1;
    }
    func_8016E778();
}
