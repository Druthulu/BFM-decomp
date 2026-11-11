/* func_8014BB24 — shared body (overlay slot 0x80128158, h_exact 79d6924b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_TestGameFlag(s32 a0);
extern u8 guess_g_PlayerRecord[];
extern s16 g_PlayerHp;
void func_8014BB24(s32 a0, s32 a1, s32 a2)
{
    u8 *base = guess_g_PlayerRecord;
    u16 cur;
    if (a2 != 0) {
        g_PlayerHp = (u16)g_PlayerHp + a1;
    } else {
        if ((guess_TestGameFlag(0x1B) & 0xFF) != 0) {
            cur = g_PlayerHp;
            if (cur < 0x3E7) {
                g_PlayerHp = cur + a1;
                if ((u16)(cur + a1) >= 0x3E8) {
                    g_PlayerHp = 0x3E7;
                }
            }
        } else {
            cur = g_PlayerHp;
            if (cur < 0x1F4) {
                g_PlayerHp = cur + a1;
                if ((u16)(cur + a1) >= 0x1F5) {
                    g_PlayerHp = 0x1F4;
                }
            }
        }
    }
    if (*(u16 *)(base + 0x3A) < *(u16 *)(base + 0x3C)) {
        *(u16 *)(base + 0x3C) = *(u16 *)(base + 0x3A);
    }
}
