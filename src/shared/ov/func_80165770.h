/* func_80165770 — shared body (overlay slot 0x80128158, h_exact 8263f830). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80078EC1;
extern void func_800CAF6C(s32 *a0);
void func_80165770(void) {
    if (D_80078EC1 == 0xC) {
        KR_AS(void, func_800CAF6C)();
    }
}
