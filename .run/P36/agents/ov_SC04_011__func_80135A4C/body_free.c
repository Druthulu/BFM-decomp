s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3) {
    typedef struct { s8 c[8]; } Blk8;
    extern s16 func_80135480(void *param_1, s32 param_2, s16 *param_3, s16 *param_4);
    extern s32 func_80135EB0(void *arg0, s32 arg1_);
    extern s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32 func_80133AB0(s16, s16, s16, s32);
    extern u8 D_801909BC;
    extern u8 D_801909C0;
    extern s16 *D_801909C4;
    extern s16 D_801EDA3C;
    extern u16 D_801EDA40;
    extern s32 D_801EDA44;
    extern s32 D_801EDA64;
    extern u8 D_801152A8[];
    extern u8 D_801152B0;

    s32 *p;
    s32 s7;
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
        p = (s32 *)&D_801EDA64;
        flag = 0;
        break;
    case 4:
        s7 = (s32)&D_801EDA44;
        p = (s32 *)&D_801EDA64;
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
        if (p != 0) goto loop;
        return 0;
    }

    i = 0;
    *(s16 *)((*(u8 **)&D_801909BC) + 6) = -0x7FFF;
    *(s16 *)((*(u8 **)&D_801909C0) + 6) = 0x7FFF;
    D_801EDA40 = 0;
    D_801EDA3C = 0;
    {
        s32 t = 0;
        if (((V3 *)a2)->x == ((V3 *)a3)->x && ((V3 *)a2)->y == ((V3 *)a3)->y) {
            s32 zt = (((V3 *)a2)->z == ((V3 *)a3)->z);
            t = zt;
        }
        eq = t;
    }

    while (1) {
        ret = func_80133AB0(0, (s16)(*(Box **)&D_801909BC)->f0, (s16)(*(Box **)&D_801909BC)->f4, (s32)p);
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
    if ((s16)acc != 0 || D_801EDA3C != 0) {
        if ((*(Box **)&D_801909BC)->f6 >= -0xBCB) {
            *(Blk8 *)D_801152A8 = *(Blk8 *)&D_801152B0;
        }
        (*(Box **)&D_801909C4)->f0 = (*(Box **)&D_801909C0)->f0;
        (*(Box **)&D_801909C4)->f2 = (*(Box **)&D_801909C0)->f2;
        (*(Box **)&D_801909C4)->f4 = (*(Box **)&D_801909C0)->f4;
        goto docall;
    }
    return 0;
}
