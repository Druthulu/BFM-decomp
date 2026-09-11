void func_8018B9D4(s32 param_1)
{
    struct { u16 a; u16 b; s16 c; u16 d; } t1;
    struct { u16 a; u16 b; s16 c; u16 d; } t2;

    func_8018BCC4((void *)param_1, 0, (u16 *)(param_1 + 0xE8), 0x81818);
    func_8018BCC4((void *)param_1, 1, (u16 *)(param_1 + 0xE8), 0x204040);
    t1.b = 0;
    t1.a = 0;
    t1.c = -*(u16 *)(param_1 + 0xE8);
    t2.b = 0;
    t2.a = 0;
    t2.c = -*(u16 *)(param_1 + 0xEA);
    if (func_8012DEB8(param_1, &t1, &t2) != 0) {
        D_80126B96 = 0x4018;
        D_80126B98 = 0x96;
    }
    if (*(s16 *)(param_1 + 0xEA) < *(s16 *)(param_1 + 0xFE)) {
        *(s16 *)(param_1 + 0xEA) += 0x40;
        if (*(s16 *)(param_1 + 0xEA) >= *(s16 *)(param_1 + 0xFE)) {
            *(s16 *)(param_1 + 0xEA) = *(s16 *)(param_1 + 0xFE);
            func_8018BC40(param_1);
        }
    } else {
        *(s16 *)(param_1 + 0xE8) += 0x40;
        if (*(s16 *)(param_1 + 0xE8) < *(s16 *)(param_1 + 0xFE)) {
            return;
        }
        if (*(s32 *)(param_1 + 0xCC) != 0) {
            func_80016714((void *)*(s32 *)(param_1 + 0xCC), 0x38);
        }
        *(s32 *)(*(s32 *)(param_1 + 0x64) + 0xD0) = 0;
        func_8012C218((void *)param_1);
    }
}
