/* func_80149B14 — shared body (overlay slot 0x80128158, h_exact 06806d92). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8015DAC4(s32 *a0);
extern void func_8015554C(s32 *a0);
void func_80149B14(s32 *a0) {
    s32 pad[6];
    (void)pad;
    if (*(s32 *)((s32)a0 + 0x178) != 0) {
        func_8015DAC4(a0);
    } else {
        func_8015554C(a0);
    }
}
