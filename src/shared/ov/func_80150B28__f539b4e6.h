/* func_80150B28 — shared body (overlay slot 0x80128158, h_exact f539b4e6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80150B28(int param_1) {

    extern s32 guess_g_CurrentEvent; // Names ledger: config/names.tsv guess_g_CurrentEvent
    extern void (*D_80180EF4[])(void);
    u32 idx;
    u32 sub;

    if ((guess_g_CurrentEvent & 0x80FFFFFF) == 0) {
        idx = *(u16 *)(param_1 + 0x16C);
        if (idx != 0 && idx < 0x26) {
            sub = idx - 1;
            D_80180EF4[sub]();
        }
    }
    *(u16 *)(param_1 + 0x16C) = 0;
}
