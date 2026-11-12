/* func_801417F8 — shared body (overlay slot 0x80128158, h_exact fa494c64). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_800D2624(void);
extern u8 D_800B9A15;
extern u8 D_800B9A16;
extern short guess_g_DoubleBufferIndex; // Names ledger: config/names.tsv guess_g_DoubleBufferIndex
extern u16 D_80115114;
extern u16 guess_g_MenuStep; // Names ledger: config/names.tsv guess_g_MenuStep
void func_801417F8(void) {
    if (D_800B9A15 == 0 || D_800B9A16 != 0) {
        if (D_80115114 == (u16)(guess_g_DoubleBufferIndex ^ 1)) {
            func_800D2624();
        } else {
            guess_g_MenuStep += 1;
        }
    }
}
