/* func_80154274 — shared body (overlay slot 0x80128158, h_exact dac93a94). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801542A4();
void func_80154274(s32 *a0, s32 a1) {
    if (*(s32 *)((s32)a0 + 0xB4) != a1) {
        func_801542A4();
    }
}
