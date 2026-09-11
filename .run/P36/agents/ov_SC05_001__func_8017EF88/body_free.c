u32 func_8017EF88(s16 *param_1, s16 *param_2, s16 *param_3) {
    s16 ax, ay, bx, by, cx, cy;
    s32 la;
    s32 lb;
    s32 lc;
    u32 r;
    s32 pad[2];

    ax = param_1[0];
    cx = param_3[0];
    if (cx < ax) {
        return 0;
    }
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
            r = func_800495EC(la | ((u16)ay << 16), lb | ((u16)by << 16),
                              lc | ((u16)cy << 16));
            return ~r >> 31;
        }
        return 1;
    } while (0);
}
