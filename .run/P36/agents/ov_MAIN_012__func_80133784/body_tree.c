s32 func_80133784(s32 arg0, void *arg1, s32 arg2) {

    extern s32 D_80184120;
    extern s32 func_80047D3C(s32);
    extern s32 func_80133AB0(s16, s16, s16, s32);
    extern Box_80133784 * D_8017E910;
    extern Box_80133784 * D_8017E914;
    extern s16 D_8018412C;
    extern u16 D_80184130;

    s32 s1;
    s32 s2;
    register s16 s3 __asm__("$19");  // !FAKE: pin $19 — NEEDED DIFFERS (P36 rung B tus1)
    register s32 s4 __asm__("$20");  // !FAKE: pin $20 — NEEDED DIFFERS (P36 rung B tus1)
    s16 a0v;
    register s16 arg0s __asm__("$21");  // !FAKE: pin $21 — NEEDED DIFFERS (P36 rung B tus1)
    s32 dx, dy, dz;
    s32 r, ret;

    a0v = ((s16)arg0);
    s1 = 0;
    s3 = 0;
    s4 = 0;
    s2 = 0;
    arg0s = a0v;
    D_8017E910->f6 = -0x7FFF;
    D_8017E914->f6 = 0x7FFF;
    D_8017E910->f0 = ((Box_80133784 *)arg1)->f0;
    D_8017E910->f4 = ((Box_80133784 *)arg1)->f4;
    D_8017E914->f0 = ((Box_80133784 *)arg2)->f0;
    D_8017E914->f4 = ((Box_80133784 *)arg2)->f4;
    D_80184130 = 0;
    D_8018412C = 0;

    if ((s16)a0v == 0) {
        s16 sx = ((Box_80133784 *)arg2)->f0 - ((Box_80133784 *)arg1)->f0;
        s16 sy = ((Box_80133784 *)arg2)->f2 - ((Box_80133784 *)arg1)->f2;
        s16 sz = ((Box_80133784 *)arg2)->f4 - ((Box_80133784 *)arg1)->f4;
        if (sx == 0 && sy == 0) {
            s32 zt = (sz == 0);
            __asm__("addu %0,%1,$zero" : "=r"(s2) : "r"(zt));  // !FAKE: instruction addu — NEEDED DIFFERS (P36 rung B tus1)
        }
        D_8017E910->f2 = ((Box_80133784 *)arg1)->f2 - 4;
        r = func_80047D3C(sx * sx + sz * sz);
        if (r < 3) {
            r = 4;
        } else if (r < 5) {
            r += 1;
        }
        D_8017E914->f2 = ((Box_80133784 *)arg2)->f2 + r + 1;
    } else {
        D_8017E910->f2 = ((Box_80133784 *)arg1)->f2;
        if ((s16)a0v == 2) {
            D_8017E914->f0 = D_8017E910->f0;
            D_8017E914->f2 = D_8017E910->f2 + 6;
            s2 = 1;
            D_8017E914->f4 = D_8017E910->f4;
        } else {
            D_8017E914->f2 = ((Box_80133784 *)arg2)->f2;
        }
    }

    while (1) {
        s32 ret0;
        register s32 retc __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus1)
        ret0 = func_80133AB0(arg0s, (s16)D_8017E910->f0, (s16)D_8017E910->f4, (*(s32*)&D_80184120));
        __asm__("addu %0,%1,$zero" : "=r"(retc) : "r"(ret0));  // !FAKE: instruction addu — NEEDED DIFFERS (P36 rung B tus1)
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

    D_8017E914->f0 = D_8017E910->f0;
    D_8017E914->f2 = D_8017E910->f2;
    s1 = 0x2000;
    D_8017E914->f4 = D_8017E910->f4;
    goto store_out;

after:
    if ((s16)s4 != 0 || D_8018412C != 0) {
        s16 t;
        __asm__ __volatile__("" :: "r"(s4));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus1)
        t = D_8017E910->f6;
        if (t >= -0xBCB) {
            if (t < -0x578) {
                s1 |= 0x4000;
            } else {
                s1 |= 0x8000;
            }
        }
        if ((s16)D_8017E914->f6 < -0xBCB) {
            s1 |= 0x2000;
        }
    store_out:
        ((Box_80133784 *)arg2)->f0 = D_8017E914->f0;
        ((Box_80133784 *)arg2)->f2 = D_8017E914->f2;
        ((Box_80133784 *)arg2)->f4 = D_8017E914->f4;
        ((Box_80133784 *)arg2)->f6 = D_80184130;
        return s1 & 0xFFFF;
    }
    ((Box_80133784 *)arg2)->f6 = D_80184130;
    return 0;
}
