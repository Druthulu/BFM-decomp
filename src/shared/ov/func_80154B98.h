/* func_80154B98 — shared body (overlay slot 0x80128158, h_exact 62cd5e3d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154BC8(void *a0, s32 a1, s32 a2);
void func_80154B98(void *a0, s32 a1, s32 a2) {
    if (*(s32 *)((s32)a0 + 0xD0) != a1) {
        func_80154BC8(a0, a1, a2);
    }
}
