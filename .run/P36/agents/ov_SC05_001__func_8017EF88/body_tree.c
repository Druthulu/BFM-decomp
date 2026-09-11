u32 func_8017EF88(s16 *param_1, s16 *param_2, s16 *param_3) {
    s16 ax, ay, bx, by, cx, cy;
    register s32 la __asm__("$8");  // !FAKE: pin $8 — NEEDED DIFFERS (P36 rung B tus8)
    register s32 lb __asm__("$7");  // !FAKE: pin $7 — NEEDED DIFFERS (P36 rung B tus8)
    register s32 lc __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus8)
    u32 r;
    s32 pad[2];

    ax = param_1[0];
    cx = param_3[0];
    if (cx < ax) {
        return 0;
    }
    __asm__ __volatile__("" : : "r"(la), "r"(lb), "r"(lc));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus8)
    bx = param_2[0];
    if (bx < cx) {
        return 1;
    }
    by = param_2[1];
    do {
        cy = param_3[2];
        if (cy < by) {
            return 0;
        }
        ay = param_1[1];
        if (ay >= cy) {
            la = (u16)ax;
            lb = (u16)bx;
            lc = (u16)cx;
            __asm__ __volatile__("" : : "r"(ax), "r"(bx), "r"(cx));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus8)
            r = func_800495EC(la | ((u16)ay << 16), lb | ((u16)by << 16),
                              lc | ((u16)cy << 16));
            return ~r >> 31;
        }
        return 1;
    } while (0);
}
