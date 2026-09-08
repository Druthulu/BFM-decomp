/* func_80154AE0 — shared body (overlay slot 0x80128158, h_exact cf62c38d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154B20(s32 a0, s32 a1, s32 a2);
void func_80154AE0(s32 a0, s32 a1, s32 a2) {
    if (*(s32 *)(a0 + 0xD0) != ((s32 *)*(s32 **)(a0 + 0xCC))[a1]) {
        func_80154B20(a0, a1, a2);
    }
}
