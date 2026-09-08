/* func_80139DC8 — shared body (overlay slot 0x80128158, h_exact 4bf7cfca). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_8012811A;
void func_80139DC8(void) {
    s32 i = 0x287;
    s16 *p = &D_8012811A;
    do {
        *p = 0;
        i--;
        p = (s16 *)((s32)p - 2);
    } while (i >= 0);
}
