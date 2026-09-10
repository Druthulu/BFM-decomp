/* func_80133784 — shared body (overlay slot 0x80128158, h_exact bcb91966). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80133784(s32 arg0, void *arg1, s32 arg2) {
    extern s32 func_80047D3C(s32);
    extern s32 func_80133AB0(s16, s16, s16, s32);
    extern Box_80133784 * D_8017F808;
    extern Box_80133784 * D_8017F80C;
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
    D_8017F808->f6 = -0x7FFF;
    D_8017F80C->f6 = 0x7FFF;
    D_8017F808->f0 = ((Box_80133784 *)arg1)->f0;
    D_8017F808->f4 = ((Box_80133784 *)arg1)->f4;
    D_8017F80C->f0 = ((Box_80133784 *)arg2)->f0;
    D_8017F80C->f4 = ((Box_80133784 *)arg2)->f4;
    D_8018E6F8 = 0;
    D_8018E6F4 = 0;

    if (mode == 0) {
        s16 dx = ((Box_80133784 *)arg2)->f0 - ((Box_80133784 *)arg1)->f0;
        s16 dy = ((Box_80133784 *)arg2)->f2 - ((Box_80133784 *)arg1)->f2;
        s16 dz = ((Box_80133784 *)arg2)->f4 - ((Box_80133784 *)arg1)->f4;
        if (dx == 0 && dy == 0) {
            same = (dz == 0);
        }
        D_8017F808->f2 = ((Box_80133784 *)arg1)->f2 - 4;
        r = func_80047D3C(dx * dx + dz * dz);
        if (r < 3) {
            r = 4;
        } else if (r < 5) {
            r += 1;
        }
        D_8017F80C->f2 = ((Box_80133784 *)arg2)->f2 + r + 1;
    } else {
        D_8017F808->f2 = ((Box_80133784 *)arg1)->f2;
        if (mode == 2) {
            D_8017F80C->f0 = D_8017F808->f0;
            D_8017F80C->f2 = D_8017F808->f2 + 6;
            same = 1;
            D_8017F80C->f4 = D_8017F808->f4;
        } else {
            D_8017F80C->f2 = ((Box_80133784 *)arg2)->f2;
        }
    }

    while (1) {
        r = func_80133AB0(mode, D_8017F808->f0, D_8017F808->f4, D_8018E6E8);
        if (r == 0) break;
        hits |= r;
        if (same) break;
        if (tries++ >= 5) {
            D_8017F80C->f0 = D_8017F808->f0;
            D_8017F80C->f2 = D_8017F808->f2;
            flags = 0x2000;
            D_8017F80C->f4 = D_8017F808->f4;
            goto store_out;
        }
    }

    if ((s16)hits != 0 || D_8018E6F4 != 0) {
        s16 t = D_8017F808->f6;
        if (t >= -0xBCB) {
            if (t < -0x578) {
                flags |= 0x4000;
            } else {
                flags |= 0x8000;
            }
        }
        if (D_8017F80C->f6 < -0xBCB) {
            flags |= 0x2000;
        }
    store_out:
        ((Box_80133784 *)arg2)->f0 = D_8017F80C->f0;
        ((Box_80133784 *)arg2)->f2 = D_8017F80C->f2;
        ((Box_80133784 *)arg2)->f4 = D_8017F80C->f4;
        ((Box_80133784 *)arg2)->f6 = D_8018E6F8;
        return flags & 0xFFFF;
    }
    ((Box_80133784 *)arg2)->f6 = D_8018E6F8;
    return 0;
}
