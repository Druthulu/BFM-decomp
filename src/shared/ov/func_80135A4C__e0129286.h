/* func_80135A4C — shared body (overlay slot 0x80128158, h_exact e0129286). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3) {
    typedef struct { s8 c[8]; } Blk8;
    extern s16 func_80135480(void *param_1, s32 param_2, s16 *param_3, s16 *param_4);
    extern s32 func_80135EB0(void *arg0, s32 arg1_);
    extern s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32 func_80133AB0(s16, s16, s16, s32);
    extern u8 D_8017F808;
    extern u8 D_8017F80C;
    extern s16 *D_8017F810;
    extern s16 D_8018E6F4;
    extern u16 D_8018E6F8;
    extern s32 D_8018E6FC;
    extern s32 D_8018E71C;
    extern u8 D_801152A8[];
    extern u8 D_801152B0;

    s32 *p;
    register s32 s7 __asm__("$23");
    s32 flag;
    s32 acc;
    s16 i;
    s32 eq;
    s32 ret;
    s32 frame_pad[8];
    (void)&frame_pad;

    switch (((s32 (*)(void))func_80135480)()) {
    case 0:
        return 0;
    case 1:
        s7 = a0 + 0x34;
        p = (s32 *)((a1 & 0xFFFFFFF) | 0x80000000);
        flag = 0;
        break;
    case 2:
        s7 = a0 + 0x34;
        p = (s32 *)((a1 & 0xFFFFFFF) | 0x80000000);
        flag = 1;
        break;
    case 3:
        s7 = a0 + 0x34;
        p = (s32 *)&D_8018E71C;
        flag = 0;
        break;
    case 4:
        s7 = (s32)&D_8018E6FC;
        p = (s32 *)&D_8018E71C;
        flag = 1;
        break;
    }

    acc = 0;
    if (a1 < 0) {
        if (func_80135EB0(p, -0x8000) == 0) {
            p = (s32 *)*p;
            if (p == 0) return 0;
        loop:
            if (func_80135EB0(p, -0x8000) == 0) goto next;
        }
    docall:
        func_80136A94(flag, a0, a3, s7);
        return 1;
    next:
        p = (s32 *)*p;
        __asm__ __volatile__("");
        if (p != 0) goto loop;
        return 0;
    }

    i = 0;
    *(s16 *)((*(u8 **)&D_8017F808) + 6) = -0x7FFF;
    *(s16 *)((*(u8 **)&D_8017F80C) + 6) = 0x7FFF;
    D_8018E6F8 = 0;
    D_8018E6F4 = 0;
    {
        s32 t = 0;
        if (((V3 *)a2)->x == ((V3 *)a3)->x && ((V3 *)a2)->y == ((V3 *)a3)->y) {
            s32 zt = (((V3 *)a2)->z == ((V3 *)a3)->z);
            __asm__("addu %0,%1,$zero" : "=r"(t) : "r"(zt));
        }
        eq = t;
    }

    while (1) {
        ret = func_80133AB0(0, (s16)(*(Box **)&D_8017F808)->f0, (s16)(*(Box **)&D_8017F808)->f4, (s32)p);
        if (ret == 0) goto out;
        acc |= ret;
        if (eq != 0) goto out;
        {
            s16 old = i;
            i = i + 1;
            if (old >= 5) return 0;
        }
    }

out:
    if ((s16)acc != 0 || D_8018E6F4 != 0) {
        if ((*(Box **)&D_8017F808)->f6 >= -0xBCB) {
            *(Blk8 *)D_801152A8 = *(Blk8 *)&D_801152B0;
        }
        (*(Box **)&D_8017F810)->f0 = (*(Box **)&D_8017F80C)->f0;
        (*(Box **)&D_8017F810)->f2 = (*(Box **)&D_8017F80C)->f2;
        (*(Box **)&D_8017F810)->f4 = (*(Box **)&D_8017F80C)->f4;
        goto docall;
    }
    return 0;
}
