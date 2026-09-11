/* func_8017D6AC — shared body (overlay slot 0x80128158, h_exact 703b5fd0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_800495EC(s32 a0, s32 a1, s32 a2);
u32 func_8017D6AC(s16 *param_1, s16 *param_2, s16 *param_3) {
    union {
        struct {
            s16 x, y;
        } v;
        s32 sxy;
    } a, b, c;
    s16 ax, ay, bx, by, cx, cy;

    cx = param_3[0];
    bx = param_2[0];
    if (cx < bx) {
        return 0;
    }
    ax = param_1[0];
    if (ax < cx) {
        return 1;
    }
    cy = param_3[2];
    ay = param_1[1];
    if (cy > ay) {
        return 0;
    }
    by = param_2[1];
    if (by <= cy) {
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
