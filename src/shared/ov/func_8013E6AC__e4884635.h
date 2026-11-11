/* func_8013E6AC — shared body (overlay slot 0x80128158, h_exact e4884635). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013E6AC(void) {
    short i;

    func_8013E83C();
    guess_g_MenuPanel = 0;
    D_80115124 = D_80078EC0;
    for (i = 0; i < 8; i++) {
        *(s16 *)((char *)&guess_g_MenuPanelCursors + (i << 1)) = 0;
        guess_g_MenuPanelScrollTops[i] = 0;
    }
    if (!((u32)guess_GetStoryProgress() < 5 || currentLocationId == 0x302A || currentLocationId == 0x3073)) {
        s32 *ep;
        s32 *fp;
        fp = (s32 *)&guess_g_OpenMenuId;
        ep = (s32 *)&D_80180618;
        for (i = 0; i < 5; i++) {
            s32 *fa;
            s32 v;
            fa = (s32 *)(i * 4 + (s32)fp);
            v = ep[i] * 3 >> 2;
            fa[0x16] = v;
            *(s32 *)((char *)&D_80115188 + (i << 2)) = v;
        }
        D_801805F0 = 2;
        D_801805F2 = 1;
        { u16 *q = &guess_g_MenuStep; *q += 1; }
    } else {
        func_8013E83C();
        guess_g_MenuPanel = 7;
        D_801805F2 = 0;
        D_801805F0 = 0;
        guess_g_MenuStep = 6;
    }
}
