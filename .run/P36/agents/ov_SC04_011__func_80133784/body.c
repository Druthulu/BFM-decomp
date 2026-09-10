s32 func_80133784(s32 arg0, void *arg1, s32 arg2) {
    extern s32 func_80047D3C(s32);
    extern s32 func_80133AB0(s16, s16, s16, s32);
    extern Box_80133784 * D_801909BC;
    extern Box_80133784 * D_801909C0;
    extern s16 D_801EDA3C;
    extern u16 D_801EDA40;

    s32 s1;
    s32 s2;
    s16 s3;
    s32 s4;
    s16 a0v;
    s16 arg0s;
    s32 dx, dy, dz;
    s32 r, ret;

    a0v = ((s16)arg0);
    s1 = 0;
    s3 = 0;
    s4 = 0;
    s2 = 0;
    arg0s = a0v;
    D_801909BC->f6 = -0x7FFF;
    D_801909C0->f6 = 0x7FFF;
    D_801909BC->f0 = ((Box_80133784 *)arg1)->f0;
    D_801909BC->f4 = ((Box_80133784 *)arg1)->f4;
    D_801909C0->f0 = ((Box_80133784 *)arg2)->f0;
    D_801909C0->f4 = ((Box_80133784 *)arg2)->f4;
    D_801EDA40 = 0;
    D_801EDA3C = 0;

    if ((s16)a0v == 0) {
        s16 sx = ((Box_80133784 *)arg2)->f0 - ((Box_80133784 *)arg1)->f0;
        s16 sy = ((Box_80133784 *)arg2)->f2 - ((Box_80133784 *)arg1)->f2;
        s16 sz = ((Box_80133784 *)arg2)->f4 - ((Box_80133784 *)arg1)->f4;
        if (sx == 0 && sy == 0) {
            s32 zt = (sz == 0);
            s2 = zt;
        }
        D_801909BC->f2 = ((Box_80133784 *)arg1)->f2 - 4;
        r = func_80047D3C(sx * sx + sz * sz);
        if (r < 3) {
            r = 4;
        } else if (r < 5) {
            r += 1;
        }
        D_801909C0->f2 = ((Box_80133784 *)arg2)->f2 + r + 1;
    } else {
        D_801909BC->f2 = ((Box_80133784 *)arg1)->f2;
        if ((s16)a0v == 2) {
            D_801909C0->f0 = D_801909BC->f0;
            D_801909C0->f2 = D_801909BC->f2 + 6;
            s2 = 1;
            D_801909C0->f4 = D_801909BC->f4;
        } else {
            D_801909C0->f2 = ((Box_80133784 *)arg2)->f2;
        }
    }

    while (1) {
        s32 ret0;
        s32 retc;
        ret0 = func_80133AB0(arg0s, (s16)D_801909BC->f0, (s16)D_801909BC->f4, (*(s32*)&D_801EDA30));
        retc = ret0;
        ret = retc;
        if (ret == 0) goto after;
        s4 |= ret;
        if (s2 != 0) goto after;
        {
            s16 oldc = s3;
            s3 = s3 + 1;
            if (oldc >= 5) break;
        }
    }

    D_801909C0->f0 = D_801909BC->f0;
    D_801909C0->f2 = D_801909BC->f2;
    s1 = 0x2000;
    D_801909C0->f4 = D_801909BC->f4;
    goto store_out;

after:
    if ((s16)s4 != 0 || D_801EDA3C != 0) {
        s16 t;
        t = D_801909BC->f6;
        if (t >= -0xBCB) {
            if (t < -0x578) {
                s1 |= 0x4000;
            } else {
                s1 |= 0x8000;
            }
        }
        if ((s16)D_801909C0->f6 < -0xBCB) {
            s1 |= 0x2000;
        }
    store_out:
        ((Box_80133784 *)arg2)->f0 = D_801909C0->f0;
        ((Box_80133784 *)arg2)->f2 = D_801909C0->f2;
        ((Box_80133784 *)arg2)->f4 = D_801909C0->f4;
        ((Box_80133784 *)arg2)->f6 = D_801EDA40;
        return s1 & 0xFFFF;
    }
    ((Box_80133784 *)arg2)->f6 = D_801EDA40;
    return 0;
}
