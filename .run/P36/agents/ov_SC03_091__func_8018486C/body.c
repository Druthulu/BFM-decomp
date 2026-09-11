void func_8018486C(s32 a0) {

    extern u8 D_801202A0[];
    s32 i;
    s32 v1;
    s32 val1;
    s32 val2;
    u8 *cur;
    u8 *best1;
    u8 *best2;
    s32 flag;
    s32 t;
    s32 pad[2];

    best1 = 0;
    best2 = 0;
    flag = 0;
    t = *(s32 *)(a0 + 0xCC);
    if (t != 0) {
        func_80184AE4(t + 4, 0);
    } else {
        func_8013B7AC(0);
    }

    cur = D_801202A0;
    for (i = 0; i < 0x60; i++, cur += 0x10C) {
        if (func_80184A40((s32)cur) == 1) {
            val1 = func_8012BD14((s32)cur);
            best1 = cur;
            flag = 1;
            break;
        }
    }
    if (!flag) {
        func_8013B7AC(1);
        func_8013B7AC(2);
        return;
    }

    flag = 0;
    for (; i < 0x60; i++, cur += 0x10C) {
        if (func_80184A40((s32)cur) == 1) {
            val2 = func_8012BD14((s32)cur);
            best2 = cur;
            flag = 1;
            break;
        }
    }
    if (!flag) {
        func_80184A98((s32)best1, 1);
        func_8013B7AC(2);
        return;
    }

    for (; i < 0x60; i++, cur += 0x10C) {
        if (func_80184A40((s32)cur) == 1) {
            v1 = func_8012BD14((s32)cur);
            if (v1 < val1) {
                best2 = best1;
                best1 = cur;
                val2 = val1;
                val1 = v1;
            } else if (v1 < val2) {
                best2 = cur;
                val2 = v1;
            }
        }
    }
    func_80184A98((s32)best1, 1);
    func_80184A98((s32)best2, 2);
}
