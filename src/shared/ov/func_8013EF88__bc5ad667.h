/* func_8013EF88 — shared body (overlay slot 0x80128158, h_exact bc5ad667). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013EF88(void)
{

    extern u16 guess_g_MenuTransitionTimer; // Names ledger: config/names.tsv guess_g_MenuTransitionTimer
    extern E4  guess_g_MenuPanelSlide[]; // Names ledger: config/names.tsv guess_g_MenuPanelSlide
    extern u16 D_80115114;
    u16 *p = &guess_g_MenuTransitionTimer;
    u16 old = *p;
    short i;

    if (old != 0) {
        u16 nw = old - 1;
        *p = nw;
        if (nw != 0) {
            guess_g_MenuPacketPtr = *(s32 *)((char *)&guess_g_MenuTransitionTimer + 0xB0 + (u16)guess_g_DoubleBufferIndex * 4);
            func_8013FAF8(0, 5);
            for (i = 0; i < 5; i++) {
                s32 t = aD80115188[i].f0 * 3;
                aD80115188[i].f0 = t;
                guess_g_MenuPanelSlide[i].f0 = guess_g_MenuPanelSlide[i].f0 + t;
            }
            if (guess_g_MenuTransitionTimer < 3) {
                u16 *s = &(*(u16 *)&D_8017FE3E);
                *s -= 1;
            }
            {
                u16 *w = &(*(u16 *)&D_8017FE3C);
                *w -= 2;
                if ((s16)*w < 0) {
                    *w = 0;
                }
            }
        }
    }

    {
        s16 *pv = &(*(s16 *)&D_80115124);
        if (*pv != 0) {
            if (func_800D0488(*pv) == 0) return;
            *pv = 0;
        }
    }

    if (guess_g_MenuTransitionTimer == 0) {
        if (D_80115114 == ((u16)guess_g_DoubleBufferIndex ^ 1)) {
            func_800D2624();
        } else {
            guess_g_MenuStep += 1;
        }
    }
}
