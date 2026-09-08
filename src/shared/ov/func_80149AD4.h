/* func_80149AD4 — shared body (overlay slot 0x80128158, h_exact fe7498e0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8015DAC4(s32 *a0);
extern void func_8015554C(s32 *a0);
void func_80149AD4(s32 *a0) {
    s32 pad[6];
    (void)pad;
    if (*(s32 *)((s32)a0 + 0x178) != 0) {
        func_8015DAC4(a0);
    } else {
        *(s8 *)((s32)a0 + 0x1AA) = 1;
        func_8015554C(a0);
    }
}
