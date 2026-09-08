/* func_801541D8 — shared body (overlay slot 0x80128158, h_exact cc56f5c9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154218(u8 *a0, s32 a1, s32 a2);
void func_801541D8(u8 *a0, s32 a1, s32 a2) {
    if (*(s32 *)(a0 + 0xB4) != ((s32 *)*(s32 **)(a0 + 0xB0))[a1]) {
        func_80154218(a0, a1, a2);
    }
}
