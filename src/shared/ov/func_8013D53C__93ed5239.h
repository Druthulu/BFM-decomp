/* func_8013D53C — shared body (overlay slot 0x80128158, h_exact 93ed5239). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013D53C(void *arg0v) {

    extern Rec9 D_8017FBA8[];
    extern Rec12 D_8017FBE0[];
    extern u8 D_80078EAF;
    extern u8 D_8018FA70;
    extern s32 D_8018E78C;
    Cmd_8013D53C *arg0 = arg0v;

    extern u8 D_8017FBE4[];
    extern u8 D_8017FBE8[];
    extern unsigned char D_8018F9D0;
    extern s16 *D_8018E774;
    extern s32 D_8018E7A4;
    extern s32 D_8018E7A8;
    extern s32 D_8018E7AC;
    s32 s0v;
    s32 t9v;
    s32 t8v;
    u8 b0, b1, b2;
    u8 pad[8];   /* dead BLKmode local: frame 0x10 -> 0x18, zero code */

    if (!(D_8018E798 & 1)) {
        D_8018E780 = 1;
    } else {
        D_8018E780 = D_80078EAF;
    }

    b0 = ((u8 *)D_8017FBE0)[D_8018E780 * 12];
    D_8018FAB2 = b0;
    D_8018FB2C = b0;
    b1 = D_8017FBE4[D_8018E780 * 12];
    D_8018F9DA = b1;
    D_8018FA94 = b1;
    b2 = D_8017FBE8[D_8018E780 * 12];
    D_8018F9B8 = b2;
    D_8018F9D9 = b2;

    (*(S9 *)&D_8018F9D0) = ((S9 *)D_8017FBA8)[D_8018E780];
    (*(S9 *)&D_8018FA70) = *(S9 *)(&D_8018F9B8 + 0x18);  /* same addr as (*(S9 *)&D_8018F9D0); distinct sym defeats cse, keeps %hi/%lo */

    D_8018FA98 = 1;
    D_8018E794 = -1;
    D_8018E790 = 0;
    D_8018E78C = -1;
    D_8018E778 = 0;
    D_8018E784 = 0;
    D_8018E788 = 0;

    if ((D_8018E798 & 2) && (D_8018E780 == 4)) {
        s0v = (*(s32 * *)&D_8018E768)[18];
        t9v = (*(s32 * *)&D_8018E768)[19];
        t8v = (*(s32 * *)&D_8018E768)[20];
    } else {
        s32 *p = (s32 *)(D_8018E780 * 12 + (s32) (*(s32 * *)&D_8018E768));  /* block-local: local-alloc ties sum into mul chain */
        s0v = p[0];
        t9v = p[1];
        t8v = p[2];
    }

    (*(Cmd_8013D53C * *)&D_8018E774) = arg0;
    if (arg0 != 0) {
        if (D_8018E7A0 != 0) {
            s32 *p = (s32 *)(D_8018E780 * 12 + (s32) (*(s32 * *)&D_8018E770));
            D_8018E7A4 = p[0];
            D_8018E7A8 = p[1];
            D_8018E7AC = p[2];
        } else {
            while ((arg0->cmd & 0xFFFF) != 0xFF) {
                if ((arg0->cmd & 0xFFFF) == 9) {
                    s32 n;
                    s32 i;
                    u16 *src;
                    u16 *dst;
                    n = arg0->w * arg0->h;
                    i = 0;
                    src = arg0->data;
                    dst = src + n;
                    if (n > 0) {
                        do {
                            u16 px;
                            s32 r, g, b, out;
                            px = *src;
                            r = ((px & 0x1F) * s0v) / 2560;
                            g = (((px & 0x3E0) * t9v) / 2560) & 0x3E0;
                            b = (((px & 0x7C00) * t8v) / 2560) & 0x7C00;
                            out = r | g | b | (px & 0x8000);
                            if (out == 0 && px != 0) {
                                out = 0x8000;
                            }
                            *dst = out;
                            dst++;
                            do { i++; } while (0);
                            src++;
                        } while (i < n);
                    }
                }
                arg0++;
            }
        }
    }
}
