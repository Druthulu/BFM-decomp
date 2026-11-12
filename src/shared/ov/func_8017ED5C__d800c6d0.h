/* func_8017ED5C — shared body (overlay slot 0x80128158, h_exact d800c6d0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void *func_8017ED5C(s32 param_1, s32 param_2) {
    extern u8 guess_g_EmptyText[]; // Names ledger: config/names.tsv guess_g_EmptyText
    extern u8 D_80112B58[];
    extern u8 D_80112B90[];
    extern u8 D_80112BA8[];
    extern s32 guess_g_MenuHelpText; // Names ledger: config/names.tsv guess_g_MenuHelpText
    extern u8 D_80183478[];
    extern u8 D_801BB920[];
    extern s16 D_801BB948[][2];
    extern void *D_801BB968[];
    extern void *D_801BB984[];
    extern u8 D_801C3A74[];
    extern u8 D_801C3B38[];
    extern u8 D_801C3B54[];
    extern u8 D_801C3BC4[];
    extern u8 D_801C3C50[];
    extern u8 D_801C3D48[];
    extern u8 D_801C3D80[];
    extern u8 D_801C3DA8[];
    extern u8 *D_801CD9A4;
    extern void *D_801CD9B0;
    extern s32 guess_TestGameFlag(s32 arg);
    extern s32 guess_GetGameVarByte(s32 arg);
    extern s32 guess_GetStoryProgress(void);
    extern void func_80139A44(s32 a0, u16 a1);
    extern s16 func_8017F730(void);
    void *result;
    s16 sel;
    s16 idx;
    s32 t;
    void *p;
    s16 *e;
    s32 off;
    s32 lim;
    s32 pad[2];                                              /* [1] */
    u8 c;
    result = guess_g_EmptyText;
    sel = param_1 - 1;
    switch (sel) {
    case 5:
        if (func_8017F730() != 0) {
            t = guess_GetStoryProgress();
            idx = D_801BB920[(s16)param_2];
            off = idx * 4;                                   /* [2] */
            lim = D_801BB948[idx][0];                        /* [3] */
            __asm__ __volatile__("");                        /* [4] */  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B headers2) wall:greg-priority
            e = (s16 *)D_801BB948;
            __asm__("" : "=r"(e) : "0"(e));                  /* [5] */  // !FAKE: launder — NEEDED DIFFERS (P36 rung B headers2) wall:greg-priority
            if (t < lim) {
                if (*(s16 *)((u8 *)e + off + 2) == 0 ||
                    (guess_TestGameFlag(*(s16 *)((u8 *)e + off + 2)) & 0xFF) == 0) {
                    idx = -1;
                }
            }
            if (idx >= 0) {
                p = D_801BB968[idx];
                func_80139A44((s32)p, 0);
                if (p != D_801CD9B0) {
                    D_801CD9B0 = p;
                    guess_g_MenuHelpText = 0;
                }
                result = D_801C3D48;
            } else {
                result = D_801C3D80;
            }
        } else {
            s16 j;
            s32 v;
            j = (s16)param_2;
            v = guess_GetGameVarByte(D_80183478[j]) & 0xFF;
            if (v == 0) {
                result = D_80112B58;
            } else if (v == 1) {
                result = D_80112B90;
            } else {
                result = D_801C3DA8;
                if (j != 0) {
                    result = D_80112BA8;
                }
            }
        }
        break;
    case 0:
        result = D_801C3A74;
        break;
    case 1:
        result = D_801C3C50;
        break;
    case 3:
        result = D_801C3B38;
        break;
    case 2:
    case 6:
    case 7:
        result = D_801C3BC4;
        break;
    case 8:
        result = D_801C3B54;
        break;
    case 9:
        c = D_801CD9A4[(s16)param_2];
        if ((guess_GetGameVarByte(c + 0x62) & 0x40) != 0) {
            result = D_801BB984[c];
        }
        break;
    }
    return result;
}
