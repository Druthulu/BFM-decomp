void func_801ABEE0(void *a0) {
    s32 r0 = (s32)a0;
    s32 ptr1;
    s32 s2;
    s16 v1;
    s32 val;
    s16 orig;
    s16 dec;

    ptr1 = *(s32 *)(r0 + 0xCC);
    s2 = *(s32 *)(r0 + 0xD0);
    func_8012AD80(r0);
    *(s16 *)(ptr1 + 0x8) = *(u16 *)(r0 + 0x6);
    *(s16 *)(ptr1 + 0xA) = *(u16 *)(r0 + 0xA);
    *(s16 *)(ptr1 + 0xC) = *(u16 *)(r0 + 0xE);
    v1 = *(s16 *)(r0 + 0xA);
    if (v1 >= -0x200) {
        *(s16 *)(r0 + 0xA) = -0x200;
        func_801A9270((void *)r0);
    } else {
        if (s2 != 0) {
            ptr1 = *(s32 *)(s2 + 0xCC);
            if (ptr1 != 0) {
                val = (v1 + 0x500) << 4;
                *(s16 *)(ptr1 + 0x1A) = val;
                *(s16 *)(ptr1 + 0x18) = val;
            }
        }
        *(s32 *)(r0 + 0x1C) += 1;
        if ((*(s32 *)(r0 + 0x1C) & 1) == 0) {
            func_801A93F4((void *)r0);
        }
    }
    func_80128ED8(*(s32 *)(r0 + 0xCC), (s32 *)(r0 + 0xF0));
    func_801A9378((void *)r0);
    orig = *(s16 *)(r0 + 0x84);
    if (orig != 0) {
        dec = orig - 1;
        *(s16 *)(r0 + 0x84) = dec;
        if (dec == 0) {
            func_801AA60C((void *)r0, 0xAB8);
        }
    }
}
