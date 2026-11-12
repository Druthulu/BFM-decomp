/* func_80142454 — shared body (overlay slot 0x80128158, h_exact ea50e5b5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 guess_g_PlayerPosX; // Names ledger: config/names.tsv guess_g_PlayerPosX
extern u16 guess_g_PlayerPosY; // Names ledger: config/names.tsv guess_g_PlayerPosY
extern u16 guess_g_PlayerPosZ; // Names ledger: config/names.tsv guess_g_PlayerPosZ
extern s32 func_8012C51C(void *a0, s32 a1);
void func_80142454(s32 a0) {
    s32 s0 = a0;
    u16 *s1 = &guess_g_PlayerPosX;
    s32 ret;
    s16 st[10];
    st[3] = 0x13;
    st[0] = *s1;
    st[1] = guess_g_PlayerPosY;
    st[2] = guess_g_PlayerPosZ;
    st[4] = 1;
    st[5] = 0;
    st[7] = 0;
    *(s32 *)&st[8] = 0;
    ret = ((s32 (*)(void *, s32))func_8012C51C)(st, 0);
    if (ret != 0) {
        *(s16 *)(ret + 0x52) = s0;
        *(s32 *)(ret + 0x64) = (s32)s1 - 6;
    }
}
