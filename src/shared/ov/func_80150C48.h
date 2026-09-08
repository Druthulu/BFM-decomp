/* func_80150C48 — shared body (overlay slot 0x80128158, h_exact e576ed79). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80150480(s32 a0);
extern s32 D_800AE6B0;
extern u16 D_800AE6DC;
void func_80150C48(s32 a0) {
    if (func_80150480(a0) != 0) {
        s32 p = *(s32 *)(a0 + 0x1A4);
        D_800AE6B0 = *(s32 *)(p + 0xDC);
        p = *(s32 *)(a0 + 0x1A4);
        D_800AE6DC = *(u16 *)(p + 0xFC);
    }
}
