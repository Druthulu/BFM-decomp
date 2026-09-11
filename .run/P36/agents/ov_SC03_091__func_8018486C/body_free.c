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
    s32 cmp;
    s32 pad[2];

    best1 = 0;
    best2 = 0;
    flag = 0;
    t = *(s32 *)(a0 + 0xCC);
    if (t == 0) {
        goto L_D54;
    }
    func_80184AE4(t + 4, 0);
    goto L_D5C;

L_D3C:
    val1 = func_8012BD14((s32)cur);
    best1 = cur;
    flag = 1;
    goto L_D8C;

L_D54:
    func_8013B7AC(0);

L_D5C:
    cur = D_801202A0;
    i = 0;
    cmp = 1;

L_D6C:
    if (func_80184A40((s32)cur) == cmp) {
        goto L_D3C;
    }
    i++;
    cur += 0x10C;
    if (i < 0x60) {
        goto L_D6C;
    }

L_D8C:
    if (flag) {
        goto L_DBC;
    }
    func_8013B7AC(1);
    goto L_DFC;

L_DA4:
    val2 = func_8012BD14((s32)cur);
    best2 = cur;
    flag = 1;
    goto L_DE8;

L_DBC:
    flag = 0;
    if (i >= 0x60) {
        goto L_DE8;
    }
    cmp = 1;

L_DC8:
    if (func_80184A40((s32)cur) == cmp) {
        goto L_DA4;
    }
    i++;
    cur += 0x10C;
    if (i < 0x60) {
        goto L_DC8;
    }

L_DE8:
    if (flag) {
        goto L_E0C;
    }
    func_80184A98((s32)best1, 1);

L_DFC:
    func_8013B7AC(2);
    return;

L_E0C:
    if (i >= 0x60) {
        goto L_E78;
    }
    flag = 1;

L_E18:
    if (func_80184A40((s32)cur) == flag) {
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
    i++;
    cur += 0x10C;
    if (i < 0x60) {
        goto L_E18;
    }

L_E78:
    func_80184A98((s32)best1, 1);
    func_80184A98((s32)best2, 2);
}
