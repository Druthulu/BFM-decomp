/* func_801552F4 — shared body (overlay slot 0x80128158, h_exact 3d478d05). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_g_PlayerTmdList[]; // Names ledger: config/names.tsv guess_g_PlayerTmdList
void func_801552F4(s32 a0) {
    s32 *p = guess_g_PlayerTmdList;
    s32 v0 = *p;
    if (v0 != 0) {
        do {
            v0 &= 0x80FFFFFF;
            *p = v0;
            p += 1;
            v0 = *p;
        } while (v0 != 0);
    }
    *(s32 *)(a0 + 0x44) = *(s32 *)(a0 + 0x44) | 0x30000000;
}
