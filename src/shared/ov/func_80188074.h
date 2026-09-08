/* func_80188074 — shared body (overlay slot 0x80128158, h_exact fc13d13e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012BCCC(s32 a0);
void func_80188074(s32 a0) {
    s16 v = *(s16 *)(a0 + 0xFC);
    if (v != 0) {
        *(s16 *)(a0 + 0xFC) = v - 1;
    } else if (func_8012BCCC(a0) <= 0xFFFFF) {
        *(s16 *)(a0 + 0x2) = 0x9;
    }
}
