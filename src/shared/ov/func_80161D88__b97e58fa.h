/* func_80161D88 — shared body (overlay slot 0x80128158, h_exact b97e58fa). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80161D88(void) {
    if ((guess_g_CurrentEvent & 0x80FFFFFF) == 0 && (D_800AE6A8 & 0x80FFFFFF) == 0 &&
        (guess_TestGameFlag(0x141) & 0xFF) != 0) {
        guess_SetGameFlag(0x141, 0);
        guess_SetGameFlag(0x95, 1);
        func_800D1734(&D_80181600);
    }
}
