u32 func_8017EF88(s16 *param_1, s16 *param_2, s16 *param_3) {
    union {
        struct {
            s16 x, y;
        } v;
        s32 sxy;
    } a, b, c;
    s16 ax, ay, bx, by, cx, cy;

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
    cy = param_3[2];
    if (cy < by) {
        return 0;
    }
    ay = param_1[1];
    if (ay >= cy) {
        a.v.x = ax;
        a.v.y = ay;
        b.v.x = bx;
        b.v.y = by;
        c.v.x = cx;
        c.v.y = cy;
        return func_800495EC(a.sxy, b.sxy, c.sxy) >= 0;
    }
    return 1;
}
