/* func_8013CB84 — shared body (overlay slot 0x80128158, h_exact 8d303dd8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013CB84(void) {

    extern u8 D_80078EAF;
    extern s32 D_8018E78C;
    extern s32 D_8018E798;
    extern s32 D_8018E7A0;
    extern s32 D_8018FA98;
    extern s32 D_8018FA18;
    extern s32 D_8018FA0C[];
    extern u8 D_8018F9D9;
    extern u8 D_8018FB2C;
    extern u8 D_8018FA94;
    extern Rec12 D_8017FBE0[];
    extern Rec9 D_8017FBA8[];
    extern u8 D_8018FA70;  /* canonical (§8d); Rec9 block-move via cast-at-use */
    s32 loc = currentLocationId;
    s32 s0 = D_80078EAF;
    s32 ta, tb, tc, t;

    D_8018FA98 = 0;
    if (D_8018E788 == 0 && s0 != D_8018E780) {
        ta = D_8017FBE0[s0].a;
        tb = D_8017FBE0[s0].b;
        tc = D_8017FBE0[s0].c;
        D_8018E780 = s0;
        D_8018F9D9 = tc;
        D_8018FB2C = ta;
        D_8018FA94 = tb;
        *(Rec9 *)&D_8018FA70 = D_8017FBA8[s0];
        D_8018E784 = 1;
        D_8018E778 = 1;
        if (D_8018E798 & 2) {
            if (s0 == 4) { D_8018FA0C[0] = 0x100; D_8018FA18 = 0x80; }
            if (s0 == 0) { D_8018FA0C[0] = 0x100; D_8018FA18 = 0; }
        }
    }
    if (D_8018E784 != 0) {
        t = D_8018E778 - 1;
        D_8018E778 = t;
        if (t == 0) {
            if (D_8018E788 == 0) {
                if ((D_8018E798 & 2) && s0 == 4) {
                    if (D_8018E7A0 != 0) func_8013DBE4(6);
                    else func_8013D9B0(6);
                } else {
                    if (D_8018E7A0 != 0) func_8013DBE4(s0);
                    else func_8013D9B0(s0);
                }
                func_8013D330();
                func_8013D178();
                func_8013CF68();
                D_8018E778 = 2;
                if (D_8018E784 != 0) {
                    if (D_8018E798 & 2) {
                        if (s0 == 4) {
                            s32 *p = &D_8018FA18;
                            t = *p - 8;
                            *p = t;
                            if (t < 0) *p = 0;
                        } else if (s0 == 0) {
                            s32 *p = &D_8018FA18;
                            t = *p + 0x20;
                            *p = t;
                            if (t >= 0x81) *p = 0x80;
                        }
                    }
                } else if (D_8018E798 & 2) {
                    if (s0 == 4) D_8018FA18 = 0;
                    if (s0 == 0) D_8018FA18 = 0x80;
                }
            } else {
                if (D_8018E7A0 != 0) func_8013DBE4(5);
                else func_8013D9B0(5);
                D_8018E778 = 1;
            }
        }
    }
    D_8018E78C = 0;
    if (loc == 0x1010) {
        if (s0 == 3) {
            if (D_8018E784 != 0) D_8018E78C = D_8018E77C;
            else D_8018E78C = 0x1F;
        } else if (s0 == 4) {
            if (D_8018E784 != 0) D_8018E78C = 0x1F - D_8018E77C;
            else D_8018E78C = 0;
        }
    }
}
