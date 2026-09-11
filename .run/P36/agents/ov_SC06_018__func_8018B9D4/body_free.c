void func_8018B9D4(s32 param_1)
{
    struct { u16 a; u16 b; s16 c; u16 d; } t1;
    struct { u16 a; u16 b; s16 c; u16 d; } t2;
    s32 r1, r2, r3, r4;
    s32 pad[2];
    s32 var_ea;
    s32 var_fe;
    s32 var_a0;
    s32 var_v0;

    func_8018BCC4((void *)param_1, 0, (u16 *)(param_1 + 0xE8), 0x81818);
    func_8018BCC4((void *)param_1, 1, (u16 *)(param_1 + 0xE8), 0x204040);
    t1.b = 0;
    t1.a = 0;
    t1.c = -*(u16 *)(param_1 + 0xE8);
    t2.b = 0;
    t2.a = 0;
    t2.c = -*(u16 *)(param_1 + 0xEA);
    (void)r1; (void)r2; (void)r3; (void)r4; (void)pad;
    if (func_8012DEB8(param_1, &t1, &t2) != 0) {
        D_80126B96 = 0x4018;
        D_80126B98 = 0x96;
    }
    var_ea = *(s16 *)(param_1 + 0xEA);
    var_fe = *(s16 *)(param_1 + 0xFE);
    var_a0 = var_ea + 0;
    if (var_ea < var_fe) {
        var_v0 = var_a0 + 0x40;
        *(s16 *)(param_1 + 0xEA) = var_v0;
        if ((var_v0 << 16) >> 16 >= *(s16 *)(param_1 + 0xFE)) {
            *(s16 *)(param_1 + 0xEA) = *(s16 *)(param_1 + 0xFE);
            func_8018BC40(param_1);
        }
    } else {
        var_v0 = *(u16 *)(param_1 + 0xE8) + 0x40;
        *(u16 *)(param_1 + 0xE8) = var_v0;
        if ((var_v0 << 16) >> 16 < *(s16 *)(param_1 + 0xFE)) {
            return;
        }
        if (*(s32 *)(param_1 + 0xCC) != 0) {
            func_80016714((void *)*(s32 *)(param_1 + 0xCC), 0x38);
        }
        *(s32 *)(*(s32 *)(param_1 + 0x64) + 0xD0) = 0;
        func_8012C218((void *)param_1);
    }
}
