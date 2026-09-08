/* func_80174F64 — shared body (overlay slot 0x80128158, h_exact 77b0bc90). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80175014(u8 *a0, u8 *a1, s32 a2);
void func_80174F64(u8 *a0) {
    s32 r;
    u16 *p = (u16 *)(a0 + 0x38);
    r = func_80175014(a0, *(u8 **)(a0 + 0x34), *p & 0x7FFF);
    if (r != 0) {
        *p = *p | 0x8000;
    } else {
        *p = *p + 1;
    }
}
