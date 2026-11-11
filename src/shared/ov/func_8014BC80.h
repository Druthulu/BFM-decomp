/* func_8014BC80 — shared body (overlay slot 0x80128158, h_exact d382a5c2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 g_PlayerHp;
extern u8 D_800B9A17;
void func_8014BC80(s32 a0, s32 a1) {
    s32 v;
    v = *(u16 *)&g_PlayerHp;
    if (v < a1) {
        g_PlayerHp = 0;
        D_800B9A17 = 0;
    } else {
        g_PlayerHp = v - a1;
    }
}
