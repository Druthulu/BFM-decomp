/* func_80174FBC — shared body (overlay slot 0x80128158, h_exact b74d9b6b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80175014(u8 *a0, u8 *a1, s32 a2);
void func_80174FBC(u8 *a0) {
    u16 *p = (u16 *)(a0 + 0x38);
    if ((*p & 0x7FFF) != 0) {
        func_80175014(a0, *(u8 **)(a0 + 0x34), *p & 0x7FFF);
        *p = *p - 1;
    } else {
        *p = *p | 0x8000;
    }
}
