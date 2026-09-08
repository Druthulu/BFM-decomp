/* func_80154B4C — shared body (overlay slot 0x80128158, h_exact 48c87330). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154B7C(u8 *a0, s32 a1);
void func_80154B4C(u8 *a0, s32 a1) {
    if (*(s32 *)(a0 + 0xD0) != a1) {
        func_80154B7C(a0, a1);
    }
}
