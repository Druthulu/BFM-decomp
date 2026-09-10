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
    s32 base;
    s32 flag;
    s32 acc;
    s16 i;
    s16 eq;
    s32 ret;
    s32 frame_pad[8];
    (void)&frame_pad;

    switch (((s32 (*)(void *, s32, s16 *, s16 *))func_80135480)((void *)a0, a1, (s16 *)a2, (s16 *)a3)) {
    case 0:
        return 0;
    case 1:
        base = a0 + 0x34;
        p = (s32 *)((a1 & 0xFFFFFFF) | 0x80000000);
        flag = 0;
        break;
    case 2:
        base = a0 + 0x34;
        p = (s32 *)((a1 & 0xFFFFFFF) | 0x80000000);
        flag = 1;
        break;
    case 3:
        base = a0 + 0x34;
        p = (s32 *)&D_8018E71C;
        flag = 0;
        break;
    case 4:
        base = (s32)&D_8018E6FC;
        p = (s32 *)&D_8018E71C;
        flag = 1;
        break;
    }

    if (a1 < 0) {
        if (func_80135EB0(p, -0x8000) != 0) {
            goto docall;
        }
        for (p = (s32 *)*p; p != 0; p = (s32 *)*p) {
            if (func_80135EB0(p, -0x8000) != 0) {
docall:
                func_80136A94(flag, a0, a3, base);
                return 1;
            }
        }
    } else {
        acc = 0;
        i = 0;
        *(s16 *)((*(u8 **)&D_8017F808) + 6) = -0x7FFF;
        *(s16 *)((*(u8 **)&D_8017F80C) + 6) = 0x7FFF;
        D_8018E6F8 = 0;
        D_8018E6F4 = 0;
        eq = ((V3 *)a2)->x == ((V3 *)a3)->x && ((V3 *)a2)->y == ((V3 *)a3)->y && ((V3 *)a2)->z == ((V3 *)a3)->z;

        while (1) {
            ret = func_80133AB0(0, (s16)(*(Box **)&D_8017F808)->f0, (s16)(*(Box **)&D_8017F808)->f4, (s32)p);
            if (ret == 0) break;
            acc |= ret;
            if (eq != 0) break;
            if (i++ >= 5) return 0;
        }

        if ((s16)acc != 0 || D_8018E6F4 != 0) {
            if ((*(Box **)&D_8017F808)->f6 >= -0xBCB) {
                *(Blk8 *)D_801152A8 = *(Blk8 *)&D_801152B0;
            }
            (*(Box **)&D_8017F810)->f0 = (*(Box **)&D_8017F80C)->f0;
            (*(Box **)&D_8017F810)->f2 = (*(Box **)&D_8017F80C)->f2;
            (*(Box **)&D_8017F810)->f4 = (*(Box **)&D_8017F80C)->f4;
            goto docall;
        }
    }
    return 0;
}
