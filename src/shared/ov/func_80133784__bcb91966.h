/* func_80133784 — shared body (overlay slot 0x80128158, h_exact bcb91966). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80133784(s32 arg0, void *arg1, s32 arg2) {
    extern s32 func_80047D3C(s32);
    extern s32 func_80133AB0(s16, s16, s16, s32);
    extern SVECTOR * D_8017F808;
    extern SVECTOR * D_8017F80C;
    extern s16 D_8018E6F4;
    extern u16 D_8018E6F8;

    s32 flags;
    s16 same;
    s16 tries;
    s32 hits;
    s16 mode = arg0;
    s32 r;

    flags = 0;
    tries = 0;
    hits = 0;
    same = 0;
    D_8017F808->pad = -0x7FFF;
    D_8017F80C->pad = 0x7FFF;
    D_8017F808->vx = ((SVECTOR *)arg1)->vx;
    D_8017F808->vz = ((SVECTOR *)arg1)->vz;
    D_8017F80C->vx = ((SVECTOR *)arg2)->vx;
    D_8017F80C->vz = ((SVECTOR *)arg2)->vz;
    D_8018E6F8 = 0;
    D_8018E6F4 = 0;

    if (mode == 0) {
        s16 dx = ((SVECTOR *)arg2)->vx - ((SVECTOR *)arg1)->vx;
        s16 dy = ((SVECTOR *)arg2)->vy - ((SVECTOR *)arg1)->vy;
        s16 dz = ((SVECTOR *)arg2)->vz - ((SVECTOR *)arg1)->vz;
        if (dx == 0 && dy == 0) {
            same = (dz == 0);
        }
        D_8017F808->vy = ((SVECTOR *)arg1)->vy - 4;
        r = func_80047D3C(dx * dx + dz * dz);
        if (r < 3) {
            r = 4;
        } else if (r < 5) {
            r += 1;
        }
        D_8017F80C->vy = ((SVECTOR *)arg2)->vy + r + 1;
    } else {
        D_8017F808->vy = ((SVECTOR *)arg1)->vy;
        if (mode == 2) {
            D_8017F80C->vx = D_8017F808->vx;
            D_8017F80C->vy = D_8017F808->vy + 6;
            same = 1;
            D_8017F80C->vz = D_8017F808->vz;
        } else {
            D_8017F80C->vy = ((SVECTOR *)arg2)->vy;
        }
    }

    while (1) {
        r = func_80133AB0(mode, D_8017F808->vx, D_8017F808->vz, D_8018E6E8);
        if (r == 0) break;
        hits |= r;
        if (same) break;
        if (tries++ >= 5) {
            D_8017F80C->vx = D_8017F808->vx;
            D_8017F80C->vy = D_8017F808->vy;
            flags = 0x2000;
            D_8017F80C->vz = D_8017F808->vz;
            goto store_out;
        }
    }

    if ((s16)hits != 0 || D_8018E6F4 != 0) {
        s16 t = D_8017F808->pad;
        if (t >= -0xBCB) {
            if (t < -0x578) {
                flags |= 0x4000;
            } else {
                flags |= 0x8000;
            }
        }
        if (D_8017F80C->pad < -0xBCB) {
            flags |= 0x2000;
        }
    store_out:
        ((SVECTOR *)arg2)->vx = D_8017F80C->vx;
        ((SVECTOR *)arg2)->vy = D_8017F80C->vy;
        ((SVECTOR *)arg2)->vz = D_8017F80C->vz;
        ((SVECTOR *)arg2)->pad = D_8018E6F8;
        return flags & 0xFFFF;
    }
    ((SVECTOR *)arg2)->pad = D_8018E6F8;
    return 0;
}
