/* func_80135EB0 — shared body (overlay slot 0x80128158, h_text 82164aab). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80135EB0(void *arg0, s32 arg1_) {
    extern u8 D_801152A8[];
    extern s16 D_801152AA;
    extern s16 D_801152AC;
    extern s16 D_80126722;
    extern s16 D_80126724;
    register s32 arg1 __asm__("$19") = arg1_;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 m1;
    s32 m2;
    s32 t4;
    s32 t5;
    s32 t6;
    s32 n1;
    s32 n2;
    s32 r;
    s32 sv;
    register s32 w __asm__("$5");
    void *q;

    t1 = (*(s16 **)&D_8017F054)[0];
    if (t1 < M2C_FIELD(arg0, s16 *, 4)) {
        m1 = 1;
    } else {
        m1 = (M2C_FIELD(arg0, s16 *, 6) < t1) << 1;
    }
    t2 = (*(s16 **)&D_8017F054)[2];
    if (t2 < M2C_FIELD(arg0, s16 *, 0xC)) {
        m1 |= 4;
    } else if (M2C_FIELD(arg0, s16 *, 0xE) < t2) {
        m1 |= 8;
    }
    t3 = (*(s16 **)&D_8017F054)[1];
    if (t3 < M2C_FIELD(arg0, s16 *, 8)) {
        m2 = 0x10;
    } else {
        m2 = (M2C_FIELD(arg0, s16 *, 0xA) < t3) << 5;
    }
    if ((m1 | m2) == 0) {
        u16 *ac;
        s16 *b4;
        s32 c0;
        s32 c1;
        s32 h0;
        s32 h1;

        ac = *(u16 **)&D_8017F054;
        b4 = D_8017F05C;
        c0 = ac[0];
        b4[0] = c0;
        h0 = (M2C_FIELD(arg0, s16 *, 4) + M2C_FIELD(arg0, s16 *, 6)) >> 1;
        D_801152AA = 0;
        (*(s16 *)D_80126720) = h0;
        (*(s16 *)D_801152A8) = c0 - h0;
        __asm__ __volatile__("");
        c1 = ac[2];
        b4[2] = c1;
        h1 = (M2C_FIELD(arg0, s16 *, 0xC) + M2C_FIELD(arg0, s16 *, 0xE)) >> 1;
        D_80126724 = h1;
        D_801152AC = c1 - h1;
        __asm__ __volatile__("");
        b4[1] = ac[1];
        D_80126722 = (M2C_FIELD(arg0, s16 *, 8) + M2C_FIELD(arg0, s16 *, 0xA)) >> 1;
        VectorNormalSS(D_801152A8, D_801152A8);
        D_801150D8 |= 1;
        return 1;
    }

    t4 = (*(s16 **)&D_8017F058)[0];
    if (t4 < M2C_FIELD(arg0, s16 *, 4)) {
        n1 = 1;
    } else {
        n1 = (M2C_FIELD(arg0, s16 *, 6) < t4) << 1;
    }
    t5 = (*(s16 **)&D_8017F058)[2];
    if (t5 < M2C_FIELD(arg0, s16 *, 0xC)) {
        n1 |= 4;
    } else if (M2C_FIELD(arg0, s16 *, 0xE) < t5) {
        n1 |= 8;
    }
    t6 = (*(s16 **)&D_8017F058)[1];
    if (t6 < M2C_FIELD(arg0, s16 *, 8)) {
        n2 = 0x10;
    } else {
        n2 = (M2C_FIELD(arg0, s16 *, 0xA) < t6) << 5;
    }
    if (((m1 | m2) & (n1 | n2)) != 0) {
        goto ret0;
    }
    {
        u16 *b0 = *(u16 **)&D_8017F058;
        u16 *ac = *(u16 **)&D_8017F054;
        s16 *b8 = *(s16 **)&D_8017F060;

        b8[0] = b0[0] - ac[0];
        b8[1] = b0[1] - ac[1];
        b8[2] = b0[2] - ac[2];
    }

    switch (m1) {
    case 4:
        q = arg0;
        sv = M2C_FIELD(arg0, s16 *, 0xC);
        w = arg1 << 16;
        goto L288;
    case 1:
        r = func_801365B8(arg0, (s16) arg1, M2C_FIELD(arg0, s16 *, 4));
        __asm__ __volatile__("");
        goto done;
    case 2:
        r = func_801365B8(arg0, (s16) (arg1 | 1), M2C_FIELD(arg0, s16 *, 6));
        __asm__ __volatile__(" ");
        goto done;
    case 5:
        if (func_80136334(arg0, (s16) arg1, M2C_FIELD(arg0, s16 *, 0xC)) != 0) {
            return 1;
        }
        r = func_801365B8(arg0, (s16) arg1, M2C_FIELD(arg0, s16 *, 4));
        goto done;
    case 6:
        if (func_80136334(arg0, (s16) arg1, M2C_FIELD(arg0, s16 *, 0xC)) != 0) {
            return 1;
        }
        r = func_801365B8(arg0, (s16) (arg1 | 1), M2C_FIELD(arg0, s16 *, 6));
        goto done;
    case 9:
        if (func_801365B8(arg0, (s16) arg1, M2C_FIELD(arg0, s16 *, 4)) != 0) {
            return 1;
        }
        /* fallthrough */
    case 8:
        q = arg0;
        sv = M2C_FIELD(arg0, s16 *, 0xE);
        w = (arg1 | 1) << 16;
    L288:
        r = func_80136334(q, w >> 16, sv);
        goto done;
    ret0:
        return 0;
    case 10:
        if (func_801365B8(arg0, (s16) (arg1 | 1), M2C_FIELD(arg0, s16 *, 6)) != 0) {
            return 1;
        }
        r = func_80136334(arg0, (s16) (arg1 | 1), M2C_FIELD(arg0, s16 *, 0xE));
    done:
        if (r != 0) {
            return 1;
        }
    case 0:
        if (m2 == 0) {
            goto ret0;
        }
        if (m2 == 0x10) {
            if (((s32 (*)(void *, s32, s32))func_80136824)(arg0, (s16) arg1, M2C_FIELD(arg0, s16 *, 8)) == 0) {
                goto ret0;
            }
        } else {
            if (((s32 (*)(void *, s32, s32))func_80136824)(arg0, (s16) (arg1 | 1), M2C_FIELD(arg0, s16 *, 0xA)) == 0) {
                goto ret0;
            }
        }
    default:
        return 1;
    }
}
