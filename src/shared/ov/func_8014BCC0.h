/* func_8014BCC0 — shared body (overlay slot 0x80128158, h_exact 4055e35f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 g_PlayerHp;
void func_8014BCC0(s32 a0, s32 a1) {
    s32 v1 = (u16)g_PlayerHp;
    if (a1 < v1) {
        g_PlayerHp = v1 - a1;
    } else {
        g_PlayerHp = 1;
    }
}
