/* func_801739D8 — shared body (overlay slot 0x80128158, h_exact 327b373c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32);
void func_801739D8(u8 *a0) {
    if ((*(s32 *)(a0 + 0x44) & 2) == 0) {
        func_80171A1C(a0);
        func_80174650((s32)a0);
    }
}
